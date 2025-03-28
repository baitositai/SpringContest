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

	//ダメージ時間
	static constexpr float DAMAGE_TIME = 2.0f;

	//タックルエフェクトの相対座標
	static constexpr VECTOR TACKLE_EFK_LOCAL_POS = { 0,100,100 };

	//タックルのエフェクトサイズ
	static constexpr float TACKLE_FEK_SIZE = 10.0f;

	//状態
	enum class STATE
	{
		NONE,
		ALIVE,
		DEATH,
		WIN,
	};

	//プレイヤーの生存状態
	enum class ALIVE_STATE
	{
		NONE,
		RUN,
		TACKLE,
		DAMAGE
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

	//引数で初期位置を取得
	Player();
	~Player();

	void Load();
	void Init();
	void Update();
	void Draw();
	void Release();

	//体力を加える
	void AddLife(const int &life);

	//力を加える
	void AddPower(const int& pow);	
	
	//状態の変更
	void ChangeState(STATE state);

	//生存状態の変更
	void ChangeAliveState(const ALIVE_STATE & state);

	//操作キーの設定
	void SetKey(
		const int& right, 
		const int& left, 
		const int& jump, 
		const int& tackle);

	//体力を返す
	inline const int& GetLife() const { return life_; }

	//力を返す
	inline const int& GetPower() const { return pow_; }
	
	//衝突判定用半径を返す
	inline const float& GetRadius() const { return radius_; }

	//状態を返す
	inline const STATE& GetState() const { return state_; }

	//生存状態を返す
	inline const ALIVE_STATE& GetAliveState() const { return aliveState_; }

	//トランスフォームを返す
	inline const Transform& GetTransform(void) const { return trans_; }

	//デバッグ描画
	void DebagDraw(); 

private:

	//操作キー
	struct Key
	{
		int right_;
		int left_;
		int jump_;
		int tackle_;
	};

	//状態
	STATE state_;

	//生存状態
	ALIVE_STATE aliveState_;

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

	//タックル時間
	float tackleTime_;

	//ダメージ時間
	float damageTime_;

	//トランスフォーム
	Transform trans_;

	//キー
	Key key_;

	// 状態管理(状態遷移時初期処理)
	std::map<STATE, std::function<void(void)>> stateChanges_;
	std::map<ALIVE_STATE, std::function<void(void)>> aliveStateChanges_;

	// 状態管理(更新ステップ)
	std::function<void(void)> stateUpdate_;
	std::function<void(void)> aliveStateUpdate_;

	// アニメーション
	std::unique_ptr<AnimationController> animationController_;

	// 状態遷移
	void ChangeStateNone(void);
	void ChangeStateAlive(void);
	void ChangeStateDeath(void);
	void ChangeStateWin(void);

	void ChanageAliveStateRun();
	void ChanageAliveStateTackle();
	void ChanageAliveStateDamage();

	// 更新ステップ
	void UpdateNone(void);
	void UpdateAlive(void);
	void UpdateDeath(void);
	void UpdateWin(void);

	//各種初期設定
	void InitModel(void);
	void InitAnimation(void);

	//操作処理
	void Process(void);

	//ジャンプ
	void Jump(void);

	//生存状態別の更新処理
	void Run();
	void Tackle();
	void Damage();
};

