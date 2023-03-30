#include "monitor.h"
int main() {
    init();
    Monitor fileMonitor("/home/phil/Downloads/");
    fileMonitor.startMonitoring();
    return 0;
}
