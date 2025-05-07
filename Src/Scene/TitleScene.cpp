#include "../Application.h"
#include "../Utility/Utility.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include "../Object/Character/TitlePlayer.h"
#include "../Object/TitleMesh.h"
#include "TitleScene.h"


TitleScene::TitleScene(SceneManager& manager) :SceneBase(manager)
{
	//�e�평��������
	imgTitle_ = -1;
	imgTitleBackGround_ = -1;
	changeSceneStep_ = -1.0f;

	int i = -1;

	//�X�V�֐��̃Z�b�g
	updateFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&TitleScene::LoadingDraw, this);

	//������
	titlePlayer_ = nullptr;
	titleMesh_ = nullptr;
}

void TitleScene::Load()
{
	// �ǂݍ��ݎ��ԏ�����
	loadingTime_ = 0.0f;

	//�񓯊��ǂݍ��݂��s��
	SetUseASyncLoadFlag(true);

	// �^�C�g��
	imgTitle_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::TITLE).handleId_;
	imgTitleBackGround_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::TITLE_BACKGROUND).handleId_;

	//�t�H���g
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::DOT).c_str(),
		LOAD_FONT_SIZE,
		0);
	mesFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::BOKUTACHI).c_str(),
		MES_FONT_SIZE,
		0);

	//�T�E���h�̃��[�h
	SoundManager::GetInstance().Add(
		SoundManager::TYPE::BGM,
		SoundManager::SOUND::TITLE_BGM,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::TITLE_BGM).handleId_);

	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::CHANGE_SCENE_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::CHANGE_SCENE_SE).handleId_);

	//�^�C�g���Ƀv���C���[�����[�h����
	titlePlayer_ = std::make_unique<TitlePlayer>();
	titlePlayer_->Load();

	//���b�V��
	titleMesh_ = std::make_unique<TitleMesh>();
	titleMesh_->Load();
}


void TitleScene::Init()
{
	//�ϐ�������
	changeSceneStep_ = CHANGE_SCENE_SECOND;

	//�v���C���[
	titlePlayer_->Init();

	//���b�V��
	titleMesh_->Init();

	//���ʐݒ�
	SoundManager::GetInstance().AdjustVolume(SoundManager::SOUND::TITLE_BGM, VOLUME);

	//���y�Đ�
	SoundManager::GetInstance().Play(SoundManager::SOUND::TITLE_BGM);
}

void TitleScene::Update(InputManager& input)
{
	updateFunc_(input);

	return;
}

void TitleScene::Draw()
{
	drawFunc_();

	return;
}

void TitleScene::Release()
{
	DeleteFontToHandle(loadFont_);
	DeleteFontToHandle(mesFont_);

	//���y��~
	SoundManager::GetInstance().Stop(SoundManager::SOUND::CHANGE_SCENE_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::TITLE_BGM);
}

void TitleScene::CommonDraw()
{
}

void TitleScene::LoadingUpdate(InputManager& input)
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
		updateFunc_ = [&](InputManager& input) {NormalUpdate(input); };
		
		//�`��֐��̃Z�b�g
		drawFunc_ = std::bind(&TitleScene::NormalDraw, this);
	}
}

void TitleScene::NormalUpdate(InputManager& ins)
{
	//�X�V����
	titlePlayer_->Update();

	//���b�V��
	titleMesh_->Update();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		//���ʉ��Đ�
		SoundManager::GetInstance().Play(SoundManager::SOUND::CHANGE_SCENE_SE);
		//�V�[���J��
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT);
		//BGM��~
		SoundManager::GetInstance().Stop(SoundManager::SOUND::TITLE_BGM);
	}

	changeSceneStep_ -= SceneManager::GetInstance().GetDeltaTime();
	if (ins.IsTrgDown(KEY_INPUT_RETURN) ||
		changeSceneStep_ <= 0.0f)
	{
		//���ʉ��Đ�
		SoundManager::GetInstance().Play(SoundManager::SOUND::CHANGE_SCENE_SE);
		//�V�[���J��
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::MOVIE);
		//BGM��~
		SoundManager::GetInstance().Stop(SoundManager::SOUND::TITLE_BGM);
	}
}

void TitleScene::LoadingDraw()
{
	//�unow loading�v�̕`��
	DrawNowLoading();
}

void TitleScene::NormalDraw()
{
	//�^�C�g���w�i
	DrawExtendGraph(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, imgTitleBackGround_, true);

	//�^�C�g�����S
	DrawRotaGraph(LOGO_POS_X, LOGO_POS_Y, LOGO_RATE, 0.0f, imgTitle_, true);

	//���f���`��ɕK�v
	SetDrawScreen(sceneManager_.GetMainScreen());

	//���b�V��
	titleMesh_->Draw();

	//�L�����N�^�[
	titlePlayer_->Draw();
}