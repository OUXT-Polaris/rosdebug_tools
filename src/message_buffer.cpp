#include <rosdebug_tools/message_buffer.h>

namespace rosdebug_tools
{
    message_buffer::message_buffer(ros::NodeHandle nh,std::string topic) : buffer_length_(3)
    {
        boost::shared_ptr<int> count = boost::make_shared<int>(0);
        nh_ = nh;
        *sub_ptr_ = nh_.subscribe<topic_tools::ShapeShifter>(topic, 1, boost::bind(&message_buffer::callback, this, _1, topic, sub_ptr_, count));
    }

    message_buffer::message_buffer(ros::NodeHandle nh,std::string topic,double buffer_length) : buffer_length_(buffer_length)
    {
        boost::shared_ptr<int> count = boost::make_shared<int>(0);
        nh_ = nh;
        *sub_ptr_ = nh_.subscribe<topic_tools::ShapeShifter>(topic, 1, boost::bind(&message_buffer::callback, this, _1, topic, sub_ptr_, count));
    }

    message_buffer::~message_buffer()
    {

    }

    std::vector<ros::MessageEvent<topic_tools::ShapeShifter const> > message_buffer::getBuffer()
    {
        boost::mutex::scoped_lock look(mtx_);
        return message_events_;
    }

    void message_buffer::callback(ros::MessageEvent<topic_tools::ShapeShifter const> msg_event, std::string const& topic, boost::shared_ptr<ros::Subscriber> subscriber, boost::shared_ptr<int> count)
    {
        boost::mutex::scoped_lock look(mtx_);
        message_events_.push_back(msg_event);
        updateEvents();
    }

    void message_buffer::updateEvents()
    {
        boost::mutex::scoped_lock look(mtx_);
        std::vector<ros::MessageEvent<topic_tools::ShapeShifter const> > newmessage_events;
        for(int i=0; i<message_events_.size(); i++)
        {
            if(message_events_[i].getReceiptTime() > ros::Time::now() - buffer_length_)
            {
                newmessage_events.push_back(message_events_[i]);
            }
        }
        message_events_ = newmessage_events;
    }
}