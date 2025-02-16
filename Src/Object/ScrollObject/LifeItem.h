#pragma once
#include "ObjectBase.h"

class LifeItem : public ObjectBase
{
public:

	//‘Ì—Í‰ñ•œ—Ê
	static constexpr int LIFE_HEAL = 1;

	//ƒXƒRƒA—Ê
	static constexpr int SCORE = 100;

	LifeItem();
	~LifeItem();

	void Load() override;
	void OnCollision(Player& player) override;

private:

};

