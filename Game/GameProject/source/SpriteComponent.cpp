#include "SpriteComponent.h"
#include "ActorClass.h"
#include "SceneBase.h"
#include "winmain.h"
#include "Stage.h"
#include "PlayerClass.h"
#include "MainSpriteComponent.h"

SpriteComponent::SpriteComponent(ActorClass* owner, int drawOrder, int alpha)
	:Component(owner)
	, _DrawOrder(drawOrder)
{
	_Owner->GetScene()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
	_Owner->GetScene()->RemoveSprite(this);
	for (int i = 0; i < _cgHandle.size();i++) {
		DeleteGraph(_cgHandle[i]);
	}
	auto s = _cgHandle.size();
	for (auto i = 0; i < s; i++) {
		_cgHandle.pop_back();
	}
}

void SpriteComponent::Draw() {
		
}

void SpriteComponent::SetImage(const TCHAR* filename) {
	_cgHandle.emplace_back(LoadGraph(filename)) ;
}

// ÉJÉÅÉâÇ…ëŒâûÇµÇΩï`âÊÇçsÇ§
void MyDrawMain(VECTOR pos, VECTOR size, int cg, MATRIX cam, bool rev, bool flag)
{
	VECTOR cf[4];
	VECTOR DrawV = VGet(SCREEN_W/2,GROUND_HEIGHT,0);	//ï`âÊíÜêS
	cf[0] = VTransform(VAdd(pos, VScale(size, -0.5f)), cam);
	cf[0] = VAdd(cf[0],DrawV);
	cf[2] = VTransform(VAdd(pos, VScale(size, 0.5f)), cam);
	cf[2] = VAdd(cf[2], DrawV);
	cf[1] = VTransform(VAdd(pos, VGet(size.x/2, -size.y/2,0)), cam);
	cf[1] = VAdd(cf[1], DrawV);
	cf[3] = VTransform(VAdd(pos, VGet(-size.x/2, size.y/2, 0)), cam);
	cf[3] = VAdd(cf[3], DrawV);
	if (rev == FALSE) { DrawModiGraph((int)cf[0].x, (int)cf[0].y, (int)cf[1].x, (int)cf[1].y, (int)cf[2].x, (int)cf[2].y, (int)cf[3].x, (int)cf[3].y, cg, flag); }
	else { DrawModiGraph((int)cf[1].x, (int)cf[1].y, (int)cf[0].x, (int)cf[0].y, (int)cf[3].x, (int)cf[3].y, (int)cf[2].x, (int)cf[2].y, cg, flag); }
}


// åıåπÇ…ÇÊÇÈåıÇ∆âeÇÃï`âÊÅiàÍÉLÉÉÉâñàÅj
void DrawLighting(PlayerClass* player, LightingComponent* Light, int mask1, int mask2, int mask3, int mask4) {


	

	VECTOR PlayerPos = player->GetPosition();
	if (player->GetScene()->GetFPSCon()->GetHitStop() > 0) {
		PlayerPos = player->GetHitPosition();
	}
	MOTION_FRAME PlayerFrame = player->GetFrame();
	VECTOR LightPos = Light->GetPosition();
	if (player->GetScene()->GetFPSCon()->GetHitStop() > 0) {
		PlayerPos = player->GetHitPosition();
		PlayerFrame = player->GetHitFrame();
	}
	VECTOR PlayerSize = VGet(PlayerFrame.w, PlayerFrame.h, 0);


	VECTOR dir = VSub(PlayerPos, LightPos);

	PlayerPos = VAdd(PlayerPos, VGet(player->GetDrawPosition().x - player->GetPosition().x, 0, 0));
	//dir.z = dir.z*2;
	dir = VNorm(dir);
	dir = VScale(dir, 255 / 200);
	SetUseMaskScreenFlag(FALSE);
	SetDrawScreen(mask1);
	ClearDrawScreen();

	DrawBox(0, 0, 1920, 1080, GetColor(255, 255, 255), TRUE);
	float alpha[3];
	alpha[0] =dir.x; alpha[1] = dir.y; alpha[2] = dir.z;
	for (auto& a : alpha) {
		if (a < 0) { a *= -a; }
		else { a *= a; }
		a *= 255;
	
	}

	if (alpha[0] < 0) {
		if (PlayerFrame.rev == TRUE) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, -alpha[0]);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_INVSRC, -alpha[0]);
		}
	}
	else {
		if (PlayerFrame.rev == TRUE) {
			SetDrawBlendMode(DX_BLENDMODE_INVSRC, alpha[0]);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha[0]);
		}

	}
	MyDrawMain(VAdd(PlayerPos, VGet(0, -PlayerSize.y / 2, 0)), PlayerSize, PlayerFrame.mask, player->GetScene()->GetCamera()->GetView(), PlayerFrame.rev);


	SetMaskScreenGraphUseChannel(DX_MASKGRAPH_CH_R);

	SetMaskScreenGraph(mask1);
	
	SetDrawScreen(mask4);
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0,0,0), TRUE);
	SetUseMaskScreenFlag(TRUE);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255,255,255), TRUE);


	SetUseMaskScreenFlag(FALSE);
	SetDrawScreen(mask2);
	
	ClearDrawScreen();
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255,255,255), TRUE);

	SetDrawBlendMode(DX_BLENDMODE_PMA_SUB,255);
	DrawGraph(0, 0, mask4, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);










	SetUseMaskScreenFlag(FALSE);
	SetDrawScreen(mask1);
	ClearDrawScreen();
	DrawBox(0, 0, 1920, 1080, GetColor(255, 255, 255), TRUE);


	if (alpha[1] > 0) {
		SetDrawBlendMode(DX_BLENDMODE_INVSRC, alpha[1]);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, -alpha[1]);
	}
	MyDrawMain(VAdd(PlayerPos, VGet(0, -PlayerSize.y / 2, 0)), PlayerSize, PlayerFrame.mask, player->GetScene()->GetCamera()->GetView(), PlayerFrame.rev);
	SetMaskScreenGraphUseChannel(DX_MASKGRAPH_CH_G);



	SetDrawScreen(mask4);
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);
	SetUseMaskScreenFlag(TRUE);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 255, 255), TRUE);



	SetUseMaskScreenFlag(FALSE);
	SetDrawScreen(mask2);

	SetDrawBlendMode(DX_BLENDMODE_PMA_SUB, 255);
	DrawGraph(0, 0, mask4, TRUE);

	SetDrawScreen(mask1);
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 255, 255), TRUE);



	if (alpha[2] < 0) {
		SetDrawBlendMode(DX_BLENDMODE_INVSRC, -alpha[2]);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha[2]);
	}
	MyDrawMain(VAdd(PlayerPos, VGet(0, -PlayerSize.y / 2, 0)), PlayerSize, PlayerFrame.mask, player->GetScene()->GetCamera()->GetView(), PlayerFrame.rev);
	SetMaskScreenGraphUseChannel(DX_MASKGRAPH_CH_B);


	SetDrawScreen(mask4);
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);
	SetUseMaskScreenFlag(TRUE);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 255, 255), TRUE);



	SetUseMaskScreenFlag(FALSE);
	SetDrawScreen(mask2);

	SetDrawBlendMode(DX_BLENDMODE_PMA_SUB, 255);
	DrawGraph(0, 0, mask4, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_DST_RGB_SRC_A, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 255, 255), TRUE);









	SetUseMaskScreenFlag(FALSE);
	SetDrawScreen(mask1);
	ClearDrawScreen();
	Light->Draw(FALSE);		//NOBLENDÇ…ñﬂÇÈ
	SetDrawScreen(mask2);
	SetDrawBlendMode(DX_BLENDMODE_MUL_A, 255);		//åıà»äOÇÃïîï™Çè¡Ç∑
	DrawGraph(0, 0, mask1, TRUE);



	SetDrawScreen(mask4);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 255, 255), TRUE);
	DrawGraph(0, 0, mask2, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(55, 55, 55), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_SUB, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(200,200,200), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_DST_RGB_SRC_A, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0,0,0), TRUE);

	SetDrawScreen(mask1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0,0,0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; i * (255 - 200) < 250; i++) {
		DrawGraph(0, 0, mask4, TRUE);
	}
	SetDrawScreen(mask4);
	ClearDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 255);
	DrawGraph(0, 0, mask3, TRUE);
	SetDrawScreen(mask3);
	ClearDrawScreen();
	Light->Draw(FALSE);
	DrawGraph(0, 0, mask4, TRUE);
	SetMaskScreenGraph(mask1);
	SetUseMaskScreenFlag(TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);




	SetUseMaskScreenFlag(FALSE);
	SetDrawScreen(mask4);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255, 255, 255), TRUE);
	DrawGraph(0, 0, mask2, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(155,155,155), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_SUB, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(250,250,250), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_DST_RGB_SRC_A, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);





	SetDrawScreen(mask1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0,0,0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	for (int i = 0; (i) * (255 - 250) < 250; i++) {
		DrawGraph(0, 0, mask4, TRUE);
	}






	SetDrawScreen(DX_SCREEN_BACK);


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	//SetUseMaskScreenFlag(FALSE);
	//DrawGraph(0, 0, mask1, TRUE);






	SetMaskReverseEffectFlag(FALSE);
	SetUseMaskScreenFlag(TRUE);
	SetMaskScreenGraph(mask1);

	SetDrawBlendMode(DX_BLENDMODE_MUL, 200);
	Light->Draw(TRUE, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 100);
	Light->Draw(TRUE, FALSE);


	//Light->Draw();

	SetUseMaskScreenFlag(FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetMaskScreenGraphUseChannel(DX_MASKGRAPH_CH_A);

	SetDrawScreen(DX_SCREEN_BACK);


}