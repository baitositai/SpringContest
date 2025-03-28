#pragma once
#include "../framework.h"
#include "../Application.h"
#include "../Manager/SceneManager.h"

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
	static constexpr int TIMER_POS_Y = 64;	//通常
	static constexpr int VS_TIMER_POS_Y = 156;	//VS

	static constexpr int TIME_CNTS_POS_X[TIME_DIGITS] = {
		Application::SCREEN_HALF_X - 64,
		Application::SCREEN_HALF_X - 32,
		Application::SCREEN_HALF_X + 32,
		Application::SCREEN_HALF_X + 64};

	TimeCount();
	~TimeCount() = default;

	void Load();
	void Init();
	void Update();
	void Draw();
	void Release();

private:

	//画像
	int imgTimerGage_;
	int* imgNums_;

	//タイマーY座標
	int posY_;

	//時間経過用ステップ
	float step_;
};

