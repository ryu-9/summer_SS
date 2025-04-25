#pragma once
#include "UIChipClass.h"
#include "UIActionComponentBase.h"
#include "DxLib.h"
class UIMoveComponent : public UIActionComponentBase {
public:
	UIMoveComponent(class UIChipClass* owner, VECTOR start, VECTOR end, int frame, int entype, int easetype, int updateOrder = 100);
	virtual ~UIMoveComponent();

	void Update() override;

};

