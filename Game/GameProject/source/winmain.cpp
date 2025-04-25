#include "DxLib.h"
#include "winmain.h"
#include "Main.h"

// プログラムはWinMain から始まります
int WINAPI WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(false);
	Set3DSoundOneMetre(50);
	// 初期化 -------------------------------------------------------------------------
	// ＤＸライブラリ初期化処理

	SetEnableXAudioFlag(TRUE);
	SetGraphMode(SCREEN_W, SCREEN_H, SCREEN_DEPTH);	// 画面の解像度を横1920×縦1080、1ドットあたり32ビットに指定する
	ChangeWindowMode(true);							// ウィンドウモードに指定する
	if (DxLib_Init() == -1)
	{	// エラーが起きたら直ちに終了
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// 描画先画面を裏画面にセット
	srand((unsigned)time(NULL));		// 乱数の初期化
	Main main;
	main.Init();
	// ゲームメイン
	main.RunLoop();


	// 解放 ---------------------------------------------------------------------------
	DxLib_End();		// ＤＸライブラリ使用の終了処理

	// 終了
	return 0;
}
