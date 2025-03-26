#include "StageBase.h"
#include "StageDefault.h"
#include "StageManager.h"
#include "StageLeft.h"
#include "StageRight.h"

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
	/*	case StageBase::STAGE_TYPE::STAGELEFT:
			newStage = new StageLeft();
			break;
		case StageBase::STAGE_TYPE::STAGERIGHT:
			newStage = new StageRight();
			break;*/
		}

		newStage->Init();

		//出現座標
		Transform spawnPos = newStage->GetTransform();
		

		//ワーニング回避のために一旦初期化
		spawnPos.pos.x = 0;
		spawnPos.pos.y = 0;
		spawnPos.pos.z = 0;

		//出現位置設定
		switch (randType)
		{
		case StageBase::STAGE_TYPE::STAGE:
			if (sSize == 0)
			{
				spawnPos.pos.x = 1000;
				spawnPos.pos.y = -1000;
				spawnPos.pos.z = 2000;
			}
			if (sSize == 1)
			{
				spawnPos.pos.x = 1000;
				spawnPos.pos.y = -1000;
				spawnPos.pos.z = 2000 + StageBase::SIZE_Z;
			}
			if (sSize == 2)
			{
				spawnPos.pos.x = 1000;
				spawnPos.pos.y = -1000;
				spawnPos.pos.z = 2000 + StageBase::SIZE_Z * 2;
			}
			break;
		}

		//座標の設定
		newStage->SetPos(spawnPos);

		//動的配列に追加
		stages_.push_back(newStage);

		stageSpawn_++;
	}

	CheckStagePos();
	
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

void StageManager::CheckStagePos()
{

	//出現しているステージすべてを確認する
	size_t sSize = stages_.size();
	for (int i = 0; i < sSize; i++)
	{
		if (stages_[i]->GetTransform().pos.z + StageBase::SIZE_Z < 0)
		{
			stages_.erase(stages_.begin() + i);
			sSize--;
			stageSpawn_--;
		}
	}

}
