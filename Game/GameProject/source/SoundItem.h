#pragma once
#include <string>
#include <vector>
#include <deque>
#include "DxLib.h"

class SoundManager;

class SoundItemBase {
public:
	

	enum class TYPE {
		NON = 0,		// 未定義
		BGM,			// 音合わせ元
		SE,				// 一回のみ再生,音合わせあり
		SE_3D,			// 一回のみ再生,音合わせあり,3dサウンド
		ONESHOT,		// ストリーミング,一回のみ再生,保持しない
	};
	SoundItemBase(std::string fname, std::string name);
	virtual ~SoundItemBase();
	void SetSoundManager(SoundManager* sndMng) { _sndManager = sndMng; }

	virtual void	Unload();
	virtual void	Play() {}
	virtual bool	IsLoad();
	virtual bool	IsPlay();
	virtual void	Stop();

	virtual int		GetVolume() const { return _Volume; }
	virtual void	SetVolume(int volume);
	virtual int		GetPan() const { return _Pan; };
	virtual void	SetPan(int pan);
	virtual int		GetFrequency() const { return _Frequency; };
	virtual void	SetFrequency(int frequency);
	virtual void	ResetFrequency();
	virtual void	SetTopPositionFlag(bool flg);

	virtual TYPE	GetType() { return TYPE::NON; }
	std::string Name() { return _Name; }
	std::string GetFileName() { return _Filename; }
	virtual int		GetSoundHandle() { return _SoundHandle; }

	virtual void	Update() {}
	virtual void	SetDead(bool dead) { _Dead = dead; }
	virtual bool	IsDead() { return _Dead; }
	virtual void	SetLoop(bool loop) { _Loop = loop; }
	virtual bool	IsLoop() { return _Loop; }

protected:
	virtual void	PlayMem(int flg);	// 再生前に音量等を設定する

	int		_SoundHandle;
	int		_Volume;
	int		_Pan;
	int		_Frequency;
	bool		_TopPositionFlag;
	std::string _Filename;
	std::string _Name;
	SoundManager*	_sndManager;
	bool	_Dead;	// 削除予約
	bool			_Loop;	// ループするか否か
};

class SoundItemBGM : public SoundItemBase {
	typedef SoundItemBase	base;
public:
	SoundItemBGM(std::string fname, std::string name)
		:base(fname, name)
	{
		SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
		_SoundHandle = LoadSoundMem(_Filename.c_str());
		if (_Frequency == 0) {
			_Frequency = GetFrequencySoundMem(_SoundHandle);
		}
		// ここで譜面系ロード
	}
	virtual ~SoundItemBGM() {}
	void Update();
	virtual TYPE	GetType() { return TYPE::BGM; }
	virtual void Play();
protected:
};

class SoundItemSEBase : public SoundItemBase {
	typedef SoundItemBase	base;
public:

	SoundItemSEBase(std::string fname, std::string name) :base(fname, name) {};
	virtual ~SoundItemSEBase() {}

	
protected:
};

class SoundItemSE : public SoundItemSEBase {
	typedef SoundItemSEBase		base;
public:
	SoundItemSE(std::string fname, std::string name) : base(fname, name) {
		_SoundHandle = LoadSoundMem(_Filename.c_str());
		
	}
	virtual TYPE	GetType() { return TYPE::SE; }
	void Play();
	virtual void	Update();
};

