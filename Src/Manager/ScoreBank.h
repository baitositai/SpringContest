#pragma once
#include <vector>
#include "../Manager/SceneManager.h"
#include "../Utility/StaticSingleton.h"

class ScoreBank : public StaticSingleton<ScoreBank>
{
public:

	//�X�R�A�ő��
	static constexpr int SCORE_MAX = 99999;

	ScoreBank();
	~ScoreBank() = default;

	//����������
	void Init();

	//�X�R�A�̉��Z
	void AddScore(const int playerId,const int value);

	//�X�R�A��Ԃ�
	inline const int & GetScore(const int playerId) const { return score_[playerId]; }

	//�X�R�A�����Z�b�g
	inline void ResetScore(const int playerId) { score_[playerId] = 0; }

private:

	//�V���O���g��
	THIS_CLASS_IS_STATIC_SINGLETON(ScoreBank);

	//�X�R�A
	std::vector<int> score_;
};