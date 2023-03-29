#include "DxLib.h"
#include "game.h"
#include "Scene/SceneManager.h"

#define  DRAW false;

#if DRAW

#include <cmath>
#include <vector>

namespace
{
	//原点からカメラまでの距離
	constexpr int kCameraDistance = 800.0f;

	//テクスチャ情報
	const char* const kTextureFilename = "texture01.png";

	//マップチップの分割数（）
	constexpr float kTextureDivNumX_F = 11.0f;
	constexpr float kTextureDivNumY_F = 8.0f;
	//使用するチップの番号(横位置、縦位置を指定する)
	constexpr int kUseTexture_X = 8;
	constexpr int kUseTexture_Y = 3;
	//使用するチップのテクスチャ座標
	constexpr float kTextureMinU = 1.0f / kTextureDivNumX_F * kUseTexture_X;
	constexpr float kTextureMaxU = kTextureMinU + 1.0f / kTextureDivNumX_F;
	constexpr float kTextureMinV = 1.0f / kTextureDivNumY_F * kUseTexture_Y;
	constexpr float kTextureMaxV = kTextureMinV + 1.0f / kTextureDivNumY_F;
}

void DrawGrid()
{
	for (float z = -1000.0f; z <= 1000.0f; z += 100.0f)
	{
		VECTOR start = VGet(-1000, 0.0f, z);
		VECTOR end = VGet(1000, 0.0f, z);
		DrawLine3D(start, end, 0xffff00);
	}

	for (float x = -1000.0f; x <= 1000.0f; x += 100.0f)
	{
		VECTOR start = VGet(x, 0.0f, -1000.0f);
		VECTOR end = VGet(x, 0.0f, 1000.0f);
		DrawLine3D(start, end, 0xffff00);
	}
}

//マップを構成する立方体の1面を表示
//原点を中心としてz-方向を向いた平面を描画

//指定位置を中心としてた指定サイズの立方体を表示すｒ
void DrawMapPolygon(VECTOR  pos,float size,int textrure)
{
	//ポリゴンの描画
	constexpr int polyNum = 2;//正方形１面描画するのに必要なポリゴンの数
	constexpr int vtxNum = polyNum * 3;//ポリゴンの１面分の描画に必要な頂点数
	constexpr int cubeVtxNum = polyNum * 6;//立方体１つの描画するのに必要な頂点数

	std::vector<VERTEX3D> drawVtx; //描画にしようする頂点データ

	VERTEX3D polyVtx[vtxNum]{};

	//左上
	polyVtx[0].pos = VGet(-size/ 2.0f, size/ 2.0f, 0.0f);
	polyVtx[0].norm = VGet(0.0f, 0.0f, -1.0f);
	polyVtx[0].dif = GetColorU8(255, 255, 255, 255);
	polyVtx[0].spc = GetColorU8(255, 255, 255, 255);
	polyVtx[0].u = 0.0f;
	polyVtx[0].v = 0.0f;
	polyVtx[0].su = 0.0f;
	polyVtx[0].sv = 0.0f;

	//0番目の頂点の情報を以降の頂点にコピーする
	for (int i = 0; i < vtxNum; i++)
	{
		polyVtx[i] = polyVtx[0];
	}

	//右上
	polyVtx[1].pos = VGet(size, 200.0f, 0.0f);
	polyVtx[1].u = kTextureMaxU;
	polyVtx[1].v = kTextureMinU;
	//左下
	polyVtx[2].pos = VGet(-200.0f, -200.0f, 0.0f);
	polyVtx[2].u = kTextureMinU;
	polyVtx[2].v = kTextureMaxU;

	//右下
	polyVtx[3].pos = VGet(200.0f, -200.0f, 0.0f);
	polyVtx[3].u = kTextureMaxU;
	polyVtx[3].v = kTextureMinU;
	//左下
	polyVtx[4].pos = VGet(-200.0f, -200.0f, 0.0f);
	polyVtx[4].u = kTextureMinU;
	polyVtx[4].v = kTextureMaxU;
	//右上
	polyVtx[5].pos = VGet(200.0f, 200.0f, 0.0f);
	polyVtx[5].u = kTextureMaxU;
	polyVtx[5].v = kTextureMinU;

	//描画の頂点データに登録
	for (auto& vtx : polyVtx)
	{
		drawVtx.push_back(vtx);
	}


	DrawPolygon3D(polyVtx, 2, textrure, false);

	//回転行列
	MATRIX mtx = MGetRotY(DX_PI_F / 2.0f);
	//側面の頂点データ生成、登録
	for (int i = 0; i < 3; i++)
	{
		for (auto& vtx : polyVtx)
		{
			vtx.pos = VTransform(polyVtx[i].pos, mtx);
			vtx.norm = VTransform(polyVtx[i].norm, mtx);
			drawVtx.push_back(vtx);
		}
	}
	//上面の頂点データ生成、登録
	mtx = MGetRotZ(DX_PI_F / 2.0f);
	for (int i = 0; i < 3; i++)
	{
		for (auto& vtx : polyVtx)
		{
			vtx.pos = VTransform(polyVtx[i].pos, mtx);
			vtx.norm = VTransform(polyVtx[i].norm, mtx);
			drawVtx.push_back(vtx);
		}
	}
	//下面の頂点データ生成、登録
	mtx = MGetRotZ(DX_PI_F / 2.0f);
	for (int i = 0; i < 3; i++)
	{
		for (auto& vtx : polyVtx)
		{
			vtx.pos = VTransform(polyVtx[i].pos, mtx);
			vtx.norm = VTransform(polyVtx[i].norm, mtx);
			drawVtx.push_back(vtx);
		}
	}
	for (auto& vtx : drawVtx)
	{
		vtx.pos = VAdd(vtx.pos, pos);
	}

	DrawPolygon3D(drawVtx.data(), drawVtx.size()/3, textrure, false);
}

#endif

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
#if DRAW
	//Zバッファを有効にする
	SetUseZBuffer3D(true);
	//Zバッファへの書き込みを行う
	SetWriteZBuffer3D(true);
	//裏面ポリゴンを表示しない
	SetUseBackCulling(false);

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

	//中心から見たカメラの方向
	float cameraAngle = 0.0f;

	//VECTOR spherePos = VGet(0.0f, 0.0f, 0.0f);
	//視野角
	float pers = 60.0f;

	int texture = LoadGraph(kTextureFilename);

#else
	// 最初のシーンの初期化
	SceneManager scene;
	scene.Init();
#endif
	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();

#if DRAW

		if (CheckHitKey(KEY_INPUT_UP))
		{
			
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
		
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			cameraAngle += 0.01;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			cameraAngle -= 0.01;
		}

		
		SetupCamera_Perspective(pers * DX_PI_F / 180.0f);
		VECTOR cameraPos = VGet(0.0f,300.0f,0.0f);
		cameraPos.x = sinf(cameraAngle) * kCameraDistance;
		cameraPos.z = cosf(cameraAngle) * kCameraDistance;
		SetCameraPositionAndTarget_UpVecY(cameraPos, VGet(0,0,0));//カメラの位置　カメラの注視点( 見ている座標 )

		DrawGrid();
		DrawMapPolygon(VGet(0.0f, 0.0f, 0.0f),200.0f,texture);

#else
		scene.Update();
		scene.Draw();
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
#if DRAW
	DeleteGraph(texture);
#else
	scene.End();
#endif

	// ＤＸライブラリ使用の終了処理
	DxLib_End();
	

	return 0;				// ソフトの終了 
}