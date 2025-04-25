#include "UICursorComponent.h"
#include "mymath.h"


UICursorComponent::UICursorComponent(UIChipClass* owner, VECTOR start, VECTOR end, int frame, int entype, int easetype, int updateOrder)
	:UIActionComponentBase(owner, start, end, frame, entype, easetype, updateOrder)
{
}

UICursorComponent::~UICursorComponent()
{
}

void UICursorComponent::Update()
{
	
	auto tmp = VGet(cos((_eData.cnt % 360) * PI / 180.0f),0.4* (sin((_eData.cnt % 360) * PI / 180.0f)+1), 0);
	_UIc->SetScale(tmp);
	_eData.cnt+=15;
	if (_eData.cnt > 360) {
		_UIc->SetType(1);
		_UIc->SetScale(VGet(1,1,1));
		delete this;
	}
}
