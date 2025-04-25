#pragma once
#include "SceneBase.h"
#include "UIChipClass.h"

class SceneOutGameBase : public SceneBase
{
public:
	SceneOutGameBase(class Main* main);
	virtual ~SceneOutGameBase();
	virtual void Init();
	virtual void Update();
	virtual int SceneEnd();

protected:
	void DeleteUIs();
	void DeleteButtons();
	std::vector<UIChipClass*> _UIs;
	std::vector<UIChipClass*> _Buttons;
	std::vector<int> _Cursor;


};

