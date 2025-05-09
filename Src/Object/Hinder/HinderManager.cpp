#include "../../Manager/ResourceManager.h"
#include "../../Manager/SoundManager.h"
#include "../../Manager/DataBank.h"
#include "HinderManager.h"

HinderManager::HinderManager()
{
	for (int i = 0; i < SceneManager::PLAYER_MAX; i++)
	{
		hinders_[i] = nullptr;
		objs_[i] = nullptr;
	}
}

void HinderManager::Load()
{
	for (int i = 0; i < SceneManager::PLAYER_MAX; i++)
	{
		hinders_[i] = std::make_unique<Hinder>();
		hinders_[i]->Load();

		objs_[i] = std::make_unique<HinderObject>();
		objs_[i]->Load();
	}

	//SE読み込み
	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::HINDER_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::HINDER_SE).handleId_);
}

void HinderManager::Init()
{
	for (int i = 0; i < SceneManager::PLAYER_MAX; i++)
	{
		hinders_[i]->Init();
		objs_[i]->Init();
	}
}

void HinderManager::Update()
{
	for (int i = 0; i < SceneManager::PLAYER_MAX; i++)
	{
		DataBank::GetInstance().Input(i);
		hinders_[i]->Update();
		objs_[i]->Update();
	}

	//妨害を与えるか調べる
	CheckHinder();
}

void HinderManager::Draw()
{
	int playerId = SceneManager::GetInstance().GetScreenCount();
	hinders_[playerId]->Draw();
	objs_[playerId]->Draw();
}

void HinderManager::CheckHinder()
{
	//妨害を与えるか調べる
	for (int attacker = 0; attacker < SceneManager::PLAYER_MAX; attacker++)
	{
		//条件を満たしているか調べる	
		if (hinders_[attacker]->IsStart() == false) { continue; }

		//被害者を設定
		int victim = 1 - attacker;

		//妨害を与える
		objs_[victim]->AddObject(ADD_OBJS);

		//自身の条件判定を取り消す
		hinders_[attacker]->SetStart(false);

		//SE再生
		SoundManager::GetInstance().Play(SoundManager::SOUND::HINDER_SE);
	}
}
