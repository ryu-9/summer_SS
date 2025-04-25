#include "LightingComponent.h"
#include "SceneBase.h"

LightingComponent::LightingComponent(ActorClass* owner, VECTOR size, int file, int fadeCnt, VECTOR center, int color)
	:Component(owner)
	,_Center(center)
	,_Size(size)
	,_Cg(file)
	,_FadeCnt(fadeCnt)
	,_Start(GetNowCount())
	,_Color(color)
	,_Rev(FALSE)
	,_Value(100)
	,_Flag(TRUE)
{
	vert[0] = VScale(size, -0.5f);
	vert[1] = VGet(size.x / 2, -size.y / 2, 0);
	vert[2] = VScale(size, 0.5f);
	vert[3] = VScale(vert[1], -1);

	_Owner->GetScene()->AddLight(this);
}

LightingComponent::~LightingComponent()
{
	_Owner->GetScene()->RemoveLight(this);
}

void LightingComponent::Draw(bool color)
{
	if (_Flag != TRUE) { return; }
	//MyDrawMain(GetPosition(),_Size,_Cg,_Owner->GetScene()->GetCamera()->GetView());

	while (_Owner->GetPosition().x < -_Owner->GetScene()->GetCamera()->GetPosition().x - 2280 * 2) { _Owner->SetPosition(VAdd(_Owner->GetPosition(), VGet(2280 * 4, 0, 0))); }
	while (_Owner->GetPosition().x > -_Owner->GetScene()->GetCamera()->GetPosition().x + 2280 * 2) { _Owner->SetPosition(VAdd(_Owner->GetPosition(), VGet(-2280 * 4, 0, 0))); }

	VECTOR cf[4];
	for (int i = 0; i < 4; i++) {
		cf[i] = VTransform(VAdd(_Owner->GetPosition(), vert[i]), _Owner->GetScene()->GetCamera()->GetView());
		cf[i] = VAdd(cf[i], DrawCenter);

	}
	if (color == TRUE) {
		int r, g, b;
		GetColor2(_Color, &r, &g, &b);
		SetDrawBright(r, g, b);
	}
	if (_Rev == TRUE) {
		VECTOR tmp = cf[0];
		cf[0] = cf[1];
		cf[1] = tmp;
		tmp = cf[2];
		cf[2] = cf[3];
		cf[3] = tmp;
	}


	if (_FadeCnt > 0){
		int value = (float)(GetNowCount() - _Start) / _FadeCnt*255;
		if (_Color == GetColor(255, 255, 255)) { value *= 150 / 255; }
		SetDrawBlendMode(DX_BLENDMODE_ADD, 50 - 50 * (GetNowCount() - _Start) / _FadeCnt);
		DrawModiGraph((int)cf[0].x, (int)cf[0].y, (int)cf[1].x, (int)cf[1].y, (int)cf[2].x, (int)cf[2].y, (int)cf[3].x, (int)cf[3].y, _Cg, TRUE);
		DrawModiGraph((int)cf[0].x, (int)cf[0].y, (int)cf[1].x, (int)cf[1].y, (int)cf[2].x, (int)cf[2].y, (int)cf[3].x, (int)cf[3].y, _Cg, TRUE);
		//DrawModiGraph(cf[0].x, cf[0].y, cf[1].x, cf[1].y, cf[2].x, cf[2].y, cf[3].x, cf[3].y, _Cg, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_MULA, 150 - 150 * (GetNowCount() - _Start) / _FadeCnt);
		DrawModiGraph((int)cf[0].x, (int)cf[0].y, (int)cf[1].x, (int)cf[1].y, (int)cf[2].x, (int)cf[2].y, (int)cf[3].x, (int)cf[3].y, _Cg, TRUE);
		//DrawModiGraph(cf[0].x, cf[0].y, cf[1].x, cf[1].y, cf[2].x, cf[2].y, cf[3].x, cf[3].y, _Cg, TRUE);


	}
	else if(_FadeCnt<=0){
		if (color == FALSE) { 
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255); 
			DrawModiGraph((int)cf[0].x, (int)cf[0].y, (int)cf[1].x, (int)cf[1].y, (int)cf[2].x, (int)cf[2].y, (int)cf[3].x, (int)cf[3].y, _Cg, TRUE);
			//DrawModiGraph(cf[0].x, cf[0].y, cf[1].x, cf[1].y, cf[2].x, cf[2].y, cf[3].x, cf[3].y, _Cg, TRUE);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_MULA, 50);
			DrawModiGraph((int)cf[0].x, (int)cf[0].y, (int)cf[1].x, (int)cf[1].y, (int)cf[2].x, (int)cf[2].y, (int)cf[3].x, (int)cf[3].y, _Cg, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_ADD, _Value);
			DrawModiGraph((int)cf[0].x, (int)cf[0].y, (int)cf[1].x, (int)cf[1].y, (int)cf[2].x, (int)cf[2].y, (int)cf[3].x, (int)cf[3].y, _Cg, TRUE);

		}
	}
	SetDrawBright(255, 255, 255);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
