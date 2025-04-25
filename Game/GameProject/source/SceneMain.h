#pragma once
#include "SceneBase.h"
#include "RhythmControlClass.h"
#include "Stage.h"
#include "EffectControlClass.h"
#include "AIControlClass.h"
#include "BackLightClass.h"


class SceneMain	:	public SceneBase{
public:
	SceneMain(class Main* main);
	virtual ~SceneMain();

	void Init() override;
	void Update() override;
	void Draw() override;
	int SceneEnd() override;
	EffectControlClass* GetEffectCon() { return _EFControl; }
	AIControlClass* GetAI() { return _AI; }
	int GetFinishFlag() const { return _FinishFlag; }
	int GetRound() { return (_WinNum[0] + _WinNum[1]) / 14; }
	bool GetGameSet();
	void SetBCnt(int num) { _BattleCnt = num; }
	StageBase* GetStage() { return _Stage; }
	BackLightClass* GetBackLight(int i = 0) { return _BackLight[i]; }
	RhythmControlClass* GetRhythm() { return _Psy; };

	void SetMyColor(int color) { _Color = color; }
	int GetMyColor() { return _Color; }

private:
	float _HPRatio[2];
	int _WinNum[2];
	RhythmControlClass* _Psy;
	EffectControlClass* _EFControl;
	class AIControlClass* _AI;
	bool _FinishFlag;
	int _Cnt;
	int _BattleCnt;
	int _FPSCnt;
	StageBase* _Stage;
	BackLightClass* _BackLight[2];
	int _Color;
	//bool _GameSet;
};
