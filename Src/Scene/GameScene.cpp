#include "GameScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/ScoreBank.h"
#include "../Manager/DataBank.h"
#include "../Manager/ScrollManager.h"
#include "../Utility/Utility.h"
#include "../Object/Character/Player.h"
#include "../Object/ScrollObject/ObjectManager.h"
#include "../Object/TimeCount.h"
#include "../Object/Stage/StageManager.h"

GameScene::GameScene(SceneManager& manager) :SceneBase(manager)
{
	//更新関数のセット
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//描画関数のセット
	drawFunc_ = std::bind(&GameScene::LoadingDraw, this);

	players_.clear();
	objs_.clear();
	state_ = STATE::START;
	strCnt_ = -1.0f;
	playNum_ = -1;

	stateChanges_.emplace(STATE::START, std::bind(&GameScene::ChangeStart, this));
	stateChanges_.emplace(STATE::PLAY, std::bind(&GameScene::ChangePlay, this));
	stateChanges_.emplace(STATE::REZALT, std::bind(&GameScene::ChangeRezalt, this));
}

void GameScene::Load(void)
{
	// 読み込み時間初期化
	loadingTime_ = 0.0f;

	//非同期読み込みをtrueにする
	SetUseASyncLoadFlag(true);

	//人数設定
	playNum_ = 1;
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS) { playNum_ = SceneManager::PLAYER_MAX; }

	//プレイヤー
	for (int i = 0; i < playNum_; i++) {
		auto player = std::make_shared<Player>();
		player->Load();
		players_.emplace_back(std::move(player));
	}

	//オブジェクト
	for (int i = 0; i < playNum_; i++) {
		auto objs = std::make_unique<ObjectManager>();
		objs->Load();
		objs_.emplace_back(std::move(objs));
	}

	//時間
	time_ = std::make_unique<TimeCount>();
	time_->Load();

	//ステージ
	stage_ = std::make_unique<StageManager>();
	stage_->Load();

	//フォント
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		LOAD_FONT_SIZE,
		0);

	//カメラの設定
	auto cameras = SceneManager::GetInstance().GetCameras();
	for (int i = 0; i < cameras.size(); i++)
	{
		cameras[i]->ChangeMode(Camera::MODE::FIXED_POINT);
		cameras[i]->SetTargetPos(LOCAL_CAMERA_POS);
	}
}

void GameScene::Init(void)
{
	//プレイヤー初期化
	for (int i = 0; i < playNum_; i++) { 
		players_[i]->Init(); 
		players_[i]->SetKey(
			RIGHT_MOVE_KEY[i],
			LEFT_MOVE_KEY[i],
			JUMP_MOVE_KEY[i],
			TACKLE_MOVE_KEY[i]);
	}

	//オブジェクト初期化
	for (auto& objs : objs_) { objs->Init(); }

	//時間初期化
	time_->Init();

	//ステージの初期化
	stage_->Init();

	//カウントダウンの設定
	strCnt_ = COUNTDOWN;

	//初期状態
	ChangeState(STATE::START);
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
	//ステージの解放処理
	stage_->Release();

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
	// 更新ステップ
	stateGameUpdate_();

	//シーン遷移
	if (ins.IsTrgDown(KEY_INPUT_RETURN))
	{
		SceneManager::GetInstance().
			ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameScene::ChangeState(STATE state)
{
	// 状態変更
	state_ = state;

	// 各状態遷移の初期処理
	stateChanges_[state_]();
}

void GameScene::ChangeStart(void)
{
	stateGameUpdate_ = std::bind(&GameScene::StartUpdate, this);
	stateGameDraw_ = std::bind(&GameScene::StartDraw, this);
}

void GameScene::ChangePlay(void)
{
	stateGameUpdate_ = std::bind(&GameScene::PlayUpdate, this);
	stateGameDraw_ = std::bind(&GameScene::PlayDraw, this);
}

void GameScene::ChangeRezalt(void)
{
	stateGameUpdate_ = std::bind(&GameScene::RezaltUpdate, this);
	stateGameDraw_ = std::bind(&GameScene::RezaltDraw, this);
}

void GameScene::StartUpdate(void)
{
	//カウントダウン
	strCnt_ -= SceneManager::GetInstance().GetDeltaTime();

	//時間になったら
	if (strCnt_ <= 0.0f)
	{
		ChangeState(STATE::PLAY);
	}
}

void GameScene::PlayUpdate(void)
{
	//時間経過処理
	time_->Update();

	//スクロール関係の処理
	ScrollManager::GetInstance().Update();

	//プレイヤーの更新
	for (auto& player : players_) { player->Update(); }

	//オブジェクトの更新
	for (auto& objs : objs_) { objs->Update(); }

	//ステージの更新
	stage_->Update();

	//衝突判定
	Collision();

	//ゲームオーバー判定
	CheckGameOver();

}

void GameScene::RezaltUpdate(void)
{
	//プレイヤーの更新(アニメーション再生のため)
	for (auto& player : players_) { player->Update(); }

	//シーン遷移
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
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
	DrawBox(
		0, 0,
		Application::SCREEN_SIZE_X,
		Application::SCREEN_SIZE_Y,
		0x00ffff,
		true);
	
	//各種オブジェクト描画処理
	//※プレイヤーはステージより前の描画
	stage_->Draw();
	players_[sceneManager_.GetScreenCount()]->Draw();
	objs_[sceneManager_.GetScreenCount()]->Draw();

	//各状態ごとの描画
	stateGameDraw_();

	//デバッグ描画
	DebagDraw();
}

void GameScene::Collision()
{
	//プレイヤーとオブジェクト同士の衝突処理
	for (int i = 0; i < playNum_; i++) {
		auto& objs = objs_[i]->GetObjects();
		for (auto& obj : objs)
		{
			//オブジェクトがNONEの場合処理をせず次へ回す
			if (obj->GetState() == ObjectBase::STATE::NONE) { continue; }

			//衝突判定
			if (Utility::IsHitSpheres(
				players_[i]->GetTransform().pos,
				players_[i]->GetRadius(),
				obj->GetTransform().pos,
				obj->GetRadius()))
			{
				//衝突判定後の処理
				obj->OnCollision(*players_[i]);
			}
		}
	}
}

void GameScene::StartDraw()
{
	DrawFormatString(
		Application::SCREEN_HALF_X,
		Application::SCREEN_HALF_Y,
		0xff0000,
		"%d",
		(int)strCnt_);
}

void GameScene::RezaltDraw()
{
	int score = ScoreBank::GetInstance().GetScore();

	DrawFormatString(
		Application::SCREEN_HALF_X - 64,
		Application::SCREEN_HALF_Y,
		0x000000,
		"GameOver");

	DrawFormatString(
		Application::SCREEN_HALF_X,
		Application::SCREEN_HALF_Y + 20,
		0x000000,
		"score = %d",
		score);
}
void GameScene::PlayDraw()
{
	//時間やスコア等のUIを描画予定
	time_->Draw();
}

void GameScene::DebagDraw()
{
	for (int i = 0; i < playNum_; i++) {
		players_[i]->DebagDraw();
	}
}

void GameScene::CheckGameOver()
{
	//プレイヤーが死亡した場合
	for (int i = 0; i < playNum_; i++) {
		if (players_[i]->GetState() == Player::STATE::DEATH){
			//リザルトに移る
			ChangeState(STATE::REZALT);
		}
	}
}