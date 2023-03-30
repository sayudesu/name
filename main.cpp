#include <DxLib.h>
#include "game.h"
#include "Scene/SceneManager.h"

#define  DRAW false;
#define td true;

#if DRAW

#include <cmath>
#include <vector>

namespace
{
	//原点からカメラまでの距離
	constexpr int kCameraDistance = 800.0f;

	//テクスチャ情報a
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

//グリッド描画
//////////////////////void DrawGrid()
//////////////////////{
//////////////////////	for (float z = -1000.0f; z <= 1000.0f; z += 100.0f)
//////////////////////	{
//////////////////////		VECTOR start = VGet(-1000, 0.0f, z);
//////////////////////		VECTOR end = VGet(1000, 0.0f, z);
//////////////////////		DrawLine3D(start, end, 0xffff00);
//////////////////////	}
//////////////////////
//////////////////////	for (float x = -1000.0f; x <= 1000.0f; x += 100.0f)
//////////////////////	{
//////////////////////		VECTOR start = VGet(x, 0.0f, -1000.0f);
//////////////////////		VECTOR end = VGet(x, 0.0f, 1000.0f);
//////////////////////		DrawLine3D(start, end, 0xffff00);
//////////////////////	}
//////////////////////}
//
////マップを構成する立方体の1面を表示
////原点を中心としてz-方向を向いた平面を描画
//
////指定位置を中心としてた指定サイズの立方体を表示すｒ
//void DrawMapPolygon(VECTOR  pos,float size,int textrure)
//{
//	//ポリゴンの描画
//	constexpr int polyNum = 2;//正方形１面描画するのに必要なポリゴンの数
//	constexpr int vtxNum = polyNum * 3;//ポリゴンの１面分の描画に必要な頂点数
//	constexpr int cubeVtxNum = polyNum * 6;//立方体１つの描画するのに必要な頂点数
//
//	std::vector<VERTEX3D> drawVtx; //描画にしようする頂点データ
//
//	VERTEX3D polyVtx[vtxNum]{};
//
//	//左上
//	polyVtx[0].pos = VGet(-size/ 2.0f, size/ 2.0f, -size / 2.0f);
//	polyVtx[0].norm = VGet(0.0f, 0.0f, -1.0f);
//	polyVtx[0].dif = GetColorU8(255, 255, 255, 255);
//	polyVtx[0].spc = GetColorU8(255, 255, 255, 255);
//	polyVtx[0].u = kTextureMinU;
//	polyVtx[0].v = kTextureMinV;
//	polyVtx[0].su = 0.0f;
//	polyVtx[0].sv = 0.0f;
//
//	//0番目の頂点の情報を以降の頂点にコピーする
//	for (int i = 0; i < vtxNum; i++)
//	{
//		polyVtx[i] = polyVtx[0];
//	}
//
//	//右上
//	polyVtx[1].pos = VGet(size, 200.0f, 0.0f);
//	polyVtx[1].u = kTextureMaxU;
//	polyVtx[1].v = kTextureMinU;
//	//左下
//	polyVtx[2].pos = VGet(-200.0f, -200.0f, 0.0f);
//	polyVtx[2].u = kTextureMinU;
//	polyVtx[2].v = kTextureMaxU;
//
//	//右下
//	polyVtx[3].pos = VGet(200.0f, -200.0f, 0.0f);
//	polyVtx[3].u = kTextureMaxU;
//	polyVtx[3].v = kTextureMinU;
//	//左下
//	polyVtx[4].pos = VGet(-200.0f, -200.0f, 0.0f);
//	polyVtx[4].u = kTextureMinU;
//	polyVtx[4].v = kTextureMaxU;
//	//右上
//	polyVtx[5].pos = VGet(200.0f, 200.0f, 0.0f);
//	polyVtx[5].u = kTextureMaxU;
//	polyVtx[5].v = kTextureMinU;
//
//	//描画の頂点データに登録
//	for (auto& vtx : polyVtx)
//	{
//		drawVtx.push_back(vtx);
//	}
//
//
//	//DrawPolygon3D(polyVtx, 2, textrure, false);
//
//	//回転行列
//	MATRIX mtx = MGetRotY(DX_PI_F / 2.0f);
//	//側面の頂点データ生成、登録
//	for (int i = 0; i < 3; i++)
//	{
//		for (auto& vtx : polyVtx)
//		{
//			vtx.pos = VTransform(polyVtx[i].pos, mtx);
//			vtx.norm = VTransform(polyVtx[i].norm, mtx);
//			drawVtx.push_back(vtx);
//		}
//	}
//	//上面の頂点データ生成、登録
//	mtx = MGetRotZ(DX_PI_F / 2.0f);
//	for (int i = 0; i < 3; i++)
//	{
//		for (auto& vtx : polyVtx)
//		{
//			vtx.pos = VTransform(polyVtx[i].pos, mtx);
//			vtx.norm = VTransform(polyVtx[i].norm, mtx);
//			drawVtx.push_back(vtx);
//		}
//	}
//	//下面の頂点データ生成、登録
//	mtx = MGetRotZ(DX_PI_F / 2.0f);
//	for (int i = 0; i < 3; i++)
//	{
//		for (auto& vtx : polyVtx)
//		{
//			vtx.pos = VTransform(polyVtx[i].pos, mtx);
//			vtx.norm = VTransform(polyVtx[i].norm, mtx);
//			drawVtx.push_back(vtx);
//		}
//	}
//	for (auto& vtx : drawVtx)
//	{
//		vtx.pos = VAdd(vtx.pos, pos);
//	}
//
//	DrawPolygon3D(drawVtx.data(), drawVtx.size()/3, textrure, false);
//}

#endif
#if td
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
	SceneManager* scene;
	scene = new SceneManager;
	scene->Init();
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

		DrawMapPolygon(VGet(200.0f, 0.0f, 0.0f),200.0f,texture);

		//DrawMapPolygon(VGet(200.0f, 0.0f, 0.0f), 200.0f, texture);
		//DrawMapPolygon(VGet(200.0f, 0.0f, 0.0f), 200.0f, texture);

#else
		scene->Update();
		scene->Draw();
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
	scene->End();
#endif

	// ＤＸライブラリ使用の終了処理
	DxLib_End();
	

	return 0;				// ソフトの終了 
}
#else

// 指定位置を中心とした指定サイズの立方体を表示する
void DrawMapPolygon(VECTOR pos, float size, int texture)
{
	constexpr int polyNum = 2;//正方形１面描画するのに必要なポリゴンの数
	constexpr int vtxNum = polyNum * 3;//ポリゴン１面分の描画に必要な頂点数
	constexpr int cuveVtxNum = vtxNum * 6;//立方体1つ描画するのに必要な超点数



	std::vector<VERTEX3D> drawVtx; //描画に使用する頂点データ



	VERTEX3D polyVtx[vtxNum];



	//左上
	polyVtx[0].pos = VGet(-size / 2.0f, size / 2.0f, -size / 2.0f);
	polyVtx[0].norm = VGet(0.0f, 0.0f, -1.0f);
	polyVtx[0].dif = GetColorU8(255, 255, 255, 255);
	polyVtx[0].spc = GetColorU8(255, 255, 255, 255);
	polyVtx[0].u = kTextureMinU;
	polyVtx[0].v = kTextureMinV;
	polyVtx[0].su = 0.0f;
	polyVtx[0].sv = 0.0f;



	//0番目の頂点の情報を以降の頂点にコピーする
	for (int i = 1; i < vtxNum; i++) {
		polyVtx[i] = polyVtx[0];
	}



	//右上
	polyVtx[1].pos = VGet(size / 2.0f, size / 2.0f, -size / 2.0f);
	polyVtx[1].u = kTextureMaxU;
	polyVtx[1].v = kTextureMinV;
	//左下
	polyVtx[2].pos = VGet(-size / 2.0f, -size / 2.0f, -size / 2.0f);
	polyVtx[2].u = kTextureMinU;
	polyVtx[2].v = kTextureMaxV;
	//右下
	polyVtx[3].pos = VGet(size / 2.0f, -size / 2.0f, -size / 2.0f);
	polyVtx[3].u = kTextureMaxU;
	polyVtx[3].v = kTextureMaxV;
	//左下
	polyVtx[4].pos = VGet(-size / 2.0f, -size / 2.0f, -size / 2.0f);
	polyVtx[4].u = kTextureMinU;
	polyVtx[4].v = kTextureMaxV;
	//右上
	polyVtx[5].pos = VGet(size / 2.0f, size / 2.0f, -size / 2.0f);
	polyVtx[5].u = kTextureMaxU;
	polyVtx[5].v = kTextureMinV;



	//描画の頂点データに登録
	for (auto& vtx : polyVtx) {
		drawVtx.push_back(vtx);
	}



	//回転行列
	MATRIX mtx = MGetRotY(DX_PI_F / 2.0f);
	//側面の頂点データ生成、登録
	for (int i = 0; i < 3; i++) {
		for (auto& vtx : polyVtx) {
			vtx.pos = VTransform(vtx.pos, mtx);
			vtx.norm = VTransform(vtx.norm, mtx);
			drawVtx.push_back(vtx);
		}
	}



	mtx = MGetRotZ(DX_PI_F / 2.0f);
	for (auto& vtx : polyVtx) {
		vtx.pos = VTransform(vtx.pos, mtx);
		vtx.norm = VTransform(vtx.norm, mtx);
		drawVtx.push_back(vtx);
	}



	mtx = MGetRotZ(DX_PI_F);
	for (auto& vtx : polyVtx) {
		vtx.pos = VTransform(vtx.pos, mtx);
		vtx.norm = VTransform(vtx.norm, mtx);
		drawVtx.push_back(vtx);
	}



	//最後に位置情報を足す
	for (auto& vtx : drawVtx) {
		vtx.pos = VAdd(vtx.pos, pos);
	}



	DrawPolygon3D(drawVtx.data(), static_cast<int>(drawVtx.size() / 3), texture, true);
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);




	if (DxLib_Init() == -1)// ＤＸライブラリ初期化処理
	{
		return -1;// エラーが起きたら直ちに終了
	}



	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
	// Zバッファを有効にする
	SetUseZBuffer3D(true);
	// Zバッファへの書き込みを行う
	SetWriteZBuffer3D(true);



	// 裏側ポリゴンを表示しない
	SetUseBackCulling(true);



	// カメラの設定
	SetCameraNearFar(5.0f, 3000.0f);
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f));

	// マテリアル設定
	MATERIALPARAM Material{};
	Material.Diffuse = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	Material.Specular = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
	Material.Ambient = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);// アンビエントライトを反射させる
	Material.Emissive = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);
	Material.Power = 20.0f;
	SetMaterialParam(Material);



	// 球の位置
	VECTOR spherePos = VGet(0.0f, 200.0f, 0.0f);
	// 中心から見たカメラの方向
	float cameraAngle = DX_PI_F;
	float cameraAngleY = 0.5f;
	float cameraVecX = 0.0f;
	float cameraVecY = 0.0f;



	// 中心から見たカメラの方向
	float cameraAngleAxisX = 0.0f;
	float cameraAngleAxisY = 0.0f;



	// 視野角
	float pers = 60.0f;



	int texture = LoadGraph("data/img/texture01.png");



	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();
		// 画面のクリア
		ClearDrawScreen();



		int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (key & PAD_INPUT_UP)
		{
			//spherePos.z += 10.0f;
			//cameraAngleY += 0.05f;
			cameraAngleAxisX += 0.01f;
		}
		if (key & PAD_INPUT_DOWN)
		{
			//spherePos.z -= 10.0f;
			//cameraAngleY -= 0.05f;
			cameraAngleAxisX -= 0.01f;
		}
		if (key & PAD_INPUT_RIGHT)
		{
			//pers -= 1.0f;
			//spherePos.x += 10.0f;
			//cameraAngle -= 0.05f;
			cameraAngleAxisY -= 0.01f;
		}
		if (key & PAD_INPUT_LEFT)
		{
			//pers += 1.0f;
			//spherePos.x -= 10.0f;
			//cameraAngle += 0.05f;
			cameraAngleAxisY += 0.01f;
		}



		if (CheckHitKey(KEY_INPUT_W))
		{
			spherePos.z += 10.0f;
		}
		if (CheckHitKey(KEY_INPUT_S))
		{
			spherePos.z -= 10.0f;
		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			//pers -= 1.0f;
			spherePos.x += 10.0f;
		}
		if (CheckHitKey(KEY_INPUT_A))
		{
			//pers += 1.0f;
			spherePos.x -= 10.0f;
		}
		// カメラリセット
		if (CheckHitKey(KEY_INPUT_R))
		{
			/*cameraAngle = DX_PI_F;
			cameraAngleY = 0.5f;*/
			if (cameraAngle <= DX_PI_F)
			{
				cameraVecX = 0.1f;
			}
			else if (cameraAngle >= DX_PI_F)
			{
				cameraVecX = -0.1f;
			}
			if (cameraAngleY <= 0.5f)
			{
				cameraVecY = 0.05f;
			}
			else if (cameraAngleY >= 0.5f)
			{
				cameraVecY = -0.05f;
			}
		}



		if (cameraAngleY >= 1.5f)
		{
			cameraAngleY = 1.5f;
		}
		if (cameraAngleY <= 0.1f)
		{
			cameraAngleY = 0.1f;
		}
		if (cameraVecX != 0 || cameraVecY != 0)
		{
			if (cameraAngle >= 3.0f && cameraAngle <= 3.2f)
			{
				cameraVecX = 0;
				cameraAngle = DX_PI_F;
			}
			if (cameraAngleY >= 0.5f && cameraAngleY <= 0.6f)
			{
				cameraVecY = 0;
				cameraAngleY = 0.5f;
			}
		}




		cameraAngle += cameraVecX;
		cameraAngleY += cameraVecY;
		if (cameraAngle >= 3.8f)
		{
			cameraAngle = 3.8f;
		}
		if (cameraAngle <= 2.48f)
		{
			cameraAngle = 2.48f;
		}



		// 視野角を毎フレーム変更する
		SetupCamera_Perspective(pers * DX_PI_F / 180.0f);
		// カメラの位置
		//VECTOR posCamera = VGet(spherePos.x, spherePos.y + 300.0f, spherePos.z - 1000.0f);
		// カメラのターゲット一を毎フレーム変更する
		//SetCameraPositionAndTarget_UpVecY(/*posCamera*/VGet(0.0f, 300.0f, -1000.0f), VGet(0.0f, 0.0f, 0.0f));
#if false
		VECTOR cameraPos = VGet(0.0f, 300.0f, 0.0f);
		cameraPos.x = sinf(cameraAngle) * kCameraDistance;
		cameraPos.y = sinf(cameraAngleY) * kCameraDistance;
		//cameraPos.y = sinf(cameraAngle) * kCameraDistance;
		//cameraPos.z = sinf(cameraAngle) * kCameraDistance;
		//cameraPos.x = cosf(cameraAngle) * kCameraDistance;
		//cameraPos.y = cosf(cameraAngle) * kCameraDistance;
		cameraPos.z = cosf(cameraAngle) * kCameraDistance;
		//cameraPos.x = cosf(cameraAngleY) * kCameraDistance;

		//SetCameraPositionAndTarget_UpVecY(cameraPos, VGet(0.0f, 0.0f, 0.0f));



		SetCameraPositionAndTarget_UpVecY(VGet(cameraPos.x + spherePos.x, cameraPos.y + spherePos.y, cameraPos.z + spherePos.z), spherePos);
#else
		VECTOR cameraPos = VGet(0.0f, 300.0f, -800.0f);// カメラ初期位置
		//MATRIX mtx = MGetRotY(cameraAngle);
		MATRIX mtxAixsX = MGetRotX(cameraAngleAxisX);
		MATRIX mtxAixsY = MGetRotY(cameraAngleAxisY);
		MATRIX mtx = MMult(mtxAixsX, mtxAixsY);
		cameraPos = VTransform(cameraPos, mtx);
		SetCameraPositionAndTarget_UpVecY(cameraPos, VGet(0.0f, 0.0f, 0.0f));
#endif



		// グリッドを表示
		DrawGrid();



		// ポリゴンの表示
		DrawMapPolygon(VGet(0.0f, 0.0f, 0.0f), 200.0f, texture);
		DrawMapPolygon(VGet(-200.0f, 0.0f, 0.0f), 200.0f, texture);
		DrawMapPolygon(VGet(0.0f, 0.0f, -200.0f), 200.0f, texture);



		// 原点に球を表示する
		DrawSphere3D(spherePos, 100.0f, 32, 0xffffff, 0xffffff, true);
		// 現在の視野角をデバッグ表示
		DrawFormatString(0, 0, 0xffffff, "pers = %f", pers);
		DrawFormatString(0, 20, 0xffffff, "cameraAngle = %f", cameraAngle);
		DrawFormatString(0, 40, 0xffffff, "cameraAngleY = %f", cameraAngleY);
		DrawFormatString(0, 60, 0xffffff, "spherePos.x = %f", spherePos.x);
		DrawFormatString(0, 80, 0xffffff, "spherePos.y = %f", spherePos.y);
		DrawFormatString(0, 100, 0xffffff, "spherePos.z = %f", spherePos.z);
		DrawFormatString(0, 140, 0xffffff, "cameraVecX = %f", cameraVecX);
		DrawFormatString(0, 160, 0xffffff, "cameraVecY = %f", cameraVecY);



		COLOR_F ambColor = GetLightAmbColor();
		DrawFormatString(0, 120, 0xffffff, "amb = (%.4f, %.4f, %.4f, %.4f)",
			ambColor.r,
			ambColor.g,
			ambColor.b,
			ambColor.a);



		DrawFormatString(0, 100, 0xffffff, "spherePos.z = %f", spherePos.z);



		// 裏画面を表画面を入れ替える
		ScreenFlip();



		// escきーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}



	DeleteGraph(texture);



	DxLib_End();// ＤＸライブラリ使用の終了処理



	return 0;// ソフトの終了 
}


#endif