#pragma once

#include "SceneBase.h"

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager() {}
	// 初期化
	void init();
	// 終了
	void end();
	// 毎フレームの処理
	void update();
	// 描画
	void draw();

private:
	// シーンベースポインタ
	SceneBase* m_pScene;
};

