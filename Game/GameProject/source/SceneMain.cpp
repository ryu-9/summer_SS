#include "SceneMain.h"
#include "SoundManager.h"
#include "PlayerClass.h"
#include "SceneBase.h"
#include "RhythmControlClass.h"
#include "Stage.h"
#include "MainSpriteComponent.h"
#include "AIControlClass.h"




SceneMain::SceneMain(class Main* main)
	:SceneBase(main)
	, _FinishFlag(0)
	, _BattleCnt(100000)
	, _FPSCnt(GetNowCount())
	,_Color(0)
	,_AI(nullptr)
{
	SetFontSize(16);
	CreateMaskScreen();
	_HPRatio[0] = 0;
	_HPRatio[1] = 0;
	_SceneFlag = 1;
	_IsUpdate = true;

	if (_CommonData->_IsDuoMode == false) {
		_AI = new AIControlClass(this);
	}
	_Cam = new CameraClass(this);
	_FPSCon = new FPSControlClass(this, 180);
	_Player[0] = new PlayerClass(this,0,_CommonData->_PlayerSelectChara[0]);
	_Player[1] = new PlayerClass(this,1, _CommonData->_PlayerSelectChara[1]);
	_EFControl = new EffectControlClass(this);
	_Psy = new RhythmControlClass(this);
	if (_CommonData->_IsDuoMode == false) {
		std::swap(_Actors[1], _Actors[6]);
	}
	else {
		std::swap(_Actors[0], _Actors[5]);
	}
	
	_Tension = 100/2;
	_Stage = new StageBase(this, VGet(0, GROUND_HEIGHT-115, 0), VGet(4200, 125, 1), "res/stage/light_land.png", 1, 0);
	new StageBase(this, VGet(0, GROUND_HEIGHT + 825, 0), VGet(3600, 2000, 1), "res/stage/stage.png", 4, 90, 0, 180 / 4);
	new StageBase(this, VGet(0, -1080 / 4, 0), VGet(1920 * 4, 1080 * 4, 0), "res/stage/dark.png",1,110);
	new StageBack(this, VGet(0, 1080 / 4, 0), VGet(3840 * 2, 1080*2, 0), "res/stage/stage_back.png", 1.0f,50);
	new StageBack(this, VGet(3840*2, 1080/4, 0), VGet(3840 * 2, 1080 * 2, 0), "res/stage/stage_back.png", 1.0f, 50);
	new StageLight(this, VGet(-2000, GROUND_HEIGHT -3160 / 2, 0), VGet(1400 *  2 , 1500 * 2 , 0), "res/stage/STAGE_LIGHT.png", 7, 95);
	new StageLight(this, VGet(2000, GROUND_HEIGHT - 3160 / 2, 0), VGet(1400 * 2, 1500 * 2, 0), "res/stage/STAGE_LIGHT.png", 7, 95);
	new StageFire(this, VGet(2000, GROUND_HEIGHT - 100, 0), 0);
	new StageFire(this, VGet(2000, GROUND_HEIGHT - 100, 0), 90);
	new StageFire(this, VGet(2000, GROUND_HEIGHT - 100, 0), 180);
	new StageFire(this, VGet(2000, GROUND_HEIGHT - 100, 0), 270);
	ScreenMask = MakeScreen(1920, 1080,TRUE);
	SubMask = MakeScreen(1920, 1080,TRUE);

	_BackLight[0] = new BackLightClass(this, 0);
	_BackLight[1] = new BackLightClass(this, 1);
	_SEControl = new SoundManager();
	SetUseMaskScreenFlag(FALSE);		//お守り


	_EFControl->AddScreenEffect(VGet(1920/2,1080/2,0), 16);
	
	sndManager.AddSound(new SoundItemSE("res/sound/se/FIRE.mp3", "fire"));
	sndManager.AddSound(new SoundItemSE("res/sound/se/backlight.mp3", "backlight"));
	sndManager.AddSound(new SoundItemSE("res/sound/se/sessionHit.mp3", "session"));
	sndManager.AddSound(new SoundItemSE("res/sound/se/JustGuard.mp3", "justguard"));
	sndManager.AddSound(new SoundItemSE("res/sound/se/kick_guide.wav", "guide"));
	sndManager.AddSound(new SoundItemSE("res/sound/se/ラウンド開演.m4a", "start"));
	sndManager.AddSound(new SoundItemSE("res/sound/se/終焉.m4a", "end"));


}

SceneMain::~SceneMain() {
	delete _FPSCon;
	delete _Psy;
	delete _EFControl;
	delete _Player[0];
	delete _Player[1];
	delete _Stage;
	SyncSystem.SetLoopSE(false, "");
	InitMask();
}

void SceneMain::Init(){

	_Player[0]->Init();
	_Player[1]->Init();
	_Tension = 100/2;
	_FinishFlag = FALSE;
	//_EFControl->AddScreenEffect(VGet(1920 / 2, 1080 / 2, 0), 1);
	_SceneFlag = 1;
	_Cnt = 0;
	_Psy->Init();
	_FPSCon->Init(SyncSystem.GetBPM());
	_BattleCnt = 100000;
	_Cam->init();
	_EFControl->ResetMotEffect(0);
	_EFControl->ResetMotEffect(1);
	if (_AI != nullptr) {
		_AI->SetAI();
		_AI->Init();
	}
	sndManager.GetSound("backlight")->SetVolume(255);
	sndManager.GetSound("guide")->SetVolume(100);
	_EFControl->Init();
}




void SceneMain::Update() 
{
	if (_FPSCon->GetUpdateFlag() == TRUE) {
	}

	switch (_SceneFlag) {
	case 0:
		_Cnt = _FPSCon->GetSession();
		_Player[0]->SetSlowFlag(_Cnt);
		_Player[1]->SetSlowFlag(_Cnt);
		break;


	case 2:
		if (_Cnt == 0) { _Cnt = GetNowCount() + 1000; }
		_Player[0]->SetState(_Player[0]->ePaused);
		_Player[1]->SetState(_Player[1]->ePaused);
		if (GetNowCount() >_Cnt) {
			_SceneFlag = 3; 
			_Cnt = GetNowCount();
			_Player[0]->SetState(_Player[0]->eActive);
			_Player[1]->SetState(_Player[1]->eActive);
		}
		break;
	case 3:
		if (_FPSCon->GetUpdateFlag() == TRUE) { _Cnt++; }
		_Player[0]->SetSlowFlag(_Cnt % 10 + 1);
		_Player[1]->SetSlowFlag(_Cnt % 10 + 1);
		ChangeVolumeSoundMem((1 - (GetNowCount()-_Cnt)/ 4000 )  * 150, _Psy->GetBGMHandle());
		if (_Cnt % 5 != 0) {
		}
		if (_Cnt+4000 < GetNowCount()) { 
			if (_Player[0]->GetHitPoint() * _Player[1]->GetMaxHp() > _Player[1]->GetHitPoint() * _Player[0]->GetMaxHp()) {
				_EFControl->AddScreenEffect(VGet(1920 / 2 - 1000, 1080 / 2, 0), 11);
				//1P勝利
			}
			else if (_Player[0]->GetHitPoint() * _Player[1]->GetMaxHp() < _Player[1]->GetHitPoint() * _Player[0]->GetMaxHp()) {
				_EFControl->AddScreenEffect(VGet(1920 / 2 + 1000, 1080 / 2, 0), 12);
				//1P勝利
			}
			else {
				_EFControl->AddScreenEffect(VGet(1920 / 2, 1080 / 2, 0), 13);
				_EFControl->AddScreenEffect(VGet(1920 / 2 - 616 / 2 - 100, 1080 / 2, 0), 14);
				_EFControl->AddScreenEffect(VGet(1920 / 2 + 616 / 2 + 100, 1080 / 2, 0), 15);
				//引き分け
			}
			_SceneFlag = 1;
			_Cnt = 0;
			_Player[0]->SetState(_Player[0]->eActive);
			_Player[1]->SetState(_Player[1]->eActive);
			StopSoundMem(_Psy->GetBGMHandle());
		}
		break;

	case 4:

		if (_WinNum[0]>=40) {
			//Player1 Win!!
			if (_CommonData->_IsDuoMode == false && _CommonData->_WinnerPlayerNum == 0) {
				_CommonData->_WinningStreak++;
			}
			else if (_CommonData->_IsDuoMode == true) {
				_CommonData->_WinningStreak = 4;
			}
			_CommonData->_WinnerPlayerNum = 1;
			
			_NextScene = SceneType::eDialogue;
			SetChangeFlag(TRUE);
			return;
		}
		if (_WinNum[1] >= 40) {
			//Player2 Win!!
			_CommonData->_WinningStreak = 4;
			_CommonData->_WinnerPlayerNum = 2;
			_NextScene = SceneType::eDialogue;
			SetChangeFlag(TRUE);
			return;
		}
		if (_WinNum[0] + _WinNum[1] > 40) {
			//Draw!!
			_CommonData->_WinningStreak = 4;
			_CommonData->_WinnerPlayerNum = -1;
			_NextScene = SceneType::eEnding;
			SetChangeFlag(TRUE);
			return;
		}

		Init();
		_HPRatio[0] += _Player[0]->GetHitPoint() / _Player[0]->GetMaxHp();
		_HPRatio[1] += _Player[0]->GetHitPoint() / _Player[1]->GetMaxHp();
		break;

	case 5:
		if (_Cnt == 0) { _Cnt = GetNowCount() + 2000;  }
		if (GetNowCount()>_Cnt) {
			if (_Player[0]->GetHitPoint() * _Player[1]->GetMaxHp() > _Player[1]->GetHitPoint() * _Player[0]->GetMaxHp()) {
				_EFControl->AddScreenEffect(VGet(1920 / 2 - 1000, 1080 / 2, 0), 11);
				//1P勝利
			}
			else if (_Player[0]->GetHitPoint() * _Player[1]->GetMaxHp() < _Player[1]->GetHitPoint() * _Player[0]->GetMaxHp()) {
				_EFControl->AddScreenEffect(VGet(1920 / 2 + 1000, 1080 / 2, 0), 12);
				//1P勝利
			}
			else {
				_EFControl->AddScreenEffect(VGet(1920 / 2, 1080 / 2, 0), 13);
				_EFControl->AddScreenEffect(VGet(1920 / 2 - 616 / 2 - 250, 1080 / 2, 0), 14);
				_EFControl->AddScreenEffect(VGet(1920 / 2 + 616 / 2 + 250, 1080 / 2, 0), 15);
				//引き分け
			}
			_SceneFlag = 1;
			_Player[0]->SetState(_Player[0]->eActive);
			_Player[1]->SetState(_Player[1]->eActive);
			
			DeleteSoundMem(_Psy->GetBGMHandle());
		}
		break;

	}

	_BattleCnt--;
	_FinishFlag = FALSE;
	int sceneFlag = 2;
	if (_Player[0]->GetHitPoint() <= 0) { _FinishFlag = TRUE; }
	if (_Player[1]->GetHitPoint() <= 0) { _FinishFlag = TRUE; }
	if (_BattleCnt <= 0) { 
		_FinishFlag = TRUE;
		sceneFlag = 5;
	}


	if (_FinishFlag == TRUE&&_SceneFlag==0) {
		if (_Player[0]->GetHitPoint() * _Player[1]->GetMaxHp() > _Player[1]->GetHitPoint() * _Player[0]->GetMaxHp()) {
			_WinNum[0] +=20;
			//1P勝利
		}
		else if (_Player[0]->GetHitPoint() * _Player[1]->GetMaxHp() < _Player[1]->GetHitPoint() * _Player[0]->GetMaxHp()) {
			_WinNum[1] +=20;
			//1P勝利
		}
		else {
			_WinNum[0] += 7;
			_WinNum[1] += 7;
			//引き分け
		}
		_SceneFlag = sceneFlag;
		_EFControl->AddScreenEffect(VGet(1920 / 2 - 616 / 2 - 100, 1080 / 2, 0), 6);
		_EFControl->AddScreenEffect(VGet(1920 / 2 + 616 / 2 + 100, 1080 / 2, 0), 7);
		_EFControl->AddScreenEffect(VGet(1920 / 2, 1080 / 2, 0), 8);
		sndManager.GetSound("end")->Play();
	}




	SceneBase::Update();

	if (_FPSCon->GetUpdateFlag() == FALSE) { return; }
	_Player[0]->MotionUpdate();
	_Player[1]->MotionUpdate();
	_Player[0]->DamageUpdate();
	_Player[1]->DamageUpdate();



}

void SceneMain::Draw() {
	SceneBase::Draw();

}




int SceneMain::SceneEnd() {
	
	return 0;
}
bool SceneMain::GetGameSet()
{
	if (_WinNum[0] >= 40 || _WinNum[1] >= 40 || _WinNum[0] + _WinNum[1] > 40) {
		return TRUE;
	}
	return false;
}
;

