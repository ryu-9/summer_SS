#pragma once
#include "SynopsisComponent.h"
#include "SpriteComponent.h"
#include "Dxlib.h"

class SynopsisSpriteComponent : public SpriteComponent {
public:
	SynopsisSpriteComponent(class ActorClass* owner, class SynopsisComponent* s_owner, int drawOrder = 100);

	void Draw() override;

private:
	class SynopsisComponent* _S_Owner;


};

