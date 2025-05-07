#pragma once
#include "ObjectBase.h"
#include "../../Utility/Utility.h"

class Gimmick : public ObjectBase
{
public:

	//スケール
	static constexpr VECTOR SCALE = { 0.3f,0.3f ,0.3f };

	//ダメージ量
	static constexpr int DAMAGE = -1;

	//スコア量
	static constexpr int SCORE = -500;

	Gimmick();
	~Gimmick();

	void InitModel() override;
	void OnCollision(Player& player) override;
	void Draw() override;

private:

};
