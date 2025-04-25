#pragma once
#include "Dxlib.h"
#include "SpriteComponent.h"
#include "SceneBase.h"

class MainSpriteComponent : public SpriteComponent
{
public:

	MainSpriteComponent(ActorClass* Owner, VECTOR size, const TCHAR* file, int DrawOrder=100, int BlendMode=DX_BLENDMODE_NOBLEND, int value=0, int color=0, bool rev = FALSE, bool maskflag=FALSE);
	virtual ~MainSpriteComponent();

	void SetCgnum(int i);
	void ChangeImage(int cg);
	void Draw() override;
	void SetReverse(bool rev) { _Reverse = rev; }
	void SetRotate(float rotate) { _Rotate = rotate; }
	void SetVert(VECTOR v1, VECTOR v2, VECTOR v3, VECTOR v4) {
		vert[0] = v1;	vert[1] = v2;	vert[2] = v3;	vert[3] = v4;
	}
	void SetColor(unsigned int color) { _Color = color; }
	void SetMask(MainSpriteComponent* sp) { _Obj = sp; };
	void SetValue(int value) { _Value = value; }
	int GetValue() { return _Value; }
	int GetBlendMode() { return _BlendMode; }
	void SetBlendMode(int mode) { _BlendMode = mode; }
	int GetMyColor() { return _Color; }
	void SetMyColor(int color) { _Color = color; }


private:
	VECTOR vert[4];
	int _Cg;
	int _BlendMode;
	int _Value;
	float _Rotate;
	unsigned int _Color;
	bool _Reverse;
	int _Mask;
	MainSpriteComponent* _Obj;


};

