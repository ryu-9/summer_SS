#pragma once
#include "UIChipClass.h"


class UIFadeSpriteClass : public UIChipClass {
public:
	struct  EASING
	{
		float start;
		float end;
		int cnt;
		int frame;
	};

	UIFadeSpriteClass(class SceneBase* scene,EASING easing, VECTOR pos = VGet(0, 0, 0), VECTOR scale = VGet(120,120,0), int drawtype = 0, const TCHAR* fname = "res/stage/fade.png");
	void UpdateActor() override;
private :
	EASING _FadeData;
};

