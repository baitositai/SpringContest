#include "../Application.h"
#include "../Utility/Utility.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include "../Object/Character/TitlePlayer.h"
#include "../Object/TitleMesh.h"
#include "TitleScene.h"


TitleScene::TitleScene(SceneManager& manager) :SceneBase(manager)
{
	//各種初期化処理
	imgTitle_ = -1;
	imgTitleBackGround_ = -1;
	changeSceneStep_ = -1.0f;

	int i = -1;

	//更新関数のセット
	updateFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//描画関数のセット
	drawFunc_ = std::bind(&TitleScene::LoadingDraw, this);

	//初期化
	titlePlayer_ = nullptr;
	titleMesh_ = nullptr;
}

void TitleScene::Load()
{
	// 読み込み時間初期化
	loadingTime_ = 0.0f;

	//非同期読み込みを行う
	SetUseASyncLoadFlag(true);

	// タイトル
	imgTitle_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::TITLE).handleId_;
	imgTitleBackGround_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::TITLE_BACKGROUND).handleId_;

	//フォント
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::DOT).c_str(),
		LOAD_FONT_SIZE,
		0);
	mesFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::BOKUTACHI).c_str(),
		MES_FONT_SIZE,
		0);

	//サウンドのロード
	SoundManager::GetInstance().Add(
		SoundManager::TYPE::BGM,
		SoundManager::SOUND::TITLE_BGM,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::TITLE_BGM).handleId_);

	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::CHANGE_SCENE_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::CHANGE_SCENE_SE).handleId_);

	//タイトルにプレイヤーをロードする
	titlePlayer_ = std::make_unique<TitlePlayer>();
	titlePlayer_->Load();

	//メッシュ
	titleMesh_ = std::make_unique<TitleMesh>();
	titleMesh_->Load();
}


void TitleScene::Init()
{
	//変数初期化
	changeSceneStep_ = CHANGE_SCENE_SECOND;

	//プレイヤー
	titlePlayer_->Init();

	//メッシュ
	titleMesh_->Init();

	//音量設定
	SoundManager::GetInstance().AdjustVolume(SoundManager::SOUND::TITLE_BGM, VOLUME);

	//音楽再生
	SoundManager::GetInstance().Play(SoundManager::SOUND::TITLE_BGM);
}

void TitleScene::Update(InputManager& input)
{
	updateFunc_(input);

	return;
}

void TitleScene::Draw()
{
	drawFunc_();

	return;
}

void TitleScene::Release()
{
	DeleteFontToHandle(loadFont_);
	DeleteFontToHandle(mesFont_);

	//音楽停止
	SoundManager::GetInstance().Stop(SoundManager::SOUND::CHANGE_SCENE_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::TITLE_BGM);
}

void TitleScene::CommonDraw()
{
}

void TitleScene::LoadingUpdate(InputManager& input)
{
	bool loadTimeOver = Utility::IsTimeOver(loadingTime_, LOADING_TIME);

	//ロードが完了したか判断
	if (GetASyncLoadNum() == 0 && loadTimeOver)
	{
		//非同期処理を無効にする
		SetUseASyncLoadFlag(false);

		//初期化処理
		Init();

		//フェードイン開始
		sceneManager_.StartFadeIn();

		//更新関数のセット
		updateFunc_ = [&](InputManager& input) {NormalUpdate(input); };
		
		//描画関数のセット
		drawFunc_ = std::bind(&TitleScene::NormalDraw, this);
	}
}

void TitleScene::NormalUpdate(InputManager& ins)
{
	//更新処理
	titlePlayer_->Update();

	//メッシュ
	titleMesh_->Update();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		//効果音再生
		SoundManager::GetInstance().Play(SoundManager::SOUND::CHANGE_SCENE_SE);
		//シーン遷移
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT);
		//BGM停止
		SoundManager::GetInstance().Stop(SoundManager::SOUND::TITLE_BGM);
	}

	changeSceneStep_ -= SceneManager::GetInstance().GetDeltaTime();
	if (ins.IsTrgDown(KEY_INPUT_RETURN) ||
		changeSceneStep_ <= 0.0f)
	{
		//効果音再生
		SoundManager::GetInstance().Play(SoundManager::SOUND::CHANGE_SCENE_SE);
		//シーン遷移
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::MOVIE);
		//BGM停止
		SoundManager::GetInstance().Stop(SoundManager::SOUND::TITLE_BGM);
	}
}

void TitleScene::LoadingDraw()
{
	//「now loading」の描画
	DrawNowLoading();
}

void TitleScene::NormalDraw()
{
	//タイトル背景
	DrawExtendGraph(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, imgTitleBackGround_, true);

	//タイトルロゴ
	DrawRotaGraph(LOGO_POS_X, LOGO_POS_Y, LOGO_RATE, 0.0f, imgTitle_, true);

	//モデル描画に必要
	SetDrawScreen(sceneManager_.GetMainScreen());

	//メッシュ
	titleMesh_->Draw();

	//キャラクター
	titlePlayer_->Draw();
}