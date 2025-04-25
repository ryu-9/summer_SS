#pragma once
#include "Component.h"
#include "DxLib.h"
#include "UIChipClass.h"

class UIExitComponent : public Component
{
public:
	UIExitComponent(class UIChipClass* owner, float start, float end, int frame, int updateOrder = 80);
	virtual ~UIExitComponent();

	void Update() override;

private:
	UIChipClass* _UIc;
	float _Start;
	float _End;
	int _Frame;
	int _Cnt;
};

