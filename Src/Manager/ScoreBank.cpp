#include "ScoreBank.h"
#include "DataBank.h"

ScoreBank::ScoreBank()
{
	Init();
}

void ScoreBank::Init()
{
	score_.clear();

	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS)
	{
		score_.resize(SceneManager::PLAYER_MAX,0);
	}
	else
	{
		score_.emplace_back(0);
	}
}

void ScoreBank::AddScore(const int playerId, const int value)
{
	score_[playerId] += value;

	//スコアが一定値を超えないようにする
	if (score_[playerId] > SCORE_MAX) { score_[playerId] = SCORE_MAX; }
	if (score_[playerId] < 0) { score_[playerId] = 0; }
}