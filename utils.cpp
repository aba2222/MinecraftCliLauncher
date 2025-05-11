#include "utils.h"
#include <cstdlib>
#include <vector>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

std::string getMinecraftDirectory() {
#ifdef _WIN32
    //char* appdata = std::getenv("APPDATA");
    //return std::string(appdata) + "\\.minecraft";
    return "D:\\Program Files\\pcl\\.minecraft";
#elif __APPLE__
    return std::string(getenv("HOME")) + "/Library/Application Support/minecraft";
#else
    return std::string(getenv("HOME")) + "/.minecraft";
#endif
}

std::string findJavaExecutable() {
    // 1. 尝试环境变量里的 java
    if (std::system("java -version >nul 2>&1") == 0) {
        return "java";
    }

#ifdef _WIN32
    // 2. 检查常见的 Windows Java 安装路径
    std::vector<std::string> candidates = {
        "C:\\Program Files\\Java\\jre1.8.0_281\\bin\\java.exe",
        "C:\\Program Files (x86)\\Java\\jre1.8.0_281\\bin\\java.exe",
        "D:\\Program Files\\pcl\\jdk-21.0.1.12-hotspot\\bin\\java.exe"
    };
#else
    // macOS / Linux
    std::vector<std::string> candidates = {
        "/usr/bin/java",
        "/usr/local/bin/java",
        "/usr/lib/jvm/java-17-openjdk-amd64/bin/java"
    };
#endif

    for (const auto& path : candidates) {
        if (fs::exists(path)) {
            return path;
        }
    }

    std::cerr << "Could not find java." << std::endl;
    return "";
}
