#include "USettings.hpp"

#include <fstream>
#include <iostream>

USettings::USettings() : mLastOpenedDirectory("") {
    LoadSettings();
}

USettings::~USettings() {
    SaveSettings();
}

void USettings::AddOpenedFile(std::filesystem::path file) {
    mPreviousFiles.push_back(file);
}

const std::vector<std::filesystem::path>& USettings::GetPreviousFiles() const {
    return mPreviousFiles;
}

const std::filesystem::path& USettings::GetLastOpenedDirectory() const {
    return mLastOpenedDirectory;
}

void USettings::SetLastOpenedDirectory(std::filesystem::path dir) {
    mLastOpenedDirectory = dir;
}

void USettings::LoadSettings() {
    std::ifstream settingsFile(SETTINGS_FILENAME);

    if (settingsFile.is_open()) {
        std::string buf;

        std::getline(settingsFile, buf);
        if (buf.empty()) {
            return;
        }

        char* pch = std::strtok(buf.data(), "=");
        if (std::strcmp(pch, "lastopendir") == 0) {
            pch = std::strtok(nullptr, "=");

            mLastOpenedDirectory = std::filesystem::path(pch);
        }
    }
}

void USettings::SaveSettings() {
    if (!std::filesystem::exists(SETTINGS_FILENAME)) {
        std::filesystem::create_directories(SETTINGS_FILENAME.parent_path());
    }

    std::ofstream settingsFile(SETTINGS_FILENAME);

    if (settingsFile.is_open()) {
        settingsFile << "lastopendir=" << mLastOpenedDirectory.generic_u8string() << std::endl;

        settingsFile.close();
    }
}
