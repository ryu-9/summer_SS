#pragma once
#include "Component.h"
#include "DxLib.h"
#include <vector>

class AudienceComponent : public Component {
public:
	AudienceComponent(class ActorClass* owner, int updateOrder = 120);
	virtual ~AudienceComponent();
	void ProcessInput() override;
	void Update() override;

private:
	void InitSE();

	std::vector<int> _ClapSEHandle;
	std::vector<VECTOR> _ClapSEPos;
	VECTOR _ListenerPos;
	float _Angle;
	class RhythmControlClass* _RhythmCon;
	int _DistMax;
};

