#include <Dxlib.h>
#include "game.h"
#include "Enemy.h"

Enemy::Enemy():
	m_enemyLeft(0), m_enemyTop(0), m_enemyRight(0), m_enemyBottom(0)//エネミーサイズ
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::End()
{
}

void Enemy::Update()
{
	m_enemyLeft = Game::kScreenWidth / 2;
	m_enemyTop = Game::kScreenHeight / 2;
	m_enemyRight = m_enemyLeft + 100;
	m_enemyBottom = m_enemyTop + 200;
}

void Enemy::Draw()
{
	DrawBox(m_enemyLeft, m_enemyTop, m_enemyRight,m_enemyBottom, 0xaa0000, true);
}
