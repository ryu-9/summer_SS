#pragma once
#include "ActorClass.h"
#include <string>

class UIChipClass :public ActorClass {
public:
	UIChipClass(class SceneBase* scene, VECTOR pos,VECTOR scale, int drawtype, std::string fname,int draworder = 100);

	void ResetScale() { _Scale = VGet(1,1,1); }
	VECTOR GetScale() const { return _Scale; }
	void SetScale(const VECTOR scale) { _Scale = scale; }
	void ChangeImage(int num) { _Num = num; }
	int GetImageNum()const { return _Num; }
	void AddImage(std::string fname);
	int GetType() { return _DrawType; }
	int GetImageSize();
	void SetType(int type) { _DrawType = type; }
protected:
	VECTOR _Scale;
	int _DrawType;
	int _Num;
	class UIChipSpriteComponent* _Sp;
};

