#pragma once
#include "Component.h"
#include "UIChipClass.h"


class UIActionComponentBase : public Component {
public:

	UIActionComponentBase(class UIChipClass* owner, VECTOR start, VECTOR end, int frame, int entype,int easetype, int updateOrder = 100);
	virtual ~UIActionComponentBase();

	void Update() override;

protected:
	struct  EASING
	{
		VECTOR start;
		VECTOR end;
		int frame;
		int cnt;
	};

	EASING _eData;
	UIChipClass* _UIc;
	int _EndType;
	int _EaseType;
};

