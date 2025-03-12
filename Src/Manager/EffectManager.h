#pragma once
#include "../framework.h"
#include "../Common/Quaternion.h"
#include "../Utility/StaticSingleton.h"
#include "SoundManager.h"


class EffectManager : public StaticSingleton<EffectManager>
{
public:

	enum class EFFECT
	{
		NONE,
	};

	//初期化
	void Init();

	//追加
	void Add(const EFFECT& efc, int data);

	//再生
	void Play(const EFFECT& efc,
		const VECTOR& pos, 
		const Quaternion& qua,
		const float& size,
		const SoundManager::SOUND sound);

	//停止
	void Stop(const EFFECT& efc);

	//エフェクトの各パラメータ同期
	void SyncEffect(const EFFECT& efc, const VECTOR& pos, const Quaternion& qua, const float& size);

	//エフェクトの再生確認
	bool IsPlayEffect(const EFFECT& efc);

	//解放
	void Destroy();

private:

	//シングルトンの生成
	THIS_CLASS_IS_STATIC_SINGLETON(EffectManager);

	//エフェクトデータ格納用
	std::unordered_map<EFFECT, int> effectRes_;		//初期データ
	std::unordered_map<EFFECT, int> effectPlay_;	//再生データ
	std::unordered_map<EFFECT, int> effectMax_;		//再生データの最大所持数

	EffectManager();
	~EffectManager() = default;
};