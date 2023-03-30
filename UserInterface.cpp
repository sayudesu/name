#include <DxLib.h>
#include "UserInterface.h"

UserInterface::UserInterface():
	m_staminaNum(0),//プレイヤーのスタミナ
	m_healthNum(0)//プレイヤーの体力
{
}

UserInterface::~UserInterface()
{
}

void UserInterface::Init()
{
}

void UserInterface::End()
{
}

void UserInterface::Update()
{
	
}

void UserInterface::Draw()
{
	//スタミナを描画
	DrawBox(100 - 1, 80 - 1, 100 + 400 + 1,                  80 + 1 + 20, 0x0000ff, true);//外枠
	DrawBox(100,     80,     100 + 400 * m_healthNum / 100, 80 + 20, 0xff0000, true);//メーター

	//体力を描画
	DrawBox(100 - 1, 130 - 1, 100 + 400 + 1,                  130 + 1 + 20, 0x0000ff, true);//外枠
	DrawBox(100,     130,     100 + 400 * m_staminaNum / 100, 130 + 20, 0x0ffff0, true);//メーター
	//長さ * HP / HPMAX
}

