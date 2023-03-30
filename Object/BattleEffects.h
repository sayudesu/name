#pragma once
class BattleEffects
{
public:
	BattleEffects();
	virtual ~BattleEffects();

	virtual void Init();
	virtual void End();

	virtual void Hit(int x, int y);

	virtual	void GetStaminaNum(int stamina);
	virtual	void GetHealthNum(int health);

	virtual void Update();
	virtual void Draw();

private:
	int m_hitEffect_X,m_hitEffect_Y;//攻撃エフェクト位置
	int m_staminaNum;//スタミナ量
	int m_healthNum;//体力量

	int m_staminatEffect;//スタミナの量でエフェクトを調整
	int m_healthEffect;//体力の量でエフェクトを調整
};

