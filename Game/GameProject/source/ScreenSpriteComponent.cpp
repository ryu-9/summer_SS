#include "ScreenSpriteComponent.h"

ScreenSpriteComponent::ScreenSpriteComponent(ActorClass* _Owner, int cg, VECTOR size, int draworder, int alpha,int color,  bool rev, int blend)
	:SpriteComponent(_Owner,draworder)
,_Cg(cg)
,_Size(size)
,_Alpha(alpha)
,_Rev(rev)
,_Color(color)
,_BlendMode(blend)
{
}

ScreenSpriteComponent::~ScreenSpriteComponent()
{
}


void ScreenSpriteComponent::Draw()
{
	if (_Alpha != 255||_BlendMode!=DX_BLENDMODE_NOBLEND ) {
		SetDrawBlendMode(_BlendMode, _Alpha);
	}
	if (_Color != 0) {
		int r, g, b;
		GetColor2(_Color, &r, &g, &b);
		SetDrawBright(r, g, b);
	}
	VECTOR pos = _Owner->GetPosition();
	if (_Rev == TRUE) {
		DrawExtendGraph(pos.x + _Size.x / 2, pos.y - _Size.y / 2, pos.x - _Size.x / 2, pos.y + _Size.y / 2, _Cg, TRUE);
	}
	else {
		DrawExtendGraph(pos.x - _Size.x / 2, pos.y - _Size.y / 2, pos.x + _Size.x / 2, pos.y + _Size.y / 2, _Cg, TRUE);
	}
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
