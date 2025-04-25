#pragma once
#include "SpriteComponent.h"
#include "UIChipSpriteComponent.h"
#include "UICharaClass.h"
class UICharaClass;
class UICharaSpriteComponent : public UIChipSpriteComponent {
public:
	UICharaSpriteComponent(class UICharaClass* owner, int drawOrder = 120);

	void Draw() override;

private:
	class UICharaClass* _UIChara;
	int _Width;
	int _Height;
};

