#pragma once
#include "ActorClass.h"
#include "SceneBase.h"
#include "PsylliumSpriteComponent.h"

#define	PSYLLIUM_MAX	(196)
#define PSYLLIUM_DIST	(100)



class PsylliumControlClass : public ActorClass
{
public:
	PsylliumControlClass();
	PsylliumControlClass(SceneBase* scene);
	virtual ~PsylliumControlClass();
	void UpdateActor() override;

protected:

private:
	int _Start;
	int _End;
	easing _Easing;
	int _Angle;
	int _Arm;
	int _Height;
	PsylliumSpriteComponent* Psyllium[PSYLLIUM_MAX];
	int _Cg[2];
	int _CgF[2];
	int _Type;
	int _NotesType;
	bool _InversFlag;
	int _Slope;
	int debugCnt;
	int debugNum;
};

