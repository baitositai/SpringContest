#include "TitlePlayer.h"
#include "../../Application.h"
#include "../../Manager/ResourceManager.h"
#include "../ScrollObject/ObjectBase.h"
#include"../../Utility/Utility.h"


TitlePlayer::TitlePlayer()
{
}

void TitlePlayer::Load()
{
	//モデルの初期化
	auto& res = ResourceManager::GetInstance();
	trans_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::PLAYER));
	trans_.scl = SCALE;
	trans_.pos = Utility::VECTOR_ZERO;
	trans_.pos = POS;
	trans_.quaRot = Quaternion();
	trans_.quaRotLocal =
		Quaternion::Euler({ 0.0f, Utility::Deg2RadF(0.0f), 0.0f });
	trans_.Update();
}

void TitlePlayer::Init()
{
	//他変数の初期化
	InitAnim();
}

void TitlePlayer::Update()
{
	trans_.Update();
	animController_->Update();
}

void TitlePlayer::Draw()
{
	//描画
	MV1DrawModel(trans_.modelId);
}

void TitlePlayer::InitAnim()
{
	//アニメーションの初期化
	animController_ = std::make_unique<AnimationController>(trans_.modelId);
	std::string path = Application::PATH_MODEL + "Player/Animation/";
	animController_->Add((int)ANIM_TYPE::IDLE, path + "Idle.mv1", IDLE_SPEED);
	animController_->Add((int)ANIM_TYPE::RUN, path + "Running.mv1", RUN_SPEED);

	//初期状態
	animController_->Play((int)ANIM_TYPE::RUN);
}
