#include "UIFadeSpriteClass.h"
#include "UIChipSpriteComponent.h"
#include "SceneBase.h"

UIFadeSpriteClass::UIFadeSpriteClass(SceneBase* scene, EASING easing, VECTOR pos, VECTOR scale, int drawtype, const TCHAR* fname)
	:UIChipClass(scene,pos,scale,drawtype,fname,1000)
	,_FadeData(easing)
{
	_Sp->SetBlendMode(DX_BLENDMODE_ALPHA);
}

void UIFadeSpriteClass::UpdateActor() {
	float tmp = (_FadeData.end - _FadeData.start) * ((float)_FadeData.cnt / (float)_FadeData.frame) + _FadeData.start;
	_Sp->SetBlendPalam(tmp);
	if (_FadeData.cnt == _FadeData.frame) {
		if (_FadeData.end == 255) {
			GetScene()->SetChangeFlag(1);
		}
		GetScene()->DeleteFade();

		return;
	}
	_FadeData.cnt++;
}
