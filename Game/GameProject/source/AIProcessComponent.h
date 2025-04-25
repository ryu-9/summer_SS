#pragma once
#include "AIStruct.h"
#include "AIControlClass.h"
#include "PlayerClass.h"
#include "Component.h"
#include <vector>
#include <map>
#include <string>
#include <queue>

class AIProcessComponent : public Component
{
public:
	AIProcessComponent(class ActorClass* owner, int updateOrder = 10);
	~AIProcessComponent();

	void Init();
	void ProcessInput() override;
	void Inference();
	void GetSituation();

	
private:
	enum STATE {
		NOMAL,
		OFFENSIVE,
		STATE_MAX
	};
	enum  ACTION {
		NON,
		Waiting,
		Avoid,
		Attack,
		ATTACK1,
		ATTACK2,
		GRAB,
		RISE
	};

	void DecAction();
	void InputKeyData();


	void ResetInputKey();
	void ResetAction();

	int InfMotion();

	int ModiPLArrow();


	STATE _State;
	int _Action;				// �A�N�V����
	int _ActType;				// �A�N�V�������̃^�C�v
	int _ActProgress;			// �A�N�V�����i�s�x
	int _Cnt;

	PlayerClass* _CPUPlayer;
	PlayerClass* _Enemy;
	RhythmControlClass* _Rhythm;

	float _Frame;



	std::vector<std::vector<float>> _ActWeight;		// �A�N�V�����̏d��
	std::queue<AIINPUT> _InputKey;					// ���͑҂��L�[

	std::vector<std::map<std::string, int>> _InfS;
	std::vector<std::map<std::string,int>> _Situation;


	// ���[�V����
	std::map<int, uint_fast8_t> _MotionDatafl;


	std::vector<std::vector<float>> _Weight;
	std::vector<float> _WeightRatio;
};

