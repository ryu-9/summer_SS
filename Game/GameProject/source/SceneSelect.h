#pragma once
#include "SceneBase.h"
#include "SaveDataClass.h"
#include "UICharaClass.h"
#include "Main.h"
#include "SceneOutGameBase.h"

#define CENTER_W						(960)
#define CENTER_H						(540)
class SceneSelect : public SceneOutGameBase
{
public:
	SceneSelect(class Main* main);
	virtual ~SceneSelect();

	void Update() override;
	int SceneEnd() override;

private:
	void SoloInit();
	void DuoInit();
	void SoloUpdate();
	void DuoUpdate();

//	std::vector<UIChipClass*> _UIs;
	std::vector<UIChipClass*> _uiCur;
	std::vector<VECTOR> _WinPos;
	std::vector<UICharaClass*> _Player;
	std::vector<bool> _IsSelect;
	bool _IsReady;
	std::vector<int> _Cursor;
	std::vector<int> _Cur2;
};

