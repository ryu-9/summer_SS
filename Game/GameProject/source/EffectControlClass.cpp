#include "EffectControlClass.h"
#include "SceneBase.h"
#include "SceneMain.h"
#include "LightingComponent.h"


EffectControlClass::EffectControlClass(SceneBase* scene)
	:ActorClass(scene)
{
	Speaker[0].emplace_back(LoadGraph("res/UI/rythm/Speaker_Circle.png"));
	Speaker[1].emplace_back(LoadGraph("res/UI/rythm/Speaker_Circle_01.png"));
	Wave.emplace_back(LoadGraph("res/UI/rythm/エフェクト.png"));
	Light.emplace_back(LoadGraph("res/UI/rythm/light.png"));
	MyLoadGraph(HitEffect, "res/stage/HitEffect.png");
	MyLoadGraph(JumpEffect, "res/stage/Jump.png");
	MyLoadGraph(LandEffect, "res/stage/Landing.png");
	MyLoadGraph(NotesStep_S[0], "res/effects/EREKI_NS_SUC.png");
	MyLoadGraph(NotesStep_F[0], "res/effects/EREKI_NS_FALSE.png");
	MyLoadGraph(Attack2[0], "res/effects/EREKI_GEN.png");
	MyLoadGraph(NotesStep_S[1], "res/effects/AKOGI_NS_SUC.png");
	MyLoadGraph(NotesStep_F[1], "res/effects/AKOGI_NS_FALSE.png");
	MyLoadGraph(Attack2[1], "res/effects/AKOGI_GEN.png");
	MyLoadGraph(NotesStep_S[2], "res/effects/KOTO_NS_SUC.png");
	MyLoadGraph(NotesStep_F[2], "res/effects/KOTO_NS_FALSE.png");
	MyLoadGraph(Attack2[2], "res/effects/KOTO_GEN.png");
	MyLoadGraph(NotesStep_S[3], "res/effects/RAIA_NS_SUC.png");
	MyLoadGraph(NotesStep_F[3], "res/effects/RAIA_NS_FALSE.png");
	MyLoadGraph(Attack2[3], "res/effects/RAIA_GEN.png");
	MyLoadGraph(NotesStep_S[4], "res/effects/FIDLE_NS_SUC.png");
	MyLoadGraph(NotesStep_F[4], "res/effects/FIDLE_NS_FALSE.png");
	MyLoadGraph(Attack2[4], "res/effects/FIDLE_GEN.png");
	MyLoadGraph(Circle, "res/effects/Circle.png");
	for (int i = 0; i < 2; i++) {
		int type = GetScene()->GetPlayer(i)->GetType();
		switch (type) {
		
		case 0:

			MyLoadGraph(Attack1[i][0][0], "res/chara00/言/LEATTACK1_1.png");
			MyLoadGraph(Attack1[i][1][0], "res/chara00/言/REATTACK1_1.png");
			MyLoadGraph(Attack1[i][0][1], "res/chara00/言/LEATTACK1_2.png");
			MyLoadGraph(Attack1[i][1][1], "res/chara00/言/REATTACK1_2.png");
			MyLoadGraph(Attack1[i][0][2], "res/chara00/言/LEATTACK1_3.png");
			MyLoadGraph(Attack1[i][1][2], "res/chara00/言/REATTACK1_3.png");
			MyLoadGraph(Attack1[i][0][3], "res/chara00/言/LEATTACK1_4.png");
			MyLoadGraph(Attack1[i][1][3], "res/chara00/言/REATTACK1_4.png");
			break;

		case 1:

			MyLoadGraph(Attack1[i][0][0], "res/chara01/言/LAATTACK1_1.png");
			MyLoadGraph(Attack1[i][1][0], "res/chara01/言/RAATTACK1_1.png");
			MyLoadGraph(Attack1[i][0][1], "res/chara01/言/LAATTACK1_2.png");
			MyLoadGraph(Attack1[i][1][1], "res/chara01/言/RAATTACK1_2.png");
			MyLoadGraph(Attack1[i][0][2], "res/chara01/言/LAATTACK1_3.png");
			MyLoadGraph(Attack1[i][1][2], "res/chara01/言/RAATTACK1_3.png");
			MyLoadGraph(Attack1[i][0][3], "res/chara01/言/LAATTACK1_4.png");
			MyLoadGraph(Attack1[i][1][3], "res/chara01/言/RAATTACK1_4.png");
			break;

		case 2:

			MyLoadGraph(Attack1[i][0][0], "res/chara02/言/LKATTACK1_1.png", VGet(1500, 1000, 0));
			MyLoadGraph(Attack1[i][1][0], "res/chara02/言/RKATTACK1_1.png", VGet(1500, 1000, 0));
			MyLoadGraph(Attack1[i][0][1], "res/chara02/言/LKATTACK1_2.png", VGet(1500, 1000, 0));
			MyLoadGraph(Attack1[i][1][1], "res/chara02/言/RKATTACK1_2.png", VGet(1500, 1000, 0));
			MyLoadGraph(Attack1[i][0][2], "res/chara02/言/LKATTACK1_3.png", VGet(1500, 1000, 0));
			MyLoadGraph(Attack1[i][1][2], "res/chara02/言/RKATTACK1_3.png", VGet(1500, 1000, 0));
			MyLoadGraph(Attack1[i][0][3], "res/chara02/言/LKATTACK1_4.png");
			MyLoadGraph(Attack1[i][1][3], "res/chara02/言/RKATTACK1_4.png");
			break;
		
		case 3:

			MyLoadGraph(Attack1[i][0][0], "res/chara03/言/LRATTACK1_1.png");
			MyLoadGraph(Attack1[i][1][0], "res/chara03/言/RRATTACK1_1.png");
			MyLoadGraph(Attack1[i][0][1], "res/chara03/言/LRATTACK1_2.png");
			MyLoadGraph(Attack1[i][1][1], "res/chara03/言/RRATTACK1_2.png");
			MyLoadGraph(Attack1[i][0][2], "res/chara03/言/LRATTACK1_3.png");
			MyLoadGraph(Attack1[i][1][2], "res/chara03/言/RRATTACK1_3.png");
			MyLoadGraph(Attack1[i][0][3], "res/chara03/言/LRATTACK1_4.png");
			MyLoadGraph(Attack1[i][1][3], "res/chara03/言/RRATTACK1_4.png");
			break;

		case 4:

			MyLoadGraph(Attack1[i][0][0], "res/chara04/言/LFATTACK1_1.png");
			MyLoadGraph(Attack1[i][1][0], "res/chara04/言/RFATTACK1_1.png");
			MyLoadGraph(Attack1[i][0][1], "res/chara04/言/LFATTACK1_2.png");
			MyLoadGraph(Attack1[i][1][1], "res/chara04/言/RFATTACK1_2.png");
			MyLoadGraph(Attack1[i][0][2], "res/chara04/言/LFATTACK1_3.png");
			MyLoadGraph(Attack1[i][1][2], "res/chara04/言/RFATTACK1_3.png");
			MyLoadGraph(Attack1[i][0][3], "res/chara04/言/LFATTACK1_4.png");
			MyLoadGraph(Attack1[i][1][3], "res/chara04/言/RFATTACK1_4.png");
			break;
		default:
			break;
		}	
	}

	MyLoadGraph(WhiteFlash, "res/effects/white_flash.png");
	PointLight = LoadGraph("res/stage/HitFlash.png");
	Start[0].emplace_back(LoadGraph("res/effects/開.png"));
	Start[1].emplace_back(LoadGraph("res/effects/演.png"));
	Start[2].emplace_back(LoadGraph("res/effects/LET’S_ROCK!.png"));
	End[0].emplace_back(LoadGraph("res/effects/終.png"));
	End[1].emplace_back(Start[1][0]);
	End[2].emplace_back(LoadGraph("res/effects/BEAT単.png"));
	RoundGet[5].emplace_back(LoadGraph("res/effects/sand_round_get.png"));
	RoundGet[0].emplace_back(LoadGraph("res/effects/eleki_round_get.png"));
	RoundGet[1].emplace_back(LoadGraph("res/effects/akogi_round_get.png"));
	RoundGet[2].emplace_back(LoadGraph("res/effects/koto_round_get.png"));
	RoundGet[3].emplace_back(LoadGraph("res/effects/lyre_round_get.png"));
	RoundGet[4].emplace_back(LoadGraph("res/effects/fidle_round_get.png"));
	Draw[0].emplace_back(LoadGraph("res/effects/DRAWBACK.png"));
	Draw[1].emplace_back(LoadGraph("res/effects/引.png"));
	Draw[2].emplace_back(LoadGraph("res/effects/分.png"));
	Round[0].emplace_back(LoadGraph("res/effects/ROUND1.png"));
	Round[1].emplace_back(LoadGraph("res/effects/ROUND2.png"));
	Round[2].emplace_back(LoadGraph("res/effects/FINALROUND .png"));
	Fade.emplace_back(LoadGraph("res/stage/fade.png"));
	ConceL.emplace_back(LoadGraph("res/effects/concent_line.png"));
	MyLoadGraph(Fire[0], "res/effects/fire_1.png", VGet(100, 200, 0));
	MyLoadGraph(Fire[1], "res/effects/fire_2.png", VGet(100, 200, 0));
	MyLoadGraph(Fire[2], "res/effects/fire_3.png", VGet(100, 200, 0));
	MyLoadGraph(Fire[3], "res/effects/fire_4.png", VGet(100, 200, 0));
}

EffectControlClass::~EffectControlClass()
{
	for (auto& cg : HitEffect) { DeleteGraph(cg); }
	for (auto& cg : JumpEffect) { DeleteGraph(cg); }
	for (auto& cg : LandEffect) { DeleteGraph(cg); }
	for (auto& cg : Start[0]) { DeleteGraph(cg); }
	for (auto& cg : Start[1]) { DeleteGraph(cg); }
	for (auto& cg : Start[2]) { DeleteGraph(cg); }
	for (auto& cg : Round[0]) { DeleteGraph(cg); }
	for (auto& cg : Round[1]) { DeleteGraph(cg); }
	for (auto& cg : Round[2]) { DeleteGraph(cg); }
	for (auto& cg : Draw[0]) { DeleteGraph(cg); }
	for (auto& cg : Draw[1]) { DeleteGraph(cg); }
	for (auto& cg : Draw[2]) { DeleteGraph(cg); }
	for (auto& cg : RoundGet[0]) { DeleteGraph(cg); }
	for (auto& cg : RoundGet[1]) { DeleteGraph(cg); }
	for (auto& cg : RoundGet[2]) { DeleteGraph(cg); }
	for (auto& cg : RoundGet[3]) { DeleteGraph(cg); }
	for (auto& cg : RoundGet[4]) { DeleteGraph(cg); }
	for (auto& cg : RoundGet[5]) { DeleteGraph(cg); }
	for (auto& cg : End[0]) { DeleteGraph(cg); }
	for (auto& cg : End[1]) { DeleteGraph(cg); }
	for (auto& cg : End[2]) { DeleteGraph(cg); }
	for (auto& cg : NotesStep_S[0]) { DeleteGraph(cg); }
	for (auto& cg : NotesStep_S[1]) { DeleteGraph(cg); }
	for (auto& cg : NotesStep_S[2]) { DeleteGraph(cg); }
	for (auto& cg : NotesStep_S[3]) { DeleteGraph(cg); }
	for (auto& cg : NotesStep_S[4]) { DeleteGraph(cg); }
	for (auto& cg : NotesStep_F[0]) { DeleteGraph(cg); }
	for (auto& cg : NotesStep_F[1]) { DeleteGraph(cg); }
	for (auto& cg : NotesStep_F[2]) { DeleteGraph(cg); }
	for (auto& cg : NotesStep_F[3]) { DeleteGraph(cg); }
	for (auto& cg : NotesStep_F[4]) { DeleteGraph(cg); }
	for (auto& cg : Attack2[0]) { DeleteGraph(cg); }
	for (auto& cg : Attack2[1]) { DeleteGraph(cg); }
	for (auto& cg : Attack2[2]) { DeleteGraph(cg); }
	for (auto& cg : Attack2[3]) { DeleteGraph(cg); }
	for (auto& cg : Attack2[4]) { DeleteGraph(cg); }
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 4; k++) {
				for (auto& cg : Attack1[i][j][k]) { DeleteGraph(cg); }
			}
		}
	}
	for (auto& cg : Speaker[0]) { DeleteGraph(cg); }
	for (auto& cg : Speaker[1]) { DeleteGraph(cg); }
	for (auto& cg : Fade) { DeleteGraph(cg); }
	for (auto& cg : Wave) { DeleteGraph(cg); }
	for (auto& cg : Light) { DeleteGraph(cg); }
	for (auto& cg : ConceL) { DeleteGraph(cg); }
	for (auto& cg : WhiteFlash) { DeleteGraph(cg); }
	for (auto& cg : Fire[0]) { DeleteGraph(cg); }
	for (auto& cg : Fire[1]) { DeleteGraph(cg); }
	for (auto& cg : Fire[2]) { DeleteGraph(cg); }
	for (auto& cg : Fire[3]) { DeleteGraph(cg); }
}

EffectClass* EffectControlClass::AddEffect(VECTOR pos, int type)
{
	//return nullptr;

	std::vector<int> EffectCg;
	VECTOR size;
	VECTOR position = VGet(0, 0, 0);
	VECTOR pos2 = position;
	bool FPSFlag = FALSE;
	int blend = DX_BLENDMODE_NOBLEND;
	int value = 0;
	unsigned int color = 0;
	int cgtime = 0;
	int draworder = 95;
	bool rev = FALSE;
	int type1 = GetScene()->GetPlayer(0)->GetType();
	int type2 = GetScene()->GetPlayer(1)->GetType();

	switch (type) {
	case 1:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(HitEffect.size());
		std::copy(HitEffect.begin(), HitEffect.end(), EffectCg.begin());
		FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		value = 225;
		color = GetColor(255, 255, 255);
		draworder = 105;
		break;

	case 2:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(HitEffect.size());
		std::copy(HitEffect.begin(), HitEffect.end(), EffectCg.begin());
		FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		value = 225;
		color = GetScene()->GetPlayer(0)->GetMyColor();
		draworder = 105;
		break;

	case 3:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(HitEffect.size());
		std::copy(HitEffect.begin(), HitEffect.end(), EffectCg.begin());
		FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		value = 225;
		color = GetScene()->GetPlayer(1)->GetMyColor();
		draworder = 105;
		break;

	case 4:
		size = VGet(2000, 2000, 0);
		EffectCg.resize(WhiteFlash.size());
		std::copy(WhiteFlash.begin(), WhiteFlash.end(), EffectCg.begin());
		FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		value = 255;
		color = GetScene()->GetPlayer(0)->GetMyColor();
		draworder = 106;
		break;

	case 5:
		size = VGet(2000, 2000, 0);
		EffectCg.resize(WhiteFlash.size());
		std::copy(WhiteFlash.begin(), WhiteFlash.end(), EffectCg.begin());
		FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		value = 255;
		rev = TRUE;
		color = GetScene()->GetPlayer(1)->GetMyColor();
		draworder = 106;
		break;

	case 6:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(HitEffect.size());
		std::copy(HitEffect.begin(), HitEffect.end(), EffectCg.begin());
		FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		value = 225;
		break;

	case 7:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(HitEffect.size());
		std::copy(HitEffect.begin(), HitEffect.end(), EffectCg.begin());
		FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		value = 225;
		break;


	case 11:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(JumpEffect.size());
		position.y -= size.y / 2;			//地面用
		std::copy(JumpEffect.begin(), JumpEffect.end(), EffectCg.begin());
		break;

	case 12:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(LandEffect.size());
		position.y -= size.y / 2;			//地面用
		std::copy(LandEffect.begin(), LandEffect.end(), EffectCg.begin());
		FPSFlag = TRUE;
		break;

		//プレイヤー1
	case 22:		//ノーツステップ成功
		rev = TRUE;
	case 23:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(NotesStep_S[type1].size());
		std::copy(NotesStep_S[type1].begin(), NotesStep_S[type1].end(), EffectCg.begin());
		FPSFlag = TRUE;
		switch (type1) {
		case 0:
			position = VAdd(position, VGet(404,317, 0));
			position = VAdd(position, VGet(500, 500, 0));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		case 1:
			size = VGet(1000, 1000, 0);
			position = VAdd(position, VGet(0,0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		case 2:
		case 3:
		case 4:
		default:
			position = VAdd(position, VGet(0, 0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;

		}
		break;

	case 24:		//ノーツステップ失敗
		rev = TRUE;
	case 25:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(NotesStep_F[type1].size());
		std::copy(NotesStep_F[type1].begin(), NotesStep_F[type1].end(), EffectCg.begin());
		FPSFlag = TRUE;
		switch (type1) {
		case 0:
			position = VAdd(position, VGet(404, 317, 0));
			position = VAdd(position, VScale(size,0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		case 1:
			size = VGet(1000, 1000, 0);
			position = VAdd(position, VGet(0, 0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		case 2:
		case 3:
		case 4:
		default:
			position = VAdd(position, VGet(0, 0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;

		}
		break;



	case 28:		//言葉攻撃一段目
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[0][0][0].size());
		std::copy(Attack1[0][0][0].begin(), Attack1[0][0][0].end(), EffectCg.begin());
		FPSFlag = TRUE;
		if (type1 == 2) { size = VGet(1500, 1000, 0); }
		position = VAdd(position, VGet(602,0, 0));
		position = VAdd(position, VScale(size, 0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		position.x = -position.x;
			break;

	case 29:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[0][1][0].size());
		std::copy(Attack1[0][1][0].begin(), Attack1[0][1][0].end(), EffectCg.begin());
		FPSFlag = TRUE;
		if (type1 == 2) { size = VGet(1500, 1000, 0); }
		position = VAdd(position, VGet(602,0, 0));
		position = VAdd(position, VScale(size, 0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		break;

	case 30:		//言葉攻撃二段目
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[0][0][1].size());
		std::copy(Attack1[0][0][1].begin(), Attack1[0][0][1].end(), EffectCg.begin());
		FPSFlag = TRUE;
		if (type1 == 2) { size = VGet(1500, 1000, 0); }
		position = VAdd(position, VGet(605, 0, 0));
		position = VAdd(position, VScale(size, 0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		position.x = -position.x;
			break;

	case 31:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[0][1][1].size());
		std::copy(Attack1[0][1][1].begin(), Attack1[0][1][1].end(), EffectCg.begin());
		FPSFlag = TRUE;
		if (type1 == 2) { size = VGet(1500, 1000, 0); }
		position = VAdd(position, VGet(605, 0, 0));
		position = VAdd(position, VScale(size, 0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		break;

	case 32:		//言葉攻撃三段目
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[0][0][2].size());
		std::copy(Attack1[0][0][2].begin(), Attack1[0][0][2].end(), EffectCg.begin());
		FPSFlag = TRUE;
		if (type1 == 2) { size = VGet(1500, 1000, 0); }
		position = VAdd(position, VGet(614,0, 0));
		position = VAdd(position, VScale(size,0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		position.x = -position.x;
			break;

	case 33:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[0][1][2].size());
		std::copy(Attack1[0][1][2].begin(), Attack1[0][1][2].end(), EffectCg.begin());
		FPSFlag = TRUE;
		if (type1 == 2) { size = VGet(1500, 1000, 0); }
		position = VAdd(position, VGet(614,0, 0));
		position = VAdd(position, VScale(size,0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		break;

	case 34:		//言葉ジャンプ
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[0][0][3].size());
		std::copy(Attack1[0][0][3].begin(), Attack1[0][0][3].end(), EffectCg.begin());
		FPSFlag = TRUE;
		size = VGet(890,945, 0);
		position = VAdd(position, VGet(616,0, 0));
		position = VAdd(position, VScale(size, 0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		position.x = -position.x;
			break;

	case 35:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[0][1][3].size());
		std::copy(Attack1[0][1][3].begin(), Attack1[0][1][3].end(), EffectCg.begin());
		FPSFlag = TRUE;
		size = VGet(890,945, 0);
		position = VAdd(position, VGet(616,0, 0));
		position = VAdd(position, VScale(size, 0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		break;



	case 36:		//楽器一段目攻撃失敗
		rev = TRUE;
	case 37:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack2[type1].size());
		std::copy(Attack2[type1].begin(), Attack2[type1].end(), EffectCg.begin());
		FPSFlag = TRUE;
		switch (type1) {
		case 0:
			size = VGet(800, 800, 0);
			position = VAdd(position, VGet(100, 151, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		case 1:
			size = VGet(800, 800, 0);
			position = VAdd(position, VGet(100, 151, 0));
			position = VAdd(position, VScale(size,0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			if (rev == TRUE) {
				rev = FALSE;
				position = VGet(-position.x, position.y, 0);
			}
			break;
		case 2:
			position = VAdd(position, VGet(0, 51, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		case 3:
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		case 4:
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		default:
			break;

		}
		break;


	case 38:		//楽器一段目攻撃成功
		rev = TRUE;
	case 39:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack2[type1].size());
		std::copy(Attack2[type1].begin(), Attack2[type1].end(), EffectCg.begin());
		FPSFlag = TRUE;
		switch (type1) {
		case 0:
			position = VAdd(position, VGet(0,0,0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			pos2 = VGet(597, 0, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			pos2 = VGet(1097, 0, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -2));

			break;

		case 1:
			position = VAdd(position, VGet(0, 0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			if (rev == TRUE) {
				//rev = FALSE;
				position = VGet(-position.x, position.y, 0);
			}
			pos2 = VGet(597, 0, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) {
				pos2 = VGet(-pos2.x, pos2.y, 0); 
				//rev = FALSE;
			}
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			pos2 = VGet(1097, 0, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) {
				pos2 = VGet(-pos2.x, pos2.y, 0); 
				rev = FALSE;
			}
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -2));

			break;
		case 2:
			position = VAdd(position, VGet(0, 51, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
		case 3:
			size = VGet(815, 815, 0);
			position = VAdd(position, VGet(597, 72, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			pos2 = VGet(1096, 72, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			break;
		case 4:
			position = VAdd(position, VGet(0, 0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			pos2 = VGet(597, 0, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -2));

			pos2 = VGet(1097, 0, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -4));

			break;
		default:
			break;

		}
		break;



	case 40:		//楽器二段目攻撃成功
		rev = TRUE;
	case 41:
		//VECTOR pos2 = position;
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack2[type1].size());
		std::copy(Attack2[type1].begin(), Attack2[type1].end(), EffectCg.begin());
		FPSFlag = TRUE;
		switch (type1) {
		case 0:
			size = VGet(510,510, 0);
			position = VAdd(position, VGet(156,256, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(358,358, 0);
			pos2 = VGet(30,321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(358, 358, 0);
			pos2 = VGet(452,321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(510, 510, 0);
			break;
		case 1:

			size = VGet(510, 510, 0);
			position = VAdd(position, VGet(156, 256, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			if (rev == TRUE) {
				//rev = FALSE;
				position = VGet(-position.x, position.y, 0);
			}

			size = VGet(358, 358, 0);
			pos2 = VGet(30, 321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));
			if (rev == TRUE) {
				pos2 = VGet(-pos2.x, pos2.y, 0);
				//rev = FALSE;
			}
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(358, 358, 0);
			pos2 = VGet(452, 321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) {
				pos2 = VGet(-pos2.x, pos2.y, 0);
				rev = FALSE;
			}
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(510, 510, 0);
			break;
		case 2:
			size = VGet(472, 472, 0);
			position = VAdd(position, VGet(0, 0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(783, 783, 0);
			pos2 = VGet(0, 217, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));
			size = VGet(472, 472, 0);

			break;
		case 3:
			size = VGet(510, 510, 0);
			position = VAdd(position, VGet(156, 256, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(358, 358, 0);
			pos2 = VGet(30, 321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(358, 358, 0);
			pos2 = VGet(452, 321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(510, 510, 0);
			break;
		case 4:
			size = VGet(510, 510, 0);
			position = VAdd(position, VGet(156, 256, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(358, 358, 0);
			pos2 = VGet(30, 321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(358, 358, 0);
			pos2 = VGet(452, 321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(510, 510, 0);
			break;
		default:
			break;

		}
		break;

	case 42:		//楽器三段目攻撃成功
		rev = TRUE;
	case 43:
		size = VGet(1000,1000, 0);
		EffectCg.resize(Attack2[type1].size());
		std::copy(Attack2[type1].begin(), Attack2[type1].end(), EffectCg.begin());
		FPSFlag = TRUE;
		switch (type1) {
		case 0:
			size = VGet(604,604, 0);
			position = VAdd(position, VGet(198,216, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(907,907, 0);
			pos2 = VGet(47,166, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(604, 604, 0);
			break;
		case 1:
			size = VGet(604, 604, 0);
			position = VAdd(position, VGet(198, 216, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			if (rev == TRUE) {
				//rev = FALSE;
				position = VGet(-position.x, position.y, 0);
			}

			size = VGet(907, 907, 0);
			pos2 = VGet(47, 166, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { 
				pos2 = VGet(-pos2.x, pos2.y, 0);
				rev = FALSE;
			}
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(604, 604, 0);
			break;
		case 2:
			size = VGet(585, 585, 0);
			position = VAdd(position, VGet(213, 251, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(491, 491, 0);
			pos2 = VGet(260, 378, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));
			size = VGet(585, 585, 0);

			break;

		case 3:
			size = VGet(604, 604, 0);
			position = VAdd(position, VGet(198, 216, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(907, 907, 0);
			pos2 = VGet(47, 166, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(604, 604, 0);
			break;
		case 4:
			size = VGet(604, 604, 0);
			position = VAdd(position, VGet(198, 216, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(907, 907, 0);
			pos2 = VGet(47, 166, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(604, 604, 0);
			break;
		default:
			break;

		}
		break; 

	case 44:		//楽器ジャンプ攻撃成功
		rev = TRUE;
	case 45:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack2[type1].size());
		std::copy(Attack2[type1].begin(), Attack2[type1].end(), EffectCg.begin());
		FPSFlag = TRUE;
		switch (type1) {
		case 0:
			size = VGet(1035, 1035, 0);
			position = VAdd(position, VGet(-79,-35, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(394, 394, 0);
			pos2 =  VGet(214,221, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(571,571, 0);
			pos2 = VGet(576,532, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(1035, 1035, 0);
			break;
		case 1:
			size = VGet(1035, 1035, 0);
			position = VAdd(position, VGet(-79, -35, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			if (rev == TRUE) {
				//rev = FALSE;
				position = VGet(-position.x, position.y, 0);
			}
			size = VGet(394, 394, 0);
			pos2 = VGet(214, 221, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) {
				pos2 = VGet(-pos2.x, pos2.y, 0);
				//rev = FALSE;
			}
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(571, 571, 0);
			pos2 = VGet(576, 532, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { 
					pos2 = VGet(-pos2.x, pos2.y, 0);
					rev = FALSE;
			}
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(1035, 1035, 0);
			break;
		case 2:
			position = VAdd(position, VGet(-89, 12, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(375,375, 0);
			pos2 = VGet(224,253, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(689, 689, 0);
			pos2 = VGet(500,426, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(1000, 1000, 0);
			break;
		case 3:
			size = VGet(1035, 1035, 0);
			position = VAdd(position, VGet(-79, -35, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(394, 394, 0);
			pos2 = VGet(214, 221, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(571, 571, 0);
			pos2 = VGet(576, 532, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(1035, 1035, 0);
			break;
		case 4:
			size = VGet(1035, 1035, 0);
			position = VAdd(position, VGet(-79, -35, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(394, 394, 0);
			pos2 = VGet(214, 221, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(571, 571, 0);
			pos2 = VGet(576, 532, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(1035, 1035, 0);
			break;
		default:
			break;

		}
		break;

	case 46:		//楽器しゃがみ攻撃成功
		rev = TRUE;
	case 47:
		size = VGet(529, 529, 0);
		EffectCg.resize(Attack2[type1].size());
		std::copy(Attack2[type1].begin(), Attack2[type1].end(), EffectCg.begin());
		FPSFlag = TRUE;
		position = VAdd(position, VGet(500,-89, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
		if (rev == TRUE&&type1==1) {
				rev = FALSE;
				position = VGet(-position.x, position.y, 0);
			}

		break;

		//プレイヤー2
	case 62:		//ノーツステップ成功
		rev = TRUE;
	case 63:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(NotesStep_S[type2].size());
		std::copy(NotesStep_S[type2].begin(), NotesStep_S[type2].end(), EffectCg.begin());
		FPSFlag = TRUE;
		switch (type2) {
		case 0:
			position = VAdd(position, VGet(404, 317, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		case 1:
			size = VGet(1000, 1000, 0);
			position = VAdd(position, VGet(0, 0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		case 2:
		case 3:
		case 4:
			position = VAdd(position, VGet(0, 0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
		default:
			break;

		}
		break;

	case 64:		//ノーツステップ失敗
		rev = TRUE;
	case 65:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(NotesStep_F[type2].size());
		std::copy(NotesStep_F[type2].begin(), NotesStep_F[type2].end(), EffectCg.begin());
		FPSFlag = TRUE;
		switch (type2) {
		case 0:
			position = VAdd(position, VGet(404, 317, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		case 1:
			size = VGet(1000, 1000, 0);
			position = VAdd(position, VGet(0, 0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		case 2:
		case 3:
		case 4:
		default:
			position = VAdd(position, VGet(0, 0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;

		}
		break;



	case 68:		//言葉攻撃一段目
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[1][0][0].size());
		std::copy(Attack1[1][0][0].begin(), Attack1[1][0][0].end(), EffectCg.begin());
		FPSFlag = TRUE;
		if (type2 == 2) { size = VGet(1500, 1000, 0); }
		position = VAdd(position, VGet(602, 0, 0));
		position = VAdd(position, VScale(size, 0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		position.x = -position.x;
			break;

	case 69:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[1][1][0].size());
		std::copy(Attack1[1][1][0].begin(), Attack1[1][1][0].end(), EffectCg.begin());
		FPSFlag = TRUE;
		if (type2 == 2) { size = VGet(1500, 1000, 0); }
		position = VAdd(position, VGet(602, 0, 0));
		position = VAdd(position, VScale(size, 0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		break;

	case 70:		//言葉攻撃二段目
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[1][0][1].size());
		std::copy(Attack1[1][0][1].begin(), Attack1[1][0][1].end(), EffectCg.begin());
		FPSFlag = TRUE;
		if (type2 == 2) { size = VGet(1500, 1000, 0); }
		position = VAdd(position, VGet(605, 0, 0));
		position = VAdd(position, VScale(size, 0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		position.x = -position.x;
			break;

	case 71:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[1][1][1].size());
		std::copy(Attack1[1][1][1].begin(), Attack1[1][1][1].end(), EffectCg.begin());
		FPSFlag = TRUE;
		if (type2 == 2) { size = VGet(1500, 1000, 0); }
		position = VAdd(position, VGet(605, 0, 0));
		position = VAdd(position, VScale(size, 0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		break;

	case 72:		//言葉攻撃三段目
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[1][0][2].size());
		std::copy(Attack1[1][0][2].begin(), Attack1[1][0][2].end(), EffectCg.begin());
		FPSFlag = TRUE;
		if (type2 == 2) { size = VGet(1500, 1000, 0); }
		position = VAdd(position, VGet(614, 0, 0));
		position = VAdd(position, VScale(size, 0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		position.x = -position.x;
			break;

	case 73:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[1][1][2].size());
		std::copy(Attack1[1][1][2].begin(), Attack1[1][1][2].end(), EffectCg.begin());
		FPSFlag = TRUE;
		if (type2 == 2) { size = VGet(1500, 1000, 0); }
		position = VAdd(position, VGet(614, 0, 0));
		position = VAdd(position, VScale(size, 0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		break;

	case 74:		//言葉ジャンプ
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[1][0][3].size());
		std::copy(Attack1[1][0][3].begin(), Attack1[1][0][3].end(), EffectCg.begin());
		FPSFlag = TRUE;
		size = VGet(890, 945, 0);
		position = VAdd(position, VGet(616, 0, 0));
		position = VAdd(position, VScale(size, 0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		position.x = -position.x;
			break;

	case 75:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack1[1][1][3].size());
		std::copy(Attack1[1][1][3].begin(), Attack1[1][1][3].end(), EffectCg.begin());
		FPSFlag = TRUE;
		size = VGet(890, 945, 0);
		position = VAdd(position, VGet(616, 0, 0));
		position = VAdd(position, VScale(size, 0.5));
		position = VAdd(position, VGet(-500, -1000, 0));
		break;



	case 76:		//楽器一段目攻撃失敗
		rev = TRUE;
	case 77:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack2[type2].size());
		std::copy(Attack2[type2].begin(), Attack2[type2].end(), EffectCg.begin());
		FPSFlag = TRUE;
		switch (type2) {
		case 0:
			size = VGet(800, 800, 0);
			position = VAdd(position, VGet(100, 151, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		case 1:
			size = VGet(800, 800, 0);
			position = VAdd(position, VGet(100, 151, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			if (rev == TRUE) {
				rev = FALSE;
				position = VGet(-position.x, position.y, 0);
			}
			break;
		case 2:
			position = VAdd(position, VGet(0, 51, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		case 3:
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		case 4:
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			break;
		default:
			break;

		}
		break;


	case 78:		//楽器一段目攻撃成功
		rev = TRUE;
	case 79:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack2[type2].size());
		std::copy(Attack2[type2].begin(), Attack2[type2].end(), EffectCg.begin());
		FPSFlag = TRUE;
		switch (type2) {
		case 0:
			position = VAdd(position, VGet(0, 0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			pos2 = VGet(597, 0, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -2));

			pos2 = VGet(1097, 0, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -4));

			break;
		case 1:
			position = VAdd(position, VGet(0, 0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			if (rev == TRUE) {
				//rev = FALSE;
				position = VGet(-position.x, position.y, 0);
			}
			pos2 = VGet(597, 0, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) {
				pos2 = VGet(-pos2.x, pos2.y, 0);
				//rev = FALSE;
			}
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			pos2 = VGet(1097, 0, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) {
				pos2 = VGet(-pos2.x, pos2.y, 0);
				rev = FALSE;
			}
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -2));

			break;
			break;
		case 2:
			position = VAdd(position, VGet(0, 51, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
		case 3:
			size = VGet(815, 815, 0);
			position = VAdd(position, VGet(597, 72, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			pos2 = VGet(1096, 72, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			break;
		case 4:
			position = VAdd(position, VGet(0, 0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			pos2 = VGet(597, 0, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			pos2 = VGet(1097, 0, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -2));

			break;
		default:
			break;

		}
		break;


	case 80:		//楽器二段目攻撃成功
		rev = TRUE;
	case 81:
		//VECTOR pos2 = position;
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack2[type2].size());
		std::copy(Attack2[type2].begin(), Attack2[type2].end(), EffectCg.begin());
		FPSFlag = TRUE;
		switch (type2) {
		case 0:
			size = VGet(510, 510, 0);
			position = VAdd(position, VGet(156, 256, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(358, 358, 0);
			pos2 = VGet(30, 321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(358, 358, 0);
			pos2 = VGet(452, 321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(510, 510, 0);
			break;
		case 1:

			size = VGet(510, 510, 0);
			position = VAdd(position, VGet(156, 256, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			if (rev == TRUE) {
				//rev = FALSE;
				position = VGet(-position.x, position.y, 0);
			}

			size = VGet(358, 358, 0);
			pos2 = VGet(30, 321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) {
				pos2 = VGet(-pos2.x, pos2.y, 0);
				//rev = FALSE;
			}
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(358, 358, 0);
			pos2 = VGet(452, 321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) {
				pos2 = VGet(-pos2.x, pos2.y, 0);
				rev = FALSE;
			}
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(510, 510, 0);
			break;
		case 2:
			size = VGet(472, 472, 0);
			position = VAdd(position, VGet(0, 0, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(783, 783, 0);
			pos2 = VGet(0, 217, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));
			size = VGet(472, 472, 0);

			break;
		case 3:
			size = VGet(510, 510, 0);
			position = VAdd(position, VGet(156, 256, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(358, 358, 0);
			pos2 = VGet(30, 321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(358, 358, 0);
			pos2 = VGet(452, 321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(510, 510, 0);
			break;
		case 4:
			size = VGet(510, 510, 0);
			position = VAdd(position, VGet(156, 256, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(358, 358, 0);
			pos2 = VGet(30, 321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(358, 358, 0);
			pos2 = VGet(452, 321, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(510, 510, 0);
			break;
		default:
			break;

		}
		break;

	case 82:		//楽器三段目攻撃成功
		rev = TRUE;
	case 83:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack2[type2].size());
		std::copy(Attack2[type2].begin(), Attack2[type2].end(), EffectCg.begin());
		FPSFlag = TRUE;
		switch (type2) {
		case 0:
			size = VGet(604, 604, 0);
			position = VAdd(position, VGet(198, 216, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(907, 907, 0);
			pos2 = VGet(47, 166, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(604, 604, 0);
			break;
		case 1:
			size = VGet(604, 604, 0);
			position = VAdd(position, VGet(198, 216, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			if (rev == TRUE) {
				//rev = FALSE;
				position = VGet(-position.x, position.y, 0);
			}

			size = VGet(907, 907, 0);
			pos2 = VGet(47, 166, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) {
				pos2 = VGet(-pos2.x, pos2.y, 0);
				rev = FALSE;
			}
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(604, 604, 0);
			break;
		case 2:
			size = VGet(585, 585, 0);
			position = VAdd(position, VGet(213, 251, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(491, 491, 0);
			pos2 = VGet(260, 378, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));
			size = VGet(585, 585, 0);

			break;

		case 3:
			size = VGet(604, 604, 0);
			position = VAdd(position, VGet(198, 216, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(907, 907, 0);
			pos2 = VGet(47, 166, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(604, 604, 0);
			break;
		case 4:
			size = VGet(604, 604, 0);
			position = VAdd(position, VGet(198, 216, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(907, 907, 0);
			pos2 = VGet(47, 166, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(604, 604, 0);
			break;
		default:
			break;

		}
		break;

	case 84:		//楽器ジャンプ攻撃成功
		rev = TRUE;
	case 85:
		size = VGet(1000, 1000, 0);
		EffectCg.resize(Attack2[type2].size());
		std::copy(Attack2[type2].begin(), Attack2[type2].end(), EffectCg.begin());
		FPSFlag = TRUE;
		switch (type2) {
		case 0:
			size = VGet(1035, 1035, 0);
			position = VAdd(position, VGet(-79, -35, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(394, 394, 0);
			pos2 = VGet(214, 221, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(571, 571, 0);
			pos2 = VGet(576, 532, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(1035, 1035, 0);
			break;
		case 1:
			size = VGet(1035, 1035, 0);
			position = VAdd(position, VGet(-79, -35, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
			if (rev == TRUE) {
				//rev = FALSE;
				position = VGet(-position.x, position.y, 0);
			}
			size = VGet(394, 394, 0);
			pos2 = VGet(214, 221, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) {
				pos2 = VGet(-pos2.x, pos2.y, 0);
				//rev = FALSE;
			}
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(571, 571, 0);
			pos2 = VGet(576, 532, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) {
				pos2 = VGet(-pos2.x, pos2.y, 0);
				rev = FALSE;
			}
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(1035, 1035, 0);
			break;
		case 2:
			position = VAdd(position, VGet(-89, 12, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(375, 375, 0);
			pos2 = VGet(224, 253, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(689, 689, 0);
			pos2 = VGet(500, 426, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(1000, 1000, 0);
			break;
		case 3:
			size = VGet(1035, 1035, 0);
			position = VAdd(position, VGet(-79, -35, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(394, 394, 0);
			pos2 = VGet(214, 221, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(571, 571, 0);
			pos2 = VGet(576, 532, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(1035, 1035, 0);
			break;
		case 4:
			size = VGet(1035, 1035, 0);
			position = VAdd(position, VGet(-79, -35, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));

			size = VGet(394, 394, 0);
			pos2 = VGet(214, 221, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(571, 571, 0);
			pos2 = VGet(576, 532, 0);
			pos2 = VAdd(pos2, VScale(size, 0.5));
			pos2 = VAdd(pos2, VGet(-500, -1000, 0));

			if (rev == TRUE) { pos2 = VGet(-pos2.x, pos2.y, 0); }
			pos2 = VAdd(pos2, pos);
			_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, pos2, size, EffectCg, EffectCg.size(), FPSFlag, blend, value, color, FALSE, rev, -1));

			size = VGet(1035, 1035, 0);
			break;
		default:
			break;

		}
		break;

	case 86:		//楽器しゃがみ攻撃成功
		rev = TRUE;
	case 87:
		size = VGet(529, 529, 0);
		EffectCg.resize(Attack2[type1].size());
		std::copy(Attack2[type1].begin(), Attack2[type1].end(), EffectCg.begin());
		FPSFlag = TRUE;
		position = VAdd(position, VGet(500, -89, 0));
			position = VAdd(position, VScale(size, 0.5));
			position = VAdd(position, VGet(-500, -1000, 0));
		if (rev == TRUE && type1 == 1) {
				rev = FALSE;
				position = VGet(-position.x, position.y, 0);
			}

		break;



	case 101:
		rev = TRUE;
	case 102:
		size = VGet(400,800, 0);
		EffectCg.resize(Fire[0].size());
		std::copy(Fire[0].begin(), Fire[0].end(), EffectCg.begin());
		//FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		cgtime = EffectCg.size() * GetScene()->GetFPSCon()->GetDeltaTime()/2;
		value = 200;
		draworder = 85;
		break;

	case 103:
		rev = TRUE;
	case 104:
		size = VGet(400, 800, 0);
		EffectCg.resize(Fire[1].size());
		std::copy(Fire[1].begin(), Fire[1].end(), EffectCg.begin());
		//FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		cgtime = EffectCg.size() * GetScene()->GetFPSCon()->GetDeltaTime() / 2;
		value = 200;
		draworder = 85;
		break;

	case 105:
		rev = TRUE;
	case 106:
		size = VGet(400, 800, 0);
		EffectCg.resize(Fire[2].size());
		std::copy(Fire[2].begin(), Fire[2].end(), EffectCg.begin());
		//FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		cgtime = EffectCg.size() * GetScene()->GetFPSCon()->GetDeltaTime() / 2;
		value = 200;
		draworder = 85;
		break;

	case 107:
		rev = TRUE;
	case 108:
		size = VGet(400, 800, 0);
		EffectCg.resize(Fire[3].size());
		std::copy(Fire[3].begin(), Fire[3].end(), EffectCg.begin());
		//FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		cgtime = EffectCg.size() * GetScene()->GetFPSCon()->GetDeltaTime() / 2;
		value = 200;
		draworder = 85;
		break;



	case 111:
		rev = TRUE;
	case 112:
		size = VGet(400, 800, 0);
		EffectCg.resize(Fire[0].size());
		std::copy(Fire[0].begin(), Fire[0].end(), EffectCg.begin());
		//FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		cgtime = EffectCg.size() * GetScene()->GetFPSCon()->GetDeltaTime() / 2;
		value = 200;
		draworder = 110;
		break;

	case 113:
		rev = TRUE;
	case 114:
		size = VGet(400, 800, 0);
		EffectCg.resize(Fire[1].size());
		std::copy(Fire[1].begin(), Fire[1].end(), EffectCg.begin());
		//FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		cgtime = EffectCg.size() * GetScene()->GetFPSCon()->GetDeltaTime() / 2;
		value = 200;
		draworder = 110;
		break;

	case 115:
		rev = TRUE;
	case 116:
		size = VGet(400, 800, 0);
		EffectCg.resize(Fire[2].size());
		std::copy(Fire[2].begin(), Fire[2].end(), EffectCg.begin());
		//FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		cgtime = EffectCg.size() * GetScene()->GetFPSCon()->GetDeltaTime() / 2;
		value = 200;
		draworder = 110;
		break;

	case 117:
		rev = TRUE;
	case 118:
		size = VGet(400, 800, 0);
		EffectCg.resize(Fire[3].size());
		std::copy(Fire[3].begin(), Fire[3].end(), EffectCg.begin());
		//FPSFlag = TRUE;
		blend = DX_BLENDMODE_ADD;
		cgtime = EffectCg.size() * GetScene()->GetFPSCon()->GetDeltaTime() / 2;
		value = 200;
		draworder = 110;
		break;




	case 121:
		size = VGet(2000, 2000, 0);
		EffectCg.resize(Circle.size());
		std::copy(Circle.begin(), Circle.end(), EffectCg.begin());
		//FPSFlag = TRUE;
		cgtime = (FRAME_NUM * 2 - 1) * GetScene()->GetFPSCon()->GetDeltaTime();
		draworder = 105;
		break;


	default:
		return nullptr;
	}
	if (cgtime == 0) {
		if (FPSFlag == TRUE) { cgtime = EffectCg.size(); }
		else { cgtime = EffectCg.size() * GetScene()->GetFPSCon()->GetDeltaTime(); }
	}
	if (rev == TRUE) { position = VGet(-position.x, position.y, 0); }
	position = VAdd(position, pos);
	_Effects.emplace_back(new EffectClass(type, GetScene(), draworder, position, size, EffectCg, cgtime, FPSFlag, blend, value, color, FALSE, rev));
	return _Effects[_Effects.size() - 1];

}

void EffectControlClass::Init()
{
	for (auto ef : _Effects) {
		delete ef;
	}
}

void EffectControlClass::AddScreenEffect(VECTOR pos, int type)
{

	std::vector<int> EffectCg;
	VECTOR size = VGet(1000, 1000, 1000);
	VECTOR position = pos;
	auto scene = dynamic_cast<SceneMain*>(GetScene());
	bool FPSFlag = FALSE;
	int blend = DX_BLENDMODE_NOBLEND;
	int value = 0;
	int color = 0;
	int cgtime = 0;
	int screenflag = type;
	int draworder = 200;
	bool rev = FALSE;

	switch (type) {
	case 1:					//試合開始時エフェクト
		size = VGet(616, 668, 0);
		EffectCg.resize(Start[0].size());
		std::copy(Start[0].begin(), Start[0].end(), EffectCg.begin());
		cgtime = 1000;
		draworder = 101;
		break;

	case 2:					//試合開始時エフェクト
		size = VGet(616, 668, 0);
		EffectCg.resize(Start[1].size());
		std::copy(Start[1].begin(), Start[1].end(), EffectCg.begin());
		cgtime = 1000;
		draworder = 101;
		break;

	case 3:					//試合開始時エフェクト
		size = VGet(1529, 206, 0);
		EffectCg.resize(Start[2].size());
		std::copy(Start[2].begin(), Start[2].end(), EffectCg.begin());
		cgtime = 1000;
		draworder = 101;
		break;


	case 6:					//試合終了時エフェクト
		size = VGet(616, 668, 0);
		EffectCg.resize(End[0].size());
		std::copy(End[0].begin(), End[0].end(), EffectCg.begin());
		cgtime = 2000;
		draworder = 90;
		break;

	case 7:					//試合終了時エフェクト
		size = VGet(616, 668, 0);
		EffectCg.resize(End[1].size());
		std::copy(End[1].begin(), End[1].end(), EffectCg.begin());
		cgtime = 2000;
		draworder = 90;
		break;

	case 8:					//試合終了時エフェクト
		size = VGet(537, 198, 0);
		EffectCg.resize(End[2].size());
		std::copy(End[2].begin(), End[2].end(), EffectCg.begin());
		cgtime = 2000;
		draworder = 105;
		break;

	case 11: {			//試合終了時エフェクト
		size = VGet(1980, 622, 0);
		int i = GetScene()->GetPlayer(0)->GetType();
		EffectCg.resize(RoundGet[i].size());
		std::copy(RoundGet[i].begin(), RoundGet[i].end(), EffectCg.begin());
		cgtime = 2000;
		draworder = 155;
		break;
	}
	case 12: {					//試合終了時エフェクト
		size = VGet(1980, 622, 0);
		int i = GetScene()->GetPlayer(1)->GetType();
		EffectCg.resize(RoundGet[i].size());
		std::copy(RoundGet[i].begin(), RoundGet[i].end(), EffectCg.begin());
		cgtime = 2000;
		draworder = 155;
		break;
	}
	case 13:
		size = VGet(1980, 621, 0);
		EffectCg.resize(Draw[0].size());
		std::copy(Draw[0].begin(), Draw[0].end(), EffectCg.begin());
		cgtime = 2000;
		draworder = 155;
		break;
	case 14:
		size = VGet(616, 668, 0);
		EffectCg.resize(Draw[1].size());
		std::copy(Draw[1].begin(), Draw[1].end(), EffectCg.begin());
		cgtime = 2000;
		draworder = 156;
		break;
	case 15:
		size = VGet(616, 668, 0);
		EffectCg.resize(Draw[2].size());
		std::copy(Draw[2].begin(), Draw[2].end(), EffectCg.begin());
		cgtime = 2000;
		draworder = 156;
		break;

	case 16:					//フェードインエフェクト
		size = VGet(1920, 1080, 0);
		EffectCg.resize(Fade.size());
		std::copy(Fade.begin(), Fade.end(), EffectCg.begin());
		cgtime = 1500;
		draworder = 300;
		blend = DX_BLENDMODE_ALPHA;
		break;

	case 17:					//フェードアウトエフェクト
		size = VGet(1920, 1080, 0);
		EffectCg.resize(Fade.size());
		std::copy(Fade.begin(), Fade.end(), EffectCg.begin());
		cgtime = 1500;
		draworder = 300;
		blend = DX_BLENDMODE_ALPHA;
		break;
	case 18:
		switch (scene->GetRound()) {
		case 0:
			size = VGet(1848, 664, 0);
			break;
		case 1:
			size = VGet(1930, 664, 0);
			break;
		case 2:
			size = VGet(1940, 664, 0);
			break;
		}
		EffectCg.resize(Round[scene->GetRound()].size());
		std::copy(Round[scene->GetRound()].begin(), Round[scene->GetRound()].end(), EffectCg.begin());
		cgtime = 1000;
		draworder = 250;
		break;


	case 19:					//真っ黒
		size = VGet(1920, 1080, 0);
		EffectCg.resize(Fade.size());
		std::copy(Fade.begin(), Fade.end(), EffectCg.begin());
		cgtime = 1500;
		draworder = 300;
		blend = DX_BLENDMODE_ALPHA;
		break;

	case 50: //スピーカー
		size = VGet(100, 100, 0);
		EffectCg.resize(Speaker[0].size());
		std::copy(Speaker[0].begin(), Speaker[0].end(), EffectCg.begin());
		cgtime = -1;
		draworder = 205;
		break;

	case 51: //スピーカー1
		FPSFlag = TRUE;
		size = VGet(100, 100, 0);
		EffectCg.resize(Speaker[1].size());
		std::copy(Speaker[1].begin(), Speaker[1].end(), EffectCg.begin());
		cgtime = -1;
		draworder = 205;
		break;

	case 52: //スピーカー2
		FPSFlag = TRUE;
		size = VGet(100, 100, 0);
		EffectCg.resize(Speaker[1].size());
		std::copy(Speaker[1].begin(), Speaker[1].end(), EffectCg.begin());
		cgtime = -1;
		draworder = 205;
		rev = TRUE;
		break;

	case 54:
		rev = TRUE;
	case 53: //スピーカー2
		FPSFlag = TRUE;
		size = VGet(250, 250, 0);
		EffectCg.resize(Wave.size());
		std::copy(Wave.begin(), Wave.end(), EffectCg.begin());
		cgtime = -1;
		draworder = 206;
		blend = DX_BLENDMODE_ALPHA;
		break;

	case 55:
		rev = TRUE;
		color = GetScene()->GetPlayer(0)->GetMyColor();
	case 56:
		if (color == 0) {
			color = GetScene()->GetPlayer(1)->GetMyColor();
		}
		size = VGet(10, 105, 0);
		EffectCg.resize(Light.size());
		std::copy(Light.begin(), Light.end(), EffectCg.begin());
		cgtime = 500;
		draworder = 201;
		value = 150;
		blend = DX_BLENDMODE_ALPHA;

		break;
	case 60:
		size = VGet(1920, 1080, 0);
		EffectCg.resize(ConceL.size());
		std::copy(ConceL.begin(), ConceL.end(), EffectCg.begin());
		cgtime = 500;
		draworder = 205;

		break;

	case 62:
		rev = TRUE;
		color = GetScene()->GetPlayer(0)->GetMyColor();
		size = VGet(1920, 1080, 0);
		EffectCg.resize(ConceL.size());
		std::copy(ConceL.begin(), ConceL.end(), EffectCg.begin());
		cgtime = 500;
		draworder = 210;
		break;

	case 63:
		rev = TRUE;
		color = GetScene()->GetPlayer(1)->GetMyColor();
		size = VGet(1920, 1080, 0);
		EffectCg.resize(ConceL.size());
		std::copy(ConceL.begin(), ConceL.end(), EffectCg.begin());
		cgtime = 500;
		draworder = 210;

		break;
	default:
		return;
	}
	if (cgtime == 0) {
		cgtime = EffectCg.size();
	}
	new EffectClass(-1, GetScene(), draworder, position, size, EffectCg, cgtime, FPSFlag, blend, value, color, screenflag, rev);
	}



void MyLoadGraph(std::vector<int> &cg, const TCHAR *file, VECTOR size)
{
	int XSize, YSize;
	int tmp = LoadGraph(file);
	if (tmp == -1) {
		DeleteGraph(tmp);
		return;
	}
	GetImageSize_File(file, &XSize, &YSize);
	int cgnum = XSize*size.y / (YSize*size.x);
	cg.resize(cgnum);
	if (cgnum <= 0) { cg.resize(1); }
	LoadDivGraph(file, cgnum, cgnum, 1, XSize / cgnum, YSize, &cg[0]);
	DeleteGraph(tmp);
}

void EffectControlClass::RemoveEffects(EffectClass* itr)
{
	for (int i = 0; i < _Effects.size(); i++) {
		if (itr == _Effects[i]) {
			_Effects.erase(_Effects.begin() + i);
			return;
		}
	}
}

void EffectControlClass::ResetMotEffect(int No)
{
	int start = 21 + No * 40, end = 60 + No * 40;
	for (int i = 0,j=0; i+j < _Effects.size(); i++) {
		if (_Effects[i]->GetType() >= start && _Effects[i]->GetType() <= end) {
			delete _Effects[i];
			i--;
			j++;
		}
	}
}
