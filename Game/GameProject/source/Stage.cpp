#include "Stage.h"
#include "SceneBase.h"
#include "SceneMain.h"
#include "MainSpriteComponent.h"
#include "Main.h"
#include "PsylliumControlClass.h"
#include "LightingComponent.h"
#include "FlameClass.h"


StageBase::StageBase(class SceneBase* scene, VECTOR pos, VECTOR size, const TCHAR* cgfile, int CgNum, int DrawOrder,float rotate, int loop, int BlendMode, int value)
	:ActorClass(scene)
	,_Size(size)
	,_Rotate(0)
	,_LoopRot(loop)
	, _InitX(pos.x)
	, _InitY(pos.y)
{
	_Rotate = rotate / 180 *4 * atan(1);
	SetPosition(pos);
	sp = new MainSpriteComponent(this,size, cgfile,DrawOrder, BlendMode, value);
	_Cg.resize(CgNum);
	int XNum;
	int XSize, YSize;
	//âÊëúÇÃì«Ç›çûÇ›
	GetImageSize_File(cgfile, &XSize, &YSize);
	for (int i = 1; i <= CgNum; i++) {
		if (CgNum==1) {
			_Cg[0] = LoadGraph(cgfile);
			break;
		}
		if (CgNum % i == 0) { XNum = CgNum / i; }
		else { XNum = CgNum / i+1; }
		if ((int)size.x * YSize / i != XSize / XNum * (int)size.y ) {
			continue;
		}
		if (LoadDivGraph(cgfile, CgNum, XNum, i, XSize/XNum, YSize/i, &_Cg[0]) != -1) {
			break;
		}
	}

	sp->ChangeImage(_Cg[0]);


}

StageBase::~StageBase()
{
	for (auto cg : _Cg) {
		DeleteGraph(cg);
	}
}

void StageBase::UpdateActor()
{
	float rotate = (-GetScene()->GetCamera()->GetPosition().x / 6000 * 4 * atan(1) +_Rotate+1);
	SetPosition(VAdd(VGet(_InitX*cos(rotate), _InitY, 0), VGet(-GetScene()->GetCamera()->GetPosition().x, 0, 0)));		//âÒì]ÇµÇΩç¿ïWÇ÷à⁄ìÆ
	int tmp = (int)(_Cg.size() * GetScene()->GetCamera()->GetPosition().x / -6000 * 360 / _LoopRot) % _Cg.size();		//âÒì]ÇµÇΩâÊëúÇ÷ïœçX
	if (-GetScene()->GetCamera()->GetPosition().x > 0) { tmp = _Cg.size() - tmp-1; }
	sp->ChangeImage(_Cg[tmp]);
	auto scene = dynamic_cast<SceneMain*>(GetScene());
	sp->SetColor(scene->GetMyColor());
}

VECTOR StageBase::GetViewPos()
{
	return VAdd(VTransform(GetPosition(), GetScene()->GetCamera()->GetView()), DrawCenter);
}

StageBack::StageBack(class SceneBase* scene, VECTOR pos, VECTOR size, const TCHAR* cgfile, float z, int DrawOrder, int BlendMode, int value)
	:StageBase( scene,  pos,  size, cgfile, 1, DrawOrder, BlendMode,value)
	,_Zdist(z)
{
}

StageBack::~StageBack()
{
}

void StageBack::UpdateActor()
{
	SetPosition(VAdd(VGet(GetInitX(), GetPosition().y, 0), VGet(2 * _Zdist*GetScene()->GetCamera()->GetPosition().x, 0, 0)));
	auto scene = dynamic_cast<SceneMain*>(GetScene());
	sp->SetColor(scene->GetMyColor());
}


StageLight::StageLight(SceneBase* scene, VECTOR pos, VECTOR size, const TCHAR* cgfile, int CgNum, int DrawOrder, int Rotate)
	:StageBase(scene,pos,size,cgfile,CgNum ,DrawOrder,Rotate)
	,_Size(size)
{
	_No = FALSE;
	if (GetInitX() > 0) {
		_No = TRUE; 
	}
	_Cg.resize(2);
	_Cg[0] = LoadGraph("res/stage/light0.png");
	_Cg[1] = LoadGraph("res/stage/light1.png");
	GetColor2(GetScene()->GetPlayer(0)->GetMyColor(), &_Color[0][0], &_Color[0][1], &_Color[0][2]);
	GetColor2(GetScene()->GetPlayer(1)->GetMyColor(), &_Color[1][0], &_Color[1][1], &_Color[1][2]);
	light = new LightingComponent(this, size, _Cg[1], -1, VGet(0, -size.y / 2, 0));
	land = new MainSpriteComponent(this, VGet(1000, 1000, 0), "res/stage/light_land.png", 93, DX_BLENDMODE_ADD, 75, 0, FALSE, TRUE);
	shadow[0] = new MainSpriteComponent(this, VGet(1000, 1000, 0), "res/stage/shadow.png", 94, DX_BLENDMODE_MULA, 150, 0, FALSE, TRUE);
	shadow[1] = new MainSpriteComponent(this, VGet(1000, 1000, 0), "res/stage/shadow.png", 94, DX_BLENDMODE_MULA, 150, 0, FALSE, TRUE);


	auto scenemain = dynamic_cast<SceneMain*>(GetScene());
	land->SetMask(scenemain->GetStage()->sp);
	shadow[0]->SetMask(land);
	shadow[1]->SetMask(land);
}

StageLight::~StageLight()
{
}

void StageLight::UpdateActor()
{
	StageBase::UpdateActor();
	

	float rotate = (-GetScene()->GetCamera()->GetPosition().x / 3000 * 4 * atan(1) + GetRotate());
	SetPosition(VAdd(VGet(0, 0, -GetInitX()*sin(rotate)), GetPosition()));



	VECTOR v[4];
	rotate = (-GetScene()->GetCamera()->GetPosition().x / 3000 + GetRotate() / 180) * 4 * atan(1);
	float X = (_No * 2 - 1) * 3280 / 2 * cos(rotate);
	v[0] = VScale(_Size, -0.5f);
	v[1] = VGet(_Size.x / 2, -_Size.y / 2, 0);
	v[2] = VSub(GetScene()->GetPlayer(_No)->GetPosition(), VAdd(GetPosition(), VGet(v[0].x,500,0)));
	VECTOR add = VScale(VAdd(v[0], v[1]), 0.5);
	v[2] = VSub(v[2], add);
	v[2] = VAdd(add, VScale(v[2], ((GROUND_HEIGHT + 500) - add.y) / v[2].y));
	v[3] = VSub(GetScene()->GetPlayer(_No)->GetPosition(), VAdd(GetPosition(), VGet(v[1].x,500,0)));
	v[3] = VSub(v[3], add);
	v[3] = VAdd(add, VScale(v[3], ((GROUND_HEIGHT + 500) - add.y) / v[3].y));
	v[0] = VAdd(v[0], VGet(0, GetInitX() * sin(rotate) / 9, 0));
	v[1] = VAdd(v[1], VGet(0, GetInitX() * sin(rotate) / 9, 0));
	sp->SetVert(v[0], v[1], v[2], v[3]);
	light->SetVert(v[0], v[1], v[2], v[3]);

	land->SetValue(75 * 2800 / (v[2].x - v[3].x) );

	v[2] = VAdd(v[2], VGet(0, -50, 0));
	v[3] = VAdd(v[3], VGet(0, -50, 0));
	v[0] = VAdd(VScale(VAdd(v[2], v[3]), 0.5), VGet(0, VSub(v[2], v[3]).x / 35, 0));
	v[1] = VAdd(VScale(VAdd(v[2], v[3]), 0.5), VGet(0, VSub(v[3], v[2]).x / 35, 0));


	land->SetVert(v[2], v[1], v[3], v[0]);

	VECTOR dir = VSub(GetScene()->GetPlayer(_No)->GetPosition(), VGet(GetPosition().x, _InitY, GetPosition().z));


	float height = dir.y+1580;
	dir = VGet(dir.x, height, dir.z);
	dir = VNorm(dir);
	int size = 3160 * 750 / height;
	v[0] = VGet(-450, 0, 0);
	v[1] = VAdd(v[0], VGet(size,-size, 0));
	v[2] = VAdd(v[0], VGet(2*size, 0, 0));
	v[3] = VAdd(v[0], VGet(size, size, 0));
	MATRIX rot = MGetRotZ(rotate);
	for (auto& vert : v) {
		vert = VTransform(vert, rot);
		vert = VGet(vert.x, vert.y / 8, 0);
		vert = VAdd(vert, VGet(GetScene()->GetPlayer(_No)->GetPosition().x,GROUND_HEIGHT-125,0));
		vert = VSub(vert, GetPosition());
		vert = VAdd(vert, VGet(6000 * (3160 - height) / 3160*dir.x, 6000 * (3160 - height) / 3160 / 35*dir.z, 0));
	}
	shadow[0]->SetVert(v[0], v[1], v[2], v[3]);
	shadow[0]->SetValue(150 * height / 3160);


	dir = VSub(GetScene()->GetPlayer(1-_No)->GetPosition(), VGet(GetPosition().x, _InitY, GetPosition().z));


	height = dir.y + 1580;
	dir = VGet(dir.x, height, dir.z);
	dir = VNorm(dir);
	size = 3160 * 750 / height;
	v[0] = VGet(-450, 0, 0);
	v[1] = VAdd(v[0], VGet(size, -size, 0));
	v[2] = VAdd(v[0], VGet(2 * size, 0, 0));
	v[3] = VAdd(v[0], VGet(size, size, 0));
	rot = MGetRotZ(rotate);
	for (auto& vert : v) {
		vert = VTransform(vert, rot);
		vert = VGet(vert.x, vert.y / 8, 0);
		vert = VAdd(vert, VGet(GetScene()->GetPlayer(1-_No)->GetPosition().x, GROUND_HEIGHT - 125, 0));
		vert = VSub(vert, GetPosition());
		vert = VAdd(vert, VGet(6000 * (3160 - height) / 3160 * dir.x, 6000 * (3160 - height) / 3160 / 35 * dir.z, 0));
	}
	shadow[1]->SetVert(v[0], v[1], v[2], v[3]);
	shadow[1]->SetValue(150 * height / 3160);



	int tmpTension = GetScene()->GetTension();
	auto scene = dynamic_cast<SceneMain*>(GetScene());
	if (scene->GetBackLight(0)->GetSprite()->GetCount()>0|| scene->GetBackLight(1)->GetSprite()->GetCount() > 0)
	{
		sp->ChangeImage(-1);
		light->SetFlag(FALSE);
		//light->SetImage(-1);
		return;
	}
	light->SetFlag(TRUE);
	sp->ChangeImage(_Cg[0]);
	light->SetImage(_Cg[1]);
	if (tmpTension <= 0) {
		sp->SetColor(GetColor(_Color[0][0], _Color[0][1], _Color[0][2]));
		light->SetColor(GetColor(_Color[0][0], _Color[0][1], _Color[0][2]));
		land->SetColor(GetColor(_Color[0][0], _Color[0][1], _Color[0][2]));
		return;
	}
	if (tmpTension >= 100) {
		sp->SetColor(GetColor(_Color[1][0], _Color[1][1], _Color[1][2]));
		light->SetColor(GetColor(_Color[1][0], _Color[1][1], _Color[1][2]));
		land->SetColor(GetColor(_Color[1][0], _Color[1][1], _Color[1][2]));
		return;
	}
	int r, g, b;
	tmpTension = (1-_No) * 100 - tmpTension;
	if (tmpTension < 0) { tmpTension *= -1; }
	r = _Color[_No][0] * tmpTension / 100 + 255 * (100 - tmpTension) / 100;
	g = _Color[_No][1] * tmpTension / 100 + 255 * (100 - tmpTension) / 100;
	b = _Color[_No][2] * tmpTension / 100 + 255 * (100 - tmpTension) / 100;

	sp->SetColor(GetColor(r, g, b));
	land->SetColor(GetColor(r, g, b));
	light->SetColor(GetColor(r, g, b));

	return;

}

StageFire::StageFire(SceneBase* scene, VECTOR pos, int Rotate)
	:StageBase(scene, pos, VGet(0,0,0), "noimage", 1, 0, Rotate)
{
	//delete sp;
	_OldTension = GetScene()->GetTension();
	_FlashCg.resize(2);
	LoadDivGraph("res/effects/FireFlash.png", 2, 2, 1, 1000, 1000, &_FlashCg[0]);
	fire = new FlameClass(GetScene(), this, &_FlashCg);
}

StageFire::~StageFire()
{
	for (auto cg : _FlashCg) {
		DeleteGraph(cg);
	}
}

void StageFire::UpdateActor()
{
	StageBase::UpdateActor();
	float rotate = (-GetScene()->GetCamera()->GetPosition().x / 6000 * 4 * atan(1) + GetRotate());
	SetPosition(VAdd(VGet(0, 0, -GetInitX() * sin(rotate)), GetPosition()));

	int tension = GetScene()->GetTension();
	if (tension != _OldTension) {
		if (tension == 100 || tension == 0) {
			fire->Init(15);
			auto f = sndManager.GetSound("fire");
			auto tmp = ((((int)_Position.x % 1920) - (1920 / 2.0f)) / 1920 / 2.0f) * 255;
			f->SetPan(tmp);
			sndManager.GetSound("fire")->Play();
		}
	}
	if (gPad._key & PAD_INPUT_DOWN) {
		//fire->Init(25);
	}
	_OldTension = tension;
}
