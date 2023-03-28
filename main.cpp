#include "DxLib.h"
#include "game.h"
#include "Scene/SceneManager.h"

#define  Draw false;

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	//�}�E�X�J�[�\���\��
	SetMouseDispFlag(Game::kMouseMode);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);
#if Draw
	//Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(true);
	//Z�o�b�t�@�ւ̏������݂��s��
	SetWriteZBuffer3D(true);
	//�J�����͈�
	SetCameraNearFar(5.0f, 2000.0f);
	//FOV
	
	//�J�����ʒu���ǂ������Ă��邩
	SetCameraPositionAndTarget_UpVecY(VGet(0, 300, -800), VGet(0, 0, 0));

	float posX = 0;
	float posY = 300;
	float posZ = -800;

	float eyeX = 0;
	float eyeY = 0;
	float eyeZ = 0;


	VECTOR spherePos = VGet(0.0f, 0.0f, 0.0f);
	//����p
	float pers = 60.0f;
#endif
	// �ŏ��̃V�[���̏�����
	SceneManager scene;
	scene.init();

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		scene.update();
		scene.draw();
#if Draw
		for (float z = -1000.0f; z <= 1000.0f; z += 100.0f)
		{
			VECTOR start = VGet(-1000, 0.0f, z);
			VECTOR end   = VGet( 1000, 0.0f, z);
			DrawLine3D(start,end,0xffff00);
		}

		for (float x = -1000.0f; x <= 1000.0f; x += 100.0f)
		{
			VECTOR start = VGet(x, 0.0f, -1000.0f);
			VECTOR end = VGet(x, 0.0f, 1000.0f);
			DrawLine3D(start, end, 0xffff00);
		}


		//SetupCamera_Perspective(pers * DX_PI_F / 180.0f);
		//SetCameraPositionAndTarget_UpVecY(VGet(posX, posY, posZ), VGet(eyeX, eyeY, eyeZ));//�J�����̈ʒu�@�J�����̒����_( ���Ă�����W )

		//if (CheckHitKey(KEY_INPUT_UP))
		//{
		//	spherePos.y += 10.0f;
		//}
		//if (CheckHitKey(KEY_INPUT_DOWN))
		//{
		//	spherePos.y -= 10.0f;
		//}
		//if (CheckHitKey(KEY_INPUT_LEFT))
		//{
		//	spherePos.x -= 10.0f;
		//}
		//if (CheckHitKey(KEY_INPUT_RIGHT))
		//{
		//	spherePos.x += 10.0f;
		//}
		

		//�|���S���̕`��

		VERTEX3D polyVtx[3];
		polyVtx[0].pos = VGet(-200.0f, 0.0f, 200.0f);
		polyVtx[0].norm = VGet(0.0f, 1.0f, 0.0f);
		polyVtx[0].dif = GetColorU8(255, 255, 255, 255);
		polyVtx[0].spc = GetColorU8(255, 255, 255, 255);
		polyVtx[0].u = 0.0f;
		polyVtx[0].v = 0.0f;
		polyVtx[0].su = 0.0f;
		polyVtx[0].sv = 0.0f;

		polyVtx[1] = polyVtx[0];
		polyVtx[2] = polyVtx[0];

		polyVtx[1].pos = VGet(200.0f, 0.0f, 200.0f);
		polyVtx[2].pos = VGet(-200.0f, 0.0f, -200.0f);


		DrawPolygon3D(polyVtx, 1, DX_NONE_GRAPH, false);

		DrawSphere3D(spherePos, 16.0f * 2.0f, 32,0xffffff, 0xffffff,true);


		SetupCamera_Perspective(pers * DX_PI_F / 180.0f);
		SetCameraPositionAndTarget_UpVecY(VGet(0, 300, -800), spherePos);//�J�����̈ʒu�@�J�����̒����_( ���Ă�����W )
#endif
		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	scene.end();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}