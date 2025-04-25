#pragma once
#include "ActorClass.h"
#include "BackLightSpriteComponent.h"
#include "LightingComponent.h"

class BackLightClass : public ActorClass
{
public:
	BackLightClass(class SceneBase* scene, bool playerNo);
	BackLightSpriteComponent* GetSprite() { return sp; }
	virtual ~BackLightClass();
	void UpdateActor() override;
	LightingComponent* GetLight() { return light; };
private:
	bool _No;
	BackLightSpriteComponent* sp;
	LightingComponent* light;
	int cg;
};

