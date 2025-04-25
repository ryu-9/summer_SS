#pragma once
#include "UIActionComponentBase.h"
#include "DxLib.h"
#include "UIChipClass.h"

class UICursorComponent : public UIActionComponentBase {
public:
	UICursorComponent(class UIChipClass* owner, VECTOR start, VECTOR end, int frame, int entype, int easetype, int updateOrder = 100);
	virtual ~UICursorComponent();

	void Update() override;

};

