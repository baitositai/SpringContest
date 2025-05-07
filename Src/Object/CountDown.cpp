#include "CountDown.h"
#include "../Application.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/SceneManager.h"

CountDown::CountDown()
{
	cnt_ = -1.0f;
	seCnt_ = -1;
	isStart_ = false;

	int i = -1;
	imgNums_ = &i;
}

void CountDown::Load()
{
	auto& res = ResourceManager::GetInstance();
	auto& snd = SoundManager::GetInstance();

	//画像の読み込み
	imgNums_ = res.Load(ResourceManager::SRC::NUMBER).handleIds_;

	//音声の読み込み
	snd.Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::COUNT_0,
		res.Load(ResourceManager::SRC::COUNT_0).handleId_);
	snd.Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::COUNT_1,
		res.Load(ResourceManager::SRC::COUNT_1).handleId_);
	snd.Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::COUNT_2,
		res.Load(ResourceManager::SRC::COUNT_2).handleId_);
	snd.Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::COUNT_3,
		res.Load(ResourceManager::SRC::COUNT_3).handleId_);
	snd.Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::GO_SE,
		res.Load(ResourceManager::SRC::GO_SE).handleId_);
}

void CountDown::Init()
{
	//カウントダウン設定
	cnt_ = COUNTDOWN;
	seCnt_ = SE_COUNT;
}

void CountDown::Update()
{
	//カウントダウン
	cnt_ -= SceneManager::GetInstance().GetDeltaTime();

	//効果音関係の処理
	PlaySE();

	//カウントが0以下になったら終了
	if (cnt_ <= 0.0f) { isStart_ = true; }
}

void CountDown::Draw()
{
	//描画
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
	SoundManager::GetInstance().Stop(SoundManager::SOUND::GO_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::COUNT_3);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::COUNT_2);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::COUNT_1);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::COUNT_0);
}

void CountDown::PlaySE()
{
	if (static_cast<int>(cnt_) == seCnt_)
	{
		switch (seCnt_)
		{
		case 3:
			SoundManager::GetInstance().Play(SoundManager::SOUND::COUNT_3);
			break;
		case 2:
			SoundManager::GetInstance().Play(SoundManager::SOUND::COUNT_2);
			break;
		case 1:
			SoundManager::GetInstance().Play(SoundManager::SOUND::COUNT_1);
			break;
		case 0:
			SoundManager::GetInstance().Play(SoundManager::SOUND::COUNT_0);
			SoundManager::GetInstance().Play(SoundManager::SOUND::GO_SE);
			break;
		default:
			break;
		}
		seCnt_--;
	}
}
