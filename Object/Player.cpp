#include <DxLib.h>
#include "game.h"
#include "Pad.h"
#include "DrawFunctions.h"
#include "Player.h"

namespace
{
	constexpr int KinitialValue = 0;//�����l�p

	const char* const kPlayer = "Data/Image/Player/Knight.png";//�v���C���[�摜�ʒu
	//��48�@�c48
	constexpr int kPlayerImageSize = 48;

	constexpr float kPlayerSpeed = 6.0f;//�v���C���[�̃X�s�[�h

}

Player::Player() :
	m_hPlayer(-1),//�v���C���[�摜
	m_attackLeft(0), m_attackTop(0), m_attackRight(0), m_attackBottom(0),//�U���������W
	m_attackLeftPos(0),//�U���������W����
	m_playerImageLetf(0), m_playerImageTop(0),//�v���C���[�̉摜�ʒu
	m_playerAnimationCut_X(0), m_playerAnimationCut_Y(0),////�v���C���[�摜��X�������ɂ���Ē���
	m_playerAnimationFrameCount(0),//�A�j���[�V�����Đ��J�E���g
	m_MapMove_X(0),//�}�b�v�̈ʒu
	m_playerSpeed(0.0f),//�v���C���[�̈ړ����x
	m_isPlayerDirection(false),//�v���C���[�̌��� false �E : true	�� 
	m_isAttackAnimation(false),//�U�������ꍇ�̃A�j���[�V����
	m_isGuardAnimation(false),//�U����h���A�j���[�V����
	m_playerPos(0.0f, 0.0f),//�v���C���[�̈ʒu
	m_playerVec(0.0f, 0.0f)//�v���C���[�̉^����
{

}

Player::~Player()
{
}

void Player::Init()
{
	m_playerPos = { Game::kScreenWidth / 2 ,Game::kScreenHeight / 2 };

	m_hPlayer = my::MyLoadGraph(kPlayer);//�摜�̃������m��
}
void Player::End()
{
	//���������
	my::MyDeleteGraph(m_hPlayer);
}

//�L�����N�^�[�𑀍�
void Player::PlayerMovement()
{
	Pad::update();

	//Idle
	m_playerAnimationCut_X = 4;
	m_playerAnimationCut_Y = 0;

	//�v���C���[�̈ړ�
	if (Pad::isPress(PAD_INPUT_UP))//��
	{
		m_playerVec.y -= m_playerSpeed;
	}
	if (Pad::isPress(PAD_INPUT_DOWN))//��
	{
		m_playerVec.y += m_playerSpeed;
	}
	if (Pad::isPress(PAD_INPUT_LEFT))//��
	{
		m_playerVec.x -= m_playerSpeed;

		m_playerAnimationCut_X = 7;//walk
		m_playerAnimationCut_Y = 1;

		m_isPlayerDirection = true;//������ύX ������
		m_attackLeftPos = -110;
		if (m_MapMove_X < 10000)
		{
			if (m_playerPos.x < 500)
			{
				m_MapMove_X += kPlayerSpeed * 3;
			}
		}

	}
	if (Pad::isPress(PAD_INPUT_RIGHT))//�E
	{
		m_playerVec.x += m_playerSpeed;

		m_playerAnimationCut_X = 7;//walk
		m_playerAnimationCut_Y = 1;

		m_isPlayerDirection = false;//������ύX �E����
		m_attackLeftPos = 60;
		if (m_MapMove_X > -10000)
		{
			if (m_playerPos.x > Game::kScreenWidth - 500)
			{
				m_MapMove_X -= kPlayerSpeed * 3;
			}
		}
	}
	if (Pad::isPress(PAD_INPUT_5))//��
	{
		m_playerAnimationCut_X = 4;
		m_playerAnimationCut_Y = 3;
	}
	printfDx("%d\n", m_MapMove_X);

	if (Pad::isTrigger(PAD_INPUT_1))//�U��
	{
		m_isAttackAnimation = true;//�U�������ꍇ�̃A�j���[�V�������Đ�
		m_playerImageLetf = 0;

	}

	if (m_isAttackAnimation)//�U�������ꍇ�̃A�j���[�V����
	{
		m_playerAnimationCut_X = 9;
		m_playerAnimationCut_Y = 2;
	}
	if (Pad::isTrigger(PAD_INPUT_3))//�K�[�h
	{
		m_isGuardAnimation = true;//�U�������ꍇ�̃A�j���[�V�����Đ�
		m_playerImageLetf = 0;
		m_playerSpeed = 0;
	}
	if (m_isGuardAnimation)//�U����h���A�j���[�V����
	{
		m_playerAnimationCut_X = 8;
		m_playerAnimationCut_Y = 4;
	}

}

void Player::PlayerMoveScope()
{
	if (m_playerPos.x < 500)
	{
		m_playerPos.x = 500;
		m_playerVec.x = 500;
	}
	if (m_playerPos.x > Game::kScreenWidth - 500)
	{
		m_playerPos.x = Game::kScreenWidth - 500;
		m_playerVec.x = Game::kScreenWidth - 500;
	}
}

void Player::Update()
{
	m_playerSpeed = kPlayerSpeed;//�ړ����x
	m_playerPos = m_playerVec;//�ړ����x

	PlayerMovement();//�L�����N�^�[�𑀍�
	PlayerMoveScope();//�v���C���[�̍s���͈�

	if (m_isAttackAnimation)//�U���͈�
	{
		if (m_playerImageLetf > kPlayerImageSize * 6 &&//�U���A�j���[�V�����̍U������
			m_playerImageLetf < kPlayerImageSize * 8)
		{
			m_attackLeft = m_playerPos.x + m_attackLeftPos;
			m_attackTop = m_playerPos.y + 20;
			m_attackRight = m_attackLeft + 50;
			m_attackBottom = m_attackTop + 50;
		}
		else
		{
			m_attackLeft = 0;
			m_attackTop = 0;
			m_attackRight = 0;
			m_attackBottom = 0;
		}
	}

	m_playerAnimationFrameCount++;//�A�j���[�V�����Đ��J�E���g
	if (m_playerAnimationFrameCount >= 4)
	{
		m_playerAnimationFrameCount = KinitialValue;
		m_playerImageTop = kPlayerImageSize * m_playerAnimationCut_Y;//Y�������炷

		if (m_playerImageLetf < kPlayerImageSize * m_playerAnimationCut_X)//
		{
			m_playerImageLetf += kPlayerImageSize;//X�����E�ɂ��炷
		}
		else
		{
			m_isAttackAnimation = false;//�U�������ꍇ�̃A�j���[�V�������~
			m_isGuardAnimation = false;//�U����h���A�j���[�V������~

			m_playerImageLetf = KinitialValue;//X���������l�ɖ߂�
		}
	}
	
}

void Player::Draw()
{
	//�v���C���[�A�j���[�V�����`��
	my::MyDrawRectRotaGraph(static_cast<int>(m_playerPos.x), static_cast<int>(m_playerPos.y),
		m_playerImageLetf, m_playerImageTop, kPlayerImageSize, kPlayerImageSize,
		1.5 * 3, DX_PI * 2, m_hPlayer, true, m_isPlayerDirection);
	
	//�U���͈͉���
	DrawBox(m_attackLeft, m_attackTop, m_attackRight, m_attackBottom,0xffff00,true);
}