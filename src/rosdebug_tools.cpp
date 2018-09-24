#include <rosdebug_tools/rosdebug_tools.h>

rosdebug_tools::rosdebug_tools()
{
    google::InitGoogleLogging("");
    google::InstallFailureSignalHandler();
}

rosdebug_tools::~rosdebug_tools()
{

}