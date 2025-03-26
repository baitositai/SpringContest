#include "StageBase.h"
#include "StageDefault.h"
#include "StageManager.h"
#include "StageLeft.h"
#include "StageRight.h"

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
	/*	case StageBase::STAGE_TYPE::STAGELEFT:
			newStage = new StageLeft();
			break;
		case StageBase::STAGE_TYPE::STAGERIGHT:
			newStage = new StageRight();
			break;*/
		}

		newStage->Init();

		//�o�����W
		Transform spawnPos = newStage->GetTransform();
		

		//���[�j���O����̂��߂Ɉ�U������
		spawnPos.pos.x = 0;
		spawnPos.pos.y = 0;
		spawnPos.pos.z = 0;

		//�o���ʒu�ݒ�
		switch (randType)
		{
		case StageBase::STAGE_TYPE::STAGE:
			if (sSize == 0)
			{
				spawnPos.pos.x = 1000;
				spawnPos.pos.y = -1000;
				spawnPos.pos.z = 2000;
			}
			if (sSize == 1)
			{
				spawnPos.pos.x = 1000;
				spawnPos.pos.y = -1000;
				spawnPos.pos.z = 2000 + StageBase::SIZE_Z;
			}
			if (sSize == 2)
			{
				spawnPos.pos.x = 1000;
				spawnPos.pos.y = -1000;
				spawnPos.pos.z = 2000 + StageBase::SIZE_Z * 2;
			}
			break;
		}

		//���W�̐ݒ�
		newStage->SetPos(spawnPos);

		//���I�z��ɒǉ�
		stages_.push_back(newStage);

		stageSpawn_++;
	}

	CheckStagePos();
	
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

void StageManager::CheckStagePos()
{

	//�o�����Ă���X�e�[�W���ׂĂ��m�F����
	size_t sSize = stages_.size();
	for (int i = 0; i < sSize; i++)
	{
		if (stages_[i]->GetTransform().pos.z + StageBase::SIZE_Z < 0)
		{
			stages_.erase(stages_.begin() + i);
			sSize--;
			stageSpawn_--;
		}
	}

}
