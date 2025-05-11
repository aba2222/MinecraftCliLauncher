#pragma once
#include <string>

class MinecraftLauncher {
public:
    bool launch(const std::string& version, const std::string& username, int memoryMb);
};
