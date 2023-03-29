#include <DxLib.h>
#include "SceneMain.h"
#include "Player.h"
#include "Enemy.h"
#include "BattleEffects.h"
#include "Map.h"

SceneMain::SceneMain():
	m_pPlayer(),//プレイヤークラス
	m_pEnemy(),//エネミークラス
	m_pEffects(),//エフェクトクラス
	m_pMap(nullptr)//マップクラス
{

	//メモリ確保
	for (int i = 0; i < kHitNum; i++)
	{
		m_pPlayer[i] = new Player;
		m_pEnemy[i] = new Enemy;
		m_pEffects[i] = new BattleEffects;
	}

	m_pMap = new Map;
}

SceneMain::~SceneMain()
{
	//メモリ開放
	for (int i = 0; i < kHitNum; i++)
	{
		delete m_pPlayer[i];
		delete m_pEnemy[i];
		delete m_pEffects[i];
	}
	delete m_pMap;
}

void SceneMain::Init()
{
	//初期化
	for (int i = 0; i < kHitNum; i++)
	{
		m_pPlayer[i]->Init();
		m_pEnemy[i]->Init();
		m_pEffects[i]->Init();
	}
	m_pMap->Init();
}
void SceneMain::End()
{
	//メモリ開放などゲーム終了処理
	for (int i = 0; i < kHitNum; i++)
	{
		m_pPlayer[i]->End();
		m_pEnemy[i]->End();
		m_pEffects[i]->End();
	}
	m_pMap->End();
}

SceneBase* SceneMain::Update()
{

	m_pEnemy[0]->Update();
	m_pPlayer[0]->Update();
	m_pMap->Update();
	//プレイヤーとエネミーの当たり判定
	if ((m_pPlayer[0]->SetRightPos() > m_pEnemy[0]->SetLeftPos()) &&
		(m_pPlayer[0]->SetLeftPos() < m_pEnemy[0]->SetRightPos()))
	{
		if ((m_pPlayer[0]->SetBottomPos() > m_pEnemy[0]->SetTopPos()) &&
			(m_pPlayer[0]->SetTopPos() < m_pEnemy[0]->SetBottomPos()))
		{
			//攻撃判定場所を引数に指定
			m_pEffects[0]->Hit(m_pPlayer[0]->SetLeftPos(), m_pPlayer[0]->SetTopPos());
		}
	}
	
	return this;
}

void SceneMain::Draw()
{
	m_pMap->Draw(m_pPlayer[0]->SetMapPosX());//マップ描画
	m_pEnemy[0]->Draw();//エネミー描画
	m_pPlayer[0]->Draw();//プレイヤー描画
	m_pEffects[0]->Draw();//攻撃エフェクト描画
}