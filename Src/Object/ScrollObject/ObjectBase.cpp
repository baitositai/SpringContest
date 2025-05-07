#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/ScrollManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Manager/DataBank.h"
#include "../../Utility/Utility.h"
#include "../Character/Player.h"
#include "ObjectBase.h"

ObjectBase::ObjectBase()
	: resMng_(ResourceManager::GetInstance()),
	scnMng_(SceneManager::GetInstance())
{
	state_ = STATE::NONE;
	color_ = -1;
	radius_ = -1.0f;

	stateChanges_.emplace(STATE::NONE, std::bind(&ObjectBase::ChangeStateNone, this));
	stateChanges_.emplace(STATE::SCROLL, std::bind(&ObjectBase::ChangeStateScroll, this));
	stateChanges_.emplace(STATE::HIT, std::bind(&ObjectBase::ChangeStateHit, this));
}

void ObjectBase::Load(void)
{
	//デバッグ用カラー
	color_ = 0xffff00;

	//モデルの初期化
	InitModel();

	//音楽の読み込み
	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::ITEM_GET_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ITEM_GET_SE).handleId_);

	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::BLAST_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::BLAST_SE).handleId_);

	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::ENEMY_DAMAGE_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::ENEMY_DAMAGE_SE).handleId_);

}

void ObjectBase::Init()
{
	//半径の設定
	radius_ = DEFAULT_RADIUS;

	//状態遷移
	ChangeState(STATE::NONE);
}

void ObjectBase::Update()
{
	// 更新ステップ
	stateUpdate_();

	//トランスフォームを更新
	transform_.Update();
}

void ObjectBase::Draw()
{
	if (state_ == STATE::NONE) { return; }	//非スクロール状態の場合描画しない
}

void ObjectBase::Release()
{
	SoundManager::GetInstance().Stop(SoundManager::SOUND::ENEMY_DAMAGE_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::BLAST_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::ITEM_GET_SE);
}

void ObjectBase::ChangeState(STATE state)
{
	// 状態変更
	state_ = state;

	// 各状態遷移の初期処理
	stateChanges_[state_]();
}

void ObjectBase::ChangeStateNone()
{
	stateUpdate_ = std::bind(&ObjectBase::UpdateNone, this);
}

void ObjectBase::ChangeStateScroll()
{
	//位置を決める
	DecideRandPos();

	stateUpdate_ = std::bind(&ObjectBase::UpdateScroll, this);
}

void ObjectBase::ChangeStateHit()
{
	stateUpdate_ = std::bind(&ObjectBase::UpdateHit, this);
}

void ObjectBase::UpdateNone()
{
	//この状態のときは何も処理をしない
}

void ObjectBase::UpdateScroll()
{
	//スクロール
	auto& scr = ScrollManager::GetInstance();
	//Z値を減らしていく
	transform_.pos.z -= scr.GetScrollSpeed(DataBank::GetInstance().Output().playerId_);
}

void ObjectBase::UpdateHit()
{
	//状態を変える
	ChangeState(STATE::NONE);
}

void ObjectBase::DecideRandPos()
{
	// 乱数で X 座標を決定
	float posX = static_cast<float>(ScrollManager::MOVE_LIMIT_LEFT + GetRand(
		static_cast<int>(ScrollManager::MOVE_LIMIT_RIGHT - ScrollManager::MOVE_LIMIT_LEFT)));

	// Z 座標を固定値で設定
	transform_.pos = { posX, 0.0f, ScrollManager::SCROLL_START_LINE };
}
