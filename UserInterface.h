#pragma once
class UserInterface
{
public:
	UserInterface();
	~UserInterface();

	void Init();
	void End();
	void Update();
	void Draw();

	void GetHealthNum(float health) { m_healthNum = health; }//�̗͂̏�Ԃ𓾂�
	void GetStaminaNum(float stamina) { m_staminaNum = stamina; }//�X�^�~�i�̏�Ԃ𓾂�
private:
	float m_staminaNum;//�v���C���[�N���X���瓾�X�^�~�i
	float m_healthNum;//�v���C���[�N���X���瓾���̗�
};

