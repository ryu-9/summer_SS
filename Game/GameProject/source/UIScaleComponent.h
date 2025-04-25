#pragma once
#include "UIActionComponentBase.h"
#include "Component.h"
#include "DxLib.h"
#include "UIChipClass.h"


class UIScaleComponent : public UIActionComponentBase {
public:
	UIScaleComponent(class UIChipClass* owner,VECTOR start,VECTOR end, int frame, int entype,int easetype, int updateOrder = 100);
	void ProcessInput() override;
	void Update() override;

};

