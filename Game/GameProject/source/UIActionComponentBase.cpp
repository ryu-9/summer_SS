#include "UIActionComponentBase.h"


UIActionComponentBase::UIActionComponentBase(UIChipClass* owner, VECTOR start, VECTOR end, int frame, int entype, int easetype, int updateOrder)
	:Component(owner, updateOrder)
	, _UIc(owner)
	,_EndType(entype)
	,_EaseType(easetype)
{
	_eData.start = start;
	_eData.end = end;
	_eData.frame = frame;
	_eData.cnt = 0;
}

UIActionComponentBase::~UIActionComponentBase()
{
}

void UIActionComponentBase::Update()
{
}
