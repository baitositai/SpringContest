#pragma once
#include <DxLib.h>
#include "../../Common/Quaternion.h"
#include "Collider.h"

/// <summary>
/// ���f������̊�{���
/// �傫���FVECTOR�
/// ��]�@�FQuaternion�
/// �ʒu�@�FVECTOR�
/// </summary>
class Transform
{

public:

	// �R���X�g���N�^
	Transform();
	Transform(int model);

	// �f�X�g���N�^
	~Transform();

	// ���f���̃n���h��ID
	int modelId;

	// �傫��
	VECTOR scl;
	// ��]
	VECTOR rot;
	// �ʒu
	VECTOR pos;
	VECTOR localPos;

	MATRIX matScl;
	MATRIX matRot;
	MATRIX matPos;

	// ��]
	Quaternion quaRot;

	// ���[�J����]
	Quaternion quaRotLocal;

	// �R���C�_
	std::shared_ptr<Collider> collider;

	/// <summary>
	/// ���f������̊�{���X�V
	/// </summary>
	/// <param name=""></param>
	void Update();

	void SetModel(int modelHId);

	void MakeCollider(Collider::TYPE type);

	// �O���������擾
	VECTOR GetForward() const;

	// ����������擾
	VECTOR GetBack() const;

	// �E�������擾
	VECTOR GetRight() const;

	// ���������擾
	VECTOR GetLeft() const;

	// ��������擾
	VECTOR GetUp() const;

	// ���������擾
	VECTOR GetDown() const;

	// �Ώە������擾
	VECTOR GetDir(const VECTOR& vec) const;

};

