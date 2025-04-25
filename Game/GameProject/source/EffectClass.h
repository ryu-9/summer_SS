#pragma once
#include "ActorClass.h"
#include "vector"
#include "MainSpriteComponent.h"

class EffectClass : public ActorClass
{
public:
	EffectClass(int type, class SceneBase* scene, int draworder, VECTOR pos,VECTOR size, std::vector<int> cgArray, int cgnum, bool fpsflag, int blend, int value, int color, int ScreenFlag, bool rev = FALSE, int cnt = 0);
	virtual ~EffectClass();
	void UpdateActor() override;
	int GetType() { return _Type; };
	bool GetDelFlag() { return _DelFlag; }
	MainSpriteComponent* GetSprite() { return sp; }
	int GetCount();

private:
	int _Cnt;
	int _CgTime;
	int _StartTime;
	std::vector<int> _CgArray;
	class MainSpriteComponent* sp;
	class ScreenSpriteComponent* sc;
	bool _FPSFlag;
	int _ScreenFlag;
	int _Type;
	bool _DelFlag;
};

