#pragma once
#include "../../framework.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Utility/Utility.h"
#include "../Common/Transform.h"

class SkyDome
{
public:

	static constexpr float ROT_SPEED = 0.01f;

	// 状態
	enum class STATE
	{
		NONE,
		STAY,
		FOLLOW
	};

	//スケールサイズ
	static constexpr VECTOR SCALE = { 100.0f, 100.0f, 100.0f };

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SkyDome();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SkyDome() = default;

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

private:

	//モデル読み込み
	void SetModel();

	//トランスフォーム
	Transform transform_;

	// 状態
	STATE state_;

	// 状態管理(状態遷移時初期処理)
	std::map<STATE, std::function<void()>> stateChanges_;

	// 状態管理(更新ステップ)
	std::function<void()> stateUpdate_;

	// 状態遷移
	void ChangeState(STATE state);
	void ChangeStateNone();
	void ChangeStateStay();
	void ChangeStateFollow();

	// 更新ステップ
	void UpdateNone();
	void UpdateStay();
	void UpdateFollow();

};