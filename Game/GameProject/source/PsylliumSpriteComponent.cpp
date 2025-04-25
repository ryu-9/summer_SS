#include "PsylliumSpriteComponent.h"
#include "RhythmControlClass.h"
#include "Dxlib.h"
#include "math.h"
#include "SceneBase.h"








PsylliumSpriteComponent::PsylliumSpriteComponent(int cg, int cgF, int cgP, int* color, float X, float Z, ActorClass* Owner,
	float *easing, int *angle, int *arm, int* height, int* slope, int DrawOrder)
	:SpriteComponent(Owner,DrawOrder)
	,_Cg(cg)
	,_CgF(cgF)
	,_CgP(cgP)
	,_StageColor(color)

{
	x = X;
	z = Z;
	lag = (rand() % 100);
	lag -= 5;
	if (lag < 0) {
		lag = sqrt(-lag);
		lag *= -1;
	}
	else { lag = sqrt(lag); }
	lag /= 100;
	lag - 0.3;
	use = TRUE;
	//_Owner = Owner;
	_Arm = arm;
	_Angle = angle;
	_Easing = easing;
	_Height = height;
	_Slope = slope;
	armError = (float)(rand() % 10) / 100;
}








PsylliumSpriteComponent::~PsylliumSpriteComponent()
{
}

void PsylliumSpriteComponent::Draw()
{
	float PI = atan(1)*4;
	float tmp = *_Easing; 
	
	int size = 150;
	float debug = cos((tmp*1.2 - 0.2 + lag) * PI);
	tmp += lag;
	if (tmp >= 1) { rotate = 2 - tmp; }
	else { rotate = tmp; }
	if (rotate < 0) { rotate *= -1; }
	rotate *= 2;
	rotate -=1;
	//rotate = cos(tmp * PI);
	float tmpSlope =(1 - debug)/2 * sin((float)*_Slope / 180 * PI);
	int tmpZ = z - tmpSlope * 5;
	VECTOR pos = VGet(x+ _Owner->GetScene()->GetCamera()->GetPosition().x*sqrt(z)/5, 400 + (7500 + *_Height*(abs(cos(tmp*PI))-0.5)*2 + armError )/z, 0);
	while (pos.x<0) {
		pos.x += 14 * PSYLLIUM_DIST * 4;
	}
	while (pos.x> 15 * PSYLLIUM_DIST * 4) {
		pos.x -= 14 * PSYLLIUM_DIST * 4;
	}

	VECTOR pos2 = pos;
	float tmpDist = pos.x - 7 * PSYLLIUM_DIST * 4;
	float tmpRot = atan2(tmpDist,1920/2);
	float test =  tmpSlope * cos(tmpRot);
	//test = size * 25 / z * test;
	pos2.y += (1 - cos(tmpRot)) * 1000 / z;
	pos.y += tmpSlope * (cos(tmpRot))*1000/z + (1-cos(tmpRot)) * 5000 / z/z;
	pos.y -= (1 - debug) * 2000 * sin((float)*_Slope / 180 * PI)/z;
	pos.y += 1000 * sin((float)*_Slope / 180 * PI) / z;
	pos.x -= _Owner->GetScene()->GetCamera()->GetPosition().x + 7 * PSYLLIUM_DIST * 4;
	pos2.x -= _Owner->GetScene()->GetCamera()->GetPosition().x + 7 * PSYLLIUM_DIST * 4;
	VECTOR testPos = VGet(tmpDist, 500 - 2 * z, 0);
	testPos = VTransform(testPos, _Owner->GetScene()->GetCamera()->GetView());
	testPos = VAdd(testPos, DrawCenter);
	//MyDrawMainP(pos,VGet(size*25/z,size*25/z*(1-test), 0), _Cg, _CgF, _Owner->GetScene()->GetCamera(), rotate * *_Angle + sin(tmpRot) * (1-cos(tmp  * PI))/2 * (float)*_Slope, *_Arm*(1 + armError), test);

	//DrawFormatString(pos.x, pos.y, GetColor(255, 255, 255), "%f", tmpSlope * (cos(tmpRot)));

	VECTOR DrawV = VGet(1920 / 2, GROUND_HEIGHT, 0);	//•`‰æ’†S
	MATRIX cam = _Owner->GetScene()->GetCamera()->GetView();
	VECTOR vert[4];
	VECTOR sizeV = VGet(size * 25 / z, size * 25 / z * (1 - test), 0);
	vert[0] = VGet(-sizeV.x / 2, -sizeV.y - *_Arm * (1 + armError), 0);
	vert[1] = VGet(sizeV.x / 2, -sizeV.y - *_Arm * (1 + armError), 0);
	vert[3] = VGet(-sizeV.x / 2, -*_Arm * (1 + armError), 0);
	vert[2] = VGet(sizeV.x / 2, -*_Arm * (1 + armError), 0);
	float rot = rotate * *_Angle +sin(tmpRot) * ((4/5- cos((tmp)*PI))) * (float)*_Slope;
	MATRIX rotM = MGetRotZ(rot / 180 * atan(1) * 4);
	VECTOR tmpV = VAdd(pos, VGet(0, *_Arm * (1 + armError), 0));

	for (int i = 0; i < 4; i++) {
		vert[i] = VTransform(vert[i], rotM);
		vert[i] = VAdd(vert[i], tmpV);
		vert[i] = VTransform(vert[i], cam);
		vert[i] = VAdd(vert[i], DrawV);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawModiGraph((int)vert[0].x, (int)vert[0].y, (int)vert[1].x, (int)vert[1].y, (int)vert[2].x, (int)vert[2].y, (int)vert[3].x, (int)vert[3].y, _Cg, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	SetDrawBright(_Color[0], _Color[1], _Color[2]);
	DrawModiGraph((int)vert[0].x, (int)vert[0].y, (int)vert[1].x, (int)vert[1].y, (int)vert[2].x, (int)vert[2].y, (int)vert[3].x, (int)vert[3].y, _CgF, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int r, g, b;
	GetColor2(*_StageColor, &r, &g, &b);
	SetDrawBright(r,g,b);

	size = 175 + armError*250;
	sizeV = VGet(size * 25 / z, size * 50 / z , 0);
	sizeV = VScale(sizeV, 1 + armError);
	vert[0] = VGet(-sizeV.x/2, -sizeV.y, 0);
	vert[1] = VGet(sizeV.x/2 , -sizeV.y, 0);
	vert[3] = VGet(-sizeV.x / 2, 0, 0);
	vert[2] = VGet(sizeV.x , 0, 0);
	pos2 = VAdd(pos2, VGet(sizeV.x*1/4 + armError * 10, sizeV.y + armError * 500, 0));

	rotM = MGetRotZ(rotate* *_Angle / 720 * atan(1) * 4);
	for (int i = 0; i < 4; i++) {
		vert[i] = VTransform(vert[i], rotM);
		vert[i] = VAdd(vert[i], pos2);
		vert[i] = VTransform(vert[i], cam);
		vert[i] = VAdd(vert[i], DrawV);
	}
	DrawModiGraph((int)vert[0].x, (int)vert[0].y, (int)vert[1].x, (int)vert[1].y, (int)vert[2].x, (int)vert[2].y, (int)vert[3].x, (int)vert[3].y, _CgP, TRUE);
	
	SetDrawBright(255, 255, 255);
}

void PsylliumSpriteComponent::SetColor(int r, int g, int b)
{
	 _Color[0] = r; 
	 _Color[1] = g; 
	 _Color[2] = b; 
}
