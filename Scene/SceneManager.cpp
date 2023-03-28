#include <cassert>
#include "SceneManager.h"
#include "SceneMain.h"

SceneManager::SceneManager()
{
	m_pScene = nullptr;
}
// 初期化
void SceneManager::Init()
{
	m_pScene = new SceneMain;
	m_pScene->Init();
}
// 終了
void SceneManager::End()
{
	// 確認処理
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->End();
	delete m_pScene;
}
// 毎フレームの処理
void SceneManager::Update()
{
	// 確認処理
	assert(m_pScene);
	if (!m_pScene)	return;
	// SceneBaseのupdate処理呼び出し
	SceneBase* pScene = m_pScene->Update();
	if (pScene != m_pScene)
	{
		m_pScene->End();
		delete m_pScene;
		// 初期化
		m_pScene = pScene;
		m_pScene->Init();
	}
}
// 描画
void SceneManager::Draw()
{
	assert(m_pScene);
	if (!m_pScene)	return;
	m_pScene->Draw();
}