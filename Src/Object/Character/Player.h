#pragma once
#include "../../framework.h"
#include "../Common/Transform.h"
#include "../Common/AnimationController.h"

class AnimationController;

class Player
{
public:

	//移動速度
	static constexpr float SPEED_MOVE = 5.0f;

	// ジャンプ関係
	static constexpr float JUMP_HEIGHT = 100.0f;	//高さ
	static constexpr float JUMP_SPEED = 20.0f;		//スピード
	static constexpr float RAD_PER_FRAME = 2 * DX_PI_F / 40; //1フレーム当たりのラジアン

	// ジャンプ受付時間
	static constexpr float TIME_JUMP_IN = 0.5f;

	//アニメーション速度
	static constexpr float ANIM_SPEED = 40.0f;

	//初期体力
	static constexpr int DEFAULT_LIFE = 3;

	//初期パワー
	static constexpr int DEFAULT_POWER = 4;

	//半径
	static constexpr float RADIUS = 30.0f;

	//タックル時間
	static constexpr float TACKLE_TIME = 1.5f;

	//状態
	enum class STATE
	{
		NONE,
		ALIVE,
		DEATH,
	};

	//アニメーション種類
	enum class ANIM_TYPE
	{
		NONE,
		IDLE,
		RUN,
		JUMP,
		TACKLE,
		DANCE,
		DEATH
	};

	Player();
	~Player() = default;

	void Load();
	void Init();
	void Update();
	void Draw();

	//体力を加える
	void AddLife(const int &life);

	//力を加える
	void AddPower(const int& pow);

	//タックル設定
	void SetIsTackle(const bool& isTackle);

	//力を返す
	inline const int& GetPower() const { return pow_; }

	//タックル判定を返す
	inline const bool& IsTackle() const { return isTackle_; }
	
	//衝突判定用半径を返す
	inline const float& GetRadius() const { return radius_; }

	//状態を返す
	inline const STATE& GetState() const { return state_; }

	//トランスフォームを返す
	inline const Transform& GetTransform(void) const { return trans_; }

	//デバッグ描画
	void DebagDraw();

private:

	//状態
	STATE state_;

	//移動速度
	float moveSpeed_;

	// ジャンプ判定
	bool isJump_;

	// ジャンプの入力受付時間
	float stepJump_;

	//タックルパワー
	int pow_;

	//体力
	int life_;

	//衝突判定用半径
	float radius_;

	//タックル判定
	bool isTackle_;

	//タックル時間
	float tackleTime_;

	//トランスフォーム
	Transform trans_;

	// 状態管理(状態遷移時初期処理)
	std::map<STATE, std::function<void(void)>> stateChanges_;

	// 状態管理(更新ステップ)
	std::function<void(void)> stateUpdate_;

	// アニメーション
	std::unique_ptr<AnimationController> animationController_;

	// 状態遷移
	void ChangeState(STATE state);
	void ChangeStateNone(void);
	void ChangeStateAlive(void);
	void ChangeStateDeath(void);

	// 更新ステップ
	void UpdateNone(void);
	void UpdateAlive(void);
	void UpdateDeath(void);

	//各種初期設定
	void InitModel(void);
	void InitAnimation(void);

	//操作処理
	void Process(void);

	//ジャンプ
	void Jump(void);

	//タックル
	void Tackle();
};

