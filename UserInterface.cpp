#include <DxLib.h>
#include "UserInterface.h"

UserInterface::UserInterface():
	m_staminaNum(0),//�v���C���[�̃X�^�~�i
	m_healthNum(0)//�v���C���[�̗̑�
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
	//�X�^�~�i��`��
	DrawBox(100 - 1, 80 - 1, 100 + 400 + 1,                  80 + 1 + 20, 0x0000ff, true);//�O�g
	DrawBox(100,     80,     100 + 400 * m_healthNum / 100, 80 + 20, 0xff0000, true);//���[�^�[

	//�̗͂�`��
	DrawBox(100 - 1, 130 - 1, 100 + 400 + 1,                  130 + 1 + 20, 0x0000ff, true);//�O�g
	DrawBox(100,     130,     100 + 400 * m_staminaNum / 100, 130 + 20, 0x0ffff0, true);//���[�^�[
	//���� * HP / HPMAX
}

