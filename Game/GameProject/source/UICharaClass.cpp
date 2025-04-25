#include "UICharaClass.h"
#include "UICharaSpriteComponent.h"
#include "UICharaComponent.h"

UICharaClass::UICharaClass(class SceneBase* scene, VECTOR pos, VECTOR scale, int drawtype, int charatype, const TCHAR* fname)
	:UIChipClass(scene, pos, scale, drawtype, fname)
{
	SetDrawScript();
	auto cs = new UICharaSpriteComponent(this, 100);
	_CharaType = charatype;
}

void UICharaClass::SetDrawScript()
{
//	new UICharaFaceChangeComponent(this,0);
}
