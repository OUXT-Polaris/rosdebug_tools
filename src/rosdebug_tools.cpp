#include <rosdebug_tools/rosdebug_tools.h>

namespace rosdebug_tools
{
    RosdebugTools::RosdebugTools(ros::NodeHandle nh,ros::NodeHandle pnh)
    {
        google::InitGoogleLogging("");
        google::InstallFailureSignalHandler();
        void (*func)() = failureCallback;
        google::InstallFailureFunction(func);
        nh_ = nh;
        pnh_ = pnh;
        writer_ptr_ = std::make_shared<RosbagWriter>(nh_);
    }

    RosdebugTools::~RosdebugTools()
    {

    }

    void RosdebugTools::failureCallback()
    {
        using namespace boost::uuids;
        const uuid id = random_generator()();
        std::string rosbag_filename = boost::lexical_cast<std::string>(id);
        ros::Publisher stacktrace_pub_;
        ros::NodeHandle nh;
        stacktrace_pub_ = nh.advertise<rosdebug_tools::LoggedData>("/logged_data",1,true);
        rosdebug_tools::LoggedData log;
        log.header.stamp = ros::Time::now();
        log.node = ros::this_node::getName();
        log.rosbag_filepath = "/tmp/"+rosbag_filename+".bag";
        stacktrace_pub_.publish(log);
        writer_ptr_->write(log.rosbag_filepath);
    }

    void RosdebugTools::logTopic(std::string topic)
    {
        writer_ptr_->logTopic(topic);
    }
}