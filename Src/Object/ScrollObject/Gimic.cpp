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
	//�v���C���[���_���[�W�̏�Ԃ͏������s��Ȃ�
	if (player.GetAliveState() == Player::ALIVE_STATE::DAMAGE) { return; }

	//�v���C���[�Ƀ_���[�W
	player.ChangeAliveState(Player::ALIVE_STATE::DAMAGE);
	player.AddLife(DAMAGE);

	//�X�R�A���Z
	ScoreBank::GetInstance().AddScore(SCORE);

	//�������Đ�
	SoundManager::GetInstance().Play(SoundManager::SOUND::BLAST_SE);

	//��Ԃ�ύX
	ChangeState(STATE::HIT);
}

void Gimic::Draw()
{
	if (state_ == STATE::NONE) { return; }

	//���f���̕`��
	MV1DrawModel(transform_.modelId);
	//DrawSphere3D(transform_.pos, 20.0f, 10, color_, color_, true);
}
