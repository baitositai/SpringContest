#include "../Application.h"
#include "ResourceManager.h"


void ResourceManager::Init()
{
	std::unique_ptr<Resource> res;
	std::string path_Stage = "Stage/";

	//タイトル画像
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "GameLogo.png");
	resourcesMap_.emplace(SRC::TITLE, std::move(res));

	//タイトル文字
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "PushSpace.png",
		TITLE_UI_NUM_X, TITLE_UI_NUM_Y, TITLE_UI_SIZE, TITLE_UI_SIZE);
	resourcesMap_.emplace(SRC::TITLE_UI, std::move(res));

	//タイトル背景
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "TitleBackGround.png");
	resourcesMap_.emplace(SRC::TITLE_BACKGROUND, std::move(res));

	// プレイヤー影
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Shadow.png");
	resourcesMap_.emplace(SRC::PLAYER_SHADOW, std::move(res));

	//プレイヤー
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "Player/Player.mv1");
	resourcesMap_.emplace(SRC::PLAYER, std::move(res));

	//ステージ
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "Stage/stage.mv1");
	resourcesMap_.emplace(SRC::STAGE, std::move(res));

	//スカイドーム
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "SkyDome/Skydome.mv1");
	resourcesMap_.emplace(SRC::SKY_DOME, std::move(res));

	//敵
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "Enemy/Zombie Cartoon_01.mv1");
	resourcesMap_.emplace(SRC::ENEMY, std::move(res));

	//爆弾
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "ScrollObject/Bomb.mv1");
	resourcesMap_.emplace(SRC::BOMB, std::move(res));

	//ハート
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "ScrollObject/Heart.mv1");
	resourcesMap_.emplace(SRC::HEART, std::move(res));

	//ポーション
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "ScrollObject/Potion.mv1");
	resourcesMap_.emplace(SRC::POTION, std::move(res));

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
		NUMBERS2_NUM_X, NUMBERS2_NUM_Y, NUMBERS2_SIZE, NUMBERS2_SIZE);
	resourcesMap_.emplace(SRC::NUMBER2, std::move(res));

	//ライフ
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Life.png");
	resourcesMap_.emplace(SRC::LIFE, std::move(res));

	//パワー
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Power.png");
	resourcesMap_.emplace(SRC::POWER, std::move(res));

	//プレイヤーUI
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "PlayersUI.png",
		PLAYER_UI_NUM_X, PLAYER_UI_NUM_Y, PLAYER_UI_SIZE_X, PLAYER_UI_SIZE_Y);
	resourcesMap_.emplace(SRC::PLAYER_UI, std::move(res));

	//タイマーUI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Timer.png");
	resourcesMap_.emplace(SRC::TIMER_UI, std::move(res));

	//勝利UI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Win.png");
	resourcesMap_.emplace(SRC::WIN_UI, std::move(res));

	//引き分け
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Draw.png");
	resourcesMap_.emplace(SRC::DRAW, std::move(res));

	//タイトルBGM
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Title.mp3");
	resourcesMap_.emplace(SRC::TITLE_BGM, std::move(res));

	//セレクトシーンBGM
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Select.mp3");
	resourcesMap_.emplace(SRC::SELECT_BGM, std::move(res));

	//ゲームシーンBGM1
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Game1.mp3");
	resourcesMap_.emplace(SRC::GAMEBGM1, std::move(res));

	//ゲームシーンBGM2
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Game2.mp3");
	resourcesMap_.emplace(SRC::GAMEBGM2, std::move(res));

	//シーン遷移SE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "SceneChange.mp3");
	resourcesMap_.emplace(SRC::CHANGE_SCENE_SE, std::move(res));

	//スイッチオン
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "SwitchOn.mp3");
	resourcesMap_.emplace(SRC::SWITCH_ON_SE, std::move(res));

	//スイッチオフ
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "SwitchOff.mp3");
	resourcesMap_.emplace(SRC::SWITCH_OFF_SE, std::move(res));

	//カウント3
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Count3.mp3");
	resourcesMap_.emplace(SRC::COUNT_3, std::move(res));

	//カウント2
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Count2.mp3");
	resourcesMap_.emplace(SRC::COUNT_2, std::move(res));

	//カウント1
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Count1.mp3");
	resourcesMap_.emplace(SRC::COUNT_1, std::move(res));

	//カウント0
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Count0.mp3");
	resourcesMap_.emplace(SRC::COUNT_0, std::move(res));

	//GOSE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Go.mp3");
	resourcesMap_.emplace(SRC::GO_SE, std::move(res));

	//アイテムGetSE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "ItemGet.mp3");
	resourcesMap_.emplace(SRC::ITEM_GET_SE, std::move(res));

	//タックルSE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Tackle.mp3");
	resourcesMap_.emplace(SRC::TACKLE_SE, std::move(res));

	//ダメージSE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Damage.mp3");
	resourcesMap_.emplace(SRC::DAMAGE_SE, std::move(res));

	//クリアSE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Clear.mp3");
	resourcesMap_.emplace(SRC::CLEAR_SE, std::move(res));

	//ジャンプSE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Jump.mp3");
	resourcesMap_.emplace(SRC::JUMP_SE, std::move(res));

	//スピードアップSE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "SpeedUp.mp3");
	resourcesMap_.emplace(SRC::SPEED_UP_SE, std::move(res));

	//爆発SE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Blast.mp3");
	resourcesMap_.emplace(SRC::BLAST_SE, std::move(res));

	//爆発SE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "EnemyDamage.mp3");
	resourcesMap_.emplace(SRC::ENEMY_DAMAGE_SE, std::move(res));

	//タックルゲージ
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "TackleGage.png");
	resourcesMap_.emplace(SRC::TACKLE_GAGE, std::move(res));

	//スピードアップ
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "SpeedUp.png");
	resourcesMap_.emplace(SRC::SPEED_UP, std::move(res));

	//タックル選択UI 
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "TackleSelect.png");
	resourcesMap_.emplace(SRC::TACKLE_SELECT, std::move(res));

	//操作説明UI
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "Explan.png",
		EXPLAN_NUM_X, EXPLAN_NUM_Y, EXPLAN_SIZE_X, EXPLAN_SIZE_Y);
	resourcesMap_.emplace(SRC::EXPLAN, std::move(res));

	//タックルエフェクト
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "TackleEfk.png",
		EFK_NUM_X, EFK_NUM_Y, EFK_SIZE, EFK_SIZE);
	resourcesMap_.emplace(SRC::TACKLE_EFK, std::move(res));

	//ヒットエフェクト
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "HitEfk.png",
		EFK_NUM_X, EFK_NUM_Y, EFK_SIZE, EFK_SIZE);
	resourcesMap_.emplace(SRC::HIT_EFK, std::move(res));

	//爆発エフェクト
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "Explosion.png",
		EFK_NUM_X, EFK_NUM_Y, EFK_SIZE, EFK_SIZE);
	resourcesMap_.emplace(SRC::EXPLOSION_EFK, std::move(res));

	//入手エフェクト
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "GetEfk.png",
		GET_EFK_NUM_X, GET_EFK_NUM_Y, GET_EFK_SIZE, GET_EFK_SIZE);
	resourcesMap_.emplace(SRC::GET_EFK, std::move(res));

	//妨害オブジェクト
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "HinderObjcets.png",
		HINDER_NUM_X, HINDER_NUM_Y, HINDER_SIZE, HINDER_SIZE);
	resourcesMap_.emplace(SRC::HINDER_OBJS, std::move(res));

	//妨害開始用SE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Hinder.mp3");
	resourcesMap_.emplace(SRC::HINDER_SE, std::move(res));

	//動画
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_MOVIE + "Movie.mp4");
	resourcesMap_.emplace(SRC::MOVIE, std::move(res));
}

void ResourceManager::Release()
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy()
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

ResourceManager::ResourceManager()
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
