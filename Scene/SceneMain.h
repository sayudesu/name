#pragma once
#include "SceneBase.h"

namespace
{
	constexpr int kHitNum = 100;
}

class Player;//プレイヤークラス
class Enemy;//エネミークラス
class BattleEffects;//エフェクトクラス
class Map;//マップクラス

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();

private:
	Player* m_pPlayer[kHitNum];//プレイヤークラス
	Enemy* m_pEnemy[kHitNum];//エネミークラス
	BattleEffects* m_pEffects[kHitNum];//エフェクトクラス
	Map* m_pMap;//マップクラス
};
