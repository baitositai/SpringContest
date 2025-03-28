#pragma once
#include "ObjectBase.h"

class PowerItem : public ObjectBase
{
public:

	//スケール
	static constexpr VECTOR SCALE = { 0.3f,0.3f ,0.3f };

	//パワーの回復量
	static constexpr int POWER_HEAL = 1;

	//スコア量
	static constexpr int SCORE = 100;

	PowerItem();
	~PowerItem();

	void InitModel() override;
	void OnCollision(Player& player) override;
	void Draw() override;

private:

};

