#include <DxLib.h>
#include "StageDefault.h"

void StageDefault::Init(void)
{
	const char* FILENAME[static_cast<int>(STAGE_TYPE::MAX)]
	{
		"Data/Model/Stage/stage.mv1",
	};

	for (int pl = 0; pl < static_cast<int>(STAGE_TYPE::MAX); pl++)
	{
		// ステージを読み込む
		stage_[pl] = MV1LoadModel(FILENAME[pl]);
		if (stage_[pl] == -1)
		{
			return;
		}
	}

	type_ = STAGE_TYPE::STAGE;
}