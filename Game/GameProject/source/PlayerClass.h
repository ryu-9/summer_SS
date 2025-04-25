#pragma once
#include "ActorClass.h"
#include "CharaStruct.h"
#include "vector"
#include "MotionComponent.h"
#include "NoteSpriteComponent.h"
#include "PlayerUISpriteComponent.h"
#include "SceneBase.h"

#define GRAVITY	(80)
#define STUN_TIME	(15)
class MotionComponent;


class PlayerClass : public ActorClass {
public:
	PlayerClass(class SceneBase* scene,bool No, int type);
	~PlayerClass();

	void UpdateActor() override;

	void SetMotTrgFlag(bool flag) { _MotTrgFlag = flag; }

	void Init();
	
	// getter
	int GetMotionID() const { return _MotionID; }
	void SetMotionID(const int motionid, bool flag = TRUE);
	int GetPlayerNo() const { return _PlayerNo; };
	int GetNotesType() const { return _NoteType; };
	void SetNotesType(const int ntype) { _NoteType = ntype; }
	int GetHitPoint() const { return _HP; }
	bool GetMotTrgFlag() const { return _MotTrgFlag; }
	MotionComponent* GetMotionCopmponent() { return mc; }
	MOTION_FRAME GetFrame(int i = 0) ;
	bool FrameProcess();
	void MotionUpdate();
	void DamageUpdate();
	int GetDamage() const { return _Damage; }
	int GetMaxHp() const { return _MaxHp; }
	MOTION_FRAME GetHitFrame() { return _HitFrame; }
	VECTOR GetHitPosition() { return _HitPosition; }
	VECTOR GetDrawPosition() const { return _DrawPosition; }
	VECTOR GetEnHitPos() const { return _EnHitPos; }
	int GetSACnt() const { return _SACnt; }
	int GetStunTime() const { return _StunTime; }
	bool GetComboFlag() const { return _ComboFlag; }
	void SetComboFlag(const bool flag) { _ComboFlag = flag; }
	int GetType() { return _Type; }
	std::deque<VECTOR>* GetOldPosition() { return &_OldPosition; }
	std::deque<MOTION_FRAME>* GetOldFrame() { return &_OldFrame; }
	unsigned int GetMyColor() { return _Color; }
	void SetSlowFlag(int num) { _SlowFlag = num; }
	int GetSlowFlag() { return _SlowFlag; }
	void SetMove(VECTOR move) ;
	void SetVolume(int value);
	int GetVolume() { return _Volume; }
	int GetFrameCnt() { return _FrameCnt; }
	int GetMotionDataSize() { return _MotionDate[_MotionID].size(); };
	//bool GetMotChange() { return _MotChangeF; }


private:

	MotionComponent* mc;
	std::vector<std::vector<MOTION_FRAME>> _MotionDate;	//モーションの総数を記述
	int _MotionID;
	int _FrameCnt;
	int _PlayerNo;		//プレイヤーナンバー
	int _Type;			//キャラナンバー
	int _Damage;		//ダメージ保留場所
	bool _BulletF;		//玉やられフラグ
	int _NoteType;
	int _HP;
	bool _MotTrgFlag;
	bool IsCPU;
	int _StopFrameCnt;
	int _MaxHp;
	MOTION_FRAME _HitFrame;
	VECTOR _HitPosition;
	VECTOR _DrawPosition;
	int _StunTime;
	bool _InvFlag;
	bool _JGFlag;
	int _SACnt;
	VECTOR _EnShock;
	int _EnMotionID;
	VECTOR _EnHitPos;
	int _EnArrow;
	bool _ComboFlag;
	std::deque<VECTOR> _OldPosition;
	std::deque<MOTION_FRAME> _OldFrame;
	unsigned int _Color;
	int _SlowFlag;
	int _Volume;
	//bool _MotChangeF;
};