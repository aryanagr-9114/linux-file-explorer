#ifndef FILEOPS_H
#define FILEOPS_H

#include <string>

void createFile(const std::string &path);
void createDirectory(const std::string &path);
void removePath(const std::string &path);
bool copyPath(const std::string &src, const std::string &dst);
bool movePath(const std::string &src, const std::string &dst);
void searchRecursive(const std::string &startPath, const std::string &pattern);
void viewPermissions(const std::string &path);
void changePermissions(const std::string &path, const std::string &octalMode);

#endif // FILEOPS_H
