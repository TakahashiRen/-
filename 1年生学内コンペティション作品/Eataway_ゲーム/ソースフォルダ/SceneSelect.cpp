//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneSelect.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   ���t
//!
//! @author ����Җ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include"SceneSelect.h"
#include"Button.h"
#include"Mouse.h"

// �萔�̒�` ==============================================================


// �O���[�o���ϐ��̒�` ====================================================
GameObject g_titleBackground;
GameObject g_clearUi[10];

// �֐��̐錾 ==============================================================
void UpdateClearUi(void);



// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeSelect(void)
{
	int i;

	InitializeStageSelectButton();
	InitializeReturnTitleButton();
	InitializeStageSelectMigButton();

	g_titleBackground.pos = { 0,0 };
	g_titleBackground.image.u = 0;
	g_titleBackground.image.v = 0;
	g_titleBackground.image.w = 640;
	g_titleBackground.image.h = 480;
	g_titleBackground.image.handle = g_backgroundImage;

	for (i = 0; i < 10; i++)
	{
		g_clearUi[i].image.u = 64;
		g_clearUi[i].image.v = 0;
		g_clearUi[i].image.w = 96;
		g_clearUi[i].image.h = 64;
		g_clearUi[i].image.handle = g_uiImage;

		g_clearUi[i].state = 0;
	}
}



//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateSelect(void)
{
	UpdateStageSelectButton();
	UpdateReturnTitleButton();
	UpdateStageSelectMigButton();
	UpdateClearUi();
}



//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!

//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderSelect(void)
{
	int i;

	DrawObject(&g_titleBackground);

	for (i = 0; i < 10; i++)
	{
		if (g_stageSelectButton[i].state == 1)
		{
			DrawObject(&g_stageSelectButton[i]);
		}
	}
	DrawObject(&g_returnTitleButton);

	if (g_selectButtonR.state == 1)
	{
		DrawObject(&g_selectButtonR);
	}
	if (g_selectButtonL.state == 1)
	{
		DrawObject(&g_selectButtonL);
	}

	for (i = 0; i < 10; i++)
	{
		if (g_clearUi[i].state == 1)
		{
			DrawObject(&g_clearUi[i]);
		}
	}

}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeSelect(void)
{

}


//----------------------------------------------------------------------
//! @brief �N���AUI�̏���
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateClearUi(void)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		g_clearUi[i].state = (g_clearStageFlag[i] & g_stageSelectButton[i].state);
		if (g_clearUi[i].state == 1)
		{
			g_clearUi[i].pos.x = g_stageSelectButton[i].pos.x + 16;
			g_clearUi[i].pos.y = g_stageSelectButton[i].pos.y + 96;
		}
	}
}