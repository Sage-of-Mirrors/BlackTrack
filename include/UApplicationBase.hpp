#pragma once

class UApplicationBase {

	virtual bool Execute(float deltaTime) = 0;
public:
	UApplicationBase() {}
	virtual ~UApplicationBase() {}

	void Run();

	virtual bool Setup() = 0;
	virtual bool Teardown() = 0;
};
