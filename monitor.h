#pragma once
#include "init.h"
#include <sys/inotify.h>

#define EVENT_SIZE ( sizeof (struct inotify_event) )
#define BUF_LEN ( 1024 * (EVENT_SIZE + 16) )

class Monitor {
public:
    explicit Monitor(const std::string& dir);
    ~Monitor();
    void startMonitoring();

private:
    int m_fd;
    int m_wd;
    std::string m_directory;
    char m_buffer[BUF_LEN];

    void handleEvents(ssize_t length);
    void handleEvent(const struct inotify_event* event);
};

