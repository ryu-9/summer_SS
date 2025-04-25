#include "UIScaleComponent.h"
#include "mymath.h"
#include "ActorClass.h"

UIScaleComponent::UIScaleComponent(UIChipClass* owner, VECTOR start, VECTOR end, int frame, int entype, int easetype, int updateOrder)
	:UIActionComponentBase(owner,start,end,frame,entype,easetype,updateOrder)
{
}

void UIScaleComponent::ProcessInput() {
	// SE“™
}

void UIScaleComponent::Update() {
	if (_Owner->GetState() == ActorClass::ePreparation) {

	}
	else {

		// Ä¶ˆÊ’u‚Å‚¢[‚¶‚ñ‚®‚É‚·‚é
		auto tmp = (cos((_eData.cnt % 360) * PI / 180.0f) + 1);
		auto sc = VGet(0, 0, 0);
		sc.x = EasingInOutQuad(tmp, _eData.start.x, _eData.end.x, 2);
		sc.y = EasingInOutQuad(tmp, _eData.start.y, _eData.end.y, 2);
		_UIc->SetScale(sc);
		_eData.cnt += 7;
	
	}
}
