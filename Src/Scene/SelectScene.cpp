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
	updateFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//描画関数のセット
	drawFunc_ = std::bind(&SelectScene::LoadingDraw, this);

	//初期化
	image_ = -1;
	imgSelect_ = -1;
	imgSpeech_ = -1;
	step_ = -1.0f;
}

void SelectScene::Load()
{
	// 読み込み時間初期化
	loadingTime_ = 0.0f;

	//非同期読み込みを実行する
	SetUseASyncLoadFlag(true);

	//フォント
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::HANAZOME).c_str(),
		LOAD_FONT_SIZE,
		0);	

	//画像の読み込み
	image_=LoadGraph( "Data/Image/select.png");
	imgSelect_ =LoadGraph( "Data/Image/TackleSelect.png");
	imgSpeech_ =LoadGraph( "Data/Image/Speech.png");

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

void SelectScene::Init()
{
	step_ = 0.0f; // ステップを初期化

	//音声再生
	SoundManager::GetInstance().AdjustVolume(SoundManager::SOUND::SELECT_BGM, VOLUME);
	SoundManager::GetInstance().Play(SoundManager::SOUND::SELECT_BGM);
}

void SelectScene::Update(InputManager& input)
{
	updateFunc_(input);
	return;
}

void SelectScene::Draw()
{
	drawFunc_();
	return;
}

void SelectScene::CommonDraw()
{
}

void SelectScene::Release()
{
	//フォント削除
	DeleteFontToHandle(loadFont_);

	//画像の解放
	DeleteGraph(imgSpeech_);
	DeleteGraph(imgSelect_);
	DeleteGraph(image_);

	//音楽を停止
	SoundManager::GetInstance().Stop(SoundManager::SOUND::SELECT_BGM);
	SoundManager::GetInstance().Stop(SoundManager::SOUND::CHANGE_SCENE_SE);
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
		updateFunc_ = [&](InputManager& input) {NormalUpdate(input); };

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

	step_ += PERIOD; // ステップを進める
}

void SelectScene::LoadingDraw()
{
	DrawNowLoading();
}

void SelectScene::NormalDraw()
{
	//画面の描画
	DrawExtendGraph(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, image_, TRUE);

	// 揺れによるY座標のオフセットを計算（sin波を使う）
	float offsetY = sinf(step_) * AMPLITUDE;

	// 画像の描画位置
	int drawX = SPEECH_POS_X; // 任意のX位置
	int drawY = SPEECH_POS_Y + (int)offsetY; // 揺れを加えたY位置

	//スピーチバブルの描画
	DrawRotaGraph(
		drawX,
		drawY,
		1.0f,
		0.0f,
		imgSpeech_,
		true,
		false);

	// 楕円を描画
	//中心位置を決める
	Vector2 cPos = { 0, 0 };
	int cr = 0;
	if (DataBank::GetInstance().Output().autoTackle_)
	{
		cPos = { ON_POS_X, ON_POS_Y }; cr = 0xff0000; 
	}
	else 
	{
		cPos = { OFF_POS_X, OFF_POS_Y }; cr = 0x0000ff;
	}
	DrawRotaGraph(
		cPos.x,
		cPos.y,
		1.0f,
		0.0f,
		imgSelect_,
		true,
		false);
}

void SelectScene::CheckPlayerTackle()
{
	auto & data = DataBank::GetInstance();
	//オンの時はオフ
	if (data.Output().autoTackle_) 
	{ 
		data.Input(false);
		SoundManager::GetInstance().Play(SoundManager::SOUND::SWITCH_OFF_SE);
	}
	//オフの時はオン
	else 
	{ 
		data.Input(true);
		SoundManager::GetInstance().Play(SoundManager::SOUND::SWITCH_ON_SE);
	}
}
