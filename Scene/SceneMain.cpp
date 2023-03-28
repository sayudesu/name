#include <DxLib.h>
#include "SceneMain.h"
#include "game.h"

namespace
{
	constexpr int KinitialValue = 0;//�����l�p

	const char* const kPlayer = "Data/Image/Player/Knight.png";//�v���C���[�摜�ʒu
	//��48�@�c48
	constexpr int kPlayerImageSize = 48;

	constexpr float kPlayerSpeed = 100.0f;//�v���C���[�̃X�s�[�h

}

SceneMain::SceneMain():
	m_hPlayer(-1),//�v���C���[�摜
	m_playerImageLetf(0),m_playerImageTop(0),//�v���C���[�̉摜�ʒu
	m_playerAnimationCut_X(0), m_playerAnimationCut_Y(0),////�v���C���[�摜��X�������ɂ���Ē���
	m_playerDirection(false),//�v���C���[�̌��� false �E : true	�� 
	m_playerPos(0.0f, 0.0f)//�v���C���[�̈ʒu
{

}

SceneMain::~SceneMain()
{
}

void SceneMain::init()
{
	m_hPlayer = LoadGraph(kPlayer);//�摜�̃������m��
}
void SceneMain::end()
{
	DeleteGraph(m_hPlayer);//���������
}

SceneBase* SceneMain::update()
{
	//Idle
	m_playerAnimationCut_X = 4;
	m_playerAnimationCut_Y = 0;


	//�v���C���[�̈ړ�
	if (CheckHitKey(KEY_INPUT_W))//��
	{
		m_playerPos.y -= kPlayerSpeed;
	}
	if (CheckHitKey(KEY_INPUT_S))//��
	{
		m_playerPos.y += kPlayerSpeed;
	}
	if (CheckHitKey(KEY_INPUT_A))//��
	{
		m_playerPos.x -= kPlayerSpeed;

		m_playerAnimationCut_X = 7;//walk
		m_playerAnimationCut_Y = 1;

		m_playerDirection = true;//������ύX ������
	}
	if (CheckHitKey(KEY_INPUT_D))//�E
	{
		m_playerPos.x += kPlayerSpeed;

		m_playerAnimationCut_X = 7;//walk
		m_playerAnimationCut_Y = 1;

		m_playerDirection = false;//������ύX �E����
	}
	if (CheckHitKey(KEY_INPUT_C))//��
	{
		m_playerAnimationCut_X = 8;
		m_playerAnimationCut_Y = 4;
	}
	if (CheckHitKey(KEY_INPUT_LSHIFT))//��
	{
		m_playerAnimationCut_X = 4;
		m_playerAnimationCut_Y = 5;
	}


	//Idle
	
	m_playerImageTop = kPlayerImageSize * m_playerAnimationCut_Y;//Y�������炷

	if (m_playerImageLetf < kPlayerImageSize * m_playerAnimationCut_X)//
	{
		m_playerImageLetf += kPlayerImageSize;//X�����E�ɂ��炷
	}
	else
	{
		m_playerImageLetf = KinitialValue;//X���������l�ɖ߂�
	}

	return this;
}

void SceneMain::draw()
{
	//�v���C���[�A�j���[�V�����`��
	DrawRectRotaGraph(static_cast<int>(m_playerPos.x), static_cast<int>(m_playerPos.y),
		m_playerImageLetf, m_playerImageTop, kPlayerImageSize, kPlayerImageSize,
		1.5 * 3, DX_PI * 2, m_hPlayer, false, m_playerDirection);
}