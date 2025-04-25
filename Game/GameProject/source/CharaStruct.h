#pragma once
#include <dxlib.h>
#include "vector"

#define AT_MAX		(3)
#define HIT_MAX		(3)

//�t���[�����Ƃ̍U������
struct ATACK_BOX {
	VECTOR	pos = VGet(0,0,0);
	VECTOR r = VGet(0, 0, 0);
	int rotate=0;
	int damage1 = 0;
	int damage2 = 0;
	VECTOR	shock=VGet(0,0,0);
};

//�t���[�����Ƃ̂��炢����
struct HIT_BOX {
	VECTOR	pos = VGet(0, 0, 0);;
	VECTOR r = VGet(0, 0, 0);;
	int rotate = 0;
};

//�t���[�����Ƃ̏��
struct MOTION_FRAME {
	int type = 0;		//�L�����Z���̉�
	float mx = 0;
	float my = 0;		//�ړ���
	int w = 1000;
	int h = 1000;		//�摜�̑傫���i�`��p�j
	std::vector<ATACK_BOX> at;
	std::vector<HIT_BOX> hit;
	int cg = -1;// LoadGraph("res/stage/NoImage.png");
	int mask;
	bool rev;
};
