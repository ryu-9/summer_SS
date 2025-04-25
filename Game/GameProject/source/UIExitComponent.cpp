#include "UIExitComponent.h"
#include "mymath.h"

UIExitComponent::UIExitComponent(UIChipClass* owner, float start, float end, int frame, int updateOrder)
	:Component(owner,updateOrder)
	, _UIc(owner)
	, _Start(start)
	, _End(end)
	, _Frame(frame)
	, _Cnt(0)
{
}

UIExitComponent::~UIExitComponent()
{

}

void UIExitComponent::Update()
{
	auto n = 1.70158f;
	auto nn = n + 1;
	auto tmp = (float)_Cnt / (float)_Frame;
	auto scale = 1 - (nn * tmp * tmp * tmp - n * tmp * tmp);
	_UIc->SetScale(VGet(scale,scale,0));
	if (_Cnt >= _Frame) {
		_Owner->SetState(ActorClass::eDead);
	}
	_Cnt++;
}
