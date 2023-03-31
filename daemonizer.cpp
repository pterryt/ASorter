#include "daemonizer.h"
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int daemonizer()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        std::cerr << "Failed to fork\n";
        return 1;
    }
    else if (pid > 0)
    {
        return 0;
    }


    setsid();

    chdir("/");

    for (int fd = sysconf(_SC_OPEN_MAX); fd >= 0; --fd)
    {
        close(fd);
    }
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);

    umask(022);

    return 0;
}
