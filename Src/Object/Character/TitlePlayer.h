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
		DANCE,
	};

	//スケール
	static constexpr VECTOR SCALE = { 1.f,1.f,1.f };

	TitlePlayer();
	~TitlePlayer();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	//トランスフォーム
	Transform trans_;
	
	//アニメーションコントローラー
	std::unique_ptr< AnimationController> animController_;
	
	//アニメーション設定
	void InitAnim();
};
