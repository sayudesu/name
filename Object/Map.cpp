#include "game.h"
#include "DrawFunctions.h"
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
	m_hMap = my::MyLoadGraph("Data/Image/Map/Hills Layer 05.png");
}

void Map::End()
{
	my::MyDeleteGraph(m_hMap);
}

void Map::Update()
{
}

void Map::Draw(int x)
{
	//ƒ}ƒbƒv‚ð•`‰æ
	my::MyDrawExtendGraph(-10000 + x, 0, Game::kScreenWidth + 10000 + x, Game::kScreenHeight, m_hMap, false);
}
