#include "files/UTrainTracksFile.hpp"

#include <pugixml.hpp>
#include <iostream>

/* == Constants == */

/* Name of the XML attribute holding the name of a track's route data file - "filename". */
const char* FILENAME_ATTRIBUTE = "filename";
/* Name of the XML attribute holding the track's config name - "trainConfigName". */
const char* TRAINCONFIGNAME_ATTRIBUTE = "trainConfigName";
/* Name of the XML attribute holding the boolean determining if AI-controlled trains on this track stop at stations - "stopsAtStations". */
const char* STOPSATSTATIONS_ATTRIBUTE = "stopsAtStations";
/* Name of the XML attribute holding the distance from a station at which AI-controlled trains will begin to brake - "brakingDist". */
const char* BRAKINGDIST_ATTRIBUTE = "brakingDist";

/* Name of the track config file's root XML node - "train_tracks". */
const char* XML_ROOT_NODE_NAME = "train_tracks";
/* Name of a track config's XML node - "train_track". */
const char* XML_CONFIG_NODE_NAME = "train_track";

/* Path within common_0.rpf that the route data files are located at - "common:/data/levels/rdr3/". */
const char* RESOURCE_PATH = "common:/data/levels/rdr3/";


/* == Train Track Config == */

UTrainTrackConfig::UTrainTrackConfig() : UTrainTrackConfig("", "", false, 0) {

}

UTrainTrackConfig::UTrainTrackConfig(std::string fileName, std::string configName, bool stopsAtStations, uint32_t brakingDistance)
    : mFileName(fileName), mConfigName(configName), bStopsAtStations(stopsAtStations), mBrakingDistance(brakingDistance) {

}

UTrainTrackConfig::UTrainTrackConfig(const pugi::xml_node& node) {
    // Extract the raw filename from the resource path
    std::filesystem::path routeResPath = node.attribute(FILENAME_ATTRIBUTE).value();
    mFileName = routeResPath.filename().u8string();
    
    mConfigName = node.attribute(TRAINCONFIGNAME_ATTRIBUTE).value();
    bStopsAtStations = node.attribute(STOPSATSTATIONS_ATTRIBUTE).value()[0] == 't';
    mBrakingDistance = std::stoi(node.attribute(BRAKINGDIST_ATTRIBUTE).value());
}

UTrainTrackConfig::~UTrainTrackConfig() {

}

void UTrainTrackConfig::SaveConfig(pugi::xml_node& node) const {
    // Re-add the resource path to the filename
    node.append_attribute(FILENAME_ATTRIBUTE) = (RESOURCE_PATH + mFileName).c_str();

    node.append_attribute(TRAINCONFIGNAME_ATTRIBUTE) = mConfigName.c_str();
    node.append_attribute(STOPSATSTATIONS_ATTRIBUTE) = bStopsAtStations;
    node.append_attribute(BRAKINGDIST_ATTRIBUTE) = mBrakingDistance;
}

void UTrainTrackConfig::RenderBezierCurve() {

}

void UTrainTrackConfig::RenderRoutePoints() {

}


/* == Train Track File == */

UTrainTracksFile::UTrainTracksFile() {

}

UTrainTracksFile::~UTrainTracksFile() {

}

bool UTrainTracksFile::LoadConfigs(std::filesystem::path filePath) {
    // Load track config XML
    pugi::xml_document trackConfigFile;
    pugi::xml_parse_result loadResult = trackConfigFile.load_file(filePath.u8string().c_str());

    if (!loadResult) {
        std::cout << "Error loading track config file " << filePath << "!" << std::endl;
        return false;
    }

    // Clear existing track configs if neccessary
    if (mConfigs.size() != 0) {
        mConfigs.clear();
    }

    // Grab root node from document
    pugi::xml_node tracksNode = trackConfigFile.child(XML_ROOT_NODE_NAME);

    // Parse config nodes from root node
    for (pugi::xml_node track = tracksNode.child(XML_CONFIG_NODE_NAME); track; track = track.next_sibling(XML_CONFIG_NODE_NAME)) {
        mConfigs.push_back(UTrainTrackConfig(track));
    }

    return true;
}

bool UTrainTracksFile::SaveConfigs(std::filesystem::path filePath) const {
    pugi::xml_document trackConfigFile;

    // Add version and encoding to the XML header
    pugi::xml_node decl = trackConfigFile.prepend_child(pugi::node_declaration);
    decl.append_attribute("version") = "1.0";
    decl.append_attribute("encoding") = "UTF-8";

    // Add root node to document
    pugi::xml_node root = trackConfigFile.append_child(XML_ROOT_NODE_NAME);
    root.append_attribute("version") = "1";

    // Add config nodes to root node
    for (UTrainTrackConfig config : mConfigs) {
        pugi::xml_node configNode = root.append_child(XML_CONFIG_NODE_NAME);
        config.SaveConfig(configNode);
    }

    trackConfigFile.save_file(filePath.u8string().c_str(), PUGIXML_TEXT("\t"), pugi::format_indent_attributes, pugi::encoding_utf8);
    return true;
}
