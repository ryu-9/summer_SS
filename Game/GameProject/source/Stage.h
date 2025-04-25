#pragma once
#include "ActorClass.h"


class StageBase : public ActorClass
{
public:
	StageBase(class SceneBase* scene,VECTOR pos, VECTOR size, const TCHAR* cgfile, int CgNum=1, int DrawOrder = 100, float rotate=0, int loop = 360, int BlendMode = DX_BLENDMODE_NOBLEND, int value = 0);
	~StageBase();

	void UpdateActor() override;
	float GetInitX() { return _InitX; }
	VECTOR GetSize() { return _Size; }
	VECTOR GetViewPos();
	int GetType() { return _Type; }
	float GetRotate() { return _Rotate; }

	class MainSpriteComponent* sp;
	std::vector<int> _Cg;

protected:
	float _InitX;
	float _InitY;
	VECTOR _Size;
	int screen;
	int _Type;
	float _Rotate;
	int _LoopRot;

};

class StageBack : public StageBase
{
public:
	StageBack(class SceneBase* scene, VECTOR pos, VECTOR size, const TCHAR* cgfile, float z, int DrawOrder = 100, int BlendMode = DX_BLENDMODE_NOBLEND, int value = 0);
	~StageBack();

	void UpdateActor() override;



private:
	float _Zdist;

};

class StageLight : public StageBase
{
public:
	StageLight(class SceneBase* scene, VECTOR pos, VECTOR size, const TCHAR* cgfile,int CgNum=1, int DrawOrder=100, int Rotate=0);
	virtual ~StageLight();
	void UpdateActor() override;

private:
	VECTOR _Size;
	bool _No;
	class LightingComponent* light;
	int _Color[2][3];
	class MainSpriteComponent* land;
	class MainSpriteComponent* shadow[2];

};

class StageFire : public StageBase
{
public:
	StageFire(class SceneBase* scene, VECTOR pos, int Rotate = 0);
	virtual ~StageFire();
	void UpdateActor() override;

private:
	int _OldTension;
	std::vector<int> _FlashCg;
	class FlameClass* fire;
};