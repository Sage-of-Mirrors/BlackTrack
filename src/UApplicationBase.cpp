#include "UApplicationBase.hpp"
#include "UTime.hpp"

void UApplicationBase::Run() {
	Clock::time_point lastFrameTime, thisFrameTime;

	while (true) {
		lastFrameTime = thisFrameTime;
		thisFrameTime = UUtil::GetTime();

		if (!Execute(UUtil::GetDeltaTime(lastFrameTime, thisFrameTime)))
			break;
	}
}
