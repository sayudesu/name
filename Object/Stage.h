#pragma once
#include <vector>

enum class LayerType {
	Background,// 0:�w�i
	Enemies,// 1:�G
	Event,// 2:�C�x���g
};

// �}�b�v�̍L��*���C���[���Ȃ̂ŁA2�̃x�N�^�[�����q�ɂ��Ă�
using MapData_t = std::vector<std::vector<unsigned char>>;
// �X�e�[�W�����Ǘ�����N���X
class Stage
{
	
	MapData_t mapData_;
	int mapWidth_;
	int mapHeight_;
public:
	void Load(const TCHAR* filePath);
	const MapData_t& GetMapData()const;
	const int GetChipId(int layerId, int chipX, int chipY)const;

	void GetMapSize(int& width, int& height);
private:
	/// <summary>
	/// �f�[�^�̓��e��XY�]�u����
	/// </summary>
	/// <param name="layerId">���C���[ID</param>
	void TransposeMapData(int layerId);
};

