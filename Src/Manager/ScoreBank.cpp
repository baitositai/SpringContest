#include "ScoreBank.h"

ScoreBank::ScoreBank()
{
	Init();
}

void ScoreBank::Init()
{
	score_ = 0;
}

void ScoreBank::AddScore(const int& value)
{
	score_ += value;

	//スコア最大値を超えないようにする
	if (score_ > SCORE_MAX) { score_ = SCORE_MAX; }
	if (score_ < 0) { score_ = 0; }
}