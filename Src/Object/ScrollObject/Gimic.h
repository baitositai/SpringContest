#pragma once
#include "ObjectBase.h"

class Gimic : public ObjectBase
{
public:

	//ダメージ量
	static constexpr int DAMAGE = -1;

	//スコア量
	static constexpr int SCORE = -500;

	Gimic();
	~Gimic();

	void InitModel() override;
	void OnCollision(Player& player) override;

private:

};
