#include "PlayerSpriteComponent.h"
#include "SceneMain.h"
#include "math.h"
#include "LightingComponent.h"

PlayerSpriteComponent::PlayerSpriteComponent(class PlayerClass* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	,_Player(owner)
{
	_ShadowMask[0] = MakeScreen(1920, 1080, TRUE);
	_ShadowMask[1] = MakeScreen(1920, 1080, TRUE);
}

PlayerSpriteComponent::~PlayerSpriteComponent() 
	
{
	
}

void PlayerSpriteComponent::Draw(){
	int cl;
	switch (_Player->GetNotesType())
	{
	case 0:
		cl = GetColor(255, 255, 255);
		break;
	case 1:
		cl = GetColor(100, 100, 100);
		break;
	case 2:
		cl = GetColor(220, 220, 0);
		break;
	default:
		cl = GetColor(50, 50, 50);
		break;
	}
	//DrawBox(_Owner->GetPosition().x, _Owner->GetPosition().y, _Owner->GetPosition().x + 64, _Owner->GetPosition().y + 64, cl, TRUE);
	MOTION_FRAME tmp;
	VECTOR pos;
	if (_Owner->GetScene()->GetFPSCon()->GetHitStop() > 0) {
		tmp = _Player->GetHitFrame();
		pos = VAdd(_Player->GetHitPosition(), VGet(_Player->GetDrawPosition().x - _Player->GetPosition().x, -tmp.h / 2, 0));
	}
	else {
		tmp = _Player->GetFrame();
		pos = VAdd(_Player->GetDrawPosition(), VGet(0, -tmp.h / 2, 0));
	}

	if (_Player->GetSACnt() > 0) {
		std::deque<VECTOR> pos = *_Player->GetOldPosition();
		std::deque<MOTION_FRAME> frame = *_Player->GetOldFrame();
		int r, g, b;
		GetColor2(_Player->GetMyColor(), &r, &g, &b);
		SetDrawBright(r, g, b);
		for (int i = 0; i < _Player->GetOldPosition()->size(); i++) {
			SetDrawBlendMode(DX_BLENDMODE_ADD, 10+40 * _Player->GetSACnt() / 255 * (FRAME_NUM  - i) / FRAME_NUM );
			MyDrawMain(VAdd(pos[i], VGet(0, -frame[i].h / 2, 0)), VGet(frame[i].w, frame[i].h, 0), frame[i].cg, _Owner->GetScene()->GetCamera()->GetView(), frame[i].rev);
		}
		SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	//DrawExtendGraph(_Owner->GetPosition().x-tmp.w/2, _Owner->GetPosition().y-tmp.h, _Owner->GetPosition().x + tmp.w/2, _Owner->GetPosition().y , tmp.cg, TRUE);


	auto scene = dynamic_cast<SceneMain*>(_Owner->GetScene());
	int r, g, b;
	GetColor2(scene->GetMyColor(), &r, &g, &b);
	SetDrawBright(r, g, b);
	MyDrawMain(pos, VGet(tmp.w, tmp.h, 0), tmp.cg, _Owner->GetScene()->GetCamera()->GetView(), tmp.rev);
	SetDrawBright(255, 255, 255);

	//DrawFormatString(_Owner->GetPosition().x, _Owner->GetPosition().y, GetColor(200, 64, 64), "%d", _Player->GetMotionID());
	SetDrawScreen(_ShadowMask[0]);
	ClearDrawScreen();
	//DrawBox(0, 0, 1920, 1080, GetColor(100, 100, 100), TRUE);
	SetDrawScreen(DX_SCREEN_BACK);

	for (const auto& light : _Player->GetScene()->GetLights()) {
		if (light->GetFlag() != TRUE) { continue; }
		DrawLighting(_Player, light, _Owner->GetScene()->GetScreenMask(), _Owner->GetScene()->GetSubMask(), _ShadowMask[0], _ShadowMask[1]);
	}

	//DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
	//DrawGraph(0, 0, _ShadowMask, TRUE);

	SetMaskScreenGraph(_ShadowMask[0]);
	SetUseMaskScreenFlag(TRUE);
	SetMaskScreenGraphUseChannel(DX_MASKGRAPH_CH_B);
	SetMaskReverseEffectFlag(TRUE);

	SetDrawBlendMode(DX_BLENDMODE_MULA, 155);
	//MyDrawMain(VAdd(_Player->GetDrawPosition(), VGet(0, -_Player->GetFrame().h / 2, 0)), VGet(_Player->GetFrame().w, _Player->GetFrame().h,0), _Player->GetFrame().cg, _Player->GetScene()->GetCamera()->GetView(), _Player->GetFrame().rev);
	SetDrawBright(25, 25, 255);
	if (_Player->GetScene()->GetFPSCon()->GetHitStop() > 0) {
		MyDrawMain(VAdd(_Player->GetHitPosition(), VGet(0, -_Player->GetHitFrame().h / 2, 0)), VGet(_Player->GetHitFrame().w, _Player->GetHitFrame().h, 0), _Player->GetHitFrame().cg, _Player->GetScene()->GetCamera()->GetView(), _Player->GetHitFrame().rev);
	}
	else {
		MyDrawMain(VAdd(_Player->GetDrawPosition(), VGet(0, -_Player->GetFrame().h / 2, 0)), VGet(_Player->GetFrame().w, _Player->GetFrame().h, 0), _Player->GetFrame().cg, _Player->GetScene()->GetCamera()->GetView(), _Player->GetFrame().rev);
	}
	
	
	SetMaskScreenGraphUseChannel(DX_MASKGRAPH_CH_A);
	SetMaskReverseEffectFlag(FALSE);
	SetUseMaskScreenFlag(FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawBright(255, 255, 255);
}

void PlayerSpriteComponent::SetImage(const TCHAR* filename) {

}