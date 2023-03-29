#pragma once
#include "Vec2.h"

class Player
{
public:
	Player();
	virtual ~Player();

	virtual void Init();
	virtual void End();

	virtual void PlayerMovement();//�L�����N�^�[�𑀍�
	virtual void PlayerAnimation();//�A�j���[�V��������
	virtual void PlayerAttackScope();//�U���͈�
	virtual void PlayerMoveScope();//�v���C���[�̍s���͈�
//	virtual void PlayerStaminaControl();//�̗͊Ǘ�
	virtual void PlayerStaminaControl();//�X�^�~�i�Ǘ�

	virtual void Update();//�X�V����
	virtual void Draw();//�`�揈��
public:
	//�v���C���[�̍U���͈�
	int SetLeftPos() { return m_attackLeft; }//����
	int SetTopPos() { return m_attackTop; }
	int SetRightPos() { return m_attackRight; }//�E��
	int SetBottomPos() { return m_attackBottom; }
	int SetMapPosX() { return m_mapMove_X; }
	
	//�v���C���[�̃X�^�~�i
	float SetStaminaNum() { return m_staminaNum; }
	//�v���C���[�̗̑�
	float SethealthNum() { return m_healthNum; }

private:
	int m_hPlayer;//�v���C���[�摜
	int m_attackLeft, m_attackTop, m_attackRight, m_attackBottom;//�U���������W
	int m_attackLeftPos;//�U���������W����
	int m_playerImageLetf, m_playerImageTop;//�v���C���[�̉摜�ʒu
	int m_playerAnimationCut_X, m_playerAnimationCut_Y;//�v���C���[�摜��X�������ɂ���Ē���
	int m_playerAnimationFrameCount;//�A�j���[�V�����Đ��J�E���g
	int m_playerAnimationFrameCountNextNum;//�A�j���[�V�����Đ����邽�߂̐�
	int m_mapMove_X;//�}�b�v�̈ʒu
	float m_staminaNum;//�X�^�~�i���Ǘ�
	float m_healthNum;//�̗͂��Ǘ�
	float m_playerSpeed;//�v���C���[�̈ړ����x
	bool m_isPlayerDirection;//�v���C���[�̌��� false �E : true	��
	bool m_isAttackAnimation;//�U�������ꍇ�̃A�j���[�V����
	bool m_isGuardAnimation;//�U����h���A�j���[�V����
	bool m_isRun;//����邩�ǂ���
	Vec2 m_playerPos;//�v���C���[�̈ʒu
	Vec2 m_playerVec;//�v���C���[�̉^����
};

