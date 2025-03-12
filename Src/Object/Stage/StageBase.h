#pragma once
#include <DxLib.h>
#include "../Common/Transform.h"
#include "../../Manager/ResourceManager.h"


class StageBase
{
public:

	static constexpr float SIZE_Z = 7214.318;

	enum class STAGE_TYPE
	{
		STAGE,			//通常ステージ
		STAGERIGHT,		//足場右側だけ
		STAGELEFT,		//足場左側だけ
		MAX
	};

	//コンストラクタ・デストラクタ
	StageBase(void);
	~StageBase(void);

	virtual void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
	Transform GetTransform(void);
	void SetPos(Transform pos);

protected:

	//ステージ
	int stage_[static_cast<int>(STAGE_TYPE::MAX)];

	//ステージタイプ
	STAGE_TYPE type_;

	//座標
	Transform transform_;

};
