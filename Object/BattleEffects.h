#pragma once
class BattleEffects
{
public:
	BattleEffects();
	virtual ~BattleEffects();

	virtual void Init();
	virtual void End();

	void Hit(int x, int y);

	void Update();
	virtual void Draw();
private:
	int m_hitEffect_X,m_hitEffect_Y;
};

