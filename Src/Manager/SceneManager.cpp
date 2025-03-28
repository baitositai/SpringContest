#include "../framework.h"
#include "../Application.h"
#include "../Common/Fader.h"
#include "../Shader/PixelShader.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "../Scene/TitleScene.h"
#include "../Scene/SelectScene.h"
#include "../Scene/GameScene.h"
#include "InputManager.h"
#include "DataBank.h"
#include "SceneManager.h"

void SceneManager::Init(void)
{

	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;

	//PixelShader::GetInstance().Init();

	fader_ = std::make_unique<Fader>();
	fader_->Init();

	// カメラ
	for (int i = 0; i < PLAYER_MAX; i++) {
		std::shared_ptr<Camera>c = std::make_shared<Camera>();
		c->Init();
		cameras_.push_back(std::move(c));
	}

	isSceneChanging_ = false;

	// デルタタイム
	preTime_ = std::chrono::system_clock::now();

	//メインスクリーンの作成
	mainScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);
	//VS用スクリーンを作成
	for (int i = 0; i < PLAYER_MAX; i++) {
		halfScreen_[i] = MakeScreen(Application::SCREEN_HALF_X, Application::SCREEN_SIZE_Y, true);
	}
	
	//スクリーン座標
	screenPos_ = { 0,0};
	screenCnt_ = 0;

	// 3D用の設定
	Init3D();

	//// 初期シーンの設定
	///DoChangeScene(SCENE_ID::GAME);

}

void SceneManager::Init3D(void)
{

	// 背景色設定
	SetBackgroundColor(0, 0, 0);

	// Zバッファを有効にする
	SetUseZBuffer3D(true);

	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(true);

	// バックカリングを有効にする
	SetUseBackCulling(true);

	// ライトの設定
	SetUseLighting(true);

	// 正面から斜め下に向かったライト
	ChangeLightTypeDir({ 0.00f, -1.00f, 1.00f });

}

void SceneManager::CreateScene(std::shared_ptr<SceneBase> scene)
{
	if (scenes_.empty())
	{
		scenes_.push_back(scene);
	}
	else
	{
		scenes_.front() = scene;
	}

	//データのロード
	scenes_.front()->Load();
}

void SceneManager::ChangeAllScene(std::shared_ptr<SceneBase> scene)
{
	//フェード開始
	StartFadeIn();

	scenes_.clear();
	scenes_.push_back(scene);
	//データのロード
	scenes_.front()->Load();
}

//void SceneManager::PushScene(std::shared_ptr<SceneBase> scene)
//{
//	scene->Init();
//	scenes_.push_front(scene);
//}
//
//void SceneManager::PopScene()
//{
//	if (scenes_.size() >= 1)
//	{
//		scenes_.pop_front();
//	}
//}

void SceneManager::Update(InputManager& ins)
{
	if (scenes_.empty())return;

	// デルタタイム
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;
	totalTime_ += GetDeltaTime();
	
	//フェード更新
	Fade();
	
	//シーン更新
	scenes_.front()->Update(ins);	
	
	// カメラ更新
	for (auto& c : cameras_) { c->Update(); }
}

void SceneManager::Draw(void)
{
	drawFunc_();
}

void SceneManager::Destroy(void)
{
	scenes_.front()->Release();
}

void SceneManager::ChangeScene(SCENE_ID nextId)
{
	//フェード中は実行しない
	if (!fader_->IsEnd())return;

	DeleteLightHandleAll();

	// フェード処理が終わってからシーンを変える場合もあるため、
	// 遷移先シーンをメンバ変数に保持
	waitSceneId_ = nextId;

	// フェードアウト(暗転)を開始する
	fader_->SetFade(Fader::STATE::FADE_OUT);
	isSceneChanging_ = true;
}

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
	return sceneId_;
}

float SceneManager::GetDeltaTime(void) const
{
	//return 1.0f / 60.0f;
	return deltaTime_;
}

// カメラの取得
std::vector<std::shared_ptr<Camera>> SceneManager::GetCameras(void) const
{
	return cameras_;
}

void SceneManager::StartFadeIn(void)
{
	// フェードインを開始する
	fader_->SetFade(Fader::STATE::FADE_IN);
}

void SceneManager::SetFadeColor(unsigned int color)
{
	fader_->SetFadeColor(color);
}

void SceneManager::SetDrawingScreen(const int& screenID)
{
	SetDrawScreen(screenID);
	ClearDrawScreen();

	//カメラ設定
	for (auto& c : cameras_) { c->SetBeforeDraw(); }
}

SceneManager::SceneManager(void)
{
	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;
	scenes_.clear();
	isSceneChanging_ = false;
	screenCnt_ = -1;
	// デルタタイム
	deltaTime_ = DELTA_TIME;
	cameras_.clear();

	//描画関数のセット
	drawFunc_ = std::bind(&SceneManager::NormalDraw, this);

	Init();
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{

	//// リソースの解放
	//ResourceManager::GetInstance().Release();

	// シーンを変更する
	sceneId_ = sceneId;

	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		ChangeAllScene(std::make_shared<TitleScene>(*this));
		drawFunc_ = std::bind(&SceneManager::NormalDraw, this);
		break;
	case SCENE_ID::SELECT:
		ChangeAllScene(std::make_shared<SelectScene>(*this));
		drawFunc_ = std::bind(&SceneManager::NormalDraw, this);
		break;
	case SCENE_ID::GAME:
		ChangeAllScene(std::make_shared<GameScene>(*this));
		//描画の切り替え
		if (DataBank::GetInstance().Output().mode_ == MODE::VS) { drawFunc_ = std::bind(&SceneManager::VSPlayDraw, this); }
		else { drawFunc_ = std::bind(&SceneManager::NormalDraw, this); }
		break;
	}

	ResetDeltaTime();

	waitSceneId_ = SCENE_ID::NONE;

}

void SceneManager::Fade(void)
{
	fader_->Update();

	Fader::STATE fState = fader_->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_IN:
		// 明転中
		if (fader_->IsEnd())
		{
			// 明転が終了したら、フェード処理終了
			fader_->SetFade(Fader::STATE::NONE);
			isSceneChanging_ = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		// 暗転中
		if (fader_->IsEnd())
		{
			// 完全に暗転してからシーン遷移
			DoChangeScene(waitSceneId_);
			// 暗転から明転へ
			fader_->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	}
}

void SceneManager::NormalDraw()
{
	// 描画先グラフィック領域の指定
	SetDrawingScreen(mainScreen_);

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();

	//シーン描画(最後尾から描画)
	auto rit = scenes_.rbegin();
	for (; rit != scenes_.rend(); rit++)
	{
		(*rit)->Draw();
		(*rit)->CommonDraw();
	}

	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();

	// 暗転・明転
	fader_->Draw();

	// 描画先グラフィック領域の指定
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	DrawGraph(static_cast<int>(screenPos_.x), static_cast<int>(screenPos_.y), mainScreen_, true);
}

void SceneManager::VSPlayDraw()
{
	//分割画面を生成
	for (int i = 0; i < PLAYER_MAX; i++) {
		//スクリーンカウント設定
		screenCnt_ = i;

		// 描画先グラフィック領域の指定
		SetDrawingScreen(halfScreen_[i]);

		//カメラの設定
		cameras_[i]->SetBeforeDraw();

		//シーン描画(最後尾から描画)
		auto rit = scenes_.rbegin();
		for (; rit != scenes_.rend(); rit++)
		{
			(*rit)->Draw();
		}

		// Effekseerにより再生中のエフェクトを更新する。
		UpdateEffekseer3D();
	}

	//全体の画面を作る
	SetDrawingScreen(mainScreen_);

	//分割した画面の描画
	for (int i = 0; i < PLAYER_MAX; i++) 
	{ 
		DrawGraph(static_cast<int>(screenPos_.x) + Application::SCREEN_HALF_X * i, static_cast<int>(screenPos_.y), halfScreen_[i], true);
			
		// Effekseerにより再生中のエフェクトを描画する。
		DrawEffekseer3D();
	}	

	//画面の共通部分を描画
	auto rit = scenes_.rbegin();
	for (; rit != scenes_.rend(); rit++) { (*rit)->CommonDraw(); }

	// 暗転・明転
	fader_->Draw();

	// 描画先グラフィック領域の指定
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();
	DrawGraph(static_cast<int>(screenPos_.x), static_cast<int>(screenPos_.y), mainScreen_, true);
}
