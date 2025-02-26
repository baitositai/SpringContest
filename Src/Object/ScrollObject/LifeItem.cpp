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
	//プレイヤーの体力を回復
	player.AddLife(LIFE_HEAL);

	//スコア加算
	ScoreBank::GetInstance().AddScore(SCORE);

	//状態を変更
	ChangeState(STATE::HIT);
}
