#include "MovieScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Utility/Utility.h"

MovieScene::MovieScene(SceneManager& manager) :SceneBase(manager)
{
	//�X�V�֐��̃Z�b�g
	updateFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//�`��֐��̃Z�b�g
	drawFunc_ = std::bind(&MovieScene::LoadingDraw, this);

	movie_ = -1;
}

void MovieScene::Load()
{
	movie_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::MOVIE).handleId_;
}

void MovieScene::Init()
{
	//����̍Đ�
	if (movie_ != -1)
	{
		PlayMovieToGraph(movie_);
	}
	else
	{
		//���[�r�[�������ꍇ�̓V�[���J��
		sceneManager_.ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void MovieScene::Update(InputManager& input)
{
	updateFunc_(input);
	return;
}

void MovieScene::Draw()
{
	drawFunc_();
	return;
}

void MovieScene::Release()
{
	DeleteFontToHandle(loadFont_);
}

void MovieScene::CommonDraw()
{
}

void MovieScene::LoadingUpdate(InputManager& ins)
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
		drawFunc_ = std::bind(&MovieScene::NormalDraw, this);
	}
}

void MovieScene::NormalUpdate(InputManager& ins)
{
	//�^�C�g���ɖ߂�
	if (ins.IsTrgDown(KEY_INPUT_SPACE) ||
		ins.IsTrgDown(KEY_INPUT_RETURN) ||
		GetMovieStateToGraph(movie_) == 0)
	{
		//�����~
		PauseMovieToGraph(movie_);
		//�Đ��ʒu���ŏ������
		SeekMovieToGraph(movie_, 0);
		//�V�[���J��
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void MovieScene::LoadingDraw()
{
	DrawNowLoading();
}

void MovieScene::NormalDraw()
{
	DrawExtendGraph(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, movie_, true);
}
