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
	int m_hPlayer;//プレイヤー画像
	int m_playerImageLetf,m_playerImageTop;//プレイヤーの画像位置
	int m_playerAnimationCut_X, m_playerAnimationCut_Y;//プレイヤー画像のX軸動きによって調整
	bool m_playerDirection;//プレイヤーの向き false 右 : true	左
	Vec2 m_playerPos;//プレイヤーの位置
};
