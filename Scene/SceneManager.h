#pragma once

#include "SceneBase.h"

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager() {}
	// ������
	void init();
	// �I��
	void end();
	// ���t���[���̏���
	void update();
	// �`��
	void draw();

private:
	// �V�[���x�[�X�|�C���^
	SceneBase* m_pScene;
};

