#pragma once
#include "SpriteComponent.h"
#include "RhythmControlClass.h"

class NoteSpriteComponent : public SpriteComponent
{
public:
	NoteSpriteComponent (class ActorClass* owner, int drawOrder = 100);
	virtual ~NoteSpriteComponent();

	void Draw() override;
	void SetImage(const TCHAR* filename) override;


private:
	class RhythmControlClass* _RhythmCon;
	float _DrawX;
	float _DrawY;
	int _Lane;
	int _Speaker;
	int _Point;
	int _Time[7];
};

