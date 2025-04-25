#pragma once
#include "Component.h"

class PlayerComponentBase : public Component
{
public:
	PlayerComponentBase(class PlayerClass* owner, int updateOrder = 100);
	virtual ~PlayerComponentBase();

protected:
	class PlayerClass* _Player;
};

