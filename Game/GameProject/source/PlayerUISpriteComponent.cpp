#include "PlayerUISpriteComponent.h"
#include "SceneMain.h"


PlayerUISpriteComponent::PlayerUISpriteComponent(class PlayerClass* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, _Player(owner)
	,Rotate(0)
{
	if (_Player->GetPlayerNo() == 0) {
		DrawStart = 311;
		DrawEnd = DrawStart + 560;
	}
	else {
		DrawStart = SCREEN_W-311;
		DrawEnd = DrawStart - 560;
	}

	Speaker[0] = LoadGraph("res/UI/gamemain/音量アイコン_ミュート.png");
	Speaker[1] = LoadGraph("res/UI/gamemain/音量アイコン.png");

	Record = LoadGraph("res/UI/gamemain/Record.png");

	//HPFrame = LoadGraph("res/UI/HP_00.png");
	switch(_Player->GetType()) {
	case 0:
		Mask = LoadGraph("res/UI/gamemain/HP_MASK_1000.png");
		HPFrame = LoadGraph("res/UI/gamemain/HP_00.png");
		break;
	case 1:
		Mask = LoadGraph("res/UI/gamemain/HP_MASK_1000.png");
		HPFrame = LoadGraph("res/UI/gamemain/HP_01.png");
		break;
	case 2:
		Mask = LoadGraph("res/UI/gamemain/HP_MASK_1000.png");
		HPFrame = LoadGraph("res/UI/gamemain/HP_02.png");
		break;
	case 3:
		Mask = LoadGraph("res/UI/gamemain/HP_MASK_1150.png");
		HPFrame = LoadGraph("res/UI/gamemain/HP_03.png");
		break;
	case 4:
		Mask = LoadGraph("res/UI/gamemain/HP_MASK_850.png");
		HPFrame = LoadGraph("res/UI/gamemain/HP_04.png");
		break;
	default:
		Mask = LoadGraph("res/UI/gamemain/HP_MASK_1000.png");
		HPFrame = LoadGraph("res/UI/gamemain/HP_05.png");
		break;
	}

}

PlayerUISpriteComponent::~PlayerUISpriteComponent()
{
	DeleteGraph(Speaker[0]);
	DeleteGraph(Speaker[1]);
	DeleteGraph(Mask);
	DeleteGraph(HPFrame);
	DeleteGraph(Record);
}

void PlayerUISpriteComponent::Draw()
{
	int DrawHeight = 29 ;
	float tmp = (float)(DrawEnd-DrawStart) / _Player->GetMaxHp() * _Player->GetHitPoint() + DrawStart;
	if (_Player->GetPlayerNo() == 1) {
		DrawTurnGraph(DrawEnd-35, DrawHeight-40, HPFrame, TRUE);
	}
	else { DrawGraph(DrawStart - 35, DrawHeight - 40, HPFrame, TRUE); }
	
	//DrawBox(1920/2, 0, tmp, 100, GetColor(25,25,25), TRUE);
	int value = rand() % (_Player->GetVolume()+1);
	value = 560 * value / 20;
	SetDrawScreen(_Owner->GetScene()->GetScreenMask());
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(255,255,255), TRUE);
	if (_Player->GetPlayerNo() == FALSE) {
		DrawGraph(DrawStart, DrawHeight, Mask, TRUE);
		//////////DrawBox(1920 / 2, 0, tmp, 100, GetColor(255, 255, 255), TRUE);
	}
	else { 
		DrawGraph(DrawEnd, DrawHeight, Mask, TRUE);
		/////////////DrawBox(1920 / 2, 0, tmp, 100, GetColor(255,255,255), TRUE);
	}

	VECTOR v[4];
	v[0] = VGet(-200, -200, 0); v[1] = VGet(200, -200, 0);
	v[2] = VGet(200, 200, 0); v[3] = VGet(-200, 200, 0);
	auto scene = dynamic_cast<SceneMain*>(_Owner->GetScene());
	Rotate += (float)scene->GetRhythm()->GetBpm()/750;
	
	int cg = Speaker[1];
	if (_Player->GetStunTime() > 0) {
		cg = Speaker[0];
		value = 0;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	DrawBox(DrawStart, DrawHeight, DrawEnd, DrawHeight + 50, GetColor(0, 0, 0), TRUE);
	SetMaskScreenGraph(_Owner->GetScene()->GetScreenMask());
	SetUseMaskScreenFlag(TRUE);
	SetMaskScreenGraphUseChannel(DX_MASKGRAPH_CH_R);
	int r, g, b;
	GetColor2(_Player->GetMyColor(), &r, &g, &b);
	if (DrawStart < DrawEnd) {
		DrawBox(DrawStart, DrawHeight, tmp, DrawHeight+50,  GetColor(255,255,255), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_MULA, 150);
		DrawBox(DrawStart, DrawHeight, DrawStart + value, DrawHeight+50, _Player->GetMyColor(), TRUE);
		MATRIX rot = MGetRotZ(Rotate / 180 * 4 * atan(1));
		for (int i = 0; i < 4; i++) {
			v[i] = VTransform(v[i], rot);
			v[i] = VAdd(v[i], VGet(200 - 103, 200 - 122, 0));
		
		}
		SetUseMaskScreenFlag(FALSE);
		SetMaskScreenGraphUseChannel(DX_MASKGRAPH_CH_A);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawModiGraph(v[0].x, v[0].y, v[1].x, v[1].y, v[2].x, v[2].y, v[3].x, v[3].y, Record, TRUE);
		DrawGraph(DrawStart - 90, DrawHeight - 20, cg, TRUE);
	}

	else { 
		DrawBox(tmp, DrawHeight, DrawStart, DrawHeight+50, GetColor(255,255,255), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_MULA, 150);
		DrawBox(DrawStart-value, DrawHeight, DrawStart, DrawHeight+50, _Player->GetMyColor(), TRUE); 
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetMaskScreenGraphUseChannel(DX_MASKGRAPH_CH_A);
		SetUseMaskScreenFlag(FALSE);
	

		MATRIX rot = MGetRotZ(-Rotate / 180 * 4 * atan(1));
		for (int i = 0; i < 4; i++) {
			v[i] = VTransform(v[i], rot);
			v[i] = VAdd(v[i], VGet(SCREEN_W + 103 - 200, 200 - 122, 0));

		}
		SetUseMaskScreenFlag(FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawModiGraph(v[0].x, v[0].y, v[1].x, v[1].y, v[2].x, v[2].y, v[3].x, v[3].y, Record, TRUE);
		DrawTurnGraph(DrawStart , DrawHeight - 20, cg, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetMaskScreenGraphUseChannel(DX_MASKGRAPH_CH_A);
	SetUseMaskScreenFlag(FALSE);


}
