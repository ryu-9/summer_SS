#include "DxLib.h"
#include "winmain.h"
#include "Main.h"

// �v���O������WinMain ����n�܂�܂�
int WINAPI WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(false);
	Set3DSoundOneMetre(50);
	// ������ -------------------------------------------------------------------------
	// �c�w���C�u��������������

	SetEnableXAudioFlag(TRUE);
	SetGraphMode(SCREEN_W, SCREEN_H, SCREEN_DEPTH);	// ��ʂ̉𑜓x����1920�~�c1080�A1�h�b�g������32�r�b�g�Ɏw�肷��
	ChangeWindowMode(true);							// �E�B���h�E���[�h�Ɏw�肷��
	if (DxLib_Init() == -1)
	{	// �G���[���N�����璼���ɏI��
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// �`����ʂ𗠉�ʂɃZ�b�g
	srand((unsigned)time(NULL));		// �����̏�����
	Main main;
	main.Init();
	// �Q�[�����C��
	main.RunLoop();


	// ��� ---------------------------------------------------------------------------
	DxLib_End();		// �c�w���C�u�����g�p�̏I������

	// �I��
	return 0;
}
