#include "ObjectBase.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	obj_ = nullptr;
}

void ObjectManager::Load()
{
	//各種オブジェクトの読み込みと初期生成
	obj_ = std::make_shared<ObjectBase>();
	obj_->Load();
}

void ObjectManager::Init()
{
	//各種オブジェクトの初期化処理
	obj_->Init();
}

void ObjectManager::Update()
{
	//各種オブジェクトの更新処理
	obj_->Update();
}

void ObjectManager::Draw()
{
	//各種オブジェクトの描画処理
	obj_->Draw();
}

void ObjectManager::Release()
{
}
