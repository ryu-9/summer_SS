#include "FlameClass.h"
#include "SceneBase.h"
#include "SceneMain.h"
#include "MainSpriteComponent.h"

FlameClass::FlameClass(SceneBase* scene, ActorClass* owner, std::vector<int>* cg, int cnt)
	:ActorClass(scene)
	,_Count(cnt)
	,_Root(owner)
	,_CntMax(cnt+1)
{
	//int cg = LoadGraph("res/stage/HitFlash.png");
	_FlashCg.resize(cg->size());
	std::copy(cg->begin(), cg->end(), _FlashCg.begin());
	light = new LightingComponent(this, VGet(8000, 8000, 0), _FlashCg[0], -1, VGet(0, 500, 0));
	SetPosition(_Root->GetPosition());
	_Start = GetNowCount();
	_Time = _Count * GetScene()->GetFPSCon()->GetDeltaTime()/2;
	//sp = new MainSpriteComponent(this, VGet(3000, 3000, 0), "res//sample/HitFlash.png");
	_Color = GetColor(255, 255, 255);
	if (scene->GetTension() == 100) {
		_Color = scene->GetPlayer(1)->GetMyColor();
	}
	else {
		_Color = scene->GetPlayer(0)->GetMyColor();
	}
	//light->SetColor(_Color);
	//light->SetValue(255);
}

FlameClass::~FlameClass()
{

}

void FlameClass::UpdateActor()
{

	if (_Count <= 0) {
		//Init(15);
		light->SetFlag(FALSE);
		return;
	}



	int tmp = effects.size();
	for (int i = 0, j = 0; i + j < tmp; i++) {
		if (effects[i]->GetDelFlag() != FALSE) {
			effects.erase(effects.begin() + i);
			j++;
			i--;
		}
	}
	tmp = effects.size();
	for (int i = 0, j = 0; i + j < tmp; i++) {
		if (effects[i]->GetDelFlag() == 221) {
			effects.erase(effects.begin() + i);
			j++;
			i--;
		}
	}
	int type = 101;
	auto scene = dynamic_cast<SceneMain*>(GetScene());
	VECTOR pos = GetPosition();
	if (_Root->GetPosition().x != pos.x) {
		VECTOR move = VGet(_Root->GetPosition().x - pos.x, 0, _Root->GetPosition().z - pos.z);

		for (int i = 0, j=0; i+j < effects.size();i++) {

				effects[i]->SetPosition(VAdd(effects[i]->GetPosition(), move));

		}
		SetPosition(VAdd(pos, move));
	}

	pos = GetPosition();
	if (pos.z > 0) {
		type = 111;
	}
	int now = GetNowCount();
	int count = _CntMax - (float)(now - _Start) / _Time * _CntMax;



	if (_Count != count) {

		light->SetImage(_FlashCg[rand() % 2]);
		light->SetReverse(rand() % 2);

		if (_Count > _CntMax - 4) {
			SetPosition(VAdd(pos, VGet(0, -300, 0)));
			for (int i = 0; i < (_CntMax - _Count) ; i++) {
				int y = rand() % ((_CntMax - _Count) * 3);
				int x = rand() % ((_CntMax - _Count) * 3 - y);
				pos = VAdd(_Root->GetPosition(), VGet(((_CntMax - _Count) * 5 - y) * 5 - x * 20, -y * 80, 0));
				//scene->GetEffectCon()->AddEffect(pos, type + rand() % 8);
				effects.emplace_back(scene->GetEffectCon()->AddEffect(pos, type + rand() % 8));
				effects[effects.size() - 1]->GetSprite()->SetColor(_Color);
			}
		}

		else if (_Count >= 7) {
			SetPosition(VAdd(pos, VGet(0, -40, 0)));
			for (int i = 0; i < (_CntMax - _Count); i++) {
				if (i <= 3) {
					int y = rand() % (_Count / 7 * 5);
					int x = rand() % (_Count / 7 * 5 - y);
					pos = VAdd(_Root->GetPosition(), VGet((_Count / 7 * 5 - y) * 5 - x * 20, -y * 80, 0));
				}
				else if (i < 50) {
					int dist = rand() % (_CntMax - _Count) * 2;
					int x = rand() % (dist + 1);
					int y = dist - x;
					int xR = rand() % 2 * 2 - 1, yR = rand() % 2 * 2 - 1;
					pos = VAdd(GetPosition(), VGet(x * 16 * xR, y *12 * yR, 0));
				}
				else {
					int dist = rand() % (_CntMax - _Count) * 2;
					int x, y;
					if (dist <= _CntMax - _Count) {
						x = rand() % (dist + 1);
						y = dist - x;
					}
					else {
						x = rand() % ((_CntMax - _Count) * 2 - dist);
						x += dist - (_CntMax - _Count);
						y = dist - x;
					}
					int xR = rand() % 2 * 2 - 1, yR = rand() % 2 * 2 - 1;
					pos = VAdd(GetPosition(), VGet(x * 20 * xR, y * 16 * yR, 0));
				}

				//scene->GetEffectCon()->AddEffect(pos, type + rand() % 8);
				effects.emplace_back(scene->GetEffectCon()->AddEffect(pos, type + rand() % 8));
				effects[effects.size() - 1]->GetSprite()->SetColor(_Color);
			}
		}

		else {
			int dist = rand() % _Count * 5;
			int x = rand() % (dist + 1);
			int y = dist - x;
			int xR = rand() % 2 * 2 - 1, yR = rand() % 2 * 2 - 1;
			pos = VAdd(GetPosition(), VGet(x * 8 * xR, y * 6 * yR, 0));
			//scene->GetEffectCon()->AddEffect(pos, type + rand() % 8);
			effects.emplace_back(scene->GetEffectCon()->AddEffect(pos, type + rand() % 8));
			effects[effects.size() - 1]->GetSprite()->SetColor(_Color);
		}
		_Count = count;
	}



	if (scene->GetFPSCon()->GetUpdateFlag() == TRUE) { 

	}

}

void FlameClass::Init(int cnt)
{
	_Count = cnt;
	_CntMax = cnt + 1;
	SetPosition(_Root->GetPosition());
	SetPosition(VAdd(GetPosition(), VGet(0, 0, -2 * GetPosition().z)));
	_Time = _Count * GetScene()->GetFPSCon()->GetDeltaTime() / 2;
	light->SetFlag(TRUE);
	_Start = GetNowCount();
	if (GetScene()->GetTension() == 100) {
		_Color = GetScene()->GetPlayer(1)->GetMyColor();
	}
	else {
		_Color = GetScene()->GetPlayer(0)->GetMyColor();
	}

	int tmp = effects.size();
	for (int i = 0; i < tmp; i++) {
		effects.erase(effects.begin());
	}

	light->SetColor(_Color);
	effects.resize(0);
}
