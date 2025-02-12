#include "../Manager/ResourceManager.h"
#include "../Manager/SceneManager.h"
#include "ObjectBase.h"

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
	//とりあえずのZ軸座標設定
	transform_.pos = { 100.0f,0.0f,200.0f };
}

void ObjectBase::Update(void)
{
	//Z軸移動関連

	//前後移動
	if (CheckHitKey(KEY_INPUT_S))
	{
		transform_.pos.z = transform_.pos.z - 5.f;
	}
	else if (CheckHitKey(KEY_INPUT_A))
	{
		transform_.pos.z = transform_.pos.z + 5.f;
	}
	//左右移動
	if (CheckHitKey(KEY_INPUT_A))
	{
		transform_.pos.x = transform_.pos.x - 5.f;
	}
	else if (CheckHitKey(KEY_INPUT_D))
	{
		transform_.pos.x = transform_.pos.x - 5.f;
	}

}

void ObjectBase::Draw(void)
{
	DrawSphere3D(transform_.pos, 20.0f, 10, 0xffff00, 0xffff00, true);
}

const Transform& ObjectBase::GetTransform(void) const
{
	return transform_;
}
