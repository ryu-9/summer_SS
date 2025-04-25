#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "dxlib.h"


ApplicationMain				g_oApplicationMain;



bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	SetMainWindowText("SS");
	gGlobal.Init();

#if 1
//	ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
#endif
#if 0
	gGlobal._Stageflg = 3;
	ModeServer::GetInstance()->Add(new ModeStageSelect(), 3, "select");

	//gGlobal._SelectStage = 3;
	//ModeServer::GetInstance()->Add(new ModeLoading(), 100, "loading");
	//ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
	//ModeServer::GetInstance()->Add(new ModeGameUI(), 2, "gameui");


#endif

	return true;
}

bool ApplicationMain::Terminate() {
	base::Terminate();
	return true;
}


bool ApplicationMain::Input() {
	base::Input();
	return true;
}

bool ApplicationMain::Process() {
	base::Process();
	return true;
}

bool ApplicationMain::Update() {
	base::Update();
	return false;
}

bool ApplicationMain::Render() {
	base::Render();
	return true;
}

