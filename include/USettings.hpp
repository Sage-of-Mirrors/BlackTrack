#pragma once

#include <vector>
#include <string>
#include <filesystem>

#ifdef __linux__
const std::filesystem::path SETTINGS_FILENAME = std::filesystem::path("~/.local/share") / "BlackTrack" / "settings.conf";
#endif

#ifdef _WIN32
const std::filesystem::path SETTINGS_FILENAME = std::filesystem::path(std::getenv("APPDATA")) / "BlackTrack" / "settings.conf";
#endif

class USettings {
    std::vector<std::filesystem::path> mPreviousFiles;
    std::filesystem::path mLastOpenedDirectory;

public:
    USettings();
    ~USettings();

    void AddOpenedFile(std::filesystem::path file);
    const std::vector<std::filesystem::path>& GetPreviousFiles() const;

    void SetLastOpenedDirectory(std::filesystem::path dir);
    const std::filesystem::path& GetLastOpenedDirectory() const;

    void LoadSettings();
    void SaveSettings();
};
