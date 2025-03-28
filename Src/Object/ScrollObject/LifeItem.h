#pragma once
#include "ObjectBase.h"

class LifeItem : public ObjectBase
{
public:

	//�X�P�[��
	static constexpr VECTOR SCALE = { 0.3f,0.3f ,0.3f };

	//�̗͉񕜗�
	static constexpr int LIFE_HEAL = 1;

	//�X�R�A��
	static constexpr int SCORE = 100;

	LifeItem();
	~LifeItem();

	void InitModel() override;
	void OnCollision(Player& player) override;
	void Draw() override;

private:

};

