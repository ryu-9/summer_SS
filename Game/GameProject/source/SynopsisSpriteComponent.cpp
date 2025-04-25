#include "SynopsisSpriteComponent.h"

SynopsisSpriteComponent::SynopsisSpriteComponent(ActorClass* owner, SynopsisComponent* s_owner, int drawOrder)
	:SpriteComponent(owner)
	,_S_Owner(s_owner)
{
	ChangeFont("DFHSMinchoS JP13N W3");
}

void SynopsisSpriteComponent::Draw() {
	for (auto iter : _S_Owner->GetTextData()) {
		DrawFormatString(iter.pos.x, 1080+iter.pos.y, GetColor(255, 255, 255), "%s", iter.text.c_str());
	}
}
