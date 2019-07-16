//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneTitle.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   日付
//!
//! @author 制作者名
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include"SceneTitle.h"
#include"Button.h"
#include"Mouse.h"


// 定数の定義 ==============================================================
#define GRID_HEIGHT (30)
#define GRID_WIDTH	(40)
#define GRID_SIZE_X (16)
#define GRID_SIZE_Y (16)


// グローバル変数の定義 ====================================================
int g_gridData[GRID_HEIGHT][GRID_WIDTH];
int g_gridDataOrigin[GRID_HEIGHT][GRID_WIDTH];
int g_gridEffect[GRID_HEIGHT][GRID_WIDTH];
GameObject g_ruleObject[3];

int g_timeCount;
// 関数の宣言 ==============================================================
void UpdateStartEffect(void);



// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeTitle(void)
{
	int i, j;

	FILE *fp = NULL;

	char buffer[256];

	char *p = NULL;

	long number;

	fp = fopen("Resources\\Data\\title.csv", "r");
	if (fp == NULL)
	{
		MessageBox(NULL, "\"title.csv\"がありません", NULL, MB_OK);
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
	fclose(fp);

	for (i = 0; i < GRID_HEIGHT; i++)
	{
		for (j = 0; j < GRID_WIDTH; j++)
		{
			g_gridEffect[i][j] = -1;
		}
	}


	InitializeStartButton(50, 300);
	InitializeRuleButton(250, 300);
	InitializeEndButton(450, 300);

	for (i = 0; i < 3; i++)
	{
		g_ruleObject[i].pos.x = 0;
		g_ruleObject[i].pos.y = 0;
		g_ruleObject[i].image.u = 0;
		g_ruleObject[i].image.v = 0;
		g_ruleObject[i].image.w = 640;
		g_ruleObject[i].image.h = 480;

		g_ruleObject[i].state = 0;
	}
	g_ruleObject[0].image.handle = g_ruleImage1;
	g_ruleObject[1].image.handle = g_ruleImage2;
	g_ruleObject[2].image.handle = g_ruleImage3;

	g_imageCount = -1;
	g_ruleFlag = 0;
	g_timeCount = 0;
}



//----------------------------------------------------------------------
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateTitle(void)
{
	static int gridX = 0, gridY = 0;
	static int lastGridX = 0, lastGridY = 0;
	static int ruleCount = 0;

	if (g_ruleFlag != 1)
	{
		if (g_startFlag != 1)
		{
			UpdateStartButton();
			UpdateRuleButton();
			UpdateEndButton();
		}
		else
		{
			if (g_timeCount >= 2)
			{
				UpdateStartEffect();
				g_timeCount = 0;
			}
		}
	}

	gridX = g_mouse.Pos.x / 16;
	gridY = g_mouse.Pos.y / 16;

	if (gridX < 0)
	{
		gridX = 0;
	}
	else if (gridX > 39)
	{
		gridX = 39;
	}

	if (gridY < 0)
	{
		gridY = 0;
	}
	else if (gridY > 29)
	{
		gridY = 29;
	}

	if (gridX != lastGridX || gridY != lastGridY)
	{
		g_gridData[lastGridY][lastGridX] = g_gridDataOrigin[lastGridY][lastGridX];
		if (g_gridData[gridY][gridX] == 6)
		{
			g_gridData[gridY][gridX] = 7;
		}
		else if (g_gridData[gridY][gridX] == 7)
		{
			g_gridData[gridY][gridX] = 6;
		}
	}

	lastGridX = gridX;
	lastGridY = gridY;

	if (g_ruleFlag == 1)
	{
		if (g_imageCount >= 0 && g_imageCount <= 2 && ruleCount >= 10)
		{
			if (((~g_mouse.LastInputState & g_mouse.CurrentInputState) & MOUSE_INPUT_LEFT) != 0)
			{
				g_ruleObject[g_imageCount].state = 0;
				g_imageCount++;
			}
		}

		if (g_imageCount >= 0 && g_imageCount <= 2)
		{
			g_ruleObject[g_imageCount].state = 1;
		}
		else
		{
			g_ruleFlag = 0;
		}
		ruleCount++;
	}
	g_timeCount++;
}



//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderTitle(void)
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

			u = (g_gridData[i][j] % 8) * GRID_SIZE_X;
			v = (g_gridData[i][j] / 8) * GRID_SIZE_Y;

			DrawRectGraph(x, y, u, v, GRID_SIZE_X, GRID_SIZE_Y, g_mapImage, TRUE, FALSE);
		}
	}

	DrawObject(&g_startButton);

	DrawObject(&g_ruleButton);

	DrawObject(&g_endButton);

	for (i = 0; i < 3; i++)
	{
		if (g_ruleObject[i].state == 1)
		{
			DrawObject(&g_ruleObject[i]);
		}
	}

	if (g_startFlag == 1)
	{
		for (i = 0; i < GRID_HEIGHT; i++)
		{
			for (j = 0; j < GRID_WIDTH; j++)
			{
				if (g_gridEffect[i][j] != -1)
				{
					x = j * GRID_SIZE_X;
					y = i * GRID_SIZE_Y;

					u = (g_gridEffect[i][j] % 8) * GRID_SIZE_X;
					v = (g_gridEffect[i][j] / 8) * GRID_SIZE_Y;

					DrawRectGraph(x, y, u, v, GRID_SIZE_X, GRID_SIZE_Y, g_mapImage, TRUE, FALSE);
				}
			}
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
void FinalizeTitle(void)
{

}


//----------------------------------------------------------------------
//! @brief スタートの演出処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateStartEffect(void)
{
	static int count[GRID_HEIGHT] = { 0 };

	int i;
	int k;

	
	for (i = 0; i < GRID_HEIGHT; i++)
	{
		k = count[i] - 0 - i;

		if (k >= 0)
		{
			g_gridEffect[i][k] = 7;
		}
	}

	if (g_gridEffect[GRID_HEIGHT][GRID_WIDTH] == 7)
	{
		ChangeScene(SCENE_SELECT);
	}
	for (i = 0; i < GRID_HEIGHT; i++)
	{
		count[i]++;
	}
}