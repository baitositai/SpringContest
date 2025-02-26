#pragma once
#include "ObjectBase.h"

class PowerItem : public ObjectBase
{
public:

	//パワーの回復量
	static constexpr int POWER_HEAL = 1;

	//スコア量
	static constexpr int SCORE = 100;

	PowerItem();
	~PowerItem();

	void Load() override;
	void OnCollision(Player& player) override;

private:

};

