#include "../../Utility/Utility.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/ScrollManager.h"
#include "../../Manager/SceneManager.h"
#include "Player.h"

Player::Player()
{
	animationController_ = nullptr;
	state_ = STATE::NONE;
	aliveState_ = ALIVE_STATE::NONE;
	moveSpeed_ = -1.0f;
	isJump_ = false;
	stepJump_ = -1.0f;
	life_ = -1;
	pow_ = -1;
	radius_ = -1.0f;
	tackleTime_ = -1.0f;
	damageTime_ = -1.0f;

	stateChanges_.emplace(STATE::NONE, std::bind(&Player::ChangeStateNone, this));
	stateChanges_.emplace(STATE::ALIVE, std::bind(&Player::ChangeStateAlive, this));
	stateChanges_.emplace(STATE::DEATH, std::bind(&Player::ChangeStateDeath, this));

	aliveStateChanges_.emplace(ALIVE_STATE::RUN, std::bind(&Player::ChanageAliveStateRun, this));
	aliveStateChanges_.emplace(ALIVE_STATE::TACKLE, std::bind(&Player::ChanageAliveStateTackle, this));
	aliveStateChanges_.emplace(ALIVE_STATE::DAMAGE, std::bind(&Player::ChanageAliveStateDamage, this));
}

void Player::Load()
{
	// モデルの基本設定
	InitModel();

	//アニメーションの設定
	animationController_ = std::make_unique<AnimationController>(trans_.modelId);
}

void Player::Init()
{
	//アニメーションの設定
	InitAnimation();

	//初期化
	moveSpeed_ = SPEED_MOVE;
	stepJump_ = 0.0f;
	pow_ = DEFAULT_POWER;
	life_ = DEFAULT_LIFE;
	radius_ = RADIUS;
	tackleTime_ = 0.0f;
	damageTime_ = 0.0f;

	//初期状態
	ChangeState(STATE::ALIVE);
	ChangeAliveState(ALIVE_STATE::RUN);
}

void Player::Update()
{
	// 更新ステップ
	stateUpdate_();

	trans_.Update();

	animationController_->Update();
}

void Player::Draw()
{
	// モデルの描画
	MV1DrawModel(trans_.modelId);
}

void Player::AddLife(const int& life)
{
	life_ += life;

	//ライフが最大の時
	if (life_ > DEFAULT_LIFE) {
		life_ = DEFAULT_LIFE;
	}
	//プレイヤーの死亡判定
	else if (life_ <= 0) {
		ChangeState(STATE::DEATH);
	}
}

void Player::AddPower(const int& pow)
{
	pow_ += pow;
	//パワーが最大の時
	if (pow_ > DEFAULT_POWER) {
		pow_ = DEFAULT_POWER;
	}
}

void Player::ChangeAliveState(const ALIVE_STATE& state)
{
	aliveState_ = state;

	// 各状態遷移の初期処理
	aliveStateChanges_[aliveState_]();
}

void Player::InitModel(void)
{
	trans_.SetModel(ResourceManager::GetInstance().LoadModelDuplicate(
		ResourceManager::SRC::PLAYER));
	trans_.scl = Utility::VECTOR_ONE;
	trans_.pos = Utility::VECTOR_ZERO;
	trans_.quaRot = Quaternion();
	trans_.quaRotLocal =
		Quaternion::Euler({ 0.0f, Utility::Deg2RadF(180.0f), 0.0f });
	trans_.Update();
}

void Player::InitAnimation(void)
{
	std::string path = Application::PATH_MODEL + "Player/Animation/";
	animationController_->Add((int)ANIM_TYPE::IDLE, path + "Idle.mv1", ANIM_SPEED);
	animationController_->Add((int)ANIM_TYPE::RUN, path + "Running.mv1", ANIM_SPEED);
	animationController_->Add((int)ANIM_TYPE::TACKLE, path + "Tackle.mv1", ANIM_SPEED);
	animationController_->Add((int)ANIM_TYPE::JUMP, path + "Jump.mv1", ANIM_SPEED);
	animationController_->Add((int)ANIM_TYPE::DANCE, path + "Flair.mv1", ANIM_SPEED);
	animationController_->Add((int)ANIM_TYPE::DEATH, path + "Fall Flat.mv1", ANIM_SPEED);

	//初期状態
	animationController_->Play((int)ANIM_TYPE::RUN);
}

void Player::Process()
{
	auto& ins = InputManager::GetInstance();

	//操作
	if (ins.IsNew(KEY_INPUT_A)) { trans_.pos.x -= moveSpeed_; }
	else if (ins.IsNew(KEY_INPUT_D)) { trans_.pos.x += moveSpeed_; }

	//移動制限
	float left = ScrollManager::MOVE_LIMIT_LEFT;
	float right = ScrollManager::MOVE_LIMIT_RIGHT;
	if (trans_.pos.x > right) { trans_.pos.x = right; }
	else if(trans_.pos.x < left) { trans_.pos.x = left; }

	//ジャンプ処理
	if (ins.IsTrgDown(KEY_INPUT_SPACE)) 
	{ 
		isJump_ = true; 
		if (aliveState_ != ALIVE_STATE::TACKLE ) { animationController_->Play((int)ANIM_TYPE::JUMP); }
	}
}

void Player::Jump(void)
{
	// ジャンプ
	if (isJump_)
	{
		stepJump_ += SceneManager::GetInstance().GetDeltaTime() * JUMP_SPEED;
		trans_.pos.y = JUMP_HEIGHT * sin(RAD_PER_FRAME * stepJump_) + ScrollManager::GROUND;

		//地面についたとき
		if (trans_.pos.y <= 0)
		{
			trans_.pos.y = ScrollManager::GROUND;
			isJump_ = false;
			stepJump_ = 0.0f;
			animationController_->Play((int)ANIM_TYPE::RUN);
		}
	}
}

void Player::Run()
{
	//特別処理はなし
}

void Player::Tackle()
{
	//時間を減らす
	tackleTime_ -= SceneManager::GetInstance().GetDeltaTime();

	//時間になった時
	if (tackleTime_ <= 0.0f) {
		//アニメーションを戻す
		animationController_->Play((int)ANIM_TYPE::RUN);
		//時間の初期化
		tackleTime_ = 0.0f;
		//タックルを終了
		ChangeAliveState(ALIVE_STATE::RUN);
	}
}

void Player::Damage()
{
	//時間を減らす
	damageTime_ -= SceneManager::GetInstance().GetDeltaTime();

	//モデルの色を変える
	//MV1SetMaterialDifColor(trans_.modelId, 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
	if(static_cast<int>(damageTime_ * 10.0f) % 2 == 0) { MV1SetMaterialDifColor(trans_.modelId, 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f)); }
	else { MV1SetMaterialDifColor(trans_.modelId, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f)); }

	//時間になった時
	if (damageTime_ <= 0.0f) {
		//モデルの色を通常に戻す
		MV1SetMaterialDifColor(trans_.modelId, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
		//時間の初期化
		damageTime_ = 0.0f;
		//タックルを終了
		ChangeAliveState(ALIVE_STATE::RUN);
	}
}

void Player::DebagDraw()
{
	DrawSphere3D(
	trans_.pos,
		radius_,
		20,
		0xff0000,
		0xff0000,
		true);

	//デバッグ
	DrawFormatString(0, 0, 0x000000, "LIFE = %d", life_);
	DrawFormatString(0, 20, 0x000000, "POW = %d", pow_);
}

void Player::ChangeState(STATE state)
{
	// 状態変更
	state_ = state;

	// 各状態遷移の初期処理
	stateChanges_[state_]();
}

void Player::ChangeStateNone(void)
{
	stateUpdate_ = std::bind(&Player::UpdateNone, this);
}

void Player::ChangeStateAlive(void)
{
	stateUpdate_ = std::bind(&Player::UpdateAlive, this);
}

void Player::ChangeStateDeath(void)
{
	stateUpdate_ = std::bind(&Player::UpdateDeath, this);

	//アニメーションを再生
	animationController_->Play((int)ANIM_TYPE::DEATH, false);
}

void Player::ChanageAliveStateRun()
{
	aliveStateUpdate_ = std::bind(&Player::Run, this);
}

void Player::ChanageAliveStateTackle()
{
	aliveStateUpdate_ = std::bind(&Player::Tackle, this);

	//アニメーションの再生
	animationController_->Play((int)ANIM_TYPE::TACKLE);
	
	//タックルの時間設定
	tackleTime_ = TACKLE_TIME;
}

void Player::ChanageAliveStateDamage()
{
	aliveStateUpdate_ = std::bind(&Player::Damage, this);

	damageTime_ = DAMAGE_TIME;
}

void Player::UpdateNone(void)
{
}

void Player::UpdateAlive(void)
{
	//操作処理
	Process();

	// ジャンプ処理
	Jump();

	//生存状態別の更新
	aliveStateUpdate_();
}

void Player::UpdateDeath(void)
{
}
