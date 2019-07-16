//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneLogo.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   日付
//!
//! @author 制作者名
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include"SceneLogo.h"



// グローバル変数の定義 ====================================================
//ロゴの表示時間の変数
int g_logoTimeCount;
//ロゴ画像の変数
HGRP g_logoImage;
//ロゴの変数
GameObject g_logo;


// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeLogo(void)
{
	g_logoImage = LoadGraph("Resources\\Images\\Game_Logo1.png");
	
	//ロゴの初期化
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
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
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
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!
//! @return なし
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
//! @brief ゲームの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeLogo(void)
{

}
