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
	//�X�e�[�W�̃T�C�Y���`
	stages_.resize(TITLE_CREATE);

	//���f���̏�����
	for (int i = 0; i < TITLE_CREATE; i++)
	{
		stages_[i].SetModel(ResourceManager::GetInstance().LoadModelDuplicate(
			ResourceManager::SRC::STAGE));
	}
}
