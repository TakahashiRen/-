//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SelectButton.h
//!
//! @brief  ゲーム関連のヘッダファイル
//!
//! @date   日付
//!
//! @author 制作者名
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once




// 定数の定義 ==============================================================


// グローバル変数の定義 ====================================================
extern GameObject g_selectButtonY;
extern GameObject g_selectButtonN;
extern GameObject g_startButton;
extern GameObject g_ruleButton;
extern GameObject g_returnButton;
extern GameObject g_stageSelectButton[10];
extern GameObject g_endButton;
extern GameObject g_returnTitleButton;
extern GameObject g_selectButtonR;
extern GameObject g_selectButtonL;
extern GameObject g_returnSelectButtonP;


extern int g_resetFlag;
extern int g_imageCount;
extern int g_ruleFlag;
extern int g_startFlag;
extern int g_lastSoundFlag;
extern int g_currentSoundFlag;

// 関数の宣言 ==============================================================
void InitializeButton(GameObject *button, int posX, int posY);

void InitializeButtonImage(void);

void InitializeRuleButton(int posX, int posY);

void InitializeStartButton(int posX, int posY);

void InitializeStageSelectButton(void);

void InitializeReturnObject(void);

void InitializeSelectButton(void);

void InitializeEndButton(int posX, int posY);

void InitializeReturnTitleButton(void);

void InitializeStageSelectMigButton(void);

void InitializeReturnSelectP(void);

int UpdateButton(GameObject *button, int *soundFlag);

int UpdateSelectButton(void);

void UpdateStageSelectButton(void);

void UpdateReturnObject(void);

void UpdateRuleButton(void);

void UpdateStartButton(void);

void UpdateEndButton(void);

void UpdateReturnTitleButton(void);

void UpdateStageSelectMigButton(void);

void UpdateReturnSelectP(void);
