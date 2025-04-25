#include "StageLightSpriteComponent.h"

StageLightSpriteComponent::StageLightSpriteComponent(ActorClass* _Owner, int* color)
	:SpriteComponent(_Owner)
	,_Color(color)
{

}

StageLightSpriteComponent::~StageLightSpriteComponent()
{
}

void StageLightSpriteComponent::Draw()
{
}
