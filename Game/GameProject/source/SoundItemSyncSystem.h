#pragma once
#include "SoundItem.h"
#include "SoundManager.h"
class SoundItemSE;

class SoundItemSyncSystem {
public:
	SoundItemSyncSystem();

	struct BGM_DATA {
		int handle;
		int bpm;								// BGMÇÃBPM
		float bTime;							// 1ÉrÅ[ÉgÇ…Ç©Ç©ÇÈéûä‘ ç◊Ç©Ç≥
		int cnt;
	};

	void Update();
	void SetBasisBGM(std::string bgmName);
	void SetBasisBGMHandle(int handle,int bpm);
	int GetBPM() { return _BGMData.bpm; }
	void PlaySyncSE(std::string seName);
	int GetPlayerTime() { return GetSoundCurrentTime(_BGMData.handle); }
	BGM_DATA GetbData() const { return _BGMData; }
	void SetLoopSE(bool flg, std::string sename);

private:
	
	BGM_DATA _BGMData;
	bool _LoopSEf;
	std::string _LoopSEname;
};

