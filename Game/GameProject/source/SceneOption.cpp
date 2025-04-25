#include "SceneOption.h"
#include "UIChipClass.h"
#include "UIMoveComponent.h"

SceneOption::SceneOption(Main* main)
	:SceneOutGameBase(main)
//	,_Message(nullptr)
{
	_IsUpdate = true;
	std::string path = "res/UI/option/";
	_Back.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 0), 0, "res/UI/menu/back.png"));
	_Back.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 0), 0, (path + "レーン.png")));
	new UIMoveComponent(_Back.back(), VGet(0, -300, 0), VGet(0, 0, 0), 30, 1,0);
	_UIs.emplace_back(new UIChipClass(this, VGet(0,50, 0), VGet(1, 1, 0), 0, (path + "コントローラ.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 50, 0), VGet(1, 1, 0), 0, (path + "1p.png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(60, 720, 0), VGet(1, 1, 0), 0, (path + "win00.png")));
	_UIs.back()->AddImage((path + "win01.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(35, 680, 0), VGet(1, 1, 0), 0, (path + "head00.png")));
	_UIs.back()->AddImage((path + "head01.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(60 + 450, 720, 0), VGet(1, 1, 0), 0, (path + "win10.png")));
	_UIs.back()->AddImage((path + "win11.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(35 + 450, 680, 0), VGet(1, 1, 0), 0, (path + "head10.png")));
	_UIs.back()->AddImage((path + "head11.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(60, 720+ 210, 0), VGet(1, 1, 0), 0, (path + "win20.png")));
	_UIs.back()->AddImage((path + "win21.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(35, 680 + 210, 0), VGet(1, 1, 0), 0, (path + "head20.png")));
	_UIs.back()->AddImage((path + "head21.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(60 + 450, 720 + 210, 0), VGet(1, 1, 0), 0, (path + "win30.png")));
	_UIs.back()->AddImage((path + "win31.png"));
	_UIs.emplace_back(new UIChipClass(this, VGet(35 + 450, 680 + 210, 0), VGet(1, 1, 0), 0, (path + "head30.png")));
	_UIs.back()->AddImage((path + "head31.png"));
	_HLpos.emplace_back(VGet(692, 263, 0));
	_HLpos.emplace_back(VGet(749, 315, 0));
	_HLpos.emplace_back(VGet(638, 315, 0));
	_HLpos.emplace_back(VGet(692, 373, 0));
	_HighLights.emplace_back(new UIChipClass(this, VGet(692, 373, 0), VGet(1, 1, 0), 0, (path + "select.png")));
	auto s = sndManager.GetSound("メニューBGM");
	if (s->IsPlay() == FALSE) {
		s->Play();
		SyncSystem.SetBasisBGM("メニューBGM");
	}
	_Cursor.emplace_back(0);
	_IsWait.emplace_back(FALSE);
	_IndexNum = { 3,1,2,0 };
}

SceneOption::~SceneOption() {
	auto s = _Back.size();
	for (auto i = 0; i < s; i++) {
		_Back.pop_back();
	}
	s = _HLpos.size();
	for (auto i = 0; i < s; i++) {
		_HLpos.pop_back();
	}
	s = _HighLights.size();
	for (auto i = 0; i < s; i++) {
		_HighLights.pop_back();
	}
	s = _Cursor.size();
	for (auto i = 0; i < s; i++) {
		_Cursor.pop_back();
	}
	s = _IsWait.size();
	for (auto i = 0; i < s; i++) {
		_IsWait.pop_back();
	}
}

void SceneOption::Update()
{

	if (gPad._m[1]._trg & PAD_INPUT_1&&_Is2P == FALSE) {
		std::string path = "res/UI/option/";
		_UIs.emplace_back(new UIChipClass(this, VGet(970, 50, 0), VGet(1, 1, 0), 0, (path + "コントローラ.png")));
		_UIs.emplace_back(new UIChipClass(this, VGet(970, 50, 0), VGet(1,1, 0), 0, (path + "2p.png")));
		_UIs.emplace_back(new UIChipClass(this, VGet(60+ 970, 720, 0), VGet(1, 1, 0), 0, (path + "win00.png")));
		_UIs.back()->AddImage((path + "win01.png"));
		_UIs.emplace_back(new UIChipClass(this, VGet(35+ 970, 680, 0), VGet(1, 1, 0), 0, (path + "head00.png")));
		_UIs.back()->AddImage((path + "head01.png"));
		_UIs.emplace_back(new UIChipClass(this, VGet(60 + 450+ 970, 720, 0), VGet(1, 1, 0), 0, (path + "win10.png")));
		_UIs.back()->AddImage((path + "win11.png"));
		_UIs.emplace_back(new UIChipClass(this, VGet(35 + 450+ 970, 680, 0), VGet(1, 1, 0), 0, (path + "head10.png")));
		_UIs.back()->AddImage((path + "head11.png"));
		_UIs.emplace_back(new UIChipClass(this, VGet(60+ 970, 720 + 210, 0), VGet(1, 1, 0), 0, (path + "win20.png")));
		_UIs.back()->AddImage((path + "win21.png"));
		_UIs.emplace_back(new UIChipClass(this, VGet(35+ 970, 680 + 210, 0), VGet(1, 1, 0), 0, (path + "head20.png")));
		_UIs.back()->AddImage((path + "head21.png"));
		_UIs.emplace_back(new UIChipClass(this, VGet(60 + 450+ 970, 720 + 210, 0), VGet(1, 1, 0), 0, (path + "win30.png")));
		_UIs.back()->AddImage((path + "win31.png"));
		_UIs.emplace_back(new UIChipClass(this, VGet(35 + 450+ 970, 680 + 210, 0), VGet(1, 1, 0), 0, (path + "head30.png")));
		_UIs.back()->AddImage((path + "head31.png"));
		_HLpos.emplace_back(VGet(692 + 970, 263, 0));
		_HLpos.emplace_back(VGet(749 + 970, 315, 0));
		_HLpos.emplace_back(VGet(638 + 970, 315, 0));
		_HLpos.emplace_back(VGet(692 + 970, 373, 0));
		_HighLights.emplace_back(new UIChipClass(this, _HLpos[4], VGet(1, 1, 0), 0, (path + "select.png")));
		_Cursor.emplace_back(0);
		_IsWait.emplace_back(FALSE);
		_Is2P = true;
		return;
	}
	for (auto i = 0; i < _Cursor.size(); i++) {
		if (_IsReady) {
			if (gPad._m[i]._trg & PAD_INPUT_1) {
				_IsWait[i] = TRUE;
			}
			if (gPad._m[i]._trg & PAD_INPUT_2) {
				_IsReady = FALSE;
			}
		}
		else {

			if (_IsWait[i] == FALSE) {
				if (gPad._m[i]._trg & PAD_INPUT_LEFT) { _Cursor[i]--; SyncSystem.PlaySyncSE("選択"); }
				if (gPad._m[i]._trg & PAD_INPUT_RIGHT) { _Cursor[i]++; SyncSystem.PlaySyncSE("選択"); }
				if (gPad._m[i]._trg & PAD_INPUT_UP) { _Cursor[i] -= 2; SyncSystem.PlaySyncSE("選択"); }
				if (gPad._m[i]._trg & PAD_INPUT_DOWN) { _Cursor[i] += 2; SyncSystem.PlaySyncSE("選択"); }
				if (_Cursor[i] < 0) { _Cursor[i] = 0; }
				if (_Cursor[i] > 3) { _Cursor[i] = 3; }
				for (auto j = 0; j < 4; j++) {
					if (j == _Cursor[i]) {
						_UIs[(2 + j*2) + 10 * i ]->ChangeImage(1);
						_UIs[(2 + j* 2)+ 10 * i +1]->ChangeImage(1);
					}
					else {
						_UIs[(2 + j * 2) + 10 * i]->ChangeImage(0);
						_UIs[(2 + j * 2) + 10 * i + 1]->ChangeImage(0);
					}
				}

				if (gPad._m[i]._trg & GetSDKey(i,0)) {
					_IsWait[i] = TRUE;
					sndManager.GetSound("決定")->Play();
				}
				if (gPad._m[i]._trg & GetSDKey(i, 1)&&_IsWait.back() == false&& _IsWait.front() == false) {
					sndManager.GetSound("戻る")->Play();
					SetNextScene(SceneType::eMenu);
					SetChangeFlag(TRUE);
				}
				_HighLights[i]->SetPosition(_HLpos[(4*i)+_Cursor[i]]);
			}
			else {
				for (auto j = 0; j < 4; j++) {
					if (gPad._m[i]._trg & GetSDKey(i, j)) {
						auto key = GetSDKey(i, _IndexNum[_Cursor[i]]);
						SetSDKey(i, _IndexNum[_Cursor[i]], GetSDKey(i, j));
						SetSDKey(i, j, key);
						std::swap(_HLpos[j], _HLpos[_Cursor[i]]);
						_IsWait[i] = false;
						break;
					}
				}
			}

		}
	}

	SceneBase::Update();
	for (auto iter : _IsWait) {
		if (iter == FALSE) {
			return;
		}
	}
	if (_IsReady) {
		SetNextScene(SceneType::eMenu);
		SetChangeFlag(TRUE);
	}

}

int SceneOption::SceneEnd()
{
	return 0;
}
