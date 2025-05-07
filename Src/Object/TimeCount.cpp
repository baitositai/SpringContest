#include "../Application.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/DataBank.h"
#include "../Manager/ScoreBank.h"
#include "../Manager/ScrollManager.h"
#include "TimeCount.h"

TimeCount::TimeCount()
{
	step_ = -1.0f;
	preStep_ = -1;
	scrCnt_ = -1.0f;
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

	//���x�㏸UI
	speedUi_ = std::make_unique<DrawSpeedUp>();
	speedUi_->Load();
}

void TimeCount::Init()
{
	//������
	step_ = 0.0f;
	preStep_ = 1;
	scrCnt_ = ScrollManager::SPEED_UP_TIME;

	//���[�h���Ƃɕ`��ʒu��ύX
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS) { posY_ = VS_TIMER_POS_Y; }	
	else { posY_ = TIMER_POS_Y; }

	//���x�㏸UI
	speedUi_->Init();
}

void TimeCount::Update()
{
	float cnt = SceneManager::GetInstance().GetDeltaTime();
	int playNum = DataBank::GetInstance().Output().playerNum_;

	//�J�E���g�X�V
	step_ += cnt;
	scrCnt_ -= cnt;

	//1�b���ƂɃX�R�A�㏸
	if (static_cast<int>(step_) != preStep_)
	{
		preStep_ = static_cast<int>(step_);
		for (int i = 0; i < playNum; i++) {
			ScoreBank::GetInstance().AddScore(i, ADD_SCORE);
		}
	}

	//�X�s�[�h�A�b�v
	if (scrCnt_ <= 0.0f)
	{
		//���x�A�b�v
		for (int i = 0; i < playNum; i++) {
			ScrollManager::GetInstance().ChangeScrollSpeed(i, ScrollManager::ACC_SPEED);
		}

		//���x�㏸UI��ԕύX
		speedUi_->ChangeState(DrawSpeedUp::STATE::EXPAND);

		//�J�E���g������
		scrCnt_ = ScrollManager::SPEED_UP_TIME;
	}

	//���x�㏸UI
	speedUi_->Update();
}

void TimeCount::Draw()
{
	//�X�s�[�h�A�b�v�`��
	speedUi_->Draw();
}

void TimeCount::Release()
{
	speedUi_->Release();
}

void TimeCount::CommonDraw()
{
	//�^�C�}�[�`��
	int min = static_cast<int>(step_) / SECONDS_PER_MINUTE;
	int sec = static_cast<int>(step_) % SECONDS_PER_MINUTE;

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
