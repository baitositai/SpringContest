#pragma once
#include "ObjectBase.h"

class PowerItem : public ObjectBase
{
public:

	//�p���[�̉񕜗�
	static constexpr int POWER_HEAL = 1;

	//�X�R�A��
	static constexpr int SCORE = 100;

	PowerItem();
	~PowerItem();

	void Load() override;
	void OnCollision(Player& player) override;

private:

};

