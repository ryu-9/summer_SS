#pragma once
#include "SpriteComponent.h"

class StageLightSpriteComponent : public SpriteComponent
{
public:
	StageLightSpriteComponent(class ActorClass* _Owner, int* color);
	~StageLightSpriteComponent();

	void Draw() override;

private:
	int _Light;
	int* _Color;
	bool _NO;
};

