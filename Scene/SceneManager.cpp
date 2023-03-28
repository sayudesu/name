#include <cassert>
#include "SceneManager.h"
#include "SceneMain.h"

SceneManager::SceneManager()
{
	m_pScene = nullptr;
}
// ������
void SceneManager::Init()
{
	m_pScene = new SceneMain;
	m_pScene->Init();
}
// �I��
void SceneManager::End()
{
	// �m�F����
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->End();
	delete m_pScene;
}
// ���t���[���̏���
void SceneManager::Update()
{
	// �m�F����
	assert(m_pScene);
	if (!m_pScene)	return;
	// SceneBase��update�����Ăяo��
	SceneBase* pScene = m_pScene->Update();
	if (pScene != m_pScene)
	{
		m_pScene->End();
		delete m_pScene;
		// ������
		m_pScene = pScene;
		m_pScene->Init();
	}
}
// �`��
void SceneManager::Draw()
{
	assert(m_pScene);
	if (!m_pScene)	return;
	m_pScene->Draw();
}