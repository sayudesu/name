#pragma once
#include <tchar.h>

// �����p���C�u�����p���O���
namespace my {
	/// <summary>
	/// �摜�����[�h����
	/// </summary>
	/// <param name="path">�p�X������</param>
	/// <returns>�摜�̃n���h��</returns>
	int MyLoadGraph(const TCHAR* path);
	//�摜�f�[�^�̃��������
	int MyDeleteGraph( int handle);
	//���W�ł̈ʒu�A�摜�̍���E���A�g�嗦�A�p�x�A�O���t�B�b�N�n���h���A�摜�̓��߁A�摜���]
	int MyDrawRectRotaGraph(int x, int y,
							int left, int top,
							int width, int height,
							float scale, float angle,
							int handle, bool transFlg, bool transFlg2);

	//����E���A�O���t�B�b�N�n���h���A�摜�̓���
	int MyDrawExtendGraph(int left, int top, 
						  int right, int bottom,
						  int handle, bool flag);
}
