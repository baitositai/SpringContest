#include "../../Manager/ScoreBank.h"
#include "../Character/Player.h"
#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Load()
{
	color_ = 0xff4500;
}

void Enemy::OnCollision(Player& player)
{
	//すでにタックル中
	if (player.IsTackle())
	{
		//スコア加算
		ScoreBank::GetInstance().AddScore(HIT_SCORE);
	}	
	//パワーがある場合
	else if (player.GetPower() > 0)
	{
		//プレイヤーをタックル状態にする
		player.SetIsTackle(true);
		player.AddPower(POWER_CONSUME);

		//スコア加算
		ScoreBank::GetInstance().AddScore(HIT_SCORE);
	}
	else
	{
		//プレイヤーにダメージ
		player.AddLife(DAMAGE);

		//スコア加算
		ScoreBank::GetInstance().AddScore(DAMAGE_SCORE);
	}
	//状態を変更
	ChangeState(STATE::HIT);

}
