#include "FPSControlClass.h"
#include "SceneBase.h"
#include "SceneMain.h"

FPSControlClass::FPSControlClass(SceneBase* scene, int BPM)
	:ActorClass(scene)
	,UpdateFlag (FALSE)
	,_DeltaTime(0)
	,cnt(0)
	//,_BPM(BPM)
	,_HitStop(0)
	,_StopFrameCnt(0)
	, _SessionCnt(0)
{
	_FrameTime = 60.0f * 1000 /((float)BPM*FRAME_NUM);
	//_StartTime = GetNowCount();
	_StartTime = 0;
	oldtime = _StartTime;
	int FPS = 60;
	if (GetFPS() > 70) { FPS = 144; }
	if (GetFPS() > 150) { FPS = 244; }
	_FrameNum = 60.0f * FPS / ((float)BPM * FRAME_NUM);
}

FPSControlClass::~FPSControlClass()
{
}

void FPSControlClass::UpdateActor()
{
	if (_DeltaTime != 0 && _DeltaTime < 0.1) {
		_DeltaTime = 0;
	}

	_FrameNum = 60.0f * GetFPS() / ((float)_BPM * FRAME_NUM);

	_InputUDFlag = FALSE;
	if (GetScene()->GetSceneFlag() != 0) {
		now = GetNowCount();
		if (now - _StartTime >= 120000) {
			_StartTime = GetNowCount();
		}
	}
	else {
		if (_StartTime%60000 != 0) {
			oldtime = 0;
			_StartTime = 0;
		}

		now = SyncSystem.GetPlayerTime();

		/*

		*/
		while (now - _StartTime >= 120000) {
			_StartTime += 60000;
		}
	}	//now = GetNowCount();

	_DeltaTime += now - oldtime;
	oldtime = now;
	UpdateFlag = FALSE;

	if (now-_StartTime>=60000) {
		_StartTime += 60000;
		_DeltaTime = now - _StartTime;
		if (cnt < _BPM*FRAME_NUM) {
			UpdateFlag = TRUE;
			cnt++;
		}
	}
	if (_HitStop > 0) {
		if (_DeltaTime >= _FrameTime) {
			_HitStop--;
			_DeltaTime -= _FrameTime;
			_StopFrameCnt++;
			cnt++;
			UpdateFlag = TRUE;
		}
		return;
	}
	if (_StopFrameCnt > 0) {
		_StopFrameCnt = 0;
	}

	int DamageCnt = 0;
	if (GetScene()->GetPlayer(0)->GetDamage() > 0) {
		DamageCnt++;
	}
	if (GetScene()->GetPlayer(1)->GetDamage() > 0) {
		DamageCnt++;
	}

	if (DamageCnt==1) {
		int motionID;
		for (int i = 0; i < 2; i++) {
			motionID = GetScene()->GetPlayer(i)->GetMotionID();
			switch (motionID) {
			case MotionComponent::MOT_R_ATTACK2_STAND_SUC:
			case MotionComponent::MOT_L_ATTACK2_STAND_SUC:
			case MotionComponent::MOT_R_ATTACK2_CROUCH_SUC:
			case MotionComponent::MOT_L_ATTACK2_CROUCH_SUC:
			case MotionComponent::MOT_R_ATTACK2_COMBO1_SUC:
			case MotionComponent::MOT_L_ATTACK2_COMBO1_SUC:
			case MotionComponent::MOT_R_ATTACK2_COMBO2_SUC:
			case MotionComponent::MOT_L_ATTACK2_COMBO2_SUC:
			case MotionComponent::MOT_R_ATTACK1_COMBO2:
			case MotionComponent::MOT_L_ATTACK1_COMBO2:
			case MotionComponent::MOT_R_GRAB_SUC:
			case MotionComponent::MOT_L_GRAB_SUC:
				_HitStop = 10;			//吹っ飛び時のヒットストップ
				break;

			default:
				if (_HitStop <= 10) {
					_HitStop = 4;
				}
				break;
			}
		}
	}
	if (_DeltaTime >= _FrameTime) {
		_DeltaTime -= _FrameTime;
		UpdateFlag = TRUE;
		cnt++;
		if (_DeltaTime >= _FrameTime) {
			float tmpDelta = _DeltaTime;
			while (_DeltaTime >= _FrameTime*2) {
		_DeltaTime -= _FrameTime;
		if (tmpDelta == _DeltaTime) {
			_DeltaTime = 0;
			break;
		}
				cnt++;
	}
	}
		else {
			int test = 0;
		}
	}
	if (_SessionCnt > 0&&UpdateFlag==TRUE) {
		_SessionCnt--;
		if (_SessionCnt == 1) {
			GetScene()->GetPlayer(0)->FrameProcess();
			GetScene()->GetPlayer(1)->FrameProcess();
		}
		UpdateFlag = FALSE;
		_InputUDFlag = TRUE;
		return;
	}


}

void FPSControlClass::Init(int BPM)
{
	_BPM = BPM;
	_FrameTime = 60.0f * 1000 / ((float)BPM * FRAME_NUM);
	_StartTime = GetNowCount();
	if (_StartTime / 60000 == 0) { _StartTime--; }
	_DeltaTime = 0;
	oldtime = _StartTime;
	int FPS = GetFPS();
	if (GetFPS() > 60) { FPS = 144; }
	if (GetFPS() > 144) { FPS = 244; }
	_HitStop = 0;
	_FrameNum = 60.0f * FPS / ((float)BPM * FRAME_NUM);
}

void FPSControlClass::StartSession()
{
	if (_SessionCnt <= 0) {
		_SessionCnt = FRAME_NUM * 2 + 1;
		auto scene = dynamic_cast<SceneMain*>(GetScene());
		VECTOR pos = VAdd(VAdd(GetScene()->GetPlayer(0)->GetEnHitPos(), GetScene()->GetPlayer(0)->GetPosition()), VAdd(GetScene()->GetPlayer(1)->GetEnHitPos(), GetScene()->GetPlayer(1)->GetPosition()));
		scene->GetEffectCon()->AddEffect(VScale(pos, 0.5), 121);
	}
}
