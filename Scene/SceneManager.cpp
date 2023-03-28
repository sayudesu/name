#include <cassert>
#include "SceneManager.h"
#include "SceneMain.h"

SceneManager::SceneManager()
{
	m_pScene = nullptr;
}
// 初期化
void SceneManager::init()
{
	m_pScene = new SceneMain;
	m_pScene->init();
}
// 終了
void SceneManager::end()
{
	// 確認処理
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->end();
	delete m_pScene;
}
// 毎フレームの処理
void SceneManager::update()
{
	// 確認処理
	assert(m_pScene);
	if (!m_pScene)	return;
	// SceneBaseのupdate処理呼び出し
	SceneBase* pScene = m_pScene->update();
	if (pScene != m_pScene)
	{
		m_pScene->end();
		delete m_pScene;
		// 初期化
		m_pScene = pScene;
		m_pScene->init();
	}
}
// 描画
void SceneManager::draw()
{
	assert(m_pScene);
	if (!m_pScene)	return;
	m_pScene->draw();
}