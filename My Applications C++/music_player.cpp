#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <vector>
#include <chrono>
#include <filesystem>
#include <conio.h>
#include <thread>
#pragma comment(lib, "winmm.lib")

namespace fs = std::filesystem;

void PlaySound(const std::string& soundFile) {
    PlaySoundA(soundFile.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void Time() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(65));
        const auto now = std::chrono::system_clock::now();
        const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
        std::cout << "\nThe time: " << std::ctime(&t_c) << std::endl;
    }
}

int main() {
    fs::path itemsDir;
    bool validDirectory = false; // Flag to track if a valid directory is entered

    while (!validDirectory) {
        std::cout << "[format of sounds should be '.wav']" << std::endl;
        std::cout << "Enter path with sounds: ";
        std::cin >> itemsDir;

        if (fs::is_directory(itemsDir)) {
            validDirectory = true; // Set the flag to true if the entered path is a valid directory
        }
        else {
            std::cout << "Directory not found. Please enter a valid path." << std::endl;
        }
    }

    long seconds = 0;
    std::vector<std::string> soundFiles;

    for (const auto& entry : fs::directory_iterator(itemsDir)) {
        if (entry.path().extension() == ".wav") {
            soundFiles.push_back(entry.path().filename().string());
        }
    }

    if (soundFiles.empty()) {
        std::cout << "No sound files found in the specified directory." << std::endl;
        return 1;
    }

    std::cout << "Available sound files:" << std::endl;
    for (const auto& soundFile : soundFiles) {
        std::cout << "- " << soundFile << std::endl;
    }

    std::cout << "Press Enter to start playing sounds..." << std::endl;
    while (_getch() != 13);

    std::thread time(Time);

    for (const auto& soundFile : soundFiles) {
        std::cout << "\nNow playing: " << soundFile << std::endl;
        PlaySound((itemsDir / soundFile).string());

        std::cout << "\nPress Enter to play the next sound..." << std::endl;

        while (_getch() != 13); // 13 - Enter
    }

    time.join();
    std::cout << std::endl; // Print a newline after the timer thread is stopped.
    return 0;
}
