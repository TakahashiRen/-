//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Button.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   ���t
//!
//! @author ����Җ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "Mouse.h"
#include "Button.h"
#include<math.h>

// �֐��̐錾 ==============================================================


// �O���[�o���ϐ��̒�` ====================================================
GameObject g_selectButtonY;
GameObject g_selectButtonN;
GameObject g_startButton;
GameObject g_ruleButton;
GameObject g_stageSelectButton[10];
GameObject g_returnButton;
GameObject g_endButton;
GameObject g_returnTitleButton;
GameObject g_selectButtonR;
GameObject g_selectButtonL;
GameObject g_returnSelectButtonP;

int g_resetFlag;
int g_ruleFlag;
int g_startFlag;
int g_imageCount;
int g_currentSoundFlag;
int g_lastSoundFlag;

// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �{�^���̉摜�̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeButtonImage(void)
{
	int i;

	g_startButton.image.u = 0;
	g_startButton.image.v = 192;
	g_startButton.image.w = 128;
	g_startButton.image.h = 64;
	g_startButton.image.handle = g_buttonImage;

	g_ruleButton.image.u = 0;
	g_ruleButton.image.v = 352;
	g_ruleButton.image.w = 128;
	g_ruleButton.image.h = 64;
	g_ruleButton.image.handle = g_buttonImage;

	for (i = 0; i < 10; i++)
	{
		g_stageSelectButton[i].image.u = 0;
		g_stageSelectButton[i].image.v = 0 + (i * 180);
		g_stageSelectButton[i].image.w = 124;
		g_stageSelectButton[i].image.h = 180;
		g_stageSelectButton[i].image.handle = g_selectImage;
	}

	g_selectButtonY.image.u = 0;
	g_selectButtonY.image.v = 64;
	g_selectButtonY.image.w = 128;
	g_selectButtonY.image.h = 64;
	g_selectButtonY.image.handle = g_buttonImage;


	g_selectButtonN.image.u = 0;
	g_selectButtonN.image.v = 128;
	g_selectButtonN.image.w = 128;
	g_selectButtonN.image.h = 64;
	g_selectButtonN.image.handle = g_buttonImage;

	g_returnButton.image.u = 0;
	g_returnButton.image.v = 0;
	g_returnButton.image.w = 128;
	g_returnButton.image.h = 64;
	g_returnButton.image.handle = g_buttonImage;

	g_endButton.image.u = 0;
	g_endButton.image.v = 416;
	g_endButton.image.w = 128;
	g_endButton.image.h = 64;
	g_endButton.image.handle = g_buttonImage;

	g_returnTitleButton.image.u = 0;
	g_returnTitleButton.image.v = 576;
	g_returnTitleButton.image.w = 64;
	g_returnTitleButton.image.h = 64;
	g_returnTitleButton.image.handle = g_buttonImage;

	g_selectButtonR.image.u = 0;
	g_selectButtonR.image.v = 640;
	g_selectButtonR.image.w = 64;
	g_selectButtonR.image.h = 64;
	g_selectButtonR.image.handle = g_buttonImage;

	g_selectButtonL.image.u = 0;
	g_selectButtonL.image.v = 704;
	g_selectButtonL.image.w = 64;
	g_selectButtonL.image.h = 64;
	g_selectButtonL.image.handle = g_buttonImage;

	g_returnSelectButtonP.image.u = 0;
	g_returnSelectButtonP.image.v = 768;
	g_returnSelectButtonP.image.w = 128;
	g_returnSelectButtonP.image.h = 64;
	g_returnSelectButtonP.image.handle = g_buttonImage;
}


//----------------------------------------------------------------------
//! @brief �{�^���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeButton(GameObject *button,int posX,int posY)
{
	button->pos.x = posX;
	button->pos.y = posY;

	g_currentSoundFlag = 0;
	g_lastSoundFlag = 0;
	button->state = 1;
}


//----------------------------------------------------------------------
//! @brief �X�^�[�g�{�^���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeStartButton(int posX,int posY)
{
	InitializeButton(&g_startButton, posX, posY);
	g_startFlag = 0;
}


//----------------------------------------------------------------------
//! @brief ���[���{�^���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeRuleButton(int posX,int posY)
{
	InitializeButton(&g_ruleButton, posX, posY);
}


//----------------------------------------------------------------------
//! @brief �X�e�[�W�Z���N�g�{�^���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeStageSelectButton(void)
{
	g_stageSelectButton[0].pos = { 20,20 };
	g_stageSelectButton[1].pos = { 260,20 };
	g_stageSelectButton[2].pos = { 500,20 };
	g_stageSelectButton[3].pos = { 140,250 };
	g_stageSelectButton[4].pos = { 380,250 };

	g_stageSelectButton[5].pos = { 20,20 };
	g_stageSelectButton[6].pos = { 260,20 };
	g_stageSelectButton[7].pos = { 500,20 };
	g_stageSelectButton[8].pos = { 140,250 };
	g_stageSelectButton[9].pos = { 380,250 };


	g_stageSelectButton[0].state = 1;
	g_stageSelectButton[1].state = 1;
	g_stageSelectButton[2].state = 1;
	g_stageSelectButton[3].state = 1;
	g_stageSelectButton[4].state = 1;

	g_stageSelectButton[5].state = 0;
	g_stageSelectButton[6].state = 0;
	g_stageSelectButton[7].state = 0;
	g_stageSelectButton[8].state = 0;
	g_stageSelectButton[9].state = 0;

}


//----------------------------------------------------------------------
//! @brief �I���{�^���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeSelectButton(void)
{
	g_selectButtonY.pos.x = 64;
	g_selectButtonY.pos.y = 300;
	g_selectButtonY.state = 0;

	g_selectButtonN.pos.x = 288;
	g_selectButtonN.pos.y = 300;
	g_selectButtonN.state = 0;
}


//----------------------------------------------------------------------
//! @brief ��蒼���{�^���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeReturnObject(void)
{
	g_returnButton.pos.x = 500;
	g_returnButton.pos.y = 400;

	g_returnButton.state = 1;
}


//----------------------------------------------------------------------
//! @brief �I���{�^���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeEndButton(int posX,int posY)
{
	InitializeButton(&g_endButton, posX, posY);
}


//----------------------------------------------------------------------
//! @brief �^�C�g���ɖ߂�{�^���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeReturnTitleButton(void)
{
	g_returnTitleButton.pos = {0,SCREEN_BOTTOM - 64};
	g_returnTitleButton.state = 1;
}


//----------------------------------------------------------------------
//! @brief �X�e�[�W�I���ڍs�{�^���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeStageSelectMigButton(void)
{
	g_selectButtonR.pos = {SCREEN_RIGHT - 64,SCREEN_CENTER_Y - 25};
	g_selectButtonR.state = 1;

	g_selectButtonL.pos = { 0,SCREEN_CENTER_Y - 25};
	g_selectButtonL.state = 0;

}



//----------------------------------------------------------------------
//! @brief �X�e�[�W�I����ʂɖ߂�{�^���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeReturnSelectP(void)
{
	g_returnSelectButtonP.pos = {500,320};
	g_returnSelectButtonP.state = 1;
}


//----------------------------------------------------------------------
//! @brief �{�^���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
int UpdateButton(GameObject *button,int *soundFlag)
{
	int mouseClicked = 0;
	int mouseOverlaped = 0;
	int imageX;

	imageX = button->image.u;

	if (button->state == 1)
	{
		mouseOverlaped = CheckOverlapMouse(button);
		mouseClicked = CheckClickObject(button);

		if (mouseOverlaped == 1)
		{
			if (imageX == 0)
			{
				button->image.u += button->image.w;
			}

			if (*soundFlag == 0)
			{
				PlaySoundMem(g_effectSound1, DX_PLAYTYPE_BACK, TRUE);
				*soundFlag = 1;
			}

			if (mouseClicked == 1)
			{
				return 2;
			}
		}
		else 
		{
			button->image.u = 0;
			*soundFlag = 0;
		}
	}
	return 0;
}


//----------------------------------------------------------------------
//! @brief �X�e�[�W�Z���N�g�{�^���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateStageSelectButton(void)
{
	int i;
	int updateResult = 0;
	static int soundFlag[10] = { 0 };

	for (i = 0; i < 10; i++)
	{
		if (g_stageSelectButton[i].state == 1)
		{
			updateResult = UpdateButton(&g_stageSelectButton[i], &soundFlag[i]);

			if (updateResult == 2)
			{
				g_stageNumber = i + 1;
				ChangeScene(SCENE_PLAY);
			}
		}
	}
}


//----------------------------------------------------------------------
//! @brief ��蒼���{�^���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateReturnObject(void)
{
	int updateResult = 0;
	int resetFlag = 0;
	static int soundFlag = 0;

	updateResult = UpdateButton(&g_returnButton,&soundFlag);
	if (updateResult == 2)
	{
		g_selectButtonY.state = 1;
		g_selectButtonN.state = 1;
	}

	//�I���{�^���̍X�V����
	g_resetFlag = UpdateSelectButton();
}



//----------------------------------------------------------------------
//! @brief ���[���{�^���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateRuleButton(void)
{
	int updateResult = 0;
	static int soundFlag = 0;

	updateResult = UpdateButton(&g_ruleButton,&soundFlag);

	if (updateResult == 2)
	{
		g_imageCount = 0;
		g_ruleFlag = 1;
	}
}


//----------------------------------------------------------------------
//! @brief �X�^�[�g�{�^���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateStartButton(void)
{
	int updateResult = 0;
	static int soundFlag = 0;

	updateResult = UpdateButton(&g_startButton,&soundFlag);

	if (updateResult == 2)
	{
		g_startFlag = 1;
		//ChangeScene(SCENE_SELECT);
	}
}


//----------------------------------------------------------------------
//! @brief �G���h�{�^���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateEndButton(void)
{
	int updateResult = 0;
	static int soundFlag = 0;

	updateResult = UpdateButton(&g_endButton, &soundFlag);

	if (updateResult == 2)
	{
		ExitGame();
	}
}


//----------------------------------------------------------------------
//! @brief �^�C�g���ɖ߂�{�^���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateReturnTitleButton(void)
{
	int updateResult = 0;
	static int soundFlag = 0;

	updateResult = UpdateButton(&g_returnTitleButton, &soundFlag);

	if (updateResult == 2)
	{
		ChangeScene(SCENE_TITLE);
	}
}

//----------------------------------------------------------------------
//! @brief �I���{�^���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
int UpdateSelectButton(void)
{
	int updateResult = 0;
	static int soundFlag[2] = {0};
	updateResult = UpdateButton(&g_selectButtonY,&soundFlag[0]);

	if (updateResult == 2)
	{
		g_selectButtonY.state = 0;
		g_selectButtonN.state = 0;
		return 1;
	}

	updateResult = UpdateButton(&g_selectButtonN,&soundFlag[1]);
	if (updateResult == 2)
	{
		g_selectButtonY.state = 0;
		g_selectButtonN.state = 0;
		return 2;
	}
	return 0;
}



//----------------------------------------------------------------------
//! @brief �X�e�[�W�I����ʂɈڍs�{�^���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateStageSelectMigButton(void)
{
	int updateResult = 0;
	static int soundFlag[2] = { 0 };

	if (g_selectButtonR.state == 1)
	{
		updateResult = UpdateButton(&g_selectButtonR,&soundFlag[0]);
		if (updateResult == 2)
		{
			g_stageSelectButton[0].state = 0;
			g_stageSelectButton[1].state = 0;
			g_stageSelectButton[2].state = 0;
			g_stageSelectButton[3].state = 0;
			g_stageSelectButton[4].state = 0;

			g_stageSelectButton[5].state = 1;
			g_stageSelectButton[6].state = 1;
			g_stageSelectButton[7].state = 1;
			g_stageSelectButton[8].state = 1;
			g_stageSelectButton[9].state = 1;
			
			g_selectButtonR.state = 0;
			g_selectButtonL.state = 1;
		}
	}

	if (g_selectButtonL.state == 1)
	{
		updateResult = UpdateButton(&g_selectButtonL, &soundFlag[1]);
		if (updateResult == 2)
		{
			g_stageSelectButton[0].state = 1;
			g_stageSelectButton[1].state = 1;
			g_stageSelectButton[2].state = 1;
			g_stageSelectButton[3].state = 1;
			g_stageSelectButton[4].state = 1;

			g_stageSelectButton[5].state = 0;
			g_stageSelectButton[6].state = 0;
			g_stageSelectButton[7].state = 0;
			g_stageSelectButton[8].state = 0;
			g_stageSelectButton[9].state = 0;

			g_selectButtonR.state = 1;
			g_selectButtonL.state = 0;
		}
	}
}


//----------------------------------------------------------------------
//! @brief �X�e�[�W�I����ʂɖ߂�{�^���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateReturnSelectP(void)
{
	int updateResult = 0;
	int returnFlag = 0;
	static int soundFlag = 0;

	updateResult = UpdateButton(&g_returnSelectButtonP, &soundFlag);
	if (updateResult == 2)
	{
		ChangeScene(SCENE_SELECT);
	}
}