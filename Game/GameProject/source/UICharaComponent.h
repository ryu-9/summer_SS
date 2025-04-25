#pragma once
#include "Component.h"
#include "UICharaClass.h"
class UICharaClass;
class UICharaFaceChangeComponent : public Component {
public:
	UICharaFaceChangeComponent(class UICharaClass* owner,int type, int updateOrder = 100);


	void Update() override;
private:
	class UICharaClass* _UIChara;
	int _Cnt;
	int _End;
};

