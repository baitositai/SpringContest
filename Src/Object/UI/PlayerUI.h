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

	//スコア座標位置
	static constexpr int SCORE_UI_X = Application::SCREEN_SIZE_X - 320;
	static constexpr int SCORE_UI_Y = 100;

	//スコア桁数
	static constexpr int SCORE_DIGIT = 5;

	PlayerUI();
	~PlayerUI() = default;

	void Load();
	void Init();
	void Update();
	void Draw(const Player & player);
	void Release();

	//勝利状態変更
	void ChangeWinState(const WIN_STATE& state);

	//クリア状態の描画
	void VSClearDraw();

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
	int* imgPlayers_;	//プレイヤー

	//数字
	int *imgNumbers_;

	//スコア
	int scoreDigits_[SCORE_DIGIT];

	//モード別描画
	std::function<void(void)> drawModeFunc_;

	//勝利状態別描画
	std::function<void(void)> drawWinFunc_;

	//モード別描画
	void DrawMarason();
	void DrawVS();

	//勝利状態別描画
	void DrawNone();
	void DrawP1Win();
	void DrawP2Win();
	void DrawDraw();
};

