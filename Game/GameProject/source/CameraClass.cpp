#include "CameraClass.h"
#include "SceneBase.h"

CameraClass::CameraClass(SceneBase* scene)
	:ActorClass(scene)
	,zoom(1)
{
	_Position = VGet(0,-GROUND_HEIGHT,0);
	_View = MGetTranslate(_Position);
}

CameraClass::~CameraClass()
{
}

void CameraClass::UpdateActor()
{
	float zoom_max = ZOOM_MAX;
	float FrameTime = GetScene()->GetFPSCon()->GetFrameNum();
	VECTOR tmpVadd = GetScene()->GetPlayer(0)->GetPosition(), tmpVsub = GetScene()->GetPlayer(1)->GetPosition();
	//tmpVadd = VAdd(tmpVadd, GetScene()->GetPlayer(0)->GetMove());
	if (tmpVadd.x - tmpVsub.x>3000) {
		tmpVadd.x = tmpVsub.x + 3000;
	}
	if (tmpVadd.x - tmpVsub.x < -3000) {
		tmpVadd.x = tmpVsub.x - 3000;
	}
	//tmpVsub = VAdd(tmpVsub, GetScene()->GetPlayer(1)->GetMove());
	if (tmpVsub.x - tmpVadd.x > 3000) {
		tmpVsub.x = tmpVadd.x + 3000;
	}
	if (tmpVsub.x - tmpVadd.x < -3000) {
		tmpVsub.x = tmpVadd.x - 3000;
	}
	//_Position.y = -tmpVadd.y;
	//if (tmpVadd.y < tmpVsub.y) { _Position.y = -tmpVsub.y; }
	tmpVadd = VAdd(tmpVadd, tmpVsub);
	tmpVsub = VSub(tmpVadd, VScale(tmpVsub, 2));
	if (tmpVsub.y < 0) { tmpVsub.y *= -1; }
	if (tmpVsub.x < 0) { tmpVsub.x *= -1; }
	float tmp = tmpVsub.x;
	//if (tmpVsub.x < tmpVsub.y * 3) { tmp = tmpVsub.y * 3; }


	if (GetScene()->GetFPSCon()->GetUpdateFlag() == TRUE|| GetScene()->GetFPSCon()->GetInputUDFlag() == TRUE) {
		_Move = VGet(0, 0, 0);
		if (GetScene()->GetFPSCon()->GetSession() > 0) {
			
			_Position.x = -tmpVadd.x / 2;
			_Position.y = -tmpVadd.y / 2;// +VAdd(GetScene()->GetPlayer(0)->GetMove(), GetScene()->GetPlayer(1)->GetMove()).y / 2;
			zoom = (float)1920 / (tmp + CAMERA_ADJ);
		}

		else if (GetScene()->GetFPSCon()->GetHitStop() > 5) {
			//_Position.x = -tmpVadd.x / 2;
			//zoom = (float)1920 / (tmp + CAMERA_ADJ);
			//zoom_max *= 1.2;
		}
		else{
			_Move.x = (_Position.x + tmpVadd.x / 2) / FrameTime;
			_Move.y = (_Position.y + tmpVadd.y / 2) / FrameTime;
			/*
			if (_Position.y > -GROUND_HEIGHT) {
				_Move.y = (_Position.y + GetScene()->GetPlayer(0)->GetPosition().y + GetScene()->GetPlayer(0)->GetMove().y) / FrameTime;
				if (GetScene()->GetPlayer(0)->GetPosition().y > GetScene()->GetPlayer(1)->GetPosition().y) {
					_Move.y = (_Position.y + GetScene()->GetPlayer(1)->GetPosition().y + GetScene()->GetPlayer(1)->GetMove().y) / FrameTime;
				}
			}
			*/

			_Move.z = ((float)1920 / (tmp + CAMERA_ADJ) - zoom) / FrameTime;
		}
		//else { _Move.z = (1920.0f / (tmpVsub.x + tmpVsub.y + CAMERA_ADJ)-zoom) / FrameTime; }
	}

	if (_Move.z > 0.01) { _Move.z = 0.01; }
	if (_Move.z < -0.01) { _Move.z = -0.01; }
	if (_Move.x > 25) { _Move.x = 30; }
	if (_Move.x < -25) { _Move.x = -30; }
	if (_Move.y > 25) { _Move.y = 25; }
	if (_Move.y < 0) { _Move.y = 0; }
	_Position.x -= _Move.x;
	_Position.y -= _Move.y;
	zoom+=_Move.z;
	if (_Move.y < -GROUND_HEIGHT) { _Move.y = -GROUND_HEIGHT; }
	if (zoom > zoom_max) { zoom = zoom_max; }
	if (GetScene()->GetFPSCon()->GetHitStop() > 2* GetScene()->GetFPSCon()->GetFrameNum()) {
		if (zoom < zoom_max) {
			zoom += GetScene()->GetFPSCon()->GetHitStop() * 0.005;
		}
		else { zoom -= GetScene()->GetFPSCon()->GetHitStop() * 0.005; }
	}
	/*
		if ((tmpX1 - tmpX2) == 0) { zoom = ZOOM_MAX; }
	else {
		if ((tmpX1 - tmpX2) < 0) { zoom = 1920.0f / (tmpX2 - tmpX1 + CAMERA_ADJ); }
		else { zoom = 1920.0f / (tmpX1 - tmpX2 + CAMERA_ADJ); }
		if (zoom > ZOOM_MAX) { zoom = ZOOM_MAX; }
		//if (zoom < 0.2) { zoom = 0.2; }
	}
	*/

	_View = MMult(MGetTranslate(_Position),MGetScale(VGet(zoom, zoom, 1)));
	//_View = MGetScale(VGet(zoom, zoom, 1));
}

void CameraClass::init()
{
	SetMove(VGet(0, 0, 0));
	SetPosition(VGet(0, -GROUND_HEIGHT, 0));
}
