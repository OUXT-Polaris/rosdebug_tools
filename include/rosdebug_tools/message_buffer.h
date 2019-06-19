#ifndef ROSDEBUG_TOOLS_MESSAGE_BUFFER_H_INCLUDED
#define ROSDEBUG_TOOLS_MESSAGE_BUFFER_H_INCLUDED

//headers in ROS
#include <ros/ros.h>
#include <topic_tools/shape_shifter.h>

//headers in Boost
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

namespace rosdebug_tools
{
    class message_buffer
    {
    public:
        message_buffer(ros::NodeHandle nh,std::string topic);
        message_buffer(ros::NodeHandle nh,std::string topic,double buffer_length);
        ~message_buffer();
        std::vector<ros::MessageEvent<topic_tools::ShapeShifter const> > getBuffer();
    private:
        void callback(ros::MessageEvent<topic_tools::ShapeShifter const> msg_event, std::string const& topic, boost::shared_ptr<ros::Subscriber> subscriber, boost::shared_ptr<int> count);
        void updateEvents();
        ros::NodeHandle nh_;
        boost::shared_ptr<ros::Subscriber> sub_ptr_;
        boost::mutex mtx_;
        std::vector<ros::MessageEvent<topic_tools::ShapeShifter const> > message_events_;
        ros::Duration buffer_length_;
    };
}

#endif //ROSDEBUG_TOOLS_MESSAGE_BUFFER_H_INCLUDED