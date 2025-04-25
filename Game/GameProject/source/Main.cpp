#include <DxLib.h>
#include "Main.h"
#include "SceneBase.h"
#include "SceneMain.h"
#include "gamepad.h"
#include "SceneMenu.h"
#include "SceneTitle.h"
#include "SaveDataClass.h"
#include "SceneSelect.h"
#include "SceneDialogue.h"
#include "SceneEnding.h"
#include "SoundManager.h"
#include "SoundItem.h"
#include "SceneOption.h"
#include "SceneInstruction.h"

SoundManager sndManager;
SoundItemSyncSystem SyncSystem;
GamePad gPad;
VECTOR DrawCenter;


Main::Main()
	:_gScene(nullptr)
{

//	SetUseASyncLoadFlag(TRUE);
	_SaveData = new sdata::SaveDataClass();
	DrawCenter = VGet(SCREEN_W / 2, GROUND_HEIGHT, 0);
}

Main::~Main() {
	if (_gScene != nullptr) {
		delete _gScene;
	}
}

void Main::Init() {
	// ソロモード用順番
	std::vector<int> tmp = { 3,1,2,4 };
	CommonDataClass::GetInstance()->_SoloOrder.emplace_back(tmp);
	tmp = { 2,0,3,4 };
	CommonDataClass::GetInstance()->_SoloOrder.emplace_back(tmp);
	tmp = { 1,4,3,0 };
	CommonDataClass::GetInstance()->_SoloOrder.emplace_back(tmp);
	tmp = { 0,1,4,2 };
	CommonDataClass::GetInstance()->_SoloOrder.emplace_back(tmp);
	tmp = { 3,2,1,0 };
	CommonDataClass::GetInstance()->_SoloOrder.emplace_back(tmp);

	sndManager.AddSound(new SoundItemBGM("res/sound/BGM/メニュー&キャラセレ.mp3", "メニューBGM"));
	sndManager.GetSound("メニューBGM")->SetLoop(true);
	
	sndManager.AddSound(new SoundItemSE("res/sound/se/menu_enter.mp3", "決定"));
	sndManager.AddSound(new SoundItemSE("res/sound/se/menu_select.mp3", "選択"));
	sndManager.AddSound(new SoundItemSE("res/sound/se/menu_back.mp3", "戻る"));


	ChangeScene(SceneType::eTitle);
	
}

void Main::RunLoop() {
	while (ProcessMessage() == 0)
	{
		gPad.Input();
		SyncSystem.Update();
		if (_oldScene != nullptr) {
			_oldScene->ProcessInput();
			_oldScene->Update();
			_oldScene->Draw();
		}
		else {
			_gScene->ProcessInput();
			_gScene->Update();
			_gScene->Draw();
		}
		ScreenFlip();
		if (_gScene->GetNextScene() != SceneType::NON) {
			ChangeScene(_gScene->GetNextScene());
		}
		if (GetASyncLoadNum() == 0&&_oldScene != nullptr&&_oldScene->GetChangeFlag()==1) {
			delete _oldScene;
			_oldScene = nullptr;
			_gScene->Init();
		}
		if (_toEnd == true) {
			delete _SaveData;
			break;
		}
	}
}

void Main::ChangeScene(SceneType scene) {
	
	if (_NowScene == scene&&scene!=SceneType::eDialogue) { return; }
	_oldScene = _gScene;
	_NowScene = scene;

	switch (scene)
	{
	case SceneType::eTitle:
		_gScene = new SceneTitle(this);
		break;
	case SceneType::eMenu:
		_gScene = new SceneMenu(this);
		break;
	case SceneType::eCharaSelect:
		_gScene = new SceneSelect(this);
		break;
	case SceneType::eOption:
		_gScene = new SceneOption(this);
		break;
	case SceneType::eInstruction:
		_gScene = new SceneInstruction(this);
		break;
	case SceneType::eGameMain:
		_gScene = new SceneMain(this);
		break;
	case SceneType::eDialogue:
		_gScene = new SceneDialogue(this);
		break;
	case SceneType::eEnding:
		_gScene = new SceneEnding(this);
		break;
	default:
		break;
	}
}