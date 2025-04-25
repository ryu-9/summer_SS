#pragma once
#include "SpriteComponent.h"
#include <string>
#include "UIChipClass.h"

class UIMessageSpriteComponent : public SpriteComponent {
public:
	UIMessageSpriteComponent(class UIChipClass* owner, int drawOrder = 500);
	void Draw() override;
private:
	std::string _Text;
	UIChipClass* _UIchip;
};

