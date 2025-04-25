#pragma once
#include <dxlib.h>
#include "ActorClass.h"

#define	FRAME_NUM	(6)

class FPSControlClass : public ActorClass
{
public :
	FPSControlClass(SceneBase* scene, int BPM);
	~FPSControlClass();

	void UpdateActor() override;
	bool GetUpdateFlag() const{ return UpdateFlag; }
	bool GetInputUDFlag() { return _InputUDFlag; }
	float GetDeltaTime() const { return _FrameTime; }
	float GetFrameNum() const { return _FrameNum; }
	int GetStopFrameCnt() { return _StopFrameCnt; }
	int GetFrameCnt() { return cnt; }
	int GetHitStop() { return _HitStop; }
	int GetSession() { return _SessionCnt; }
	int GetStartTime() { return _StartTime; }
	void Init(int BPM);
	int GetNowTime() { return now; }
	void StartSession();

private:
	int oldtime;
	float _FrameTime;
	bool UpdateFlag;
	float _DeltaTime;
	int cnt;
	int _StartTime;
	int _BPM;
	float _FrameNum;
	int _HitStop;
	int _StopFrameCnt;
	int _SessionCnt;
	bool _InputUDFlag;
	int now;
};