#include "EffectClass.h"
#include "SceneBase.h"
#include "ScreenSpriteComponent.h"
#include "SceneMain.h"
#include "deque"

EffectClass::EffectClass(int type, class SceneBase* scene, int draworder, VECTOR pos, VECTOR size, std::vector<int> cgArray, int cgtime, bool fpsflag, int blend, int value, int color, int ScreenFlag, bool rev, int cnt)
	:ActorClass(scene)
	,_Cnt(cnt)
	,_FPSFlag(fpsflag)
	,_ScreenFlag(ScreenFlag)
	,_CgTime(cgtime)
	,_StartTime(GetNowCount())
	,_Type(type)
	, _DelFlag(FALSE)
{
	_CgArray.resize(cgArray.size());
	std::copy(cgArray.begin(), cgArray.end(), _CgArray.begin());
	//_CgNum = _CgArray.size();
	SetPosition(pos);

	if (_ScreenFlag==0) {
		sp = new MainSpriteComponent(this, size, "noimage", draworder, blend, value, color, rev);
		if (_Cnt < 0) {
			sp->ChangeImage(-2);
		}
		else {
			if (_CgArray.size() > 0) {
				sp->ChangeImage(_CgArray[_Cnt]);
			}
			else {
				delete this;
				return;
			}
		}
		delete sc;
	}
	else {
		int alpha = 255;
		switch (_ScreenFlag) {
		case 1:
		case 2:
		case 3:
		case 6:
		case 7:
		case 8:
		case 13:
		case 14:
		case 15:
		case 17:
			alpha = 0;
			break;
		default:
			break;
		}
		sc = new ScreenSpriteComponent(this, cgArray[0], size, draworder, alpha, color, rev, blend);
		delete sp;
	}

}

EffectClass::~EffectClass()
{
	auto scene = dynamic_cast<SceneMain*>(GetScene());


	switch (_ScreenFlag) {
	case 3:									//試合開始時エフェクト
		GetScene()->SetSceneFlag(0);
		break;

	case 8:
		//GetScene()->SetSceneFlag(3);
		break;
	case 16:									//フェードインエフェクト
		scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W + 2080, SCREEN_H / 2, 0), 18);
		sndManager.GetSound("start")->Play();
		break;
	case 18:									
		scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2 - 616 / 2 - 100, SCREEN_H / 2, 0), 1);
		scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2 + 616 / 2 + 100, SCREEN_H / 2, 0), 2);
		scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2, SCREEN_H / 2, 0), 3);
		scene->GetRhythm()->Play();
		
	//	scene->GetAI()->SetAI();
		break;

	case 17:									//フェードアウトエフェクト
		GetScene()->SetSceneFlag(4);
		if (scene->GetGameSet() == FALSE) {
		scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2, SCREEN_H / 2, 0), 16);
		}
		else { scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2, SCREEN_H / 2, 0), 19); }
		break;


	default:
		break;
	
	}
	if (_DelFlag != TRUE) {
		int test = 0;
	}
	
	if (scene != nullptr) { scene->GetEffectCon()->RemoveEffects(this); }

}

void EffectClass::UpdateActor()
{
	if (_DelFlag == TRUE) {
		delete this;
		return;
	}
	auto scene = dynamic_cast<SceneMain*>(GetScene());
	VECTOR pos = GetPosition();
	if (_CgTime > 0) {
		if (_FPSFlag == TRUE) {
			if (GetScene()->GetFPSCon()->GetUpdateFlag() == FALSE) { return; }
			if (GetScene()->GetPlayer(0)->GetState() == ePaused ||
				GetScene()->GetPlayer(0)->GetSlowFlag() > 1) {
				return;
			}
			_Cnt++;
			if (_Cnt >= _CgTime) {
				_DelFlag = TRUE;
				return;
			}
		}
		else {
			_Cnt = GetNowCount();
			if (_Cnt - _StartTime >= _CgTime) {
				_DelFlag = TRUE;
				return;
			}
		}
	}
	else { if (_Cnt > 0) { _Cnt--; } }
	
	//if (GetScene()->GetFPSCon()->GetUpdateFlag() == FALSE) { return; }

	int CgNum = (float)(_Cnt - _StartTime) / _CgTime * _CgArray.size();


	if (_ScreenFlag == 0) {
		if (_FPSFlag == TRUE) {
			int size = _CgArray.size();
			if (size <= _Cnt) {
				sp->ChangeImage(_CgArray[_CgArray.size() - 1]);
			}
			else if(_Cnt>=0){
				sp->ChangeImage(_CgArray[_Cnt]); 
			}
		}
		else { sp->ChangeImage(_CgArray[CgNum]); }
	}
	else {
		if (_CgArray.size() <= CgNum) {
			sc->ChangeImage(_CgArray[_CgArray.size() - 1]);
		}
		else { sc->ChangeImage(_CgArray[CgNum]); }
	}



	VECTOR move = VGet(0, 0, 0);
	bool rev = FALSE;

	switch (_Type) {

	case 23:
	case 25:
		rev = TRUE;
	case 22:
	case 24:
		switch (GetScene()->GetPlayer(0)->GetType()) {
		case 0:
			move = VGet(150, 0, 0);
			break;
		case 1:
			move = VGet(150, 0, 0);
			break;
		default:
			break;

		}
		break;

	default:
		break;
	
	}




	if (_Type >= 21 && _Type <= 100 && _Cnt > 0) {
		
		if (_Type <= 60) {
			if (GetScene()->GetPlayer(0)->GetState() == ePaused) { return; }
			float slow = 1;
			if (GetScene()->GetPlayer(0)->GetSlowFlag() > 0) { slow = 0.2; }
			std::deque<VECTOR> oldposition = *GetScene()->GetPlayer(0)->GetOldPosition();
			pos = VAdd(pos, VScale(VSub(GetScene()->GetPlayer(0)->GetPosition(), oldposition[0]), slow));
			/*
			if (GetScene()->GetPlayer(0)->GetMotChange() == TRUE) {
				delete this;
				return;
			}
			*/
		}
		else {
			if (GetScene()->GetPlayer(0)->GetState() == ePaused) { return; }
			float slow = 1;
			if (GetScene()->GetPlayer(0)->GetSlowFlag() > 1) { slow = 0.2; }

			std::deque<VECTOR> oldposition = *GetScene()->GetPlayer(1)->GetOldPosition();
			pos = VAdd(pos, VScale(VSub(GetScene()->GetPlayer(1)->GetPosition(), oldposition[0]),slow));
			/*
						if (GetScene()->GetPlayer(1)->GetMotChange() == TRUE) {
				delete this;
				return;
			}
			*/
		}
		if (rev == TRUE) { move = VGet(-move.x, move.y, 0); }
		pos = VAdd(pos, move);
	}




	SetPosition(pos);



	switch (_ScreenFlag) {
	case 1:
		if ((float)(_Cnt - _StartTime) / _CgTime < 0.2) {
			SetPosition(VGet(SCREEN_W / 2 - 616 / 2 - 100 + 100 * (_Cnt - _StartTime) / _CgTime / 0.2, GetPosition().y, 0));
		}
		else { SetPosition(VGet(SCREEN_W / 2 - 616 / 2, GetPosition().y, 0)); }	
		sc->SetAlpha(255 * (_Cnt - _StartTime) / _CgTime / 0.2);
		break;
	case 2:
		if ((float)(_Cnt - _StartTime) / _CgTime < 0.2) {
			SetPosition(VGet(SCREEN_W / 2 + 616 / 2 + 100 - 100 * (_Cnt - _StartTime) / _CgTime / 0.2, GetPosition().y, 0));		
		}
		else { SetPosition(VGet(SCREEN_W / 2 + 616 / 2, GetPosition().y, 0)); }	
		sc->SetAlpha(255 * (_Cnt - _StartTime) / _CgTime / 0.2);
		break;
	case 3:
		sc->SetAlpha(255 * (_Cnt - _StartTime) / _CgTime / 0.2);
		break;
	case 6:
		if ((float)(_Cnt - _StartTime) / _CgTime < 0.2) {
			SetPosition(VGet(SCREEN_W / 2 - 616 / 2 - 100 + 100 * (_Cnt - _StartTime) / _CgTime / 0.2, GetPosition().y, 0));
		}
		else { SetPosition(VGet(SCREEN_W / 2 - 616 / 2, GetPosition().y, 0)); }
		sc->SetAlpha(255 * (_Cnt - _StartTime) / _CgTime / 0.2);
		break;
	case 7:
		if ((float)(_Cnt - _StartTime) / _CgTime < 0.2) {
			SetPosition(VGet(SCREEN_W / 2 + 616 / 2 + 100 - 100 * (_Cnt - _StartTime) / _CgTime / 0.2, GetPosition().y, 0));
		}
		else { SetPosition(VGet(SCREEN_W / 2 + 616 / 2, GetPosition().y, 0)); }
		sc->SetAlpha(255 * (_Cnt - _StartTime) / _CgTime / 0.2);
		break;
	case 8:
		sc->SetAlpha(255 * (_Cnt - _StartTime) / _CgTime / 0.2);
		break;
	case 11:
		if ((float)(_Cnt - _StartTime) / _CgTime < 0.1) {
			SetPosition(VGet(SCREEN_W / 2 - 1000 + 1000 * (_Cnt - _StartTime) / _CgTime / 0.1, GetPosition().y, 0));
		}
		else { SetPosition(VGet(SCREEN_W / 2 , GetPosition().y, 0)); }
		if (_Cnt - _StartTime> _CgTime /2) {
			scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2, SCREEN_H / 2, 0), 17);
			_ScreenFlag = -1;
		}
		break;
	case 12:
		if ((float)(_Cnt - _StartTime) / _CgTime < 0.1) {
			SetPosition(VGet(SCREEN_W / 2 + 1000 - 1000 * (_Cnt - _StartTime) / _CgTime / 0.1, GetPosition().y, 0));
		}
		else { SetPosition(VGet(SCREEN_W / 2 , GetPosition().y, 0)); }
		if (_Cnt - _StartTime > _CgTime / 2) {
			scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2, SCREEN_H / 2, 0), 17);
			_ScreenFlag = -1;
		}
		break;
	case 13:
		sc->SetAlpha(255 * (_Cnt - _StartTime) / _CgTime / 0.2);
		if (_Cnt - _StartTime > _CgTime / 2) {
			scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2, SCREEN_H / 2, 0), 17);
			_ScreenFlag = -1;
		}
		break;
	case 14:
		if ((float)(_Cnt - _StartTime) / _CgTime < 0.2) {
			SetPosition(VGet(SCREEN_W / 2 - 616 / 2 - 100 + 100 * (_Cnt - _StartTime) / _CgTime / 0.2, GetPosition().y, 0));
		}
		else { SetPosition(VGet(SCREEN_W / 2 - 616 / 2, GetPosition().y, 0)); }
		sc->SetAlpha(255 * (_Cnt - _StartTime) / _CgTime / 0.2);
		break;
	case 15:
		if ((float)(_Cnt - _StartTime) / _CgTime < 0.2) {
			SetPosition(VGet(SCREEN_W / 2 + 616 / 2 + 100 - 100 * (_Cnt - _StartTime) / _CgTime / 0.2, GetPosition().y, 0));
		}
		else { SetPosition(VGet(SCREEN_W / 2 + 616 / 2, GetPosition().y, 0)); }
		sc->SetAlpha(255 * (_Cnt - _StartTime) / _CgTime / 0.2);
		break;
	case 16:
		sc->SetAlpha(255 - 255 * (_Cnt - _StartTime) / _CgTime*3/2);
		break;

	case 17:
		sc->SetAlpha(255 * (_Cnt - _StartTime) / _CgTime*3/2);
		break;
	case 18:
		SetPosition(VGet(SCREEN_W / 2 + 2080 - 4160 * (_Cnt - _StartTime) / _CgTime, GetPosition().y, 0));
		break;

	case 50:
		if (rand() % 10 == 0) {
			_Cnt = 10;
		}
		sc->SetSize(VGet((100 + _Cnt) / 2, (100 + _Cnt) / 2, 0));
		break;

	case 51:
		if (_StartTime<GetScene()->GetPlayer(1)->GetVolume()) {
			_Cnt = 10;
		}
		_StartTime = GetScene()->GetPlayer(1)->GetVolume();
		sc->SetSize(VGet((100 + _Cnt) / 2, (100 + _Cnt) / 2, 0));
		break;

	case 52:
		if (_StartTime < GetScene()->GetPlayer(0)->GetVolume()) {
			_Cnt = 10;
		}
		_StartTime = GetScene()->GetPlayer(0)->GetVolume();
		sc->SetSize(VGet((100 + _Cnt) / 2, (100 + _Cnt) / 2, 0));
		break;

	case 53:
		if (_StartTime < GetScene()->GetPlayer(1)->GetVolume()) {
			_Cnt = 10;
		}
		_StartTime = GetScene()->GetPlayer(1)->GetVolume();
		if (_Cnt == 0) {
			sc->SetAlpha(0);
		}
		else sc->SetAlpha(255);
		sc->SetSize(VGet((200 - _Cnt) / 2, (200 - _Cnt) / 2, 0));
		break;
	case 54:
		if (_StartTime < GetScene()->GetPlayer(0)->GetVolume()) {
			_Cnt = 10;
		}
		_StartTime = GetScene()->GetPlayer(0)->GetVolume();
		if (_Cnt == 0) {
			sc->SetAlpha(0);
		}
		else sc->SetAlpha(255);
		sc->SetSize(VGet((200 - _Cnt) / 2, (200 - _Cnt) / 2, 0));
		break;

	case 55:
		move.x = sqrt((float)(_Cnt - _StartTime) / _CgTime);
		sc->SetSize(VGet(500 * move.x, 105, 0));
		sc->SetAlpha(255 - 255 * move.x);
		SetPosition(VGet(-move.x * 250 + SCREEN_W / 2 - 102, 1011, 0));
		break;
	case 56:
		move.x = sqrt((float)(_Cnt - _StartTime) / _CgTime);
		sc->SetSize(VGet(500 * move.x, 105, 0));
		sc->SetAlpha(255 - 255 * move.x);
		SetPosition(VGet(move.x * 250 + SCREEN_W / 2 + 102, 1011, 0));
		break;

	case 60:
	case 62:
	case 63:
		move.x = sqrt((float)(_Cnt - _StartTime) / _CgTime);
		sc->SetAlpha(255 - 255 * move.x);
		break;
	default:
		break;

	}
}

int EffectClass::GetCount()
{
	if (_FPSFlag == TRUE) {
		return _Cnt;
	}
	else {
		return (float)(_Cnt - _StartTime) / _CgTime * _CgArray.size();
	}
}
