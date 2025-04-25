#pragma once
#include "SpriteComponent.h"
#include "vector"

class ScreenSpriteComponent : public SpriteComponent
{
public:
	ScreenSpriteComponent(ActorClass* _Owner, int cg, VECTOR size, int draworder, int alpha = 255, int color = 0, bool rev = FALSE, int blend = DX_BLENDMODE_NOBLEND);
	~ScreenSpriteComponent();
	void Draw() override;
	void ChangeImage(int cg) { _Cg = cg; }
	void SetAlpha(int alpha) { _Alpha = alpha; }
	void SetSize(VECTOR size) { _Size = size; }

private:
	int _Cg;
	VECTOR _Size;
	int _Alpha;
	bool _Rev;
	int _Color;
	int _BlendMode;
};

