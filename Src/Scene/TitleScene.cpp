#include "../Application.h"
#include "../Utility/Utility.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/TextManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/Camera.h"
#include "TitleScene.h"
#include "../Object/Character/TitlePlayer.h"

TitleScene::TitleScene(SceneManager& manager) :SceneBase(manager)
{
	//各種初期化処理
	cnt_ = -1;
	deg_ = -1.0f;
	ex_ = -1.0f;
	exSpeed_ = -1.0f;
	mesFont_ = -1;

	int i = -1;
	for (auto& img : imgTexts_) { img = &i; }

	//更新関数のセット
	updataFunc_ = [&](InputManager& input) {LoadingUpdate(input); };

	//描画関数のセット
	drawFunc_ = std::bind(&TitleScene::LoadingDraw, this);

	//初期化
	titlePlayer_ = nullptr;
}

void TitleScene::Load(void)
{
	// 読み込み時間初期化
	loadingTime_ = 0.0f;

	//非同期読み込みをtrueにする
	SetUseASyncLoadFlag(true);

	// タイトル
	imgTexts_[0] = ResourceManager::GetInstance().Load(ResourceManager::SRC::ALPHABET).handleIds_;
	imgTitle_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::TITLE).handleId_;
	imgTitleUI_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::TITLE_UI).handleId_;
	imgTitleBackGround_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::TITLE_BACKGROUND).handleId_;
	//フォント
	loadFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::DOT).c_str(),
		LOAD_FONT_SIZE,
		0);
	mesFont_ = CreateFontToHandle(
		TextManager::GetInstance().GetFontName(TextManager::FONT_TYPE::BOKUTACHI).c_str(),
		MES_FONT_SIZE,
		0);

	//タイトルにプレイヤーをロードする
	titlePlayer_ = std::make_unique<TitlePlayer>();
	titlePlayer_->Load();
}


void TitleScene::Init(void)
{
	//メッシュの設定
	MeshInit();

	//変数初期化
	cnt_ = 0;
	deg_ = 2.0f;// 角度
	ex_ = 1.0f;
	exSpeed_ = 0.2f;
	alpha_ = 256;
	fade_ = -1;

	//初期化
	titlePlayer_->Init();
}

void TitleScene::Update(InputManager& input)
{
	updataFunc_(input);

	return;
}

void TitleScene::Draw(void)
{
	drawFunc_();

	return;
}

void TitleScene::Release(void)
{
	DeleteFontToHandle(loadFont_);
	DeleteFontToHandle(mesFont_);

	//解放処理
	titlePlayer_->Release();
}

void TitleScene::CommonDraw()
{
}

void TitleScene::LoadingUpdate(InputManager& input)
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
		drawFunc_ = std::bind(&TitleScene::NormalDraw, this);
	}
}

void TitleScene::NormalUpdate(InputManager& ins)
{
	MeshUpdate();

	if (alpha_ > 256 ||
		alpha_ < 128)
	{
		fade_ *= -1;
	}
	alpha_ += fade_;

	//更新処理
	titlePlayer_->Update();


	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT);
	}
}

void TitleScene::LoadingDraw(void)
{
	//「now loading」の描画
	DrawNowLoading();
}

void TitleScene::NormalDraw(void)
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);

	//背景
	DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, 0xffb6c1, true);
	for (int j = 0; j < MESH_FONT_NUM; j++)
	{
		VERTEX3D vertices1[3] = { fonts_[j].vertices_[0],fonts_[j].vertices_[1], fonts_[j].vertices_[2] };
		VERTEX3D vertices2[3] = { fonts_[j].vertices_[1],fonts_[j].vertices_[3], fonts_[j].vertices_[2] };

		DrawPolygon3D(vertices1, 1, *imgTexts_[0], true); // 三角形1
		DrawPolygon3D(vertices2, 1, *imgTexts_[0], true); // 三角形2
	}
	
	//タイトル背景
	DrawRotaGraph(500, 375, 0.75, 0.f, imgTitleBackGround_, true);
	
	//タイトルロゴ生成
	DrawRotaGraph(525,200, 0.5,0.f, imgTitle_, true);
	

	

	SetDrawScreen(sceneManager_.GetMainScreen());

	//描画処理
	titlePlayer_->Draw();

	//int cx = Application::SCREEN_HALF_X;
	//int cy = Application::SCREEN_HALF_Y;

	////シーン遷移
	//std::string mes = "スペースを押してね";
	//DrawFormatStringToHandle(
	//	cx - mes.length() * MES_FONT_SIZE / 2,
	//	cy + 150,
	//	0xffffff,
	//	mesFont_,
	//	mes.c_str());

	Fade();
}

void TitleScene::MeshInit()
{
#pragma region メッシュ用変数の宣言

	VECTOR norm = VGet(0.0f, 0.0f, -1.0f);	//法線ベクトルの初期化用
	MeshText m;								//メッシュフォントの仮領域
	VECTOR fPos = { -180,100,0 };			//一文字目の初期座標

	for (int i = 0; i < MESH_FONT_NUM; i++)
	{
		switch (i)
		{
		case 0: //L
			m.fontNumber_ = { 1,1 };
			break;

		case 1: //e
			m.fontNumber_ = { 0,3 };
			break;

		case 2: //t
			m.fontNumber_ = { 5,4 };
			break;

		case 3: //s
			m.fontNumber_ = { 4,4 };
			break;

		case 4: //G
			m.fontNumber_ = { 6,0 };
			break;

		case 5: //a
			m.fontNumber_ = { 6,2 };
			break;

		case 6: //m
			m.fontNumber_ = { 8,3 };
			break;

		case 7: //e
			m.fontNumber_ = { 0,3 };
			break;

		case 8: //P
			m.fontNumber_ = { 5,1 };
			break;

		case 9: //l
			m.fontNumber_ = { 7,3 };
			break;

		case 10: //a
			m.fontNumber_ = { 6,2 };
			break;

		case 11: //y
			m.fontNumber_ = { 0,5 };
			break;

		}

		//画像分割情報
		Vector2 num = m.fontNumber_;

		//描画中央位置
		m.center_ = VAdd(fPos, { i * TEXT_INTERVEL , 0 , 0 });

		//左上
		m.vertices_[0].pos = VAdd(m.center_, { FONT_SIZE_H, FONT_SIZE_H, 0.0f });
		m.vertices_[0].norm = norm;
		m.vertices_[0].dif = GetColorU8(255, 255, 255, 255);
		m.vertices_[0].u = 1.0f / ALPHABET_NUM_X * num.x;
		m.vertices_[0].v = 1.0f / ALPHABET_NUM_Y * num.y;

		//右上
		m.vertices_[1].pos = VAdd(m.center_, { -FONT_SIZE_H, FONT_SIZE_H, 0.0f });
		m.vertices_[1].norm = norm;
		m.vertices_[1].dif = GetColorU8(255, 0, 255, 255);
		m.vertices_[1].u = 1.0f / ALPHABET_NUM_X * (num.x + 1);
		m.vertices_[1].v = 1.0f / ALPHABET_NUM_Y * num.y;

		//左下
		m.vertices_[2].pos = VAdd(m.center_, { FONT_SIZE_H, -FONT_SIZE_H, 0.0f });
		m.vertices_[2].norm = norm;
		m.vertices_[2].dif = GetColorU8(0, 255, 255, 255);
		m.vertices_[2].u = 1.0f / ALPHABET_NUM_X * num.x;
		m.vertices_[2].v = 1.0f / ALPHABET_NUM_Y * (num.y + 1);

		//右下
		m.vertices_[3].pos = VAdd(m.center_, { -FONT_SIZE_H, -FONT_SIZE_H, 0.0f });
		m.vertices_[3].norm = norm;
		m.vertices_[3].dif = GetColorU8(0, 255, 255, 255);
		m.vertices_[3].u = 1.0f / ALPHABET_NUM_X * (num.x + 1);
		m.vertices_[3].v = 1.0f / ALPHABET_NUM_Y * (num.y + 1);
#pragma endregion

		//相対座標
		for (int j = 0; j < VERTEXS; j++)
		{
			m.relative_[j] = VSub(m.vertices_[j].pos, m.center_);
		}

		m.state_ = ROT_STATE::START;
		m.rots_ = 0.0f;

		//情報の格納
		fonts_[i] = m;
	}
}

void TitleScene::MeshUpdate()
{
	//回転情報を求める
	Quaternion qua = Quaternion::AngleAxis(Utility::Deg2RadF(deg_), Utility::AXIS_Y);

	//カウント更新
	cnt_++;

	for (int j = 0; j < MESH_FONT_NUM; j++)
	{
		//処理を行うか判断
		if (cnt_ <= j * 20 ||							//カウントが一定量満たしてないとき
			fonts_[j].state_ == ROT_STATE::NONE)		//回転し終わった時
		{
			continue;	//処理を行わない
		}

		//z軸移動量
		float move = -1.0f;

		//中心位置を動かす
		if (fonts_[j].state_ == ROT_STATE::HALF) { move *= -1; }
		fonts_[j].center_.z += move;

		for (int i = 0; i < VERTEXS; i++)
		{
			//回転後の相対座標
			fonts_[j].relative_[i] = Quaternion::PosAxis(qua, fonts_[j].relative_[i]);

			//座標
			fonts_[j].vertices_[i].pos = VAdd(fonts_[j].center_, fonts_[j].relative_[i]);
		}

		//回転量の加算
		fonts_[j].rots_ += deg_;

		//ステートごとの処理
		switch (fonts_[j].state_)
		{
		case ROT_STATE::START:
			if (fonts_[j].rots_ >= 90.0f)
			{
				fonts_[j].state_ = ROT_STATE::HALF;
			}
			break;

		case ROT_STATE::HALF:
			if (fonts_[j].rots_ >= 180.0f)
			{
				fonts_[j].rots_ = 0.0f;		//回転量初期化
				fonts_[j].state_ = ROT_STATE::NONE;

				//ラストの処理を終えたら
				if (j == MESH_FONT_NUM - 1)
				{
					cnt_ = 0;
					for (int i = 0; i < MESH_FONT_NUM; i++)
					{
						fonts_[i].state_ = ROT_STATE::START;
					}
				}
			}
			break;

		}
	}
}

void TitleScene::Fade()
{
	//タイトルUI
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, alpha_);

	DrawRotaGraph(525, 375, 0.3f, 0.f, imgTitleUI_, true);

	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 256);
}
