#include "DxLib.h"
#include "GamePad.h"


GamePad::GamePad() {
	_key = 0;
	_trg = 0;
	_rel = 0;
	// �����Q�[���p�b�h�p
	for (int i = 0; i < MUTIPAD_MAX; i++) {
		_m[i]._key = 0;
		_m[i]._trg = 0;
		_m[i]._rel = 0;
	}
}

GamePad::~GamePad() {
}

void GamePad::Input() {
	// �L�[���́A�g���K���́A�����[�X���͂𓾂�
	int keyold = _key;
	_key = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// �L�[���͂��擾
	_trg = (_key ^ keyold) & _key;
	_rel = (_key ^ keyold) & ~_key;

	// �����Q�[���p�b�h�p
	int padTbl[] = {
//		DX_INPUT_KEY_PAD1,	// 0:�L�[����
		DX_INPUT_PAD1,	// 1:�p�b�h1
		DX_INPUT_PAD2,	// 2:�p�b�h2
		DX_INPUT_PAD3,	// 3:�p�b�h3
		DX_INPUT_PAD4,	// 4:�p�b�h4
		DX_INPUT_PAD5,	// 5:�p�b�h5
		DX_INPUT_PAD6,	// 6:�p�b�h6
		DX_INPUT_PAD7,	// 7:�p�b�h7
		DX_INPUT_PAD8,	// 8:�p�b�h8
		DX_INPUT_PAD9,	// 9:�p�b�h9
		DX_INPUT_PAD10,	// 10:�p�b�h10
		DX_INPUT_PAD11,	// 11:�p�b�h11
		DX_INPUT_PAD12,	// 12:�p�b�h12
		DX_INPUT_PAD13,	// 13:�p�b�h13
		DX_INPUT_PAD14,	// 14:�p�b�h14
		DX_INPUT_PAD15,	// 15:�p�b�h15
		DX_INPUT_PAD16,	// 16:�p�b�h16
	};
	for (int i = 0; i < MUTIPAD_MAX; i++) {
		int keyold = _m[i]._key;
		_m[i]._key = GetJoypadInputState(padTbl[i]);
		_m[i]._trg = (_m[i]._key ^ keyold) & _m[i]._key;
		_m[i]._rel = (_m[i]._key ^ keyold) & ~_m[i]._key;
	}
}

