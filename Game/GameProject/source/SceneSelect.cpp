#include "SceneSelect.h"
#include "UICharaClass.h"
#include "UIScaleComponent.h"
#include "BuildScene.h"
#include "UICursorComponent.h"

SceneSelect::SceneSelect(Main* main)
	:SceneOutGameBase(main)
{
	if (GetCommonData()->_pSelect == FALSE) {
		std::string path = "res/chara0";
		for (auto i = 0; i < 5; i++) {
			auto p = path + std::to_string(i) + "/voice/2.wav";
			sndManager.AddSound(new SoundItemSE(p, "キャラセレ" + std::to_string(i)));
		}
		GetCommonData()->_pSelect = TRUE;
	}
	if (GetCommonData()->_IsDuoMode) {
		DuoInit();
			}
	else {
		SoloInit();
	}

}

SceneSelect::~SceneSelect() {
	auto s = _WinPos.size();
	for (auto i = 0; i < s; i++) {
		_WinPos.pop_back();
	}
	s = _IsSelect.size();
	for (auto i = 0; i < s; i++) {
		_IsSelect.pop_back();
	}
	s = _Cursor.size();
	for (auto i = 0; i < s; i++) {
		_Cursor.pop_back();
	}
	s = _uiCur.size();
	for (auto i = 0; i < s; i++) {
		_uiCur.pop_back();
	}
	s = _uiCur.size();
	for (auto i = 0; i < s; i++) {
		_uiCur.pop_back();
	}
	s = _Cur2.size();
	for (auto i = 0; i < s; i++) {
		_Cur2.pop_back();
	}
}



void SceneSelect::Update()
{
	if (GetCommonData()->_IsDuoMode) {
		DuoUpdate();
	}
	else {
		SoloUpdate();
	}
	SceneBase::Update();
}

int SceneSelect::SceneEnd()
{
	return 0;
}

void SceneSelect::SoloInit() {
	_Cursor.emplace_back(0);
	_Cur2.emplace_back(0);
	_IsSelect.emplace_back(false);
	std::string path = "res/UI/select/";
	_UIs.emplace_back(new UIChipClass(this, VGet(CENTER_W, CENTER_H, 0), VGet(1, 1, 1), 1, (path + "back.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(811,0, 0), VGet(1, 1, 1), 0, (path + "ilust_back_solo.png")));
	_Player.emplace_back(new UICharaClass(this, VGet(1010, -250, 0), VGet(0.43, 0.43, 0.43), 0, _Cursor[0], ""));
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 1), 0, (path + "heading.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 1), 0, (path + "backbtn.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(1230, 0, 0), VGet(1, 1, 1), 0, (path + "solo.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(1720, 12, 0), VGet(1, 1, 1), 0, (path + "1p.png")));
	_WinPos.emplace_back(VGet(206, 494, 0));
	_WinPos.emplace_back(VGet(441, 464, 0));
	_WinPos.emplace_back(VGet(671, 434, 0));
	_WinPos.emplace_back(VGet(406, 869, 0));
	_WinPos.emplace_back(VGet(636, 834, 0));
	_UIs.emplace_back(new UIChipClass(this, _WinPos[0], VGet(1, 1, 1), 1, (path + "window00.png")));
	_UIs.emplace_back(new UIChipClass(this, VAdd(_WinPos[0],VGet(5,5,0)), VGet(1, 1, 1), 1, (path + "chara00.png")));
	_UIs.emplace_back(new UIChipClass(this, _WinPos[1], VGet(1, 1, 1), 1, (path + "window01.png")));
	_UIs.emplace_back(new UIChipClass(this, VAdd(_WinPos[1], VGet(5, 5, 0)), VGet(1, 1, 1), 1, (path + "chara01.png")));
	_UIs.emplace_back(new UIChipClass(this, _WinPos[2], VGet(1,1, 1), 1, (path + "window02.png")));
	_UIs.emplace_back(new UIChipClass(this, VAdd(_WinPos[2], VGet(5, 5, 0)), VGet(1, 1, 1), 1, (path + "chara02.png")));
	_UIs.emplace_back(new UIChipClass(this, _WinPos[3], VGet(1, 1, 1), 1, (path + "window03.png")));
	_UIs.emplace_back(new UIChipClass(this, VAdd(_WinPos[3], VGet(5, 5, 0)), VGet(1, 1, 1), 1, (path + "chara03.png")));
	_UIs.emplace_back(new UIChipClass(this, _WinPos[4], VGet(1, 1, 1), 1, (path + "window04.png")));
	_UIs.emplace_back(new UIChipClass(this, VAdd(_WinPos[4], VGet(5,5, 0)), VGet(1, 1, 1), 1, (path + "chara04.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(870, 600, 0), VGet(1, 1, 1), 0, (path + "textwindow00.png")));
	_UIs.back()->AddImage((path + "textwindow01.png"));
	_UIs.back()->AddImage((path + "textwindow02.png"));
	_UIs.back()->AddImage((path + "textwindow03.png"));
	_UIs.back()->AddImage((path + "textwindow04.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(870, 600, 0), VGet(1, 1, 1), 0, (path + "soloE.png")));
	_UIs.back()->AddImage((path + "soloA.png"));
	_UIs.back()->AddImage((path + "soloK.png"));
	_UIs.back()->AddImage((path + "soloR.png"));
	_UIs.back()->AddImage((path + "soloF.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(750, 600, 0), VGet(0.85, 0.85, 0), 0, (path + "name00.png")));
	_UIs.back()->AddImage((path + "name01.png"));
	_UIs.back()->AddImage((path + "name02.png"));
	_UIs.back()->AddImage((path + "name03.png"));
	_UIs.back()->AddImage((path + "name04.png"));
	_uiCur.emplace_back(new UIChipClass(this, _WinPos[0], VGet(1, 1, 1), 1, (path + "1pselect.png")));
	new UIScaleComponent(_uiCur.back(),VGet(0.95,0.95,0.95), VGet(1.08,1.08,1.08), 0,0,0);
	_uiCur.emplace_back(new UIChipClass(this, VAdd(_WinPos[0], VGet(-30, -180, 0)), VGet(1, 1, 1), 1, (path + "1pcursor.png"),130));
}

void SceneSelect::DuoInit() {
	_Cursor.emplace_back(0);
	_Cursor.emplace_back(4);
	_Cur2.emplace_back(0);
	_Cur2.emplace_back(0);
	_IsSelect.emplace_back(false);
	_IsSelect.emplace_back(false);
	std::string path = "res/UI/select/";
	_UIs.emplace_back(new UIChipClass(this, VGet(CENTER_W, CENTER_H, 0), VGet(1, 1, 1), 1, (path + "back.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(CENTER_W, CENTER_H, 0), VGet(1, 1, 1), 1, (path + "ilust_back.png")));
	_Player.emplace_back(new UICharaClass(this, VGet(-120, -165, 0), VGet(0.4, 0.4, 0.4), 0, _Cursor[0], ""));
	_Player.emplace_back(new UICharaClass(this, VGet(1240, -165, 0), VGet(0.37, 0.37, 0.37), 0, _Cursor[1], ""));
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 1), 0, (path + "heading.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 1), 0, (path + "backbtn.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(1230, 0, 0), VGet(1, 1, 1), 0, (path + "duo.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(20, 260, 0), VGet(1, 1, 1), 0, (path + "1p.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(1720, 12, 0), VGet(1, 1, 1), 0, (path + "2p.png")));
	_WinPos.emplace_back(VGet(701, 459, 0));
	_WinPos.emplace_back(VGet(936, 429, 0));
	_WinPos.emplace_back(VGet(1166, 399, 0));
	_WinPos.emplace_back(VGet(901, 834, 0));
	_WinPos.emplace_back(VGet(1131, 799, 0));
	_UIs.emplace_back(new UIChipClass(this, _WinPos[0], VGet(1, 1, 1), 1, path + "window00.png"));
	_UIs.emplace_back(new UIChipClass(this, VAdd(_WinPos[0], VGet(5, 5, 0)), VGet(1, 1, 1), 1, (path + "chara00.png")));
	_UIs.emplace_back(new UIChipClass(this, _WinPos[1], VGet(1, 1, 1), 1, path + "window01.png"));
	_UIs.emplace_back(new UIChipClass(this, VAdd(_WinPos[1], VGet(5, 5, 0)), VGet(1, 1, 1), 1, (path + "chara01.png")));
	_UIs.emplace_back(new UIChipClass(this, _WinPos[2], VGet(1, 1, 1), 1, path + "window02.png"));
	_UIs.emplace_back(new UIChipClass(this, VAdd(_WinPos[2], VGet(5, 5, 0)), VGet(1, 1, 1), 1, (path + "chara02.png")));
	_UIs.emplace_back(new UIChipClass(this, _WinPos[3], VGet(1, 1, 1), 1, path + "window03.png"));
	_UIs.emplace_back(new UIChipClass(this, VAdd(_WinPos[3], VGet(5, 5, 0)), VGet(1, 1, 1), 1, (path + "chara03.png")));
	_UIs.emplace_back(new UIChipClass(this, _WinPos[4], VGet(1, 1, 1), 1, path + "window04.png"));
	_UIs.emplace_back(new UIChipClass(this, VAdd(_WinPos[4], VGet(5, 5, 0)), VGet(1, 1, 1), 1, (path + "chara04.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(14, 818, 0), VGet(1, 1, 1), 0, (path + "name00.png")));
	_UIs.back()->AddImage((path + "name01.png"));
	_UIs.back()->AddImage((path + "name02.png"));
	_UIs.back()->AddImage((path + "name03.png"));
	_UIs.back()->AddImage((path + "name04.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(1334, 797, 0), VGet(1, 1, 1), 0, (path + "name00.png")));
	_UIs.back()->AddImage((path + "name01.png"));
	_UIs.back()->AddImage((path + "name02.png"));
	_UIs.back()->AddImage((path + "name03.png"));
	_UIs.back()->AddImage((path + "name04.png"));
	_uiCur.emplace_back(new UIChipClass(this, _WinPos[0], VGet(1, 1, 1), 1, (path + "1pselect.png")));
	new UIScaleComponent(_uiCur.back(), VGet(0.95, 0.95, 0.95), VGet(1.08, 1.08, 1.08), 0, 0, 0);
	_uiCur.emplace_back(new UIChipClass(this, _WinPos[4], VGet(1, 1, 1), 1, (path + "2pselect.png")));
	new UIScaleComponent(_uiCur.back(), VGet(0.95, 0.95, 0.95), VGet(1.08, 1.08, 1.08), 0, 0, 0);
	_uiCur.emplace_back(new UIChipClass(this, VAdd(_WinPos[0], VGet(-30, -180, 0)), VGet(1, 1, 1), 1, (path + "1pcursor.png"),130));
	_uiCur.emplace_back(new UIChipClass(this, VAdd(_WinPos[4], VGet(-30, -180, 0)), VGet(1, 1, 1), 1, (path + "2pcursor.png"),130));

}

void SceneSelect::SoloUpdate() {
	if (_IsReady) {
		if (_IsSelect[0] == FALSE) {
			if (gPad._m[0]._trg & PAD_INPUT_LEFT) { _Cur2[0]--; SyncSystem.PlaySyncSE("選択"); }
			if (gPad._m[0]._trg & PAD_INPUT_RIGHT) { _Cur2[0]++; SyncSystem.PlaySyncSE("選択"); }
			if (_Cur2[0] < 0) { _Cur2[0] = 0; }
			if (_Cur2[0] > 1) { _Cur2[0] = 1; }
			_uiCur[1]->SetPosition(VAdd((_UIs[_UIs.size() - (2 - _Cur2[0])])->GetPosition(), VGet(110, -20, 0)));
			if (gPad._m[0]._trg & PAD_INPUT_1) {
				if (_Cur2[0] == 0) {
					_IsSelect[0] = TRUE;
					new UICursorComponent(_uiCur[1], VGet(0, 0, 0), VGet(0, 0, 0), 60, 0, 0);
					_uiCur[1]->SetType(3);
				}
				else {
					_IsReady = FALSE;
					_Player[0]->SetFaceType(0);
					for (auto i = 0; i < 3; i++) {
						delete _UIs.back();
						_UIs.pop_back();
					}
					_Cur2[0] = 0;
					_IsSelect[0] = FALSE;
				}
			}
			if (gPad._m[0]._trg & PAD_INPUT_2) {
				_Cur2[0] = 1;
			}
		}
		else {
			if (_IsSelect[0] == TRUE) {
				_IsSelect[0] = FALSE;
			}
		}
	}
	else {
		if (_IsSelect[0] == FALSE) {
			if (gPad._m[0]._trg & PAD_INPUT_LEFT) { _Cursor[0]--; SyncSystem.PlaySyncSE("選択"); }
			if (gPad._m[0]._trg & PAD_INPUT_RIGHT) { _Cursor[0]++; SyncSystem.PlaySyncSE("選択"); }
			if (gPad._m[0]._trg & PAD_INPUT_UP && _Cursor[0] > 2) { _Cursor[0] -= 3; SyncSystem.PlaySyncSE("選択"); }
			if (gPad._m[0]._trg & PAD_INPUT_DOWN && _Cursor[0] < 3) { _Cursor[0] += 3; SyncSystem.PlaySyncSE("選択"); }
			if (_Cursor[0] < 0) { _Cursor[0] = 0; }
			if (_Cursor[0] > 4) { _Cursor[0] = 4; }
			_uiCur[0]->SetPosition(_WinPos[_Cursor[0]]);
			_UIs[16]->ChangeImage(_Cursor[0]);
			_UIs[17]->ChangeImage(_Cursor[0]);
			_UIs[18]->ChangeImage(_Cursor[0]);
			_uiCur[1]->SetPosition(VAdd(_WinPos[_Cursor[0]], VGet(-30, -180, 0)));
			
			if (gPad._m[0]._trg & PAD_INPUT_1) {
				_IsSelect[0] = TRUE;
				new UICursorComponent(_uiCur[1], VGet(0, 0, 0), VGet(0, 0, 0), 60, 0, 0);
				_uiCur[1]->SetType(3);
				sndManager.GetSound("決定")->Play();
				sndManager.GetSound("キャラセレ" + std::to_string(_Cursor[0]))->Play();
				_Player[0]->SetFaceType(1);
	}

}
		_Player[0]->SetCharaType(_Cursor[0]);
		if (gPad._m[0]._trg & PAD_INPUT_2) {
			if (_IsSelect[0] == TRUE) {
				_IsSelect[0] = FALSE;
				_Player[0]->SetFaceType(0);
			}
			else {
				sndManager.GetSound("戻る")->Play();
				SetNextScene(SceneType::eMenu);
				SetChangeFlag(TRUE);
			}
		}
	}

	if (_IsSelect[0] == TRUE && _IsSelect.back() && _IsReady == FALSE) {
		_IsReady = TRUE;
		std::string path = "res/UI/select/";
		_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 1), 0, (path + "AreYouReady.png"), 110));
		_UIs.emplace_back(new UIChipClass(this, VGet(850, 650, 0), VGet(1, 1, 1), 0, (path + "ok.png"), 110));
		_UIs.emplace_back(new UIChipClass(this, VGet(1100, 612, 0), VGet(1, 1, 1), 0, (path + "no.png"), 110));
		for (auto&& iter : _IsSelect) {
			iter = FALSE;
		}
	}

	for (auto iter : _IsSelect) {
		if (iter == FALSE) {
			return;
		}
}
	if (_IsReady) {
		GetCommonData()->_PlayerSelectChara[0] = _Cursor[0];
		GetCommonData()->_PlayerSelectChara[1] = GetCommonData()->_SoloOrder[_Cursor[0]][0];

		sndManager.GetSound("メニューBGM")->Stop();
		SetNextScene(SceneType::eDialogue);
		SetChangeFlag(TRUE);

	}
}

void SceneSelect::DuoUpdate() {
	for (auto i = 0; i < _Cursor.size(); i++) {
		if (_IsReady) {
			if (_Cur2[i] == _Cur2[1 - i]) {
				_uiCur[2]->SetPosition(VAdd((_UIs[_UIs.size() - (2 - _Cur2[i])])->GetPosition(), VGet(60, -15, 0)));
				_uiCur[3]->SetPosition(VAdd((_UIs[_UIs.size() - (2 - _Cur2[i])])->GetPosition(), VGet(160, -30, 0)));
			}
			else {
				_uiCur[2 + i]->SetPosition(VAdd((_UIs[_UIs.size() - (2 - _Cur2[i])])->GetPosition(), VGet(110, -20, 0)));
			}
			if (_IsSelect[i] == FALSE) {
				if (gPad._m[i]._trg & PAD_INPUT_LEFT) { _Cur2[i]--; SyncSystem.PlaySyncSE("選択"); }
				if (gPad._m[i]._trg & PAD_INPUT_RIGHT) { _Cur2[i]++; SyncSystem.PlaySyncSE("選択"); }
				if (_Cur2[i] < 0) { _Cur2[i] = 0; }
				if (_Cur2[i] > 1) { _Cur2[i] = 1; }
				if (gPad._m[i]._trg & PAD_INPUT_1) {
					if (_Cur2[i] == 0) {
						_IsSelect[i] = TRUE;
						new UICursorComponent(_uiCur[2 + i], VGet(0, 0, 0), VGet(0, 0, 0), 60, 0, 0);
						_uiCur[2 + i]->SetType(3);
						if(GetJoypadNum() < 2) {
							_IsSelect[1] = TRUE;
						}
					}
					else {
						_IsReady = FALSE;
						_Player[0]->SetFaceType(0);
						_Player[1]->SetFaceType(0);
						for (auto i = 0; i < 3; i++) {
							delete _UIs.back();
							_UIs.pop_back();
						}
						_Cur2[0] = 0;
						_Cur2[1] = 0;
						_IsSelect[0] = FALSE;
						_IsSelect[1] = FALSE;
					}
				}
				if (gPad._m[i]._trg & PAD_INPUT_2) {
					_Cur2[i] = 1;
				}
			}
			else {
				if (gPad._m[i]._trg & PAD_INPUT_2) {
					_IsSelect[i] = FALSE;
				}
			}
		}
		else {
			if (_IsSelect[i] == FALSE) {
				if (gPad._m[i]._trg & PAD_INPUT_LEFT) { _Cursor[i]--; SyncSystem.PlaySyncSE("選択"); }
				if (gPad._m[i]._trg & PAD_INPUT_RIGHT) { _Cursor[i]++; SyncSystem.PlaySyncSE("選択"); }
				if (gPad._m[i]._trg & PAD_INPUT_UP && _Cursor[i] > 2) { _Cursor[i] -= 3; SyncSystem.PlaySyncSE("選択"); }
				if (gPad._m[i]._trg & PAD_INPUT_DOWN && _Cursor[i] < 3) { _Cursor[i] += 3; SyncSystem.PlaySyncSE("選択"); }
				if (_Cursor[i] < 0) { _Cursor[i] = 0; }
				if (_Cursor[i] > 4) { _Cursor[i] = 4; }
				_uiCur[i]->SetPosition(_WinPos[_Cursor[i]]);
				_UIs[19-(2-i)]->ChangeImage(_Cursor[i]);
				if (_Cursor[i] == _Cursor[1 - i]) {
					_uiCur[2]->SetPosition(VAdd(_WinPos[_Cursor[i]], VGet(-80, -170, 0)));
					_uiCur[3]->SetPosition(VAdd(_WinPos[_Cursor[i]], VGet(10, -185, 0)));
				}
				else {
					_uiCur[2 + i]->SetPosition(VAdd(_WinPos[_Cursor[i]], VGet(-30, -180, 0)));
				}
				if (gPad._m[i]._trg & PAD_INPUT_1) {
					if (_IsSelect[1 - i] == TRUE && _Cursor[0] == _Cursor[1]) {}
					else {
						new UICursorComponent(_uiCur[2+i], VGet(0, 0, 0), VGet(0, 0, 0), 60, 0, 0);
						_uiCur[2+i]->SetType(3);
						sndManager.GetSound("決定")->Play();
						_IsSelect[i] = TRUE;
						sndManager.GetSound("キャラセレ" + std::to_string(_Cursor[i]))->Play();
						_Player[i]->SetFaceType(1);
					}
					if (GetJoypadNum() < 2) {
						_IsSelect[1] = TRUE;
						_Cursor[1] = 5;
					}
				}
			}
			_Player[i]->SetCharaType(_Cursor[i]);
			if (gPad._m[i]._trg & PAD_INPUT_2) {
				if (_IsSelect[i] == TRUE) {
					_IsSelect[i] = FALSE;
					_Player[i]->SetFaceType(0);
				}
				else {
					sndManager.GetSound("戻る")->Play();
					SetNextScene(SceneType::eMenu);
					SetChangeFlag(TRUE);
				}
			}
		}
	}
	if (_IsSelect[0] == TRUE && _IsSelect.back() && _IsReady == FALSE) {
		_IsReady = TRUE;
		std::string path = "res/UI/select/";
		_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 1), 0, (path + "AreYouReady.png"),110));
		_UIs.emplace_back(new UIChipClass(this, VGet(850, 650, 0), VGet(1, 1, 1), 0, (path + "ok.png"),110));
		_UIs.emplace_back(new UIChipClass(this, VGet(1100, 612, 0), VGet(1, 1, 1), 0, (path + "no.png"),110));
		for (auto&& iter : _IsSelect) {
			iter = FALSE;
		}
	}

	for (auto iter : _IsSelect) {
		if (iter == FALSE) {
			return;
		}
	}
	if (_IsReady) {
		GetCommonData()->_PlayerSelectChara[0] = _Cursor[0];
		GetCommonData()->_PlayerSelectChara[1] = _Cursor[1];
		if (GetJoypadNum() < 2) {
			GetCommonData()->_IsPractice = true;
		}
		sndManager.GetSound("メニューBGM")->Stop();
		SetNextScene(SceneType::eDialogue);
		SetChangeFlag(TRUE);
	}
}
