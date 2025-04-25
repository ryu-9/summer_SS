#pragma once
#include <string>
#include <vector>
#include <deque>
#include "DxLib.h"

class SoundManager;

class SoundItemBase {
public:
	

	enum class TYPE {
		NON = 0,		// ����`
		BGM,			// �����킹��
		SE,				// ���̂ݍĐ�,�����킹����
		SE_3D,			// ���̂ݍĐ�,�����킹����,3d�T�E���h
		ONESHOT,		// �X�g���[�~���O,���̂ݍĐ�,�ێ����Ȃ�
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
	virtual void	PlayMem(int flg);	// �Đ��O�ɉ��ʓ���ݒ肷��

	int		_SoundHandle;
	int		_Volume;
	int		_Pan;
	int		_Frequency;
	bool		_TopPositionFlag;
	std::string _Filename;
	std::string _Name;
	SoundManager*	_sndManager;
	bool	_Dead;	// �폜�\��
	bool			_Loop;	// ���[�v���邩�ۂ�
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
		// �����ŕ��ʌn���[�h
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

