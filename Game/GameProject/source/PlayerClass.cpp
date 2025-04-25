#include "PlayerClass.h"
#include "PlayerSpriteComponent.h"
#include "SceneMain.h"
#include "SceneBase.h"
#include "MotionComponent.h"
#include "vector"
#include "deque"
#include "ioJson.h"
#include "EffectClass.h"
#include "SoundManager.h"
#include "SoundItem.h"


PlayerClass::PlayerClass(SceneBase* scene, bool No, int type)
	:ActorClass(scene)
	, _MotionID(MotionComponent::MotionID::MOT_R_STAND)
	, _NoteType(-1)
	, _PlayerNo(No)
	, _Type(type)
	, _Damage(FALSE)
	, _BulletF(FALSE)
	,_MotTrgFlag(FALSE)
	, IsCPU(No)
	, _StopFrameCnt(0)
	, _MaxHp(1000)
	,_StunTime(0)
	,_InvFlag(FALSE)
	,_SACnt(0)
	,_HitPosition(VGet(0,0,0))
	,_ComboFlag(FALSE)
	,_SlowFlag(0)
	,_Volume(3)
	,_JGFlag(FALSE)
	//,_MotChangeF(0)
{

	_HP = _MaxHp;

	int EnType = GetScene()->GetCommonData()->_PlayerSelectChara[1 - _PlayerNo];
	switch (type) {
	case 0:
		_MaxHp = 1000;
		switch (EnType) {
		//case 0:
			//_Color = GetColor(110, 27, 255);
			//break;
		case 1:
			_Color = GetColor(110, 27, 255);
			break;
		case 2:
			_Color = GetColor(142, 89, 240);
			break;
		case 3:
			_Color = GetColor(31, 15, 174);
			break;
		case 4:
			_Color = GetColor(205,150,244);
			break;
		default :
		_Color = GetColor(140, 0, 255);
		break;
		}
		break;
	case 1:
		_MaxHp = 1000;
		switch (EnType) {
		case 0:
			_Color = GetColor(255, 181, 48);
			break;
		//case 1:
			//_Color = GetColor(110, 27, 255);
			//break;
		case 2:
			_Color = GetColor(213,194,118);
			break;
		case 3:
			_Color = GetColor(255,198,135);
			break;
		case 4:
			_Color = GetColor(255,205,100);
			break;
		default:
		_Color = GetColor(255,153,0);
		break;
		}
		break;
	case 2:
		_MaxHp = 1000;
		switch (EnType) {
		case 0:
			_Color = GetColor(26,189,195);
			break;
		case 1:
			_Color = GetColor(48,154,34);
			break;
		//case 2:
			//_Color = GetColor(213, 194, 118);
			//break;
		case 3:
			_Color = GetColor(154,251,150);
			break;
		case 4:
			_Color = GetColor(116,244,46);
			break;
		default:
		_Color = GetColor(63,255,127);
		break;
		}
		break;
	case 3:
		_MaxHp = 1150;
		switch (EnType) {
		case 0:
			_Color = GetColor(232,144,255);
			break;
		case 1:
			_Color = GetColor(229,106,194);
			break;
		case 2:
			_Color = GetColor(211,102,184);
			break;
		//case 3:
			//_Color = GetColor(154, 251, 150);
			//break;
		case 4:
			_Color = GetColor(225,173,240);
			break;
		default:
		_Color = GetColor(255,176,255);
		break;
		}
		break;
	case 4:
		_MaxHp = 650;
		switch (EnType) {
		case 0:
			_Color = GetColor(167,12,18);
			break;
		case 1:
			_Color = GetColor(185,18,21);
			break;
		case 2:
			_Color = GetColor(185,16,18);
			break;
		case 3:
			_Color = GetColor(196,15,38);
			break;
		//case 4:
			//_Color = GetColor(225, 173, 240);
			//break;
		default:
		_Color = GetColor(199,0,0);
		break;
		}
		break;
	case 5:
		_MaxHp = 1150;
		_Color = GetColor(78,87,182);
		break;
	}

	_MaxHp *= 2;
	std::string path = "res/chara0";
	path += std::to_string(_Type) + "/";
	// モーションデータのロード
	if (!GetScene()->GetCommonData()->_CopyData.empty() && No == 0) {
		_MotionDate = GetScene()->GetCommonData()->_CopyData;
	}
	else {
		iojson::InputMotionFrameJson(path, _MotionDate);
		sndManager.AddSound(new SoundItemSE(path + "se/attackhit1.mp3", std::to_string(type) + "1"));
		sndManager.AddSound(new SoundItemSE(path + "se/walkse.mp3", std::to_string(type) + "2"));
		sndManager.AddSound(new SoundItemSE(path + "se/NSs.mp3", std::to_string(type) + "3"));
		sndManager.AddSound(new SoundItemSE(path + "se/NSf.mp3", std::to_string(type) + "4"));
		sndManager.AddSound(new SoundItemSE(path + "se/バタンと倒れる音.mp3", std::to_string(type) + "5"));
		sndManager.AddSound(new SoundItemSE(path + "se/jump.mp3", std::to_string(type) + "6"));
		sndManager.AddSound(new SoundItemSE(path + "se/gen.m4a", std::to_string(type) + "7"));
		sndManager.AddSound(new SoundItemSE(path + "voice/11.wav", std::to_string(type) + "8"));
		sndManager.AddSound(new SoundItemSE(path + "voice/12.wav", std::to_string(type) + "9"));
		sndManager.AddSound(new SoundItemSE(path + "voice/13.wav", std::to_string(type) + "10"));
		sndManager.AddSound(new SoundItemSE(path + "voice/14.wav", std::to_string(type) + "11"));
		sndManager.AddSound(new SoundItemSE(path + "se/Grap_Try.mp3", std::to_string(type) + "13"));
	}

	_FrameCnt = 0;
	_Stand = TRUE;
	_Move = VGet(0, 0, 0);

	VECTOR pos = VGet(-1000, GROUND_HEIGHT, 0);
	if (_PlayerNo == 1) {pos=VGet(1000, GROUND_HEIGHT, 0);
	}
	_MotionID = _PlayerNo;

	SetPosition(pos);

	// スプライト作成
	PlayerSpriteComponent* sc = new PlayerSpriteComponent(this);
	sc->SetImage("res/test.png");
	PlayerUISpriteComponent* ui = new PlayerUISpriteComponent(this,200);

	mc = new MotionComponent(this);

	

}

PlayerClass::~PlayerClass()
{
	if (GetScene()->GetCommonData()->_IsDuoMode == false&& GetScene()->GetCommonData()->_CopyData.empty()) {
		GetScene()->GetCommonData()->_CopyData = _MotionDate;
	}
	auto s = _MotionDate.size();
	for (auto i = 0; i < s; i++) {
		auto ss = _MotionDate[0].size();
		for (auto j = 0; j < ss; j++) {
			if (GetScene()->GetCommonData()->_IsDuoMode == false && _PlayerNo == 0) {}
			else {
				DeleteGraph(_MotionDate[0].front().cg);
				DeleteGraph(_MotionDate[0].front().mask);
			}
			_MotionDate[0].erase(_MotionDate[0].begin());
		}
		_MotionDate.erase(_MotionDate.begin());
	}
}

// プレイヤーの移動処理
void PlayerClass::UpdateActor() {

	_Damage = 0;		//ダメージフラグの初期化
	_BulletF = FALSE;	//弾被弾フラグの初期化

	_EnMotionID = GetScene()->GetPlayer(1 - _PlayerNo)->GetMotionID();
	_EnArrow = 0;
	if (_Position.x > GetScene()->GetPlayer(1 - _PlayerNo)->GetPosition().x) { _EnArrow = 1; }

	if (_StunTime > 0) {
		if (GetScene()->GetFPSCon()->GetUpdateFlag() == TRUE) {
		_StunTime--;
		}
		if (GetScene()->GetFPSCon()->GetSession() <= 0) {
			_DrawPosition = VAdd(GetPosition(), VGet(3 * (10 + _StunTime) * cos(_StunTime * 4 * atan(1)), 0, 0));
		}
		return;
	}
	if (_EnMotionID == MotionComponent::MOT_L_GRAB_SUC ||
		_EnMotionID == MotionComponent::MOT_R_GRAB_SUC) {
		return;
	}
	// 移動ベクトルの反映と初期化
	if (_SlowFlag > 0) {
		_Position.x += _Move.x / 12 / GetScene()->GetFPSCon()->GetFrameNum();
		_Position.y += _Move.y / 12 / GetScene()->GetFPSCon()->GetFrameNum();
		if (_Stand == FALSE) {
			_Move.y += GRAVITY / 10.0f / GetScene()->GetFPSCon()->GetFrameNum();
		}
		if (_SlowFlag == 1&& GetScene()->GetFPSCon()->GetUpdateFlag() == TRUE) {
			/////////////////_Position.x += _Move.x;
			//////////////////////////_Position.y += _Move.y;
			if (_Stand == FALSE) {
				/////_Move.y += GRAVITY;
			}
		}
	}
	else if (GetScene()->GetFPSCon()->GetUpdateFlag() == FALSE) {
		return;
	}

	if (_SlowFlag <= 1 && GetScene()->GetFPSCon()->GetUpdateFlag() == TRUE) {
		_OldPosition.emplace_front(GetPosition());
		_OldFrame.emplace_front(GetFrame());
		if (_OldPosition.size() > FRAME_NUM) {
			_OldPosition.pop_back();
			_OldFrame.pop_back();
		}
	}




	if(_SlowFlag==0){
		_Position.x += _Move.x;
		_Position.y += _Move.y;
		if (_Stand == FALSE) {
			if (_Move.y < 250) {
				if (_MotionID == MotionComponent::MOT_R_DAMAGE_FLY ||
					_MotionID == MotionComponent::MOT_L_DAMAGE_FLY) {
					_Move.y += GRAVITY / 2;
				}
				else {
					_Move.y += GRAVITY;
				}

				if (_Move.y > 250) {
					_Move.y = 250;
				}
			}

		}
	}

	// 相手のプレイヤーからの移動制限
	if (_Position.y > GROUND_HEIGHT) {
		_Move.y = 0;
		_Position.y = GROUND_HEIGHT;
		if (_SlowFlag <= 1) {
		_Stand = TRUE;
		if (_MotionID == MotionComponent::MOT_R_DAMAGE_FLY) {
			SetMotionID(MotionComponent::MOT_R_DAMAGE_RISE);
			sndManager.GetSound(std::to_string(_Type) + "5")->Play();
		}
		else if (_MotionID == MotionComponent::MOT_L_DAMAGE_FLY) {
			SetMotionID(MotionComponent::MOT_L_DAMAGE_RISE);
			sndManager.GetSound(std::to_string(_Type) + "5")->Play();
		}
		else if (_MotionID == MotionComponent::MOT_L_DAMAGE_FLY ||
			_MotionID == MotionComponent::MOT_R_DAMAGE_FLY) {
		}
		else {
			SetMotionID(MotionComponent::MOT_R_STAND + 0.5 - 0.5 * mc->GetArrow());
			sndManager.GetSound(std::to_string(_Type) + "6")->Play();
		}
		SetMove(VGet(0, 0, 0));
		auto scene = dynamic_cast<SceneMain*>(GetScene());
		scene->GetEffectCon()->AddEffect(GetPosition(), 12);
		
	}
		else { SetMove(VGet(0, 0, 0)); }
	
	}
	float enemyX = GetScene()->GetPlayer(1 - _PlayerNo)->GetPosition().x;
	float moveX;
	if (_Stand == TRUE&& GetScene()->GetPlayer(1 - _PlayerNo)->GetStandFlag()==TRUE&&GetFrame().type<40000&& GetScene()->GetPlayer(1 - _PlayerNo)->GetFrame().type < 40000) {
		if (_Position.x >= enemyX && _Position.x - enemyX < 300) {
			moveX = (300 - (_Position.x - enemyX)) / 2;
			_Position.x += moveX;
			GetScene()->GetPlayer(1 - _PlayerNo)->SetPosition(VGet(enemyX - moveX, GetScene()->GetPlayer(1 - _PlayerNo)->GetPosition().y, 0));
		}
		if (_Position.x < enemyX && enemyX - _Position.x < 300) {
			moveX = -(300 + (_Position.x - enemyX)) / 2;
			_Position.x += moveX;
			GetScene()->GetPlayer(1 - _PlayerNo)->SetPosition(VGet(enemyX - moveX, GetScene()->GetPlayer(1 - _PlayerNo)->GetPosition().y, 0));
		}
	}

	if (_Position.x > enemyX && _Position.x - enemyX > 3000)
	{
		_Position.x -= (_Position.x - (enemyX + 3000)) / 2;
		GetScene()->GetPlayer(1 - _PlayerNo)->SetPosition(VGet(_Position.x - 3000, GetScene()->GetPlayer(1 - _PlayerNo)->GetPosition().y, 0));
	}
	if (_Position.x < enemyX && enemyX - _Position.x > 3000)
	{
		_Position.x -= (_Position.x - (enemyX - 3000)) / 2;
		GetScene()->GetPlayer(1 - _PlayerNo)->SetPosition(VGet(_Position.x + 3000, GetScene()->GetPlayer(1 - _PlayerNo)->GetPosition().y, 0));
	}

	_DrawPosition = GetPosition();

}

void PlayerClass::Init()
{
	_NoteType = -1;
	_Damage = FALSE;
	_BulletF = FALSE;
	_MotTrgFlag = FALSE;
	_StopFrameCnt = 0;
	_HP = _MaxHp;
	_StunTime = 0;
	//_InvFlag = FALSE;
	_SACnt = 0;
	_HitPosition = VGet(0, 0, 0);
	_ComboFlag = FALSE;
	_FrameCnt = 0;
	_Stand = TRUE;
	_Move = VGet(0, 0, 0);
	_MotionID = _PlayerNo;
	_SlowFlag = 0;

	VECTOR pos = VGet(-1000, GROUND_HEIGHT, 0);
	if (_PlayerNo == 1) { pos = VGet(1000, GROUND_HEIGHT, 0); }
	SetPosition(pos);
}

void PlayerClass::SetMotionID(const int motionid, bool flag)
{
	if (_MotionID == motionid) { 
		switch (_MotionID) {
		case MotionComponent::MOT_R_DAMAGE:
		case MotionComponent::MOT_L_DAMAGE:
		case MotionComponent::MOT_R_DAMAGE_CROUCH:
		case MotionComponent::MOT_L_DAMAGE_CROUCH:
		case MotionComponent::MOT_R_DAMAGE_FLY:
		case MotionComponent::MOT_L_DAMAGE_FLY:
			break;
		default:
			return;
		}
	}
	 _FrameCnt = 0; 
	 if (_MotTrgFlag == TRUE) {
		 SetVolume(12);
	 }
	 auto scene = dynamic_cast<SceneMain*>(GetScene());
	 scene->GetEffectCon()->ResetMotEffect(_PlayerNo);


	 if (_MotionID == MotionComponent::MOT_R_DAMAGE_RISE ||
		 _MotionID == MotionComponent::MOT_L_DAMAGE_RISE) {
		 if (_Type == 5) {
			 _HP = _MaxHp;
		 } 
	 }




	 if (GetMotTrgFlag() == TRUE) {
		 _SACnt /= 2;
	 }

	 if (motionid == MotionComponent::MOT_R_DAMAGE_FLY ||
		 motionid == MotionComponent::MOT_L_DAMAGE_FLY) {
		 _Stand = FALSE;
	 }



	 if (_HP <= 0) {
		 _StunTime = 0;
		 if (motionid == MotionComponent::MOT_R_DAMAGE) {
			 _MotionID = MotionComponent::MOT_R_DAMAGE_FLY;
			 _Stand = FALSE;
			 return;
		 }
		 else if (motionid == MotionComponent::MOT_L_DAMAGE) {
			 _MotionID = MotionComponent::MOT_L_DAMAGE_FLY;
			 _Stand = FALSE;
			 return;
		 }
		 else if (motionid != MotionComponent::MOT_R_DAMAGE_RISE &&
			 motionid != MotionComponent::MOT_L_DAMAGE_RISE) {
			 _MotionID = MotionComponent::MOT_R_DAMAGE_FLY + (VNorm(VSub(_Position, GetScene()->GetPlayer(1 - _PlayerNo)->GetPosition())).x + 1) / 2;
			 _Stand = FALSE;
			 return;
		 }
		 _MotionID = motionid;
		 return;
	 }


	 _MotionID = motionid; 
	 if (motionid == MotionComponent::MOT_R_STAND || motionid == MotionComponent::MOT_L_STAND) {
		 float frameCnt = (float)GetScene()->GetFPSCon()->GetFrameCnt();
		 while (frameCnt > 4 * FRAME_NUM) {
			 frameCnt -= 4 * FRAME_NUM;
		 }
		 _FrameCnt = frameCnt/ (4.0f * FRAME_NUM) * (_MotionDate[MotionComponent::MOT_R_STAND].size()-1);
	 }

	 if (motionid >= MotionComponent::MOT_R_ATTACK2_STAND_SUC
		 && motionid <= MotionComponent::MOT_L_ATTACK2_COMBO2_SUC) {
		 if (motionid == MotionComponent::MOT_R_ATTACK2_JUMP_SUC ||
			 motionid == MotionComponent::MOT_L_ATTACK2_JUMP_SUC) {
			 GetScene()->ChangeTension(3 * (_PlayerNo * 2 - 1));
		 }
		 else {
			 GetScene()->ChangeTension(5 * (_PlayerNo * 2 - 1));
	 }
	 }
	 if (motionid == MotionComponent::MOT_R_STEP_SUC) {
		 if (GetPosition().x < GetScene()->GetPlayer(1 - _PlayerNo)->GetPosition().x) {		//NSで相手に近づいたとき
			 GetScene()->ChangeTension(3 * (_PlayerNo * 2 - 1));				//テンションを増加
		 }
		 _SACnt = 255;										//スーパーアーマーを付与
	 }
	 if ( motionid == MotionComponent::MOT_L_STEP_SUC) {
		 if (GetPosition().x > GetScene()->GetPlayer(1 - _PlayerNo)->GetPosition().x) {		//NSで相手に近づいたとき
			 GetScene()->ChangeTension(3 * (_PlayerNo * 2 - 1));				//テンションを増加
		 }
		 _SACnt = 255;										//スーパーアーマーを付与
	 }
	 if (motionid == MotionComponent::MOT_R_STEP_FAIL || motionid == MotionComponent::MOT_L_STEP_FAIL) {
		 GetScene()->ChangeTension(-5 * (_PlayerNo * 2 - 1));
		 _SACnt = 0;
	 }



	 int type =GetFrame().type;
	 if (type % 100 >= 22 && type % 100 <= 67) {
		 if (_MotionID % 2 == 1) {
			 scene->GetEffectCon()->AddEffect(GetPosition(), type % 100 + 40 * _PlayerNo);
		 }
		 else {
			 scene->GetEffectCon()->AddEffect(GetPosition(), type % 100 + 1 + 40 * _PlayerNo);
		 }
	 }
	 if (type % 10000 >= 100) {
		 auto tmp = (type / 100) % 100;
		 sndManager.GetSound(std::to_string(_Type) + std::to_string(tmp))->Play();
	 }
	 if (motionid >= MotionComponent::MOT_R_ATTACK2_STAND_SUC && motionid <= MotionComponent::MOT_L_ATTACK2_COMBO2_SUC || motionid >= MotionComponent::MOT_R_STEP_SUC && motionid <= MotionComponent::MOT_L_STEP_SUC) {
		 scene->GetRhythm()->SucFrontNote(_PlayerNo , flag);
		 SetVolume(20);
	 }
	 
}


//フレームデータの取得(revに反転してるかを記載、rev=1で渡すとそのままの値)
MOTION_FRAME PlayerClass::GetFrame(int i)
{
	if (_MotionDate[_MotionID].size() <= 0) {
		return _MotionDate[_MotionID%2][0];
	}
	return _MotionDate[_MotionID][_FrameCnt + i];
}
//フレームを進める、モーションが終わる場合FALSE
bool PlayerClass::FrameProcess()
{
	if (_SlowFlag > 1) {
		return TRUE;
	}
	if (GetScene()->GetFPSCon()->GetUpdateFlag() == TRUE) {
		if (_Volume > 3) {
			_Volume--;
		}
		else {
			_Volume = 3;
		}
	}
	//_MotChangeF = FALSE;
	if (_StunTime > 0) {
		_Volume = 0;
		return TRUE;
	}

	if (_EnMotionID == MotionComponent::MOT_L_GRAB_SUC ||
		_EnMotionID == MotionComponent::MOT_R_GRAB_SUC) {
		return TRUE;
	}
	_SACnt--;


	auto scene = dynamic_cast<SceneMain*>(GetScene());
	_FrameCnt++;
	if (_FrameCnt < size(_MotionDate[_MotionID])) {
		int type = GetFrame().type;
		if (type % 100 >= 22 && type % 100 <= 67) {
			if (_MotionID % 2 == 1) {
				scene->GetEffectCon()->AddEffect(GetPosition(), type % 100 + 40 * _PlayerNo);
			}
			else {
				scene->GetEffectCon()->AddEffect(GetPosition(), type % 100 + 1 + 40 * _PlayerNo);
			}
		}
		if (type % 10000 >= 100) {
			auto tmp = (type / 100) % 100;
			sndManager.GetSound(std::to_string(_Type) + std::to_string(tmp))->Play();
		}
	}
	if (_HP <= 0) {
		if (_MotionID == MotionComponent::MOT_L_DAMAGE_RISE ||
			_MotionID == MotionComponent::MOT_R_DAMAGE_RISE) {
			if (_FrameCnt > 5) {
				_FrameCnt--;
				_Volume = 0;
				return TRUE;
			}
		}
	}
	if (_MotionID < MotionComponent::MOT_R_ATTACK1_STAND &&
		_MotionID > MotionComponent::MOT_L_GRAB_SUC) {
		_ComboFlag = FALSE;
	}

	if (_FrameCnt >= size(_MotionDate[_MotionID])) {
		_ComboFlag = FALSE;
		if (_MotionID == MotionComponent::MOT_R_DAMAGE_FLY ||
			_MotionID == MotionComponent::MOT_L_DAMAGE_FLY) {
			_FrameCnt--;
			return TRUE;
		}
		mc->SetArrow(_MotionID % 2 * -2 + 1);	
		_FrameCnt = 0;
		if (_MotionID==MotionComponent::MOT_R_DAMAGE_FLY) {
			SetMotionID(MotionComponent::MOT_R_DAMAGE_RISE);

			sndManager.GetSound(std::to_string(_Type) + "6")->Play();
			
			return TRUE;
		}
		if (_MotionID == MotionComponent::MOT_L_DAMAGE_FLY) {
			SetMotionID(MotionComponent::MOT_L_DAMAGE_RISE);
			sndManager.GetSound(std::to_string(_Type) + "6")->Play();
			return TRUE;
		}

		return FALSE;
		
	}
	return TRUE;
}

// 攻撃の当たり判定
void PlayerClass::MotionUpdate()
{
	auto scene = dynamic_cast<SceneMain*>(GetScene());

	int HitCnt = 0;

	//当たり判定

	MOTION_FRAME player = GetFrame();
	MOTION_FRAME enemy = GetScene()->GetPlayer(1 - _PlayerNo)->GetFrame();


	for (int i = 0; i < player.hit.size(); i++) {
		for (int j = 0; j < enemy.at.size(); j++) {
			if (VSize(VGet(player.hit[i].r.x, player.hit[i].r.y, 0)) != 0 && VSize(VGet(enemy.at[j].r.x, enemy.at[j].r.y, 0)) != 0) {
				VECTOR tmp = VAdd(enemy.at[j].pos, GetScene()->GetPlayer(1 - _PlayerNo)->GetPosition());
				if (CheckHitSome(VAdd(player.hit[i].pos, _Position), player.hit[i].r, player.hit[i].rotate,
					VAdd(enemy.at[j].pos, GetScene()->GetPlayer(1 - _PlayerNo)->GetPosition()), enemy.at[j].r, enemy.at[j].rotate) == 1) {
					HitCnt++;
					if (_BulletF == FALSE && HitCnt <= 1&&_InvFlag==FALSE) { 
						_EnShock = enemy.at[j].shock;
						_Damage = (abs(_PlayerNo*100-(float)GetScene()->GetTension())/100* enemy.at[j].damage1+
						abs((1 - _PlayerNo) *100 - (float)GetScene()->GetTension()) / 100 * enemy.at[j].damage2);
						GetScene()->GetPlayer(1 - _PlayerNo)->SetVolume(12);

						_EnHitPos = enemy.at[j].pos;
						int type = 1;
						int enID = GetScene()->GetPlayer(1 - _PlayerNo)->GetMotionID();
						if (MotionComponent::MOT_R_ATTACK2_STAND_SUC <= enID && enID <= MotionComponent::MOT_L_GRAB_SUC) {
							type = 2 + 1 - _PlayerNo;
						}
						if (enID == MotionComponent::MOT_R_GRAB_SUC || enID == MotionComponent::MOT_L_GRAB_SUC) {
							if (scene->GetTension() == 100 * (1-_PlayerNo)) { _Damage = _MaxHp; }
						}

						if (GetFrame().type < 40000) {
						VECTOR pos = VAdd(VScale(VAdd(player.hit[i].pos, _Position),1), VScale(VAdd(enemy.at[j].pos, GetScene()->GetPlayer(1 - _PlayerNo)->GetPosition()),0));
					scene->GetEffectCon()->AddEffect(pos,type);
					scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W/2, SCREEN_H/2, 0), 60);
					if (type != 1) { 
						scene->GetEffectCon()->AddScreenEffect(VGet(SCREEN_W / 2, SCREEN_H / 2, 0), 60+type ); 
						scene->GetEffectCon()->AddEffect(pos, type + 2);
					}
						}

					if (GetScene()->GetPlayer(1-_PlayerNo)->GetNotesType()!=-1) {
						GetScene()->ChangeTension(-5 * (_PlayerNo * 2 - 1));
					}
				}
					
			}
		}
	}
	}
	if (HitCnt <= 0) {
		_InvFlag = FALSE;
	}
	//delete[] TmpHit;
	//delete[] TmpAt;

}

// ダメージの反映と打ち消し処理
void PlayerClass::DamageUpdate()
{
		int EnDamage = GetScene()->GetPlayer(1 - _PlayerNo)->_Damage;

	if (_InvFlag == TRUE) { 
		_Damage = 0;
		return; 
	}
	if (_Damage>0) {
		if (GetFrame().type >= 40000) { 
			if (GetFrame().type < 50000 && _JGFlag ==FALSE) {
				_JGFlag = TRUE;
				_InvFlag = TRUE;
				sndManager.GetSound("justguard")->Play();
			GetScene()->ChangeTension(10 * (_PlayerNo * 2 - 1));
			GetScene()->GetFPSCon()->StartSession();
			_HitPosition = GetPosition();
			_HitFrame = GetFrame();
			}
			_Damage = 0;
			return; 
		}		//コンボに派生しない

		else { _InvFlag = TRUE; }

		if (_JGFlag == TRUE) {
			if (GetFrame().type < 40000 || GetFrame().type >= 50000) {
				_JGFlag = FALSE;
			}
		}

		GetScene()->GetPlayer(1 - _PlayerNo)->SetComboFlag(TRUE);
		if (_BulletF == TRUE) {
			return;
		}
		//VECTOR EnShock = GetScene()->GetPlayer(1 - _PlayerNo)->GetOldFrame().at[0].shock;
		VECTOR OldMove = GetMove();
		bool OldStand = _Stand;
		if (OldMove.x == 0) { OldMove.x = 0.1; }
		if (OldMove.y == 0) { OldMove.y = -0.1; }

		SetMove(VGet(_EnShock.x * (_EnArrow*2-1), _EnShock.y, 0));	//相手の吹き飛ばしベクトル

		if (EnDamage > 0) {
			if (_EnMotionID == MotionComponent::MOT_R_GRAB_TRY ||			//相手が掴み攻撃の時
				_EnMotionID == MotionComponent::MOT_L_GRAB_TRY) {

				if (_MotionID == MotionComponent::MOT_R_GRAB_TRY ||			//掴み攻撃の時
					_MotionID == MotionComponent::MOT_L_GRAB_TRY) {
					SetMotionID(MotionComponent::MOT_R_DAMAGE + _EnArrow);
				}
				else if (_MotionID >= MotionComponent::MOT_R_ATTACK1_STAND &&			//言葉攻撃の時
					_MotionID <= MotionComponent::MOT_L_ATTACK1_CROUCH_COMBO) {
				}
				else if (_Stand != TRUE) {
					SetMotionID(MotionComponent::MOT_R_DAMAGE_FLY + _EnArrow);
				}
				else {
					GetScene()->GetPlayer(1 - _PlayerNo)->SetMotionID(MotionComponent::MOT_R_GRAB_SUC + GetScene()->GetPlayer(1 - _PlayerNo)->GetMotionID() % 2);
				}
			}

			else {
				if (_MotionID == MotionComponent::MOT_R_GRAB_TRY ||			//掴み攻撃の時
					_MotionID == MotionComponent::MOT_L_GRAB_TRY) {
					_HP -= _Damage;
					if (_EnMotionID >= MotionComponent::MOT_R_ATTACK1_STAND &&			//相手が言葉攻撃の時
						_EnMotionID <= MotionComponent::MOT_L_ATTACK1_CROUCH_COMBO) {
						SetMotionID(MotionComponent::MOT_R_DAMAGE + _EnArrow);
					}
				}


				if (_MotionID >= MotionComponent::MOT_R_ATTACK1_STAND			//言攻撃の時
					&& _MotionID <= MotionComponent::MOT_L_ATTACK1_CROUCH_COMBO) {
					if (_EnMotionID >= MotionComponent::MOT_R_ATTACK1_STAND		//相手も言葉攻撃
						&& _EnMotionID <= MotionComponent::MOT_L_ATTACK1_CROUCH_COMBO) {
						if (_Damage > EnDamage) {
							_HP += EnDamage - _Damage;					//差分ダメージ、ノーツ失敗時ひるみ
						}
						if (GetNotesType() == -1) {
							switch (_MotionID) {
							case MotionComponent::MOT_R_CROUCH:
							case MotionComponent::MOT_L_CROUCH:
							case MotionComponent::MOT_R_ATTACK1_CROUCH:
							case MotionComponent::MOT_L_ATTACK1_CROUCH:
							case MotionComponent::MOT_R_ATTACK1_CROUCH_COMBO:
							case MotionComponent::MOT_L_ATTACK1_CROUCH_COMBO:
								SetMotionID(MotionComponent::MOT_R_DAMAGE_CROUCH + _EnArrow);
								break;

							case MotionComponent::MOT_R_ATTACK1_JUMP:
							case MotionComponent::MOT_L_ATTACK1_JUMP:
								SetMotionID(MotionComponent::MOT_R_DAMAGE_FLY + _EnArrow);
								break;

							default:
								SetMotionID(MotionComponent::MOT_R_DAMAGE + _EnArrow);
								break;
							}
						}
						else { 
							SetMove(OldMove);
							_Stand = OldStand;
						}
					}
					if (_EnMotionID >= MotionComponent::MOT_R_ATTACK2_STAND_SUC		//相手は成功弦攻撃の時
						&& _EnMotionID <= MotionComponent::MOT_L_ATTACK2_COMBO2_SUC) {
						_HP -= _Damage;									//そのままのダメージ、吹っ飛び
						SetMotionID(MotionComponent::MOT_R_DAMAGE_FLY + _EnArrow);
						if (GetScene()->GetPlayer(1 - _PlayerNo)->GetNotesType() != -1) {
							GetScene()->ChangeTension(-5 * (_PlayerNo * 2 - 1));
						}
						if (_EnMotionID != MotionComponent::MOT_R_ATTACK2_JUMP_SUC &&
							_EnMotionID != MotionComponent::MOT_L_ATTACK2_JUMP_SUC) {
							_StunTime = STUN_TIME;
						}
					}
					if (_EnMotionID >= MotionComponent::MOT_R_ATTACK2_STAND_FAIL	//相手は失敗弦攻撃の時
						&& _EnMotionID <= MotionComponent::MOT_L_ATTACK2_COMBO2_FAIL) {

						if (_Damage > EnDamage) {
							_HP += EnDamage - _Damage;					//差分ダメージ、怯みモーション
						}
						switch (_MotionID) {
						case MotionComponent::MOT_R_CROUCH:
						case MotionComponent::MOT_L_CROUCH:
						case MotionComponent::MOT_R_ATTACK1_CROUCH:
						case MotionComponent::MOT_L_ATTACK1_CROUCH:
						case MotionComponent::MOT_R_ATTACK1_CROUCH_COMBO:
						case MotionComponent::MOT_L_ATTACK1_CROUCH_COMBO:
							SetMotionID(MotionComponent::MOT_R_DAMAGE_CROUCH + _EnArrow);
							break;

						case MotionComponent::MOT_R_ATTACK1_JUMP:
						case MotionComponent::MOT_L_ATTACK1_JUMP:
							SetMotionID(MotionComponent::MOT_R_DAMAGE_FLY + _EnArrow);
							break;

						default:
							SetMotionID(MotionComponent::MOT_R_DAMAGE + _EnArrow);
							break;
						}
					}
				}

				if (_MotionID >= MotionComponent::MOT_R_ATTACK2_STAND_SUC			//成功弦攻撃の時
					&& _MotionID <= MotionComponent::MOT_L_ATTACK2_COMBO2_SUC) {
					if (_EnMotionID >= MotionComponent::MOT_R_ATTACK2_STAND_SUC			//相手も成功弦攻撃の時
						&& _EnMotionID <= MotionComponent::MOT_L_ATTACK2_COMBO2_SUC) {
						if (_SACnt > 0) {
							_SACnt = 1;
							SetMove(OldMove);
							_Stand = OldStand;
							//return;
						}
						else {
						if (GetScene()->GetPlayer(1 - _PlayerNo)->GetSACnt() > 0) {
							_HP -= _Damage;
							SetMotionID(MotionComponent::MOT_R_DAMAGE_FLY + _EnArrow);
							//return;
						}

							else {
						if (_Damage > EnDamage) {
							_HP += EnDamage - _Damage;					//差分ダメージ
						}
						if (GetNotesType() == -1) {
							SetMotionID(MotionComponent::MOT_R_DAMAGE + _EnArrow);
						}
								else {
									SetMove(OldMove);
									_Stand = OldStand;
								}
							}
						} 
					}
				}

				if (_MotionID >= MotionComponent::MOT_R_ATTACK2_STAND_FAIL			//失敗弦攻撃の時
					&& _MotionID <= MotionComponent::MOT_L_ATTACK2_COMBO2_FAIL) {
					if (_EnMotionID >= MotionComponent::MOT_R_ATTACK1_STAND		//相手は言攻撃
						&& _EnMotionID <= MotionComponent::MOT_L_ATTACK1_CROUCH_COMBO) {
						if (_Damage > EnDamage) {
							_HP += EnDamage - _Damage;					//差分ダメージ、モーション変更なし
						}
					}
						if (_EnMotionID >= MotionComponent::MOT_R_ATTACK2_STAND_SUC		//相手は成功弦攻撃の時
							&& _EnMotionID <= MotionComponent::MOT_L_ATTACK2_COMBO2_SUC) {
							_HP -= _Damage;									//そのままのダメージ、吹っ飛び
							SetMotionID(MotionComponent::MOT_R_DAMAGE_FLY + _EnArrow);
						if (GetScene()->GetPlayer(1 - _PlayerNo)->GetNotesType() != -1) {
							GetScene()->ChangeTension(-5 * (_PlayerNo * 2 - 1));
						}
							if (_EnMotionID != MotionComponent::MOT_R_ATTACK2_JUMP_SUC &&
								_EnMotionID != MotionComponent::MOT_L_ATTACK2_JUMP_SUC) {
							_StunTime = STUN_TIME;
							}
						}

						if (_EnMotionID >= MotionComponent::MOT_R_ATTACK2_STAND_FAIL	//相手も失敗弦攻撃の時
							&& _EnMotionID <= MotionComponent::MOT_L_ATTACK2_COMBO2_FAIL) {
						if (_SACnt > 0) {
							_SACnt = 1;
							SetMove(OldMove);
							_Stand = OldStand;
						}
						else {
							if (GetScene()->GetPlayer(1 - _PlayerNo)->GetSACnt() > 0) {
								_HP -= _Damage;
								SetMotionID(MotionComponent::MOT_R_DAMAGE + _EnArrow);
								//return;
							}


							else {
							if (_Damage > EnDamage) {
								_HP += EnDamage - _Damage;					//差分ダメージ、モーション変更なし
							}
							if (GetNotesType() == -1) {
								switch (_MotionID) {
								case MotionComponent::MOT_R_ATTACK2_JUMP_FAIL:
								case MotionComponent::MOT_L_ATTACK2_JUMP_FAIL:
									SetMotionID(MotionComponent::MOT_R_DAMAGE_FLY + _EnArrow);
									break;

								case MotionComponent::MOT_R_ATTACK2_CROUCH_FAIL:
								case MotionComponent::MOT_L_ATTACK2_CROUCH_FAIL:
								case MotionComponent::MOT_R_ATTACK2_CROUCH_COMBO_FAIL:
								case MotionComponent::MOT_L_ATTACK2_CROUCH_COMBO_FAIL:
									SetMotionID(MotionComponent::MOT_R_DAMAGE_CROUCH + _EnArrow);
									break;

								default:
									SetMotionID(MotionComponent::MOT_R_DAMAGE + _EnArrow);
									break;
								}
							}
								else {
									SetMove(OldMove);
									_Stand = OldStand;
								}
							} 
						}
					}

				}
			
			}
			
		}
		else {					//相打ちじゃないとき

			_HP -= _Damage;		//HPを減らす


			if (_MotionID >= MotionComponent::MOT_R_DAMAGE && _MotionID <= MotionComponent::MOT_L_DAMAGE_FLY) {
				if (OldMove.y > GetMove().y) {
					SetMove(VGet(OldMove.x + GetMove().x,OldMove.y, 0));
				}
				else {
					SetMove(VGet(OldMove.x + GetMove().x, GetMove().y, 0));
				}

			}


			if (_SACnt > 0) {
				_SACnt = 0;
				if (_MotionID >= MotionComponent::MOT_R_ATTACK2_STAND_SUC
					&& _MotionID <= MotionComponent::MOT_L_ATTACK2_COMBO2_FAIL) {
					_SACnt = 1;
					SetMove(OldMove);
					_Stand = OldStand;
				}
				if (_EnMotionID == MotionComponent::MOT_R_GRAB_TRY ||
					_EnMotionID == MotionComponent::MOT_L_GRAB_TRY) {
					_SACnt = 0;
				}
			}
			if(_SACnt <= 0) {
			if (_EnMotionID >= MotionComponent::MOT_R_ATTACK2_STAND_SUC
				&& _EnMotionID <= MotionComponent::MOT_L_ATTACK2_COMBO2_SUC) {
				if (_EnMotionID != MotionComponent::MOT_R_ATTACK2_JUMP_SUC &&
					_EnMotionID != MotionComponent::MOT_L_ATTACK2_JUMP_SUC) {
						_StunTime = STUN_TIME;
				}
			}
			if (_EnMotionID >= MotionComponent::MOT_R_ATTACK1_STAND &&
				_EnMotionID <= MotionComponent::MOT_L_ATTACK1_CROUCH_COMBO) {
				if (_EnMotionID != MotionComponent::MOT_R_ATTACK1_JUMP &&
					_EnMotionID != MotionComponent::MOT_L_ATTACK1_JUMP) {
					_StunTime = STUN_TIME / 5;
				}
			}

			//ここに吹き飛ばしを記述

			if (_EnMotionID == MotionComponent::MOT_R_GRAB_SUC ||
				_EnMotionID == MotionComponent::MOT_L_GRAB_SUC) {
				SetMotionID(MotionComponent::MOT_R_DAMAGE_FLY + _EnArrow);
				_StunTime = GetScene()->GetPlayer(1 - _PlayerNo)->GetMotionDataSize() - GetScene()->GetPlayer(1 - _PlayerNo)->GetFrameCnt();
			}

			if (_Stand == FALSE) {
				SetMotionID(MotionComponent::MOT_R_DAMAGE_FLY + _EnArrow);
			}
			else if (_EnMotionID >= MotionComponent::MOT_R_ATTACK2_STAND_SUC
				&& _EnMotionID <= MotionComponent::MOT_L_ATTACK2_COMBO2_SUC) {
				SetMotionID(MotionComponent::MOT_R_DAMAGE_FLY + _EnArrow);
					//GetScene()->ChangeTension(-5 * (_PlayerNo * 2 - 1));
				}
			else if ((_EnMotionID >= MotionComponent::MOT_R_ATTACK1_STAND
				&& _EnMotionID <= MotionComponent::MOT_L_ATTACK1_CROUCH_COMBO)
				||(_EnMotionID >= MotionComponent::MOT_R_ATTACK2_STAND_FAIL
					&& _EnMotionID <= MotionComponent::MOT_R_ATTACK2_COMBO2_FAIL)) {
				if (_EnMotionID == MotionComponent::MOT_R_ATTACK1_COMBO2 ||
					_EnMotionID == MotionComponent::MOT_L_ATTACK1_COMBO2) {
					SetMotionID(MotionComponent::MOT_R_DAMAGE_FLY + _EnArrow);
				}
				else {
					switch (_MotionID) {
					case MotionComponent::MOT_R_CROUCH:
					case MotionComponent::MOT_L_CROUCH:
					case MotionComponent::MOT_R_ATTACK1_CROUCH:
					case MotionComponent::MOT_L_ATTACK1_CROUCH:
					case MotionComponent::MOT_R_ATTACK1_CROUCH_COMBO:
					case MotionComponent::MOT_L_ATTACK1_CROUCH_COMBO:
						SetMotionID(MotionComponent::MOT_R_DAMAGE_CROUCH + _EnArrow);
						break;

					default:
						SetMotionID(MotionComponent::MOT_R_DAMAGE + _EnArrow);
						break;
					}
				}

			}
			else if (_EnMotionID == MotionComponent::MOT_R_GRAB_TRY ||
				_EnMotionID == MotionComponent::MOT_L_GRAB_TRY) {
				GetScene()->GetPlayer(1 - _PlayerNo)->SetMotionID(MotionComponent::MOT_R_GRAB_SUC + (GetScene()->GetPlayer(1 - _PlayerNo)->GetMotionID() % 2));
				SetMotionID(MotionComponent::MOT_R_DAMAGE + _EnArrow);
				_HP += _Damage;
			}

			}

		}
		if (_HP <= 0) {
			SetMotionID(MotionComponent::MOT_R_DAMAGE_FLY + _EnArrow);
		}
	}
	if (_Damage > 0 || EnDamage > 0) {
		_HitPosition = GetPosition();
		_HitFrame = GetFrame();
	}
}



void PlayerClass::SetMove(VECTOR move)
{
	if (move.y != 0.0f) { //空中で止まってほしい場合、0.1を記述
		_Move.y = (int)move.y;
		if (move.y <= -1) {
		_Stand = FALSE;
		}
	}
	if (_MotionID != MotionComponent::MOT_R_DAMAGE && _MotionID != MotionComponent::MOT_L_DAMAGE) {
		if (_Stand == TRUE) { _Move.x = 0; }
	}
	if (move.x != 0.0f) { 
		_Move.x = (int)move.x;
		if (_MotionID >= MotionComponent::MOT_R_STEP_SUC &&
			_MotionID <= MotionComponent::MOT_L_STEP_FAIL) {
			if (GetScene()->GetTension() == (1 - _PlayerNo) * 100) {
				_Move.x /= 2;
			}
		}
	}
}

void PlayerClass::SetVolume(int value)
{
	if (value > _Volume) {
		_Volume =value;
	}
}



