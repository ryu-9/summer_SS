#pragma once
#include "ActorClass.h"
#include "AIProcessComponent.h"
class AIProcessComponent;

class AIControlClass :public ActorClass {
public:
	AIControlClass(class SceneBase* scene);
	void UpdateActor() override;
	void Init();
	void SetAI();
//	void SetPlayer(class PlayerClass* pl, class PlayerClass* en);

private:
	AIProcessComponent* _AIProcessInput;

};