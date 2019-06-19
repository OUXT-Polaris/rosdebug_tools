#ifndef ROSDEBUG_TOOLS_ROSBAG_WRITER_H_INCLUDED
#define ROSDEBUG_TOOLS_ROSBAG_WRITER_H_INCLUDED

//headers in this package
#include <rosdebug_tools/message_buffer.h>

//headers in rosbag
#include <rosbag/bag.h>

namespace rosdebug_tools
{
    class RosbagWriter
    {
    public:
        RosbagWriter(ros::NodeHandle nh);
        ~RosbagWriter();
        void logTopic(std::string topic);
        void write(std::string path);
    private:
        std::vector<boost::shared_ptr<message_buffer> > buf_;
        ros::NodeHandle nh_;
    };
}

#endif  //ROSDEBUG_TOOLS_ROSBAG_WRITER_H_INCLUDED