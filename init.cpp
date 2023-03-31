#include <dirent.h>
#include <cerrno>
#include <sys/stat.h>
#include <iostream>
#include "init.h"
#include <yaml-cpp//yaml.h>

using namespace std;

vector<string> vidExt =
        {
        ".mp4", ".avi", ".mov", ".wmv", ".flv", ".mkv", ".webm", ".mpg", ".mpeg", ".m4v"
        };
vector<string> subExt =
        {
        ".srt", ".ass"
        };
vector<string> txtExt =
        {
        ".txt", ".doc", ".docx", ".pdf", ".rtf", ".csv", ".xml", ".html", ".htm", ".json", ".md",
        ".log", ".cfg", ".ini", ".sql", ".py", ".java", ".cpp", ".h", ".c", ".php", ".js", ".css",
        ".scss", ".less", ".jsx", ".ts", ".tsx", ".go", ".rs", ".swift"
        };
vector<string> archExt =
        {
        ".zip", ".rar", ".tar", ".gz", ".7z", ".bz2", ".xz", ".z", ".iso", ".cab"
        };
vector<string> audExt =
        {
        ".mp3", ".wav", ".flac", ".aac", ".wma", ".ogg", ".m4a"
        };
vector<string> picExt =
        {
        ".png", ".jpg"
        };

const char *subdirs[] =
        {
                "/home/phil/_downloads/_Video/",
                "/home/phil/_downloads/_Subtitle/",
                "/home/phil/_downloads/_Text/",
                "/home/phil/_downloads/_Archive/",
                "/home/phil/_downloads/_Music/",
                "/home/phil/_downloads/_Pictures/"
        };

const char *ddir = "/home/phil/_downloads/";

unordered_map<string, int> initializeExt(int count, ...)
{
    va_list args;
    unordered_map<string, int> extMap;
    va_start(args, count);

    for (int i = 0; i < count; i++)
    {
        vector<string>* extList = va_arg(args, vector<string>*);

        for (string const& str: *extList){
            extMap.insert(pair(str, i));
        }
    }

    va_end(args);
    return extMap;
}

unordered_map<string, int>  extMList = initializeExt(6, &vidExt, &subExt, &txtExt, &archExt, &audExt, &picExt);

void init()
{
    initMain();
    initSub();
}

void initMain()
{
    makeDir(ddir);
}


void initSub()
{
    for (auto dir : subdirs)
    {
        makeDir(dir);
    }
}

void makeDir(const char *dirpath)
{
    DIR *dir = opendir(dirpath);

    if (dir) {
        closedir(dir);
        std::cout << "Skipped directory creation of (" + std::string(dirpath) +
        ") because it already exists." << std::endl;
    }

    else if (ENOENT == errno)
    {
        if (mkdir(dirpath,0744) == -1)
        {
            std::cout << "Couldn't make (" + std::string(dirpath) + ") directory." << std::endl;
        }
        else {
            std::cout << "Successfully made (" + std::string(dirpath) + ") directory" << std::endl;
        }
    }

    else
    {
        std::cout << "Life sucks." << std::endl;
    }
}

