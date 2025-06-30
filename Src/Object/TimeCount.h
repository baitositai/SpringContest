#pragma once
#include "../framework.h"
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Common/Vector2.h"
#include "UI/DrawSpeedUp.h"

class DrawSpeedUp;

class TimeCount
{
public:

	//時間桁数
	static constexpr int TIME_DIGITS = 4;

	//時間描画拡大率
	static constexpr float TIME_RATE = 0.35f;

	//画像描画位置
	static constexpr int TIMER_GAGE_POS_X = Application::SCREEN_HALF_X;

	//Y座標
	static constexpr int TIMER_POS_Y = 64;		//通常
	static constexpr int VS_TIMER_POS_Y = 350;	//VS

	//追加スコア
	static constexpr int ADD_SCORE = 100;

	//一分当たりの秒数
	static constexpr int SECONDS_PER_MINUTE = 60;

	static constexpr int TIME_CNTS_POS_X[TIME_DIGITS] = {
		Application::SCREEN_HALF_X - 64,
		Application::SCREEN_HALF_X - 32,
		Application::SCREEN_HALF_X + 32,
		Application::SCREEN_HALF_X + 64};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TimeCount();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TimeCount() = default;

	/// <summary>
	/// 読み込み
	/// </summary>
	void Load();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 解放
	/// </summary>
	void Release();

	/// <summary>
	/// 解放
	/// </summary>
	void CommonDraw();

private:

	//画像
	int imgTimerGage_;
	int* imgNums_;

	//タイマーY座標
	int posY_;

	//時間経過用ステップ
	float step_;
	int preStep_;
	float scrCnt_;

	//速度上昇UI
	std::unique_ptr<DrawSpeedUp> speedUi_;

};

