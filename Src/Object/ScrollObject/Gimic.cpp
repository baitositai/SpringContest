#include "../../Manager/ScoreBank.h"
#include "../Character/Player.h"
#include "Gimic.h"

Gimic::Gimic()
{
}

Gimic::~Gimic()
{
}

void Gimic::InitModel()
{
	color_ = 0xb22222;
}

void Gimic::OnCollision(Player& player)
{
	//プレイヤーがダメージの状態は処理を行わない
	if (player.GetAliveState() == Player::ALIVE_STATE::DAMAGE) { return; }

	//プレイヤーにダメージ
	player.ChangeAliveState(Player::ALIVE_STATE::DAMAGE);
	player.AddLife(DAMAGE);

	//スコア加算
	ScoreBank::GetInstance().AddScore(SCORE);

	//状態を変更
	ChangeState(STATE::HIT);
}
