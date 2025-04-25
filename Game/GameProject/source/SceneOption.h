#pragma once
#include "SceneBase.h"
#include "SceneOutGameBase.h"
#include "Main.h"
#include "UIChipClass.h"

class ButtonClass;
class MessageBoxClass;

class SceneOption : public SceneOutGameBase
{
public:
	SceneOption(class Main* main);
	virtual ~SceneOption();

	//	void Init() override;
	void Update() override;
	//	void Draw() override;
	int SceneEnd() override;

	int GetSDKey(int plnum, int index) { return GetMain()->GetSaveData()->_KeyData[plnum][index]; }

private:
	std::vector<UIChipClass*> _Back;
	std::vector<UIChipClass*> _HighLights;
	std::vector<VECTOR> _HLpos;
	void SetSDKey(int plnum, int index, int key) { GetMain()->GetSaveData()->_KeyData[plnum][index] = key; }
	bool _Is2P;
	std::vector<bool> _IsWait;
	bool _IsReady;
	std::vector<int> _IndexNum;
};

