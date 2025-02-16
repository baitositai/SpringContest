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
	
	//X座標生成をランダムにしたいよ
	//最初に乱数の初期値を設定する
	int SRand(0);

	float posX;
	posX = GetRand(100);

	//とりあえずのZ軸座標設定
	transform_.pos = { posX,0.0f,200.0f };
}

void ObjectBase::Update(void)
{
	auto& scr = ScrollManager::GetInstance();

	//Z軸移動関連

	//前後移動
	
	transform_.pos.z = transform_.pos.z + scr.GetScrollSpeed();
	
	/*else if (CheckHitKey(KEY_INPUT_A))
	{
		transform_.pos.z = transform_.pos.z + 5.f;
	}*/
	//左右移動
	/*if (CheckHitKey(KEY_INPUT_A))
	{
		transform_.pos.x = transform_.pos.x - 5.f;
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		transform_.pos.x = transform_.pos.x - 5.f;
	}*/

}

void ObjectBase::Draw(void)
{
	DrawSphere3D(transform_.pos, 20.0f, 10, 0xffff00, 0xffff00, true);
}

const Transform& ObjectBase::GetTransform(void) const
{
	return transform_;
}
