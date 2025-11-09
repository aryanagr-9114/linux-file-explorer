#include "explorer.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

// Color
const std::string COLOR_BLUE = "\033[1;34m";
const std::string COLOR_GREEN = "\033[1;32m";
const std::string COLOR_GRAY  = "\033[0;37m";
const std::string COLOR_YELLOW= "\033[1;33m";
const std::string COLOR_RESET = "\033[0m";

// Icons
const std::string ICON_DIR   = "📁 ";
const std::string ICON_FILE  = "📄 ";
const std::string ICON_EXEC  = "⚙️  ";
const std::string ICON_OTHER = "🔹 ";

void listDirectory(const std::string &path) {
    try {
        if (!fs::exists(path)) {
            std::cerr << "Path does not exist: " << path << '\n';
            return;
        }

        for (const auto &entry : fs::directory_iterator(path)) {
            auto p = entry.path();
            std::string name = p.filename().string();

            if (entry.is_directory()) {
                std::cout << "[DIR]  " << COLOR_BLUE << ICON_DIR << name << COLOR_RESET << '\n';
            } else if (entry.is_regular_file()) {
                // detect if file is executable
                fs::perms perms = fs::status(p).permissions();
                bool exec = (perms & fs::perms::owner_exec) != fs::perms::none;
                if (exec) {
                    std::cout << "[FILE] " << COLOR_YELLOW << ICON_EXEC << name << COLOR_RESET
                              << " (" << fs::file_size(p) << " bytes)\n";
                } else {
                    std::cout << "[FILE] " << COLOR_GREEN << ICON_FILE << name << COLOR_RESET
                              << " (" << fs::file_size(p) << " bytes)\n";
                }
            } else {
                std::cout << "[OTHER] " << COLOR_GRAY << ICON_OTHER << name << COLOR_RESET << '\n';
            }
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Error listing directory: " << e.what() << '\n';
    }
}

bool changeDirectory(const std::string &path) {
    try {
        fs::path p(path);
        if (p.is_relative()) p = fs::current_path() / p;
        if (fs::exists(p) && fs::is_directory(p)) {
            fs::current_path(p);
            return true;
        } else {
            std::cerr << "No such directory: " << p.string() << '\n';
            return false;
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "chdir error: " << e.what() << '\n';
        return false;
    }
}

std::string getCurrentPath() {
    return fs::current_path().string();
}
