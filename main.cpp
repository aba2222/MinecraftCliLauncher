#include <iostream>
#include "MinecraftLauncher.h"

int main() {
    std::string version = "1.21.5";
    std::string username;
    int memoryMb = 2048;

    std::cout << "Please type username:";
    std::getline(std::cin, username);

    std::cout << "Please type max ram:";
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty()) memoryMb = std::stoi(input);

    MinecraftLauncher launcher;
    if (!launcher.launch(version, username, memoryMb)) {
        std::cerr << "Launch failed." << std::endl;
        return 1;
    }

    return 0;
}
