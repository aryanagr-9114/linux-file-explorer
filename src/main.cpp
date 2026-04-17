#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "explorer.h"
#include "fileops.h"

static std::vector<std::string> splitArgs(const std::string &s) {
    std::istringstream iss(s);
    std::vector<std::string> v;
    std::string t;
    while (iss >> t) {
        v.push_back(t);
    }
    return v;
}

int main() {
    std::string currentPath = getCurrentPath();
    std::string line;
    std::cout << "Simple Console File Explorer\nType 'help' for commands.\n";
    while (true) {
        currentPath = getCurrentPath();
        std::cout << "[" << currentPath << "] > ";
        if (!std::getline(std::cin, line)) break; // EOF
        if (line.empty()) continue;
        auto args = splitArgs(line);
        if (args.empty()) continue;
        std::string cmd = args[0];
        if (cmd == "exit" || cmd == "quit") break;
        else if (cmd == "help") {
            std::cout << "Commands:\n"
                      << " ls\n cd <dir>\n pwd\n create-file <name>\n mkdir <name>\n rm <path>\n cp <src> <dst>\n mv <src> <dst>\n search <pattern>\n viewperm <path>\n chmod <octal> <path>\n help\n exit\n";
        } else if (cmd == "ls") {
            listDirectory(currentPath);
        } else if (cmd == "pwd") {
            std::cout << currentPath << "\n";
        } else if (cmd == "cd") {
            if (args.size() < 2) std::cout << "Usage: cd <dir>\n";
            else changeDirectory(args[1]);
        } else if (cmd == "create-file") {
            if (args.size() < 2) std::cout << "Usage: create-file <name>\n";
            else createFile(currentPath + "/" + args[1]);
        } else if (cmd == "mkdir") {
            if (args.size() < 2) std::cout << "Usage: mkdir <name>\n";
            else createDirectory(currentPath + "/" + args[1]);
        } else if (cmd == "rm") {
            if (args.size() < 2) std::cout << "Usage: rm <path>\n";
            else {
                std::cout << "Are you sure you want to remove '" << args[1] << "'? (y/n): ";
                std::string r; std::getline(std::cin, r);
                if (!r.empty() && (r[0] == 'y' || r[0] == 'Y')) removePath(currentPath + "/" + args[1]);
                else std::cout << "Aborted.\n";
            }
        } else if (cmd == "cp") {
            if (args.size() < 3) std::cout << "Usage: cp <src> <dst>\n";
            else copyPath(currentPath + "/" + args[1], currentPath + "/" + args[2]);
        } else if (cmd == "mv") {
            if (args.size() < 3) std::cout << "Usage: mv <src> <dst>\n";
            else movePath(currentPath + "/" + args[1], currentPath + "/" + args[2]);
        } else if (cmd == "search") {
            if (args.size() < 2) std::cout << "Usage: search <pattern>\n";
            else searchRecursive(currentPath, args[1]);
        } else if (cmd == "viewperm") {
            if (args.size() < 2) std::cout << "Usage: viewperm <path>\n";
            else viewPermissions(currentPath + "/" + args[1]);
        } else if (cmd == "chmod") {
            if (args.size() < 3) std::cout << "Usage: chmod <octal> <path>\n";
            else changePermissions(currentPath + "/" + args[2], args[1]);
        } else {
            std::cout << "Unknown command: " << cmd << " (type 'help')\n";
        }
    }
    return 0;
}
