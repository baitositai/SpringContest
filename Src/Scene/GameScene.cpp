#include "GameScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Utility/Utility.h"
#include "../Object/ObjectBase.h"
#include "../Object/Character/Player.h"
#include "../Object/ObjectManager.h"


GameScene::GameScene(SceneManager& manager) :SceneBase(manager)
{
	//�X�V�֐��̃Z�b�g
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&GameScene::LoadingDraw, this);
}

void GameScene::Load(void)
{
	// �ǂݍ��ݎ��ԏ�����
	loadingTime_ = 0.0f;

	//�񓯊��ǂݍ��݂�true�ɂ���
	SetUseASyncLoadFlag(true);

	//�v���C���[
	player_ = std::make_shared<Player>();
	player_->Load();

	//�I�u�W�F�N�g
	obj_ = std::make_unique<ObjectManager>();
	obj_->Load();


	obj_ = std::make_unique<ObjectBase>();
	obj_->Load();

	//�t�H���g
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		LOAD_FONT_SIZE,
		0);

	//�J����
	mainCamera->ChangeMode(Camera::MODE::FIXED_POINT);
	mainCamera->SetTargetPos(LOCAL_CAMERA_POS);
}

void GameScene::Init(void)
{
	player_->Init();
	obj_->Init();
	obj_->Init();
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
	//�t�H���g�폜
	DeleteFontToHandle(loadFont_);
}

void GameScene::LoadingUpdate(InputManager& ins)
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
		drawFunc_ = std::bind(&GameScene::NormalDraw, this);
	}
}

void GameScene::NormalUpdate(InputManager& ins)
{
	player_->Update();
	obj_->Update();

	obj_->Update();

	//�V�[���J��
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().
			ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameScene::LoadingDraw(void)
{
	//�unow loading�v�̕`��
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

	//�e��I�u�W�F�N�g�`�揈��
	obj_->Draw();
	player_->Draw();
	obj_->Draw();

	//�f�o�b�O�`��
	DebagDraw();
}

void GameScene::DebagDraw()
{
	////�f�o�b�O�n�̕`��͂����ɏ���
	//DrawBox(
	//	0, 0,
	//	Application::SCREEN_SIZE_X,
	//	Application::SCREEN_SIZE_Y,
	//	0xfff000,
	//	true);
}
