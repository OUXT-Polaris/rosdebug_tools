#include <rosdebug_tools/message_buffer.h>

message_buffer::message_buffer(std::string topic) : _buffer_length(3)
{
    boost::shared_ptr<int> count = boost::make_shared<int>(0);
    *_sub_ptr = _nh.subscribe<topic_tools::ShapeShifter>(topic, 1, boost::bind(&message_buffer::_callback, this, _1, topic, _sub_ptr, count));
}

message_buffer::message_buffer(std::string topic,double buffer_length) : _buffer_length(buffer_length)
{
    boost::shared_ptr<int> count = boost::make_shared<int>(0);
    *_sub_ptr = _nh.subscribe<topic_tools::ShapeShifter>(topic, 1, boost::bind(&message_buffer::_callback, this, _1, topic, _sub_ptr, count));
}

message_buffer::~message_buffer()
{

}

void message_buffer::_callback(ros::MessageEvent<topic_tools::ShapeShifter const> msg_event, std::string const& topic, boost::shared_ptr<ros::Subscriber> subscriber, boost::shared_ptr<int> count)
{
    boost::mutex::scoped_lock look(_mtx);
    _message_events.push_back(msg_event);
}

void message_buffer::_update_events()
{
    boost::mutex::scoped_lock look(_mtx);
}