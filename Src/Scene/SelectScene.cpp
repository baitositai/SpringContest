#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/ScoreBank.h"
#include "../Manager/DataBank.h"
#include "../Utility/Utility.h"
#include "SelectScene.h"

SelectScene::SelectScene(SceneManager& manager) :SceneBase(manager)
{
	//更新関数のセット
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//描画関数のセット
	drawFunc_ = std::bind(&SelectScene::LoadingDraw, this);
}

void SelectScene::Load(void)
{
	// 読み込み時間初期化
	loadingTime_ = 0.0f;

	//非同期読み込みをtrueにする
	SetUseASyncLoadFlag(true);

	//フォント
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		LOAD_FONT_SIZE,
		0);
}

void SelectScene::Init(void)
{
}

void SelectScene::Update(InputManager& input)
{
	updataFunc_(input);
	return;
}

void SelectScene::Draw(void)
{
	drawFunc_();
	return;
}

void SelectScene::Release(void)
{
	//フォント削除
	DeleteFontToHandle(loadFont_);
}

void SelectScene::LoadingUpdate(InputManager& ins)
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
		updataFunc_ = [&](InputManager& input) {NormalUpdate(input); };

		//描画関数のセット
		drawFunc_ = std::bind(&SelectScene::NormalDraw, this);
	}
}

void SelectScene::NormalUpdate(InputManager& ins)
{
	//シーン遷移
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{		
		DataBank::GetInstance().Input(SceneManager::MODE::MARASON);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
	else if (ins.IsTrgDown(KEY_INPUT_W))
	{
		DataBank::GetInstance().Input(SceneManager::MODE::VS);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
}

void SelectScene::LoadingDraw(void)
{
	DrawNowLoading();
}

void SelectScene::NormalDraw(void)
{
	DrawBox(
		0, 0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		0x00ffff,
		true);

	DrawFormatString(0, 0, 0xffffff, "1人プレイはSPACE");
	DrawFormatString(0, 20, 0xffffff, "2人プレイはW");
}
