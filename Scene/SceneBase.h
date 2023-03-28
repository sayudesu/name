#pragma once

// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}

	virtual void Init() {}
	virtual void End() {}

	virtual SceneBase* Update() { return this; }
	virtual void Draw() {}
};

