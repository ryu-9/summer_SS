#include "PsylliumControlClass.h"

PsylliumControlClass::PsylliumControlClass()
{
}

PsylliumControlClass::PsylliumControlClass(SceneBase* scene)
	:ActorClass(scene)
	, _Start(0)
	, _End(PSYLLIUM_MAX / 2)
	//,_Easing(0)
	, _Angle(0)
	, _Arm(200)
	, _Height(1500)
	, debugCnt(60)
	, debugNum(60)
	, _Type(0)
	, _Slope(30)
{
	_Cg[0] = LoadGraph("res/sample/psyllium.png");
	_Cg[1] = LoadGraph("res/sample/psyllium2.png");
	_CgF[0] = LoadGraph("res/sample/psyllium_1.png");
	_CgF[1] = LoadGraph("res/sample/psyllium2_1.png");
	int j;


		for (int i = 0; i < PSYLLIUM_MAX; i++) {
		j = rand() % PSYLLIUM_MAX;
		for (int ii = j; i < j+PSYLLIUM_MAX;ii++) {
			if (Psyllium[ii % PSYLLIUM_MAX] == nullptr) {
				int x, z;
				x = i * PSYLLIUM_DIST*2; z = 20;
				if(i>=28){
					x = (i - 28) * PSYLLIUM_DIST*1; z = 40;
					if (i >= 84) {
						x = (i-84) * PSYLLIUM_DIST/2; z = 80;
					}
				}
				Psyllium[ii%PSYLLIUM_MAX] = new PsylliumSpriteComponent(x,z,this,&_Easing,&_Angle,&_Arm, &_Height, &_Slope, 80);
				if(ii<_End){ Psyllium[ii % PSYLLIUM_MAX]->SetCg(_Cg[0], _CgF[0]); }
				else { Psyllium[ii % PSYLLIUM_MAX]->SetCg(_Cg[1], _CgF[1]); }
				break;
			}
		}
	}


}

PsylliumControlClass::~PsylliumControlClass()
{
}

void PsylliumControlClass::UpdateActor()
{
	//ここにイージングの更新とサイリウムの色変更を記述
	if (GetScene()->GetFPSCon()->GetHitStop() <= 0) {
		_Easing.now = GetNowCount();
	}
	int tmp = _End - _Start;
	float tmpTension = (float)GetScene()->GetTension() / 100.0f * PSYLLIUM_MAX;
	if (_Start > _End) { tmp =100* PSYLLIUM_MAX- (_Start - _End); }
	if (tmpTension > tmp) { 
		_End += tmpTension - tmp;
		while (_End > PSYLLIUM_MAX) { _End -= PSYLLIUM_MAX; }
	}
	if (tmpTension < tmp) { 
		_Start += tmp - tmpTension;
		while (_Start > PSYLLIUM_MAX) { _Start -= PSYLLIUM_MAX; }
	}
	for (int i = 0; i < PSYLLIUM_MAX;i++) {
		Psyllium[i]->SetCg(_Cg[0], _CgF[0]);
		if(_Start<_End){
			if(_Start<=i&&i<_End){ Psyllium[i]->SetCg(_Cg[1], _CgF[1]); }
		}
		if (_Start > _End) {
			if(_Start <= i || i < _End){ Psyllium[i]->SetCg(_Cg[1], _CgF[1]); }
		}
		if (_Start == _End) {
			if(GetScene()->GetTension()==100){
				Psyllium[i]->SetCg(_Cg[1], _CgF[1]);
			}
			else {
				Psyllium[i]->SetCg(_Cg[0], _CgF[0]);
			}
		}

	}

	int height = 0;
	int angle = 45;
	int arm = 250;

	switch (_Type) {
	case 1:
		arm = 0;
		break;

	case 2:
		angle = 0;
		arm = 0;


	}



	if (_Easing.end*1000 < GetNowCount()) {
		_Easing.start = (float)GetNowCount() / 1000.0f;
		_Easing.end = (float)(_Easing.start * 1000 + 1000)/1000;// +(float)(rand() % 240) / 60 * 1000) / 1000.0f;
	}
}
