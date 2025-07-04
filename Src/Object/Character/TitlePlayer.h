#pragma once
#include "../../framework.h"
#include "../Common/Transform.h"
#include "../Common/AnimationController.h"

class AnimationController;

class TitlePlayer
{
public:

	//アニメーション種類
	enum class ANIM_TYPE
	{
		NONE,
		IDLE,
		RUN,
	};
	//位置
	static constexpr VECTOR POS = { 500,100,-100 };

	//スケール
	static constexpr VECTOR SCALE = { 1.f,1.f,1.f };

	//アニメーション速度
	static constexpr float IDLE_SPEED = 10.0f;
	static constexpr float RUN_SPEED = 40.0f;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitlePlayer();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitlePlayer() = default;

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

	//トランスフォーム
	Transform trans_;
	
	//アニメーションコントローラー
	std::unique_ptr< AnimationController> animController_;
	
	//アニメーション設定
	void InitAnim();
};
