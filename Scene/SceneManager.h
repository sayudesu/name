#pragma once

#include "SceneBase.h"

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager() {}
	// 初期化
	void Init();
	// 終了
	void End();
	// 毎フレームの処理
	void Update();
	// 描画
	void Draw();

private:
	// シーンベースポインタ
	SceneBase* m_pScene;
};

