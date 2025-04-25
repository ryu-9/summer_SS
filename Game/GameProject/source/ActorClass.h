#pragma once
#include <vector>
#include "DxLib.h"

class ActorClass
{
public:
	enum State
	{
		ePreparation,
		eActive,
		ePaused,
		eEnd,
		eDead
	};
	ActorClass();
	ActorClass(class SceneBase* scene);
	virtual ~ActorClass();

	void ProcessInput();
	virtual void ActorInput() {};

	void Update();
	void UpdateComponents();
	virtual void UpdateActor();



	// get/set
	VECTOR GetPosition() const { return _Position; }
	void SetPosition(const VECTOR pos) { _Position = pos; }

	VECTOR GetMove() const { return _Move; }

	State GetState() const { return _State; }
	void SetState(const State state) { _State = state; }

	class SceneBase* GetScene();// const { return _Scene; }

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	void SetMove(VECTOR move);
	bool GetStandFlag();


protected:
	VECTOR _Position;
	VECTOR _Move;
	bool _Stand;


private:
	
	std::vector<class Component*> _Components;
	class SceneBase* _Scene;

	State _State;
};

