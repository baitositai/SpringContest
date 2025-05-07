#include "../../Manager/ScoreBank.h"
#include "../../Manager/DataBank.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Manager/Effect2DManagerContainer.h"
#include "../../Manager/Effect2DManager.h"
#include "../../Utility/Utility.h"
#include "../Character/Player.h"
#include "PowerItem.h"

PowerItem::PowerItem()
{
}

PowerItem::~PowerItem()
{
}

void PowerItem::InitModel()
{
	transform_.SetModel(resMng_.LoadModelDuplicate(
		ResourceManager::SRC::POTION));
	transform_.scl = SCALE;
	transform_.pos = Utility::VECTOR_ZERO;
	transform_.quaRot = Quaternion();
	transform_.quaRotLocal =
		Quaternion::Euler({ 0.0f, Utility::Deg2RadF(0.0f), 0.0f });
	transform_.Update();
	color_ = 0x00bfff;
}

void PowerItem::OnCollision(Player& player)
{
	//�v���C���[�̃p���[����
	player.AddPower(POWER_HEAL);

	//�X�R�A���Z
	ScoreBank::GetInstance().AddScore(DataBank::GetInstance().Output().playerId_, SCORE);

	//��Ԃ�ύX
	ChangeState(STATE::HIT);

	//�G�t�F�N�g�Đ�
	Effect2DManagerContainer::GetInstance().GetManager(DataBank::GetInstance().Output().playerId_)->Play(Effect2DManager::EFFECT::GET,
		VAdd(player.GetTransform().pos, Player::TACKLE_EFK_LOCAL_POS),
		1.0f,
		0.0f,
		SoundManager::SOUND::ITEM_GET_SE);
}

void PowerItem::Draw()
{
	if (state_ == STATE::NONE) { return; }

	//���f���̕`��
	MV1DrawModel(transform_.modelId);
}