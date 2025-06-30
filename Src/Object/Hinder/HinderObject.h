#pragma once
#include "../../Common/Vector2.h"
#include "../../framework.h"
#include "../../Application.h"

class HinderObject
{
public:

	//�摜�T�C�Y
	static constexpr int IMG_SIZE = 96;

	//���x
	static constexpr float SPEED = 4.0f;

	//�����p�x
	static constexpr float ANGLE = 45.0f;

	//RAND�͈�
	static constexpr int RAND_RANGE = 359;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	HinderObject();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~HinderObject() = default;

	/// <summary>
	/// �ǂݍ���
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
	/// �I�u�W�F�N�g��ǉ�
	/// </summary>
	/// <param name="num"></param>�ǉ��l
	void AddObject(const int num);

private:

	struct Object
	{
		int type_;		//�摜���
		Vector2 pos_;	//�ʒu
		Vector2 vec_;	//�ړ��x�N�g��
	};

	//�摜
	int* imgs_;

	//�I�u�W�F�N�g�z��
	std::vector<Object> objs_;
	
	//���ˏ���
	void Reflect(Vector2& vec, float nx, float ny);

};

