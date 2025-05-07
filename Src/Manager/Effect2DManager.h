#pragma once
#include "../framework.h"
#include "SoundManager.h"


class Effect2DManager
{
public:

	//エフェクトのアニメーション速度
	static constexpr float DEFAULT_ANIM_SPEED = 3.0f;

	//中心に合わせるよう
	static constexpr float CENTER = 0.5f;

	enum class EFFECT
	{
		NONE,
		TACKLE,
		DAMAGE,
		GET,
		BLAST,
	};	
	
	Effect2DManager();
	~Effect2DManager() = default;

	//更新処理
	void Update();

	/// <summary>
	/// 追加
	/// </summary>
	/// <param name="efc"></param>種類
	/// <param name="image"></param>リソース
	/// <param name="animMax"></param>アニメーション総数
	/// <param name="animSpeed"></param>アニメーション速度
	void Add(
		const EFFECT& efc, 
		int* image,
		const int& animMax,
		const float& animSpeed = DEFAULT_ANIM_SPEED);

	/// <summary>
	/// 再生
	/// </summary>
	/// <param name="efc"></param>種類
	/// <param name="pos"></param>座標
	/// <param name="rate"></param>拡大率
	/// <param name="angle"></param>角度
	/// <param name="sound"></param>サウンド
	void Play(
		const EFFECT& efc,
		const VECTOR& pos,
		const float& rate = 1.0f,
		const float& angle = 0.0f,
		const SoundManager::SOUND& sound = SoundManager::SOUND::NONE);

	/// <summary>
	/// エフェクトの同期
	/// </summary>
	/// <param name="efc"></param>種類
	/// <param name="pos"></param>座標
	/// <param name="rate"></param>拡大率
	/// <param name="angle"></param>角度
	void Sync(
		const EFFECT& efc, 
		const VECTOR& pos,
		const float& rate = 1.0f,
		const float& angle =0.0f);	
	
	/// <summary>
	/// 停止
	/// </summary>
	/// <param name="efc"></param>エフェクトタイプ
	void Stop(const EFFECT& efc);

	//解放
	void Destroy();

	/// <summary>
	/// エフェクトのスクリーン描画
	/// </summary>
	/// <param name="efc"></param>種類
	void DrawScreenEffect(const EFFECT& efc);

	/// <summary>
	/// ビルボード描画
	/// </summary>
	/// <param name="efc"></param>種類
	void DrawBillboard(const EFFECT& efc);

	/// <summary>
	/// エフェクトの再生確認
	/// </summary>
	/// <param name="efc"></param>種類
	/// <returns></returns>再生中ならtrue,違う場合false
	inline const bool IsPlayEffect(const EFFECT& efc) { return effects_[efc].isPlay_; }

private:

	struct Efc
	{
		int* image_;	//画像	
		int animMax_;	//アニメーション総数
		int animNum_;	//現在のアニメーション番号
		float animSpeed_;	//アニメーション速度
		VECTOR pos_;	//座標位置
		float rate_;	//拡大率
		float angle_;	//角度		
		float step_;	//更新用ステップ
		bool isPlay_;	//開始
	};

	//エフェクトデータ格納用
	std::unordered_map<EFFECT, Efc> effects_;	//エフェクトデータ

};

