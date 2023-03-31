#include "monitor.h"
#include "daemonizer.h"

int main()
{
    // make the object a daemon process
    daemonizer();
    // check the status of directories and creates those missing
    init();

    // start monitoring the specified folder for file creates
    Monitor fileMonitor("/home/phil/_downloads/");
    fileMonitor.startMonitoring();

    return 0;
}
