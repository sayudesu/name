#include <Dxlib.h>
#include "BattleEffects.h"

BattleEffects::BattleEffects()
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

void BattleEffects::Update()
{
}

void BattleEffects::Draw()
{
	DrawString(m_hitEffect_X, m_hitEffect_Y,"HIT", 0xffffff);
}
