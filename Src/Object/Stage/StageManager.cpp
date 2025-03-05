#include "StageBase.h"
#include "StageDefault.h"
#include "StageManager.h"

StageManager::StageManager()
{
	stages_.clear();
	stageSpawnCounter_ = -1;
	stageSpawn_ = -1;
}

void StageManager::Load()
{
	//ステージの初期化
	size_t sSize = stages_.size();
	for (int i = 0; i < sSize; i++)
	{
		stages_[i]->Release();
		delete stages_[i];
	}
}

void StageManager::Init()
{	
	//初期化
	stageSpawnCounter_ = 0;
	stageSpawn_ = 0;
}

void StageManager::Update()
{
	//ステージの更新処理は動的配列で回す
	//出現しているアイテムはすべて更新する
	size_t sSize = stages_.size();
	for (int i = 0; i < sSize; i++)
	{
		stages_[i]->Update();
	}

	//ステージの出現カウントを増やす
	++stageSpawnCounter_;

	//出現カウントが指定値を超えたら
	if (stageSpawn_ < 3)
	{

		stageSpawnCounter_ = 0;

		//ステージを動的生成
		//ポインタに何もささない上程を設定するときは
		//nullptrをしようする
		StageBase* newStage = nullptr;

		//ステージの生成
		int stageTypeMaxNum = static_cast<int>(StageBase::STAGE_TYPE::MAX) - 1;

		//ステージのタイプをランダムで決定する
		int newStageType = GetRand(stageTypeMaxNum);

		//enmuで使用するためにステージのタイプに戻す
		StageBase::STAGE_TYPE randType = static_cast<StageBase::STAGE_TYPE>(newStageType);

		switch (randType)
		{
		case StageBase::STAGE_TYPE::STAGE:
			newStage = new StageDefault();
			break;
		}

		newStage->Init();

		//出現座標
		VECTOR spawnPos;

		//ワーニング回避のために一旦初期化
		spawnPos.x = 0;
		spawnPos.y = 0;
		spawnPos.z = 0;

		//出現位置設定
		switch (randType)
		{
		case StageBase::STAGE_TYPE::STAGE:
			if (sSize == 0)
			{
				spawnPos.x = 1000;
				spawnPos.y = -2000;
				spawnPos.z = 2000;
			}
			if (sSize == 1)
			{
				spawnPos.x = 1000;
				spawnPos.y = -2000;
				spawnPos.z = 2000 + StageBase::SIZE_Z;
			}
			if (sSize == 2)
			{
				spawnPos.x = 1000;
				spawnPos.y = -2000;
				spawnPos.z = 2000 + StageBase::SIZE_Z * 2;
			}
			break;
		}
		//座標の設定
		newStage->SetPos(spawnPos);

		//動的配列に追加
		stages_.push_back(newStage);

		stageSpawn_++;
	}
}

void StageManager::Draw()
{
	//ステージの描画も動的配列でまわす形に変更
	//出現しているアイテムすべてを描画する
	size_t sSize = stages_.size();
	for (int i = 0; i < sSize; i++)
	{
		stages_[i]->Draw();
	}
}

void StageManager::Release()
{
	for (auto& stage : stages_)
	{
		stage->Release();
		delete stage;
	}
}
