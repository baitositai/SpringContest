#include "../../Manager/ScoreBank.h"
#include "../../Manager/DataBank.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/SoundManager.h"
#include "../Character/Player.h"
#include "../../Utility/Utility.h"
#include "../../Object/Common/AnimationController.h"
#include "Enemy.h"

Enemy::Enemy()
{
	cnt_ = -1;
	moveDirX_ = -1.0f;
}

Enemy::~Enemy()
{
}

void Enemy::InitModel(void)
{
	transform_.SetModel(resMng_.LoadModelDuplicate(
		ResourceManager::SRC::ENEMY));
	transform_.scl = SCALE;
	transform_.pos = Utility::VECTOR_ZERO;
	transform_.quaRot = Quaternion();
	transform_.quaRotLocal =
		Quaternion::Euler({ 0.0f, Utility::Deg2RadF(0.0f), 0.0f });
	transform_.Update();

	color_ = 0xff4500;
}

void Enemy::Load()
{
	ObjectBase::Load();
	InitAnimation();
}

void Enemy::Update()
{
	ObjectBase::Update();
	animationController_->Update();
}

void Enemy::UpdateHit()
{
	cnt_ += scnMng_.GetDeltaTime();
	transform_.pos = VSub(transform_.pos, {moveDirX_, -SMASH_SPEED, -SMASH_SPEED });
	
	if (CHANGE_SECOND <= cnt_)
	{
		//��Ԃ�ς���
		ChangeState(STATE::NONE);
	}
}

void Enemy::InitAnimation(void)
{
	//�A�j���[�V�����̐ݒ�
	animationController_ = std::make_unique<AnimationController>(transform_.modelId);
	std::string path = Application::PATH_MODEL + "Enemy/Animation/";
	animationController_->Add((int)ANIM_TYPE::RUN, path + "ZombieRunning.mv1", ANIM_SPEED);

	//�������
	animationController_->Play((int)ANIM_TYPE::RUN);
}

void Enemy::ResetHitAnim()
{
	//�A�j���[�V�����p�ϐ���������
	cnt_ = 0;
	moveDirX_ = 0.0f;

	//�����_���Œl��ݒ�
	int posX = GetRand(10);

	//���f
	if (posX / 2){moveDirX_ = SMASH_SPEED;}
	else { moveDirX_ = -SMASH_SPEED; }
}

void Enemy::Draw()
{
	if (state_ == STATE::NONE) { return; }

	//���f���̕`��
	MV1DrawModel(transform_.modelId);
	//DrawSphere3D(transform_.pos, 20.0f, 10, color_, color_, true);
}

void Enemy::OnCollision(Player& player)
{
	//�v���C���[���_���[�W�̏�Ԃ͏������s��Ȃ�
	if (player.GetAliveState() == Player::ALIVE_STATE::DAMAGE) { return; }

	//���łɃ^�b�N����
	if (player.GetAliveState() == Player::ALIVE_STATE::TACKLE)
	{
		//�X�R�A���Z
		ScoreBank::GetInstance().AddScore(HIT_SCORE);

		//���ʉ��Đ�
		SoundManager::GetInstance().Play(SoundManager::SOUND::ENEMY_DAMAGE_SE);

		//��Ԃ�ύX
		ChangeState(STATE::HIT);

		//�Փ˃A�j���[�V�����̏�����
		ResetHitAnim();
	}	
	//�p���[������ꍇ
	else if (player.GetPower() > 0 && DataBank::GetInstance().Output().autoTackle_)
	{
		//�v���C���[���^�b�N����Ԃɂ���
		player.ChangeAliveState(Player::ALIVE_STATE::TACKLE);
		player.AddPower(POWER_CONSUME);

		//�X�R�A���Z
		ScoreBank::GetInstance().AddScore(HIT_SCORE);

		//���ʉ��Đ�
		SoundManager::GetInstance().Play(SoundManager::SOUND::ENEMY_DAMAGE_SE);

		//��Ԃ�ύX
		ChangeState(STATE::HIT);

		//�Փ˃A�j���[�V�����̏�����
		ResetHitAnim();
	}
	else
	{
		//�v���C���[�Ƀ_���[�W
		player.ChangeAliveState(Player::ALIVE_STATE::DAMAGE);
		player.AddLife(DAMAGE);

		//�X�R�A���Z
		ScoreBank::GetInstance().AddScore(DAMAGE_SCORE);
	}
}
