#pragma once
#include "SceneOutGameBase.h"
#include "UIChipClass.h"

class SceneInstruction : public SceneOutGameBase
{
public:
	SceneInstruction(class Main* main);
	virtual ~SceneInstruction();

	void Init() override;
	void Update() override;
	int SceneEnd() override;


private:

	int _Cnt;
	int _SceneType;
};


