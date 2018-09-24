#include <rosdebug_tools/rosdebug_tools.h>

rosdebug_tools::rosdebug_tools()
{
    _buf = boost::make_shared<message_buffer>("imu");
    google::InitGoogleLogging("");
    google::InstallFailureSignalHandler();
    void (*func)() = _failure_callback;
    google::InstallFailureFunction(func);
}

rosdebug_tools::~rosdebug_tools()
{

}

void rosdebug_tools::_failure_callback()
{

}