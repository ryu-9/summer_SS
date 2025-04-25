#include "SceneMenu.h"
#include "BuildScene.h"
#include "ioJson.h"
#include "SaveDataClass.h"
#include "UICharaClass.h"
#include "UIExitComponent.h"
#include "UIMessageSpriteComponent.h"
#include "UIScaleComponent.h"

SceneMenu::SceneMenu(class Main* main)
	:SceneOutGameBase(main)
	, _Cursor(0)
	, _Message(nullptr)
{
//	new UICharaClass(this, 0);
	_IsUpdate = true;
	std::string path = "res/UI/menu/";
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 0), 0, (path + "back.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 0), 0, (path + "heading.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(1198, 974, 0), VGet(1, 1, 0), 0, (path + "operation.png")));
	_Buttons.emplace_back(new UIChipClass(this, VGet(494, 511, 0), VGet(1,1, 0),1, (path + "Solo.png")));
	auto st = VGet(1, 1, 1);
	auto e = VGet(1.16, 1.16, 1.16);
	new UIScaleComponent(_Buttons.back(), st, e, 0, 0, 0);
	_Buttons.emplace_back(new UIChipClass(this, VGet(1426, 511, 0), VGet(1, 1, 0),1, (path + "Duo.png")));
	new UIScaleComponent(_Buttons.back(), st, e, 0, 0, 0);
	_Buttons.emplace_back(new UIChipClass(this, VGet(335, 877.5, 0), VGet(1, 1, 0),1, (path + "keyconfig.png")));
	new UIScaleComponent(_Buttons.back(), st, e, 0, 0, 0);
	_Buttons.emplace_back(new UIChipClass(this, VGet(960, 877.5, 0), VGet(1, 1, 0),1, (path + "instructions.png")));
	new UIScaleComponent(_Buttons.back(), st, e, 0, 0, 0);
	_Buttons.emplace_back(new UIChipClass(this, VGet(1585, 877.5, 0), VGet(1, 1, 0),1, (path + "exit.png")));
	new UIScaleComponent(_Buttons.back(), st, e, 0, 0, 0);
//	iojson::BuildScene("menu",this, _UIs, _Buttons);
	
	auto s = sndManager.GetSound("メニューBGM");
	if (s->IsPlay() == FALSE) {
		s->Play();
		SyncSystem.SetBasisBGM("メニューBGM");
	}
	// 開発用
	/*
	const auto path = _T("res\\chara01\\");
	std::vector<std::vector<MOTION_FRAME>> m;
	_SaveData = new sdata::SaveDataClass();
	iojson::InputMotionFrameJson(path,m);
	*/
}

SceneMenu::~SceneMenu() {
	auto s = _Buttons.size();
	for (auto i = 0; i < s; i++) {
		_Buttons.pop_back();
	}
}

void SceneMenu::Update() {
	if (_Message != nullptr) {
		if (gPad._m[0]._trg & PAD_INPUT_1) {
			//delete _Message;
			//_Message = nullptr;
			 new UIExitComponent(_Message,1,0,50);
			_Message = nullptr;
		}
	}
	else {
		if (gPad._m[0]._trg & PAD_INPUT_LEFT) { _Cursor--; SyncSystem.PlaySyncSE("選択"); }
		if (gPad._m[0]._trg & PAD_INPUT_RIGHT) { _Cursor++; SyncSystem.PlaySyncSE("選択"); }
		if (gPad._m[0]._trg & PAD_INPUT_UP) { _Cursor -= 3; SyncSystem.PlaySyncSE("選択"); }
		if (gPad._m[0]._trg & PAD_INPUT_DOWN) { _Cursor += 2; SyncSystem.PlaySyncSE("選択"); }
		if (_Cursor < 0) { _Cursor = 0; }
		if (_Cursor >= _Buttons.size()) { _Cursor = _Buttons.size() - 1; }
		if (gPad._m[0]._trg & PAD_INPUT_1) {
			switch (_Cursor)
			{
				{
			case 0:

				GetCommonData()->_IsDuoMode = _Cursor;
				SetNextScene(SceneType::eCharaSelect);
				SetChangeFlag(TRUE);
				sndManager.GetSound("決定")->Play();
				break;
				}
			case 1:
				GetCommonData()->_IsDuoMode = _Cursor;
				SetNextScene(SceneType::eCharaSelect);
//				for (auto it : _Buttons) {
//					new EasingScaleComponent(it, 1, 0, 30);
//				}
				SetChangeFlag(TRUE);
				sndManager.GetSound("決定")->Play();
				break;
			case 2:
				SetNextScene(SceneType::eOption);
				SetChangeFlag(TRUE);
				sndManager.GetSound("決定")->Play();
				break;
			case 3:
				SetNextScene(SceneType::eInstruction);
				SetChangeFlag(TRUE);
				sndManager.GetSound("決定")->Play();
				break;
			case 4:
				sndManager.GetSound("戻る")->Play();
				_Main->End(true);

				break;
			default:
				_Message = new UIChipClass(this,VGet(1920/2,1080/2,0), VGet(1, 1, 0),1, "res/UI/menu");
				new UIMessageSpriteComponent(_Message);
				break;
			}
		}
		if (gPad._m[0]._trg & PAD_INPUT_2) {
			_Cursor = 4;
			sndManager.GetSound("戻る")->Play();
		}
		for (auto i = 0; i < _Buttons.size(); i++) {
			if (_Buttons[i]->GetState() != ActorClass::ePreparation) {
				if (_Cursor == i) {
					_Buttons[i]->SetState(ActorClass::eActive);
				}
				else {
					_Buttons[i]->SetState(ActorClass::ePaused);
				}
			}
		}
	}
	SceneBase::Update();
}

int SceneMenu::SceneEnd() {
	return 0;
}