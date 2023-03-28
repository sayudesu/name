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
	virtual void PlayerMoveScope();//�v���C���[�̍s���͈�

	virtual void Update();
	virtual void Draw();
public:
	int SetLeftPos() { return m_attackLeft; }
	int SetTopPos() { return m_attackTop; }
	int SetRightPos() { return m_attackRight; }
	int SetBottomPos() { return m_attackBottom; }
private:
	int m_hPlayer;//�v���C���[�摜
	int m_attackLeft, m_attackTop, m_attackRight, m_attackBottom;//�U���������W
	int m_attackLeftPos;//�U���������W����
	int m_playerImageLetf, m_playerImageTop;//�v���C���[�̉摜�ʒu
	int m_playerAnimationCut_X, m_playerAnimationCut_Y;//�v���C���[�摜��X�������ɂ���Ē���
	int m_playerAnimationFrameCount;//�A�j���[�V�����Đ��J�E���g
	float m_playerSpeed;//�v���C���[�̈ړ����x
	bool m_isPlayerDirection;//�v���C���[�̌��� false �E : true	��
	bool m_isAttackAnimation;//�U�������ꍇ�̃A�j���[�V����
	bool m_isGuardAnimation;//�U����h���A�j���[�V����
	Vec2 m_playerPos;//�v���C���[�̈ʒu
	Vec2 m_playerVec;//�v���C���[�̉^����

	//�ʃN���X�Ɉړ��p
	int m_hMap;
	int m_MapMove_X;
};

