#pragma once
#include "ObjectBase.h"

class Enemy : public ObjectBase
{
public:

	//ダメージ
	static constexpr int DAMAGE = -1;

	//パワー消費量
	static constexpr int POWER_CONSUME = -1;

	//スコア量
	static constexpr int HIT_SCORE = 300;
	static constexpr int DAMAGE_SCORE = -500;

	Enemy();
	~Enemy();

	void Load() override;
	void OnCollision(Player& player) override;

private:

};

