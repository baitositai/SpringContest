#pragma once
#include "ObjectBase.h"
#include "../../Utility/Utility.h"

class Gimmick : public ObjectBase
{
public:

	//�X�P�[��
	static constexpr VECTOR SCALE = { 0.3f,0.3f ,0.3f };

	//�_���[�W��
	static constexpr int DAMAGE = -1;

	//�X�R�A��
	static constexpr int SCORE = -500;

	Gimmick();
	~Gimmick();

	void InitModel() override;
	void OnCollision(Player& player) override;
	void Draw() override;

private:

};
