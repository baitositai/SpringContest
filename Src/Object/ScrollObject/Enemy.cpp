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
	//���łɃ^�b�N����
	if (player.GetAliveState() == Player::ALIVE_STATE::TACKLE)
	{
		//�X�R�A���Z
		ScoreBank::GetInstance().AddScore(HIT_SCORE);
	}	
	//�p���[������ꍇ
	else if (player.GetPower() > 0)
	{
		//�v���C���[���^�b�N����Ԃɂ���
		player.ChangeAliveState(Player::ALIVE_STATE::TACKLE);
		player.AddPower(POWER_CONSUME);

		//�X�R�A���Z
		ScoreBank::GetInstance().AddScore(HIT_SCORE);
	}
	else
	{
		//�v���C���[�Ƀ_���[�W
		player.ChangeAliveState(Player::ALIVE_STATE::DAMAGE);
		player.AddLife(DAMAGE);

		//�X�R�A���Z
		ScoreBank::GetInstance().AddScore(DAMAGE_SCORE);
	}
	//��Ԃ�ύX
	ChangeState(STATE::HIT);

}
