#include "DxLib.h"
#include "SoundItem.h"
#include "SoundManager.h"

SoundItemBase::SoundItemBase(std::string fname, std::string name)
	: _Filename(fname)
	, _Name(name)
	, _SoundHandle(-1)
	, _Volume(160)
	, _Pan(0)
	, _Frequency(0)
	, _Dead(false)
	, _sndManager(nullptr)
	, _Loop(false)
	, _TopPositionFlag(TRUE)
{
}

SoundItemBase::~SoundItemBase() {
	Unload();
}

void SoundItemBase::Unload() {
	if (_SoundHandle != -1) {
		DeleteSoundMem(_SoundHandle);
		_SoundHandle = -1;
	}
}

bool SoundItemBase::IsLoad() {
	// 非同期ロードが終わっているかチェック
	if (_SoundHandle != -1 && CheckHandleASyncLoad(_SoundHandle) == FALSE) {
		return true;
	}
	return false;
}

bool SoundItemBase::IsPlay() {
	if (_SoundHandle != -1 && CheckSoundMem(_SoundHandle) == 1) {
		return true;
	}
	return false;
}

void SoundItemBase::Stop() {
	if (_SoundHandle != -1) {
		StopSoundMem(_SoundHandle);
	}
}

void SoundItemBase::SetVolume(int volume) {
	_Volume = volume;
	if (_SoundHandle != -1) {
		ChangeVolumeSoundMem(_Volume, _SoundHandle);
	}
}

void SoundItemBase::SetPan(int pan) {
	_Pan = pan;
	if (_SoundHandle != -1) {
		ChangePanSoundMem(_Pan,_SoundHandle);
	}
}

void SoundItemBase::SetFrequency(int frequency) {
	_Frequency = frequency;
	if (_SoundHandle != -1 && _Frequency != 0) {
		SetFrequencySoundMem(_Frequency, _SoundHandle);
	}
}

void SoundItemBase::ResetFrequency() {
	_Frequency = 0;
	if (_SoundHandle != -1) {
		ResetFrequencySoundMem(_SoundHandle);
		_Frequency = GetFrequencySoundMem(_SoundHandle);
	}
}

void SoundItemBase::SetTopPositionFlag(bool flg) {
	_TopPositionFlag = flg;
}

void SoundItemBase::PlayMem(int flg) {
	// 再生前に音量等を設定
	SetVolume(_Volume);
	SetPan(_Pan);
	SetFrequency(_Frequency);
	PlaySoundMem(_SoundHandle, flg, _TopPositionFlag);
}

void SoundItemBGM::Update() {
}

void SoundItemBGM::Play() {
	
	if (_sndManager) {
		_sndManager->StopType(TYPE::BGM);
		if (IsPlay() == false) {	// BGMは再生されていない場合のみ
			if (IsLoop() == TRUE) {
				PlayMem(DX_PLAYTYPE_LOOP);
			}
			else {
				PlayMem(DX_PLAYTYPE_BACK);
			}
		}
	}
}




void SoundItemSE::Play() {
	PlayMem(DX_PLAYTYPE_BACK);
}

void SoundItemSE::Update()
{
	if (_Frequency == 0) {
		_Frequency = GetFrequencySoundMem(_SoundHandle);
	}
}
