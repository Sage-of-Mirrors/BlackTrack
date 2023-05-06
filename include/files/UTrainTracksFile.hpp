#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <filesystem>

/* == Forward declarations == */

namespace pugi {
    class xml_node;
}


/* Represents the configuration for a train track. */
class UTrainTrackConfig {
    std::string mFileName;
    std::string mConfigName;
    bool bStopsAtStations;
    uint32_t mBrakingDistance;

public:
    UTrainTrackConfig();
    UTrainTrackConfig(std::string fileName, std::string configName, bool stopsAtStations, uint32_t brakingDistance);
    UTrainTrackConfig(const pugi::xml_node& node);

    virtual ~UTrainTrackConfig();

    /* Serializes this config's data into the given XML node. */
    void SaveConfig(pugi::xml_node& node) const;

    void RenderBezierCurve();
    void RenderRoutePoints();
};


/* Contains all of the train track configs the game will load. */
class UTrainTracksFile {
    std::vector<UTrainTrackConfig> mConfigs;

public:
    UTrainTracksFile();
    virtual ~UTrainTracksFile();

    /* Loads the track configs from the XML file at the given path. */
    bool LoadConfigs(std::filesystem::path filePath);
    /* Saves the currently loaded track configs to the XML file at the given path. */
    bool SaveConfigs(std::filesystem::path filePath) const;
};
