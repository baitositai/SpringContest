#include "../../Manager/ScoreBank.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "../Character/Player.h"
#include "../../Utility/Utility.h"
#include "../../Object/Common/AnimationController.h"
#include "Enemy.h"

Enemy::Enemy()
{
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
	transform_.pos = VSub(transform_.pos, {moveDirX_, -5.0f, -5.0f});
	
	if (1.5f <= cnt_)
	{
		//状態を変える
		ChangeState(STATE::NONE);
	}
	
}

void Enemy::InitAnimation(void)
{
	//アニメーションの設定
	animationController_ = std::make_unique<AnimationController>(transform_.modelId);
	std::string path = Application::PATH_MODEL + "Enemy/Animation/";
	/*animationController_->Add((int)ANIM_TYPE::IDLE, path + "", ANIM_SPEED);*/
	animationController_->Add((int)ANIM_TYPE::RUN, path + "ZombieRunning.mv1", ANIM_SPEED);
	/*animationController_->Add((int)ANIM_TYPE::DEATH, path + "", ANIM_SPEED);*/

	//初期状態
	animationController_->Play((int)ANIM_TYPE::RUN);
}



void Enemy::Draw()
{
	if (state_==STATE::NONE)
	{
		return;
	}

	//モデルの描画
	MV1DrawModel(transform_.modelId);
	DrawSphere3D(transform_.pos, 20.0f, 10, color_, color_, true);
}

void Enemy::OnCollision(Player& player)
{
	//すでにタックル中
	if (player.GetAliveState() == Player::ALIVE_STATE::TACKLE)
	{
		//スコア加算
		ScoreBank::GetInstance().AddScore(HIT_SCORE);
	}	
	//パワーがある場合
	else if (player.GetPower() > 0)
	{
		//プレイヤーをタックル状態にする
		player.ChangeAliveState(Player::ALIVE_STATE::TACKLE);
		player.AddPower(POWER_CONSUME);

		//スコア加算
		ScoreBank::GetInstance().AddScore(HIT_SCORE);
	}
	else
	{
		//プレイヤーにダメージ
		player.ChangeAliveState(Player::ALIVE_STATE::DAMAGE);
		player.AddLife(DAMAGE);

		//スコア加算
		ScoreBank::GetInstance().AddScore(DAMAGE_SCORE);
	}
	//状態を変更
	ChangeState(STATE::HIT);
	
	//カウントをリセット
	cnt_ = 0;

	moveDirX_ = 0.0f;

	int posX;
	
	posX = GetRand(10);

	if (posX / 2)
	{
		moveDirX_ = 5.0f;
	}
	else
	{
		moveDirX_ = -5.0f;
	}
}
