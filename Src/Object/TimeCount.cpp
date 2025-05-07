#include "../Application.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/DataBank.h"
#include "../Manager/ScoreBank.h"
#include "../Manager/ScrollManager.h"
#include "TimeCount.h"

TimeCount::TimeCount()
{
	step_ = -1.0f;
	preStep_ = -1;
	scrCnt_ = -1.0f;
	int i = -1;
	imgNums_ = &i;
	imgTimerGage_ = -1;
	posY_ = -1;
}

void TimeCount::Load()
{
	//画像読み込み
	auto& res = ResourceManager::GetInstance();
	imgTimerGage_ = res.Load(ResourceManager::SRC::TIMER_UI).handleId_;
	imgNums_ = res.Load(ResourceManager::SRC::NUMBER).handleIds_;

	//速度上昇UI
	speedUi_ = std::make_unique<DrawSpeedUp>();
	speedUi_->Load();
}

void TimeCount::Init()
{
	//初期化
	step_ = 0.0f;
	preStep_ = 1;
	scrCnt_ = ScrollManager::SPEED_UP_TIME;

	//モードごとに描画位置を変更
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS) { posY_ = VS_TIMER_POS_Y; }	
	else { posY_ = TIMER_POS_Y; }

	//速度上昇UI
	speedUi_->Init();
}

void TimeCount::Update()
{
	float cnt = SceneManager::GetInstance().GetDeltaTime();
	int playNum = DataBank::GetInstance().Output().playerNum_;

	//カウント更新
	step_ += cnt;
	scrCnt_ -= cnt;

	//1秒ごとにスコア上昇
	if (static_cast<int>(step_) != preStep_)
	{
		preStep_ = static_cast<int>(step_);
		for (int i = 0; i < playNum; i++) {
			ScoreBank::GetInstance().AddScore(i, ADD_SCORE);
		}
	}

	//スピードアップ
	if (scrCnt_ <= 0.0f)
	{
		//速度アップ
		for (int i = 0; i < playNum; i++) {
			ScrollManager::GetInstance().ChangeScrollSpeed(i, ScrollManager::ACC_SPEED);
		}

		//速度上昇UI状態変更
		speedUi_->ChangeState(DrawSpeedUp::STATE::EXPAND);

		//カウント初期化
		scrCnt_ = ScrollManager::SPEED_UP_TIME;
	}

	//速度上昇UI
	speedUi_->Update();
}

void TimeCount::Draw()
{
	//スピードアップ描画
	speedUi_->Draw();
}

void TimeCount::Release()
{
	speedUi_->Release();
}

void TimeCount::CommonDraw()
{
	//タイマー描画
	int min = static_cast<int>(step_) / SECONDS_PER_MINUTE;
	int sec = static_cast<int>(step_) % SECONDS_PER_MINUTE;

	int timeNum[TIME_DIGITS] = {
		min / 10,
		min % 10,
		sec / 10,
		sec % 10
	};

	//タイマーゲージの描画
	DrawRotaGraph(
		Application::SCREEN_HALF_X,
		posY_,
		1.0f,
		0.0f,
		imgTimerGage_,
		true,
		false);

	//数字
	for (int i = 0; i < TIME_DIGITS; i++)
	{
		DrawRotaGraph(
			TIME_CNTS_POS_X[i],
			posY_,
			TIME_RATE,
			0.0f,
			imgNums_[timeNum[i]],
			true,
			false);
	}
}
