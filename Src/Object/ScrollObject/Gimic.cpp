#include "../../Manager/ScoreBank.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/SoundManager.h"
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

	transform_.SetModel(resMng_.LoadModelDuplicate(
		ResourceManager::SRC::BOMB));
	transform_.scl = SCALE;
	transform_.pos = Utility::VECTOR_ZERO;
	transform_.quaRot = Quaternion();
	transform_.quaRotLocal =
		Quaternion::Euler({ 0.0f, Utility::Deg2RadF(0.0f), 0.0f });
	transform_.Update();
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

	//爆発音再生
	SoundManager::GetInstance().Play(SoundManager::SOUND::BLAST_SE);

	//状態を変更
	ChangeState(STATE::HIT);
}

void Gimic::Draw()
{
	if (state_ == STATE::NONE) { return; }

	//モデルの描画
	MV1DrawModel(transform_.modelId);
	//DrawSphere3D(transform_.pos, 20.0f, 10, color_, color_, true);
}
