#include <vector>
#include "SceneBase.h"
#include "ActorClass.h"
#include "DxLib.h"
#include "Component.h"

ActorClass::ActorClass()
{
}

ActorClass::ActorClass(SceneBase* scene)
	:_State(eActive)
	,_Position(VGet(0, 0, 0))
	,_Scene(scene)
{
	_Scene->AddActor(this);
}

ActorClass::~ActorClass()
{
	// 解放
	_Scene->RemoveActor(this);
	int tmp = _Components.size();
	for (int i = 0, j = 0; i + j < tmp; i++) {
		auto itr = _Components[i];
		delete itr;
		i--;
		j++;
	}
}

void ActorClass::ProcessInput() {
	if (_State == eActive)
	{

		for (auto comp : _Components)
		{
			comp->ProcessInput();
		}

		ActorInput();
	}
}

void ActorClass::Update() {
	if (_State == eActive||_State == ePreparation) {
		if (this == nullptr) {
			delete this;
			return;
		}
		if (_Components.size() >500) {
			int test = 0;
		}
		UpdateComponents();
		UpdateActor();
	}
}

void ActorClass::UpdateComponents() {
	for (auto comp : _Components) {
		comp->Update();
	}
}


void ActorClass::UpdateActor(){
}

SceneBase* ActorClass::GetScene()
{
	if (_Scene == nullptr) {
		delete this;
		return nullptr;
	}
	return _Scene;
}

void ActorClass::AddComponent(Component* component) { // コンポーネント追加
	int Order = component->GetUpdateOrder();
	auto comp = _Components.begin();
	for (; comp != _Components.end();++comp) { // 挿入する位置を検索
		if (Order < (*comp)->GetUpdateOrder()) {
			break;
		}
	}

	_Components.insert(comp, component); // コンポーネント追加
}

void ActorClass::RemoveComponent(Component* component) {
	auto comp = std::find(_Components.begin(), _Components.end(), component);
	if (comp != _Components.end()) {
		_Components.erase(comp);
	}
}

void ActorClass::SetMove(VECTOR move)
{

	if (move.y != 0.0f) { //空中で止まってほしい場合、0.1を記述
		_Move.y = (int)move.y;
		_Stand = FALSE;
	}
	if (_Stand == TRUE) { _Move.x = 0; }
	if(move.x != 0){ _Move.x = (int)move.x; }

}

bool ActorClass::GetStandFlag()
{
	return _Stand;
}
