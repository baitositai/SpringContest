#include "TitleStage.h"
#include "../../Manager/ResourceManager.h"

TitleStage::TitleStage()
{
}

TitleStage::~TitleStage()
{
}

void TitleStage::Load()
{
	//ステージのサイズを定義
	stages_.resize(TITLE_CREATE);

	//モデルの初期化
	for (int i = 0; i < TITLE_CREATE; i++)
	{
		stages_[i].SetModel(ResourceManager::GetInstance().LoadModelDuplicate(
			ResourceManager::SRC::STAGE));
	}
}
