#include "SceneInstruction.h"
#include "UIScaleComponent.h"

SceneInstruction::SceneInstruction(Main* main)
	:SceneOutGameBase(main)
	, _SceneType(0)
	, _Cnt(0)
{
	std::string path = "res/UI/Instructions/";
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1,1, 0), 0, (path + "0.png")));
	_UIs.front()->AddImage((path + "1.png"));
	_UIs.front()->AddImage((path + "2.png"));
	_UIs.front()->AddImage((path + "3.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(900, 1060, 0), VGet(0.4, 0.4, 0), 1, (path + "ci.png")));
	_UIs.back()->AddImage((path + "cir.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(940, 1060, 0), VGet(0.4, 0.4, 0), 1, (path + "ci.png")));
	_UIs.back()->AddImage((path + "cir.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(980, 1060, 0), VGet(0.4, 0.4, 0), 1, (path + "ci.png")));
	_UIs.back()->AddImage((path + "cir.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(1020, 1060, 0), VGet(0.4, 0.4, 0), 1, (path + "ci.png")));
	_UIs.back()->AddImage((path + "cir.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(82, 540, 0), VGet(1, 1, 0), 1, (path + "Ltri.png")));
	new UIScaleComponent(_UIs.back(), VGet(0.95,0.95,0.95), VGet(1.05, 1.05, 1.05), 0, 0, 0);
	_UIs.emplace_back(new UIChipClass(this, VGet(1838, 540, 0), VGet(1, 1, 0), 1, (path + "Rtri.png")));
	new UIScaleComponent(_UIs.back(), VGet(0.95, 0.95, 0.95), VGet(1.05, 1.05, 1.05), 0, 0, 0);
}

SceneInstruction::~SceneInstruction()
{
}

void SceneInstruction::Init()
{
}

void SceneInstruction::Update()
{
	if (gPad._m[0]._trg & PAD_INPUT_LEFT) {
		_Cnt--; SyncSystem.PlaySyncSE("‘I‘ð");
	}
	if (gPad._m[0]._trg & PAD_INPUT_RIGHT) {
		_Cnt++; SyncSystem.PlaySyncSE("‘I‘ð");
	}
	if (_Cnt < 0) { _Cnt = 0; }
	if (_Cnt > 3) { _Cnt = 3; }
	_UIs.front()->ChangeImage(_Cnt);
	for (auto i = 1; i < 5; i++) {
		if (i == _Cnt + 1) {
			_UIs[i]->ChangeImage(1);
		}
		else {
			_UIs[i]->ChangeImage(0);
		}
	}
	if (gPad._m[0]._trg & PAD_INPUT_2) {
		SetNextScene(SceneType::eMenu);
		SetChangeFlag(TRUE);
		SyncSystem.PlaySyncSE("–ß‚é");
	}
	SceneBase::Update();
}

int SceneInstruction::SceneEnd()
{
	return 0;
}
