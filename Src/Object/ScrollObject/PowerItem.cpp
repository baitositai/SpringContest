#include "../../Manager/ScoreBank.h"
#include "../Character/Player.h"
#include "PowerItem.h"

PowerItem::PowerItem()
{
}

PowerItem::~PowerItem()
{
}

void PowerItem::Load()
{
	color_ = 0x00bfff;
}

void PowerItem::OnCollision(Player& player)
{
	//�v���C���[�̃p���[����
	player.AddPower(POWER_HEAL);

	//�X�R�A���Z
	ScoreBank::GetInstance().AddScore(SCORE);

	//��Ԃ�ύX
	ChangeState(STATE::HIT);
}
