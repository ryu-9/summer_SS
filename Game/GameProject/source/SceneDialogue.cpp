#include "SceneDialogue.h"

SceneDialogue::SceneDialogue(class Main* main) 
	:SceneOutGameBase(main)
{
	SetChangeFlag(0);
	if (GetCommonData()->_pDialogue == FALSE) {

		std::string path = "res/chara0";
		for (auto i = 0; i < 6; i++) {
			for (auto j = 0; j < 6; j++) {
				auto p = path + std::to_string(i) + "/voice/開始時" + std::to_string(i) + std::to_string(j) + ".wav";
				sndManager.AddSound(new SoundItemSE(p, "開始時" + std::to_string(i) + std::to_string(j)));
				p = path + std::to_string(i) + "/voice/勝利時" + std::to_string(i) + std::to_string(j) + ".wav";
				sndManager.AddSound(new SoundItemSE(p, "勝利時" + std::to_string(i) + std::to_string(j)));
			}
		}
		GetCommonData()->_pDialogue = TRUE;

		// 勝利時も追加

	}
	if (GetCommonData()->_WinnerPlayerNum == 0) {
		_Voice = sndManager.GetSound("開始時" + std::to_string(GetCommonData()->_PlayerSelectChara[0]) + std::to_string(GetCommonData()->_PlayerSelectChara[1]));
		_Voice->Play();
	}
	else {
		if (GetCommonData()->_WinnerPlayerNum == 1) {
			_Voice = sndManager.GetSound("勝利時" + std::to_string(GetCommonData()->_PlayerSelectChara[0]) + std::to_string(GetCommonData()->_PlayerSelectChara[1]));
			_Voice->Play();
		}
	}
//	new DialogueClass(this);
	if (GetCommonData()->_WinnerPlayerNum == 0) {
		_DrawType = false;
		BeforeInit();
	}
	else {
		_DrawType = true;
		AfterInit();
	}
}

SceneDialogue::~SceneDialogue()
{
	
}

void SceneDialogue::Update() {
	if (_DrawType == FALSE) {
		BeforeUpdate();
	}
	else {
		AfterUpdate();
	}
}

int SceneDialogue::SceneEnd()
{
	return 0;
}

void SceneDialogue::BeforeInit() {
	auto ch = GetCommonData()->_PlayerSelectChara;
	std::string path = "res/UI/dialogue/";
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 1), 0, (path + "back.png")));
	
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 1), 0, (path + std::to_string(ch[0])+ "_left.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(782, 0, 0), VGet(1, 1, 1), 0, (path + std::to_string(ch[1]) + "_right.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(18, 508, 0), VGet(1, 1, 1), 0, (path + "talk_L.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(904, 18, 0), VGet(1, 1, 1), 0, (path + "talk_R.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(594, 262, 0), VGet(1, 1, 1), 0, (path + "vs.png")));
	if (_CommonData->_IsPractice) {
		_UIs.emplace_back(new UIChipClass(this, VGet(448, 800, 0), VGet(1, 1, 1), 1, (path + "0/99.png")));
		_UIs.emplace_back(new UIChipClass(this, VAdd(VGet(904, 18, 0), VGet(216, 64, 0)), VGet(1, 1, 1), 0, (path + "1/99.png")));
	}
	else {
		std::string cha = std::to_string(ch[0]) + std::to_string(ch[1]);
		_UIs.emplace_back(new UIChipClass(this, VGet(448, 800, 0), VGet(1, 1, 1), 1, (path + "0/" + cha + ".png")));
		_UIs.emplace_back(new UIChipClass(this, VAdd(VGet(904, 18, 0), VGet(216, 64, 0)), VGet(1, 1, 1), 0, (path + "1/" + cha + ".png")));
	}
}

void SceneDialogue::BeforeUpdate() {

		if (CheckSoundMem(_Voice->GetSoundHandle()) == FALSE) {
			SetChangeFlag(1);
		}

	SetNextScene(SceneType::eGameMain);
}

void SceneDialogue::AfterInit() {
	auto ch = GetCommonData()->_PlayerSelectChara;
	std::string path = "res/UI/dialogue/win/";
	std::string num = std::to_string(GetCommonData()->_PlayerSelectChara[GetCommonData()->_WinnerPlayerNum - 1]);
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 1), 0, (path + "back.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(1920/2,1080/2, 0), VGet(1, 1, 1), 1, (path + "0" + num + ".png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 1), 0, (path + "winner.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(60, 650, 0), VGet(1, 1, 1), 0, (path + "wordbox.png")));
	if (_CommonData->_IsPractice) {
		_UIs.emplace_back(new UIChipClass(this, VAdd(VGet(60, 650, 0), VGet(157, 44, 0)), VGet(1, 1, 1), 0, (path + "0/99.png")));
	}else {
		auto n = std::to_string(GetCommonData()->_WinnerPlayerNum - 1);
		std::string cha = std::to_string(ch[0]) + std::to_string(ch[1]);
		_UIs.emplace_back(new UIChipClass(this, VAdd(VGet(60, 650, 0), VGet(157, 44, 0)), VGet(1, 1, 1), 0, (path + n + "/" + cha + ".png")));
	}
}

void SceneDialogue::AfterUpdate() {
	if (GetCommonData()->_WinnerPlayerNum == 1) {
		if (CheckSoundMem(_Voice->GetSoundHandle()) == FALSE) {
			SetChangeFlag(1);
		}
	}
	else {
		SetChangeFlag(1);
	}
	if (_ChangeFlag) {
		if (gPad._m[0]._trg & PAD_INPUT_1) {
			if (GetCommonData()->_WinningStreak == 4) {
				SetNextScene(SceneType::eEnding);
			}
			else {
				GetCommonData()->_WinnerPlayerNum = 0;
				GetCommonData()->_PlayerSelectChara[1] = GetCommonData()->_SoloOrder[GetCommonData()->_PlayerSelectChara[0]][GetCommonData()->_WinningStreak];
				SetNextScene(SceneType::eDialogue);
			}
		}
	}
}
