#pragma once
#include "SceneBase.h"
#include "gamepad.h"
#include "winmain.h"
#include "SoundItemSyncSystem.h"

extern SoundManager sndManager;
extern SoundItemSyncSystem SyncSystem;
extern GamePad gPad;
extern VECTOR DrawCenter;	//ï`âÊíÜêS

#define CHARA_MAX		(5)

enum class SceneType {
	NON,
	eTitle,
	eMenu,
	eOption,
	eInstruction,
	eCharaSelect,
	eGameMain,
	eDialogue,
	eEnding,
	SceneMax
};


class Main
{
public:
	Main();
	virtual ~Main();
	void Init();
	void RunLoop();
	void End(bool flag) { _toEnd = flag; }
	sdata::SaveDataClass* GetSaveData() { return _SaveData; }
private:
	void ChangeScene(SceneType scene);
	SceneType _NowScene;
	sdata::SaveDataClass* _SaveData;
	SceneBase* _gScene;
	SceneBase* _oldScene;
	bool _toEnd;
};

