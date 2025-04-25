#pragma once
#include "SpriteComponent.h"
#include "PlayerClass.h"

class PlayerUISpriteComponent : public SpriteComponent
{
public:

	PlayerUISpriteComponent(class PlayerClass* owner, int drawOrder = 100);
	~PlayerUISpriteComponent();
	void Draw() override;

	int GetDrawOrder() const { return _DrawOrder; }

protected:
	class PlayerClass* _Player;

private:
	int DrawStart;
	int DrawEnd;
	int Mask;
	int HPFrame;
	int Record;
	int Speaker[2];
	float Rotate;
};

