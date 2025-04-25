#include "SceneBase.h"

// 何もしない

SceneBase::SceneBase()
	:_IsUpdate(true)
	,_UpdatingActors(false)
{
}

SceneBase::SceneBase(Main* main)
	:_IsUpdate(true)
	, _UpdatingActors(false)
	,_Main(main)
{
	_CommonData = CommonDataClass::GetInstance();
}

SceneBase::~SceneBase()
{
	while (!_Actors.empty()) {
		delete _Actors.back();
	}
}

void SceneBase::Init(){}

void SceneBase::ProcessInput(){
	_UpdatingActors = true;
	for (auto actor : _Actors) {
		actor->ProcessInput();
	}
	_UpdatingActors = false;
}

void SceneBase::Update() {
	
	// アクタのアップデート
	_UpdatingActors = true;
	for (int i = 0; i < _Actors.size();i++) {
		_Actors[i]->Update();
	}
	_UpdatingActors = false;

	// 待機中アクタの追加
	for (auto p_actor : _PendingActors) {
		_Actors.emplace_back(p_actor);
	}
	_PendingActors.clear();

	// アクタの削除
	std::vector<ActorClass*> deadActors;
	for (auto actor : _Actors) {
		if (actor->GetState() == ActorClass::eDead) {
			deadActors.emplace_back(actor);
		}
	}
	for (auto actor : deadActors) {
		delete actor;
	}
}

void SceneBase::Draw() {
	ClearDrawScreen();
	for (auto sprite : _Sprites) {
		sprite->Draw();
	}
};
int SceneBase::SceneEnd() { return 0; };

// アクターの追加
void SceneBase::AddActor(ActorClass* actor) {
	if (_UpdatingActors) {
		_PendingActors.emplace_back(actor);
	}
	else {
		_Actors.emplace_back(actor);
	}
}

// アクターの削除
void SceneBase::RemoveActor(ActorClass* actor) {
	auto iter = std::find(_PendingActors.begin(), _PendingActors.end(), actor);
	if (iter != _PendingActors.end()) {
		std::iter_swap(iter, _PendingActors.end() - 1);
		_PendingActors.pop_back();
	}

	iter = std::find(_Actors.begin(), _Actors.end(), actor);
	if (iter != _Actors.end()) {
		std::iter_swap(iter, _Actors.end() - 1);
		_Actors.pop_back();
	}
}

void SceneBase::AddSprite(SpriteComponent* sprite) {
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = _Sprites.begin();
	for (; iter != _Sprites.end(); ++iter) {
		if (myDrawOrder < (*iter)->GetDrawOrder()) { break; }
	}

	_Sprites.insert(iter, sprite);
}

void SceneBase::RemoveSprite(SpriteComponent* sprite) {
	auto iter = std::find(_Sprites.begin(), _Sprites.end(), sprite);
	_Sprites.erase(iter);
}

void SceneBase::AddLight(LightingComponent* light)
{
	_Lights.emplace_back(light);
}

void SceneBase::RemoveLight(LightingComponent* light)
{
	auto iter = std::find(_Lights.begin(), _Lights.end(), light);
	_Lights.erase(iter);
}

void SceneBase::ChangeTension(int tension)
{
	_Tension += tension;
	if (_Tension > 100) { _Tension = 100; }
	if (_Tension < 0) { _Tension = 0; }
}

void SceneBase::SetNextScene(SceneType n)
{
	  _NextScene = n; 
}

void SceneBase::SetFade(int start,int end,int frame)
{
	if (_Fade == nullptr) {
		UIFadeSpriteClass::EASING data = { start,end,0,frame };
		_Fade = new UIFadeSpriteClass(this, data);
	}
}

void SceneBase::DeleteFade() {
	if (_Fade != nullptr) {
		delete _Fade;
		_Fade = nullptr;
	}
}

