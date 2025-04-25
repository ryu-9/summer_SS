#include "SceneTitle.h"
#include "SynopsisClass.h"
#include "UIScaleComponent.h"

SceneTitle::SceneTitle(class Main* main) 
	:SceneOutGameBase(main)
{	
	auto n = rand() % 5;
	std::string path = "res/chara0" + std::to_string(n) + "/voice/1.wav";

	sndManager.AddSound(new SoundItemSE(path, "タイトルコール"));
	if (_CommonData->_pSynopsis == FALSE) {
		new SynopsisClass(this);
		_SceneFlag = 0;
		_CommonData->_pSynopsis = TRUE;
	}
	else {
		_SceneFlag = 1;
	}
	SetFade(255, 0, 60);
	_SwitchPoint = { 0,0,4000, };
}

SceneTitle::~SceneTitle() {
}

void SceneTitle::SetTitle() {
	DeleteUIs();
	_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 1), 0, "res/UI/title/title.png", 50));
	_UIs.emplace_back(new UIChipClass(this, VGet(1920/2, 1080/2, 0), VGet(1, 1, 1), 1, "res/UI/title/name.png"));
	new UIScaleComponent(_UIs.back(), VGet(1.08, 1.08, 0), VGet(0.95, 0.95, 0), 120, 0, 0);
	SetFontSize(24);
	ChangeFont("Impact");
}

void SceneTitle::Update()
{
	float tmp = 0;
	switch (_SceneFlag)
	{
	case 0:
		// あらすじ
		break;
	case 1:
		_UIs.emplace_back(new UIChipClass(this, VGet(0, 0, 0), VGet(1, 1, 1), 0, "res/UI/title/LOGO.png", 50));
		_SceneFlag = 2;
		_PointCnt = GetNowCount();
		break;
	case 2:
		if (GetNowCount() - _PointCnt< 1000) {
			tmp = (GetNowCount() - _PointCnt) / 1000.0f;
			
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255.0f * tmp);
		}
		else if (GetNowCount() - _PointCnt < 3000) {

		}
		else {
			tmp = 1-(GetNowCount() - (_PointCnt+3000)) / 1000.0f;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255.0f * tmp);
		}
		if (gPad._m[0]._trg & PAD_INPUT_1||_PointCnt + _SwitchPoint[_SceneFlag] <=GetNowCount()) {
			_PointCnt = GetNowCount();
			_SceneFlag = 3;

		}
		break;
	case 3:
		SetTitle();
		_SceneFlag = 4;
		sndManager.GetSound("タイトルコール")->Play();
		break;
	case 4:
		if (gPad._m[0]._trg) {
			SetNextScene(SceneType::eMenu);
			if (_Fade == nullptr) {
				SetFade(0, 255, 60);
			}
		}
		break;
	default:
		break;
	}
	SceneBase::Update();
	
}

