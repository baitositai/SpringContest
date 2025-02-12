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
	//�Ƃ肠������Z�����W�ݒ�
	transform_.pos = { 100.0f,0.0f,200.0f };
}

void ObjectBase::Update(void)
{
	//Z���ړ��֘A

	//�O��ړ�
	if (CheckHitKey(KEY_INPUT_S))
	{
		transform_.pos.z = transform_.pos.z - 5.f;
	}
	else if (CheckHitKey(KEY_INPUT_A))
	{
		transform_.pos.z = transform_.pos.z + 5.f;
	}
	//���E�ړ�
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
