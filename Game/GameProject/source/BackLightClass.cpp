#include "BackLightClass.h"
#include "SceneBase.h"
#include "Main.h"
#include "MainSpriteComponent.h"


BackLightClass::BackLightClass(class SceneBase* scene, bool playerNo)
	:ActorClass(scene)
	, _No(playerNo)
{
	SetPosition(VGet(0, GROUND_HEIGHT-185, 0));
	sp =new BackLightSpriteComponent(this, _No);
	cg = LoadGraph("res/stage/light_land.png");
	light = new LightingComponent(this, VGet(10000, 10000, 0), cg);
	light->SetColor(GetScene()->GetPlayer(_No)->GetMyColor());

}

BackLightClass::~BackLightClass()
{
	DeleteGraph(cg);
}

void BackLightClass::UpdateActor()
{
	light->SetFlag(FALSE);
	int x = -1000;
	if (_No == TRUE) { x = 1000; }
	SetPosition(VAdd(VGet(x, GetPosition().y, 0), VGet(-GetScene()->GetCamera()->GetPosition().x, 0, -800)));
}
