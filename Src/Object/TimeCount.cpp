#include "../Application.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/DataBank.h"
#include "TimeCount.h"

TimeCount::TimeCount()
{
	step_ = -1.0f;
	int i = -1;
	imgNums_ = &i;
	imgTimerGage_ = -1;
	posY_ = -1;
}

void TimeCount::Load()
{
	//�摜�ǂݍ���
	auto& res = ResourceManager::GetInstance();
	imgTimerGage_ = res.Load(ResourceManager::SRC::TIMER_UI).handleId_;
	imgNums_ = res.Load(ResourceManager::SRC::NUMBER).handleIds_;
}

void TimeCount::Init()
{
	//������
	step_ = 0.0f;

	//���[�h���Ƃɕ`��ʒu��ύX
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS) { posY_ = VS_TIMER_POS_Y; }	
	else { posY_ = TIMER_POS_Y; }
}

void TimeCount::Update()
{
	//���Ԍo��
	step_ += SceneManager::GetInstance().GetDeltaTime();
}

void TimeCount::Draw()
{
	int min = static_cast<int>(step_) / 60;
	int sec = static_cast<int>(step_) % 60;

	int timeNum[TIME_DIGITS] = {
		min / 10,
		min % 10,
		sec / 10,
		sec % 10
	};

	//�^�C�}�[�Q�[�W�̕`��
	DrawRotaGraph(
		Application::SCREEN_HALF_X,
		posY_,
		1.0f,
		0.0f,
		imgTimerGage_,
		true,
		false);

	//����
	for (int i = 0; i < TIME_DIGITS; i++)
	{
		DrawRotaGraph(
			TIME_CNTS_POS_X[i],
			posY_,
			TIME_RATE,
			0.0f,
			imgNums_[timeNum[i]],
			true,
			false);
	}
}

void TimeCount::Release()
{
}
