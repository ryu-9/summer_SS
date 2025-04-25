/*
** WinMain
*/

//
// include ��
//

#include "../appframe.h"



//
// WinMain(). �v���O�����N���֐�
//
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	ApplicationBase *appBase = ApplicationBase::GetInstance();
	if (!appBase) { return 0; }

	SetZBufferBitDepth(64);
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		printf("CoInitializeEx failed: %#X\n", hr);
		return false;
	}
	if (!appBase->Initialize(hInstance)) {
		return 0;
	}

	// 1�t���[�����[�v��g�� ----------------------------------------------------------
	while (ProcessMessage() == 0)		// �v���O�������I������܂Ń��[�v
	{
		appBase->Input();
		appBase->Process();

		ClearDrawScreen();		// ��ʂ�����������
		appBase->Render();
		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f������
	}

	appBase->Terminate();

	return 0;
}
