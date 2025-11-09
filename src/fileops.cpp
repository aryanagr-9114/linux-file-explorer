#include "fileops.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>

namespace fs = std::filesystem;

void createFile(const std::string &path) {
    std::ofstream out(path, std::ios::binary);
    if (!out)
        std::cerr << "Failed to create file: " << path << '\n';
}

void createDirectory(const std::string &path) {
    std::error_code ec;
    if (!fs::create_directory(path, ec)) {
        if (ec)
            std::cerr << "mkdir failed: " << ec.message() << '\n';
    }
}

void removePath(const std::string &path) {
    std::error_code ec;
    fs::remove_all(path, ec);
    if (ec)
        std::cerr << "remove failed: " << ec.message() << '\n';
}

bool copyPath(const std::string &src, const std::string &dst) {
    std::error_code ec;
    fs::path s(src), d(dst);
    if (!fs::exists(s)) {
        std::cerr << "Source does not exist: " << src << '\n';
        return false;
    }
    if (fs::is_directory(s)) {
        fs::create_directories(d, ec);
        fs::copy(s, d, fs::copy_options::recursive | fs::copy_options::overwrite_existing, ec);
        if (ec) {
            std::cerr << "copy error: " << ec.message() << '\n';
            return false;
        }
    } else {
        fs::copy_file(s, d, fs::copy_options::overwrite_existing, ec);
        if (ec) {
            std::cerr << "copy failed: " << ec.message() << '\n';
            return false;
        }
    }
    return true;
}

bool movePath(const std::string &src, const std::string &dst) {
    std::error_code ec;
    fs::rename(src, dst, ec);
    if (ec) {
        if (!copyPath(src, dst))
            return false;
        removePath(src);
    }
    return true;
}

void searchRecursive(const std::string &startPath, const std::string &pattern) {
    try {
        int count = 0;
        for (auto &p : fs::recursive_directory_iterator(startPath)) {
            if (p.path().filename().string().find(pattern) != std::string::npos) {
                std::cout << p.path().string() << '\n';
                ++count;
            }
        }
        std::cout << "Total matches: " << count << '\n';
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Search error: " << e.what() << '\n';
    }
}

void viewPermissions(const std::string &path) {
    std::error_code ec;
    auto st = fs::status(path, ec);
    if (ec) {
        std::cerr << "stat failed: " << ec.message() << '\n';
        return;
    }
    auto p = st.permissions();
    std::string s;
    s += (p & fs::perms::owner_read) != fs::perms::none ? 'r' : '-';
    s += (p & fs::perms::owner_write) != fs::perms::none ? 'w' : '-';
    s += (p & fs::perms::owner_exec) != fs::perms::none ? 'x' : '-';
    s += (p & fs::perms::group_read) != fs::perms::none ? 'r' : '-';
    s += (p & fs::perms::group_write) != fs::perms::none ? 'w' : '-';
    s += (p & fs::perms::group_exec) != fs::perms::none ? 'x' : '-';
    s += (p & fs::perms::others_read) != fs::perms::none ? 'r' : '-';
    s += (p & fs::perms::others_write) != fs::perms::none ? 'w' : '-';
    s += (p & fs::perms::others_exec) != fs::perms::none ? 'x' : '-';
    std::cout << "Permissions: " << s << '\n';
}

void changePermissions(const std::string &path, const std::string &octalMode) {
    long mode = strtol(octalMode.c_str(), nullptr, 8);
    if (chmod(path.c_str(), static_cast<mode_t>(mode)) != 0)
        perror("chmod failed");
}
