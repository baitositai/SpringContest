#pragma once
#include "../Utility/StaticSingleton.h"

class ScoreBank : public StaticSingleton<ScoreBank>
{
public:

	ScoreBank();
	~ScoreBank() = default;

	//����������
	void Init();

	//�X�R�A�̉��Z
	void AddScore(const int& value);

	//�X�R�A��Ԃ�
	inline const int & GetScore() const { return score_; }

private:

	//�V���O���g��
	THIS_CLASS_IS_STATIC_SINGLETON(ScoreBank);

	//�X�R�A
	int score_;
};