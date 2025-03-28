#pragma once
#include "ObjectBase.h"

class LifeItem : public ObjectBase
{
public:

	//スケール
	static constexpr VECTOR SCALE = { 0.3f,0.3f ,0.3f };

	//体力回復量
	static constexpr int LIFE_HEAL = 1;

	//スコア量
	static constexpr int SCORE = 100;

	LifeItem();
	~LifeItem();

	void InitModel() override;
	void OnCollision(Player& player) override;
	void Draw() override;

private:

};

