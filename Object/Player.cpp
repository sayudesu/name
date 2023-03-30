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

	constexpr float kAcc = 0.3f;//�v���C���[�̉����x
	constexpr float kPlayerMaxSpeed = 6.0f;//�v���C���[�̃X�s�[�h

	constexpr float kStaminaMax = 100.0f;//�X�^�~�i�ő吔
	constexpr float kStaminaCharge = 0.20f;//�X�^�~�i��
	constexpr float kStaminaFall = 0.30f;//�X�^�~�i����

}

Player::Player() :
	m_hPlayer(-1),//�v���C���[�摜
	m_attackLeft(0), m_attackTop(0), m_attackRight(0), m_attackBottom(0),//�U���������W
	m_attackLeftPos(0),//�U���������W����
	m_playerImageLetf(0), m_playerImageTop(0),//�v���C���[�̉摜�ʒu
	m_playerAnimationCut_X(0), m_playerAnimationCut_Y(0),////�v���C���[�摜��X�������ɂ���Ē���
	m_playerAnimationFrameCount(0),m_playerAnimationFrameCountNextNum(0),//�A�j���[�V�����Đ��J�E���g//�A�j���[�V�����Đ����邽�߂̐�
	m_mapMove_X(0),//�}�b�v�̈ʒu
	m_staminaNum(0.0f),//�X�^�~�i���Ǘ�
	m_healthNum(0.0f),//�̗͂��Ǘ�
	m_playerSpeed(0.0f),//�v���C���[�̈ړ����x
	m_isPlayerDirection(false),//�v���C���[�̌��� false �E : true	�� 
	m_isAttackAnimation(false),m_isAttackRunAnimation(false),//�U�������ꍇ�̃A�j���[�V����
	m_isGuardAnimation(false),//�U����h���A�j���[�V����
	m_isRun(false),//����邩�ǂ���
	m_playerPos(0.0f, 0.0f),//�v���C���[�̈ʒu
	m_playerVec(0.0f, 0.0f)//�v���C���[�̉^����
{

}

Player::~Player()
{
}

void Player::Init()
{
	m_playerPos = { static_cast<float>(Game::kScreenWidth / 2 + 20) ,static_cast<float>(Game::kScreenHeight / 2  + 200)};

	m_hPlayer = my::MyLoadGraph(kPlayer);//�摜�̃������m��

	m_staminaNum = 100.0f;//�X�^�~�i
	m_healthNum = 100.0f;//�̗�
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
#if false
	//�v���C���[�̈ړ�
	if (Pad::isPress(PAD_INPUT_UP))//��
	{
		m_playerVec.y -= kAcc;//�^���ʂ���

		//�^���ʂ��m�F���}�b�N�X�X�s�[�h���w��
		if (m_playerVec.y < -kPlayerMaxSpeed)	m_playerVec.y = -kPlayerMaxSpeed;
	}
	else if (Pad::isPress(PAD_INPUT_DOWN))//��
	{
		m_playerVec.y += kAcc;//�^���ʂ���
		//�^���ʂ��m�F���}�b�N�X�X�s�[�h���w��
		if (m_playerVec.y > kPlayerMaxSpeed)	m_playerVec.y = kPlayerMaxSpeed;
	}
	else
	{
		m_playerVec.y *= 0.9f;
	}
#endif
	if (Pad::isPress(PAD_INPUT_LEFT))//��
	{
		m_playerVec.x -= kAcc;//�^���ʂ���

		//�^���ʂ��m�F���}�b�N�X�X�s�[�h���w��
		if (m_playerVec.x < -kPlayerMaxSpeed)	m_playerVec.x = -kPlayerMaxSpeed;

		m_playerAnimationCut_X = 7;//walk
		m_playerAnimationCut_Y = 1;

		m_isPlayerDirection = true;//������ύX ������

		m_attackLeftPos = -110;//�U��X�ʒu

		if (m_playerPos.x < 500)
		{
			if (m_mapMove_X < 10000)
			{
				m_mapMove_X += kPlayerMaxSpeed * 1;
			}
		}
	}
	else if (Pad::isPress(PAD_INPUT_RIGHT))//�E
	{
		m_playerVec.x += kAcc;//�^���ʂ���

		//�^���ʂ��m�F���}�b�N�X�X�s�[�h���w��
		if (m_playerVec.x > kPlayerMaxSpeed)	m_playerVec.x = kPlayerMaxSpeed;

		m_playerAnimationCut_X = 7;//walk
		m_playerAnimationCut_Y = 1;//�U��X�ʒu

		m_isPlayerDirection = false;//������ύX �E����

		m_attackLeftPos = 60;//�U��X�ʒu

		if (m_playerPos.x > Game::kScreenWidth - 500)
		{
			if (m_mapMove_X > -10000)
			{
				m_mapMove_X -= kPlayerMaxSpeed * 1;
			}
		}
	}
	else
	{
		m_playerVec.x *= 0.9f;
	}

	m_isAttackRunAnimation = false;//����U���͈̔͂��w�肵�Ȃ�

	if (m_isRun)//�X�^�~�i������
	{
		if (Pad::isPress(PAD_INPUT_5))//����
		{
			m_playerAnimationCut_X = 4;
			m_playerAnimationCut_Y = 3;

			m_staminaNum -= kStaminaFall;//�X�^�~�i����

			m_isAttackRunAnimation = true;//����U���͈̔͂��w�肷��

			//�����Ă�������ɑ΂��č����ړ�
			if (m_isPlayerDirection)
			{
				m_playerVec.x -= 0.3f;
				m_mapMove_X += kPlayerMaxSpeed + 3.0f;
			}
			else
			{
				m_playerVec.x += 0.3f;
				m_mapMove_X -= kPlayerMaxSpeed + 3.0f;
			}
		}
	}

	if (Pad::isTrigger(PAD_INPUT_1))//�U��
	{
		m_isAttackAnimation = true;//�U�������ꍇ�̃A�j���[�V�������Đ�
		m_playerImageLetf = 0;

	}

	if (m_isAttackAnimation)//�U�������ꍇ�̃A�j���[�V����
	{
		m_playerAnimationCut_X = 9;
		m_playerAnimationCut_Y = 2;

		m_staminaNum -= kStaminaFall;//�X�^�~�i����
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

		m_staminaNum -= kStaminaFall;//�X�^�~�i����
	}

}

//�A�j���[�V��������
void Player::PlayerAnimation()
{
	m_playerAnimationFrameCount++;//�A�j���[�V�����Đ��J�E���g
	if (m_playerAnimationFrameCount > m_playerAnimationFrameCountNextNum)
	{
		m_playerAnimationFrameCount = KinitialValue;//�A�j���[�V�����Đ��J�E���g������
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

//�U���͈�
void Player::PlayerAttackScope()
{
	//�ʏ�U��
	if (m_isAttackAnimation)//�U���͈�
	{
		if (m_playerImageLetf > kPlayerImageSize * 6 &&//�U���A�j���[�V�����̍U������
			m_playerImageLetf < kPlayerImageSize * 8)
		{
			//�U���ʒu
			m_attackLeft = m_playerPos.x + m_attackLeftPos;//����,�E���������������ōU���ʒu��ύX
			m_attackTop = m_playerPos.y + 20;
			m_attackRight = m_attackLeft + 50;//�E��
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
	//�ːi�U��
	if (m_isAttackRunAnimation)
	{
		if (m_playerImageLetf > kPlayerImageSize * 0 &&//�U���A�j���[�V�����̍U������
			m_playerImageLetf < kPlayerImageSize * 4)
		{
			//�U���ʒu
			m_attackLeft = m_playerPos.x + m_attackLeftPos;//����,�E���������������ōU���ʒu��ύX
			m_attackTop = m_playerPos.y + 20;
			m_attackRight = m_attackLeft + 50;//�E��
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
	
	if(!m_isAttackAnimation && !m_isAttackRunAnimation)//�U�����ĂȂ��ꍇ�̏���
	{
		m_attackLeft = 0;
		m_attackTop = 0;
		m_attackRight = 0;
		m_attackBottom = 0;
	}
}

//�v���C���[�̍s���͈�
void Player::PlayerMoveScope()
{
	//���ړ��̏��
	if (m_playerPos.x < 500)
	{
		m_playerPos.x = 500;
	}
	//�E�ړ��̏��
	if (m_playerPos.x > Game::kScreenWidth - 500)
	{
		m_playerPos.x = Game::kScreenWidth - 500;
	}

	//��ړ��̏��
	if (m_playerPos.y < 0)
	{
		m_playerPos.y = 0;
	}
	//���ړ��̏��
	if (m_playerPos.y > Game::kScreenHeight)
	{
		m_playerPos.y = Game::kScreenHeight;
	}
}

//�X�^�~�i�Ǘ�
void Player::PlayerStaminaControl()
{
	//�X�^�~�i�̏��
	if (m_staminaNum < kStaminaMax)m_staminaNum += kStaminaCharge;
	//�v���C���[�̓�����x������
	if (m_staminaNum <= 30.0f)m_playerAnimationFrameCountNextNum = 7;
	//����𖳌�������
	if (m_staminaNum <= 25.0f)m_isRun = false;//����Ȃ�
	else m_isRun = true;//�����

	//�X�^�~�i�̉���
	if (m_staminaNum < 0.0f)
	{
		m_staminaNum = 0.0f;
		m_healthNum -= 0.1f;//�X�^�~�i���Ȃ��Ȃ�Ƒ̗͂�����
	}
}

//�X�V����
void Player::Update()
{
	//�A�j���[�V�����Đ����邽�߂̐�
	if(m_playerAnimationFrameCountNextNum != 4)m_playerAnimationFrameCountNextNum = 4;

	//Idle
	m_playerAnimationCut_X = 4;
	m_playerAnimationCut_Y = 0;

	PlayerMovement();//�L�����N�^�[�𑀍�
	PlayerMoveScope();//�v���C���[�̍s���͈�
	PlayerAttackScope();//�U���͈�

	//�v���C���[�������ł������Ă�����
	if (m_playerVec.x > 0.01f && m_playerVec.x < 1.0f ||
		m_playerVec.x < -0.01f && m_playerVec.x > -1.0f)
	{
		//walk
		//m_playerAnimationCut_X = 7;
		//m_playerAnimationCut_Y = 1;
		//m_playerAnimationFrameCountNextNum = 4;
	}

	PlayerStaminaControl();//�X�^�~�i�Ǘ�
	PlayerAnimation();//�A�j���[�V��������

	m_playerPos += m_playerVec;//�ړ���
}

//�`�揈��
void Player::Draw()
{
	//�v���C���[�A�j���[�V�����`��
	my::MyDrawRectRotaGraph(static_cast<int>(m_playerPos.x), static_cast<int>(m_playerPos.y),
		m_playerImageLetf, m_playerImageTop, kPlayerImageSize, kPlayerImageSize,
		1.5 * 3, DX_PI * 2, m_hPlayer, true, m_isPlayerDirection);
	
	//�U���͈͉���
	DrawBox(m_attackLeft, m_attackTop, m_attackRight, m_attackBottom,0xffff00,true);
}