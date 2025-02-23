#include "../../Manager/SceneManager.h"
#include "../../Manager/ScrollManager.h"
#include "LifeItem.h"
#include "PowerItem.h"
#include "Enemy.h"
#include "Gimic.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
	step_ = -1.0f;
	objs_.clear();
}

void ObjectManager::Load()
{
	//�ŏ��ɕ����I�u�W�F�N�g�𐶐����Ă���
	for (int i = 0; i < ENEMY_CREATE_CNT; i++) {objs_.push_back(std::make_unique<Enemy>());}
	for (int i = 0; i < GIMIC_CREATE_CNT; i++) {objs_.push_back(std::make_unique<Gimic>());}
	for (int i = 0; i < LIFE_CREATE_CNT; i++) {objs_.push_back(std::make_unique<LifeItem>());}
	for (int i = 0; i < POW_CREATE_CNT; i++) {objs_.push_back(std::make_unique<PowerItem>());}
	for (auto& obj : objs_){
		obj->Load();
	}
}

void ObjectManager::Init()
{
	//�e��I�u�W�F�N�g�̏���������
	for (auto& obj : objs_) {
		obj->Init();
	}

	step_ = 0.0f;
}

void ObjectManager::Update()
{
	//�X�e�b�v�X�V
	step_ -= SceneManager::GetInstance().GetDeltaTime();

	//�X�N���[�������邩���ׂ�
	if (step_ <= 0.0f) {
		ScrollStart();
	}

	//�e��I�u�W�F�N�g�̍X�V����
	for (auto& obj : objs_) {

		//�X�V����
		obj->Update();

		//�ʒu�����̃��C���֗�����X�N���[������߂�
		if (ScrollManager::SCROLL_FINISH_LINE > obj->GetTransform().pos.z)
		{
			obj->ChangeState(ObjectBase::STATE::NONE);
		}
	}
}

void ObjectManager::Draw()
{
	//�e��I�u�W�F�N�g�̕`�揈��
	for (auto& obj : objs_) {
		obj->Draw();
	}
}

void ObjectManager::Release()
{
}

void ObjectManager::ScrollStart()
{
	std::vector<ObjectBase*> noScrollObjs;

	// �X�N���[�����Ă��Ȃ��I�u�W�F�N�g�����W
	for (auto& obj : objs_) {
		if (obj->GetState() == ObjectBase::STATE::NONE) {
			noScrollObjs.push_back(obj.get());
		}
	}

	// �X�N���[�����Ă��Ȃ��I�u�W�F�N�g������ꍇ�A�����_���ɑI��
	if (!noScrollObjs.empty()) {
		int index = rand() % noScrollObjs.size();
		noScrollObjs[index]->ChangeState(ObjectBase::STATE::SCROLL);
	}

	//�X�e�b�v�̏�����
	step_ = NextStartSecond();
}

float ObjectManager::NextStartSecond()
{
	float range = INTERVEL_SECOND_MAX - INTERVEL_SECOND_MIN;
	float randValue = static_cast<float>(GetRand(range)) / RAND_MAX;  // 0.0f ���� 1.0f �̊Ԃ̃����_���l�𐶐�
	return INTERVEL_SECOND_MIN + randValue * range;  // ���������l��͈͂ɃX�P�[�����O
}