#pragma once
#include <cstdarg>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

extern const char *ddir;
extern const char *subdirs[];

extern std::vector<std::string> vidExt;
extern std::vector<std::string> subExt;
extern std::vector<std::string> txtExt;
extern std::vector<std::string> archExt;
extern std::vector<std::string> audExt;

void init();
void makeDir(const char *dirpath);
void initMain();
void initSub();

extern std::unordered_map<std::string, int> extMList;

std::unordered_map<std::string, int> initializeExt(int count, ...);
