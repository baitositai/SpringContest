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


	HinderObject();
	~HinderObject() = default;

	void Load();
	void Init();
	void Update();
	void Draw();

	//�I�u�W�F�N�g��ǉ�
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

	//�I�����c
	std::vector<Object> omus_;
	
	//���ˏ���
	void Reflect(Vector2& vec, float nx, float ny);

};

