#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "HinderObject.h"

HinderObject::HinderObject()
{
	//������
	objs_.clear();

	int i = -1;
	imgs_ = &i;
}

void HinderObject::Load()
{
	//�摜�ǂݍ���
	imgs_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::HINDER_OBJS).handleIds_;
}

void HinderObject::Init()
{
	objs_.clear();
}

void HinderObject::Update()
{
	//���g���Ȃ��ꍇ�����𔲂���
	if (objs_.empty()) { return; }

	//�ʒu�X�V
	for (Object& omu : objs_)
	{
		//�ړ�
		omu.pos_.x += omu.vec_.x;
		omu.pos_.y += omu.vec_.y;

		// ��ʒ[�ł̔��ˏ���
		if (omu.pos_.x <= 0 || omu.pos_.x + IMG_SIZE >= Application::SCREEN_HALF_X)
		{
			Reflect(omu.vec_, 1.0f, 0.0f);  // �����ȕ� (�@��: x����)
			// ��ʓ��ɉ����߂�
			omu.pos_.x += static_cast<int>(omu.vec_.x * 0.1f);
		}
		if (omu.pos_.y <= 0 || omu.pos_.y + IMG_SIZE >= Application::SCREEN_SIZE_Y)
		{
			Reflect(omu.vec_, 0.0f, 1.0f);  // �����ȕ� (�@��: y����)
			// ��ʓ��ɉ����߂�
			omu.pos_.y += static_cast<int>(omu.vec_.y * 0.1f);
		}

		// �x�N�g���̐�Βl������������Ƃ��ɍă����_����
		double magnitude = sqrt(omu.vec_.x * omu.vec_.x + omu.vec_.y * omu.vec_.y);
		if (magnitude < 0.01f) 
		{
			float angle = static_cast<float>(GetRand(RAND_RANGE) * DX_PI / 180.0f);
			omu.vec_.x = static_cast<int>(cosf(angle) * SPEED);
			omu.vec_.y = static_cast<int>(sinf(angle) * SPEED);
		}
	}
}

void HinderObject::Draw()
{
	//���g���Ȃ��ꍇ�����𔲂���
	if (objs_.empty()) { return; }

	for (Object& omu : objs_)
	{
		//�`��
		DrawGraph(
			omu.pos_.x,
			omu.pos_.y,
			imgs_[omu.type_],
			true);
	}
}

void HinderObject::AddObject(const int num)
{
	//������
	for (int i = 0; i < num; i++)
	{
		Object omu;
		//�����ʒu(�����_��)
		omu.pos_.x = GetRand(Application::SCREEN_HALF_X - HINDER_SIZE -1);
		omu.pos_.y = GetRand(Application::SCREEN_SIZE_Y - HINDER_SIZE -1);
		// �p�x�����W�A���ɕϊ����đ��x�x�N�g���ɕϊ�
		omu.vec_.x = static_cast<int>(SPEED * cos(ANGLE * DX_PI / 180.0f));
		omu.vec_.y = static_cast<int>(SPEED * sin(ANGLE * DX_PI / 180.0f));
		//�摜��ނ����߂�
		omu.type_ = GetRand(HINDER_NUM_X * HINDER_NUM_Y - 1);
		//�ǉ�
		objs_.emplace_back(omu);
	}
}

void HinderObject::Reflect(Vector2& vec, float nx, float ny)
{
	float dot = vec.x * nx + vec.y * ny;

	//���˃x�N�g���̌v�Z
	vec.x = static_cast<int>(vec.x - 2.0f * dot * nx);
	vec.y = static_cast<int>(vec.y - 2.0f * dot * ny);
}
