#pragma once
#include "ObjectBase.h"

class AnimationController;

class Enemy : public ObjectBase
{
public:

	//スケール
	static constexpr VECTOR SCALE = { 0.8f,0.8f ,0.8f };

	//ダメージ
	static constexpr int DAMAGE = -1;

	//パワー消費量
	static constexpr int POWER_CONSUME = -1;

	//スコア量
	static constexpr int HIT_SCORE = 300;
	static constexpr int DAMAGE_SCORE = -500;

	//アニメーション速度
	static constexpr float ANIM_SPEED = 40.0f;

	//吹っ飛び速度
	static constexpr float SMASH_SPEED = 5.0f;

	//チェンジ時間
	static constexpr float CHANGE_SECOND = 1.5f;


	//アニメーション種類
	enum class ANIM_TYPE
	{
		NONE,
		IDLE,
		RUN,
		DEATH
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

	/// <summary>
	/// モデル初期化
	/// </summary>
	void InitModel() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	void Load() override;

	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;

	/// <summary>
	/// 諸突後の更新
	/// </summary>
	/// <param name=""></param>
	void UpdateHit(void) override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;	

	/// <summary>
	/// 衝突後の処理
	/// </summary>
	/// <param name="player"></param>プレイヤー
	void OnCollision(Player& player) override;

	/// <summary>
	/// アニメーション初期化
	/// </summary>
	/// <param name=""></param>
	void InitAnimation(void);

	/// <summary>
	/// アニメーションの初期化
	/// </summary>
	void ResetHitAnim();

private:

	// アニメーション
	std::unique_ptr<AnimationController> animationController_;

	//カウンタ
	float cnt_;

	//向き決定用
	float moveDirX_;
};

