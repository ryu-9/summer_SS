#include "PlayerComponentBase.h"
#include "PlayerClass.h"
#include "ActorClass.h"

PlayerComponentBase::PlayerComponentBase(class PlayerClass* owner, int updateOrder)
	:Component(owner, updateOrder)
	,_Player(owner)
{

}

PlayerComponentBase::~PlayerComponentBase()
{
}