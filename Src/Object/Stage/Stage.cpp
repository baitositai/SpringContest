#include "../../Manager/ResourceManager.h"
#include "../../Manager/ScrollManager.h"
#include "../../Manager/DataBank.h"
#include "../../Utility/Utility.h"
#include "Stage.h"

Stage::Stage()
{
	stages_.clear();
}

Stage::~Stage()
{
}

void Stage::Load()
{
	//ステージのサイズを定義
	stages_.resize(CREATES);

	//モデルの初期化
	for (int i = 0; i < CREATES; i++) 
	{
		stages_[i].SetModel(ResourceManager::GetInstance().LoadModelDuplicate(
			ResourceManager::SRC::STAGE));
	}
}

void Stage::Init()
{
	//初期化
	int i = 0;
	for (Transform& stage : stages_)
	{
		stage.scl = SCLAE;
		stage.pos = DEFAULT_POS[i];
		stage.quaRot = Quaternion();
		stage.quaRotLocal =
			Quaternion::Euler({ 0.0f, Utility::Deg2RadF(180.0f), 0.0f });
		stage.Update();
		i++;
	}
}

void Stage::Update()
{
	ScrollManager& scr = ScrollManager::GetInstance();

	//更新処理
	for (Transform& stage : stages_)
	{
		//移動処理
		stage.pos.z -= scr.GetScrollSpeed(DataBank::GetInstance().Output().playerId_);

		//一定地点まで達したら
		if (stage.pos.z <= ScrollManager::SCROLL_FINISH_LINE)
		{
			stage.pos.z = DEFAULT_POS[CREATES - 1].z;
		}

		//トランスフォームの更新
		stage.Update();
	}
}

void Stage::Draw()
{
	//描画処理
	for (Transform& stage : stages_)
	{
		MV1DrawModel(stage.modelId);
	}
}
