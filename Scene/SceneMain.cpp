#include <DxLib.h>
#include "SceneMain.h"
#include "game.h"

namespace
{
	constexpr int KinitialValue = 0;//初期値用

	const char* const kPlayer = "Data/Image/Player/Knight.png";//プレイヤー画像位置
	//横48　縦48
	constexpr int kPlayerImageSize = 48;

	constexpr float kPlayerSpeed = 100.0f;//プレイヤーのスピード

}

SceneMain::SceneMain():
	m_hPlayer(-1),//プレイヤー画像
	m_playerImageLetf(0),m_playerImageTop(0),//プレイヤーの画像位置
	m_playerAnimationCut_X(0), m_playerAnimationCut_Y(0),////プレイヤー画像のX軸動きによって調整
	m_playerDirection(false),//プレイヤーの向き false 右 : true	左 
	m_playerPos(0.0f, 0.0f)//プレイヤーの位置
{

}

SceneMain::~SceneMain()
{
}

void SceneMain::init()
{
	m_hPlayer = LoadGraph(kPlayer);//画像のメモリ確保
}
void SceneMain::end()
{
	DeleteGraph(m_hPlayer);//メモリ解放
}

SceneBase* SceneMain::update()
{
	//Idle
	m_playerAnimationCut_X = 4;
	m_playerAnimationCut_Y = 0;


	//プレイヤーの移動
	if (CheckHitKey(KEY_INPUT_W))//上
	{
		m_playerPos.y -= kPlayerSpeed;
	}
	if (CheckHitKey(KEY_INPUT_S))//下
	{
		m_playerPos.y += kPlayerSpeed;
	}
	if (CheckHitKey(KEY_INPUT_A))//左
	{
		m_playerPos.x -= kPlayerSpeed;

		m_playerAnimationCut_X = 7;//walk
		m_playerAnimationCut_Y = 1;

		m_playerDirection = true;//方向を変更 左向き
	}
	if (CheckHitKey(KEY_INPUT_D))//右
	{
		m_playerPos.x += kPlayerSpeed;

		m_playerAnimationCut_X = 7;//walk
		m_playerAnimationCut_Y = 1;

		m_playerDirection = false;//方向を変更 右向き
	}
	if (CheckHitKey(KEY_INPUT_C))//下
	{
		m_playerAnimationCut_X = 8;
		m_playerAnimationCut_Y = 4;
	}
	if (CheckHitKey(KEY_INPUT_LSHIFT))//下
	{
		m_playerAnimationCut_X = 4;
		m_playerAnimationCut_Y = 5;
	}


	//Idle
	
	m_playerImageTop = kPlayerImageSize * m_playerAnimationCut_Y;//Y軸をずらす

	if (m_playerImageLetf < kPlayerImageSize * m_playerAnimationCut_X)//
	{
		m_playerImageLetf += kPlayerImageSize;//X軸を右にずらす
	}
	else
	{
		m_playerImageLetf = KinitialValue;//X軸を初期値に戻す
	}

	return this;
}

void SceneMain::draw()
{
	//プレイヤーアニメーション描画
	DrawRectRotaGraph(static_cast<int>(m_playerPos.x), static_cast<int>(m_playerPos.y),
		m_playerImageLetf, m_playerImageTop, kPlayerImageSize, kPlayerImageSize,
		1.5 * 3, DX_PI * 2, m_hPlayer, false, m_playerDirection);
}