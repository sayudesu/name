#include <Dxlib.h>
#include "game.h"
#include "Map.h"

Map::Map():
	m_hMap(-1)
{
}

Map::~Map()
{
}

void Map::Init()
{
	m_hMap = LoadGraph("Data/Image/Map/Hills Layer 05.png");
}

void Map::End()
{
	DeleteGraph(m_hMap);
}

void Map::Update()
{
}

void Map::Draw(int x)
{
	DrawExtendGraph(-10000 + x, -100, Game::kScreenWidth + 10000 + x, Game::kScreenHeight, m_hMap, false);
}
