#ifndef ROSDEBUG_TOOLS_ROSDEBUG_TOOLS_H_INCLUDED
#define ROSDEBUG_TOOLS_ROSDEBUG_TOOLS_H_INCLUDED

//headers in this package
#include <rosdebug_tools/rosbag_writer.h>
#include <rosdebug_tools/LoggedData.h>

//headers in ROS
#include <ros/ros.h>

//headers in glog
#include <glog/logging.h>

//headers in boost
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>

namespace rosdebug_tools
{
    class RosdebugTools
    {
    public:
        RosdebugTools(ros::NodeHandle nh,ros::NodeHandle pnh);
        ~RosdebugTools();
        void logTopic(std::string topic);
        static void failureCallback();
    private:
        static std::shared_ptr<RosbagWriter> writer_ptr_;
        ros::NodeHandle nh_;
        ros::NodeHandle pnh_;
    };
}

#endif  //ROSDEBUG_TOOLS_ROSDEBUG_TOOLS_H_INCLUDED