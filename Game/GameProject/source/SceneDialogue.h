#pragma once
#include "SceneBase.h"
#include "SceneOutGameBase.h"
class SceneDialogue : public SceneOutGameBase
{
public:
	SceneDialogue(class Main* main);
	virtual ~SceneDialogue();

	void Update() override;
	int SceneEnd() override;

private:
	void BeforeInit();
	void BeforeUpdate();
	void AfterInit();
	void AfterUpdate();
	SoundItemBase* _Voice;
	bool _DrawType;
};

