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
	//�v���C���[�Ƀ_���[�W
	player.ChangeAliveState(Player::ALIVE_STATE::DAMAGE);
	player.AddLife(DAMAGE);

	//�X�R�A���Z
	ScoreBank::GetInstance().AddScore(SCORE);

	//��Ԃ�ύX
	ChangeState(STATE::HIT);
}
