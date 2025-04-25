#pragma once
#include <vector>
#include <deque>
#include "gamepad.h"
#include "CameraClass.h"
#include "PlayerClass.h"
#include "HitBox.h"
#include <algorithm>
#include <iostream>
#include "ActorClass.h"
#include "SpriteComponent.h"
#include "SaveDataClass.h"
#include "SoundManager.h"
#include "FPSControlClass.h"
#include "Stage.h"
#include "Main.h"
#include "LightingComponent.h"
#include "CommonDataClass.h"
#include "SoundItem.h"
#include "UIFadeSpriteClass.h"

enum class SceneType;
class SoundManager;

#define		GROUND_HEIGHT	(1000)

class SceneBase
{
public:
	SceneBase();
	SceneBase(class Main* main);
	virtual ~SceneBase();
	virtual void Init();
	void ProcessInput();
	virtual void Update();
	virtual void Draw();
	virtual int SceneEnd();

	PlayerClass* GetPlayer(int i) { return _Player[i]; };
	CameraClass* GetCamera() { return _Cam; };
	void AddActor(class ActorClass* actor);
	void RemoveActor(class ActorClass* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddLight(class LightingComponent* light);
	void RemoveLight(class LightingComponent* light);
	std::deque<LightingComponent*> GetLights() { return _Lights; }

	bool GetIsUpdate() const { return _IsUpdate; };
	void SetIsUpdate(const bool flag) { _IsUpdate = flag; };

	FPSControlClass* GetFPSCon() { return _FPSCon; };
	int GetTension() { return _Tension; }
	void ChangeTension(int tension);
	int GetScreenMask() { return ScreenMask; }
	int GetSubMask() { return SubMask; }
	SceneType GetNextScene() const { return _NextScene; }
	int GetChangeFlag() const { return _ChangeFlag; }
	void SetChangeFlag(int n) { _ChangeFlag = n;  }
	void SetNextScene(SceneType n);
	Main* GetMain()const { return _Main; }
	CommonDataClass* GetCommonData()const { return _CommonData; }
	SoundManager* GetSEControl() { return _SEControl; }
	void SetFade(int start, int end, int frame);
	void DeleteFade();
	int GetSceneFlag() { return _SceneFlag; }
	void SetSceneFlag(int flag) { _SceneFlag = flag; }


protected:
	Main* _Main;
	bool _IsUpdate;
	bool _UpdatingActors;
	PlayerClass* _Player[2];
	CameraClass* _Cam;

	UIFadeSpriteClass* _Fade;
	SoundManager* _SEControl;
	// アクタ
	std::vector<class ActorClass*> _Actors;
	// 待機中のアクタ
	std::vector<class ActorClass*> _PendingActors;

	// 描画コンポーネント
	std::vector<class SpriteComponent*> _Sprites;

	//光処理コンポーネント
	std::deque<class LightingComponent*> _Lights;

	//ﾌﾚｰﾑﾚｰﾄ制御用
	FPSControlClass* _FPSCon;

	//テンションゲージ管理用
	int _Tension;
	CommonDataClass* _CommonData;
	int ScreenMask;
	int SubMask;



	SceneType _NextScene;			// シーン移行用 = SceneType::NON;
	int _ChangeFlag = 0;			// シーン移行可能フラグ
	int _SceneFlag;					// シーン内
};
