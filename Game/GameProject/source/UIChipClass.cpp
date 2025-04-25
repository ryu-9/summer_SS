#include "UIChipClass.h"
#include "UIChipSpriteComponent.h"

UIChipClass::UIChipClass(SceneBase* scene, VECTOR pos,VECTOR scale,  int drawtype ,std::string fname, int draworder)
	:ActorClass(scene)
	,_Scale(scale)
	,_DrawType(drawtype)
	, _Num(0)
{
	_Sp = new UIChipSpriteComponent(this,draworder);
	_Sp->SetImage(fname.c_str());
	_Position = pos;
}

void UIChipClass::AddImage(std::string fname) {
	_Sp->SetImage(fname.c_str());
}

int UIChipClass::GetImageSize()
{
	return _Sp->GetImageSize();
}
