#pragma once
#include "../../framework.h"
#include "../../Application.h"

class Player;

class PlayerUI
{
public:

	//勝利状態
	enum class WIN_STATE
	{
		NONE,
		P1_WIN,
		P2_WIN,
		DRAW
	};

	//アイコン座標位置
	static constexpr int ICON_POS_X = 0;
	static constexpr int ICON_POS_Y = 0;

	//操作説明位置
	static constexpr int EXPLAN_POS_X = 0;
	static constexpr int EXPLAN_POS_Y = 128;

	//ライフUI座標位置
	static constexpr int LIFE_UI_X = 128;
	static constexpr int LIFE_UI_Y = 0;

	//ライフ座標位置
	static constexpr int LIFE_X = 128;
	static constexpr int LIFE_Y = 32;

	//パワーUI座標位置
	static constexpr int POWER_UI_X = 128;
	static constexpr int POWER_UI_Y = 64;

	//パワー座標位置
	static constexpr int POWER_X = 128;
	static constexpr int POWER_Y = 96;

	//スコア背景座標位置
	static constexpr int SCORE_UI_X = Application::SCREEN_SIZE_X - 320;
	static constexpr int SCORE_UI_Y = 100;

	static constexpr int REZALT_SCORE_UI_X = Application::SCREEN_HALF_X - 160;
	static constexpr int REZALT_SCORE_UI_Y = Application::SCREEN_HALF_Y - 40;

	//スコア桁数
	static constexpr int SCORE_DIGIT = 5;

	//タックルゲージ長さ
	static constexpr int GAGE_SIZE_X = 128;
	static constexpr int GAGE_SIZE_Y = 50;

	//クリア者UI位置
	static constexpr int CLEAR_PLAYER_POS_Y = Application::SCREEN_HALF_Y - 64;

	//クリアメッセUI位置
	static constexpr int CLEAR_MES_POS_Y = Application::SCREEN_HALF_Y + 64;

	//スコアの座標位置
	static constexpr int RESULT_SCORE_INTERVAL = 35;
	static constexpr int SCORE_UI_POS_X = SCORE_UI_X + 120;
	static constexpr int SCORE_UI_POS_Y = SCORE_UI_Y + 10;
	static constexpr int RESULT_SCORE_POS_X = REZALT_SCORE_UI_X + 120;
	static constexpr int RESULT_SCORE_POS_Y = REZALT_SCORE_UI_Y + 10;

	//UI描画用オフセット
	static constexpr int UI_OFFSET = 35;
	
	PlayerUI();
	~PlayerUI() = default;

	void Load();
	void Init();
	void Update();
	void Draw(const Player & player);

	//勝利状態変更
	void ChangeWinState(const WIN_STATE& state);

	//クリア状態の描画
	void ResultDraw();

private:

	//勝利状態
	WIN_STATE winState_;

	//アイコン画像
	int *imgPlayerIcons_;

	//メッセージ画像
	int imgLife_;		//体力
	int imgPow_;		//パワー
	int imgLifeMes_;	//体力UI
	int imgPowMes_;		//パワーUI
	int imgScoreMes_;	//スコア
	int imgWin_;		//勝利
	int imgDraw_;		//引き分け
	int imgTackleGage_;	//タックルゲージ
	int* imgPlayers_;	//プレイヤー
	int* imgExplan_;	//操作説明

	//数字
	int *imgNumbers_;

	//スコア
	int scoreDigits_[SCORE_DIGIT];

	//モード別描画
	std::function<void()> drawModeFunc_;

	//リザルト画面
	std::function<void()> drawResultFunc_;

	//勝利状態別描画
	std::function<void()> drawWinFunc_;

	//モード別描画
	void DrawMarathon();
	void DrawVS();

	//勝利状態別描画
	void DrawNone();
	void DrawP1Win();
	void DrawP2Win();
	void DrawDraw();

	//マラソンリザルト描画
	void DrawResultScore();

	//クリアUIの描画
	void VSClearDraw();
};

