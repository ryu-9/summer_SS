#include "NoteSpriteComponent.h"
#include "DxLib.h"
#include "Main.h"
#include <deque>
#include "SceneMain.h"


NoteSpriteComponent::NoteSpriteComponent(ActorClass* owner, int drawOrder)
	:SpriteComponent(owner,200)
	,_DrawX(15)
	,_DrawY(52)
{
	_RhythmCon = dynamic_cast<RhythmControlClass*>(owner);
	_Lane = LoadGraph("res/UI/rythm/lane.png");
	_Speaker = LoadGraph("res/UI/rythm/Speakers.png");
	_Point = LoadGraph("res/UI/rythm/Point.png");
	_Time[0] = LoadGraph("res/UI/gamemain/時間制限バー.png");
	_Time[1] = LoadGraph("res/UI/gamemain/1 明_時間制限バー.png");
	_Time[2] = LoadGraph("res/UI/gamemain/2 明_時間制限バー.png");
	_Time[3] = LoadGraph("res/UI/gamemain/3 明_時間制限バー.png");
	_Time[4] = LoadGraph("res/UI/gamemain/4 明_時間制限バー.png");
	_Time[5] = LoadGraph("res/UI/gamemain/5 明_時間制限バー.png");
	_Time[6] = LoadGraph("res/UI/gamemain/6 明_時間制限バー.png");
	auto scene = dynamic_cast<SceneMain*>(_Owner->GetScene());
	if (scene != nullptr) {
		scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2, SCREEN_H / 2 + 415, 0), 50);
		scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2, SCREEN_H / 2 + 490, 0), 50);
		scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2+70, SCREEN_H / 2 + 430, 0), 51);
		scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2+70, SCREEN_H / 2 + 490, 0), 51);
		scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2-70, SCREEN_H / 2 + 430, 0), 52);
		scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2-70, SCREEN_H / 2 + 490, 0), 52);
		scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2 + 120, SCREEN_H / 2 + 370, 0), 53);
		scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2 - 120, SCREEN_H / 2 + 370, 0), 54);

	}
}

NoteSpriteComponent::~NoteSpriteComponent()
{
	DeleteGraph(_Lane);
	DeleteGraph(_Speaker);

}

void NoteSpriteComponent::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawGraph(0, 950, _Lane, TRUE);
	DrawGraph(775, 910, _Point, TRUE);
	DrawGraph(SCREEN_W - 775 - 140, 910, _Point, TRUE);
	if (CheckSoundMem(_RhythmCon->GetBGMHandle()) == FALSE) {
		DrawGraph(SCREEN_W / 2 - 250, 29 + 130 - 40, _Time[0], TRUE);
	}

	else { DrawGraph(SCREEN_W / 2 - 250, 29 + 130 - 40, _Time[(GetSoundCurrentTime(_RhythmCon->GetBGMHandle()) * 6 - 1)/GetSoundTotalTime(_RhythmCon->GetBGMHandle()) + 1], TRUE); }

	int tmp1 = GetSoundCurrentTime(_RhythmCon->GetBGMHandle());
	int tmp2 = GetSoundTotalTime(_RhythmCon->GetBGMHandle());


	auto mt = _RhythmCon->GetMeasureTime();
	

	if (CheckSoundMem(_RhythmCon->GetBGMHandle()) == 1) {
	auto nt = _RhythmCon->GetNotes();
	auto fr = _Owner->GetScene()->GetFPSCon()->GetFrameNum();
	for (auto i = 0; i < 2; i++) {
		int r, g, b;
		GetColor2(_Owner->GetScene()->GetPlayer(i)->GetMyColor(), &r, &g, &b);
		SetDrawBright(255-r, 255-g , 255-b);
		SetDrawBlendMode(DX_BLENDMODE_ADD, 150);
		if (i == 0) {
			DrawBox(_RhythmCon->GetInopTime(i, 2) + _DrawX, 1010 - _DrawY, _RhythmCon->GetInopTime(i, 0) + _DrawX, 1010 + _DrawY, GetColor(255, 255, 255), TRUE);
			SetDrawBright(255, 255, 255);
			DrawBox(_RhythmCon->GetInopTime(i, 0) + _DrawX, 1010 - _DrawY, _RhythmCon->GetInopTime(i, 1) + _DrawX, 1010 + _DrawY, GetColor(150, 150, 150), TRUE);
		}
		else {
			DrawBox(SCREEN_W - (_RhythmCon->GetInopTime(i, 2) + _DrawX), 1010 - _DrawY, SCREEN_W - (_RhythmCon->GetInopTime(i, 0) + _DrawX), 1010 + _DrawY, GetColor(255, 255, 255), TRUE);

			SetDrawBright(255, 255, 255);
			DrawBox(SCREEN_W - (_RhythmCon->GetInopTime(i, 0) + _DrawX), 1010 - _DrawY, SCREEN_W - (_RhythmCon->GetInopTime(i, 1) + _DrawX), 1010 + _DrawY, GetColor(150, 150, 150), TRUE);
		}

		for (const auto& iter : nt[i]) {
			if (iter.easingcnt >= mt) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - ((iter.easingcnt - mt) / 80.0f * 255)); }
			else {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}		

			if (iter.notetype == -2) {}
			else {
				if (i == 0) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
					SetDrawBright(255, 255, 255);
					DrawBox(iter.x - _DrawX, 1010 - _DrawY, iter.x - _DrawX+31, 1010 - _DrawY + 104, _Owner->GetScene()->GetPlayer(0)->GetMyColor(), TRUE);
					SetDrawBlendMode(DX_BLENDMODE_ADD, 150);
					SetDrawBright(255 - r, 255 - g, 255 - b);
					DrawGraph(iter.x - _DrawX, 1010 - _DrawY, _cgHandle[0], TRUE);
				}
				else {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
					SetDrawBright(255, 255, 255);
					DrawBox(1920 - iter.x - _DrawX, 1010 - _DrawY, 1920 - iter.x - _DrawX + 31, 1010 - _DrawY + 104, _Owner->GetScene()->GetPlayer(1)->GetMyColor(), TRUE);
					SetDrawBlendMode(DX_BLENDMODE_ADD, 150);
					SetDrawBright(255 - r, 255 - g, 255 - b);
					DrawGraph(1920 - iter.x - _DrawX, 1010 - _DrawY, _cgHandle[0], TRUE);
				}
				if (fabs(iter.easingcnt - _RhythmCon->GetMeasureTime()) <= fr * 20.0f) {
					SetDrawBlendMode(DX_BLENDMODE_ADD, 100);

					if (i == 0) {
						DrawGraph(iter.x - _DrawX, 1010 - _DrawY, _cgHandle[0], TRUE);
					}
					else {
						DrawGraph(1920 - (iter.x + _DrawX), 1010 - _DrawY, _cgHandle[0], TRUE);
					}
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				}
		}
	}
	SetDrawBright(255, 255, 255);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		if (i == 0) {
			DrawBox(_RhythmCon->GetInopTime(i ,1) + _DrawX, 1010 - _DrawY, SCREEN_W / 2, 1010 + _DrawY, GetColor(0,0,0), TRUE);
		}
		else {
			DrawBox(1920 - (_RhythmCon->GetInopTime(i , 1) + _DrawX), 1010 - _DrawY, SCREEN_W / 2, 1010 + _DrawY, GetColor(0,0,0), TRUE);
		}
		
	}
	SetDrawBright(255, 255, 255);
	//DrawGraph(DrawCenter.x - _DrawX, 1000 - _DrawY, _cgHandle[1], FALSE);
	}
	else {

	}

	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(858, 908, _Speaker, TRUE);
}

void NoteSpriteComponent::SetImage(const TCHAR* filename) {
	_cgHandle.emplace_back(LoadGraph("res/UI/rythm/note.png"));
}