#pragma once
#include "SpriteComponent.h"
#include "ActorClass.h"

struct easing {
	int start, off, end, now;
	float point;
};

class PsylliumSpriteComponent : public SpriteComponent
{
public:
	PsylliumSpriteComponent(int cg, int cgF, int cgP, int* color, float X, float Z, ActorClass* Owner,
		float *easing, int *angle, int *arm, int* height, int* slope, int DrawOrder=100);
	virtual ~PsylliumSpriteComponent();

	bool GetUse() const { return use; }
	void Draw() override;
	void SetColor(int r, int g, int b);

private:
	float lag;
	int x, z;
	int _Cg;
	int _CgF;
	int _CgP;
	float rotate;
	int *_Arm;
	int *_Angle;
	float *_Easing;
	int* _Height;
	int* _Slope;
	float armError;
	int type;
	bool use;
	int _Arrow;
	int _Color[3];
	int* _StageColor;
};

