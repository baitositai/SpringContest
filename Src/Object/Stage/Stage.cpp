#include "../../Manager/ResourceManager.h"
#include "../../Manager/ScrollManager.h"
#include "../../Manager/DataBank.h"
#include "../../Utility/Utility.h"
#include "Stage.h"

Stage::Stage()
{
	stages_.clear();
}

Stage::~Stage()
{
}

void Stage::Load()
{
	//�X�e�[�W�̃T�C�Y���`
	stages_.resize(CREATES);

	//���f���̏�����
	for (int i = 0; i < CREATES; i++) 
	{
		stages_[i].SetModel(ResourceManager::GetInstance().LoadModelDuplicate(
			ResourceManager::SRC::STAGE));
	}
}

void Stage::Init()
{
	//������
	int i = 0;
	for (Transform& stage : stages_)
	{
		stage.scl = SCLAE;
		stage.pos = DEFAULT_POS[i];
		stage.quaRot = Quaternion();
		stage.quaRotLocal =
			Quaternion::Euler({ 0.0f, Utility::Deg2RadF(180.0f), 0.0f });
		stage.Update();
		i++;
	}
}

void Stage::Update()
{
	ScrollManager& scr = ScrollManager::GetInstance();

	//�X�V����
	for (Transform& stage : stages_)
	{
		//�ړ�����
		stage.pos.z -= scr.GetScrollSpeed(DataBank::GetInstance().Output().playerId_);

		//���n�_�܂ŒB������
		if (stage.pos.z <= ScrollManager::SCROLL_FINISH_LINE)
		{
			stage.pos.z = DEFAULT_POS[CREATES - 1].z;
		}

		//�g�����X�t�H�[���̍X�V
		stage.Update();
	}
}

void Stage::Draw()
{
	//�`�揈��
	for (Transform& stage : stages_)
	{
		MV1DrawModel(stage.modelId);
	}
}
