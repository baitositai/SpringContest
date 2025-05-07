#include "../../Manager/ScoreBank.h"
#include "../../Manager/DataBank.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Manager/Effect2DManagerContainer.h"
#include "../../Manager/Effect2DManager.h"
#include "../Character/Player.h"
#include "Gimmick.h"

Gimmick::Gimmick()
{
}

Gimmick::~Gimmick()
{
}

void Gimmick::InitModel()
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

void Gimmick::OnCollision(Player& player)
{
	//プレイヤーがダメージの状態は処理を行わない
	if (player.GetAliveState() == Player::ALIVE_STATE::DAMAGE) { return; }

	//プレイヤーにダメージ
	player.ChangeAliveState(Player::ALIVE_STATE::DAMAGE);
	player.AddLife(DAMAGE);

	//スコア加算
	ScoreBank::GetInstance().AddScore(DataBank::GetInstance().Output().playerId_, SCORE);

	//爆発音再生
	//SoundManager::GetInstance().Play(SoundManager::SOUND::BLAST_SE);

	//エフェクト再生
	Effect2DManagerContainer::GetInstance().GetManager(DataBank::GetInstance().Output().playerId_)->Play(Effect2DManager::EFFECT::BLAST,
		VAdd(player.GetTransform().pos, EXPLOSION_POS),
		Player::EFK_RATE,
		0.0f,
		SoundManager::SOUND::BLAST_SE);

	//状態を変更
	ChangeState(STATE::HIT);
}

void Gimmick::Draw()
{
	if (state_ == STATE::NONE) { return; }

	//モデルの描画
	MV1DrawModel(transform_.modelId);

	//エフェクトの描画
	Effect2DManagerContainer::GetInstance().GetManager(SceneManager::GetInstance().GetScreenCount())->DrawScreenEffect(Effect2DManager::EFFECT::BLAST);
}
