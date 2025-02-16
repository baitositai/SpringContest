#include "../../Manager/ScoreBank.h"
#include "../Character/Player.h"
#include "Gimic.h"

Gimic::Gimic()
{
}

Gimic::~Gimic()
{
}

void Gimic::Load()
{
	color_ = 0xb22222;
}

void Gimic::OnCollision(Player& player)
{
	//プレイヤーにダメージ
	player.AddLife(DAMAGE);

	//スコア加算
	ScoreBank::GetInstance().AddScore(SCORE);

	//プレイヤーの状態がタックルの場合戻す
	if (player.IsTackle()) { player.SetIsTackle(false); }

	//状態を変更
	ChangeState(STATE::HIT);
}
