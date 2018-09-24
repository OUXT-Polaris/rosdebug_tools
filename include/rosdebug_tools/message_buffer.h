#ifndef MESSAGE_BUFFER_H_INCLUDED
#define MESSAGE_BUFFER_H_INCLUDED

//headers in ROS
#include <ros/ros.h>
#include <topic_tools/shape_shifter.h>

//headers in Boost
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

class message_buffer
{
public:
    message_buffer(std::string topic);
    message_buffer(std::string topic,double buffer_length);
    ~message_buffer();
    std::vector<ros::MessageEvent<topic_tools::ShapeShifter const> > get_buffer();
private:
    void _callback(ros::MessageEvent<topic_tools::ShapeShifter const> msg_event, std::string const& topic, boost::shared_ptr<ros::Subscriber> subscriber, boost::shared_ptr<int> count);
    void _update_events();
    ros::NodeHandle _nh;
    boost::shared_ptr<ros::Subscriber> _sub_ptr;
    boost::mutex _mtx;
    std::vector<ros::MessageEvent<topic_tools::ShapeShifter const> > _message_events;
    ros::Duration _buffer_length;
};

#endif //MESSAGE_BUFFER_H_INCLUDED