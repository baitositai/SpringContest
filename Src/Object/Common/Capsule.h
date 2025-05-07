#pragma once
#include <DxLib.h>
class Transform;

class Capsule
{

public :

	// �f�o�b�O���̊ȈՃJ�v�Z���\���̐F
	static constexpr int COLOR = 0xffffff;

	// �R���X�g���N�^
	// �J�v�Z��������I�u�W�F�N�g���w�肷��
	Capsule(const Transform& parent);
	Capsule(const Capsule& base, const Transform& parent);

	// �f�X�g���N�^
	~Capsule();

	// �`��
	void Draw();

	// �eTransform����̑��Έʒu���擾
	VECTOR GetLocalPosTop() const;
	VECTOR GetLocalPosDown() const;

	// �eTransform����̑��Έʒu���Z�b�g
	void SetLocalPosTop(const VECTOR& pos);
	void SetLocalPosDown(const VECTOR& pos);

	// ���[���h���W���擾
	VECTOR GetPosTop() const;
	VECTOR GetPosDown() const;

	// ���΍��W����]�����ă��[���h���W�Ŏ擾����
	VECTOR GetRotPos(const VECTOR& localPos) const;

	// ���a
	float GetRadius() const;
	void SetRadius(float radius);

	// ����
	float GetHeight() const;

	// �J�v�Z���̒��S���W
	VECTOR GetCenter() const;

private :

	// �J�v�Z�����������鑊��
	const Transform& transformParent_;

	// �eTransform����̑��Έʒu(�㑤)
	VECTOR localPosTop_;

	// �eTransform����̑��Έʒu(����)
	VECTOR localPosDown_;

	// ���a
	float radius_;

};
