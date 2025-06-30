#pragma once
#include "../../framework.h"
#include "ObjectBase.h"

class ObjectBase;

class ObjectManager
{
public:

	//�X�N���[���̊Ԋu�b��
	static constexpr float INTERVEL_SECOND_MIN = 1.0f;
	static constexpr float INTERVEL_SECOND_MAX = 2.0f;

	//�e��I�u�W�F�N�g������
	static constexpr int ENEMY_CREATE_CNT = 4;
	static constexpr int GIMIC_CREATE_CNT = 2;
	static constexpr int LIFE_CREATE_CNT = 1;
	static constexpr int POW_CREATE_CNT = 1;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ObjectManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ObjectManager() = default;

	/// <summary>
	/// �ǂ݂���
	/// </summary>
	void Load();

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���
	/// </summary>
	void Release();

	/// <summary>
	/// �I�u�W�F�N�g�z���Ԃ�
	/// </summary>
	/// <returns></returns>�I�u�W�F�N�g�z��
	inline const std::vector<std::unique_ptr<ObjectBase>>& GetObjects() const { return objs_; }

private:

	//�X�N���[���J�n�p�X�e�b�v
	float step_;

	//�I�u�W�F�N�g
	std::vector<std::unique_ptr<ObjectBase>> objs_;

	//�X�N���[���̊J�n
	void ScrollStart();

	//����̃X�N���[���J�n�b��
	float NextStartSecond();

};

