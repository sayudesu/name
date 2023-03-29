#include <DxLib.h>
#include <cassert>
#include "DrawFunctions.h"

namespace my
{
	/// <summary>
	/// �O���t�B�N�X�����[�h����
	/// </summary>
	/// <param name="path">�摜�t�@�C���̃p�X</param>
	/// <returns>�摜�̃n���h��</returns>
	int MyLoadGraph(const TCHAR* path) {
		int handle = LoadGraph(path);
		//�n���h���͐������������Ă��邩�m�F
		assert(handle != -1);//�����l��-1�Ɏw�肷��
		return handle;
	}
	//�摜�f�[�^�̃��������
	int MyDeleteGraph(int handle)
	{
		//Dxlib�̊֐��̈����ɓn��
		return DeleteGraph(handle);
	}
	//���W�ł̈ʒu�A�摜�̍���E���A�g�嗦�A�p�x�A�O���t�B�b�N�n���h���A�摜�̓��߁A�摜���]
	int MyDrawRectRotaGraph(int x, int y, int left, int top, int width, int height, float scale, float angle, int handle, bool transFlg, bool transFlg2)
	{
		//Dxlib�̊֐��̈����ɓn��
		return DrawRectRotaGraph(x,y,
								 left,top,
								 width,height,
								 scale,angle,
								 handle,transFlg, transFlg2);
	}
	//����E���A�O���t�B�b�N�n���h���A�摜�̓���
	int MyDrawExtendGraph(int left, int top, int right, int bottom, int handle, bool flag)
	{
		//Dxlib�̊֐��̈����ɓn��
		return DrawExtendGraph(left, top,
							   right, bottom,
							   handle, flag);
	}
}// end of namespace my