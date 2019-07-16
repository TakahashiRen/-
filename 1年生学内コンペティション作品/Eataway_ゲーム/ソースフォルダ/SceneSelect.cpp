//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneSelect.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   日付
//!
//! @author 制作者名
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include"SceneSelect.h"
#include"Button.h"
#include"Mouse.h"

// 定数の定義 ==============================================================


// グローバル変数の定義 ====================================================
GameObject g_titleBackground;
GameObject g_clearUi[10];

// 関数の宣言 ==============================================================
void UpdateClearUi(void);



// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
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
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateSelect(void)
{
	UpdateStageSelectButton();
	UpdateReturnTitleButton();
	UpdateStageSelectMigButton();
	UpdateClearUi();
}



//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!

//! @return なし
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
//! @brief ゲームの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeSelect(void)
{

}


//----------------------------------------------------------------------
//! @brief クリアUIの処理
//!
//! @param[in] なし
//!
//! @return なし
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