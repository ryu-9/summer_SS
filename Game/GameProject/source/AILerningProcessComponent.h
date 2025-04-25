#pragma once
#include "AIProcessComponentBase.h"
// #include "AILerningJudgementBase.h"
#include <vector>



class AILerningProcessComponent : public AIProcessComponentBase
{
public:
	AILerningProcessComponent(class ActorClass* owner, int updateOrder = 10);

	void Update() override;
	void GetSituation() override;

private:
	void RunJudge() override;
	void CreateInputKey() override;
	struct PARAMETER {
		VECTOR distance;
		int hp[2];
		float firstNote;
		int tention;
	};
	enum ACTION {
		NON,
		WAITING,
		ATTACK,
		RUNOUT,
		DAMAGE,
	};
	enum STATE {
		NOMAL,
		OFFENSIVE,
		STATE_MAX
	};
	int _Motion;

	STATE _State;
	ACTION _Action;
	PARAMETER _CurrentSituation;
//	std::vector<std::vector<AIRuleJudgementBase*>> _Judgement;
//	std::vector<AIRuleJudgementBase*> _StateJudgement;
};

