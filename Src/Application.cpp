#include "FpsControl/FpsControl.h"
#include "Manager/ResourceManager.h"
#include "Manager/TextManager.h"
#include "Manager/InputManager.h"
#include "Manager/SceneManager.h"
#include "Manager/SoundManager.h"
#include "Manager/EffectManager.h"
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
const std::string Application::PATH_SOUND = "Data/Sound/";

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
	// �A�v���P�[�V�����̏����ݒ�
	SetWindowText("�����������Ȃ��̖�Y");

	// �E�B���h�E�T�C�Y
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);

	// DxLib�̏�����
	SetOutApplicationLogValidFlag(TRUE);  // ���O�o�͂�L����
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	isInitFail_ = false;
	if (DxLib_Init() == -1)
	{
		isInitFail_ = true;
		return;
	}

	//�G�t�F�N�V�A�̏�����
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
	}
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// �L�[���䏉����
	SetUseDirectInputFlag(true);

	// ���\�[�X�Ǘ�������
	ResourceManager::GetInstance();

	// �e�L�X�g�Ǘ�������
	TextManager::GetInstance();

	// FPS������
	fps_ = std::make_unique<FpsControl>();
	fps_->Init();
}

void Application::Run(void)
{
	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();

	MSG msg;
	LONGLONG time = GetNowHiPerformanceCount();
	LONGLONG temp_time;

	//�����V�[��
	sceneManager.CreateScene(std::make_shared<TitleScene>(sceneManager));

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�t���[�����[�g���X�V
		if (!fps_->UpdateFrameRate()) continue;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//�e��X�V����
		inputManager.Update();
		sceneManager.Update(inputManager);

		//�`�揈��
		sceneManager.Draw();		
		
		temp_time = GetNowHiPerformanceCount();
		while (temp_time - time < 1000000 / 60)
		{
			Sleep(0);
			temp_time = GetNowHiPerformanceCount();
		}
		time = temp_time;

		//�t���[�����[�g�v�Z
		fps_->CalcFrameRate();

		//�t���[�����[�g�`��(�f�o�b�O�p)
		//fps_->DrawFrameRate();

		ScreenFlip();
	}
}

void Application::Destroy(void)
{
	InputManager::GetInstance().Destroy();	
	EffectManager::GetInstance().Destroy();	
	SoundManager::GetInstance().Destroy();
	PixelShader::GetInstance().Destroy();
	SceneManager::GetInstance().Destroy();
	TextManager::GetInstance().Destroy();
	ResourceManager::GetInstance().Destroy();

	// Effekseer���I������B
	Effkseer_End();
	
	// DxLib�I��
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

Application::Application(void)
{
	isInitFail_ = false;
	isReleaseFail_ = false;
	fps_ = nullptr;
}
