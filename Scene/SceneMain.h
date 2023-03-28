#pragma once
#include "SceneBase.h"
#include "Vec2.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();


	virtual void init();
	virtual void end();

	virtual SceneBase* update() override;
	virtual void draw();
private:
	int m_hPlayer;//�v���C���[�摜
	int m_playerImageLetf,m_playerImageTop;//�v���C���[�̉摜�ʒu
	int m_playerAnimationCut_X, m_playerAnimationCut_Y;//�v���C���[�摜��X�������ɂ���Ē���
	bool m_playerDirection;//�v���C���[�̌��� false �E : true	��
	Vec2 m_playerPos;//�v���C���[�̈ʒu
};
