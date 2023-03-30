#include <Dxlib.h>
#include "BattleEffects.h"
#include "game.h"

BattleEffects::BattleEffects():
	m_hitEffect_X(0), m_hitEffect_Y(0),//攻撃エフェクト位置
	m_staminaNum(0),//スタミナ量
	m_healthNum(0),//体力量
	m_staminatEffect(0),//スタミナの量でエフェクトを調整
	m_healthEffect(0)//体力の量でエフェクトを調整
{
}

BattleEffects::~BattleEffects()
{
}

void BattleEffects::Init()
{
}

void BattleEffects::End()
{
}

void BattleEffects::Hit(int x, int y)
{
	m_hitEffect_X = x + GetRand(30);
	m_hitEffect_Y = y + GetRand(30);
}

//プレイヤーのスタミナを管理する
void BattleEffects::GetStaminaNum(int stamina)
{
	m_staminaNum = stamina;//プレイヤーのスタミナを管理

	//エフェクト処理
	if (m_staminaNum > 30)m_staminatEffect--;//スタミナがある状態ではエフェクトをしない
	if (m_staminaNum < 30)m_staminatEffect++;//スタミナの量が一定数下がるとエフェクトをする

	//エフェクトの上限
	if (m_staminatEffect < 0)m_staminatEffect = 0;
	if (m_staminatEffect > 128)m_staminatEffect = 128;
}

//プレイヤーの体力を管理する
void BattleEffects::GetHealthNum(int health)
{
	m_healthNum = health;//体力スタミナを管理
	
	//エフェクト処理
	if (m_healthNum > 30)m_healthEffect--;//体力がある状態ではエフェクトをしない
	if (m_healthNum < 30)m_healthEffect++;//体力の量が一定数下がるとエフェクトをする

	//エフェクトの上限
	if (m_healthEffect < 0)m_healthEffect = 0;
	if (m_healthEffect > 80)m_healthEffect = 80;

}

void BattleEffects::Update()
{
}

void BattleEffects::Draw()
{
	//プレイヤーのスタミナのエフェクト
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_staminatEffect);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xff00ff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//プレイヤーの体力のエフェクト
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_healthEffect);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xff0000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//攻撃したエフェクト（仮）
	DrawString(m_hitEffect_X, m_hitEffect_Y,"HIT", 0xffffff);
}
