#pragma once
#include "Dxlib.h"
#include "math.h"
#include "CameraClass.h"
#include "CharaStruct.h"


int IsHitCC(VECTOR pos1, VECTOR r1, VECTOR pos2, VECTOR r2);
int IsHitBC(VECTOR pos1, VECTOR r1, int rotate, VECTOR pos2, VECTOR r2);
int IsHitBB(VECTOR pos1, VECTOR r1, int rotate1, VECTOR pos2, VECTOR r2, int rotate2);
int CheckHitSome(VECTOR pos1, VECTOR r1, int rotate1, VECTOR pos2, VECTOR r2, int rotate2);
void DrawHitBox(VECTOR pos, VECTOR r, int rotate, unsigned int color, CameraClass* cam);
void ConvertBox(HIT_BOX* hit_array, MOTION_FRAME player_frame, ATACK_BOX* at_array, MOTION_FRAME enemy_frame);
void ConVert(VECTOR &pos,VECTOR &r,int rotate);