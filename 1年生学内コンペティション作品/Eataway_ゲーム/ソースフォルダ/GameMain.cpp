//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   ���t
//!
//! @author ����Җ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include"SceneLogo.h"
#include"SceneTitle.h"
#include"SceneSelect.h"
#include"ScenePlay.h"
#include"Button.h"
#include"Mouse.h"

// �萔�̒�` ====================================================
//�V�[���̏��
enum tag_SceneState
{
	SSTATE_NORMAL,
	SSTATE_FADEIN,
	SSTATE_FADEOUT
};
typedef enum tag_SceneState SceneState;

// �O���[�o���ϐ��̒�` ====================================================
SceneId g_currentSceneId;
SceneId g_nextSceneId;

int g_currentInputState;
int g_lastInputState;
int g_sceneState;
int g_alpha;
int g_clearFlag;
int g_stageNumber;
int g_clearStageFlag[10];

GameObject g_mouseEffect;

HGRP g_mapImage;
HGRP g_objectImage;
HGRP g_uiImage;
HGRP g_backgroundImage;
HGRP g_clearImage;
HGRP g_ruleImage1;
HGRP g_ruleImage2;
HGRP g_ruleImage3;
HGRP g_selectImage;
HGRP g_buttonImage;
HGRP g_mouseEffectImage;
HGRP g_eatEffectImageB;
HGRP g_eatEffectImageW;

HSND g_effectSound1;
HSND g_effectSound2;

// �֐��̐錾 ==============================================================
//�V�[���̏�����
void InitializeScene(void);
//�V�[���̍X�V
void UpdateScene(void);
//�V�[���̕`�揈��
void RenderScene(void);
//�V�[���̏I������
void FinalizeScene(void);
//�V�[���̐؂�ւ�����
void ChangeScene(SceneId nextSceneId);
//�A�j���[�V�����̍X�V
int UpdateAnimetion(GameObject *object);
//�t�F�[�h�C���̏���
void FadeIn(void);
//�t�F�[�h�A�E�g�̏���
void FadeOut(void);
//�摜�̓ǂݍ���
void loadImage(void);
//�}�E�X�G�t�F�N�g�̏���������
void InitializeMouseEffect(void);
//�}�E�X�G�t�F�N�g�̍X�V����
void UpdateMouseEffect(void);


// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeGame(void)
{
	int i;
	SetMouseDispFlag(TRUE);
	//���̃V�[��ID�̏�����
	g_currentSceneId = SCENE_NONE;
	//���̃V�[��ID�̏�����
	g_nextSceneId = SCENE_LOGO;
	//�����x�̏�����
	g_alpha = 255;
	//�V�[���̏�Ԃ̏�����
	g_sceneState = SSTATE_FADEIN;

	g_stageNumber = 0;

	loadImage();

	g_effectSound1 = LoadSoundMem("Resources\\Sounds\\cursor8.mp3");
	g_effectSound2 = LoadSoundMem("Resources\\Sounds\\suck1.mp3");

	for (i = 0; i < 10; i++)
	{
		g_clearStageFlag[i] = 0;
	}

	InitializeButtonImage();
	InitializeMouseEffect();
}



//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateGame(void)
{
	g_currentInputState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	UpdateMouse();
	UpdateMouseEffect();

	//�t�F�[�h�A�E�g����
	if (g_sceneState == SSTATE_FADEOUT)
	{
		FadeOut();
	}

	//�t�F�[�h�C������
	if (g_sceneState == SSTATE_FADEIN)
	{
		FadeIn();
	}
	if (g_nextSceneId != g_currentSceneId)
	{
		if (g_sceneState == SSTATE_FADEIN)
		{
			//�V�[���̏I������
			FinalizeScene();

			//�V�[��ID�̐؂�ւ�
			g_currentSceneId = g_nextSceneId;

			//�V�[���̏���������
			InitializeScene();
		}
	}

	//�V�[���̍X�V����
	if (g_sceneState == SSTATE_NORMAL)
	{
		UpdateScene();
	}

	g_mouse.LastInputState = g_mouse.CurrentInputState;
	g_lastInputState = g_currentInputState;
}



//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderGame(void)
{
	RenderScene();
	if (g_sceneState != SSTATE_NORMAL)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, g_alpha);
		DrawBox(0, 0, SCREEN_RIGHT, SCREEN_BOTTOM, COLOR_BLACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	if (g_mouseEffect.state == 1)
	{
		DrawAnimation(&g_mouseEffect);
	}
}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeGame(void)
{
	DeleteSoundMem(g_effectSound1);
	DeleteSoundMem(g_effectSound2);
	DeleteGraph(g_uiImage);
	DeleteGraph(g_mapImage);
	DeleteGraph(g_objectImage);
	DeleteGraph(g_uiImage);
	DeleteGraph(g_backgroundImage);
	DeleteGraph(g_clearImage);
	DeleteGraph(g_ruleImage1);
	DeleteGraph(g_ruleImage2);
	DeleteGraph(g_ruleImage3);
	DeleteGraph(g_selectImage);
	DeleteGraph(g_buttonImage);
	DeleteGraph(g_mouseEffectImage);
	DeleteGraph(g_eatEffectImageB);
	DeleteGraph(g_eatEffectImageW);
}
//----------------------------------------------------------------------
//! @brief �V�[���̐؂�ւ�����
//!
//! @param[in] nextSceneId	���̃V�[��ID
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ChangeScene(SceneId nextSceneId)
{
	
	g_nextSceneId = nextSceneId;
	g_sceneState = SSTATE_FADEOUT;
	
}
//----------------------------------------------------------------------
//! @brief �t�F�[�h�C������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FadeIn(void)
{
	g_alpha -= 2;
	if (g_alpha <= 0)
	{
		g_sceneState = SSTATE_NORMAL;
	}
}
//----------------------------------------------------------------------
//! @brief �t�F�[�h�A�E�g����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FadeOut(void)
{
	g_alpha += 4;
	if (g_alpha >= 255)
	{
		g_sceneState = SSTATE_FADEIN;
	}
}
//----------------------------------------------------------------------
//! @brief �V�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeScene(void)
{
	switch (g_currentSceneId)
	{
	case SCENE_LOGO:
		InitializeLogo();
		break;
	case SCENE_TITLE:
		InitializeTitle();
		break;
	case SCENE_SELECT:
		InitializeSelect();
		break;
	case SCENE_PLAY:
		InitializePlay();
		break;
	}
}
//----------------------------------------------------------------------
//! @brief �V�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateScene(void)
{
	switch (g_currentSceneId)
	{
	case SCENE_LOGO:
		UpdateLogo();
		break;
	case SCENE_TITLE:
		UpdateTitle();
		break;
	case SCENE_SELECT:
		UpdateSelect();
		break;
	case SCENE_PLAY:
		UpdatePlay();
		break;
	}
}
//----------------------------------------------------------------------
//! @brief �V�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderScene(void)
{
	switch (g_currentSceneId)
	{
	case SCENE_LOGO:
		RenderLogo();
		break;
	case SCENE_TITLE:
		RenderTitle();
		break;
	case SCENE_SELECT:
		RenderSelect();
		break;
	case SCENE_PLAY:
		RenderPlay();
		break;
	}
}
//----------------------------------------------------------------------
//! @brief �V�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeScene(void)
{
	switch (g_currentSceneId)
	{
	case SCENE_LOGO:
		FinalizeLogo();
		break;
	case SCENE_TITLE:
		FinalizeTitle();
		break;
	case SCENE_SELECT:
		FinalizeSelect();
		break;
	case SCENE_PLAY:
		FinalizePlay();
		break;
	}
}
//----------------------------------------------------------------------
//! @brief	�A�j���[�V�����̍X�V����
//!
//! @param[in] object	�A�j���[�V�������X�V������I�u�W�F�N�g
//!
//! @return �A�j���[�V�������I��������ǂ����̒l 0�E�E�E�I����Ă��Ȃ� 1�E�E�E�I�����
//----------------------------------------------------------------------
int UpdateAnimetion(GameObject *object)
{
	object->anime.elapsedCount++;
	if (object->anime.elapsedCount > object->anime.frameDuration)
	{
		object->anime.frameIndex++;
		object->anime.elapsedCount = 0;
		if (object->anime.frameIndex == object->anime.numFrames)
		{
			return 1;
		}
	}
	return 0;
}


//----------------------------------------------------------------------
//! @brief �I�u�W�F�N�g�Ƀ}�E�X���d�Ȃ��Ă��邩���肷�鏈��
//!
//! @param[in] Object
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
int CheckOverlapMouse(GameObject *object)
{
	int objectRight, objectLeft, objectTop, objectBottom;

	objectRight = object->pos.x + object->image.w;
	objectLeft = object->pos.x;
	objectTop = object->pos.y;
	objectBottom = object->pos.y + object->image.h;

	if (objectRight > g_mouse.Pos.x)
	{
		if (objectLeft < g_mouse.Pos.x)
		{
			if (objectTop < g_mouse.Pos.y)
			{
				if (objectBottom > g_mouse.Pos.y)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}


//----------------------------------------------------------------------
//! @brief �I�u�W�F�N�g���N���b�N����Ă��邩���肷�鏈��
//!
//! @param[in] Object
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
int CheckClickObject(GameObject *object)
{
	int mouseOverlaped = 0;

	mouseOverlaped = CheckOverlapMouse(object);

	//�w�肵���I�u�W�F�N�g���A�N���b�N���ꂽ��
	if (mouseOverlaped == 1)
	{
		if (g_mouse.CurrentInputState == 1)
		{
			return 1;
		}
	}

	return 0;
}


//----------------------------------------------------------------------
//! @brief �G���[����
//!
//! @param[in] �摜�n���h��
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void CheckError(HGRP *image)
{
	if (*image == -1)
	{
		MessageBox(NULL, "\"image.png\"������܂���", NULL, MB_OK | MB_ICONWARNING);
		ExitGame();
		return;
	}
}


//----------------------------------------------------------------------
//! @brief �I�u�W�F�N�g�̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawObject(GameObject *object)
{
	int x, y;
	int u, v, w, h;
	HGRP handle;

	x = object->pos.x;
	y = object->pos.y;

	u = object->image.u;
	v = object->image.v;
	w = object->image.w;
	h = object->image.h;

	handle = object->image.handle;

	DrawRectGraph(x, y, u, v, w, h, handle, TRUE, FALSE);
}


//----------------------------------------------------------------------
//! @brief �w�i�̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void loadImage(void)
{
	g_mapImage = LoadGraph("Resources\\Images\\mapchip.png");
	CheckError(&g_mapImage);

	g_objectImage = LoadGraph("Resources\\Images\\pazuruImage.png");
	CheckError(&g_objectImage);

	g_uiImage = LoadGraph("Resources\\Images\\UI_Asset02.png");
	CheckError(&g_uiImage);

	g_backgroundImage = LoadGraph("Resources\\Images\\bg_image.png");
	CheckError(&g_backgroundImage);

	g_clearImage = LoadGraph("Resources\\Images\\clearImage.png");
	CheckError(&g_clearImage);

	g_ruleImage1 = LoadGraph("Resources\\Images\\rule1.png");
	CheckError(&g_ruleImage1);

	g_ruleImage2 = LoadGraph("Resources\\Images\\rule2.png");
	CheckError(&g_ruleImage2);

	g_ruleImage3 = LoadGraph("Resources\\Images\\rule3.png");
	CheckError(&g_ruleImage3);

	g_selectImage = LoadGraph("Resources\\Images\\stageSelectImage.png");
	CheckError(&g_selectImage);

	g_buttonImage = LoadGraph("Resources\\Images\\buttonImage.png");
	CheckError(&g_buttonImage);

	g_mouseEffectImage = LoadGraph("Resources\\Images\\mouseEffect.png");
	CheckError(&g_mouseEffectImage);

	g_eatEffectImageB = LoadGraph("Resources\\Images\\effect2.png");
	CheckError(&g_eatEffectImageB);

	g_eatEffectImageW = LoadGraph("Resources\\Images\\effect1.png");
	CheckError(&g_eatEffectImageW);
}


//----------------------------------------------------------------------
//! @brief �A�j���[�V�����̕`��̏���
//!
//! @param[in] Object
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawAnimation(GameObject *object)
{
	//��A�s�̌v�Z
	int colamn = object->anime.frameIndex % object->anime.numColumns;
	int row = object->anime.frameIndex / object->anime.numColumns;
	//�摜�̏��̌v�Z
	int imageU = object->image.u + (object->image.w * colamn);
	int imageV = object->image.v + (object->image.h * row);
	int imageW = object->image.w;
	int imageH = object->image.h;
	int imageHandle = object->image.handle;
	//��ʂł̈ʒu
	int ScreenX = object->pos.x;
	int ScreenY = object->pos.y;
	//�`�揈��
	DrawRectGraph(ScreenX, ScreenY, imageU, imageV, imageW, imageH, imageHandle, TRUE, FALSE);
}


//----------------------------------------------------------------------
//! @brief �}�E�X�G�t�F�N�g�̏���������
//!
//! @param[in] Object
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeMouseEffect(void)
{
	g_mouseEffect.image.u = 0;
	g_mouseEffect.image.v = 0;
	g_mouseEffect.image.w = 256;
	g_mouseEffect.image.h = 256;
	g_mouseEffect.image.handle = g_mouseEffectImage;

	g_mouseEffect.state = 0;

	g_mouseEffect.anime.numFrames = 30;
	g_mouseEffect.anime.numColumns = 5;
	g_mouseEffect.anime.frameDuration = 0;
	g_mouseEffect.anime.frameIndex = 0;
	g_mouseEffect.anime.elapsedCount = 0;
}


//----------------------------------------------------------------------
//! @brief �}�E�X�G�t�F�N�g�̍X�V����
//!
//! @param[in] Object
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateMouseEffect(void)
{
	int animeEnd = 0;

	if (((~g_mouse.LastInputState & g_mouse.CurrentInputState) & MOUSE_INPUT_LEFT) != 0)
	{
		
		g_mouseEffect.pos.x = g_mouse.Pos.x - (g_mouseEffect.image.w / 2);
		g_mouseEffect.pos.y = g_mouse.Pos.y - (g_mouseEffect.image.h / 2);
		g_mouseEffect.anime.frameIndex = 0;
		g_mouseEffect.state = 1;
	}

	if (g_mouseEffect.state == 1)
	{
		animeEnd = UpdateAnimetion(&g_mouseEffect);
		if(animeEnd == 1)
		{
			g_mouseEffect.state = 0;
		}
	}
}