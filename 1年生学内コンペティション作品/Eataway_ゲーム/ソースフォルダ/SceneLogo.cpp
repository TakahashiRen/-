//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneLogo.cpp
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



// �O���[�o���ϐ��̒�` ====================================================
//���S�̕\�����Ԃ̕ϐ�
int g_logoTimeCount;
//���S�摜�̕ϐ�
HGRP g_logoImage;
//���S�̕ϐ�
GameObject g_logo;


// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeLogo(void)
{
	g_logoImage = LoadGraph("Resources\\Images\\Game_Logo1.png");
	
	//���S�̏�����
	g_logo.pos.x = SCREEN_CENTER_X - 325;
	g_logo.pos.y = SCREEN_CENTER_Y - 75;
	g_logo.image.u = 0;
	g_logo.image.v = 0;
	g_logo.image.w = 552;
	g_logo.image.h = 72;
	g_logo.image.handle = g_logoImage;
	g_logo.anime.numFrames = 19;
	g_logo.anime.numColumns = 1;
	g_logo.anime.frameDuration = 7;
	g_logo.anime.frameIndex = 0;
	g_logo.anime.elapsedCount = 0;

	g_logo.state = 1;

	g_logoTimeCount = 0;
}



//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateLogo(void)
{
	if (g_logo.state == 1)
	{
		g_logo.anime.elapsedCount++;
		if (g_logo.anime.elapsedCount > g_logo.anime.frameDuration)
		{
			g_logo.anime.frameIndex++;
			g_logo.anime.elapsedCount = 0;

			if (g_logo.anime.frameIndex >= g_logo.anime.numFrames)
			{
				g_logo.anime.frameIndex = g_logo.anime.numFrames;
			}
		}
	}
	g_logoTimeCount++;
	if (g_logoTimeCount >= 240)
	{
		ChangeScene(SCENE_TITLE);
	}
	
}



//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderLogo(void)
{

	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_WHITE, TRUE);

	if (g_logo.state == 1)
	{
		DrawAnimation(&g_logo);
	}
}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeLogo(void)
{

}
