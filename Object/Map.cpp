#include "game.h"
#include "DrawFunctions.h"
#include "Map.h"

Map::Map():
	m_hMap(-1)//�}�b�v�摜�p
{
}

Map::~Map()
{
}

void Map::Init()
{
	//�}�b�v�摜�������ǂݍ���
	m_hMap = my::MyLoadGraph("Data/Image/Map/Hills Layer 05.png");
	//TestMapChip.ppj
	m_hMap = my::MyLoadGraph("Data/Image/Map/TestMapChip.fmf");
}

void Map::End()
{
	//�������J��
	my::MyDeleteGraph(m_hMap);
}

void Map::Update()
{
}

void Map::Draw(int x)
{
	//�}�b�v��`��
	my::MyDrawExtendGraph(0 + x, 0, Game::kScreenWidth + 0 + x, Game::kScreenHeight, m_hMap, false);
}
