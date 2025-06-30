#pragma once
#include "Stage.h"

class TitleStage : public Stage
{
public:

	//生成数
	static constexpr int TITLE_CREATE = 1;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleStage();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleStage() override;

	/// <summary>
	/// 読み込み
	/// </summary>
	void Load() override;
};

