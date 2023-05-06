#pragma once

#include "UApplicationBase.hpp"

class UBlackTrackApplication : public UApplicationBase {
	struct GLFWwindow* mWindow;
	class UBlackTrackContext* mContext;

	virtual bool Execute(float deltaTime) override;

public:
	UBlackTrackApplication();
	virtual ~UBlackTrackApplication() {}

	virtual bool Setup() override;
	virtual bool Teardown() override;
};

void GLFWDropCallback(GLFWwindow* window, int count, const char* paths[]);
