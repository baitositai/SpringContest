#include "GameScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Utility/Utility.h"

GameScene::GameScene(SceneManager& manager) :SceneBase(manager)
{
	//更新関数のセット
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//描画関数のセット
	drawFunc_ = std::bind(&GameScene::LoadingDraw, this);
}

void GameScene::Load(void)
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

	//カメラ
	mainCamera->ChangeMode(Camera::MODE::FIXED_POINT);
}

void GameScene::Init(void)
{

}

void GameScene::Update(InputManager& input)
{
	updataFunc_(input);
	return;
}

void GameScene::Draw(void)
{
	drawFunc_();
	return;
}

void GameScene::Release(void)
{
	//フォント削除
	DeleteFontToHandle(loadFont_);
}

void GameScene::LoadingUpdate(InputManager& ins)
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
		drawFunc_ = std::bind(&GameScene::NormalDraw, this);
	}
}

void GameScene::NormalUpdate(InputManager& ins)
{
	//シーン遷移
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().
			ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameScene::LoadingDraw(void)
{
	//「now loading」の描画
	DrawNowLoading();
}

void GameScene::NormalDraw(void)
{
	//各種オブジェクト描画処理

	//デバッグ描画
	DebagDraw();
}

void GameScene::DebagDraw()
{
	//デバッグ系の描画はここに書く
	DrawBox(
		0, 0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		0xfff000,
		true);
}
