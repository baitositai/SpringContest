#include "ResourceManager.h"

void ResourceManager::Init(void)
{
	std::unique_ptr<Resource> res;
	std::string path_Omuretu = "Character/Omuretu/";
	std::string path_Stage = "Stage/";

	// プレイヤー影
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Shadow.png");
	resourcesMap_.emplace(SRC::PLAYER_SHADOW, std::move(res));

	//オムレツ(走る)
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "Alphabet.png",
		ALPHABET_NUM_X, ALPHABET_NUM_Y, ALPHABET_SIZE_X, ALPHABET_SIZE_Y);
	resourcesMap_.emplace(SRC::ALPHABET, std::move(res));

	//プレイヤー
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "Player/Player.mv1");
	resourcesMap_.emplace(SRC::PLAYER, std::move(res));

	//ステージ
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "Stage/MainPlanet.mv1");
	resourcesMap_.emplace(SRC::STAGE, std::move(res));

	//スカイドーム
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "SkyDome/Skydome.mv1");
	resourcesMap_.emplace(SRC::SKY_DOME, std::move(res));

	//敵
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "Enemy/Zombie Cartoon_01.mv1");
	resourcesMap_.emplace(SRC::ENEMY, std::move(res));

	//プレイヤーアイコン
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "PlayerIcons.png",
		PLAYER_ICONS_NUM_X, PLAYER_ICONS_NUM_Y, PLAYER_ICONS_SIZE, PLAYER_ICONS_SIZE);
	resourcesMap_.emplace(SRC::PLAYER_ICONS, std::move(res));

	//ライフUI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "LifeUi.png");
	resourcesMap_.emplace(SRC::LIFE_UI, std::move(res));

	//パワーUI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "PowerUi.png");
	resourcesMap_.emplace(SRC::POWER_UI, std::move(res));

	//スコアUI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "ScoreUi.png");
	resourcesMap_.emplace(SRC::SCORE_UI, std::move(res));

	//お邪魔UI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Hinder.png");
	resourcesMap_.emplace(SRC::HINDER, std::move(res));

	//お邪魔ゲージUI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "HinderGage.png");
	resourcesMap_.emplace(SRC::HINDER_GAGE, std::move(res));

	//数字画像
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "Numbers.png",
		NUMBERS_NUM_X, NUMBERS_NUM_Y, NUMBERS_SIZE, NUMBERS_SIZE);
	resourcesMap_.emplace(SRC::NUMBER, std::move(res));

	//数字画像2
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "Numbers2.png",
		NUMBERS_NUM_X, NUMBERS_NUM_Y, NUMBERS_SIZE, NUMBERS_SIZE);
	resourcesMap_.emplace(SRC::NUMBER2, std::move(res));

	//ライフ
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Life.png");
	resourcesMap_.emplace(SRC::LIFE, std::move(res));

	//パワー
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Power.png");
	resourcesMap_.emplace(SRC::POWER, std::move(res));

	//プレイヤーUI
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "PlayersUi.png",
		PLAYER_UI_NUM_X, PLAYER_UI_NUM_Y, PLAYER_UI_SIZE_X, PLAYER_UI_NUM_Y);
	resourcesMap_.emplace(SRC::PLAYER_UI, std::move(res));

	//タイマーUI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Timer.png");
	resourcesMap_.emplace(SRC::TIMER_UI, std::move(res));

	//勝利UI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Win.png");
	resourcesMap_.emplace(SRC::WIN_UI, std::move(res));
}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	resourcesMap_.clear();
}

Resource &ResourceManager::Load(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return dummy_;
	}
	return res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
	Init();
}

Resource& ResourceManager::_Load(SRC src)
{
	// ロード済みチェック
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return lPair->second;
	}

	// リソース登録チェック
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない
		return dummy_;
	}

	// ロード処理
	rPair->second->Load();

	// 念のためコピーコンストラクタ
	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;
}
