#include "ModelComponent.h"
#include "ActorClass.h"
#include "../ModelServer/ModelServer.h"

ModelComponent::ModelComponent(ActorClass* owner, const TCHAR* file, int draworder,bool useownersize)
	:Component(owner)
	, _Indipendent(false)
	// �Đ����Ԃ̏�����
	,_TotalTime(0.f)
	,_PlayTime(0.0f)
	,_AttachIndex(-1)
	, _Front(VGet(0, 0, 1))
	, _Up(VGet(0, 1, 0))
	, _Rot(VGet(0, 0, 0))
	, _Position(VGet(0, 0, 0))
	, _Scale(VGet(1, 1, 1))
	, _Center(VGet(0, 0, 0))
	, _UseOwnerSize(useownersize)
{
	// ���f���f�[�^�̃��[�h�i�e�N�X�`�����ǂݍ��܂��j
	//_Handle = MV1LoadModel("res/Debug/chinpo.mv1");
	_Handle = ModelServer::GetInstance()->Add(file);
	_Sprite = new ModelSpriteComponent(_Owner, this, draworder);
}



ModelComponent::~ModelComponent()
{
}

void ModelComponent::ProcessInput()
{

}

void ModelComponent::Update()
{
	SetModelInfo();
}

void ModelComponent::SetModelInfo()
{
	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(_Handle, _AttachIndex, _PlayTime);

	// ��������Y����]���Z�o
	VECTOR vRot = { 0,0,0 };
	vRot = MV1GetRotationXYZ(_Handle);
	MV1SetRotationXYZ(_Handle, GetRotation());
	MV1SetRotationZYAxis(_Handle, GetFront(), GetUp(), 0);

	if (_Front.z < 0.9 && _Front.z > -0.9) {
		int test = 0;
	}
	VECTOR v = VScale(GetCenter(), -1);
	v = VTransform(v, MGetRotX(vRot.x));
	v = VTransform(v, MGetRotY(vRot.y));
	v = VTransform(v, MGetRotZ(vRot.z));
	v = VAdd(v, GetCenter());
	// �ʒu
	if (_UseOwnerSize) {
		MV1SetPosition(_Handle, VAdd(VAdd(_Owner->GetPosition(), VMulti(_Position, _Owner->GetSize())), v));
		MV1SetScale(_Handle, VMulti(_Owner->GetSize(), _Scale));
	}
	else {
		MV1SetPosition(_Handle, VAdd(VAdd(_Owner->GetPosition(), _Position), v));
		MV1SetScale(_Handle, _Scale);
	}
	

}

VECTOR ModelComponent::GetFront()
{
	VECTOR front = _Front;
	if (!_Indipendent) {
		VECTOR Rot = _Owner->GetDirection();
		front = VTransform(front, MGetRotX(Rot.x));
		front = VTransform(front, MGetRotY(Rot.y));
		front = VTransform(front, MGetRotZ(Rot.z));
	}
	return front;
}

void ModelComponent::SetFront(VECTOR front)
{
	_Front = front;
	MV1SetRotationZYAxis(_Handle, GetFront(), GetUp(), 0);
	_Rot = MV1GetRotationXYZ(_Handle);
}

VECTOR ModelComponent::GetUp()
{
	VECTOR up = _Up;
	if (!_Indipendent) {
		VECTOR Rot = _Owner->GetDirection();
		up = VTransform(up, MGetRotX(Rot.x));
		up = VTransform(up, MGetRotY(Rot.y));
		up = VTransform(up, MGetRotZ(Rot.z));
	}
	return up;
}

void ModelComponent::SetRotation(VECTOR rot)
{
	_Rot = rot;
	VECTOR Rot = VAdd(rot, _Owner->GetDirection());
	//MV1SetRotationXYZ(_Handle, Rot);
	VECTOR front = VGet(0, 0, 1), up = VGet(0, 1, 0);
	front = VTransform(front, MGetRotX(rot.x));
	front = VTransform(front, MGetRotY(rot.y));
	front = VTransform(front, MGetRotZ(rot.z));
	_Front = front;
	up = VTransform(up, MGetRotX(rot.x));
	up = VTransform(up, MGetRotY(rot.y));
	up = VTransform(up, MGetRotZ(rot.z));
	_Up = up;
}

VECTOR ModelComponent::GetRotation()
{
	VECTOR rot = _Rot;
	if (!_Indipendent) {
		rot = VAdd(rot, _Owner->GetDirection());
	}
	return rot;
}

void ModelComponent::SetRotationZY(VECTOR front, VECTOR up)
{
	_Front = front;
	_Up = up;
	MV1SetRotationZYAxis(_Handle, front, up, 0);
	_Rot = MV1GetRotationXYZ(_Handle);
}

VECTOR ModelComponent::GetCenter()
{
	return VMulti(_Center, _Owner->GetSize());
}


ModelSpriteComponent::ModelSpriteComponent(ActorClass* owner,ModelComponent* model, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	,_Model(model)
{
}

ModelSpriteComponent::~ModelSpriteComponent()
{
}

void ModelSpriteComponent::Draw()
{
	
	/*
	// ���x���擾
	VECTOR v =_Owner -> GetMove();
	// �p�x���擾
	VECTOR rot = _Owner->GetRotation();
	VECTOR rot2 = _Owner->GetRotation2();

	//	���x����p�x���Z�o
	rot = VTransform(rot, MGetRotX(v.z/100 / _Owner->GetSize().x / 2));
	rot = VTransform(rot, MGetRotZ(-v.x/100 / _Owner->GetSize().x / 2));
	rot2 = VTransform(rot2, MGetRotX(v.z / 100 / _Owner->GetSize().x / 2));
	rot2 = VTransform(rot2, MGetRotZ(-v.x / 100 / _Owner->GetSize().x / 2));

	//	�p�x���Z�b�g

	MV1SetRotationZYAxis(_Model->GetHandle(),rot,rot2,0);

	_Owner->SetRotation(rot);
	_Owner->SetRotation2(rot2);
	//*/

	// �f�o�b�O�`��
	//_Owner->GetComponent<MoveCollisionComponent>()[0]->DebugDraw();
	
	{
		_Model->SetModelInfo();
		// �`��
		if (_Material.size() > 0)
		{
			MATERIALPARAM MatParam;
			for (auto m : _Material)
			{
				if (m.first == "diffuse")
				{
					MatParam.Diffuse = m.second;	// �f�B�t���[�Y�J���[
				}
				if (m.first == "ambient")
				{
					MatParam.Ambient = m.second;	// �A���r�G���g�J���[
				}
				if (m.first == "specular")
				{
					MatParam.Specular = m.second;	// �X�y�L�����J���[
					SetMaterialUseVertSpcColor(false);
				}
				if (m.first == "emissive")
				{
					MatParam.Emissive = m.second;	// �G�~�b�V�u�J���[
				}
				if (m.first == "power")
				{
					MatParam.Power = m.second.a;	// �X�y�L�����̋���
				}
			}
			int debug = SetMaterialParam(MatParam);
			int test = 0;
			//SetMaterialUseVertSpcColor(true);
		}

		else {
			SetMaterialUseVertSpcColor(true);
		}



		MV1DrawModel(_Model->GetHandle());
		//DrawFormatString(0,0,GetColor(255,255,255),"x %f, y %f, z %f",rot.x,rot.y,rot.z);

	}
}

void ModelSpriteComponent::SetImage()
{
}

