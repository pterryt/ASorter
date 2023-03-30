#include "monitor.h"
#include "mover.h"
#include <fstream>
#include <unistd.h>

using namespace std;

#define EVENT_SIZE ( sizeof (struct inotify_event) )

Monitor::Monitor(const string &dir) : m_fd(-1), m_wd(-1), m_directory(dir)
{
    m_fd = inotify_init();
    if (m_fd < 0)
    {
        cerr << "Failed to initialize inotify." << endl;
        throw runtime_error("Failed to initialize inotify.");
    }
    m_wd = inotify_add_watch(m_fd, dir.c_str(), IN_CREATE);
    if (m_wd < 0)
    {
        cerr << "Failed to add watch." << endl;
        throw runtime_error("Failed to add watch.");
    }
}

Monitor::~Monitor()
{
    if (m_wd > 0)
    {
        inotify_rm_watch(m_fd, m_wd);
    }
    if (m_fd > 0)
    {
        close(m_fd);
    }
}

void Monitor::startMonitoring()
{
    while (true)
    {
        ssize_t len = read(m_fd, m_buffer, sizeof(m_buffer));
        if (len < 0)
        {
            cerr << "Empty buffer on read." << endl;
            throw runtime_error("Empty buffer on read.");
        }
        handleEvents(len);
    }
}

void Monitor::handleEvents(ssize_t length)
{
    for (char *ptr = m_buffer; ptr < m_buffer + length; ptr += EVENT_SIZE + ((struct inotify_event *) ptr)->len)
    {
        handleEvent((const struct inotify_event *) ptr);
    }
}

void Monitor::handleEvent(const struct inotify_event *event)
{
    if (event->mask & IN_CREATE)
    {
        string finalName = string(m_directory) + string(event->name);
        moveFiles(finalName);
    }
}

