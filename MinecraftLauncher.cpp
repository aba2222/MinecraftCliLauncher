#include "MinecraftLauncher.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <filesystem>
#include <fstream>

#ifdef _WIN32
#define PATH_SEP "\\"
#else
#define PATH_SEP "/"
#endif

bool MinecraftLauncher::launch(const std::string& version, const std::string& username, int memoryMb) {
    std::string baseDir = getMinecraftDirectory();
    std::string versionDir = baseDir + PATH_SEP + "versions" + PATH_SEP + version;
    std::string jarPath = versionDir + PATH_SEP + version + ".jar";
    std::string javaPath = findJavaExecutable();
    if (javaPath.empty()) {
        std::cerr << "NoNoNo" << std::endl;
        return false;
    }

    std::string classpath = jarPath; // 简化版，不处理 libraries
    std::string mainClass = "net.minecraft.client.main.Main";

    // Minecraft libraries 目录
    std::string librariesDir = "D:\\Program Files\\pcl\\.minecraft\\libraries";

    // 用于存储所有找到的 .jar 文件路径
    std::vector<std::string> jarFiles;

    // 遍历 libraries 目录
    for (const auto& entry : std::filesystem::recursive_directory_iterator(librariesDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".jar") {
            // 将 .jar 文件路径添加到 jarFiles 向量中
            jarFiles.push_back(entry.path().string());
        }
    }

    // 将所有路径用分号连接
    std::string jarFilePaths = "";
    for (size_t i = 0; i < jarFiles.size(); ++i) {
        jarFilePaths += jarFiles[i];
        if (i != jarFiles.size() - 1) {
            jarFilePaths += ";"; // 每个路径之间用分号分隔
        }
    }

    std::string command = "\"" + javaPath + "\"" +
        " -Xmx" + std::to_string(memoryMb) + "M" +
        " -XX:+UseG1GC" +
        " -Djava.library.path=\"" + versionDir + "\\" + version + "- natives" + "\"" +
        " -cp \"" + classpath + ";" + jarFilePaths + "\"" +
        " " + mainClass +
        " --username " + username +
        " --version " + version +
        " --gameDir \"" + baseDir + "\"" +
        " --assetsDir \"" + baseDir + PATH_SEP + "assets\"" +
		" --assetIndex 24" + //todo: 24 是硬编码的，应该从版本文件中读取
        " --accessToken 0" +                      // 离线登录使用任意值
        " --uuid 0" +                             // 离线固定UUID
        " --userType legacy" +
        " --versionType release";

    std::cout << "Launch command: " << command << std::endl;

#ifdef _WIN32
    // 保存命令到 .bat 文件
    std::string batFile = "launch_minecraft.bat";
    std::ofstream batStream(batFile);
    batStream << "echo off\n";
    batStream << command << "\n";
    batStream.close();

    // 使用管理员权限运行 .bat 文件
    std::string wrappedCommand = "\"cmd /C \"" + batFile + "\"\"";
    return std::system(wrappedCommand.c_str()) == 0;
#else
    // 保存命令到 .sh 文件
    std::string shFile = "launch_minecraft.sh";
    std::ofstream shStream(shFile);
    shStream << "#!/bin/bash\n";
    shStream << command << "\n";
    shStream.close();

    // 赋予执行权限
    std::string chmodCommand = "chmod +x " + shFile;
    std::system(chmodCommand.c_str());

    // 使用 sudo 运行 .sh 文件
    std::string sudoCommand = "sudo ./" + shFile;
    return std::system(sudoCommand.c_str()) == 0;
#endif
}