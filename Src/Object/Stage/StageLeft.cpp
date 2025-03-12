#include "StageLeft.h"

void StageLeft::Init(void)
{
	//const char* FILENAME[static_cast<int>(STAGE_TYPE::MAX)]
	//{
	//	"Data/Model/Stage/stageLeft.mv1"
	//};

	//for (int pl = 0; pl < static_cast<int>(STAGE_TYPE::MAX); pl++)
	//{
	//	// ステージを読み込む
	//	stage_[pl] = MV1LoadModel(FILENAME[pl]);
	//	if (stage_[pl] == -1)
	//	{
	//		return;
	//	}
	//}

	transform_.SetModel(ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::STAGELEFT));
	transform_.Update();
	/*type_ = STAGE_TYPE::STAGELEFT;*/
}
