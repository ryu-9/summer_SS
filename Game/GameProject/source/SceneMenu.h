#pragma once
#include "SceneOutGameBase.h"
#include "Main.h"
#include "UIChipClass.h"

class ButtonClass;
class MessageBoxClass;

class SceneMenu	:	public SceneOutGameBase
{
public:
	SceneMenu(class Main* main);
	virtual ~SceneMenu();

	void Update() override;
	int SceneEnd() override;

	

private:
	UIChipClass* _Message;
	int _Cursor;
};