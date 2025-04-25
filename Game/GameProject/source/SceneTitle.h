#pragma once
#include "SceneOutGameBase.h"

class SceneTitle :	public SceneOutGameBase {
public:
	SceneTitle(class Main* main);
	virtual ~SceneTitle();

	void SetTitle();
	void Update() override;

private:
	int _PointCnt;
	std::vector<int> _SwitchPoint;
};

