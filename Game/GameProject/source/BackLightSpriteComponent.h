#pragma once
#include "SpriteComponent.h"
#define BACKLIGHT_SIZE	(2000)

class BackLightSpriteComponent : public SpriteComponent
{
public:
	BackLightSpriteComponent(class ActorClass* _Owner, bool playerNo);
	virtual ~BackLightSpriteComponent();
	void Draw() override;
	int GetCount() { return _Cnt; }
	void SetCount(int count) { _Cnt = count; }
private:
	int _Cg;
	bool _No;
	int _Cnt;
};

