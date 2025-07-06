#include <iostream>
#include <string>
#include "MinecraftLauncher.h"

int main() {
    std::string version = "1.21.5";
    std::string username;
    int memoryMb = 2048;
    std::string input;


	std::cout << "Welcome to the Minecraft Launcher!" << std::endl;
	std::cout << "1. Launch Minecraft" << std::endl;
	std::cout << "2. Download Minecraft" << std::endl;
	std::cout << "3. Dowload Mods" << std::endl;
	std::cout << "4. Exit" << std::endl;
    
    switch(std::cin.get()) {
        case '1':
            std::cout << "Please type Minecraft version (default: " << version << "): ";
            std::cin >> version;

            std::cout << "Please type username:";
            std::cin >> username;

            std::cout << "Please type max ram:";
            std::cin >> input;
            if (!input.empty()) memoryMb = std::stoi(input);

            MinecraftLauncher launcher;
            if (!launcher.launch(version, username, memoryMb)) {
                std::cerr << "Launch failed." << std::endl;
                return 1;
            }
            break;
        case '2':
            std::cout << "Downloading Minecraft..." << std::endl;
            return 0;
        case '3':
            std::cout << "Downloading Mods..." << std::endl;
            return 0;
        case '4':
            std::cout << "Exiting..." << std::endl;
            return 0;
        default:
            std::cout << "Invalid option. Exiting..." << std::endl;
            return 1;
	}


    return 0;
}
