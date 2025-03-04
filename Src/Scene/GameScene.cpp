#include "GameScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Utility/Utility.h"
#include "../Object/Stage/StageBase.h"
#include "../Object/Stage/StageDefault.h"


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

	//ステージの初期化
	size_t sSize = stages_.size();
	for (int i = 0; i < sSize; i++)
	{
		stages_[i]->Release();
		delete stages_[i];
	}

	stages_.clear();

	//初期化
	stageSpawnCounter_ = 0;
	stageSpawn_ = 0;
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

	for (auto& stage : stages_) {
		stage->Release();
	}
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

	//ステージの更新処理は動的配列で回す
	//出現しているアイテムはすべて更新する
	size_t sSize = stages_.size();
	for (int i = 0; i < sSize; i++)
	{
		stages_[i]->Update();

	}

	//ステージの出現カウントを増やす
	++stageSpawnCounter_;

	//出現カウントが指定値を超えたら
	if (stageSpawn_ < 3)
	{

		stageSpawnCounter_ = 0;

		//ステージを動的生成
		//ポインタに何もささない上程を設定するときは
		//nullptrをしようする
		StageBase* newStage = nullptr;

		//ステージの生成
		int stageTypeMaxNum = static_cast<int>(StageBase::STAGE_TYPE::MAX) - 1;

		//ステージのタイプをランダムで決定する
		int newStageType = GetRand(stageTypeMaxNum);

		//enmuで使用するためにステージのタイプに戻す
		StageBase::STAGE_TYPE randType = static_cast<StageBase::STAGE_TYPE>(newStageType);

		switch (randType)
		{
		case StageBase::STAGE_TYPE::STAGE:
			newStage = new StageDefault();
			break;
		}

		newStage->Init();

		//出現座標
		VECTOR spawnPos;

		//ワーニング回避のために一旦初期化
		spawnPos.x = 0;
		spawnPos.y = 0;
		spawnPos.z = 0;



		//出現位置設定
		switch (randType)
		{
		case StageBase::STAGE_TYPE::STAGE:
			if (sSize == 0)
			{
				spawnPos.x = 1000;
				spawnPos.y = -2000;
				spawnPos.z = 2000;
			}
			if (sSize == 1)
			{
				spawnPos.x = 1000;
				spawnPos.y = -2000;
				spawnPos.z = 2000 + StageBase::SIZE_Z;
			}
			if (sSize == 2)
			{
				spawnPos.x = 1000;
				spawnPos.y = -2000;
				spawnPos.z = 2000 + StageBase::SIZE_Z * 2;
			}


			break;
		}


		//座標の設定
		newStage->SetPos(spawnPos);

		//動的配列に追加
		stages_.push_back(newStage);

		stageSpawn_++;

	}

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
	//デバッグ描画
	DebagDraw();

	//ステージの描画も動的配列でまわす形に変更
	//出現しているアイテムすべてを描画する
	size_t sSize = stages_.size();
	for (int i = 0; i < sSize; i++)
	{
		stages_[i]->Draw();
	}


}

void GameScene::DebagDraw()
{
	////デバッグ系の描画はここに書く
	DrawBox(
		0, 0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		0xfff000,
		true);
}
