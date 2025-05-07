#pragma once
#include <vector>
#include "../Manager/SceneManager.h"
#include "../Utility/StaticSingleton.h"

class ScoreBank : public StaticSingleton<ScoreBank>
{
public:

	//スコア最大量
	static constexpr int SCORE_MAX = 99999;

	ScoreBank();
	~ScoreBank() = default;

	//初期化処理
	void Init();

	//スコアの加算
	void AddScore(const int playerId,const int value);

	//スコアを返す
	inline const int & GetScore(const int playerId) const { return score_[playerId]; }

	//スコアをリセット
	inline void ResetScore(const int playerId) { score_[playerId] = 0; }

private:

	//シングルトン
	THIS_CLASS_IS_STATIC_SINGLETON(ScoreBank);

	//スコア
	std::vector<int> score_;
};