#pragma once
#include "ActorClass.h"
#include "EffectClass.h"
#include "vector"

class FlameClass : public ActorClass
{
public:
	FlameClass(class SceneBase* scene, ActorClass* owner, std::vector<int>* cg, int cnt = 0);
	virtual ~FlameClass();
	void UpdateActor() override;
	LightingComponent* GetLight() { return light; }
	void Init(int cnt);

private:
	int _Count;
	std::vector<EffectClass*> effects;
	ActorClass* _Root;
	class LightingComponent* light;
	int _CntMax;
	int _Start;
	int _Time;
	unsigned int _Color;
	std::vector<int> _FlashCg;
	//class MainSpriteComponent* sp;

};

