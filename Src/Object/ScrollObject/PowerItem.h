#pragma once
#include "ObjectBase.h"

class PowerItem : public ObjectBase
{
public:

	//�X�P�[��
	static constexpr VECTOR SCALE = { 0.3f,0.3f ,0.3f };

	//�p���[�̉񕜗�
	static constexpr int POWER_HEAL = 1;

	//�X�R�A��
	static constexpr int SCORE = 100;

	PowerItem();
	~PowerItem();

	void InitModel() override;
	void OnCollision(Player& player) override;
	void Draw() override;

private:

};

