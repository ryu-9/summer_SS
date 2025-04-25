#pragma once
#include "ActorClass.h"
#include "Component.h"

class LightingComponent : public Component{
public:
	LightingComponent(ActorClass* owner, VECTOR size, int file, int fadeCnt = -1, VECTOR center = VGet(0, 0, 0), int color = GetColor(255, 255, 255));
	virtual ~LightingComponent();
	void SetImage(int cg) { _Cg = cg; }
	void Draw(bool color = TRUE, bool blend = TRUE);

	int GetFadeCnt() { return 30 * (GetNowCount() - _Start) / _FadeCnt; }
	VECTOR GetPosition() { return VAdd(_Owner->GetPosition(),_Center); }
	void SetVert(VECTOR v1, VECTOR v2, VECTOR v3, VECTOR v4) {
		vert[0] = v1;	vert[1] = v2;	vert[2] = v3;	vert[3] = v4;
	}
	void SetColor(unsigned int color) { _Color = color; }
	int GetImage() { return _Cg; }
	int GetLightColor() { return _Color; }
	void SetReverse(bool flag) { _Rev = flag; }
	void SetValue(int value) { _Value = value; }
	void SetFlag(bool flag) { _Flag = flag; }
	bool GetFlag() { return _Flag; }

private:
	VECTOR _Center;
	VECTOR _Size;
	int _Cg;
	VECTOR vert[4];
	int _FadeCnt;
	int _Start;
	unsigned int _Color;
	bool _Rev;
	int _Value;
	bool _Flag;
};

