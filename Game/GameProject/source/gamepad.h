#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�

class GamePad {
public:
	GamePad();			// �R���X�g���N�^
	virtual ~GamePad();	// �f�X�g���N�^

	virtual void Input();		// ���͍X�V

public:
	// �L�[�{�[�h���Q�[���p�b�h1�̂ǂ���ł��g����ꍇ
	int _key;			// �L�[���͂̏��
	int _trg;			// �g���K���͂̏��
	int _rel;			// �����[�X���͂̏��

	// �����Q�[���p�b�h�p�̏ꍇ
	struct MULTIPAD {
		int _key;			// �L�[���͂̏��
		int _trg;			// �g���K���͂̏��
		int _rel;			// �����[�X���͂̏��
	};
#define	MUTIPAD_MAX		(17)	// �ő�ŁA�p�b�h16�{�L�[�{�[�h��17��
	MULTIPAD	_m[MUTIPAD_MAX];

};

