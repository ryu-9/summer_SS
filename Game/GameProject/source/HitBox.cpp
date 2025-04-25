#include "HitBox.h"
#include "SceneBase.h"

int IsHitCC(VECTOR pos1, VECTOR r1, VECTOR pos2, VECTOR r2) {
	if (VSize(VSub(pos1, pos2)) <= r1.x+r2.x) {
		return 1;
	}
	return 0;
}

int IsHitBC(VECTOR pos1, VECTOR r1, int rotate, VECTOR pos2, VECTOR r2) {
	MATRIX rot = MGetRotZ(-(float)rotate / 180 * atan(1) * 4);
	VECTOR dist = VTransform(VSub(pos2, pos1), rot);
	VECTOR tmp = VGet(0,0,0);
	if (abs((long)dist.x) > r1.x) {
		if (dist.x >= 0) { tmp.x = r1.x; }
		else { tmp.x = -r1.x; }
	}
	else { tmp.x = dist.x; }
	if (abs((long)dist.y) > r1.y) {
		if (dist.y >= 0) { tmp.y = r1.y; }
		else { tmp.y = -r1.y; }
	}
	else { tmp.y = dist.y; }
	if (VSize(VSub(dist, tmp)) < r2.x) { return 1; }
	return 0;
}

int IsHitBB(VECTOR pos1, VECTOR r1, int rotate1, VECTOR pos2, VECTOR r2, int rotate2) {

	MATRIX rot = MGetRotZ(-(float)rotate1 / 180 * atan(1) * 4);
	VECTOR dist = VTransform(VSub(pos2, pos1), rot);
	rot = MGetRotZ(((float)rotate2 - (float)rotate1) / 180 * atan(1) * 4);
	VECTOR v[2][4] = { {	
			VGet(-1,-1,0), VGet(1,-1,0),
		VGet(1,1,0), VGet(-1,1,0)},
		{	VGet(-1,-1,0), VGet(1,-1,0),
		VGet(1,1,0), VGet(-1,1,0)}
	};
	for (int i = 0; i < 4; i++) {
		v[0][i].x *= r1.x; v[0][i].y *= r1.y;
		v[1][i].x *= r2.x; v[1][i].y *= r2.y;
		v[1][i] = VTransform(v[1][i], rot);
		v[1][i] = VAdd(v[1][i], dist);
	}

	if (v[0][0].y <= dist.y && v[0][2].y >= dist.y) {
		if (v[0][0].x <= dist.x && v[0][2].x >= dist.x) {
			return 1;
		}
	}

	for (int i = 0,j=0; i < 4; i++) {
		VECTOR tmp[3];
		tmp[1] = VSub(v[1][i], VGet(0, 0, 0));
		tmp[2] = VSub(v[1][i], dist);
		if (i == 0) {
			tmp[0] = VSub(v[1][0], v[1][3]);
		}
		else { tmp[0] = VSub(v[1][i], v[1][i - 1]); }
		tmp[1] = VCross(tmp[0], tmp[1]);
		tmp[2] = VCross(tmp[0], tmp[2]);
		if (VNorm(tmp[1]).z == VNorm(tmp[2]).z) { 
			j++;
		}
		if (j >= 4) {
			return 1;
		}
	}


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			VECTOR tmp[4];
			if (i == 0) { tmp[0] = v[0][3]; tmp[1] = v[0][0]; }
			else { tmp[0] = v[0][i - 1]; tmp[1] = v[0][i];}
			if (j == 0) { tmp[2] = v[1][3]; tmp[3] = v[1][0]; }
			else { tmp[2] = v[1][j - 1]; tmp[3] = v[1][j]; }

			if (i % 2 == 0) {
				if (tmp[0].y > tmp[1].y) {
					if (tmp[1].y > tmp[2].y && tmp[1].y > tmp[3].y) { continue; }
					if (tmp[0].y < tmp[2].y && tmp[0].y < tmp[3].y) { continue; }
				}
				else {
					if (tmp[1].y < tmp[2].y && tmp[1].y < tmp[3].y) { continue; }
					if (tmp[0].y > tmp[2].y && tmp[0].y > tmp[3].y) { continue; }
				}
				if (tmp[2].x == tmp[3].x) { 
					if (tmp[0].x == tmp[2].x) {
						return 1;
					}
					else { continue; }
				}
				tmp[3] = VSub(tmp[3], tmp[2]);
				float X = tmp[1].x - tmp[2].x;
				if (X / tmp[3].x >= 0 && X / tmp[3].x <= 1) {
					return 1;
				}
			}
			else {
				if (tmp[0].x > tmp[1].x) {
					if (tmp[1].x > tmp[2].x && tmp[1].x > tmp[3].x) { continue; }
					if (tmp[0].x < tmp[2].x && tmp[0].x < tmp[3].x) { continue; }
				}
				else {
					if (tmp[1].x < tmp[2].x && tmp[1].x < tmp[3].x) { continue; }
					if (tmp[0].x > tmp[2].x && tmp[0].x > tmp[3].x) { continue; }
				}
				if (tmp[2].y == tmp[3].y) {
					if (tmp[0].y == tmp[2].y) {
						return 1;
					}
					else { continue; }
				}
				tmp[3] = VSub(tmp[3], tmp[2]);
				float Y = tmp[1].y - tmp[2].y;
				if (Y / tmp[3].y >= 0 && Y / tmp[3].y <= 1) {
					return 1;
				}
			}
		}
	}
	return 0;



	/*
		MATRIX rot = MGetRotZ(-(float)rotate1 / 180 * atan(1) * 4);
	VECTOR dist = VTransform(VSub(pos2, pos1), rot);
	rot = MGetRotZ(((float)rotate2 - (float)rotate1) / 180 * atan(1) * 4);
	VECTOR vertex[4] = {
	VGet(-1,-1,0), VGet(1,-1,0),
	VGet(-1,1,0), VGet(1,1,0)
	};
	for (int i = 0; i < 4; i++) {
		vertex[i].x *= r2.x; vertex[i].y *= r2.y;
		vertex[i] = VTransform(vertex[i], rot);
		vertex[i] = VAdd(vertex[i], dist);
		VECTOR tmp = VNorm(vertex[i]);
		if (tmp.x * tmp.x * r1.y * r1.y >= tmp.y * tmp.y * r1.x * r1.x)
		{
			tmp = VScale(tmp, 1 * r1.x / tmp.x);
		}
		else { tmp = VScale(tmp, 1 * r1.y / tmp.y); }
		if (VSize(tmp) >= VSize(vertex[i])) { return 1; }
	}

	rot = MGetRotZ(-(float)rotate2 / 180 * atan(1) * 4);
	dist = VTransform(VSub(pos1, pos2), rot);
	rot = MGetRotZ(((float)rotate1 - (float)rotate2) / 180 * atan(1) * 4);
	vertex[0] = VGet(-1, -1, 0); vertex[1] = VGet(1, -1, 0);
	vertex[2] = VGet(-1, 1, 0); vertex[3] = VGet(1, 1, 0);
	for (int i = 0; i < 4; i++) {
		vertex[i].x *= r1.x; vertex[i].y *= r1.y;
		vertex[i] = VTransform(vertex[i], rot);
		vertex[i] = VAdd(vertex[i], dist);
		VECTOR tmp = VNorm(vertex[i]);
		if (tmp.x * tmp.x * r2.y * r2.y >= tmp.y * tmp.y * r2.x * r2.x)
		{
			tmp = VScale(tmp, 1 * r2.x / tmp.x);
		}
		else { tmp = VScale(tmp, 1 * r2.y / tmp.y); }
		if (VSize(tmp) >= VSize(vertex[i])) { return 1; }
	}
	return 0;
	/*
	*/

}

int CheckHitSome(VECTOR pos1, VECTOR r1, int rotate1, VECTOR pos2, VECTOR r2, int rotate2) {
	if (VSize(r1) == 0 || VSize(r2) == 0) { return 0; }
	if (r1.z == 0 && r2.z == 0) {
		return IsHitCC(pos1, r1, pos2, r2);
	}
	else {
		if (r1.z != 0) {
			if (r2.z != 0) {
				return IsHitBB(pos1, r1, rotate1, pos2, r2, rotate2);
			}
			return IsHitBC(pos1, r1, rotate1, pos2, r2);
		}
		return IsHitBC(pos2, r2, rotate2, pos1, r1);
	}
}

void DrawHitBox(VECTOR pos, VECTOR r, int rotate, unsigned int color, CameraClass* cam) {
	VECTOR DrawV = VGet(1920 / 2, GROUND_HEIGHT, 0);
	if (r.z == 0) {
		float diam = r.x*cam->GetZomm();
		VECTOR position = VAdd(VTransform(pos, cam->GetView()),DrawV);
		DrawCircle(position.x, position.y, diam, color, TRUE);
	}
	else {
		VECTOR ft[2] = { r,VGet(r.x,-r.y,0) };
		MATRIX rot = MGetRotZ((float)rotate / 180 * atan(1) * 4);
		for (int i = 0; i < 2; i++) {
			ft[i] = VTransform(ft[i], rot);
		}
		VECTOR vert[4];
		vert[0] = VTransform(VAdd(pos, VScale(ft[0], -1)), cam->GetView());
		vert[1] = VTransform(VAdd(pos, VScale(ft[1], -1)), cam->GetView());
		vert[2] = VTransform(VAdd(pos, ft[0]), cam->GetView());
		vert[3] = VTransform(VAdd(pos, ft[1]), cam->GetView());
		for (int i = 0; i < 4; i++) {
			vert[i] = VAdd(vert[i], DrawV);
		}
		/*
		DrawQuadrangle(pos.x - ft[0].x, pos.y - ft[0].y, pos.x - ft[1].x, pos.y - ft[1].y,
			pos.x + ft[0].x, pos.y + ft[0].y, pos.x + ft[1].x, pos.y + ft[1].y, color, TRUE);

		*/
		DrawQuadrangle(vert[0].x, vert[0].y, vert[1].x, vert[1].y, vert[2].x, vert[2].y, vert[3].x, vert[3].y, color, TRUE);
			}
}

void ConvertBox(HIT_BOX* hit_array, MOTION_FRAME player_frame, ATACK_BOX* at_array, MOTION_FRAME enemy_frame) {
	int i;
	for (i = 0; i < player_frame.hit.size();i++) {
		//hit_array[i].r = VGet(0,0,0);
		if(VSize(VGet(hit_array[i].r.x, player_frame.hit[i].r.y, 0)) != 0) {
			hit_array[i] = player_frame.hit[i];
			hit_array[i].r = VScale(player_frame.hit[i].r, 0.5);
			hit_array[i].pos = VAdd(hit_array[i].pos, VGet(-player_frame.w / 2, -player_frame.h, 0));
			ConVert(hit_array[i].pos, hit_array[i].r, hit_array[i].rotate);
		}

	}
	for (i = 0; i < enemy_frame.at.size(); i++) {
		//at_array[i].r = VGet(0, 0, 0);
		//player_frame.hit[i].r = VScale(player_frame.hit[i].r, 0.5);
		at_array[i] = enemy_frame.at[i];
		at_array[i].r = VScale(enemy_frame.at[i].r, 0.5);
		at_array[i].pos = VAdd(at_array[i].pos, VGet(-enemy_frame.w / 2, -enemy_frame.h, 0));
		ConVert(at_array[i].pos, at_array[i].r, at_array[i].rotate);
	}
}

void ConVert(VECTOR &pos, VECTOR &r, int rotate)
{
	if (r.z == 0) {
		float tmp = r.x;
		pos = VAdd(pos, VGet(tmp, tmp, 0));
	}
	else {
		std::vector<VECTOR> vert;
		vert.resize(4);
		float rot = rotate * 4 * atan(1) / 180;
		MATRIX rotation = MGetRotZ(rot);
		vert[0] = VScale(r, -1); vert[1] = VGet(r.x, -r.y, 0);
		vert[2] = VGet(-r.x, r.y, 0); vert[3] = r;
		float tmpX = 0;
		float tmpY = 0;
		for (int j = 0; j < 4; j++) {
			vert[j] = VTransform(vert[j], rotation);
			if (vert[j].x < tmpX) { tmpX = vert[j].x; }
			if (vert[j].y < tmpY) { tmpY = vert[j].y; }
		}
		pos = VAdd(pos, VGet(-tmpX, -tmpY, 0));
	}
}
