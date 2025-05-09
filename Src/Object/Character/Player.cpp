#include "../../Utility/Utility.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/ScrollManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Manager/DataBank.h"
#include "../../Manager/Effect2DManager.h"
#include "../../Manager/Effect2DManagerContainer.h"
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
	key_ = { -1, -1, -1, -1 };

	int i = -1;
	imgTackleEfk_ = &i;
	imgHitEfk_ = &i;

	stateChanges_.emplace(STATE::NONE, std::bind(&Player::ChangeStateNone, this));
	stateChanges_.emplace(STATE::ALIVE, std::bind(&Player::ChangeStateAlive, this));
	stateChanges_.emplace(STATE::DEATH, std::bind(&Player::ChangeStateDeath, this));
	stateChanges_.emplace(STATE::WIN, std::bind(&Player::ChangeStateWin, this));

	aliveStateChanges_.emplace(ALIVE_STATE::RUN, std::bind(&Player::ChangeAliveStateRun, this));
	aliveStateChanges_.emplace(ALIVE_STATE::TACKLE, std::bind(&Player::ChangeAliveStateTackle, this));
	aliveStateChanges_.emplace(ALIVE_STATE::DAMAGE, std::bind(&Player::ChangeAliveStateDamage, this));
}

void Player::Load()
{
	ResourceManager & res = ResourceManager::GetInstance();
	SoundManager& snd = SoundManager::GetInstance();
	Effect2DManagerContainer& efc = Effect2DManagerContainer::GetInstance();
	int playerId = DataBank::GetInstance().Output().playerId_;

	// モデルの基本設定
	InitModel();

	//アニメーションの設定
	animationController_ = std::make_unique<AnimationController>(trans_.modelId);

	//音楽の読み込み
	snd.Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::JUMP_SE,
		res.Load(ResourceManager::SRC::JUMP_SE).handleId_);

	snd.Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::TACKLE_SE,
		res.Load(ResourceManager::SRC::TACKLE_SE).handleId_);

	snd.Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::DAMAGE_SE,
		res.Load(ResourceManager::SRC::DAMAGE_SE).handleId_);
	
	//エフェクトの追加
	efc.GetManager(playerId)->Add(
		Effect2DManager::EFFECT::TACKLE, 
		res.Load(ResourceManager::SRC::TACKLE_EFK).handleIds_, 
		EFK_NUM_X * EFK_NUM_Y);

	efc.GetManager(playerId)->Add(
		Effect2DManager::EFFECT::DAMAGE, 
		res.Load(ResourceManager::SRC::HIT_EFK).handleIds_,
		EFK_NUM_X * EFK_NUM_Y,
		EFK_SPEED);

	efc.GetManager(playerId)->Add(
		Effect2DManager::EFFECT::BLAST,
		res.Load(ResourceManager::SRC::EXPLOSION_EFK).handleIds_,
		EFK_NUM_X * EFK_NUM_Y,
		EFK_SPEED);

	efc.GetManager(playerId)->Add(
		Effect2DManager::EFFECT::GET,
		res.Load(ResourceManager::SRC::GET_EFK).handleIds_,
		GET_ANIM_MAX,
		EFK_SPEED);
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

	//エフェクトの描画
	Effect2DManagerContainer& efc = Effect2DManagerContainer::GetInstance();
	efc.GetManager(SceneManager::GetInstance().GetScreenCount())->DrawScreenEffect(Effect2DManager::EFFECT::TACKLE);
	efc.GetManager(SceneManager::GetInstance().GetScreenCount())->DrawScreenEffect(Effect2DManager::EFFECT::DAMAGE);
	efc.GetManager(SceneManager::GetInstance().GetScreenCount())->DrawScreenEffect(Effect2DManager::EFFECT::GET);
}

void Player::Release()
{
	SoundManager::GetInstance().Stop(SoundManager::SOUND::JUMP_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::DAMAGE_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::TACKLE_SE);
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

void Player::SetKey(const int& right, const int& left, const int& jump, const int& tackle)
{
	key_.right_ = right;
	key_.left_ = left;
	key_.jump_ = jump;
	key_.tackle_ = tackle;
}

void Player::InitModel()
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

void Player::InitAnimation()
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
	if (ins.IsNew(key_.left_)) { trans_.pos.x -= moveSpeed_; }
	else if (ins.IsNew(key_.right_)) { trans_.pos.x += moveSpeed_; }

	//移動制限
	float left = ScrollManager::MOVE_LIMIT_LEFT;
	float right = ScrollManager::MOVE_LIMIT_RIGHT;
	if (trans_.pos.x > right) { trans_.pos.x = right; }
	else if(trans_.pos.x < left) { trans_.pos.x = left; }

	//ジャンプ処理
	if (ins.IsTrgDown(key_.jump_)) 
	{ 
		isJump_ = true; 
		SoundManager::GetInstance().Play(SoundManager::SOUND::JUMP_SE);
		if (aliveState_ != ALIVE_STATE::TACKLE ) { animationController_->Play((int)ANIM_TYPE::JUMP); }
	}

	//タックル処理
	if (ins.IsTrgDown(key_.tackle_) &&
		pow_ > 0 &&
		aliveState_ != ALIVE_STATE::TACKLE )
	{
		//状態変更
		ChangeAliveState(ALIVE_STATE::TACKLE);
		//パワーを減少
		AddPower(-1);
	}
}

void Player::Jump()
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
	Effect2DManagerContainer& efc = Effect2DManagerContainer::GetInstance();

	//時間を減らす
	tackleTime_ -= SceneManager::GetInstance().GetDeltaTime();

	//エフェクトを追従させる
	efc.GetManager(DataBank::GetInstance().Output().playerId_)->Sync(
		Effect2DManager::EFFECT::TACKLE,
		VAdd(trans_.pos, TACKLE_EFK_LOCAL_POS),
		EFK_RATE,
		0.0f);

	//時間になった時
	if (tackleTime_ <= 0.0f)
	{
		//アニメーションを戻す
		animationController_->Play((int)ANIM_TYPE::RUN);
		//時間の初期化
		tackleTime_ = 0.0f;
		//タックルを終了
		ChangeAliveState(ALIVE_STATE::RUN);
		//エフェクト終了
		efc.GetManager(DataBank::GetInstance().Output().playerId_)->Stop(Effect2DManager::EFFECT::TACKLE);
		//色を戻す
		MV1SetMaterialDifColor(trans_.modelId, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void Player::Damage()
{
	Effect2DManagerContainer& efc = Effect2DManagerContainer::GetInstance();

	//時間を減らす
	damageTime_ -= SceneManager::GetInstance().GetDeltaTime();

	//エフェクトを追従させる
	efc.GetManager(DataBank::GetInstance().Output().playerId_)->Sync(
		Effect2DManager::EFFECT::TACKLE,
		VAdd(trans_.pos, TACKLE_EFK_LOCAL_POS),
		1.0f,
		0.0f);

	//モデルの色を変える
	if(static_cast<int>(damageTime_ * 10.0f) % 2 == 0) 
	{ 
		MV1SetMaterialDifColor(trans_.modelId, 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		MV1SetMaterialDifColor(trans_.modelId, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//時間になった時
	if (damageTime_ <= 0.0f) 
	{
		//モデルの色を通常に戻す
		MV1SetMaterialDifColor(trans_.modelId, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));
		//時間の初期化
		damageTime_ = 0.0f;
		//タックルを終了
		ChangeAliveState(ALIVE_STATE::RUN);
		//エフェクト終了
		efc.GetManager(DataBank::GetInstance().Output().playerId_)->Stop(Effect2DManager::EFFECT::DAMAGE);
	}
}

void Player::DebagDraw()
{
	constexpr int DIV_NUM = 20;

	DrawSphere3D(
	trans_.pos,
		radius_,
		DIV_NUM,
		Utility::RED,
		Utility::RED,
		true);

	//デバッグ
	constexpr int INTERVAL = 20;
	int i = 0;
	DrawFormatString(0, INTERVAL * i, Utility::BLACK, "LIFE = %d", life_);
	i++;
	DrawFormatString(0, INTERVAL * i, Utility::BLACK, "POW = %d", pow_);
}

void Player::ChangeState(STATE state)
{
	// 状態変更
	state_ = state;

	// 各状態遷移の初期処理
	stateChanges_[state_]();
}

void Player::ChangeStateNone()
{
	stateUpdate_ = std::bind(&Player::UpdateNone, this);
}

void Player::ChangeStateAlive()
{
	stateUpdate_ = std::bind(&Player::UpdateAlive, this);
}

void Player::ChangeStateDeath()
{
	stateUpdate_ = std::bind(&Player::UpdateDeath, this);

	//アニメーションを再生
	animationController_->Play((int)ANIM_TYPE::DEATH, false);
}

void Player::ChangeStateWin()
{
	stateUpdate_ = std::bind(&Player::UpdateDeath, this);

	//アニメーションを再生
	animationController_->Play((int)ANIM_TYPE::DANCE, true);
}

void Player::ChangeAliveStateRun()
{
	aliveStateUpdate_ = std::bind(&Player::Run, this);
}

void Player::ChangeAliveStateTackle()
{
	aliveStateUpdate_ = std::bind(&Player::Tackle, this);

	//アニメーションの再生
	animationController_->Play((int)ANIM_TYPE::TACKLE);

	//エフェクトの再生
	Effect2DManagerContainer::GetInstance().GetManager(DataBank::GetInstance().Output().playerId_)->Play(Effect2DManager::EFFECT::TACKLE,
		VAdd(trans_.pos, TACKLE_EFK_LOCAL_POS),
		EFK_RATE,
		0.0f,
		SoundManager::SOUND::TACKLE_SE);
	
	//タックルの時間設定
	tackleTime_ = TACKLE_TIME;
}

void Player::ChangeAliveStateDamage()
{
	aliveStateUpdate_ = std::bind(&Player::Damage, this);

	//ダメージによる無敵時間
	damageTime_ = DAMAGE_TIME;

	//エフェクトの再生
	Effect2DManagerContainer::GetInstance().GetManager(DataBank::GetInstance().Output().playerId_)->Play(Effect2DManager::EFFECT::DAMAGE,
		VAdd(trans_.pos, TACKLE_EFK_LOCAL_POS),
		1.0f,
		0.0f,
		SoundManager::SOUND::DAMAGE_SE);
}

void Player::UpdateNone()
{
}

void Player::UpdateAlive()
{
	//操作処理
	Process();

	// ジャンプ処理
	Jump();

	//生存状態別の更新
	aliveStateUpdate_();
}

void Player::UpdateDeath()
{
}

void Player::UpdateWin()
{
}
