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
}
