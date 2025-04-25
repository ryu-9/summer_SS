#include "MainSpriteComponent.h"
#include "ActorClass.h"
#include "Main.h"



MainSpriteComponent::MainSpriteComponent(ActorClass* Owner, VECTOR size, const TCHAR* file, int DrawOrder, int BlendMode, int value, int color, bool rev, bool maskflag)
:SpriteComponent(Owner,DrawOrder)
,_BlendMode(BlendMode)
,_Value(value)
,_Rotate(0)
,_Color(color)
,_Reverse(rev)
,_Mask(-1)
,_Obj(nullptr)
{
	vert[0] = VScale(size, -0.5f);
	vert[1] = VGet(size.x / 2, -size.y / 2, 0);
	vert[2] = VScale(size, 0.5f);
	vert[3] = VScale(vert[1], -1);
	SetImage(file);
	_Cg = GetImage()[0];
	if (maskflag == TRUE) {
		_Mask = MakeScreen(1920, 1080, TRUE);
	}
}

MainSpriteComponent::~MainSpriteComponent()
{
	if (_Obj == nullptr) {
		delete _Obj;
	}
}

void MainSpriteComponent::SetCgnum(int i)
{
	//DeleteGraph(_Cg);
	_Cg = GetImage()[i];
}

void MainSpriteComponent::Draw()
{
	if (_Cg == -1) {
		SetDrawBlendMode(DX_BLENDMODE_MULA, 100);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		return;
	}



	while (_Owner->GetPosition().x < -_Owner->GetScene()->GetCamera()->GetPosition().x - 3840 * 2) { _Owner->SetPosition(VAdd(_Owner->GetPosition(), VGet(3840 * 4, 0, 0))); }
	while (_Owner->GetPosition().x > -_Owner->GetScene()->GetCamera()->GetPosition().x + 3840 * 2) { _Owner->SetPosition(VAdd(_Owner->GetPosition(), VGet(-3840 * 4, 0, 0))); }
	
	VECTOR cf[4];
	for (int i = 0; i < 4; i++) {
		cf[i] = VTransform(VAdd(_Owner->GetPosition(), vert[i]), _Owner->GetScene()->GetCamera()->GetView());
		cf[i] = VAdd(cf[i], DrawCenter);

	}
	if (_Mask!=-1&&_Obj!=nullptr) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetUseMaskScreenFlag(FALSE);
		int screen = GetDrawScreen();
		/*
				
		if (screen != _Owner->GetScene()->GetScreenMask()) {
			SetDrawScreen(_Owner->GetScene()->GetScreenMask());
		}
		else {
			SetDrawScreen(_Owner->GetScene()->GetSubMask()); 
		}
		*/
		SetDrawScreen(_Mask);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		int mode = _Obj->GetBlendMode();
		int value = _Obj->GetValue();
		int color = _Obj->GetMyColor();
		_Obj->SetMyColor(GetColor(255, 255, 255));
		_Obj->SetBlendMode(DX_BLENDMODE_ADD);
		_Obj->SetValue(255);
		_Obj->Draw();
		_Obj->SetBlendMode(mode);
		_Obj->SetValue(value);
		_Obj->SetMyColor(color);
		SetDrawScreen(screen);
		//DrawGraph(0, 0, _Owner->GetScene()->GetScreenMask(), FALSE);
		SetMaskScreenGraph(_Mask);
		SetUseMaskScreenFlag(TRUE);
		SetMaskReverseEffectFlag(TRUE);
		SetMaskScreenGraphUseChannel(DX_MASKGRAPH_CH_G);
	}
	SetDrawBlendMode(_BlendMode, _Value);
	if (_Color != 0) {
		int r, g, b;
		GetColor2(_Color, &r, &g, &b);
		SetDrawBright(r, g, b);
	}
	if (_Reverse == TRUE) {
		DrawModiGraph((int)cf[1].x, (int)cf[1].y, (int)cf[0].x, (int)cf[0].y, (int)cf[3].x, (int)cf[3].y, (int)cf[2].x, (int)cf[2].y, _Cg, TRUE);
	}
	else {
		DrawModiGraph((int)cf[0].x, (int)cf[0].y, (int)cf[1].x, (int)cf[1].y, (int)cf[2].x, (int)cf[2].y, (int)cf[3].x, (int)cf[3].y, _Cg, TRUE);

	}
	//DrawExtendGraph(cf[0].x, cf[0].y, cf[1].x, cf[1].y, _Cg, TRUE);


	SetDrawBright(255,255,255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	SetUseMaskScreenFlag(FALSE);
	SetMaskReverseEffectFlag(FALSE);
	SetMaskScreenGraphUseChannel(DX_MASKGRAPH_CH_A);
}


void MainSpriteComponent::ChangeImage(int cg)
{
	_Cg = cg; 
}