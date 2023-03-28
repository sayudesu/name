#include "DxLib.h"
#include "game.h"
#include "Scene/SceneManager.h"

#define  Draw false;

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	//マウスカーソル表示
	SetMouseDispFlag(Game::kMouseMode);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
#if Draw
	//Zバッファを有効にする
	SetUseZBuffer3D(true);
	//Zバッファへの書き込みを行う
	SetWriteZBuffer3D(true);
	//カメラ範囲
	SetCameraNearFar(5.0f, 2000.0f);
	//FOV
	
	//カメラ位置＆どこを見ているか
	SetCameraPositionAndTarget_UpVecY(VGet(0, 300, -800), VGet(0, 0, 0));

	float posX = 0;
	float posY = 300;
	float posZ = -800;

	float eyeX = 0;
	float eyeY = 0;
	float eyeZ = 0;


	VECTOR spherePos = VGet(0.0f, 0.0f, 0.0f);
	//視野角
	float pers = 60.0f;
#endif
	// 最初のシーンの初期化
	SceneManager scene;
	scene.init();

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

		scene.update();
		scene.draw();
#if Draw
		for (float z = -1000.0f; z <= 1000.0f; z += 100.0f)
		{
			VECTOR start = VGet(-1000, 0.0f, z);
			VECTOR end   = VGet( 1000, 0.0f, z);
			DrawLine3D(start,end,0xffff00);
		}

		for (float x = -1000.0f; x <= 1000.0f; x += 100.0f)
		{
			VECTOR start = VGet(x, 0.0f, -1000.0f);
			VECTOR end = VGet(x, 0.0f, 1000.0f);
			DrawLine3D(start, end, 0xffff00);
		}


		//SetupCamera_Perspective(pers * DX_PI_F / 180.0f);
		//SetCameraPositionAndTarget_UpVecY(VGet(posX, posY, posZ), VGet(eyeX, eyeY, eyeZ));//カメラの位置　カメラの注視点( 見ている座標 )

		//if (CheckHitKey(KEY_INPUT_UP))
		//{
		//	spherePos.y += 10.0f;
		//}
		//if (CheckHitKey(KEY_INPUT_DOWN))
		//{
		//	spherePos.y -= 10.0f;
		//}
		//if (CheckHitKey(KEY_INPUT_LEFT))
		//{
		//	spherePos.x -= 10.0f;
		//}
		//if (CheckHitKey(KEY_INPUT_RIGHT))
		//{
		//	spherePos.x += 10.0f;
		//}
		

		//ポリゴンの描画

		VERTEX3D polyVtx[3];
		polyVtx[0].pos = VGet(-200.0f, 0.0f, 200.0f);
		polyVtx[0].norm = VGet(0.0f, 1.0f, 0.0f);
		polyVtx[0].dif = GetColorU8(255, 255, 255, 255);
		polyVtx[0].spc = GetColorU8(255, 255, 255, 255);
		polyVtx[0].u = 0.0f;
		polyVtx[0].v = 0.0f;
		polyVtx[0].su = 0.0f;
		polyVtx[0].sv = 0.0f;

		polyVtx[1] = polyVtx[0];
		polyVtx[2] = polyVtx[0];

		polyVtx[1].pos = VGet(200.0f, 0.0f, 200.0f);
		polyVtx[2].pos = VGet(-200.0f, 0.0f, -200.0f);


		DrawPolygon3D(polyVtx, 1, DX_NONE_GRAPH, false);

		DrawSphere3D(spherePos, 16.0f * 2.0f, 32,0xffffff, 0xffffff,true);


		SetupCamera_Perspective(pers * DX_PI_F / 180.0f);
		SetCameraPositionAndTarget_UpVecY(VGet(0, 300, -800), spherePos);//カメラの位置　カメラの注視点( 見ている座標 )
#endif
		//裏画面を表画面を入れ替える
		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	scene.end();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}