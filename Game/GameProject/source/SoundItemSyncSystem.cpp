#include "SoundItemSyncSystem.h"
#include "Main.h"
#include "ioJson.h"

SoundItemSyncSystem::SoundItemSyncSystem() {
}

void SoundItemSyncSystem::Update() {
	if (GetSoundCurrentTime(_BGMData.handle) > (_BGMData.bTime * (_BGMData.cnt + 1))) {

		if (_LoopSEf == TRUE&& _BGMData.cnt%2==1) {
			PlaySyncSE(_LoopSEname);
		}
		_BGMData.cnt++;
	}
}

void SoundItemSyncSystem::SetBasisBGM(std::string bgmName) {

	_BGMData.handle = sndManager.GetSound(bgmName)->GetSoundHandle();

	_BGMData.bpm = 182;
	_BGMData.bTime = 1000.0f / (_BGMData.bpm / 60.0f);
	_BGMData.cnt = 0;
}

void SoundItemSyncSystem::SetBasisBGMHandle(int handle,int bpm)
{


	_BGMData.handle = handle;

	_BGMData.bpm = bpm;
	_BGMData.bTime = 1000.0f / (_BGMData.bpm / 60.0f);
	_BGMData.cnt = 0;
}

void SoundItemSyncSystem::PlaySyncSE(std::string seName) {
	auto se = sndManager.GetSound(seName);
	if (se == nullptr) {
		return;
	}
	else {
	
		auto diff = GetSoundCurrentTime(_BGMData.handle) - (_BGMData.bTime * _BGMData.cnt);

		
		SetSoundCurrentTime(500 - (_BGMData.bTime - diff),se->GetSoundHandle());
		se->Play();
		
	}
}

void SoundItemSyncSystem::SetLoopSE(bool flg, std::string sename) {
	_LoopSEf = flg;
	if (flg == TRUE) {
		if (_LoopSEname != "") {
			sndManager.GetSound(_LoopSEname)->SetTopPositionFlag(TRUE);
		}
		_LoopSEname = sename;
		sndManager.GetSound(_LoopSEname)->SetTopPositionFlag(FALSE);
	}
	else {
		sndManager.GetSound(_LoopSEname)->SetTopPositionFlag(TRUE);
		_LoopSEname = "";
	}
}
