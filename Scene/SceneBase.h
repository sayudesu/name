#pragma once

// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	virtual void init() {}
	virtual void end() {}

	virtual SceneBase* update() { return this; }
	virtual void draw() {}

	// シーン終了
	virtual bool isEnd() { return false; }
};

