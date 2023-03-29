#pragma once
#include "Vec2.h"

class Player
{
public:
	Player();
	virtual ~Player();

	virtual void Init();
	virtual void End();

	virtual void PlayerMovement();//キャラクターを操作
	virtual void PlayerAnimation();//アニメーション処理
	virtual void PlayerAttackScope();//攻撃範囲
	virtual void PlayerMoveScope();//プレイヤーの行動範囲
//	virtual void PlayerStaminaControl();//体力管理
	virtual void PlayerStaminaControl();//スタミナ管理

	virtual void Update();//更新処理
	virtual void Draw();//描画処理
public:
	//プレイヤーの攻撃範囲
	int SetLeftPos() { return m_attackLeft; }//左上
	int SetTopPos() { return m_attackTop; }
	int SetRightPos() { return m_attackRight; }//右下
	int SetBottomPos() { return m_attackBottom; }
	int SetMapPosX() { return m_mapMove_X; }
	
	//プレイヤーのスタミナ
	float SetStaminaNum() { return m_staminaNum; }
	//プレイヤーの体力
	float SethealthNum() { return m_healthNum; }

private:
	int m_hPlayer;//プレイヤー画像
	int m_attackLeft, m_attackTop, m_attackRight, m_attackBottom;//攻撃した座標
	int m_attackLeftPos;//攻撃した座標調整
	int m_playerImageLetf, m_playerImageTop;//プレイヤーの画像位置
	int m_playerAnimationCut_X, m_playerAnimationCut_Y;//プレイヤー画像のX軸動きによって調整
	int m_playerAnimationFrameCount;//アニメーション再生カウント
	int m_playerAnimationFrameCountNextNum;//アニメーション再生するための数
	int m_mapMove_X;//マップの位置
	float m_staminaNum;//スタミナを管理
	float m_healthNum;//体力を管理
	float m_playerSpeed;//プレイヤーの移動速度
	bool m_isPlayerDirection;//プレイヤーの向き false 右 : true	左
	bool m_isAttackAnimation;//攻撃した場合のアニメーション
	bool m_isGuardAnimation;//攻撃を防ぐアニメーション
	bool m_isRun;//走れるかどうか
	Vec2 m_playerPos;//プレイヤーの位置
	Vec2 m_playerVec;//プレイヤーの運動量
};

