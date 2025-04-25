#include "SceneOutGameBase.h"

SceneOutGameBase::SceneOutGameBase(Main* main)
	:SceneBase(main)
	
{
	_SceneFlag = -1;
}

SceneOutGameBase::~SceneOutGameBase()
{
	DeleteUIs();
	DeleteButtons();
}

void SceneOutGameBase::Init()
{
}

void SceneOutGameBase::Update()
{
}

int SceneOutGameBase::SceneEnd()
{
	return 0;
}


void SceneOutGameBase::DeleteUIs()
{
	auto s = _UIs.size();
	for (auto i = 0; i < s; i++) {
		delete _UIs.back();
		_UIs.pop_back();
	}

}

void SceneOutGameBase::DeleteButtons() {
	auto s = _Buttons.size();
	for (auto i = 0; i < s; i++) {
		delete _Buttons.back();
		_Buttons.pop_back();
	}
}

