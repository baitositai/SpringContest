#include "../../Manager/SceneManager.h"
#include "../../Manager/ScrollManager.h"
#include "LifeItem.h"
#include "PowerItem.h"
#include "Enemy.h"
#include "Gimmick.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	step_ = -1.0f;
	objs_.clear();
}

void ObjectManager::Load()
{
	//最初に複数個オブジェクトを生成しておく
	for (int i = 0; i < ENEMY_CREATE_CNT; i++) {objs_.push_back(std::make_unique<Enemy>());}	//敵
	for (int i = 0; i < GIMIC_CREATE_CNT; i++) {objs_.push_back(std::make_unique<Gimmick>());}	//ギミック
	for (int i = 0; i < LIFE_CREATE_CNT; i++) {objs_.push_back(std::make_unique<LifeItem>());}	//体力回復アイテム
	for (int i = 0; i < POW_CREATE_CNT; i++) {objs_.push_back(std::make_unique<PowerItem>());}	//パワーの回復アイテム
	for (auto& obj : objs_) { obj->Load(); }
}

void ObjectManager::Init()
{
	//各種オブジェクトの初期化処理
	for (auto& obj : objs_) 
	{
		obj->Init();
	}

	//オブジェクトのスクロールインターバル用ステップ
	step_ = 0.0f;
}

void ObjectManager::Update()
{
	//ステップ更新
	step_ -= SceneManager::GetInstance().GetDeltaTime();

	//スクロールさせるか調べる
	if (step_ <= 0.0f) {
		//スクロールを開始する処理をさせる
		ScrollStart();
	}

	//各種オブジェクトの更新処理
	for (auto& obj : objs_)
	{

		//更新処理
		obj->Update();

		//位置が一定のラインへ来たらスクロールをやめる
		if (ScrollManager::SCROLL_FINISH_LINE > obj->GetTransform().pos.z)
		{
			obj->ChangeState(ObjectBase::STATE::NONE);
		}
	}
}

void ObjectManager::Draw()
{
	//各種オブジェクトの描画処理
	for (auto& obj : objs_) 
	{
		obj->Draw();
	}
}

void ObjectManager::Release()
{
	for (auto& obj : objs_)
	{
		obj->Release();
	}
}

void ObjectManager::ScrollStart()
{
	//スクロールしてないオブジェクト配列
	std::vector<ObjectBase*> noScrollObjs;

	// スクロールしていないオブジェクトを収集
	for (auto& obj : objs_) 
	{
		//スクロールしていないオブジェクト
		if (obj->GetState() == ObjectBase::STATE::NONE)
		{
			//非スクロール配列に格納
			noScrollObjs.push_back(obj.get());
		}
	}

	// スクロールしていないオブジェクト配列から、ランダムに1つ選択
	if (!noScrollObjs.empty()) 
	{
		int index = rand() % noScrollObjs.size();
		noScrollObjs[index]->ChangeState(ObjectBase::STATE::SCROLL);
	}

	//ステップの初期化
	step_ = NextStartSecond();
}

float ObjectManager::NextStartSecond()
{
	int range = static_cast<int>(INTERVEL_SECOND_MAX - INTERVEL_SECOND_MIN);
	float randValue = static_cast<float>(GetRand(range)) / RAND_MAX;  // 0.0f から 1.0f の間のランダム値を生成
	return INTERVEL_SECOND_MIN + randValue * range;  // 生成した値を範囲にスケーリング
}