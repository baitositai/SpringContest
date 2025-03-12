#include "EffectManager.h"
#include "SoundManager.h"

void EffectManager::Init()
{
}

void EffectManager::Add(const EFFECT& efc, int data)
{
	//連想配列内にすでに要素が入っているかを検索
	//入っていたら処理終了
	if (effectRes_.find(efc) != effectRes_.end())return;

	//新規データのため情報を追加
	effectRes_.emplace(efc, data);
}

void EffectManager::Play(const EFFECT& efc, const VECTOR& pos, const Quaternion& qua, const float& size, const SoundManager::SOUND sound)
{
	//元データがないときは警告
	if (effectRes_.find(efc) == effectRes_.end())assert("設定していないエフェクトを再生しようとしています。");

	//再生配列内に要素が入っていないかを検索
	if (effectPlay_.find(efc) == effectPlay_.end())
	{
		//入っていないとき要素を追加する
		effectPlay_.emplace(efc, PlayEffekseer3DEffect(effectRes_[efc]));
	}
	else
	{
		//入っていたら元あるやつに上書きする
		effectPlay_[efc] = PlayEffekseer3DEffect(effectRes_[efc]);
	}

	//各種設定同期
	SyncEffect(efc, pos, qua, size);

	//効果音の再生
	if (sound != SoundManager::SOUND::NONE) {
		SoundManager::GetInstance().Play(sound);
	} 
}

void EffectManager::Stop(const EFFECT& efc)
{
	//配列内に入っていないものを停止しようとしたら警告
	if (effectPlay_.find(efc) == effectPlay_.end())assert("設定していないエフェクトを停止しようとしています。");
	//再生停止
	StopEffekseer3DEffect(effectPlay_[efc]);
}

void EffectManager::SyncEffect(const EFFECT& efc, const VECTOR& pos, const Quaternion& qua, const float& size)
{
	//その他各種設定
	//大きさ
	SetScalePlayingEffekseer3DEffect(effectPlay_[efc], size, size, size);
	//角度
	SetRotationPlayingEffekseer3DEffect(effectPlay_[efc], qua.ToEuler().x, qua.ToEuler().y, qua.ToEuler().z);
	//位置
	SetPosPlayingEffekseer3DEffect(effectPlay_[efc], pos.x, pos.y, pos.z);
}

bool EffectManager::IsPlayEffect(const EFFECT& efc)
{
	if (effectPlay_[efc] == -1 || IsEffekseer3DEffectPlaying(effectPlay_[efc]) == -1)
	{
		return true;
	}
	return false;
}

void EffectManager::Destroy()
{
	//元々のデータはリソースマネージャが持っているのでおｋ。
	effectRes_.clear();
}

EffectManager::EffectManager()
{
	Init();
}