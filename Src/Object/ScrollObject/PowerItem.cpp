#include "../../Manager/ScoreBank.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/SoundManager.h"
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
	ScoreBank::GetInstance().AddScore(SCORE);

	//���ʉ��̍Đ�
	SoundManager::GetInstance().Play(SoundManager::SOUND::ITEM_GET_SE);

	//��Ԃ�ύX
	ChangeState(STATE::HIT);
}

void PowerItem::Draw()
{
	if (state_ == STATE::NONE) { return; }

	//���f���̕`��
	MV1DrawModel(transform_.modelId);
	//DrawSphere3D(transform_.pos, 20.0f, 10, color_, color_, true);
}