#include "DxLib.h"
#include "game.h"
#include "Scene/SceneManager.h"

#define  DRAW false;

#if DRAW

#include <cmath>
#include <vector>

namespace
{
	//���_����J�����܂ł̋���
	constexpr int kCameraDistance = 800.0f;

	//�e�N�X�`�����
	const char* const kTextureFilename = "texture01.png";

	//�}�b�v�`�b�v�̕������i�j
	constexpr float kTextureDivNumX_F = 11.0f;
	constexpr float kTextureDivNumY_F = 8.0f;
	//�g�p����`�b�v�̔ԍ�(���ʒu�A�c�ʒu���w�肷��)
	constexpr int kUseTexture_X = 8;
	constexpr int kUseTexture_Y = 3;
	//�g�p����`�b�v�̃e�N�X�`�����W
	constexpr float kTextureMinU = 1.0f / kTextureDivNumX_F * kUseTexture_X;
	constexpr float kTextureMaxU = kTextureMinU + 1.0f / kTextureDivNumX_F;
	constexpr float kTextureMinV = 1.0f / kTextureDivNumY_F * kUseTexture_Y;
	constexpr float kTextureMaxV = kTextureMinV + 1.0f / kTextureDivNumY_F;
}

void DrawGrid()
{
	for (float z = -1000.0f; z <= 1000.0f; z += 100.0f)
	{
		VECTOR start = VGet(-1000, 0.0f, z);
		VECTOR end = VGet(1000, 0.0f, z);
		DrawLine3D(start, end, 0xffff00);
	}

	for (float x = -1000.0f; x <= 1000.0f; x += 100.0f)
	{
		VECTOR start = VGet(x, 0.0f, -1000.0f);
		VECTOR end = VGet(x, 0.0f, 1000.0f);
		DrawLine3D(start, end, 0xffff00);
	}
}

//�}�b�v���\�����闧���̂�1�ʂ�\��
//���_�𒆐S�Ƃ���z-���������������ʂ�`��

//�w��ʒu�𒆐S�Ƃ��Ă��w��T�C�Y�̗����̂�\������
void DrawMapPolygon(VECTOR  pos,float size,int textrure)
{
	//�|���S���̕`��
	constexpr int polyNum = 2;//�����`�P�ʕ`�悷��̂ɕK�v�ȃ|���S���̐�
	constexpr int vtxNum = polyNum * 3;//�|���S���̂P�ʕ��̕`��ɕK�v�Ȓ��_��
	constexpr int cubeVtxNum = polyNum * 6;//�����̂P�̕`�悷��̂ɕK�v�Ȓ��_��

	std::vector<VERTEX3D> drawVtx; //�`��ɂ��悤���钸�_�f�[�^

	VERTEX3D polyVtx[vtxNum]{};

	//����
	polyVtx[0].pos = VGet(-size/ 2.0f, size/ 2.0f, 0.0f);
	polyVtx[0].norm = VGet(0.0f, 0.0f, -1.0f);
	polyVtx[0].dif = GetColorU8(255, 255, 255, 255);
	polyVtx[0].spc = GetColorU8(255, 255, 255, 255);
	polyVtx[0].u = 0.0f;
	polyVtx[0].v = 0.0f;
	polyVtx[0].su = 0.0f;
	polyVtx[0].sv = 0.0f;

	//0�Ԗڂ̒��_�̏����ȍ~�̒��_�ɃR�s�[����
	for (int i = 0; i < vtxNum; i++)
	{
		polyVtx[i] = polyVtx[0];
	}

	//�E��
	polyVtx[1].pos = VGet(size, 200.0f, 0.0f);
	polyVtx[1].u = kTextureMaxU;
	polyVtx[1].v = kTextureMinU;
	//����
	polyVtx[2].pos = VGet(-200.0f, -200.0f, 0.0f);
	polyVtx[2].u = kTextureMinU;
	polyVtx[2].v = kTextureMaxU;

	//�E��
	polyVtx[3].pos = VGet(200.0f, -200.0f, 0.0f);
	polyVtx[3].u = kTextureMaxU;
	polyVtx[3].v = kTextureMinU;
	//����
	polyVtx[4].pos = VGet(-200.0f, -200.0f, 0.0f);
	polyVtx[4].u = kTextureMinU;
	polyVtx[4].v = kTextureMaxU;
	//�E��
	polyVtx[5].pos = VGet(200.0f, 200.0f, 0.0f);
	polyVtx[5].u = kTextureMaxU;
	polyVtx[5].v = kTextureMinU;

	//�`��̒��_�f�[�^�ɓo�^
	for (auto& vtx : polyVtx)
	{
		drawVtx.push_back(vtx);
	}


	DrawPolygon3D(polyVtx, 2, textrure, false);

	//��]�s��
	MATRIX mtx = MGetRotY(DX_PI_F / 2.0f);
	//���ʂ̒��_�f�[�^�����A�o�^
	for (int i = 0; i < 3; i++)
	{
		for (auto& vtx : polyVtx)
		{
			vtx.pos = VTransform(polyVtx[i].pos, mtx);
			vtx.norm = VTransform(polyVtx[i].norm, mtx);
			drawVtx.push_back(vtx);
		}
	}
	//��ʂ̒��_�f�[�^�����A�o�^
	mtx = MGetRotZ(DX_PI_F / 2.0f);
	for (int i = 0; i < 3; i++)
	{
		for (auto& vtx : polyVtx)
		{
			vtx.pos = VTransform(polyVtx[i].pos, mtx);
			vtx.norm = VTransform(polyVtx[i].norm, mtx);
			drawVtx.push_back(vtx);
		}
	}
	//���ʂ̒��_�f�[�^�����A�o�^
	mtx = MGetRotZ(DX_PI_F / 2.0f);
	for (int i = 0; i < 3; i++)
	{
		for (auto& vtx : polyVtx)
		{
			vtx.pos = VTransform(polyVtx[i].pos, mtx);
			vtx.norm = VTransform(polyVtx[i].norm, mtx);
			drawVtx.push_back(vtx);
		}
	}
	for (auto& vtx : drawVtx)
	{
		vtx.pos = VAdd(vtx.pos, pos);
	}

	DrawPolygon3D(drawVtx.data(), drawVtx.size()/3, textrure, false);
}

#endif

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
#if DRAW
	//Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(true);
	//Z�o�b�t�@�ւ̏������݂��s��
	SetWriteZBuffer3D(true);
	//���ʃ|���S����\�����Ȃ�
	SetUseBackCulling(false);

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

	//���S���猩���J�����̕���
	float cameraAngle = 0.0f;

	//VECTOR spherePos = VGet(0.0f, 0.0f, 0.0f);
	//����p
	float pers = 60.0f;

	int texture = LoadGraph(kTextureFilename);

#else
	// �ŏ��̃V�[���̏�����
	SceneManager scene;
	scene.Init();
#endif
	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

#if DRAW

		if (CheckHitKey(KEY_INPUT_UP))
		{
			
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
		
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			cameraAngle += 0.01;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			cameraAngle -= 0.01;
		}

		
		SetupCamera_Perspective(pers * DX_PI_F / 180.0f);
		VECTOR cameraPos = VGet(0.0f,300.0f,0.0f);
		cameraPos.x = sinf(cameraAngle) * kCameraDistance;
		cameraPos.z = cosf(cameraAngle) * kCameraDistance;
		SetCameraPositionAndTarget_UpVecY(cameraPos, VGet(0,0,0));//�J�����̈ʒu�@�J�����̒����_( ���Ă�����W )

		DrawGrid();
		DrawMapPolygon(VGet(0.0f, 0.0f, 0.0f),200.0f,texture);

#else
		scene.Update();
		scene.Draw();
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
#if DRAW
	DeleteGraph(texture);
#else
	scene.End();
#endif

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();
	

	return 0;				// �\�t�g�̏I�� 
}