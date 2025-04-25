#include "SynopsisClass.h"
#include "SynopsisComponent.h"
#include "SynopsisSpriteComponent.h"

SynopsisClass::SynopsisClass(SceneBase* scene)
	:ActorClass(scene)
{
	auto sc = new SynopsisComponent(this);
	new SynopsisSpriteComponent(this, sc);
}

void SynopsisClass::UpdateActor() {
	
}
