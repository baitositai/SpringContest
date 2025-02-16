#include "ObjectBase.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	obj_ = nullptr;
}

void ObjectManager::Load()
{
	//�e��I�u�W�F�N�g�̓ǂݍ��݂Ə�������
	obj_ = std::make_shared<ObjectBase>();
	obj_->Load();
}

void ObjectManager::Init()
{
	//�e��I�u�W�F�N�g�̏���������
	obj_->Init();
}

void ObjectManager::Update()
{
	//�e��I�u�W�F�N�g�̍X�V����
	obj_->Update();
}

void ObjectManager::Draw()
{
	//�e��I�u�W�F�N�g�̕`�揈��
	obj_->Draw();
}

void ObjectManager::Release()
{
}
