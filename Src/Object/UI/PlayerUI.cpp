#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/DataBank.h"
#include "../../Manager/ScoreBank.h"
#include "../Character/Player.h"
#include "PlayerUI.h"

PlayerUI::PlayerUI()
{
	int i = -1;
	imgPlayerIcons_ = &i;
	imgNumbers_ = &i;
	imgPlayers_ = &i;
	imgLifeMes_ = -1;
	imgPowMes_ = -1;
	imgScoreMes_ = -1;
	imgLife_ = -1;
	imgPow_ = -1;
	imgWin_ = -1;
	imgDraw_ = -1;
	winState_ = WIN_STATE::NONE;
	for (int i = 0; i < SCORE_DIGIT; i++) { scoreDigits_[i] = -1; }
}

void PlayerUI::Load()
{
	auto & res = ResourceManager::GetInstance();

	//画像読み込み
	imgPlayerIcons_ = res.Load(ResourceManager::SRC::PLAYER_ICONS).handleIds_;
	imgLifeMes_ = res.Load(ResourceManager::SRC::LIFE_UI).handleId_;
	imgPowMes_ = res.Load(ResourceManager::SRC::POWER_UI).handleId_;
	imgScoreMes_ = res.Load(ResourceManager::SRC::SCORE_UI).handleId_;
	imgNumbers_ = res.Load(ResourceManager::SRC::NUMBER2).handleIds_;
	imgLife_ = res.Load(ResourceManager::SRC::LIFE).handleId_;
	imgPow_ = res.Load(ResourceManager::SRC::POWER).handleId_;
	imgPlayers_ = res.Load(ResourceManager::SRC::PLAYER_UI).handleIds_;
	imgWin_ = res.Load(ResourceManager::SRC::WIN_UI).handleId_;
	imgDraw_ = res.Load(ResourceManager::SRC::DRAW).handleId_;
}

void PlayerUI::Init()
{

	//モード別に関数を設定
	switch (DataBank::GetInstance().Output().mode_)
	{
	case SceneManager::MODE::MARASON:
		drawModeFunc_ = std::bind(&PlayerUI::DrawMarason, this);
		break;
	case SceneManager::MODE::VS:
		drawModeFunc_ = std::bind(&PlayerUI::DrawVS, this);
		break;
	default:
		break;
	}

	//スコア桁数字初期化
	for (int i = 0; i < SCORE_DIGIT; i++) { scoreDigits_[i] = 0; }

	//勝利状態初期化
	ChangeWinState(WIN_STATE::NONE);
}

void PlayerUI::Update()
{
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS)
	{
		//VSモードの場合は処理を行わない
		return;
	}
	//スコアの更新
	scoreDigits_[0] = ScoreBank::GetInstance().GetScore() / 10000;
	scoreDigits_[1] = (ScoreBank::GetInstance().GetScore() % 10000) / 1000;
	scoreDigits_[2] = (ScoreBank::GetInstance().GetScore() % 1000) / 100;
	scoreDigits_[3] = (ScoreBank::GetInstance().GetScore() % 100) / 10;
	scoreDigits_[4] = ScoreBank::GetInstance().GetScore() % 10;
}

void PlayerUI::Draw(const Player& player)
{
	//アイコン
	//体力メッセージ
	//体力
	//パワーメッセージ
	//パワー

	DrawGraph(
		ICON_POS_X,
		ICON_POS_Y,
		imgPlayerIcons_[SceneManager::GetInstance().GetScreenCount()],
		true);
	DrawGraph(
		LIFE_UI_X,
		LIFE_UI_Y,
		imgLifeMes_,
		true);

	for (int i = 0; i < player.GetLife(); i++)
	{
		DrawGraph(
			LIFE_X + 35 * i,
			LIFE_Y,
			imgLife_,
			true);
	}

	DrawGraph(
		POWER_UI_X,
		POWER_UI_Y,
		imgPowMes_,
		true);

	for (int i = 0; i < player.GetPower(); i++)
	{
		DrawGraph(
			POWER_X + 35 * i,
			POWER_Y,
			imgPow_,
			true);
	}

	//モード別に描画
	drawModeFunc_();
}

void PlayerUI::Release()
{
}

void PlayerUI::ChangeWinState(const WIN_STATE& state)
{
	winState_ = state;

	//勝利状態によって描画関数を変更
	switch (winState_)
	{
	case WIN_STATE::NONE:
		drawWinFunc_ = std::bind(&PlayerUI::DrawNone, this);
		break;
	case WIN_STATE::P1_WIN:
		drawWinFunc_ = std::bind(&PlayerUI::DrawP1Win, this);
		break;
	case WIN_STATE::P2_WIN:
		drawWinFunc_ = std::bind(&PlayerUI::DrawP2Win, this);
		break;
	case WIN_STATE::DRAW:
		drawWinFunc_ = std::bind(&PlayerUI::DrawDraw, this);
		break;
	default:
		drawWinFunc_ = std::bind(&PlayerUI::DrawNone, this);
		break;
	}
}

void PlayerUI::VSClearDraw()
{
	//VSモードでのみ勝利状態を描画
	drawWinFunc_();
}

void PlayerUI::DrawMarason()
{
	//マラソンでのみスコアを描画		
	DrawGraph(
		SCORE_UI_X,
		SCORE_UI_Y,
		imgScoreMes_,
		true);

	//スコア描画
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		DrawRotaGraph(
			SCORE_UI_X + 120 + 35 * i,
			SCORE_UI_Y + 10,
			1.0f,
			0.0f,
			imgNumbers_[scoreDigits_[i]],
			true);
	}
}

void PlayerUI::DrawVS()
{
}

void PlayerUI::DrawNone()
{
	//何もしないお
}

void PlayerUI::DrawP1Win()
{
	DrawRotaGraph(
		Application::SCREEN_HALF_X,
		Application::SCREEN_HALF_Y - 64,
		1.0f,
		0.0f,
		imgPlayers_[0],
		true);

	DrawRotaGraph(
		Application::SCREEN_HALF_X,
		Application::SCREEN_HALF_Y + 64,
		1.0f,
		0.0f,
		imgWin_,
		true);
}

void PlayerUI::DrawP2Win()
{
	DrawRotaGraph(
		Application::SCREEN_HALF_X,
		Application::SCREEN_HALF_Y - 64,
		1.0f,
		0.0f,
		imgPlayers_[1],
		true);

	DrawRotaGraph(
		Application::SCREEN_HALF_X,
		Application::SCREEN_HALF_Y + 64,
		1.0f,
		0.0f,
		imgWin_,
		true);
}

void PlayerUI::DrawDraw()
{
	DrawRotaGraph(
		Application::SCREEN_HALF_X,
		Application::SCREEN_HALF_Y,
		1.0f,
		0.0f,
		imgDraw_,
		true);
}
