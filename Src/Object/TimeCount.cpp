#include "TimeCount.h"

TimeCount::TimeCount()
{
	step_ = -1.0f;
}

void TimeCount::Load()
{
}

void TimeCount::Init()
{
	//初期化
	step_ = 0.0f;
}

void TimeCount::Update()
{
	//時間経過
	step_ += SceneManager::GetInstance().GetDeltaTime();
}

void TimeCount::Draw()
{
	int min = static_cast<int>(step_) / 60;
	int sec = static_cast<int>(step_) % 60;

	DrawFormatString(
		Application::SCREEN_HALF_X - 32,
		0,
		0xffffff,
		"%d : %d",
		min,
		sec);
}

void TimeCount::Release()
{
}
