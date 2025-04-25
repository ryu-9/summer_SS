#pragma once

class Component
{
public:
	Component(class ActorClass* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update();
	virtual void ProcessInput() {}

	// Getter
	int GetUpdateOrder() const { return _UpdateOrder; }

protected:
	class ActorClass* _Owner;
	// 処理順決定用 デフォルトは100
	int _UpdateOrder;
};
