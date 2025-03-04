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

	Enemy();
	~Enemy();

	void InitModel() override;
	void Load() override;
	void Update()override;
	void UpdateHit(void) override;
	void Draw() override;	
	void OnCollision(Player& player) override;

	//アニメーションの初期化処理
	void InitAnimation(void);

	//衝突アニメーション関係の初期化
	void ResetHitAnim();

private:

	// アニメーション
	std::unique_ptr<AnimationController> animationController_;

	//カウンタ
	float cnt_;

	//向き決定用
	float moveDirX_;
};

