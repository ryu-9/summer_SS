#include "BackLightSpriteComponent.h"
#include "ActorClass.h"
#include "SceneBase.h"
#include "Main.h"
#include "SceneMain.h"
#include "BackLightClass.h"

BackLightSpriteComponent::BackLightSpriteComponent(ActorClass* _Owner, bool playerNo)
	:SpriteComponent(_Owner,95)
	,_No(playerNo)
	,_Cnt(0)
{
	_Cg = LoadGraph("res/stage/Back_light_0.png");
}

BackLightSpriteComponent::~BackLightSpriteComponent()
{
	DeleteGraph(_Cg);
}

void BackLightSpriteComponent::Draw()
{
	auto owner = dynamic_cast<BackLightClass*>(_Owner);
	owner->GetLight()->SetFlag(FALSE);
	if (_Owner->GetScene()->GetPlayer(1-_No)->GetDamage() > 0
		) {
		if (_Owner->GetScene()->GetPlayer(_No)->GetNotesType() != -1) {
		_Cnt = 255;
		auto scene = dynamic_cast<SceneMain*>(_Owner->GetScene());
		scene->GetRhythm()->SucFrontNote(_No);
		sndManager.GetSound("backlight")->Play();
			_Owner->GetScene()->GetPlayer(_No)->SetVolume(20);
			if (_Owner->GetScene()->GetPlayer(_No)->GetDamage() > 0) {
				_Owner->GetScene()->GetFPSCon()->StartSession();
				if (_Owner->GetScene()->GetFPSCon()->GetSession() <= 0) {
					sndManager.GetSound("session")->Play();
				}
			}
		}
		//_Owner->GetScene()->ChangeTension(5 * (_No * 2 - 1));
	}
	if (_Cnt <= 0) { return; }
	owner->GetLight()->SetFlag(TRUE);
	if (_Owner->GetScene()->GetFPSCon()->GetSession() > 0 && _Owner->GetScene()->GetFPSCon()->GetInputUDFlag() == TRUE) { _Cnt -= 5; }
	if (_Owner->GetScene()->GetFPSCon()->GetUpdateFlag() == TRUE) { _Cnt -= 50; }
	VECTOR vert[4];
	VECTOR pos = _Owner->GetPosition();
	VECTOR playerPos = _Owner->GetScene()->GetPlayer(_No)->GetHitPosition();
	if (_Owner->GetScene()->GetFPSCon()->GetSession() > 0) { playerPos = _Owner->GetScene()->GetPlayer(_No)->GetPosition(); }
	VECTOR playerSize = VGet(_Owner->GetScene()->GetPlayer(_No)->GetHitFrame().w, _Owner->GetScene()->GetPlayer(_No)->GetHitFrame().h, 0);
	MATRIX cam = _Owner->GetScene()->GetCamera()->GetView();
	pos = VTransform(pos, cam);
	pos = VAdd(pos, DrawCenter);
	vert[0] = VGet(playerSize.x / 2, 0, 0);
	vert[1] = VGet(playerSize.x / 2, -playerSize.y, 0);
	vert[2] = VGet(-playerSize.x / 2, -playerSize.y, 0);
	vert[3] = VGet(-playerSize.x / 2, 0, 0);
	for (int i = 0; i < 4; i++) {
		vert[i] = VScale(vert[i], 2);
		vert[i] = VAdd(playerPos, vert[i]);
		vert[i] = VTransform(vert[i], cam);
		vert[i] = VAdd(vert[i], DrawCenter);
	}
	SetDrawBlendMode(DX_BLENDMODE_ADD, _Cnt);
	int r, g, b;
	GetColor2(_Owner->GetScene()->GetPlayer(_No)->GetMyColor(), &r, &g, &b);
	SetDrawBright(r, g, b);
	DrawModiGraph((int)vert[1].x, (int)vert[1].y, (int)vert[0].x, (int)vert[0].y, (int)pos.x, (int)pos.y, (int)pos.x, (int)pos.y, _Cg, TRUE);
	DrawModiGraph((int)vert[2].x, (int)vert[2].y, (int)vert[1].x, (int)vert[1].y, (int)pos.x, (int)pos.y, (int)pos.x, (int)pos.y, _Cg, TRUE);
	DrawModiGraph((int)vert[3].x, (int)vert[3].y, (int)vert[2].x, (int)vert[2].y, (int)pos.x, (int)pos.y, (int)pos.x, (int)pos.y, _Cg, TRUE);
	SetDrawBright(255,255,255);


	SetDrawBlendMode(DX_BLENDMODE_MULA, _Cnt);
	MyDrawMain(VAdd(playerPos, VGet(0, -playerSize.y / 2, 0)), playerSize, _Owner->GetScene()->GetPlayer(_No)->GetHitFrame().cg, cam, _Owner->GetScene()->GetPlayer(_No)->GetHitFrame().rev);
	//MyDrawMain(VAdd(_Owner->GetScene()->GetPlayer(1 - _No)->GetDrawPosition(), VGet(0, -_Owner->GetScene()->GetPlayer(1 - _No)->GetFrame().h / 2, 0)),
	//	VGet(_Owner->GetScene()->GetPlayer(1 - _No)->GetFrame().w, _Owner->GetScene()->GetPlayer(1 - _No)->GetFrame().h,0), _Owner->GetScene()->GetPlayer(1 - _No)->GetHitFrame().cg, cam);
	SetDrawBlendMode(DX_BLENDMODE_SUB1, _Cnt/2);
	MyDrawMain(VAdd(playerPos, VGet(0, -playerSize.y / 2, 0)), playerSize, _Owner->GetScene()->GetPlayer(_No)->GetHitFrame().cg, cam, _Owner->GetScene()->GetPlayer(_No)->GetHitFrame().rev);
	//MyDrawMain(VAdd(_Owner->GetScene()->GetPlayer(1 - _No)->GetDrawPosition(), VGet(0, -_Owner->GetScene()->GetPlayer(1 - _No)->GetFrame().h / 2, 0)),
	//	VGet(_Owner->GetScene()->GetPlayer(1 - _No)->GetFrame().w, _Owner->GetScene()->GetPlayer(1 - _No)->GetFrame().h, 0), _Owner->GetScene()->GetPlayer(1 - _No)->GetHitFrame().cg, cam);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
