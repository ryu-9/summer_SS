#pragma once
#include "SceneOutGameBase.h"
#include "UIChipClass.h"

class SceneEnding : public SceneOutGameBase
{
public:
	SceneEnding(class Main* main);
	virtual ~SceneEnding();

	void Init() override;
	void Update() override;
	int SceneEnd() override;

	
private:
	void StoryInit();
	void CreditInit();
	void EndInit();
	void StoryUpdate();
	void CreditUpdate();
	void EndUpdate();

	int _TrgCnt;
	int _Time;
	int _SceneType;
	std::vector<int> _VoiceNum;
};

