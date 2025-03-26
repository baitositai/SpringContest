#include "CountDown.h"
#include "../Application.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"



CountDown::CountDown()
{
	cnt_ = -1.0f;
	isStart_ = false;
}

void CountDown::Load()
{
	auto& res = ResourceManager::GetInstance();
	imgNums_ = res.Load(ResourceManager::SRC::NUMBER).handleIds_;
}

void CountDown::Init()
{
	//�J�E���g�_�E���ݒ�
	cnt_ = COUNTDOWN;
}

void CountDown::Update()
{
	//�J�E���g�_�E��
	cnt_ -= SceneManager::GetInstance().GetDeltaTime();

	//�J�E���g��0�ȉ��ɂȂ�����I��
	if (cnt_ <= 0.0f) { isStart_ = true; }
}

void CountDown::Draw()
{
	//�`��
	DrawRotaGraph(
		Application::SCREEN_HALF_X,
		Application::SCREEN_HALF_Y,
		1.0f,
		0.0f,
		imgNums_[static_cast<int>(cnt_)],
		true,
		false);
}

void CountDown::Release()
{
}
