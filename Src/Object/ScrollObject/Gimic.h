#pragma once
#include "ObjectBase.h"

class Gimic : public ObjectBase
{
public:

	//�_���[�W��
	static constexpr int DAMAGE = -1;

	//�X�R�A��
	static constexpr int SCORE = -500;

	Gimic();
	~Gimic();

	void InitModel() override;
	void OnCollision(Player& player) override;

private:

};
