#include "GameScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/ScoreBank.h"
#include "../Manager/ScrollManager.h"
#include "../Utility/Utility.h"
#include "../Object/Character/Player.h"
#include "../Object/ScrollObject/ObjectManager.h"
#include "../Object/TimeCount.h"

GameScene::GameScene(SceneManager& manager) :SceneBase(manager)
{
	//更新関数のセット
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//描画関数のセット
	drawFunc_ = std::bind(&GameScene::LoadingDraw, this);

	player_ = nullptr;
	objs_ = nullptr;
	state_ = STATE::START;
	strCnt_ = 0.0f;

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

	//プレイヤー
	player_ = std::make_shared<Player>();
	player_->Load();

	//オブジェクト
	objs_ = std::make_unique<ObjectManager>();
	objs_->Load();

	//時間
	time_ = std::make_unique<TimeCount>();
	time_->Load();

	//フォント
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		LOAD_FONT_SIZE,
		0);

	//カメラ
	mainCamera->ChangeMode(Camera::MODE::FIXED_POINT);
	mainCamera->SetTargetPos(LOCAL_CAMERA_POS);
}

void GameScene::Init(void)
{
	//プレイヤー初期化
	player_->Init();

	//オブジェクト初期化
	objs_->Init();

	//時間初期化
	time_->Init();

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
	player_->Update();

	//オブジェクトの更新
	objs_->Update();

	//衝突判定
	Collision();

	//ゲーム終了判定
	CheckGameOver();
}

void GameScene::RezaltUpdate(void)
{
	//プレイヤーの更新(アニメーション再生のため)
	player_->Update();
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
	//※ステージは絶対プレイヤーより前の描画
	player_->Draw();
	objs_->Draw();

	//各状態ごとの描画
	stateGameDraw_();

	//デバッグ描画
	DebagDraw();
}

void GameScene::Collision()
{
	//プレイヤーとオブジェクト同士の衝突処理
	auto & objs = objs_->GetObjects();
	for (auto& obj : objs)
	{
		//オブジェクトがNONEの場合処理をせず次へ回す
		if (obj->GetState() == ObjectBase::STATE::NONE) { continue; }

		//衝突判定
		if (Utility::IsHitSpheres(
			player_->GetTransform().pos,
			player_->GetRadius(),
			obj->GetTransform().pos,
			obj->GetRadius()))
		{
			//衝突判定後の処理
			obj->OnCollision(*player_);
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

void GameScene::PlayDraw()
{
	//時間やスコア等のUIを描画予定
	time_->Draw();
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

void GameScene::DebagDraw()
{
	player_->DebagDraw();
}

void GameScene::CheckGameOver()
{
	//プレイヤーが死亡した場合
	if (player_->GetState() == Player::STATE::DEATH)
	{
		//リザルトに移る
		ChangeState(STATE::REZALT);
	}
}