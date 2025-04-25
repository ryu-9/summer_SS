#include "SceneEnding.h"
#include "CommonDataClass.h"

SceneEnding::SceneEnding(Main* main)
	:SceneOutGameBase(main)
	,_SceneType(0)
	,_TrgCnt(0)
{
	// ここで分岐
	if (_CommonData->_IsDuoMode == false && _CommonData->_WinnerPlayerNum ==1) {
		_SceneType = 0;

}
	else {
		_SceneType = 2;
	}
	Init();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);
	SetFade(255, 0, 60);

}

SceneEnding::~SceneEnding()
{
	SceneEnd();
}

void SceneEnding::Init()
{
	_TrgCnt = 0;
	DeleteUIs();
	switch (_SceneType)
	{
	case 0:
		StoryInit();
		break;
	case 1:
		CreditInit();
		break;
	case 2:
		EndInit();
		break;
	default:
		break;
	}
}

void SceneEnding::Update()
{
	switch (_SceneType)
	{case 0:
		StoryUpdate();
		break;
	case 1:
		CreditUpdate();
		break;
	case 2:
		EndUpdate();
		break;
	default:
		break;
	}
	SceneBase::Update();
}

int SceneEnding::SceneEnd()
{
	DeleteUIs();
	_CommonData->_IsDuoMode = false;
	_CommonData->_IsPractice = false;
	_CommonData->_PlayerSelectChara[0] = -1;
	_CommonData->_PlayerSelectChara[1] = -1;
	_CommonData->_WinnerPlayerNum = 0;
	_CommonData->_WinningStreak = 0;
	for (auto dt : _CommonData->_CopyData) {
		for (auto mot : dt) {
			DeleteGraph(mot.cg);
		}
	}

	auto size = _CommonData->_CopyData.size();
	for (int i = 0; i < size; i++) {
		std::vector<MOTION_FRAME> tmp;
		std::swap(tmp, _CommonData->_CopyData.back());
		_CommonData->_CopyData.pop_back();
	}
	
	return 0;
}

void SceneEnding::StoryInit() {
	_VoiceNum = { 2,2,4,4,3 };
	std::string path = "res/UI/Ending/";
	int n = GetCommonData()->_PlayerSelectChara[0];
	std::string num = std::to_string(n);
	sndManager.AddSound(new SoundItemSE("res/chara0" + num + "/voice/15.wav", "endvoice"));
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 1), 0, (path + "0" + num + ".png")));
	_UIs.emplace_back(new UIChipClass(this, VGet(-10, 700, 0), VGet(1, 1, 0), 0, (path + "枠縁.png")));
	path = path + "0" + num + "/";
	_UIs.emplace_back(new UIChipClass(this, VGet(100, 800, 0), VGet(1, 1, 0), 0, (path + "01.png")));
	switch (n)
	{
	case 0:
		_UIs.back()->AddImage((path  + "02.png"));
		_UIs.back()->AddImage((path+ "03.png"));
		break;
	case 1:
		_UIs.back()->AddImage((path + "02.png"));
		_UIs.back()->AddImage((path + "03.png"));
		break;
	case 2:
		_UIs.back()->AddImage((path  + "02.png"));
		_UIs.back()->AddImage((path  + "03.png"));
		_UIs.back()->AddImage((path + "04.png"));
		_UIs.back()->AddImage((path+ "05.png"));
		_UIs.back()->AddImage((path  + "06.png"));
		_UIs.back()->AddImage((path + "07.png"));
		break;
	case 3:
		_UIs.back()->AddImage((path + "02.png"));
		_UIs.back()->AddImage((path  + "03.png"));
		_UIs.back()->AddImage((path + "04.png"));
		_UIs.back()->AddImage((path + "05.png"));
		_UIs.back()->AddImage((path + "06.png"));
		break;
	case 4:
		_UIs.back()->AddImage((path + "02.png"));
		_UIs.back()->AddImage((path + "03.png"));
		_UIs.back()->AddImage((path + "04.png"));
		break;
	default:
		break;
	}
}

void SceneEnding::CreditInit() {
	std::string path = "res/UI/Ending/";
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 0), 0, (path + "Credit.png")));
	_Time = GetNowCount();
}

void SceneEnding::EndInit() {
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	std::string path = "res/UI/Ending/";
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 0), 0, (path + "thankyouforplaying.png")));
}

void SceneEnding::StoryUpdate() {
	if (GetCommonData()->_PlayerSelectChara[0] == 2) {
		auto tmp = GetSoundCurrentTime(sndManager.GetSound("endvoice")->GetSoundHandle());
		if (_TrgCnt == 4 && tmp >= 3600) {
			_TrgCnt++;
			_UIs[2]->ChangeImage(_TrgCnt);
		}
		if (_TrgCnt == 5 && tmp >= 4800) {
			_TrgCnt++;
			_UIs[2]->ChangeImage(_TrgCnt);
		}
	}
	if(gPad._m[0]._trg & PAD_INPUT_1) {
		_TrgCnt++;
		if (_TrgCnt == _VoiceNum[GetCommonData()->_PlayerSelectChara[0]]) {
			sndManager.GetSound("endvoice")->Play();
		}
		if (GetCommonData()->_PlayerSelectChara[0] == 2 && _TrgCnt == 5) {
			SetSoundCurrentTime(3600, sndManager.GetSound("endvoice")->GetSoundHandle());
		}
		if (GetCommonData()->_PlayerSelectChara[0] == 2 && _TrgCnt == 6) {
			SetSoundCurrentTime(4800, sndManager.GetSound("endvoice")->GetSoundHandle());
		}
		_UIs[2]->ChangeImage(_TrgCnt);
	}
	if (_UIs[2]->GetImageNum() == _UIs[2]->GetImageSize()) {
		_SceneType++;
		Init();
	}
	
}

void SceneEnding::CreditUpdate() {
	auto move = VGet(0, -5, 0);
	// スキップ等
	
	for (auto i = 0; i < 4; i++) {
		if (gPad._m[0]._trg & PAD_INPUT_1) {
			if (_TrgCnt == 0) {
				_TrgCnt++;
				std::string path = "res/UI/Ending/";
				_UIs.emplace_back(new UIChipClass(this, VGet(0, 1018, 0), VGet(0.75, 0.75, 0), 0, (path + "operation.png")));
				break;
			}
			else {
				_SceneType++;
				Init();
				return;
			}
		}
	}
	if (GetNowCount() - _Time <= 1000 ) {
		move = VGet(0, 0, 0);
	}
	if (_UIs.front()->GetPosition().y >= -23000 + 1080) {
		if (gPad._m[0]._key & PAD_INPUT_DOWN) {
			move = VGet(0, -20, 0);
		}
		if (gPad._m[0]._key & PAD_INPUT_UP) {
			move = VGet(0, 10, 0);
		}
	}
	if (_UIs.front()->GetPosition().y <= -24000 + 1080) {
		auto tmp = (_UIs.front()->GetPosition().y -(-24000.0f + 1080.0f)) / (250.0f);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (1 + tmp));
	}
	_UIs.front()->SetPosition(VAdd(_UIs.front()->GetPosition(), move));
	if (_UIs.front()->GetPosition().y > 0) {
		_UIs.front()->SetPosition(VGet(_UIs.front()->GetPosition().x,0, _UIs.front()->GetPosition().z));
	}
	if (_UIs.front()->GetPosition().y < -24250 + 1080) {
		_UIs.front()->SetPosition(VGet(0, -24250 + 1080, 0));
		_SceneType++;
		Init();
	}
}

void SceneEnding::EndUpdate() {
	if (gPad._m[0]._trg & PAD_INPUT_1) {
		SetNextScene(SceneType::eTitle);
		_ChangeFlag = true;
	}
}


