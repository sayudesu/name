#include "game.h"
#include "DrawFunctions.h"
#include "Map.h"

Map::Map():
	m_hMap(-1)//マップ画像用
{
}

Map::~Map()
{
}

void Map::Init()
{
	//マップ画像メモリ読み込み
	m_hMap = my::MyLoadGraph("Data/Image/Map/Hills Layer 05.png");
	//TestMapChip.ppj
	m_hMap = my::MyLoadGraph("Data/Image/Map/TestMapChip.fmf");
}

void Map::End()
{
	//メモリ開放
	my::MyDeleteGraph(m_hMap);
}

void Map::Update()
{
}

void Map::Draw(int x)
{
	//マップを描画
	my::MyDrawExtendGraph(0 + x, 0, Game::kScreenWidth + 0 + x, Game::kScreenHeight, m_hMap, false);
}
