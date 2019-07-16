//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ScenePlay.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   ���t
//!
//! @author ����Җ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "ScenePlay.h"
#include "Button.h"
#include "Mouse.h"


// �萔�̒�` ==============================================================
#define MAP_HEIGHT	(480)
#define MAP_WIDTH	(480)
#define GRID_HEIGHT (15)
#define GRID_WIDTH	(15)
#define GRID_SIZE_X	(32)
#define GRID_SIZE_Y	(32)
#define OBJECT_RADIAN (14)


// �O���[�o���ϐ��̒�` ====================================================
GameObject g_player;
GameObject g_enemyObject;
GameObject g_allyObject;
GameObject g_directionObject[4];
GameObject g_returnObjectUi;
GameObject g_background;
GameObject g_clearBackground[2];
GameObject g_nextStageButton;
GameObject g_returnSelectButton;
GameObject g_resetUiObject;
GameObject g_eatEffectB;
GameObject g_eatEffectW;

UI g_arrowUi;

int g_gridData[GRID_HEIGHT][GRID_WIDTH];
int g_mapData[GRID_HEIGHT][GRID_WIDTH];

int g_gridDataOrigin[GRID_HEIGHT][GRID_WIDTH];
int g_mapDataOrigin[GRID_HEIGHT][GRID_WIDTH];

int g_clearGrid[GRID_HEIGHT][GRID_WIDTH];

int g_endFlag;
int g_transitionCount;

// �֐��̐錾 ==============================================================
void InitializeGrid(void);
void InitializeMapData(void);
void InitializeObjectPotision(void);
void InitializePlayer(void);
void InitializeObject(void);
void InitializeDirectionObject(void);
void InitializeBackground(void);
void InitializNextStageButton(void);
void InitializeReturnSelectButton(void);
void InitializeUi(void);
void InitializeEffect(void);

void UpdatePlayer(void);
void UpdateAllyObject(void);
void UpdateEnemyObject(void);
void UpdateDirectionObject(void);
void UpdateReturnObject(void);
void UpdateNextStageButton(void);
void UpdateBackground(void);
void UpdateUi(void);
void UpdateReturnSelectButton(void);
void UpdateEffect(void);

void DrawGrid(void);
void RenderUi(void);

void FollowCursor(GameObject *Object);
void NotOverlapObject(GameObject *ObjectA,GameObject *ObjectB);
void FitToGrid(GameObject *Object);
int MobilityLimitation(GameObject *Object);
void ObjectPotisioning(GameObject *Object);
void ResetMap(void);
int MoveHormingEnemy(GameObject *enemy);
int ClearTransition(void);
void UpdateWorpGrid(GameObject *object,int *worpFlag);


// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializePlay(void)
{
	//�}�X�ڂ̏���������
	InitializeGrid();

	//�}�b�v�̏���������
	InitializeMapData();

	//�v���C���[�̏���������
	InitializePlayer();
	//�I�u�W�F�N�g�̏���������
	InitializeObject();
	//�����I�u�W�F�N�g�̏���������
	InitializeDirectionObject();

	//��蒼���{�^���̏���������
	InitializeReturnObject();

	//�I����ʂɖ߂�{�^���̏�����
	InitializeReturnSelectP();

	//�I���{�^���̏���������
	InitializeSelectButton();

	//�I�u�W�F�N�g�̈ʒu�̏�����
	InitializeObjectPotision();

	//�w�i�̏���������
	InitializeBackground();

	//���̃X�e�[�W�֐i�ރ{�^���̏�����
	InitializNextStageButton();

	//�Z���N�g��ʂɖ߂�{�^���̏�����
	InitializeReturnSelectButton();

	//UI�̏�����
	InitializeUi();

	//�G�t�F�N�g�̏�����
	InitializeEffect();

	g_clearFlag = 0;
	g_endFlag = 0;
	g_transitionCount = 0;
}



//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdatePlay(void)
{
	if (g_endFlag == 0)
	{
		//�v���C���[�̍X�V����
		UpdatePlayer();
		//�����I�u�W�F�N�g�̍X�V����
		if (g_allyObject.state != 0)
		{
			UpdateAllyObject();
		}
		//�G�I�u�W�F�N�g�̍X�V����
		if (g_enemyObject.state != 0)
		{
			UpdateEnemyObject();
		}
		//�����I�u�W�F�N�g�̍X�V����
		UpdateDirectionObject();
		//��蒼���I�u�W�F�N�g�̍X�V����
		UpdateReturnObject();
		//�I����ʂɖ߂�{�^���̍X�V����
		UpdateReturnSelectP();
		if (g_resetFlag == 1)
		{
			ResetMap();
		}
		//Ui�̍X�V
		UpdateUi();
		//�G�t�F�N�g�̍X�V
		UpdateEffect();
	}
	else
	{
		//�N���A���̍X�V����
		UpdateNextStageButton();
		UpdateReturnSelectButton();
		UpdateBackground();
		ClearTransition();
	}
}



//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderPlay(void)
{
	int i;

	int x, y, u, v, w, h;

	//�w�i�̕`��
	DrawObject(&g_background);

	//�}�X�ڂ̕`��
	DrawGrid();

	//�����I�u�W�F�N�g�̕`��
	for (i = 0; i < 4; i++)
	{
		DrawObject(&g_directionObject[i]);
	}

	//�v���C���[�̕`��
	DrawObject(&g_player);

	//�����I�u�W�F�N�g�̕`��
	if (g_allyObject.state != 0)
	{
		DrawAnimation(&g_allyObject);
	}

	//�G�I�u�W�F�N�g�̕`��
	if (g_enemyObject.state != 0)
	{
		DrawAnimation(&g_enemyObject);
	}

	//�G�t�F�N�g�̕`��
	if (g_eatEffectB.state == 1)
	{
		DrawAnimation(&g_eatEffectB);
	}
	if (g_eatEffectW.state == 1)
	{
		DrawAnimation(&g_eatEffectW);
	}

	//��蒼���{�^���̕`��
	if (g_endFlag != 1)
	{
		DrawObject(&g_returnButton);
		DrawObject(&g_returnSelectButtonP);
	}
	if (g_returnObjectUi.state == 1)
	{
		DrawObject(&g_returnObjectUi);
	}

	//�I���{�^���̕`��
	if (g_selectButtonY.state == 1)
	{
		DrawObject(&g_selectButtonY);
	}
	if (g_selectButtonN.state == 1)
	{
		DrawObject(&g_selectButtonN);
	}
	
	if (g_clearFlag == 1)
	{
		for (i = 0; i < 2; i++)
		{
			DrawObject(&g_clearBackground[i]);
		}
	}

	//���̃X�e�[�W�֐i�ރ{�^���̕`��
	if (g_nextStageButton.state == 1)
	{
		DrawObject(&g_nextStageButton);
	}

	//�Z���N�g��ʂɖ߂�{�^���̕`��
	if (g_returnSelectButton.state == 1)
	{
		DrawObject(&g_returnSelectButton);
	}

	//UI�̕`��
	RenderUi();

	if (g_clearFlag == 1)
	{
		x = 120;
		y = 120;

		u = 0;
		v = 128;

		w = 256;
		h = 128;

		DrawRectGraph(x, y, u, v, w, h, g_uiImage, TRUE, FALSE);
	}

}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizePlay(void)
{

}


//----------------------------------------------------------------------
//! @brief �}�X�ڂ̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeGrid(void)
{
	int i, j;

	FILE *fp = NULL;

	char buffer[256];

	char *p = NULL;

	long number;

	switch (g_stageNumber)
	{
	case 1:
		fp = fopen("Resources\\Data\\stage1\\grid1.csv", "r");
		break;
	case 2:
		fp = fopen("Resources\\Data\\stage2\\grid1.csv", "r");
		break;
	case 3:
		fp = fopen("Resources\\Data\\stage3\\grid1.csv", "r");
		break;
	case 4:
		fp = fopen("Resources\\Data\\stage4\\grid1.csv", "r");
		break;
	case 5:
		fp = fopen("Resources\\Data\\stage5\\grid1.csv", "r");
		break;
	case 6:
		fp = fopen("Resources\\Data\\stage6\\grid1.csv", "r");
		break;
	case 7:
		fp = fopen("Resources\\Data\\stage7\\grid1.csv", "r");
		break;
	case 8:
		fp = fopen("Resources\\Data\\stage8\\grid1.csv", "r");
		break;
	case 9:
		fp = fopen("Resources\\Data\\stage9\\grid1.csv", "r");
		break;
	case 10:
		fp = fopen("Resources\\Data\\stage10\\grid1.csv", "r");
		break;
	case 11:
		fp = fopen("Resources\\Data\\stage11\\grid1.csv", "r");
		break;
	}
	if (fp == NULL)
	{
		MessageBox(NULL, "\"grid1.csv\"������܂���", NULL, MB_OK);
		return;
	}

	for (i = 0; i < GRID_HEIGHT; i++)
	{
		if (fgets(buffer, 256, fp) != NULL)
		{
			p = buffer;
			for (j = 0; j < GRID_WIDTH; j++)
			{
				number = strtol(p, &p, 0);
				g_gridData[i][j] = (int)number;
				g_gridDataOrigin[i][j] = (int)number;
				p++;
			}
		}
	}
	if (g_stageNumber == 10)
	{
		fp = fopen("Resources\\Data\\stage12\\grid1.csv", "r");
		if (fp == NULL)
		{
			MessageBox(NULL, "\"grid1.csv\"������܂���", NULL, MB_OK);
			return;
		}

		for (i = 0; i < GRID_HEIGHT; i++)
		{
			if (fgets(buffer, 256, fp) != NULL)
			{
				p = buffer;
				for (j = 0; j < GRID_WIDTH; j++)
				{
					number = strtol(p, &p, 0);
					g_clearGrid[i][j] = (int)number;
					p++;
				}
			}
		}
	}
	fclose(fp);
}


//----------------------------------------------------------------------
//! @brief �v���C���[�̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializePlayer(void)
{
	g_player.pos = { 0,0 };
	g_player.vel = { 0,0 };
	g_player.collisionR = OBJECT_RADIAN;
	g_player.type = 1;
	g_player.state = 1;

	g_player.image.u = 0;
	g_player.image.v = 128;
	g_player.image.w = 32;
	g_player.image.h = 32;
	g_player.image.handle = g_objectImage;

}


//----------------------------------------------------------------------
//! @brief �I�u�W�F�N�g�̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeObject(void)
{
	//�����I�u�W�F�N�g�̏�����
	g_allyObject.pos = { 0,64 };
	g_allyObject.vel = { 0,0 };
	g_allyObject.collisionR = OBJECT_RADIAN;
	g_allyObject.type = 1;
	g_allyObject.state = 0;

	g_allyObject.image.u = 64;
	g_allyObject.image.v = 0;
	g_allyObject.image.w = 32;
	g_allyObject.image.h = 32;
	g_allyObject.image.handle = g_objectImage;

	g_allyObject.anime.numColumns = 2;
	g_allyObject.anime.numFrames = 2;
	g_allyObject.anime.frameDuration = 5;
	g_allyObject.anime.frameIndex = 0;
	g_allyObject.anime.elapsedCount = 0;


	//�G�̃I�u�W�F�N�g�̏�����
	g_enemyObject.pos = { 0,128 };
	g_enemyObject.vel.x = -g_allyObject.vel.x;
	g_enemyObject.vel.y = -g_allyObject.vel.y;
	g_enemyObject.collisionR = OBJECT_RADIAN;
	g_enemyObject.type = 0;
	g_enemyObject.state = 0;

	g_enemyObject.image.u = 0;
	g_enemyObject.image.v = 0;
	g_enemyObject.image.w = 32;
	g_enemyObject.image.h = 32;
	g_enemyObject.image.handle = g_objectImage;

	g_enemyObject.anime.numFrames = 2;
	g_enemyObject.anime.numColumns = 2;
	g_enemyObject.anime.frameDuration = 5;
	g_enemyObject.anime.frameIndex = 0;
	g_enemyObject.anime.elapsedCount = 0;
}


//----------------------------------------------------------------------
//! @brief �����I�u�W�F�N�g�̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeDirectionObject(void)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		g_directionObject[i].type = i + 1;

		g_directionObject[i].image.u = 32 + (32 * i);		//�����ŕ���ł���̂�i�Œ���
		g_directionObject[i].image.v = 128;
		g_directionObject[i].image.w = 32;					//�T�C�Y�͂��ׂē���
		g_directionObject[i].image.h = 32;
		g_directionObject[i].image.handle = g_objectImage;
	}
	g_directionObject[0].pos.x = 564;
	g_directionObject[0].pos.y = 100;

	g_directionObject[1].pos.x = 532;
	g_directionObject[1].pos.y = 68;

	g_directionObject[2].pos.x = 500;
	g_directionObject[2].pos.y = 100;

	g_directionObject[3].pos.x = 532;
	g_directionObject[3].pos.y = 132;

}


//----------------------------------------------------------------------
//! @brief ���̃X�e�[�W�ɐi�ރ{�^���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializNextStageButton(void)
{
	g_nextStageButton.pos = {50,300};
	g_nextStageButton.image.u = 0;
	g_nextStageButton.image.v = 480;
	g_nextStageButton.image.w = 192;
	g_nextStageButton.image.h = 96;
	g_nextStageButton.image.handle = g_buttonImage;

	g_nextStageButton.state = 0;
}


//----------------------------------------------------------------------
//! @brief �Z���N�g��ʂɖ߂�{�^���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeReturnSelectButton(void)
{
	g_returnSelectButton.pos = { 300,300 };
	g_returnSelectButton.image.u = 0;
	g_returnSelectButton.image.v = 256;
	g_returnSelectButton.image.w = 192;
	g_returnSelectButton.image.h = 96;
	g_returnSelectButton.image.handle = g_buttonImage;

	g_returnSelectButton.state = 0;
}


//----------------------------------------------------------------------
//! @brief �I�u�W�F�N�g�ʒu�}�b�v�̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeMapData(void)
{
	int i, j;

	FILE *fp = NULL;

	char buffer[256];

	char *p = NULL;

	long number;


	switch (g_stageNumber)
	{
	case 1:
		fp = fopen("Resources\\Data\\stage1\\potision1.csv", "r");
		break;
	case 2:
		fp = fopen("Resources\\Data\\stage2\\potision1.csv", "r");
		break;
	case 3:
		fp = fopen("Resources\\Data\\stage3\\potision1.csv", "r");
		break;
	case 4:
		fp = fopen("Resources\\Data\\stage4\\potision1.csv", "r");
		break;
	case 5:
		fp = fopen("Resources\\Data\\stage5\\potision1.csv", "r");
		break;
	case 6:
		fp = fopen("Resources\\Data\\stage6\\potision1.csv", "r");
		break;
	case 7:
		fp = fopen("Resources\\Data\\stage7\\potision1.csv", "r");
		break;
	case 8:
		fp = fopen("Resources\\Data\\stage8\\potision1.csv", "r");
		break;
	case 9:
		fp = fopen("Resources\\Data\\stage9\\potision1.csv", "r");
		break;
	case 10:
		fp = fopen("Resources\\Data\\stage10\\potision1.csv", "r");
		break;
	case 11:
		fp = fopen("Resources\\Data\\stage11\\potision1.csv", "r");
		break;
	}
	if (fp == NULL)
	{
		MessageBox(NULL, "\"position.csv\"������܂���", NULL, MB_OK);
		return;
	}

	for (i = 0; i < GRID_HEIGHT; i++)
	{
		if (fgets(buffer, 256, fp) != NULL)
		{
			p = buffer;
			for (j = 0; j < GRID_WIDTH; j++)
			{
				number = strtol(p, &p, 0);
				g_mapData[i][j] = (int)number;
				g_mapDataOrigin[i][j] = (int)number;
				p++;
			}
		}
	}
	fclose(fp);
}



//----------------------------------------------------------------------
//! @brief �I�u�W�F�N�g�̈ʒu�̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeObjectPotision(void)
{
	int i, j;

	for (i = 0; i < GRID_HEIGHT; i++)
	{
		for (j = 0; j < GRID_WIDTH; j++)
		{
			switch (g_mapData[i][j])
			{
				//�v���C���[�̈ʒu�̏�����
			case 1:
				g_player.pos.x = j * GRID_SIZE_X;
				g_player.pos.y = i * GRID_SIZE_Y;
				break;
				//�����I�u�W�F�N�g�̈ʒu�̏�����
			case 2:
				g_allyObject.pos.x = j * GRID_SIZE_X;
				g_allyObject.pos.y = i * GRID_SIZE_Y;
				g_allyObject.state = 1;
				break;
				//�G�I�u�W�F�N�g�̈ʒu�̏�����
			case 3:
				g_enemyObject.pos.x = j * GRID_SIZE_X;
				g_enemyObject.pos.y = i * GRID_SIZE_Y;
				g_enemyObject.state = 1;
				g_enemyObject.type = 0;
				break;
			case 4:
				g_enemyObject.pos.x = j * GRID_SIZE_X;
				g_enemyObject.pos.y = i * GRID_SIZE_Y;
				g_enemyObject.state = 1;
				g_enemyObject.type = 1;
				break;
			default:
				break;
			}
		}
	}
}



//----------------------------------------------------------------------
//! @brief �w�i�̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeBackground(void)
{
	int i;

	g_background.pos.x = 0;
	g_background.pos.y = 0;
	g_background.image.u = 0;
	g_background.image.v = 0;
	g_background.image.w = 640;
	g_background.image.h = 480;
	g_background.image.handle = g_backgroundImage;

	for (i = 0; i < 2; i++)
	{
		g_clearBackground[i].pos.x = 0;
		g_clearBackground[i].pos.y = i * SCREEN_HEIGHT;
		g_clearBackground[i].vel.x = 0;
		g_clearBackground[i].vel.y = -4;
		g_clearBackground[i].image.u = 0;
		g_clearBackground[i].image.v = 0;
		g_clearBackground[i].image.w = 640;
		g_clearBackground[i].image.h = 480;
		g_clearBackground[i].image.handle = g_clearImage;
	}

}


//----------------------------------------------------------------------
//! @brief UI�̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeUi(void)
{
	g_resetUiObject.pos.x = 120;
	g_resetUiObject.pos.y = 50;

	g_resetUiObject.image.u = 256;
	g_resetUiObject.image.v = 160;
	g_resetUiObject.image.w = 256;
	g_resetUiObject.image.h = 96;
	g_resetUiObject.image.handle = g_uiImage;

	g_resetUiObject.state = 0;

	g_arrowUi.posX = 0.0f;
	g_arrowUi.posY = 0.0f;
	g_arrowUi.velX = 0.0f;
	g_arrowUi.velY = 0.0f;
	g_arrowUi.state = 0;

	g_arrowUi.image.u = 0;
	g_arrowUi.image.v = 0;
	g_arrowUi.image.w = 64;
	g_arrowUi.image.h = 64;
	g_arrowUi.image.handle = g_uiImage;
}


//----------------------------------------------------------------------
//! @brief �v���C���[�̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdatePlayer(void)
{
	int playerLeft;
	int playerRight;
	int playerTop;
	int playerBottom;

	int playerCenterX;
	int playerCenterY;

	int gridX, gridY;

	static int worpFlag = 0;

	int x, y;
	int x2, y2;
	int x3, y3;

	int i;

	for (i = 0; i < 4; i++)
	{
		//�����I�u�W�F�N�g�̒��S�̍��W
		gridX = g_directionObject[i].pos.x + (GRID_SIZE_X / 2);
		gridY = g_directionObject[i].pos.y + (GRID_SIZE_Y / 2);

		//�����I�u�W�F�N�g�̒��S�̈ʒu
		playerCenterX = g_player.pos.x + (GRID_SIZE_X / 2);
		playerCenterY = g_player.pos.y + (GRID_SIZE_Y / 2);

		//�����I�u�W�F�N�g�̒��S�̍��W�ƕ����I�u�W�F�N�g�̒��S�̍��W���r
		if (gridX == playerCenterX)
		{
			if (gridY == playerCenterY)
			{
				switch (g_directionObject[i].type)
				{
				case 1:
					g_player.vel.x = 2;
					g_player.vel.y = 0;
					break;
				case 2:
					g_player.vel.x = 0;
					g_player.vel.y = -2;
					break;
				case 3:
					g_player.vel.x = -2;
					g_player.vel.y = 0;
					break;
				case 4:
					g_player.vel.x = 0;
					g_player.vel.y = 2;
					break;
				default:
					g_player.vel.x = 0;
					g_player.vel.y = 0;
					break;
				}
			}
		}
	}

	g_player.pos.x += g_player.vel.x;
	g_player.pos.y += g_player.vel.y;

	//�v���C���[�̈ʒu���}�X�ڂɍ��킹�鏈��
	{
		playerLeft = g_player.pos.x + 1;
		playerRight = g_player.pos.x + 32 - 1;
		playerTop = g_player.pos.y + 1;
		playerBottom = g_player.pos.y + 32 - 1;

		playerCenterX = g_player.pos.x + 16;
		playerCenterY = g_player.pos.y + 16;

		x = playerLeft / 32;
		y = playerTop / 32;

		//�ړ��悪���}�X�ȊO�̎�
		if (g_gridData[y][x] == 0 || g_gridData[y][x] == -1)
		{
			g_player.pos.x = (playerCenterX / 32) * 32;
			g_player.pos.y = (playerCenterY / 32) * 32;
		}

		x = playerRight / 32;
		y = playerTop / 32;

		if (g_gridData[y][x] == 0 || g_gridData[y][x] == -1 && x < 15)
		{
			g_player.pos.x = (playerCenterX / 32) * 32;
			g_player.pos.y = (playerCenterY / 32) * 32;
		}

		x = playerLeft / 32;
		y = playerBottom / 32;

		if (g_gridData[y][x] == 0 || g_gridData[y][x] == -1)
		{
			g_player.pos.x = (playerCenterX / 32) * 32;
			g_player.pos.y = (playerCenterY / 32) * 32;
		}

		x = playerRight / 32;
		y = playerBottom / 32;

		if (g_gridData[y][x] == 0 || g_gridData[y][x] == -1 && x < 15)
		{
			g_player.pos.x = (playerCenterX / 32) * 32;
			g_player.pos.y = (playerCenterY / 32) * 32;
		}
	}
	//�N���A�������ǂ������f���鏈��
	//�}�b�v��2�̈ʒu�ɐG�ꂽ��N���A
	x = playerCenterX / 32;
	y = playerCenterY / 32;

	x2 = playerLeft / 32;
	y2 = playerTop / 32;

	x3 = playerRight / 32;
	y3 = playerBottom / 32;

	if (g_gridData[y][x] == 2 && g_gridData[y2][x2] == 2 && g_gridData[y3][x3] == 2)  
	{
		g_endFlag = 1;
	}

	UpdateWorpGrid(&g_player,&worpFlag);

	//�v���C���[���}�b�v���Ɏ��߂鏈��
	{
		if (g_player.pos.x >= 480 - 32)
		{
			g_player.pos.x = 480 - 32;
		}
		if (g_player.pos.x <= 0)
		{
			g_player.pos.x = 0;
		}

		if (g_player.pos.y >= 480 - 32)
		{
			g_player.pos.y = 480 - 32;
		}
		if (g_player.pos.y <= 0)
		{
			g_player.pos.y = 0;
		}
	}
}


//----------------------------------------------------------------------
//! @brief �����I�u�W�F�N�g�̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateAllyObject(void)
{
	int objectGridX, objectGridY;
	int objectCenterX, objectCenterY;
	int gridX, gridY;
	static int soundFlag = 0;
	static int worpFlag = 0;

	int i;
	int animeEnd;

	for (i = 0; i < 4; i++)
	{
		//�����I�u�W�F�N�g�̒��S�̍��W
		gridX = g_directionObject[i].pos.x + (GRID_SIZE_X / 2);
		gridY = g_directionObject[i].pos.y + (GRID_SIZE_Y / 2);

		//�����I�u�W�F�N�g�̒��S�̈ʒu
		objectCenterX = g_allyObject.pos.x + (GRID_SIZE_X / 2);
		objectCenterY = g_allyObject.pos.y + (GRID_SIZE_Y / 2);

		//�����I�u�W�F�N�g�̒��S�̍��W�ƕ����I�u�W�F�N�g�̒��S�̍��W���r
		if (gridX == objectCenterX)
		{
			if (gridY == objectCenterY)
			{
				switch (g_directionObject[i].type)
				{

				case 1:
					g_allyObject.vel.x = 2;
					g_allyObject.vel.y = 0;
					break;
				case 2:
					g_allyObject.vel.x = 0;
					g_allyObject.vel.y = -2;
					break;
				case 3:
					g_allyObject.vel.x = -2;
					g_allyObject.vel.y = 0;
					break;
				case 4:
					g_allyObject.vel.x = 0;
					g_allyObject.vel.y = 2;
					break;
				default:
					break;
				}
				switch (g_enemyObject.type)
				{
				case 0:
					g_enemyObject.vel.x = -g_allyObject.vel.x;
					g_enemyObject.vel.y = -g_allyObject.vel.y;
					break;
				case 1:
					break;
				case 2:
					break;
				default:
					break;
				}
				ObjectPotisioning(&g_enemyObject);
			}
		}
	}

	objectGridX = (g_allyObject.pos.x + 16) / 32;
	objectGridY = (g_allyObject.pos.y + 16) / 32;

	//�}�X��h��ւ��鏈��
	if (g_gridData[objectGridY][objectGridX] != g_allyObject.type && g_gridData[objectGridY][objectGridX] == 0)
	{
		if (soundFlag != 1)
		{
			PlaySoundMem(g_effectSound2, DX_PLAYTYPE_BACK, TRUE);
			soundFlag = 1;
		}
		g_gridData[objectGridY][objectGridX] = g_allyObject.type;

		g_eatEffectW.pos.x = (objectGridX * 32) + 16 - (g_eatEffectW.image.w / 2);
		g_eatEffectW.pos.y = (objectGridY * 32) + 16 - (g_eatEffectW.image.h / 2);
		g_eatEffectW.anime.frameIndex = 0;
		g_eatEffectW.state = 1;	
	}
	else
	{
		soundFlag = 0;
	}

	//�ړ�����
	g_allyObject.pos.x += g_allyObject.vel.x;
	g_allyObject.pos.y += g_allyObject.vel.y;

	UpdateWorpGrid(&g_allyObject,&worpFlag);

	//�摜�̉�]����
	if (g_allyObject.vel.x < 0)
	{
		g_allyObject.image.v = 0;
	}
	else if (g_allyObject.vel.x > 0)
	{
		g_allyObject.image.v = 64;
	}
	else if (g_allyObject.vel.y < 0)
	{
		g_allyObject.image.v = 32;
	}
	else if (g_allyObject.vel.y > 0)
	{
		g_allyObject.image.v = 96;
	}
	//�A�j���[�V��������
	animeEnd = UpdateAnimetion(&g_allyObject);
	if (animeEnd == 1)
	{
		g_allyObject.anime.frameIndex = 0;
	}

	//�ړ������̏���
	MobilityLimitation(&g_allyObject);
}


//----------------------------------------------------------------------
//! @brief �G�I�u�W�F�N�g�̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateEnemyObject(void)
{
	int x, y;
	static int soundFlag = 0;
	int animeEnd;
	static int worpFlag = 0;
	int i;
	int gridX, gridY;
	int objectCenterX, objectCenterY;

	for (i = 0; i < 4; i++)
	{
		//�����I�u�W�F�N�g�̒��S�̍��W
		gridX = g_directionObject[i].pos.x + (GRID_SIZE_X / 2);
		gridY = g_directionObject[i].pos.y + (GRID_SIZE_Y / 2);

		//�G�I�u�W�F�N�g�̒��S�̈ʒu
		objectCenterX = g_enemyObject.pos.x + (GRID_SIZE_X / 2);
		objectCenterY = g_enemyObject.pos.y + (GRID_SIZE_Y / 2);

		//�G�I�u�W�F�N�g�̒��S�̍��W�ƕ����I�u�W�F�N�g�̒��S�̍��W���r
		if (gridX == objectCenterX)
		{
			if (gridY == objectCenterY)
			{
				switch (g_directionObject[i].type)
				{
				case 1:
					g_enemyObject.vel.x = 2;
					g_enemyObject.vel.y = 0;
					break;
				case 2:
					g_enemyObject.vel.x = 0;
					g_enemyObject.vel.y = -2;
					break;
				case 3:
					g_enemyObject.vel.x = -2;
					g_enemyObject.vel.y = 0;
					break;
				case 4:
					g_enemyObject.vel.x = 0;
					g_enemyObject.vel.y = 2;
					break;
				default:
					break;
				}
			}
		}
	}

	x = (g_enemyObject.pos.x + g_enemyObject.collisionR) / 32;
	y = (g_enemyObject.pos.y + g_enemyObject.collisionR) / 32;

	if (g_gridData[y][x] != g_enemyObject.type && g_gridData[y][x] == 1)
	{
		if (soundFlag != 1)
		{
			PlaySoundMem(g_effectSound2, DX_PLAYTYPE_BACK, TRUE);
			soundFlag = 1;
		}
		g_gridData[y][x] = g_enemyObject.type;

		g_eatEffectB.pos.x = (x * 32) + 16 - (g_eatEffectB.image.w / 2);
		g_eatEffectB.pos.y = (y * 32) + 16 - (g_eatEffectB.image.h / 2);
		g_eatEffectB.anime.frameIndex = 0;
		g_eatEffectB.state = 1;


	}
	else
	{
		soundFlag = 0;
	}

	//�ړ�����
	g_enemyObject.pos.x += g_enemyObject.vel.x;
	g_enemyObject.pos.y += g_enemyObject.vel.y;

	UpdateWorpGrid(&g_enemyObject,&worpFlag);

	//�摜�̉�]����
	if (g_enemyObject.vel.x < 0)
	{
		g_enemyObject.image.v = 0;
	}
	else if(g_enemyObject.vel.x > 0)
	{
		g_enemyObject.image.v = 64;
	}
	else if (g_enemyObject.vel.y < 0)
	{
		g_enemyObject.image.v = 32;
	}
	else if (g_enemyObject.vel.y > 0)
	{
		g_enemyObject.image.v = 96;
	}
	//�A�j���[�V�����̍X�V
	animeEnd = UpdateAnimetion(&g_enemyObject);
	if (animeEnd == 1)
	{
		g_enemyObject.anime.frameIndex = 0;
	}

	//�ړ������̏���
	MobilityLimitation(&g_enemyObject);

}


//----------------------------------------------------------------------
//! @brief �����I�u�W�F�N�g�̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateDirectionObject(void)
{
	int i,j;

	for (i = 0; i < 4; i++)
	{
		if (g_mouse.CurrentInputState != 1)
		{
			//�}�X�ڂɍ��킹�鏈��
			FitToGrid(&g_directionObject[i]);
		}
		//�I�u�W�F�N�g���d�Ȃ�Ȃ��悤�ɂ��鏈��
		for (j = 0; j < 4; j++)
		{
			if (i == j)continue;
			NotOverlapObject(&g_directionObject[i], &g_directionObject[j]);
		}

		//�J�[�\���ɒǏ]�����鏈��
		FollowCursor(&g_directionObject[i]);
	}
}


//----------------------------------------------------------------------
//! @brief ���̃X�e�[�W�֐i�ރ{�^���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateNextStageButton(void)
{
	int updateResult = 0;
	static int soundFlag = 0;
	
	updateResult = UpdateButton(&g_nextStageButton, &soundFlag);
	
	if (updateResult == 2)
	{
		g_stageNumber += 1;
		InitializePlay();
	}
}


//----------------------------------------------------------------------
//! @brief �Z���N�g��ʂɖ߂�{�^���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateReturnSelectButton(void)
{
	int updateResult = 0;
	static int soundFlag = 0;

	updateResult = UpdateButton(&g_returnSelectButton, &soundFlag);

	if (updateResult == 2)
	{
		ChangeScene(SCENE_SELECT);
	}
}


//----------------------------------------------------------------------
//! @brief �N���A���w�i�̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateBackground(void)
{
	int i;
	for (i = 0; i < 2; i++)
	{
		if (g_clearFlag == 1)
		{
			g_clearBackground[i].pos.x += g_clearBackground[i].vel.x;
			g_clearBackground[i].pos.y += g_clearBackground[i].vel.y;

			if (g_clearBackground[i].pos.y == 0 - SCREEN_HEIGHT)
			{
				g_clearBackground[i].pos.y = SCREEN_HEIGHT;
			}
		}
	}
}


//----------------------------------------------------------------------
//! @brief �}�b�v�̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawGrid(void)
{
	int i, j;
	int x, y;
	int u, v;


	for (i = 0; i < GRID_HEIGHT; i++)
	{
		for (j = 0; j < GRID_WIDTH; j++)
		{
			x = j * GRID_SIZE_X;
			y = i * GRID_SIZE_Y;

			u = (g_gridData[i][j] % 6) * GRID_SIZE_X;
			v = (g_gridData[i][j] / 6) * GRID_SIZE_Y;

			DrawRectGraph(x, y, u, v, GRID_SIZE_X, GRID_SIZE_Y, g_mapImage, TRUE, FALSE);
		}
	}
}


//----------------------------------------------------------------------
//! @brief �I�u�W�F�N�g���}�E�X�J�[�\���ɒǏ]�����鏈��
//!
//! @param[in] Object
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FollowCursor(GameObject *object)
{
	static int followNumber = 0;
	static int holdFlag = 0;

	int mouseClicked = 0;

	mouseClicked = CheckClickObject(object);
	//�}�E�X�ɂ��Ă������鏈��
	if (mouseClicked == 1 || holdFlag == 1 && g_mouse.CurrentInputState == 1)
	{
		if (followNumber == object->type || followNumber == 0)
		{
			followNumber = object->type;

			object->pos.x = g_mouse.Pos.x - 16;
			object->pos.y = g_mouse.Pos.y - 16;

			holdFlag = 1;

			object->state = 1;
		}
	}
	else
	{
		object->state = 0;
		followNumber = 0;
		holdFlag = 0;
	}
}


//----------------------------------------------------------------------
//! @brief �I�u�W�F�N�gA�ƃI�u�W�F�N�gB���d�Ȃ�Ȃ��悤�ɂ��鏈��
//!
//! @param[in] ObjectA ObjectB
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void NotOverlapObject(GameObject *objectA, GameObject *objectB)
{
	if (objectA->pos.x == objectB->pos.x)
	{
		if (objectA->pos.y == objectB->pos.y)
		{
			objectA->pos.x += -32;
			if (objectA->pos.x <= 0)
			{
				objectA->pos.x += 32;
				objectA->pos.y += -32;
			}
		}
	}
}


//----------------------------------------------------------------------
//! @brief �I�u�W�F�N�g���}�X�ڂɍ��킹�鏈��
//!
//! @param[in] Object
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FitToGrid(GameObject *object)
{
	int gridX;
	int gridY;

	gridX = (object->pos.x + 16) / GRID_SIZE_X;
	gridY = (object->pos.y + 16) / GRID_SIZE_Y;

	if (g_mouse.CurrentInputState != 1)
	{
		if (gridX < GRID_WIDTH && gridY < GRID_HEIGHT)
		{
			object->pos.x = gridX * GRID_SIZE_X;
			object->pos.y = gridY * GRID_SIZE_Y;
		}
	}

	
}


//----------------------------------------------------------------------
//! @brief �I�u�W�F�N�g�̈ړ������̏���
//!
//! @param[in] Object
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
int MobilityLimitation(GameObject *object)
{
	int objectCenterX	= object->pos.x + GRID_SIZE_X / 2;
	int objectCenterY	= object->pos.y + GRID_SIZE_Y / 2;
	int objectRight		= objectCenterX + object->collisionR;
	int objectLeft		= objectCenterX - object->collisionR;
	int objectTop		= objectCenterY - object->collisionR;
	int objectBottom	= objectCenterY + object->collisionR;


	int gridX;
	int gridY;

	//X���̒[�̒��˕Ԃ�
	if (object->pos.x > MAP_WIDTH - GRID_SIZE_X)
	{
		//Object->pos.x = MAP_WIDTH - GRID_SIZE_X;
		ObjectPotisioning(object);
		object->vel.x *= -1;
		return 0;
	}
	if (object->pos.x < 0)
	{
		//Object->pos.x = 0;
		ObjectPotisioning(object);
		object->vel.x *= -1;
		return 0;
	}

	//Y���̒[�̒��˕Ԃ菈��
	if (object->pos.y > MAP_HEIGHT - GRID_SIZE_Y)
	{
		//Object->pos.y = MAP_HEIGHT - GRID_SIZE_Y;
		ObjectPotisioning(object);
		object->vel.y *= -1;
		return 0;
	}
	if (object->pos.y < 0)
	{
		//Object->pos.y = 0;
		ObjectPotisioning(object);
		object->vel.y *= -1;
		return 0;
	}

	//�����}�X�̒��˕Ԃ菈��
	//�E�[
	gridX = objectRight / GRID_SIZE_X;
	gridY = objectCenterY / GRID_SIZE_Y;
	if (g_gridData[gridY][gridX] == -1)
	{
		//Object->pos.x -= 1;
		ObjectPotisioning(object);
		object->vel.x *= -1;
		return 0;
	}

	//���[
	gridX = objectLeft / GRID_SIZE_X;
	gridY = objectCenterY / GRID_SIZE_Y;
	if (g_gridData[gridY][gridX] == -1)
	{
		//Object->pos.x += 1;
		ObjectPotisioning(object);
		object->vel.x *= -1;
		return 0;
	}

	//��[
	gridX = objectCenterX / GRID_SIZE_X;
	gridY = objectTop / GRID_SIZE_Y;
	if (g_gridData[gridY][gridX] == -1)
	{
		//Object->pos.y -= 1;
		ObjectPotisioning(object);
		object->vel.y *= -1;
		return 0;
	}

	//���[
	gridX = objectCenterX / GRID_SIZE_X;
	gridY = objectBottom / GRID_SIZE_Y;
	if (g_gridData[gridY][gridX] == -1)
	{
		//Object->pos.y += 1;
		ObjectPotisioning(object);
		object->vel.y *= -1;
		return 0;
	}

	return 0;
}


//----------------------------------------------------------------------
//! @brief �I�u�W�F�N�g�̈ʒu�����̏���
//!
//! @param[in] Object
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ObjectPotisioning(GameObject *object)
{
	int	gridX = (object->pos.x + (GRID_SIZE_X / 2)) / 32;
	int gridY = (object->pos.y + (GRID_SIZE_Y / 2)) / 32;

	object->pos.x = gridX * 32;
	object->pos.y = gridY * 32;
}


//----------------------------------------------------------------------
//! @brief �}�b�v�����Ƃ̏�ԂɃ��Z�b�g���鏈��
//!
//! @param[in] Object
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ResetMap(void)
{
	int i, j;

	for (i = 0; i < GRID_HEIGHT; i++)
	{
		for (j = 0; j < GRID_WIDTH; j++)
		{
			g_gridData[i][j] = g_gridDataOrigin[i][j];
			InitializePlayer();
			InitializeObject();
			InitializeDirectionObject();
			InitializeObjectPotision();
		}
	}
}


//----------------------------------------------------------------------
//! @brief �G�̒ǔ��ړ�����(������)
//!
//! @param[in] Object �G
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
int MoveHormingEnemy(GameObject *enemy)
{
	int gridX,gridY;

	int right, left;

	int top, bottom;

	int x, y;

	gridX = (enemy->pos.x + GRID_SIZE_X / 2) / GRID_SIZE_X;
	gridY = (enemy->pos.y + GRID_SIZE_Y / 2) / GRID_SIZE_Y;

	for (x = 0; x < GRID_WIDTH; x++)
	{
		right = gridX + x;
		left = gridX - x;

		if (right < GRID_WIDTH)
		{
			if (g_gridData[gridY][gridX + x] == 1)
			{
				enemy->vel.x = 2;
				enemy->vel.y = 0;
				return 0;
			}
		}
		if (left >= 0)
		{
			if (g_gridData[gridY][gridX - x] == 1)
			{
				enemy->vel.x = -2;
				enemy->vel.y = 0;
				return 0;
			}
		}
	}

	for (y = 0; y < GRID_HEIGHT; y++)
	{
		top = gridY - y;
		bottom = gridY + y;

		if (bottom < GRID_HEIGHT)
		{
			if (g_gridData[gridY + y][gridX] == 1)
			{
				enemy->vel.x = 0;
				enemy->vel.y = 2;
				return 0;
			}
		}
		if (top >= 0)
		{
			if (g_gridData[gridY - y][gridX] == 1)
			{
				enemy->vel.x = 0;
				enemy->vel.y = -2;
				return 0;
			}
		}
	}

	return 0;
}



//----------------------------------------------------------------------
//! @brief UI�̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateUi(void)
{
	Vec2D uiPos1 = {g_directionObject[0].pos.x - 96,g_directionObject[0].pos.y - 64};
	Vec2D uiPos2 = {g_player.pos.x - 64,g_player.pos.y - 64};
	Vec2D uiPos3 = {g_allyObject.pos.x - 64,g_allyObject.pos.y - 64};

	switch (g_stageNumber)
	{
	case 1:
		if (g_directionObject[0].state == 0)
		{
			g_arrowUi.posX = (float)uiPos1.x;
			g_arrowUi.posY = (float)uiPos1.y;
			g_arrowUi.state = 1;
			if (g_player.vel.x != 0)
			{
				g_arrowUi.state = 0;
			}
		}
		else if (g_player.vel.x == 0)
		{
			g_arrowUi.posX = (float)uiPos2.x;
			g_arrowUi.posY = (float)uiPos2.y;
			g_arrowUi.state = 1;
		}
		else
		{
			g_arrowUi.state = 0;
		}
		break;
	case 2:
		if (g_directionObject[0].state == 0)
		{
			g_arrowUi.posX = (float)uiPos1.x;
			g_arrowUi.posY = (float)uiPos1.y;
			g_arrowUi.state = 1;
		}
		else if (g_allyObject.vel.x == 0)
		{
			g_arrowUi.posX = (float)uiPos3.x;
			g_arrowUi.posY = (float)uiPos3.y;
			g_arrowUi.state = 1;
		}
		else
		{
			g_arrowUi.state = 0;
		}

		if (g_directionObject[1].state == 0)
		{
			if (g_allyObject.vel.x != 0)
			{
				g_arrowUi.posX = (float)(g_directionObject[1].pos.x - 64);
				g_arrowUi.posY = (float)(g_directionObject[1].pos.y - 64);
				g_arrowUi.state = 1;
				if (g_player.vel.y != 0)
				{
					g_arrowUi.state = 0;
				}
			}
		}
		else if (g_player.vel.y == 0)
		{
			g_arrowUi.posX = (float)uiPos2.x;
			g_arrowUi.posY = (float)uiPos2.y;
			g_arrowUi.state = 1;
		}
		else
		{
			g_arrowUi.state = 0;
		}
		
		break;
	default:
		break;
	}


	if (g_selectButtonY.state == 1)
	{
		g_resetUiObject.state = 1;
	}
	else
	{
		g_resetUiObject.state = 0;
	}
}


//----------------------------------------------------------------------
//! @brief UI�̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderUi(void)
{
	if (g_resetUiObject.state == 1)
	{
		DrawObject(&g_resetUiObject);
	}
	if (g_arrowUi.state == 1)
	{
		DrawRectGraphF(g_arrowUi.posX, g_arrowUi.posY, g_arrowUi.image.u, g_arrowUi.image.v, g_arrowUi.image.w, g_arrowUi.image.h,
			g_arrowUi.image.handle, TRUE, FALSE);
	}
}


//----------------------------------------------------------------------
//! @brief �N���A���o�̏���
//!
//! @param[in] 
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
int ClearTransition(void)
{
	int i, j;

	if (g_transitionCount >= 2)
	{
		g_transitionCount = 0;
		for (i = 0; i < GRID_HEIGHT; i++)
		{
			for (j = 0; j < GRID_WIDTH; j++)
			{
				if (g_stageNumber == 10)
				{
					if (g_gridData[i][j] != g_clearGrid[i][j])
					{
						g_gridData[i][j] = g_clearGrid[i][j];
						return 0;
					}
				}
				else
				{
					if (g_gridData[i][j] == 0)
					{
						g_gridData[i][j] = 1;
						return 0;
					}
				}
			}
		}
		if (i == GRID_HEIGHT && j == GRID_WIDTH)
		{
			g_clearFlag = 1;
			g_nextStageButton.state = 1;
			g_returnSelectButton.state = 1;
			g_clearStageFlag[g_stageNumber - 1] = g_clearFlag;
		}
	}
	g_transitionCount++;
	return 0;
}


//----------------------------------------------------------------------
//! @brief �G�t�F�N�g�̏���������
//!
//! @param[in] 
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeEffect(void)
{
	g_eatEffectB.image.u = 0;
	g_eatEffectB.image.v = 0;
	g_eatEffectB.image.w = 64;
	g_eatEffectB.image.h = 64;
	g_eatEffectB.image.handle = g_eatEffectImageB;

	g_eatEffectB.anime.numFrames = 30;
	g_eatEffectB.anime.numColumns = 5;
	g_eatEffectB.anime.frameDuration = 0;
	g_eatEffectB.anime.frameIndex = 0;
	g_eatEffectB.anime.elapsedCount = 0;

	g_eatEffectB.state = 0;

	g_eatEffectW.image.u = 0;
	g_eatEffectW.image.v = 0;
	g_eatEffectW.image.w = 64;
	g_eatEffectW.image.h = 64;
	g_eatEffectW.image.handle = g_eatEffectImageW;

	g_eatEffectW.anime.numFrames = 30;
	g_eatEffectW.anime.numColumns = 5;
	g_eatEffectW.anime.frameDuration = 0;
	g_eatEffectW.anime.frameIndex = 0;
	g_eatEffectW.anime.elapsedCount = 0;

	g_eatEffectW.state = 0;
}

//----------------------------------------------------------------------
//! @brief �G�t�F�N�g�̍X�V����
//!
//! @param[in] 
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateEffect(void)
{
	int animeEnd = 0;

	if (g_eatEffectB.state == 1)
	{
		animeEnd = UpdateAnimetion(&g_eatEffectB);
		if (animeEnd == 1)
		{
			g_eatEffectB.state = 0;
		}
	}

	if (g_eatEffectW.state == 1)
	{
		animeEnd = UpdateAnimetion(&g_eatEffectW);
		if (animeEnd == 1)
		{
			g_eatEffectW.state = 0;
		}
	}
}


//----------------------------------------------------------------------
//! @brief ���[�v�}�X�̍X�V����
//!
//! @param[in] 
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateWorpGrid(GameObject *object,int *worpFlag)
{
	int gridX, gridY;
	int i, j;

	gridX = object->pos.x / 32;
	gridY = object->pos.y / 32;

	if (g_gridData[gridY][gridX] == 4)
	{
		if (*worpFlag != 1)
		{
			for (i = 0; i < GRID_HEIGHT; i++)
			{
				for (j = 0; j < GRID_WIDTH; j++)
				{
					if (g_gridData[i][j] == 5)
					{
						object->pos.x = j * 32;
						object->pos.y = i * 32;
						*worpFlag = 1;
						break;
					}
				}
			}
		}
	}
	else if (g_gridData[gridY][gridX] == 5)
	{
		if (*worpFlag != 1)
		{
			for (i = 0; i < GRID_HEIGHT; i++)
			{
				for (j = 0; j < GRID_WIDTH; j++)
				{
					if (g_gridData[i][j] == 4)
					{
						object->pos.x = j * 32;
						object->pos.y = i * 32;
						*worpFlag = 1;
					}
				}
			}
		}
	}
	else
	{
		*worpFlag = 0;
	}
}