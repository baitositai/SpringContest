#include "../../Manager/ScoreBank.h"
#include "../../Manager/DataBank.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Manager/Effect2DManagerContainer.h"
#include "../../Manager/Effect2DManager.h"
#include "../../Utility/Utility.h"
#include "../Character/Player.h"
#include "LifeItem.h"

LifeItem::LifeItem()
{
}

LifeItem::~LifeItem()
{
}

void LifeItem::InitModel()
{
	transform_.SetModel(resMng_.LoadModelDuplicate(
		ResourceManager::SRC::HEART));
	transform_.scl = SCALE;
	transform_.pos = Utility::VECTOR_ZERO;
	transform_.quaRot = Quaternion();
	transform_.quaRotLocal =
		Quaternion::Euler({ 0.0f, Utility::Deg2RadF(0.0f), 0.0f });
	transform_.Update();
	color_ = Utility::LIME;
}

void LifeItem::OnCollision(Player& player)
{
	//プレイヤーの体力を回復
	player.AddLife(LIFE_HEAL);

	//スコア加算
	ScoreBank::GetInstance().AddScore(DataBank::GetInstance().Output().playerId_, SCORE);

	//状態を変更
	ChangeState(STATE::HIT);

	//エフェクト再生
	Effect2DManagerContainer::GetInstance().GetManager(DataBank::GetInstance().Output().playerId_)->Play(Effect2DManager::EFFECT::GET,
		VAdd(player.GetTransform().pos, Player::TACKLE_EFK_LOCAL_POS),
		1.0f,
		0.0f,
		SoundManager::SOUND::ITEM_GET_SE);
}

void LifeItem::Draw()
{
	if (state_ == STATE::NONE) { return; }

	//モデルの描画
	MV1DrawModel(transform_.modelId);
}