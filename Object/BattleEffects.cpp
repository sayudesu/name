#include <Dxlib.h>
#include "BattleEffects.h"
#include "game.h"

BattleEffects::BattleEffects():
	m_hitEffect_X(0), m_hitEffect_Y(0),//�U���G�t�F�N�g�ʒu
	m_staminaNum(0),//�X�^�~�i��
	m_healthNum(0),//�̗͗�
	m_staminatEffect(0),//�X�^�~�i�̗ʂŃG�t�F�N�g�𒲐�
	m_healthEffect(0)//�̗̗͂ʂŃG�t�F�N�g�𒲐�
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

//�v���C���[�̃X�^�~�i���Ǘ�����
void BattleEffects::GetStaminaNum(int stamina)
{
	m_staminaNum = stamina;//�v���C���[�̃X�^�~�i���Ǘ�

	//�G�t�F�N�g����
	if (m_staminaNum > 30)m_staminatEffect--;//�X�^�~�i�������Ԃł̓G�t�F�N�g�����Ȃ�
	if (m_staminaNum < 30)m_staminatEffect++;//�X�^�~�i�̗ʂ���萔������ƃG�t�F�N�g������

	//�G�t�F�N�g�̏��
	if (m_staminatEffect < 0)m_staminatEffect = 0;
	if (m_staminatEffect > 128)m_staminatEffect = 128;
}

//�v���C���[�̗̑͂��Ǘ�����
void BattleEffects::GetHealthNum(int health)
{
	m_healthNum = health;//�̗̓X�^�~�i���Ǘ�
	
	//�G�t�F�N�g����
	if (m_healthNum > 30)m_healthEffect--;//�̗͂������Ԃł̓G�t�F�N�g�����Ȃ�
	if (m_healthNum < 30)m_healthEffect++;//�̗̗͂ʂ���萔������ƃG�t�F�N�g������

	//�G�t�F�N�g�̏��
	if (m_healthEffect < 0)m_healthEffect = 0;
	if (m_healthEffect > 80)m_healthEffect = 80;

}

void BattleEffects::Update()
{
}

void BattleEffects::Draw()
{
	//�v���C���[�̃X�^�~�i�̃G�t�F�N�g
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_staminatEffect);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xff00ff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//�v���C���[�̗̑͂̃G�t�F�N�g
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_healthEffect);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xff0000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�U�������G�t�F�N�g�i���j
	DrawString(m_hitEffect_X, m_hitEffect_Y,"HIT", 0xffffff);
}
