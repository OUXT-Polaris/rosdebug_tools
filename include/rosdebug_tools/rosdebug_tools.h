#ifndef ROSDEBUG_TOOLS_H_INCLUDED
#define ROSDEBUG_TOOLS_H_INCLUDED

//headers in this package
#include <rosdebug_tools/message_buffer.h>

//headers in ROS
#include <ros/ros.h>

//headers in glog
#include <glog/logging.h>

//headers in boost
#include <boost/thread.hpp>
#include <boost/bind.hpp>

class rosdebug_tools
{
public:
    rosdebug_tools();
    ~rosdebug_tools();
    static void _failure_callback();
private:
    static boost::shared_ptr<message_buffer> _buf;
};

#endif  //ROSDEBUG_TOOLS_H_INCLUDED