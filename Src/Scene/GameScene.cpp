#include "GameScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/ScoreBank.h"
#include "../Manager/DataBank.h"
#include "../Manager/ScrollManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/Effect2DManager.h"
#include "../Manager/Effect2DManagerContainer.h"
#include "../Utility/Utility.h"
#include "../Object/Character/Player.h"
#include "../Object/ScrollObject/ObjectManager.h"
#include "../Object/TimeCount.h"
#include "../Object/Stage/Stage.h"
#include "../Object/Stage/SkyDome.h"
#include "../Object/UI/PlayerUI.h"
#include "../Object/CountDown.h"
#include "../Object/Hinder/HinderManager.h"
#include "../Object/GameBGM.h"

GameScene::GameScene(SceneManager& manager) :SceneBase(manager)
{
	//更新関数のセット
	updateFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//描画関数のセット
	drawFunc_ = std::bind(&GameScene::LoadingDraw, this);

	players_.clear();
	objs_.clear();	
	stage_ = nullptr;
	uis_ = nullptr;
	bgm_ = nullptr;
	sky_ = nullptr;
	hinder_ = nullptr;
	state_ = STATE::NONE;
	strCnt_ = -1.0f;
	playNum_ = -1;

	stateChanges_.emplace(STATE::START, std::bind(&GameScene::ChangeStart, this));
	stateChanges_.emplace(STATE::PLAY, std::bind(&GameScene::ChangePlay, this));
	stateChanges_.emplace(STATE::RESULT, std::bind(&GameScene::ChangeResult, this));
}

void GameScene::Load()
{
	// 読み込み時間初期化
	loadingTime_ = 0.0f;

	//非同期読み込みを行う
	SetUseASyncLoadFlag(true);	
	
	//エフェクト関係初期化※最初に行う
	Effect2DManagerContainer::GetInstance().Init();

	//人数設定
	playNum_ = 1;
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS) { playNum_ = SceneManager::PLAYER_MAX; }
	DataBank::GetInstance().InputPlayNum(playNum_);

	//プレイヤー
	for (int i = 0; i < playNum_; i++) 
	{
		auto player = std::make_shared<Player>();
		DataBank::GetInstance().Input(i);
		player->Load();
		players_.emplace_back(std::move(player));
	}

	//オブジェクト
	for (int i = 0; i < playNum_; i++) 
	{
		auto objs = std::make_unique<ObjectManager>();
		objs->Load();
		objs_.emplace_back(std::move(objs));
	}

	//時間
	time_ = std::make_unique<TimeCount>();
	time_->Load();

	//ステージ
	stage_ = std::make_unique<Stage>();
	stage_->Load();

	//UI
	uis_ = std::make_unique<PlayerUI>();
	uis_->Load();

	//カウントダウン
	cntDown_ = std::make_unique<CountDown>();
	cntDown_->Load();

	//BGM
	bgm_ = std::make_unique<GameBGM>();
	bgm_->Load();

	//スカイドーム
	sky_ = std::make_unique<SkyDome>();
	sky_->Load();

	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS)
	{
		//妨害関係
		hinder_ = std::make_unique<HinderManager>();
		hinder_->Load();
	}

	//フォント
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		LOAD_FONT_SIZE,
		0);

	//サウンド関係
	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::CHANGE_SCENE_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::CHANGE_SCENE_SE).handleId_);

	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::CLEAR_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::CLEAR_SE).handleId_);

	//カメラの設定
	auto cameras = SceneManager::GetInstance().GetCameras();
	for (int i = 0; i < cameras.size(); i++)
	{
		cameras[i]->ChangeMode(Camera::MODE::FIXED_POINT);
		cameras[i]->SetTargetPos(LOCAL_CAMERA_POS);
	}
}

void GameScene::Init()
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

	//UIの初期化
	uis_->Init();

	//カウントダウン初期化
	cntDown_->Init();

	//BGM
	bgm_->Init();

	//スカイドーム
	sky_->Init();

	//妨害関係初期化	
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS)
	{
		hinder_->Init();
	}

	//初期状態
	ChangeState(STATE::START);

	//スピード関係の初期化
	ScrollManager::GetInstance().Init();

	//スコア初期化
	ScoreBank::GetInstance().Init();
}

void GameScene::Update(InputManager& input)
{
	updateFunc_(input);
	return;
}

void GameScene::Draw()
{
	drawFunc_();
	return;
}

void GameScene::Release()
{
	//各インスタンスのリリース処理
	time_->Release();
	cntDown_->Release();
	bgm_->Release();
	for (auto& obj : objs_) { obj->Release(); }
	for (auto& player : players_) { player->Release(); }

	//フォント削除
	DeleteFontToHandle(loadFont_);
}

void GameScene::CommonDraw()
{	
	if (state_ == STATE::NONE) { return; }
	//各状態ごとの描画
	stateGameDraw_();
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
		updateFunc_ = [&](InputManager& input) {NormalUpdate(input); };
		
		//描画関数のセット
		drawFunc_ = std::bind(&GameScene::NormalDraw, this);
	}
}

void GameScene::NormalUpdate(InputManager& ins)
{
	// 更新ステップ
	stateGameUpdate_();

	//スカイドーム更新
	sky_->Update();

	//2Dエフェクト更新
	Effect2DManagerContainer::GetInstance().Update();
}

void GameScene::ChangeState(STATE state)
{
	// 状態変更
	state_ = state;

	// 各状態遷移の初期処理
	stateChanges_[state_]();
}

void GameScene::ChangeStart()
{
	stateGameUpdate_ = std::bind(&GameScene::StartUpdate, this);
	stateGameDraw_ = std::bind(&GameScene::StartDraw, this);
}

void GameScene::ChangePlay()
{
	stateGameUpdate_ = std::bind(&GameScene::PlayUpdate, this);
	stateGameDraw_ = std::bind(&GameScene::PlayDraw, this);
}

void GameScene::ChangeResult()
{
	stateGameUpdate_ = std::bind(&GameScene::ResultUpdate, this);
	stateGameDraw_ = std::bind(&GameScene::ResultDraw, this);

	//勝利状態の確認
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS) { CheckWinPlayer(); }

	//BGM停止
	bgm_->Stop();

	//クリアSE
	SoundManager::GetInstance().Play(SoundManager::SOUND::CLEAR_SE);
}

void GameScene::StartUpdate()
{
	//カウントダウン
	cntDown_->Update();

	//時間になったら
	if (cntDown_->IsStart())
	{
		ChangeState(STATE::PLAY);
	}
}

void GameScene::PlayUpdate()
{
	//時間経過処理
	time_->Update();

	//プレイヤーの更新
	for (int i = 0; i < players_.size(); i++)
	{
		DataBank::GetInstance().Input(i);
		players_[i]->Update();
	}

	//オブジェクトの更新
	for (int i = 0; i < objs_.size(); i++)
	{
		DataBank::GetInstance().Input(i);
		objs_[i]->Update();
	}

	//妨害関係の更新
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS)
	{
		hinder_->Update();
	}

	//ステージの更新
	stage_->Update();

	//UIの更新
	uis_->Update();

	//衝突判定
	Collision();

	//ゲームオーバー判定
	CheckGameOver();
}

void GameScene::ResultUpdate()
{
	//プレイヤーの更新(アニメーション再生のため)
	for (auto& player : players_) { player->Update(); }

	//シーン遷移
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);

		//シーン遷移SE
		SoundManager::GetInstance().Play(SoundManager::SOUND::CHANGE_SCENE_SE);

		//SEの停止
		SoundManager::GetInstance().Stop(SoundManager::SOUND::CLEAR_SE);
	}
}

void GameScene::LoadingDraw()
{
	//「now loading」の描画
	DrawNowLoading();
}

void GameScene::NormalDraw()
{
	int playerId = sceneManager_.GetScreenCount();

	//スカイドーム
	sky_->Draw();

	//ステージ
	stage_->Draw();

	//プレイヤー
	players_[playerId]->Draw();

	//オブジェクト関連
	objs_[sceneManager_.GetScreenCount()]->Draw();

	//妨害関係の描画
	if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS)
	{
		hinder_->Draw();
	}

	//タイム
	time_->Draw();

	//UI
	uis_->Draw(*players_[playerId]);
}

void GameScene::Collision()
{
	//プレイヤーとオブジェクト同士の衝突処理
	for (int i = 0; i < playNum_; i++)
	{
		//プレイヤーIDを設定
		DataBank::GetInstance().Input(i);

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
	cntDown_->Draw();
}

void GameScene::ResultDraw()
{
	//クリア描画
	uis_->ResultDraw();
}

void GameScene::PlayDraw()
{
	//時間やスコア等のUIを描画予定
	time_->CommonDraw();
}

void GameScene::DebagDraw()
{
	for (int i = 0; i < playNum_; i++)
	{
		players_[i]->DebagDraw();
	}
}

void GameScene::CheckGameOver()
{
	//プレイヤーが死亡した場合
	for (int i = 0; i < playNum_; i++) 
	{
		if (players_[i]->GetState() == Player::STATE::DEATH){

			//リザルトに移る
			ChangeState(STATE::RESULT);
		}
	}			
}

void GameScene::CheckWinPlayer()
{
	//生存状態のプレイヤーの状態を変更
	for (int j = 0; j < playNum_; j++)
	{
		if (players_[j]->GetState() != Player::STATE::DEATH) { players_[j]->ChangeState(Player::STATE::WIN); }
	}

	//ゲームの勝利状態を調べる
	if (players_[0]->GetState() == Player::STATE::WIN &&
		players_[1]->GetState() == Player::STATE::WIN)
	{
		//引き分け
		uis_->ChangeWinState(PlayerUI::WIN_STATE::DRAW);
	}
	else if (players_[0]->GetState() == Player::STATE::WIN)
	{
		//プレイヤー1の勝利
		uis_->ChangeWinState(PlayerUI::WIN_STATE::P1_WIN);
	}
	else if (players_[1]->GetState() == Player::STATE::WIN)
	{
		//プレイヤー2の勝利
		uis_->ChangeWinState(PlayerUI::WIN_STATE::P2_WIN);
	}
}
