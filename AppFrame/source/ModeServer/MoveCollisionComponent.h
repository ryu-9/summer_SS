#pragma once
#include "ModeBase.h"
#include "Component.h"

struct CollResult {
	class MoveCollisionComponent* mc;
	std::deque<MV1_COLL_RESULT_POLY> mesh;
};


class MoveCollisionComponent : public	Component
{
public:
	MoveCollisionComponent(class ActorClass* owner, class ModelComponent* model,  VECTOR pos = VGet(0,0,0), VECTOR size = VGet(1,1,1)
	, int type = 0, bool move = FALSE, bool active = TRUE , int handle = -1);

	~MoveCollisionComponent() override;

	void Update() override;

	void RefleshCollInfo();

	VECTOR GetPosition();
	void SetOldPosition(VECTOR pos) { OldPos = pos; }

	VECTOR GetSize();

	VECTOR GetUp();
	VECTOR GetFront();
	VECTOR GetRight();

	VECTOR GetRPosition() const { return Pos; }
	VECTOR GetRSize() const { return Size; }

	VECTOR GetRotation();

	void SetRPosition(VECTOR pos) { Pos = pos; }
	void SetRSize(VECTOR size) { Size = size; }

	int GetType() const { return Type; }
	void SetType(int type) { Type = type; }
	// collision�̌`�@0: �� 1:���� 2:�J�v�Z�� 3:���b�V��

	bool GetIsMove() const { return isMove; }
	void SetIsMove(bool move) { isMove = move; }

	bool GetIsActive() const { return isActive; }
	void SetIsActive(bool active) { isActive = active; }

	int GetHandle() const { return Handle; }
	void SetHandle(int handle) { Handle = handle; }

	void DebugDraw();

	bool GetFlag() const { return flag; }

	void Push();

	void SetRotation(VECTOR rot);

	class MoveComponent* GetMove() const { return _Move; }

	VECTOR GetDrawPos(int num = 0) const { return drawpos[num]; }

	std::deque<CollResult> GetCollResult(int num = 0) const { return _CollResult; }

protected:
	// �ʒu
	VECTOR Pos;
	
	// �T�C�Y
	VECTOR Size;

	VECTOR Rot;
	VECTOR Front;
	VECTOR Up;

	// collision�̌`
	int Type;

	//	�ړ����邩
	bool isMove;

	//	�A�N�e�B�u��
	bool isActive;

	//	�\���I�ɏ������邩
	bool isCalc;

	//	���f���n���h��
	int Handle;

	bool flag;
	bool shomen;
	VECTOR OldMove;
	VECTOR OldPos;

	VECTOR devpos;
	VECTOR drawpos[2];

	class ModelComponent* _Model;
	class MoveComponent* _Move;

	std::deque<CollResult> _CollResult;

	std::deque<VECTOR> debugpos;
};

