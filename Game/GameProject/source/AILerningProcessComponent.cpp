#include "AILerningProcessComponent.h"
#include "MotionComponent.h"


AILerningProcessComponent::AILerningProcessComponent(ActorClass* owner, int updateOrder)
	:AIProcessComponentBase(owner,updateOrder)
	,_State(NOMAL)
	,_Action(NON)
{
	// �����Ń��[�h

}

void AILerningProcessComponent::Update() {

}

void AILerningProcessComponent::GetSituation() {
	// �����_���Ŏ擾�ł��Ȃ�����
	_CurrentSituation.distance = VSub(_CPUPlayer->GetPosition(), _Enemy->GetPosition());
	_CurrentSituation.hp[0] = _CPUPlayer->GetHitPoint();
	_CurrentSituation.hp[1] = _Enemy->GetHitPoint();
//	_CurrentSituation.firstNote = 
	_CurrentSituation.tention = _Owner->GetScene()->GetTension();
}

void AILerningProcessComponent::RunJudge() {
	GetSituation();
	if (_Enemy->GetMotionID() == MotionComponent::MOT_L_STAND || _Enemy->GetMotionID() == MotionComponent::MOT_R_STAND) {

	}
	else {
		if (rand() % 100 <= 50) {
			_Motion = _Enemy->GetMotionID();
		}
	}

}

void AILerningProcessComponent::CreateInputKey() {
	auto createKey = 0;
	switch (_Action)
	{
	case NON:
		_InputQueue.push({ 0,0,0 });
		break;
	case WAITING:

		break;
	case ATTACK:
		break;
	case RUNOUT:
		break;
	default:
		break;
	}
}

