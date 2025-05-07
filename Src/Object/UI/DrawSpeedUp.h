#pragma once
#include "../../framework.h"
#include "../../Application.h"
#include "../../Common/Vector2.h"

class DrawSpeedUp
{
public:

	//�`��ʒu(�}���\��)
	static constexpr int MARASON_POS_X = Application::SCREEN_HALF_X;
	static constexpr int VS_POS_X = Application::SCREEN_HALF_X / 2;
	static constexpr int POS_Y = 200;

	//�ێ�����
	static constexpr float MAINTAIN_TIME = 1.5f;

	//�g�呬�x
	static constexpr float RATE_SPEED = 0.05f;

	enum class STATE
	{
		NONE,		//�Ȃ�
		EXPAND,		//�g��
		MAINTAIN,	//�ێ�
		TRANS		//������
	};

	DrawSpeedUp();
	~DrawSpeedUp() = default;

	void Load();
	void Init();
	void Update();
	void Draw();
	void Release();

	//��ԕύX
	void ChangeState(const STATE& state);

private:

	//���
	STATE state_;

	//�摜
	int img_;

	//�A���t�@�n
	int alpha_;

	//�g�嗦
	float rate_;

	//�X�e�b�v
	float step_;

	//�`��ʒu
	Vector2 pos_;

	//��ԕʍX�V
	std::function<void()> updateFunc_;

	//��ԕʍX�V����
	void UpdateStateNone();
	void UpdateStateExpand();
	void UpdateStateMaintain();
	void UpdateStateTrans();

};

