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
	void InitAnimation(void);
	void Draw() override;
	void OnCollision(Player& player) override;

private:

	// アニメーション
	std::unique_ptr<AnimationController> animationController_;

	//カウンタ
	float cnt_;

	//向き決定用
	float moveDirX_;
};

