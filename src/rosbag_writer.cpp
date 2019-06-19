#include <rosdebug_tools/rosbag_writer.h>

namespace rosdebug_tools
{
    RosbagWriter::RosbagWriter(ros::NodeHandle nh)
    {

    }

    RosbagWriter::~RosbagWriter()
    {

    }

    void RosbagWriter::logTopic(std::string topic)
    {
        buf_.push_back(boost::make_shared<message_buffer>(nh_,topic));
        return;
    }

    void RosbagWriter::write(std::string path)
    {
        rosbag::Bag bag;
        bag.open(path, rosbag::bagmode::Write);
        for(auto buf_itr_ = buf_.begin(); buf_itr_ != buf_.end(); buf_itr_++)
        {
            boost::shared_ptr<message_buffer> itr_ptr = *buf_itr_;
            std::vector<ros::MessageEvent<topic_tools::ShapeShifter const> > messages = itr_ptr->getBuffer();
            for(auto message_itr = messages.begin(); message_itr != messages.end(); message_itr++)
            {
                bag.write("chatter", *message_itr);
            }
        }
        return;
    }
}