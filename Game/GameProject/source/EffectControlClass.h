#pragma once
#include "ActorClass.h"
#include "EffectClass.h"
#include "vector"
#include "deque"

void MyLoadGraph(std::vector<int> &cg, const TCHAR *file, VECTOR size = VGet(1000,1000,0));

class EffectControlClass : public ActorClass
{
public :
	EffectControlClass(class SceneBase* scene);
	virtual ~EffectControlClass();
	EffectClass* AddEffect(VECTOR pos, int type);
	void Init();
	void AddScreenEffect(VECTOR pos, int type);
	std::deque<EffectClass*>* GetEffectList() { return &_Effects; }
	void RemoveEffects(EffectClass* itr);
	void ResetMotEffect(int No);

private :
	std::vector<int> HitEffect;
	std::vector<int> JumpEffect;
	std::vector<int> LandEffect;
	std::deque<EffectClass*> _Effects;
	int PointLight;
	std::vector<int> Start[3];
	std::vector<int> End[3];
	std::vector<int> Round[3];
	std::vector<int> Draw[3];
	std::vector<int> RoundGet[6];
	std::vector<int> Fade;
	std::vector<int> NotesStep_S[5];
	std::vector<int> NotesStep_F[5];
	std::vector<int> Attack2[5];
	std::vector<int> Attack1[2][2][4];
	std::vector<int> Speaker[2];
	std::vector<int> Wave;
	std::vector<int> Light;
	std::vector<int> ConceL;
	std::vector<int> WhiteFlash;
	std::vector<int> Fire[4];
	std::vector<int> Circle;
};

