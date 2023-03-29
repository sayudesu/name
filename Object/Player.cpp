#include <DxLib.h>
#include "game.h"
#include "Pad.h"
#include "DrawFunctions.h"
#include "Player.h"

namespace
{
	constexpr int KinitialValue = 0;//初期値用

	const char* const kPlayer = "Data/Image/Player/Knight.png";//プレイヤー画像位置
	//横48　縦48
	constexpr int kPlayerImageSize = 48;

	constexpr float kPlayerSpeed = 6.0f;//プレイヤーのスピード

}

Player::Player() :
	m_hPlayer(-1),//プレイヤー画像
	m_attackLeft(0), m_attackTop(0), m_attackRight(0), m_attackBottom(0),//攻撃した座標
	m_attackLeftPos(0),//攻撃した座標調整
	m_playerImageLetf(0), m_playerImageTop(0),//プレイヤーの画像位置
	m_playerAnimationCut_X(0), m_playerAnimationCut_Y(0),////プレイヤー画像のX軸動きによって調整
	m_playerAnimationFrameCount(0),//アニメーション再生カウント
	m_MapMove_X(0),//マップの位置
	m_playerSpeed(0.0f),//プレイヤーの移動速度
	m_isPlayerDirection(false),//プレイヤーの向き false 右 : true	左 
	m_isAttackAnimation(false),//攻撃した場合のアニメーション
	m_isGuardAnimation(false),//攻撃を防ぐアニメーション
	m_playerPos(0.0f, 0.0f),//プレイヤーの位置
	m_playerVec(0.0f, 0.0f)//プレイヤーの運動量
{

}

Player::~Player()
{
}

void Player::Init()
{
	m_playerPos = { Game::kScreenWidth / 2 ,Game::kScreenHeight / 2 };

	m_hPlayer = my::MyLoadGraph(kPlayer);//画像のメモリ確保
}
void Player::End()
{
	//メモリ解放
	my::MyDeleteGraph(m_hPlayer);
}

//キャラクターを操作
void Player::PlayerMovement()
{
	Pad::update();

	//Idle
	m_playerAnimationCut_X = 4;
	m_playerAnimationCut_Y = 0;

	//プレイヤーの移動
	if (Pad::isPress(PAD_INPUT_UP))//上
	{
		m_playerVec.y -= m_playerSpeed;
	}
	if (Pad::isPress(PAD_INPUT_DOWN))//下
	{
		m_playerVec.y += m_playerSpeed;
	}
	if (Pad::isPress(PAD_INPUT_LEFT))//左
	{
		m_playerVec.x -= m_playerSpeed;

		m_playerAnimationCut_X = 7;//walk
		m_playerAnimationCut_Y = 1;

		m_isPlayerDirection = true;//方向を変更 左向き
		m_attackLeftPos = -110;
		if (m_MapMove_X < 10000)
		{
			if (m_playerPos.x < 500)
			{
				m_MapMove_X += kPlayerSpeed * 3;
			}
		}

	}
	if (Pad::isPress(PAD_INPUT_RIGHT))//右
	{
		m_playerVec.x += m_playerSpeed;

		m_playerAnimationCut_X = 7;//walk
		m_playerAnimationCut_Y = 1;

		m_isPlayerDirection = false;//方向を変更 右向き
		m_attackLeftPos = 60;
		if (m_MapMove_X > -10000)
		{
			if (m_playerPos.x > Game::kScreenWidth - 500)
			{
				m_MapMove_X -= kPlayerSpeed * 3;
			}
		}
	}
	if (Pad::isPress(PAD_INPUT_5))//下
	{
		m_playerAnimationCut_X = 4;
		m_playerAnimationCut_Y = 3;
	}
	printfDx("%d\n", m_MapMove_X);

	if (Pad::isTrigger(PAD_INPUT_1))//攻撃
	{
		m_isAttackAnimation = true;//攻撃した場合のアニメーションを再生
		m_playerImageLetf = 0;

	}

	if (m_isAttackAnimation)//攻撃した場合のアニメーション
	{
		m_playerAnimationCut_X = 9;
		m_playerAnimationCut_Y = 2;
	}
	if (Pad::isTrigger(PAD_INPUT_3))//ガード
	{
		m_isGuardAnimation = true;//攻撃した場合のアニメーション再生
		m_playerImageLetf = 0;
		m_playerSpeed = 0;
	}
	if (m_isGuardAnimation)//攻撃を防ぐアニメーション
	{
		m_playerAnimationCut_X = 8;
		m_playerAnimationCut_Y = 4;
	}

}

void Player::PlayerMoveScope()
{
	if (m_playerPos.x < 500)
	{
		m_playerPos.x = 500;
		m_playerVec.x = 500;
	}
	if (m_playerPos.x > Game::kScreenWidth - 500)
	{
		m_playerPos.x = Game::kScreenWidth - 500;
		m_playerVec.x = Game::kScreenWidth - 500;
	}
}

void Player::Update()
{
	m_playerSpeed = kPlayerSpeed;//移動速度
	m_playerPos = m_playerVec;//移動速度

	PlayerMovement();//キャラクターを操作
	PlayerMoveScope();//プレイヤーの行動範囲

	if (m_isAttackAnimation)//攻撃範囲
	{
		if (m_playerImageLetf > kPlayerImageSize * 6 &&//攻撃アニメーションの攻撃部分
			m_playerImageLetf < kPlayerImageSize * 8)
		{
			m_attackLeft = m_playerPos.x + m_attackLeftPos;
			m_attackTop = m_playerPos.y + 20;
			m_attackRight = m_attackLeft + 50;
			m_attackBottom = m_attackTop + 50;
		}
		else
		{
			m_attackLeft = 0;
			m_attackTop = 0;
			m_attackRight = 0;
			m_attackBottom = 0;
		}
	}

	m_playerAnimationFrameCount++;//アニメーション再生カウント
	if (m_playerAnimationFrameCount >= 4)
	{
		m_playerAnimationFrameCount = KinitialValue;
		m_playerImageTop = kPlayerImageSize * m_playerAnimationCut_Y;//Y軸をずらす

		if (m_playerImageLetf < kPlayerImageSize * m_playerAnimationCut_X)//
		{
			m_playerImageLetf += kPlayerImageSize;//X軸を右にずらす
		}
		else
		{
			m_isAttackAnimation = false;//攻撃した場合のアニメーションを停止
			m_isGuardAnimation = false;//攻撃を防ぐアニメーション停止

			m_playerImageLetf = KinitialValue;//X軸を初期値に戻す
		}
	}
	
}

void Player::Draw()
{
	//プレイヤーアニメーション描画
	my::MyDrawRectRotaGraph(static_cast<int>(m_playerPos.x), static_cast<int>(m_playerPos.y),
		m_playerImageLetf, m_playerImageTop, kPlayerImageSize, kPlayerImageSize,
		1.5 * 3, DX_PI * 2, m_hPlayer, true, m_isPlayerDirection);
	
	//攻撃範囲可視化
	DrawBox(m_attackLeft, m_attackTop, m_attackRight, m_attackBottom,0xffff00,true);
}