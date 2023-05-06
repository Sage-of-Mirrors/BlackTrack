#include "UBlackTrackContext.hpp"
#include "files/UTrainTracksFile.hpp"

#include <glad/gl.h>
#include <imgui.h>
#include <imgui_internal.h>
//#include <bstream.h>

UBlackTrackContext::UBlackTrackContext() {
	mSettings = std::make_shared<USettings>();

	mTrackConfigFile = new UTrainTracksFile();
}

UBlackTrackContext::~UBlackTrackContext() {
	delete mTrackConfigFile;
}

bool UBlackTrackContext::Update(float deltaTime) {
	mCamera.Update(deltaTime);

	return true;
}

void UBlackTrackContext::Render(float deltaTime) {
	const glm::mat4 viewMtx = mCamera.GetViewMatrix();
	const glm::mat4 projMtx = mCamera.GetProjectionMatrix();

	RenderMenuBar();
}

void UBlackTrackContext::SetUpDocking() {
	const ImGuiViewport* mainViewport = ImGui::GetMainViewport();

	ImGuiDockNodeFlags dockFlags = ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_NoDockingInCentralNode;
	mMainDockSpaceID = ImGui::DockSpaceOverViewport(mainViewport, dockFlags);
	
	if (!bIsDockingSetUp) {
		ImGui::DockBuilderRemoveNode(mMainDockSpaceID); // clear any previous layout
		ImGui::DockBuilderAddNode(mMainDockSpaceID, dockFlags | ImGuiDockNodeFlags_DockSpace);
		ImGui::DockBuilderSetNodeSize(mMainDockSpaceID, mainViewport->Size);

		mDockNodeTopID = ImGui::DockBuilderSplitNode(mMainDockSpaceID, ImGuiDir_Up, 0.5f, nullptr, &mMainDockSpaceID);
		mDockNodeRightID = ImGui::DockBuilderSplitNode(mMainDockSpaceID, ImGuiDir_Right, 0.5f, nullptr, &mMainDockSpaceID);
		mDockNodeDownID = ImGui::DockBuilderSplitNode(mMainDockSpaceID, ImGuiDir_Down, 0.5f, nullptr, &mMainDockSpaceID);
		mDockNodeLeftID = ImGui::DockBuilderSplitNode(mMainDockSpaceID, ImGuiDir_Left, 0.5f, nullptr, &mMainDockSpaceID);

		ImGui::DockBuilderDockWindow("mainWindow", mDockNodeLeftID);

		ImGui::DockBuilderFinish(mMainDockSpaceID);

		bIsDockingSetUp = true;
	}
}

void UBlackTrackContext::RenderMenuBar() {
	bool bIsFileBrowserOpen = false, bIsSaveBrowserOpen = false;

	/* Render menu bar */
	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("Open...")) {
			bIsFileBrowserOpen = true;
		}
		if (ImGui::MenuItem("Save...")) {
			bIsSaveBrowserOpen = true;
		}

		ImGui::Separator();
		ImGui::MenuItem("Close");

		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Edit")) {
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("About")) {
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();

	/* Handle file browser operations */
	if (bIsFileBrowserOpen) {
		ImGui::OpenPopup("Open File");
	}
	if (bIsSaveBrowserOpen) {
		ImGui::OpenPopup("Save File");
	}

	if (mFileBrowser.showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 500), ".xml",
		mSettings->GetLastOpenedDirectory().parent_path().u8string() + "//"))
	{
		mTrackConfigFile->LoadConfigs(mFileBrowser.selected_path);

		mSettings->AddOpenedFile(mFileBrowser.selected_path);
		mSettings->SetLastOpenedDirectory(mFileBrowser.selected_path);
	}
	if (mFileBrowser.showFileDialog("Save File", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(700, 500), ".xml"))
	{
		mTrackConfigFile->SaveConfigs(mFileBrowser.selected_path);
	}
}

void UBlackTrackContext::OnFileDropped(std::string path) {
	//LoadModelFromPath(path);
}
