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

	void GetHealthNum(float health) { m_healthNum = health; }//体力の状態を得る
	void GetStaminaNum(float stamina) { m_staminaNum = stamina; }//スタミナの状態を得る
private:
	float m_staminaNum;//プレイヤークラスから得スタミナ
	float m_healthNum;//プレイヤークラスから得た体力
};

