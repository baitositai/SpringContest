#include "FpsControl/FpsControl.h"
#include "Manager/ResourceManager.h"
#include "Manager/TextManager.h"
#include "Manager/InputManager.h"
#include "Manager/SceneManager.h"
#include "Shader/PixelShader.h"
#include "Scene/TitleScene.h"
#include "Scene/GameScene.h"
#include "Application.h"

Application* Application::instance_ = nullptr;

const std::string Application::PATH_IMAGE = "Data/Image/";
const std::string Application::PATH_MODEL = "Data/Model/";
const std::string Application::PATH_EFFECT = "Data/Effect/";
const std::string Application::PATH_FONT = "Data/Font/";
const std::string Application::PATH_TEXT = "Data/Text/";

void Application::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}
	instance_->Init();
}

Application& Application::GetInstance(void)
{
	return *instance_;
}

void Application::Init(void)
{

	// アプリケーションの初期設定
	SetWindowText("ここを見たなこの野郎");

	// ウィンドウサイズ
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);

	// DxLibの初期化
	SetOutApplicationLogValidFlag(TRUE);  // ログ出力を有効化
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	isInitFail_ = false;
	if (DxLib_Init() == -1)
	{
		isInitFail_ = true;
		return;
	}

	// キー制御初期化
	SetUseDirectInputFlag(true);

	// リソース管理初期化
	ResourceManager::GetInstance();

	// テキスト管理初期化
	TextManager::GetInstance();

	// FPS初期化
	fps_ = std::make_unique<FpsControl>();
	fps_->Init();
}

void Application::Run(void)
{
	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();

	//初期シーン
	sceneManager.CreateScene(std::make_shared<TitleScene>(sceneManager));

	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//フレームレートを更新
		if (!fps_->UpdateFrameRate()) continue;

		//各種更新処理
		inputManager.Update();
		sceneManager.Update(inputManager);

		//描画処理
		sceneManager.Draw();

		//フレームレート計算
		fps_->CalcFrameRate();

		//フレームレート描画(デバッグ用)
		//fps_->DrawFrameRate();

		ScreenFlip();
	}
}

void Application::Destroy(void)
{

	InputManager::GetInstance().Destroy();
	ResourceManager::GetInstance().Destroy();
	SceneManager::GetInstance().Destroy();
	TextManager::GetInstance().Destroy();
	PixelShader::GetInstance().Destroy();
	
	// DxLib終了
	if (DxLib_End() == -1)
	{
		isReleaseFail_ = true;
	}

	delete instance_;

}

bool Application::IsInitFail(void) const
{
	return isInitFail_;
}

bool Application::IsReleaseFail(void) const
{
	return isReleaseFail_;
}

Application::Application(void)
{
	isInitFail_ = false;
	isReleaseFail_ = false;
	fps_ = nullptr;
}
