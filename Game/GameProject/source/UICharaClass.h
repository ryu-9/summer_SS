#pragma once
#include "ActorClass.h"
#include "UIChipClass.h"
class UICharaClass : public UIChipClass {
public:
	UICharaClass(class SceneBase* scene, VECTOR pos, VECTOR scale, int drawtype,int charatype, const TCHAR* fname);
	void SetCharaType(const int n) { _CharaType = n; }
	void SetFaceType(const int n) { _FaceType = n; }
	int GetCharaType() { return _CharaType; }
	int GetFaceType() { return _FaceType; }
private:
	void SetDrawScript();
//	int _DrawType;
	int _CharaType;
	int _FaceType;
};

