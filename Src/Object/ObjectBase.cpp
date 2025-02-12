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
	//X���֘A
	int SRand(0);				//�����̂͂��߂̐������w�肷��
	float posX;
	posX = GetRand(100);		//0����100�܂ł̃����_���̐��l�𐶐�

	//�I�u�W�F�N�g�̏����ʒu(�Ƃ肠���������)
	//X��:�����ʒu�����_��
	//Y��:�������߂����̂��Œ�
	//Z��:�Q�[����ʂ𒲐߂����̂��Œ�
	transform_.pos = { posX,0.0f,200.0f };
}

void ObjectBase::Update(void)
{
	//�V���O���g���ŃX�N���[�������擾
	auto& scr = ScrollManager::GetInstance();

	//Z���ړ��֘A
	//��ނ̂ݎ��{����//��ޑ��x��ScrManag���Ǘ�����
	transform_.pos.z = transform_.pos.z + scr.GetScrollSpeed();
}

void ObjectBase::Draw(void)
{
	//�f�o�b�O�p�Ƃ���3D�̋��̂�`�悷��
	DrawSphere3D(transform_.pos, 20.0f, 10, 0xffff00, 0xffff00, true);
}

const Transform& ObjectBase::GetTransform(void) const
{
	return transform_;
}
