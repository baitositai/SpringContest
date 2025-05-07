#include "SkyDome.h"

SkyDome::SkyDome()
{
	state_ = STATE::NONE;

	// 状態管理
	stateChanges_.emplace(STATE::NONE, std::bind(&SkyDome::ChangeStateNone, this));
	stateChanges_.emplace(STATE::STAY, std::bind(&SkyDome::ChangeStateStay, this));
	stateChanges_.emplace(STATE::FOLLOW, std::bind(&SkyDome::ChangeStateFollow, this));
}

void SkyDome::Load()
{
	//モデル設定
	SetModel();
}

void SkyDome::Init()
{
	// Zバッファ無効(突き抜け対策)
	MV1SetUseZBuffer(transform_.modelId, false);
	MV1SetWriteZBuffer(transform_.modelId, false);

	// 状態遷移
	ChangeState(STATE::STAY);
}

void SkyDome::Update()
{
	// 更新ステップ
	stateUpdate_();
}

void SkyDome::Draw()
{
	MV1DrawModel(transform_.modelId);
}

void SkyDome::SetModel()
{
	// モデル制御の基本情報
	transform_.SetModel(
		ResourceManager::GetInstance().LoadModelDuplicate(
			ResourceManager::SRC::SKY_DOME));
	transform_.scl = SCALE;
	transform_.pos = Utility::VECTOR_ZERO;
	transform_.quaRot = Quaternion::Euler(
		0.0f,
		Utility::Deg2RadF(180.0f),
		0.0f
	);
	transform_.quaRotLocal = Quaternion();
	transform_.Update();
}

void SkyDome::ChangeState(STATE state)
{
	// 状態変更
	state_ = state;

	// 各状態遷移の初期処理
	stateChanges_[state_]();
}

void SkyDome::ChangeStateNone()
{
	stateUpdate_ = std::bind(&SkyDome::UpdateNone, this);
}

void SkyDome::ChangeStateStay()
{
	stateUpdate_ = std::bind(&SkyDome::UpdateStay, this);
}

void SkyDome::ChangeStateFollow()
{
	stateUpdate_ = std::bind(&SkyDome::UpdateFollow, this);
	transform_.Update();
}

void SkyDome::UpdateNone()
{
}

void SkyDome::UpdateStay()
{
	//スカイドームの回転処理
	Quaternion yRot = Quaternion::AngleAxis(Utility::Deg2RadF(ROT_SPEED), Utility::AXIS_Y);
	transform_.quaRot = Quaternion::Mult(transform_.quaRot, yRot);
	transform_.Update();
}

void SkyDome::UpdateFollow()
{
	transform_.Update();
}
