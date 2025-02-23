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
	if (player.GetAliveState() == Player::ALIVE_STATE::TACKLE)
	{
		//スコア加算
		ScoreBank::GetInstance().AddScore(HIT_SCORE);
	}	
	//パワーがある場合
	else if (player.GetPower() > 0)
	{
		//プレイヤーをタックル状態にする
		player.ChangeAliveState(Player::ALIVE_STATE::TACKLE);
		player.AddPower(POWER_CONSUME);

		//スコア加算
		ScoreBank::GetInstance().AddScore(HIT_SCORE);
	}
	else
	{
		//プレイヤーにダメージ
		player.ChangeAliveState(Player::ALIVE_STATE::DAMAGE);
		player.AddLife(DAMAGE);

		//スコア加算
		ScoreBank::GetInstance().AddScore(DAMAGE_SCORE);
	}
	//状態を変更
	ChangeState(STATE::HIT);

}
