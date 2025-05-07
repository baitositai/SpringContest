#include "Effect2DManager.h"
#include "../Utility/Utility.h"

Effect2DManager::Effect2DManager()
{
	//データの初期化
	effects_.clear();
}

void Effect2DManager::Update()
{
	//中身がない場合処理を終える
	if (effects_.empty()) { return; }

	//アニメーション更新
	for (auto it = effects_.begin(); it != effects_.end(); ++it) 
	{
		//アニメーションを再生済みか
		if (!it->second.isPlay_)
		{ 
			continue;//再生してない場合次へ
		}	
		//更新処理
		it->second.step_++;

		//アニメーション番号のアタッチ
		it->second.animNum_ = static_cast<int>(it->second.step_ / it->second.animSpeed_) % it->second.animMax_;

		//アニメーションの終了確認
		if (it->second.animNum_ >= it->second.animMax_ - 1) { Stop(it->first); }
	}
}

void Effect2DManager::Add(const EFFECT& efc, int* image, const int& animMax, const float & animSpeed)
{	
	//エフェクトデータ
	Efc data = { image, animMax,0,animSpeed, Utility::VECTOR_ZERO, 1.0f,0.0f,0.0f,false };

	//連想配列内にすでに要素が入っているかを検索
	//入っていたら処理終了
	if (effects_.find(efc) != effects_.end()) { return; }

	//新規データのため情報を追加
	effects_.emplace(efc, data);
}

void Effect2DManager::Play(const EFFECT& efc, const VECTOR& pos, const float& rate, const float& angle, const SoundManager::SOUND& sound)
{
	//元データがないときは警告
	if (effects_.find(efc) == effects_.end())assert("設定していないエフェクトを再生しようとしています。");

	//再生中か確認
	if (effects_[efc].isPlay_) { Stop(efc); }	//再生中の場合は初期化させてから再生する

	//再生開始
	effects_[efc].isPlay_ = true;

	//各種設定同期
	Sync(efc, pos, rate, angle);

	//効果音の再生
	if (sound != SoundManager::SOUND::NONE)
	{
		SoundManager::GetInstance().Play(sound);
	}
}

void Effect2DManager::Sync(const EFFECT& efc, const VECTOR& pos, const float& rate, const float& angle)
{
	effects_[efc].pos_ = pos;
	effects_[efc].rate_ = rate;
	effects_[efc].angle_ = angle;
}

void Effect2DManager::Stop(const EFFECT& efc)
{
	//再生停止
	effects_[efc].isPlay_ = false;

	//情報を初期化する
	effects_[efc].pos_ = Utility::VECTOR_ZERO;
	effects_[efc].rate_ = 1.0f;;
	effects_[efc].angle_ = 0.0f;
	effects_[efc].step_ = 0.0f;
	effects_[efc].animNum_ = 0;
}

void Effect2DManager::Destroy()
{
	//データの初期化
	effects_.clear();
}

void Effect2DManager::DrawScreenEffect(const EFFECT& efc)
{
	//再生中か確認
	if (!effects_[efc].isPlay_) { return; }

	//スクリーン座標にする
	VECTOR pos = ConvWorldPosToScreenPos(effects_[efc].pos_);

	DrawRotaGraph(
		static_cast<int>(pos.x),
		static_cast<int>(pos.y),
		effects_[efc].rate_,
		effects_[efc].angle_,
		effects_[efc].image_[effects_[efc].animNum_],
		true,
		false);
}

void Effect2DManager::DrawBillboard(const EFFECT& efc)
{
	//再生中か確認
	if (!effects_[efc].isPlay_) { return; }

	DrawBillboard3D(
		effects_[efc].pos_,
		CENTER, CENTER,
		effects_[efc].rate_,
		0.0f,
		effects_[efc].image_[(int)effects_[efc].animNum_],
		true,
		false);
}
