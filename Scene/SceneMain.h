#pragma once
#include "SceneBase.h"

namespace
{
	constexpr int kHitNum = 100;
}

class Player;//�v���C���[�N���X
class Enemy;//�G�l�~�[�N���X
class BattleEffects;//�G�t�F�N�g�N���X
class Map;//�}�b�v�N���X

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
	Player* m_pPlayer[kHitNum];//�v���C���[�N���X
	Enemy* m_pEnemy[kHitNum];//�G�l�~�[�N���X
	BattleEffects* m_pEffects[kHitNum];//�G�t�F�N�g�N���X
	Map* m_pMap;//�}�b�v�N���X
};
