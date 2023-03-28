#pragma once
class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Init();
	virtual void End();

	virtual void Update();
	virtual void Draw();
public:
	int SetLeftPos() {return m_enemyLeft;}
	int SetTopPos() { return m_enemyTop; }
	int SetRightPos() { return m_enemyRight; }
	int SetBottomPos() { return m_enemyBottom; }
private:
	int m_enemyLeft,m_enemyTop,m_enemyRight,m_enemyBottom;//エネミーサイズ
};

