#include <DxLib.h>
#include "SceneMain.h"
#include "Player.h"
#include "Enemy.h"
#include "BattleEffects.h"

SceneMain::SceneMain():
	m_pPlayer(),//�v���C���[�N���X
	m_pEnemy(),//�G�l�~�[�N���X
	m_pEffects()//�G�t�F�N�g�N���X
{
	//�������m��
	for (int i = 0; i < kHitNum; i++)
	{
		m_pPlayer[i] = new Player;
		m_pEnemy[i] = new Enemy;
		m_pEffects[i] = new BattleEffects;
	}
}

SceneMain::~SceneMain()
{
	//�������J��
	for (int i = 0; i < kHitNum; i++)
	{
		delete m_pPlayer[i];
		delete m_pEnemy[i];
		delete m_pEffects[i];
	}
}

void SceneMain::Init()
{
	//������
	for (int i = 0; i < kHitNum; i++)
	{
		m_pPlayer[i]->Init();
		m_pEnemy[i]->Init();
		m_pEffects[i]->Init();
	}
}
void SceneMain::End()
{
	//�������J���ȂǃQ�[���I������
	for (int i = 0; i < kHitNum; i++)
	{
		m_pPlayer[i]->End();
		m_pEnemy[i]->End();
		m_pEffects[i]->End();
	}
}

SceneBase* SceneMain::Update()
{

	m_pEnemy[0]->Update();
	m_pPlayer[0]->Update();

	//�v���C���[�ƃG�l�~�[�̓����蔻��
	if ((m_pPlayer[0]->SetRightPos() > m_pEnemy[0]->SetLeftPos()) &&
		(m_pPlayer[0]->SetLeftPos() < m_pEnemy[0]->SetRightPos()))
	{
		if ((m_pPlayer[0]->SetBottomPos() > m_pEnemy[0]->SetTopPos()) &&
			(m_pPlayer[0]->SetTopPos() < m_pEnemy[0]->SetBottomPos()))
		{
			//�U������ꏊ�������Ɏw��
			m_pEffects[0]->Hit(m_pPlayer[0]->SetLeftPos(), m_pPlayer[0]->SetTopPos());
		}
	}
	
	return this;
}

void SceneMain::Draw()
{
	m_pPlayer[0]->Draw();
	m_pEnemy[0]->Draw();
	m_pEffects[0]->Draw();
}