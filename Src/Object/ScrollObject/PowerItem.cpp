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
	//プレイヤーのパワーを回復
	player.AddPower(POWER_HEAL);

	//スコア加算
	ScoreBank::GetInstance().AddScore(SCORE);

	//状態を変更
	ChangeState(STATE::HIT);
}
