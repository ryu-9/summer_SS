
#include "ApplicationBase.h"
#include <vector>
#include <DXLib.h>

ApplicationBase	*ApplicationBase::_lpInstance = NULL;

ApplicationBase::ApplicationBase() {
	_lpInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// DX���C�u�����̏�����
	if (AppWindowed()) {
		ChangeWindowMode(true);							// �E�B���h�E���[�h�Ɏw�肷��
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);

	SetZBufferBitDepth(32);	// Z�o�b�t�@�̃r�b�g�[�x��24bit�ɐݒ�

	
	SetUseDirect3DVersion(DX_DIRECT3D_11);	// Direct3D11���g�p����
	
	if (DxLib_Init() == -1)
	{	// �G���[���N�����璼���ɏI��
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// �`����ʂ𗠉�ʂɃZ�b�g


	// ����������
	srand((unsigned int)time(NULL));
	
	// ���[�h�T�[�o�̏�����
	_serverMode = new ModeServer();
	_serverModel = new ModelServer();
	_serverSound = new SoundServer();

	return true;
}

bool ApplicationBase::Terminate() {
	// DX���C�u�����J��
	DxLib_End();

	return true;
}


bool ApplicationBase::Input() {
	// �L�[�̓��́A�g���K���͂𓾂�
	{
		int keyold = _gKey[0];
		_gKey[0] = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		_gTrg[0] = (_gKey[0] ^ keyold) & _gKey[0];	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
		_gRel[0] = (_gKey[0] ^ keyold) & keyold;	// �L�[�̃����[�X��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
	}

	{
		int keyold = _gKey[1];
		_gKey[1] = GetJoypadInputState(DX_INPUT_PAD2);
		_gTrg[1] = (_gKey[1] ^ keyold) & _gKey[1];	// �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
		_gRel[1] = (_gKey[1] ^ keyold) & keyold;	// �L�[�̃����[�X��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
	}
	
	return true;
}

bool ApplicationBase::Process() {
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();
	SoundServer::GetInstance()->UpdateDeleteSV();
	return true;
}

bool ApplicationBase::Update()
{
	return false;
}

bool ApplicationBase::Render() {
	_serverMode->RenderInit();
	_serverMode->Render();
	_serverMode->RenderFinish();
	return true;
}
