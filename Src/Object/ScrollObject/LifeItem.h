#pragma once
#include "ObjectBase.h"

class LifeItem : public ObjectBase
{
public:

	//�̗͉񕜗�
	static constexpr int LIFE_HEAL = 1;

	//�X�R�A��
	static constexpr int SCORE = 100;

	LifeItem();
	~LifeItem();

	void Load() override;
	void OnCollision(Player& player) override;

private:

};

