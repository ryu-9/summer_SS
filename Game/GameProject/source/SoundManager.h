#pragma once
#include "SoundItem.h"
#include <string>
#include <vector>

class SoundManager{
public:
	SoundManager();
	virtual ~SoundManager();
	
	void Clear();
	void AddSound(SoundItemBase* snd);
	bool DeleteSound(SoundItemBase* snd);
	void StopType(SoundItemBase::TYPE type);

	SoundItemBase* GetSound(std::string name);
	std::vector<SoundItemBase*> GetSoundVec() { return _Sounds; }

	void Update();
	
private:
	std::vector<SoundItemBase*> _Sounds;
	bool _isUpdate;
};