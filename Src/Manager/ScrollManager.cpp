#include "SceneManager.h"
#include "DataBank.h"
#include "ScrollManager.h"

ScrollManager::ScrollManager()
{
	Init();
}

void ScrollManager::Init()
{
	//������
	step_ = 0.0f;

	//���R���[�����x�̏�����
	scrollSpeed_.clear();

	//�v���C���[�̐������X�N���[���X�s�[�h���m��
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS)
	{
		scrollSpeed_.resize(SceneManager::PLAYER_MAX, DEFAULRT_SCROLL_SPEED);
	}
	else
	{
		scrollSpeed_.emplace_back(DEFAULRT_SCROLL_SPEED);
	}
}

void ScrollManager::ChangeScrollSpeed(const int playerId, const float speed)
{
	scrollSpeed_[playerId] += speed;
	
	//�Œᑬ�x�������Ȃ��悤�ɂ���
	if (scrollSpeed_[playerId] < DEFAULRT_SCROLL_SPEED)
	{ 
		scrollSpeed_[playerId] = DEFAULRT_SCROLL_SPEED; 
	}

	//�ō����x������Ȃ��悤�ɂ���
	else if (scrollSpeed_[playerId] > MAX_SCROLL_SPEED) 
	{ 
		scrollSpeed_[playerId] = MAX_SCROLL_SPEED; 
	}
}
