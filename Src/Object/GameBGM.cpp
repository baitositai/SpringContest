#include "../Manager/ResourceManager.h"
#include "GameBGM.h"

GameBGM::GameBGM()
{
	soundType_ = SoundManager::SOUND::NONE;
}

void GameBGM::Load()
{
	//�����_���Ō���
	int rand = GetRand(PERCENT);
	ResourceManager::SRC src = ResourceManager::SRC::GAMEBGM1;
	soundType_ = SoundManager::SOUND::GAMEBGM1;
	if (rand == 0) { soundType_ = SoundManager::SOUND::GAMEBGM2; src = ResourceManager::SRC::GAMEBGM2; }

	//���y�̓ǂݍ���
	SoundManager::GetInstance().Add(
		SoundManager::TYPE::BGM,
		soundType_,
		ResourceManager::GetInstance().Load(src).handleId_);

	//���ʒ���
	SoundManager::GetInstance().AdjustVolume(soundType_, VOLUME);
}

void GameBGM::Init()
{
	//�Đ�
	SoundManager::GetInstance().Play(soundType_);
}

void GameBGM::Stop()
{
	//��~
	SoundManager::GetInstance().Stop(soundType_);
}

void GameBGM::Release()
{	
	SoundManager::GetInstance().Stop(SoundManager::SOUND::GAMEBGM1);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::GAMEBGM2);	
}
