#pragma once
#include <dxlib.h>
#include "vector"

#define AT_MAX		(3)
#define HIT_MAX		(3)

//フレームごとの攻撃判定
struct ATACK_BOX {
	VECTOR	pos = VGet(0,0,0);
	VECTOR r = VGet(0, 0, 0);
	int rotate=0;
	int damage1 = 0;
	int damage2 = 0;
	VECTOR	shock=VGet(0,0,0);
};

//フレームごとのくらい判定
struct HIT_BOX {
	VECTOR	pos = VGet(0, 0, 0);;
	VECTOR r = VGet(0, 0, 0);;
	int rotate = 0;
};

//フレームごとの情報
struct MOTION_FRAME {
	int type = 0;		//キャンセルの可否
	float mx = 0;
	float my = 0;		//移動量
	int w = 1000;
	int h = 1000;		//画像の大きさ（描画用）
	std::vector<ATACK_BOX> at;
	std::vector<HIT_BOX> hit;
	int cg = -1;// LoadGraph("res/stage/NoImage.png");
	int mask;
	bool rev;
};
