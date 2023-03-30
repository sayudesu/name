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

	constexpr float kAcc = 0.3f;//プレイヤーの加速度
	constexpr float kPlayerMaxSpeed = 6.0f;//プレイヤーのスピード

	constexpr float kStaminaMax = 100.0f;//スタミナ最大数
	constexpr float kStaminaCharge = 0.20f;//スタミナ回復
	constexpr float kStaminaFall = 0.30f;//スタミナ減少

}

Player::Player() :
	m_hPlayer(-1),//プレイヤー画像
	m_attackLeft(0), m_attackTop(0), m_attackRight(0), m_attackBottom(0),//攻撃した座標
	m_attackLeftPos(0),//攻撃した座標調整
	m_playerImageLetf(0), m_playerImageTop(0),//プレイヤーの画像位置
	m_playerAnimationCut_X(0), m_playerAnimationCut_Y(0),////プレイヤー画像のX軸動きによって調整
	m_playerAnimationFrameCount(0),m_playerAnimationFrameCountNextNum(0),//アニメーション再生カウント//アニメーション再生するための数
	m_mapMove_X(0),//マップの位置
	m_staminaNum(0.0f),//スタミナを管理
	m_healthNum(0.0f),//体力を管理
	m_playerSpeed(0.0f),//プレイヤーの移動速度
	m_isPlayerDirection(false),//プレイヤーの向き false 右 : true	左 
	m_isAttackAnimation(false),m_isAttackRunAnimation(false),//攻撃した場合のアニメーション
	m_isGuardAnimation(false),//攻撃を防ぐアニメーション
	m_isRun(false),//走れるかどうか
	m_playerPos(0.0f, 0.0f),//プレイヤーの位置
	m_playerVec(0.0f, 0.0f)//プレイヤーの運動量
{

}

Player::~Player()
{
}

void Player::Init()
{
	m_playerPos = { static_cast<float>(Game::kScreenWidth / 2 + 20) ,static_cast<float>(Game::kScreenHeight / 2  + 200)};

	m_hPlayer = my::MyLoadGraph(kPlayer);//画像のメモリ確保

	m_staminaNum = 100.0f;//スタミナ
	m_healthNum = 100.0f;//体力
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
#if false
	//プレイヤーの移動
	if (Pad::isPress(PAD_INPUT_UP))//上
	{
		m_playerVec.y -= kAcc;//運動量を代入

		//運動量を確認しマックススピードを指定
		if (m_playerVec.y < -kPlayerMaxSpeed)	m_playerVec.y = -kPlayerMaxSpeed;
	}
	else if (Pad::isPress(PAD_INPUT_DOWN))//下
	{
		m_playerVec.y += kAcc;//運動量を代入
		//運動量を確認しマックススピードを指定
		if (m_playerVec.y > kPlayerMaxSpeed)	m_playerVec.y = kPlayerMaxSpeed;
	}
	else
	{
		m_playerVec.y *= 0.9f;
	}
#endif
	if (Pad::isPress(PAD_INPUT_LEFT))//左
	{
		m_playerVec.x -= kAcc;//運動量を代入

		//運動量を確認しマックススピードを指定
		if (m_playerVec.x < -kPlayerMaxSpeed)	m_playerVec.x = -kPlayerMaxSpeed;

		m_playerAnimationCut_X = 7;//walk
		m_playerAnimationCut_Y = 1;

		m_isPlayerDirection = true;//方向を変更 左向き

		m_attackLeftPos = -110;//攻撃X位置

		if (m_playerPos.x < 500)
		{
			if (m_mapMove_X < 10000)
			{
				m_mapMove_X += kPlayerMaxSpeed * 1;
			}
		}
	}
	else if (Pad::isPress(PAD_INPUT_RIGHT))//右
	{
		m_playerVec.x += kAcc;//運動量を代入

		//運動量を確認しマックススピードを指定
		if (m_playerVec.x > kPlayerMaxSpeed)	m_playerVec.x = kPlayerMaxSpeed;

		m_playerAnimationCut_X = 7;//walk
		m_playerAnimationCut_Y = 1;//攻撃X位置

		m_isPlayerDirection = false;//方向を変更 右向き

		m_attackLeftPos = 60;//攻撃X位置

		if (m_playerPos.x > Game::kScreenWidth - 500)
		{
			if (m_mapMove_X > -10000)
			{
				m_mapMove_X -= kPlayerMaxSpeed * 1;
			}
		}
	}
	else
	{
		m_playerVec.x *= 0.9f;
	}

	m_isAttackRunAnimation = false;//走り攻撃の範囲を指定しない

	if (m_isRun)//スタミナしだい
	{
		if (Pad::isPress(PAD_INPUT_5))//走り
		{
			m_playerAnimationCut_X = 4;
			m_playerAnimationCut_Y = 3;

			m_staminaNum -= kStaminaFall;//スタミナ減少

			m_isAttackRunAnimation = true;//走り攻撃の範囲を指定する

			//向いている方向に対して高速移動
			if (m_isPlayerDirection)
			{
				m_playerVec.x -= 0.3f;
				m_mapMove_X += kPlayerMaxSpeed + 3.0f;
			}
			else
			{
				m_playerVec.x += 0.3f;
				m_mapMove_X -= kPlayerMaxSpeed + 3.0f;
			}
		}
	}

	if (Pad::isTrigger(PAD_INPUT_1))//攻撃
	{
		m_isAttackAnimation = true;//攻撃した場合のアニメーションを再生
		m_playerImageLetf = 0;

	}

	if (m_isAttackAnimation)//攻撃した場合のアニメーション
	{
		m_playerAnimationCut_X = 9;
		m_playerAnimationCut_Y = 2;

		m_staminaNum -= kStaminaFall;//スタミナ減少
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

		m_staminaNum -= kStaminaFall;//スタミナ減少
	}

}

//アニメーション処理
void Player::PlayerAnimation()
{
	m_playerAnimationFrameCount++;//アニメーション再生カウント
	if (m_playerAnimationFrameCount > m_playerAnimationFrameCountNextNum)
	{
		m_playerAnimationFrameCount = KinitialValue;//アニメーション再生カウント初期化
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

//攻撃範囲
void Player::PlayerAttackScope()
{
	//通常攻撃
	if (m_isAttackAnimation)//攻撃範囲
	{
		if (m_playerImageLetf > kPlayerImageSize * 6 &&//攻撃アニメーションの攻撃部分
			m_playerImageLetf < kPlayerImageSize * 8)
		{
			//攻撃位置
			m_attackLeft = m_playerPos.x + m_attackLeftPos;//左上,右向きか左向きかで攻撃位置を変更
			m_attackTop = m_playerPos.y + 20;
			m_attackRight = m_attackLeft + 50;//右下
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
	//突進攻撃
	if (m_isAttackRunAnimation)
	{
		if (m_playerImageLetf > kPlayerImageSize * 0 &&//攻撃アニメーションの攻撃部分
			m_playerImageLetf < kPlayerImageSize * 4)
		{
			//攻撃位置
			m_attackLeft = m_playerPos.x + m_attackLeftPos;//左上,右向きか左向きかで攻撃位置を変更
			m_attackTop = m_playerPos.y + 20;
			m_attackRight = m_attackLeft + 50;//右下
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
	
	if(!m_isAttackAnimation && !m_isAttackRunAnimation)//攻撃してない場合の処理
	{
		m_attackLeft = 0;
		m_attackTop = 0;
		m_attackRight = 0;
		m_attackBottom = 0;
	}
}

//プレイヤーの行動範囲
void Player::PlayerMoveScope()
{
	//左移動の上限
	if (m_playerPos.x < 500)
	{
		m_playerPos.x = 500;
	}
	//右移動の上限
	if (m_playerPos.x > Game::kScreenWidth - 500)
	{
		m_playerPos.x = Game::kScreenWidth - 500;
	}

	//上移動の上限
	if (m_playerPos.y < 0)
	{
		m_playerPos.y = 0;
	}
	//下移動の上限
	if (m_playerPos.y > Game::kScreenHeight)
	{
		m_playerPos.y = Game::kScreenHeight;
	}
}

//スタミナ管理
void Player::PlayerStaminaControl()
{
	//スタミナの上限
	if (m_staminaNum < kStaminaMax)m_staminaNum += kStaminaCharge;
	//プレイヤーの動きを遅くする
	if (m_staminaNum <= 30.0f)m_playerAnimationFrameCountNextNum = 7;
	//走りを無効かする
	if (m_staminaNum <= 25.0f)m_isRun = false;//走れない
	else m_isRun = true;//走れる

	//スタミナの下限
	if (m_staminaNum < 0.0f)
	{
		m_staminaNum = 0.0f;
		m_healthNum -= 0.1f;//スタミナがなくなると体力が減少
	}
}

//更新処理
void Player::Update()
{
	//アニメーション再生するための数
	if(m_playerAnimationFrameCountNextNum != 4)m_playerAnimationFrameCountNextNum = 4;

	//Idle
	m_playerAnimationCut_X = 4;
	m_playerAnimationCut_Y = 0;

	PlayerMovement();//キャラクターを操作
	PlayerMoveScope();//プレイヤーの行動範囲
	PlayerAttackScope();//攻撃範囲

	//プレイヤーが少しでも動いていたら
	if (m_playerVec.x > 0.01f && m_playerVec.x < 1.0f ||
		m_playerVec.x < -0.01f && m_playerVec.x > -1.0f)
	{
		//walk
		//m_playerAnimationCut_X = 7;
		//m_playerAnimationCut_Y = 1;
		//m_playerAnimationFrameCountNextNum = 4;
	}

	PlayerStaminaControl();//スタミナ管理
	PlayerAnimation();//アニメーション処理

	m_playerPos += m_playerVec;//移動量
}

//描画処理
void Player::Draw()
{
	//プレイヤーアニメーション描画
	my::MyDrawRectRotaGraph(static_cast<int>(m_playerPos.x), static_cast<int>(m_playerPos.y),
		m_playerImageLetf, m_playerImageTop, kPlayerImageSize, kPlayerImageSize,
		1.5 * 3, DX_PI * 2, m_hPlayer, true, m_isPlayerDirection);
	
	//攻撃範囲可視化
	DrawBox(m_attackLeft, m_attackTop, m_attackRight, m_attackBottom,0xffff00,true);
}