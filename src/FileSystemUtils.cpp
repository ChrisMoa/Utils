//
// Created by chris-tab on 11.05.21.
//

#include "FileSystemUtils.h"
#include <StringUtils.hpp>
#include <filesystem>
#include <fstream>

using namespace std;
using namespace filesystem;
namespace fs = std::filesystem;

namespace Util {
#ifdef UNIX

string getExePath(void) {
    // create test dir in exe folder
    string dir = "pt";
    fs::create_directory(dir);
    path p(dir);
    p = fs::canonical(p);
    if (exists(p)) {
        fs::remove(dir);
        string from = p.string();
        std::string::iterator iFrom = from.end();
        while (*iFrom != '/') {
            --iFrom;
        }
        from = from.substr(0, iFrom - from.begin());
        return from;
    } else {
        return "";
    }
}

vector< string > getExePathStrings(void) {
    string exe = getExePath();
    auto rets = String::ExtendedString::extractList(exe, "/");
    if (exe.size()) {
        rets[0] = "/";
    }
    return rets;
}

vector< string > getSubDirectoriesAbs(string path) {
    vector< string > ret;
    fs::path p(path);

    if (exists(p) && is_regular_file(p)) {
        // do anything
    }
    if (exists(p) && is_directory(p)) {
        for (const auto& entry : fs::directory_iterator(p)) {
            if (is_directory(entry)) {
                ret.push_back(entry.path());
            } else {
                // do anything
            }
        }
    }
    return ret;
}

vector< string > getSubDirectoriesRel(string path) {
    vector< string > ret = getSubDirectoriesAbs(path);
    for (auto& r : ret) {
        int i = r.size();
        for (; i >= 0 && r[i] != '/'; i--) {
            // Do nothing
        }
        r = r.substr(i + 1, r.size() - i - 1);
    }
    return ret;
}

std::vector< string > getSubFilesAbs(string path) {
    vector< string > ret;
    fs::path p(path);

    if (exists(p) && is_regular_file(p)) {
        // do anything
    }
    if (exists(p) && is_directory(p)) {
        for (const auto& entry : fs::directory_iterator(p)) {
            if (is_regular_file(entry)) {
                ret.push_back(entry.path());
            } else {
                // do anything
            }
        }
    }
    return ret;
}

std::vector< string > getSubFilesRel(string path) {
    vector< string > ret = getSubFilesAbs(path);
    for (auto& r : ret) {
        int i = r.size();
        for (; i >= 0 && r[i] != '/'; i--) {
            // Do nothing
        }
        r = r.substr(i + 1, r.size() - i - 1);
    }
    return ret;
}

void createFolderInDirectory(std::string foldername, std::string relPath) {
    if (relPath.size()) {
        // path += path + "/" + relPath;
        fs::create_directories(relPath);
        foldername.insert(0, relPath + "/");
    }
    fs::create_directory(foldername);
    /* other examples:
        fs::permissions("sandbox/1/2/b", fs::perms::others_all, fs::perm_options::remove);
        std::system("ls -l sandbox/1/2");
        std::system("tree sandbox");
        fs::remove_all("sandbox");
    */
}

void createFileInDirectory(std::string filename, std::string relPath) {
    if (relPath.size()) {
        fs::create_directories(relPath);
        filename.insert(0, "/");
    }
    ofstream* f = new ofstream();
    f->open(relPath + filename, ios::trunc);
    f->close();
}

std::string getFilenameOfName(std::string name) {
    int i = name.size();
    for (; i >= 0 && name[i] != '/'; i--) {
        // Do nothing
    }
    return name.substr(i + 1, name.size() - i - 1);
}

string getDirOfName(string name) {
    int i = name.size();
    for (; i >= 0 && name[i] != '/'; i--) {
        // Do nothing
    }
    return name.substr(0, i);
}

bool fileExists(string filename) {
    filesystem::path p(filename);
    if (exists(p) && is_regular_file(p)) {
        return true;
    } else {
        return false;
    }
}

void removeFile(std::string filename) {
    if (!fileExists(filename)) {
        return;
    }
    filesystem::path p(filename);
    fs::remove(p);
}

void renameFile(std::string originFilename, std::string newFilename) {
    if (!fileExists(originFilename)) {
        return;
    }
    filesystem::path fileFrom(originFilename);
    filesystem::path fileTo(newFilename);
    fs::rename(fileFrom, fileTo);
}

void copyFile(std::string originFilename, std::string copyFilename) {
    if (!fileExists(originFilename)) {
        return;
    } else if (fileExists(copyFilename)) {
        removeFile(copyFilename);
    }
    filesystem::path fileFrom(originFilename);
    filesystem::path fileTo(copyFilename);
    fs::copy_file(fileFrom, fileTo);
}

#endif
}  // namespace Util
