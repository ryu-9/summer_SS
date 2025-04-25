#include "UIMoveComponent.h"
#include "ActorClass.h"
#include "mymath.h"

namespace {
	float t1_1 = 7.5625;
	float t1_2 = 2.75;
}

UIMoveComponent::UIMoveComponent(class UIChipClass* owner, VECTOR start, VECTOR end, int frame, int entype, int easetype, int updateOrder)
	:UIActionComponentBase(owner, start, end, frame, entype, easetype, updateOrder)
{
	if (entype == 0) {
		_Owner->SetState(ActorClass::ePreparation);
	}
}

UIMoveComponent::~UIMoveComponent() {
	_Owner->SetState(ActorClass::eActive);
}

void UIMoveComponent::Update() {
	VECTOR tmp;
	switch (_EaseType)
	{
		{
	case 0:
		tmp = VGet(EasingInCubic(_eData.cnt, _eData.start.x, _eData.end.x, _eData.frame), EasingInCubic(_eData.cnt, _eData.start.y, _eData.end.y, _eData.frame), EasingInCubic(_eData.cnt, _eData.start.z, _eData.end.z, _eData.frame));
		break;
		}
		{
	case 1:
		auto par = 0.0f;
		float s = (float)_eData.cnt / (float)_eData.frame;
		if (s < 1 / t1_1) {
			par = t1_1 * s * s;
		}
		else if (s < 2 / t1_2) {
			par = t1_1 * (s -= 1.5f / t1_2) * s + 0.75f;
		}
		else if (s < 2.5 / t1_2) {
			par = t1_1 * (s -= 2.25f / t1_2) * s + 0.9375f;
		}
		else {
			par = t1_1 * (s -= 2.625f / t1_2) * s + 0.9843f;
		}
		tmp = VGet(EasingLinear(par, _eData.start.x, _eData.end.x, 1.0f), EasingLinear(par, _eData.start.y, _eData.end.y, 1.0f), EasingLinear(par, _eData.start.z, _eData.end.z, 1.0f));
			break;
		}
	default:
		break;
	}
	_Owner->SetPosition(tmp);
	if (_eData.cnt >= _eData.frame) {
		delete this;
	}
	_eData.cnt++;

}
