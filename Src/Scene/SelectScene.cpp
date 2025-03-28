#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/ScoreBank.h"
#include "../Manager/DataBank.h"
#include "../Utility/Utility.h"
#include "SelectScene.h"

SelectScene::SelectScene(SceneManager& manager) :SceneBase(manager)
{
	//更新関数のセット
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//描画関数のセット
	drawFunc_ = std::bind(&SelectScene::LoadingDraw, this);

	//初期化
	image_ = -1;
}

SelectScene::~SelectScene(void)
{
	SoundManager::GetInstance().Stop(SoundManager::SOUND::SWITCH_OFF_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::SWITCH_ON_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::CHANGE_SCENE_SE);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::SELECT_BGM);
}

void SelectScene::Load(void)
{
	// 読み込み時間初期化
	loadingTime_ = 0.0f;

	//非同期読み込みをtrueにする
	SetUseASyncLoadFlag(true);

	//フォント
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		LOAD_FONT_SIZE,
		0);	

	//画像の読み込み
	image_=LoadGraph( "Data/Image/select.png");

	//サウンドのロード
	SoundManager::GetInstance().Add(
		SoundManager::TYPE::BGM,
		SoundManager::SOUND::SELECT_BGM,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::SELECT_BGM).handleId_);

	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::CHANGE_SCENE_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::CHANGE_SCENE_SE).handleId_);

	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::SWITCH_ON_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::SWITCH_ON_SE).handleId_);

	SoundManager::GetInstance().Add(
		SoundManager::TYPE::SE,
		SoundManager::SOUND::SWITCH_OFF_SE,
		ResourceManager::GetInstance().Load(ResourceManager::SRC::SWITCH_OFF_SE).handleId_);
}

void SelectScene::Init(void)
{
	//音声再生
	SoundManager::GetInstance().Play(SoundManager::SOUND::SELECT_BGM);
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

void SelectScene::CommonDraw(void)
{
}

void SelectScene::Release(void)
{
	//フォント削除
	DeleteFontToHandle(loadFont_);

	//画像の解放
	DeleteGraph(image_);
}

void SelectScene::LoadingUpdate(InputManager& ins)
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
		drawFunc_ = std::bind(&SelectScene::NormalDraw, this);
	}
}

void SelectScene::NormalUpdate(InputManager& ins)
{
	//シーン遷移
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{		
		DataBank::GetInstance().Input(SceneManager::MODE::MARASON);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		SoundManager::GetInstance().Play(SoundManager::SOUND::CHANGE_SCENE_SE);
		SoundManager::GetInstance().Stop(SoundManager::SOUND::SELECT_BGM);
	}
	else if (ins.IsTrgDown(KEY_INPUT_W))
	{
		DataBank::GetInstance().Input(SceneManager::MODE::VS);
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
		SoundManager::GetInstance().Play(SoundManager::SOUND::CHANGE_SCENE_SE);
		SoundManager::GetInstance().Stop(SoundManager::SOUND::SELECT_BGM);
	}

	//プレイヤーの自動攻撃の有無
	if (ins.IsTrgDown(KEY_INPUT_RETURN))
	{
		CheckPlayerTackle();
	}
}

void SelectScene::LoadingDraw(void)
{
	DrawNowLoading();
}

void SelectScene::NormalDraw(void)
{
	//画面の描画
	DrawExtendGraph(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, image_, TRUE);
	// 楕円を描画
	//中心位置を決める
	Vector2 cPos = { 0, 0 };
	int cr = 0;
	if (DataBank::GetInstance().Output().autoTackle_) { cPos = { 350, 550 }; cr = 0xff0000; }
	else { cPos = { 500, 550 }; cr = 0x0000ff;}
	DrawOval(cPos.x, cPos.y, 80, 60, cr, false);
}

void SelectScene::CheckPlayerTackle()
{
	auto & data = DataBank::GetInstance();
	//オンの時はオフ
	if (data.Output().autoTackle_) { 
		data.Input(false);
		SoundManager::GetInstance().Play(SoundManager::SOUND::SWITCH_OFF_SE);
	}
	//オフの時はオン
	else { 
		data.Input(true);
		SoundManager::GetInstance().Play(SoundManager::SOUND::SWITCH_ON_SE);
	}
}
