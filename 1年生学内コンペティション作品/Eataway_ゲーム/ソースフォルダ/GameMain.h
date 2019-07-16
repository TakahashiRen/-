//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  ゲーム関連のヘッダファイル
//!
//! @date   日付
//!
//! @author 制作者名
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once



// 構造体の定義 ====================================================
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


// 定数の定義 ==============================================================

// ゲームタイトル
#define GAME_TITLE     "EatAway"


// 画面
#define SCREEN_WIDTH    (640)    // 画面の幅[pixel]
#define SCREEN_HEIGHT   (480)    // 画面の高さ[pixel]

#define SCREEN_TOP      (0)                    // 画面の上端
#define SCREEN_BOTTOM   (SCREEN_HEIGHT - 1)    // 画面の下端
#define SCREEN_LEFT     (0)                    // 画面の左端
#define SCREEN_RIGHT    (SCREEN_WIDTH - 1)     // 画面の右端

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // 画面の中央(X座標)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // 画面の中央(Y座標)

#define STAGE_NUMBER	(6)		//ステージ数

//シーンID
enum tag_SceneId
{
	SCENE_NONE,
	SCENE_LOGO,
	SCENE_TITLE,
	SCENE_SELECT,
	SCENE_PLAY
};
typedef enum tag_SceneId SceneId;
// グローバル変数の定義 ====================================================
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


// 関数の宣言 ==============================================================

// ゲームの初期化処理
void InitializeGame(void);

// ゲームの更新処理
void UpdateGame(void);

// ゲームの描画処理
void RenderGame(void);

// ゲームの終了処理
void FinalizeGame(void);

//シーンの切り替え処理
void ChangeScene(SceneId nextSceneId);

//アニメーションの更新処理
int UpdateAnimetion(GameObject *object);

//クリックされているか判定する処理
int CheckClickObject(GameObject *object);

//オブジェクトにマウスが重なっているか判定する処理
int CheckOverlapMouse(GameObject *object);

//エラー処理
void CheckError(HGRP *image);

//オブジェクトの描画処理
void DrawObject(GameObject *Object);

//アニメーションの描画処理
void DrawAnimation(GameObject *object);

