#pragma once

#include "UCamera.hpp"
#include "USettings.hpp"
#include "ImGuiFileBrowser.h"

#include <vector>
#include <filesystem>
#include <memory>

class UTrainTracksFile;

class UBlackTrackContext {
	//std::vector<std::shared_ptr<UMaterializerUIPanel>> mPanels;

	USceneCamera mCamera;
	
	/* Docking */
	bool bIsDockingSetUp { false };
	uint32_t mMainDockSpaceID;
	uint32_t mDockNodeTopID;
	uint32_t mDockNodeRightID;
	uint32_t mDockNodeDownID;
	uint32_t mDockNodeLeftID;
	
	imgui_addons::ImGuiFileBrowser mFileBrowser;
	std::shared_ptr<USettings> mSettings;
	
	UTrainTracksFile* mTrackConfigFile;

	void SetUpDocking();
	void RenderMenuBar();

public:
	UBlackTrackContext();
	virtual ~UBlackTrackContext();

	bool Update(float deltaTime);
	void Render(float deltaTime);

	void OnFileDropped(std::string path);
};
