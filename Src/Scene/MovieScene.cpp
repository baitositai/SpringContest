#include "MovieScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Utility/Utility.h"

MovieScene::MovieScene(SceneManager& manager) :SceneBase(manager)
{
	//更新関数のセット
	updateFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//描画関数のセット
	drawFunc_ = std::bind(&MovieScene::LoadingDraw, this);

	movie_ = -1;
}

void MovieScene::Load()
{
	movie_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::MOVIE).handleId_;
}

void MovieScene::Init()
{
	//動画の再生
	if (movie_ != -1)
	{
		PlayMovieToGraph(movie_);
	}
	else
	{
		//ムービーが無い場合はシーン遷移
		sceneManager_.ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void MovieScene::Update(InputManager& input)
{
	updateFunc_(input);
	return;
}

void MovieScene::Draw()
{
	drawFunc_();
	return;
}

void MovieScene::Release()
{
	DeleteFontToHandle(loadFont_);
}

void MovieScene::CommonDraw()
{
}

void MovieScene::LoadingUpdate(InputManager& ins)
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
		drawFunc_ = std::bind(&MovieScene::NormalDraw, this);
	}
}

void MovieScene::NormalUpdate(InputManager& ins)
{
	//タイトルに戻る
	if (ins.IsTrgDown(KEY_INPUT_SPACE) ||
		ins.IsTrgDown(KEY_INPUT_RETURN) ||
		GetMovieStateToGraph(movie_) == 0)
	{
		//動画停止
		PauseMovieToGraph(movie_);
		//再生位置を最初からへ
		SeekMovieToGraph(movie_, 0);
		//シーン遷移
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void MovieScene::LoadingDraw()
{
	DrawNowLoading();
}

void MovieScene::NormalDraw()
{
	DrawExtendGraph(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, movie_, true);
}
