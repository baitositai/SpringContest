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

	//入手アニメーション総数
	static constexpr int GET_ANIM_MAX = 35;

	//エフェクト速度
	static constexpr float EFK_SPEED = 1.0f;

	//エフェクトの拡大率
	static constexpr float EFK_RATE = 2.0f;

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

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player() = default;

	/// <summary>
	/// 読み込み
	/// </summary>
	void Load();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 解放
	/// </summary>
	void Release();

	/// <summary>
	/// 体力を加える
	/// </summary>
	/// <param name="life"></param>追加ライフ
	void AddLife(const int life);

	/// <summary>
	/// パワーを加える
	/// </summary>
	/// <param name="pow"></param>追加パワー
	void AddPower(const int pow);	
	
	/// <summary>
	/// 状態の変更
	/// </summary>
	/// <param name="state"></param>変更先の状態
	void ChangeState(const STATE state);

	/// <summary>
	/// 生存時の状態の変更
	/// </summary>
	/// <param name="state"></param>変更先の状態
	void ChangeAliveState(const ALIVE_STATE state);

	/// <summary>
	/// キーの設定
	/// </summary>
	/// <param name="right"></param>右移動
	/// <param name="left"></param>左移動
	/// <param name="jump"></param>ジャンプ
	/// <param name="tackle"></param>攻撃
	void SetKey(
		const int right, 
		const int left, 
		const int jump, 
		const int tackle);

	/// <summary>
	/// ライフを返す
	/// </summary>
	/// <returns></returns>ライフ
	inline const int& GetLife() const { return life_; }

	/// <summary>
	/// パワーを返す
	/// </summary>
	/// <returns></returns>パワー
	inline const int& GetPower() const { return pow_; }
	
	/// <summary>
	/// 衝突判定用半径を返す
	/// </summary>
	/// <returns></returns>半径
	inline const float& GetRadius() const { return radius_; }

	/// <summary>
	/// タックル時間を返す
	/// </summary>
	/// <returns></returns>タックル時間
	inline const float& GetTackleTime() const { return tackleTime_; }

	/// <summary>
	/// 状態を返す
	/// </summary>
	/// <returns></returns>状態
	inline const STATE& GetState() const { return state_; }

	/// <summary>
	/// 生存状態を返す
	/// </summary>
	/// <returns></returns>生存状態
	inline const ALIVE_STATE& GetAliveState() const { return aliveState_; }

	/// <summary>
	/// トランスフォームを返す
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>トランスフォーム
	inline const Transform& GetTransform(void) const { return trans_; }

	/// <summary>
	/// デバッグ描画
	/// </summary>
	void DebagDraw(); 

private:

	//エフェクト用画像
	int* imgTackleEfk_;
	int* imgHitEfk_;

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
	std::map<STATE, std::function<void()>> stateChanges_;
	std::map<ALIVE_STATE, std::function<void()>> aliveStateChanges_;

	// 状態管理(更新ステップ)
	std::function<void()> stateUpdate_;
	std::function<void()> aliveStateUpdate_;

	// アニメーション
	std::unique_ptr<AnimationController> animationController_;

	// 状態遷移
	void ChangeStateNone();
	void ChangeStateAlive();
	void ChangeStateDeath();
	void ChangeStateWin();

	void ChangeAliveStateRun();
	void ChangeAliveStateTackle();
	void ChangeAliveStateDamage();

	// 更新ステップ
	void UpdateNone();
	void UpdateAlive();
	void UpdateDeath();
	void UpdateWin();

	//各種初期設定
	void InitModel();
	void InitAnimation();

	//操作処理
	void Process();

	//ジャンプ
	void Jump();

	//生存状態別の更新処理
	void Run();
	void Tackle();
	void Damage();
};

