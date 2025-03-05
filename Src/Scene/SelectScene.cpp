#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/ScoreBank.h"
#include "../Manager/DataBank.h"
#include "../Utility/Utility.h"
#include "SelectScene.h"

SelectScene::SelectScene(SceneManager& manager) :SceneBase(manager)
{
	//�X�V�֐��̃Z�b�g
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&SelectScene::LoadingDraw, this);
}

void SelectScene::Load(void)
{
	// �ǂݍ��ݎ��ԏ�����
	loadingTime_ = 0.0f;

	//�񓯊��ǂݍ��݂�true�ɂ���
	SetUseASyncLoadFlag(true);

	//�t�H���g
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
	//�t�H���g�폜
	DeleteFontToHandle(loadFont_);
}

void SelectScene::LoadingUpdate(InputManager& ins)
{
	bool loadTimeOver = Utility::IsTimeOver(loadingTime_, LOADING_TIME);

	//���[�h���������������f
	if (GetASyncLoadNum() == 0 && loadTimeOver)
	{
		//�񓯊������𖳌��ɂ���
		SetUseASyncLoadFlag(false);

		//����������
		Init();

		//�t�F�[�h�C���J�n
		sceneManager_.StartFadeIn();

		//�X�V�֐��̃Z�b�g
		updataFunc_ = [&](InputManager& input) {NormalUpdate(input); };

		//�`��֐��̃Z�b�g
		drawFunc_ = std::bind(&SelectScene::NormalDraw, this);
	}
}

void SelectScene::NormalUpdate(InputManager& ins)
{
	//�V�[���J��
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

	DrawFormatString(0, 0, 0xffffff, "1�l�v���C��SPACE");
	DrawFormatString(0, 20, 0xffffff, "2�l�v���C��W");
}
