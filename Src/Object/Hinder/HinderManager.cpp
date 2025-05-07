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

	//SE“Ç‚İ‚İ
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

	//–WŠQ‚ğ—^‚¦‚é‚©’²‚×‚é
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
	//–WŠQ‚ğ—^‚¦‚é‚©’²‚×‚é
	for (int attacker = 0; attacker < SceneManager::PLAYER_MAX; attacker++)
	{
		//ğŒ‚ğ–‚½‚µ‚Ä‚¢‚é‚©’²‚×‚é	
		if (hinders_[attacker]->IsStart() == false) { continue; }

		//”íŠQÒ‚ğİ’è
		int victim = 1 - attacker;

		//–WŠQ‚ğ—^‚¦‚é
		objs_[victim]->AddObject(ADD_OBJS);

		//©g‚ÌğŒ”»’è‚ğæ‚èÁ‚·
		hinders_[attacker]->SetStart(false);

		//SEÄ¶
		SoundManager::GetInstance().Play(SoundManager::SOUND::HINDER_SE);
	}
}
