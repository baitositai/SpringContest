#pragma once
#include "../Utility/StaticSingleton.h"

class ScoreBank : public StaticSingleton<ScoreBank>
{
public:

	ScoreBank();
	~ScoreBank() = default;

	//初期化処理
	void Init();

	//スコアの加算
	void AddScore(const int& value);

	//スコアを返す
	inline const int & GetScore() const { return score_; }

private:

	//シングルトン
	THIS_CLASS_IS_STATIC_SINGLETON(ScoreBank);

	//スコア
	int score_;
};