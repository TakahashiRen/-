//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ScenePlay.h
//!
//! @brief  �Q�[���֘A�̃w�b�_�t�@�C��
//!
//! @date   ���t
//!
//! @author ����Җ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once




// �萔�̒�` ==============================================================
struct tag_UI
{
	float posX;
	float posY;
	float velX;
	float velY;
	int state;
	Image image;
};
typedef struct tag_UI UI;


// �֐��̐錾 ==============================================================

// �Q�[���̏���������
void InitializePlay(void);

// �Q�[���̍X�V����
void UpdatePlay(void);

// �Q�[���̕`�揈��
void RenderPlay(void);

// �Q�[���̏I������
void FinalizePlay(void);

