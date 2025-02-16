#include "../../Manager/ScoreBank.h"
#include "../Character/Player.h"
#include "LifeItem.h"

LifeItem::LifeItem()
{
}

LifeItem::~LifeItem()
{
}

void LifeItem::Load()
{
	color_ = 0xabff2f;
}

void LifeItem::OnCollision(Player& player)
{
	//�v���C���[�̗̑͂���
	player.AddLife(LIFE_HEAL);

	//�X�R�A���Z
	ScoreBank::GetInstance().AddScore(SCORE);

	//��Ԃ�ύX
	ChangeState(STATE::HIT);
}
