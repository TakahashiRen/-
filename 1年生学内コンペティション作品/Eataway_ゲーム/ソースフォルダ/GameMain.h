//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  �Q�[���֘A�̃w�b�_�t�@�C��
//!
//! @date   ���t
//!
//! @author ����Җ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once



// �\���̂̒�` ====================================================
struct tag_Vec2D
{
	int x;
	int y;
};
typedef struct tag_Vec2D Vec2D;

struct tag_Image
{
	int u;
	int v;
	int w;
	int h;
	HGRP handle;
};
typedef struct tag_Image Image;

struct tag_Anime
{
	int numFrames;
	int numColumns;
	int frameDuration;
	int frameIndex;
	int elapsedCount;
};
typedef struct tag_Anime Anime;

struct tag_GameObject
{
	Vec2D pos;
	Vec2D vel;
	int type;
	int state;
	int collisionR;
	Image image;
	Anime anime;
};
typedef struct tag_GameObject GameObject;


// �萔�̒�` ==============================================================

// �Q�[���^�C�g��
#define GAME_TITLE     "EatAway"


// ���
#define SCREEN_WIDTH    (640)    // ��ʂ̕�[pixel]
#define SCREEN_HEIGHT   (480)    // ��ʂ̍���[pixel]

#define SCREEN_TOP      (0)                    // ��ʂ̏�[
#define SCREEN_BOTTOM   (SCREEN_HEIGHT - 1)    // ��ʂ̉��[
#define SCREEN_LEFT     (0)                    // ��ʂ̍��[
#define SCREEN_RIGHT    (SCREEN_WIDTH - 1)     // ��ʂ̉E�[

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // ��ʂ̒���(X���W)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // ��ʂ̒���(Y���W)

#define STAGE_NUMBER	(6)		//�X�e�[�W��

//�V�[��ID
enum tag_SceneId
{
	SCENE_NONE,
	SCENE_LOGO,
	SCENE_TITLE,
	SCENE_SELECT,
	SCENE_PLAY
};
typedef enum tag_SceneId SceneId;
// �O���[�o���ϐ��̒�` ====================================================
extern SceneId g_currentSceneId;
extern SceneId g_nextSceneId;
extern int g_sceneState;

extern int g_currentInputState;
extern int g_lastInputState;

extern int g_clearFlag;
extern int g_clearStageFlag[10];
extern int g_stageNumber;

extern HGRP g_uiImage;
extern HGRP g_mapImage;
extern HGRP g_objectImage;
extern HGRP g_uiImage;
extern HGRP g_backgroundImage;
extern HGRP g_clearImage;
extern HGRP g_ruleImage1;
extern HGRP g_ruleImage2;
extern HGRP g_ruleImage3;
extern HGRP g_selectImage;
extern HGRP g_buttonImage;
extern HGRP g_eatEffectImageB;
extern HGRP g_eatEffectImageW;

extern HSND g_effectSound1;
extern HSND g_effectSound2;


// �֐��̐錾 ==============================================================

// �Q�[���̏���������
void InitializeGame(void);

// �Q�[���̍X�V����
void UpdateGame(void);

// �Q�[���̕`�揈��
void RenderGame(void);

// �Q�[���̏I������
void FinalizeGame(void);

//�V�[���̐؂�ւ�����
void ChangeScene(SceneId nextSceneId);

//�A�j���[�V�����̍X�V����
int UpdateAnimetion(GameObject *object);

//�N���b�N����Ă��邩���肷�鏈��
int CheckClickObject(GameObject *object);

//�I�u�W�F�N�g�Ƀ}�E�X���d�Ȃ��Ă��邩���肷�鏈��
int CheckOverlapMouse(GameObject *object);

//�G���[����
void CheckError(HGRP *image);

//�I�u�W�F�N�g�̕`�揈��
void DrawObject(GameObject *Object);

//�A�j���[�V�����̕`�揈��
void DrawAnimation(GameObject *object);

