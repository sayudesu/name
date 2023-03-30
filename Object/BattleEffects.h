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
	int m_hitEffect_X,m_hitEffect_Y;//�U���G�t�F�N�g�ʒu
	int m_staminaNum;//�X�^�~�i��
	int m_healthNum;//�̗͗�

	int m_staminatEffect;//�X�^�~�i�̗ʂŃG�t�F�N�g�𒲐�
	int m_healthEffect;//�̗̗͂ʂŃG�t�F�N�g�𒲐�
};

