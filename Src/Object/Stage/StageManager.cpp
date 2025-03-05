#include "StageBase.h"
#include "StageDefault.h"
#include "StageManager.h"

StageManager::StageManager()
{
	stages_.clear();
	stageSpawnCounter_ = -1;
	stageSpawn_ = -1;
}

void StageManager::Load()
{
	//�X�e�[�W�̏�����
	size_t sSize = stages_.size();
	for (int i = 0; i < sSize; i++)
	{
		stages_[i]->Release();
		delete stages_[i];
	}
}

void StageManager::Init()
{	
	//������
	stageSpawnCounter_ = 0;
	stageSpawn_ = 0;
}

void StageManager::Update()
{
	//�X�e�[�W�̍X�V�����͓��I�z��ŉ�
	//�o�����Ă���A�C�e���͂��ׂčX�V����
	size_t sSize = stages_.size();
	for (int i = 0; i < sSize; i++)
	{
		stages_[i]->Update();
	}

	//�X�e�[�W�̏o���J�E���g�𑝂₷
	++stageSpawnCounter_;

	//�o���J�E���g���w��l�𒴂�����
	if (stageSpawn_ < 3)
	{

		stageSpawnCounter_ = 0;

		//�X�e�[�W�𓮓I����
		//�|�C���^�ɉ��������Ȃ������ݒ肷��Ƃ���
		//nullptr�����悤����
		StageBase* newStage = nullptr;

		//�X�e�[�W�̐���
		int stageTypeMaxNum = static_cast<int>(StageBase::STAGE_TYPE::MAX) - 1;

		//�X�e�[�W�̃^�C�v�������_���Ō��肷��
		int newStageType = GetRand(stageTypeMaxNum);

		//enmu�Ŏg�p���邽�߂ɃX�e�[�W�̃^�C�v�ɖ߂�
		StageBase::STAGE_TYPE randType = static_cast<StageBase::STAGE_TYPE>(newStageType);

		switch (randType)
		{
		case StageBase::STAGE_TYPE::STAGE:
			newStage = new StageDefault();
			break;
		}

		newStage->Init();

		//�o�����W
		VECTOR spawnPos;

		//���[�j���O����̂��߂Ɉ�U������
		spawnPos.x = 0;
		spawnPos.y = 0;
		spawnPos.z = 0;

		//�o���ʒu�ݒ�
		switch (randType)
		{
		case StageBase::STAGE_TYPE::STAGE:
			if (sSize == 0)
			{
				spawnPos.x = 1000;
				spawnPos.y = -2000;
				spawnPos.z = 2000;
			}
			if (sSize == 1)
			{
				spawnPos.x = 1000;
				spawnPos.y = -2000;
				spawnPos.z = 2000 + StageBase::SIZE_Z;
			}
			if (sSize == 2)
			{
				spawnPos.x = 1000;
				spawnPos.y = -2000;
				spawnPos.z = 2000 + StageBase::SIZE_Z * 2;
			}
			break;
		}
		//���W�̐ݒ�
		newStage->SetPos(spawnPos);

		//���I�z��ɒǉ�
		stages_.push_back(newStage);

		stageSpawn_++;
	}
}

void StageManager::Draw()
{
	//�X�e�[�W�̕`������I�z��ł܂킷�`�ɕύX
	//�o�����Ă���A�C�e�����ׂĂ�`�悷��
	size_t sSize = stages_.size();
	for (int i = 0; i < sSize; i++)
	{
		stages_[i]->Draw();
	}
}

void StageManager::Release()
{
	for (auto& stage : stages_)
	{
		stage->Release();
		delete stage;
	}
}
