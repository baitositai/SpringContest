#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "ObjectBase.h"
#include "../Manager/ScrollManager.h"

ObjectBase::ObjectBase(void)
	: resMng_(ResourceManager::GetInstance()),
	scnMng_(SceneManager::GetInstance())
{
}

ObjectBase::~ObjectBase(void)
{
}

void ObjectBase::Load(void)
{
}

void ObjectBase::Init(void)
{
	//X軸関連
	int SRand(0);				//乱数のはじめの数字を指定する
	float posX;
	posX = GetRand(100);		//0から100までのランダムの数値を生成

	//オブジェクトの初期位置(とりあえず一つだけ)
	//X軸:初期位置ランダム
	//Y軸:高さ調節したのち固定
	//Z軸:ゲーム画面を調節したのち固定
	transform_.pos = { posX,0.0f,200.0f };
}

void ObjectBase::Update(void)
{
	//シングルトンでスクロール情報を取得
	auto& scr = ScrollManager::GetInstance();

	//Z軸移動関連
	//後退のみ実施する//後退速度はScrManagが管理する
	transform_.pos.z = transform_.pos.z + scr.GetScrollSpeed();
}

void ObjectBase::Draw(void)
{
	//デバッグ用として3Dの球体を描画する
	DrawSphere3D(transform_.pos, 20.0f, 10, 0xffff00, 0xffff00, true);
}

const Transform& ObjectBase::GetTransform(void) const
{
	return transform_;
}
