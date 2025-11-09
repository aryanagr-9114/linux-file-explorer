#ifndef EXPLORER_H
#define EXPLORER_H

#include <string>

void listDirectory(const std::string &path);
bool changeDirectory(const std::string &path);
std::string getCurrentPath();

#endif // EXPLORER_H
