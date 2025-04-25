#include "SoundManager.h"
#include "SceneBase.h"
#include <string>
#include "winmain.h"

SoundManager::SoundManager() {
	_isUpdate = false;
}

SoundManager::~SoundManager() {
	Clear();
}

void SoundManager::Clear() {
	for (auto&& snd : _Sounds) {
		delete snd;
	}
	_Sounds.clear();
}


void SoundManager::AddSound(SoundItemBase* snd) {
	DeleteSound(snd);
	_Sounds.push_back(snd);
	snd->SetSoundManager(this);
}

bool SoundManager::DeleteSound(SoundItemBase* snd) {

	auto name = snd->Name();
	for (auto i = 0; i < _Sounds.size();i++) {
		if (_Sounds[i]->Name() == name) {
			if (_isUpdate == false) {
				delete _Sounds[i];
				_Sounds.erase(_Sounds.begin()+i);
				return true;
			}
			else {
				_Sounds[i]->SetDead(true);
				return true;
			}
			
		}
	}
	return false;
}

void SoundManager::StopType(SoundItemBase::TYPE type) {
	for (auto&& s : _Sounds) {
		if (s->GetType() == type) {
			s->Stop();
		}
	}
}

SoundItemBase* SoundManager::GetSound(std::string name) {
	for (auto iter = _Sounds.begin(); iter != _Sounds.end(); iter++) {
		if ((*iter)->Name() == name) {
			return (*iter);
		}
	}
	return nullptr;
}

void SoundManager::Update() {
	_isUpdate = true;
	for (auto&& snd : _Sounds) {
		snd->Update();
	}
	_isUpdate = false;

	// íœ—\–ñ‚³‚ê‚½‚à‚Ì‚ðíœ
	for (auto iter = _Sounds.begin(); iter != _Sounds.end();) {
		if ((*iter)->IsDead()) {
			std::iter_swap(iter, _Sounds.end() - 1);
			delete (*iter);
			_Sounds.pop_back();
		}
		else {
			iter++;
		}
	}
}
