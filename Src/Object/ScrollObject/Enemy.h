#pragma once
#include "ObjectBase.h"

class Enemy : public ObjectBase
{
public:

	//�_���[�W
	static constexpr int DAMAGE = -1;

	//�p���[�����
	static constexpr int POWER_CONSUME = -1;

	//�X�R�A��
	static constexpr int HIT_SCORE = 300;
	static constexpr int DAMAGE_SCORE = -500;

	Enemy();
	~Enemy();

	void Load() override;
	void OnCollision(Player& player) override;

private:

};

