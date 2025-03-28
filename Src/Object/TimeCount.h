#pragma once
#include "../framework.h"
#include "../Application.h"
#include "../Manager/SceneManager.h"

class TimeCount
{
public:

	//���Ԍ���
	static constexpr int TIME_DIGITS = 4;

	//���ԕ`��g�嗦
	static constexpr float TIME_RATE = 0.35f;

	//�摜�`��ʒu
	static constexpr int TIMER_GAGE_POS_X = Application::SCREEN_HALF_X;

	//Y���W
	static constexpr int TIMER_POS_Y = 64;	//�ʏ�
	static constexpr int VS_TIMER_POS_Y = 156;	//VS

	static constexpr int TIME_CNTS_POS_X[TIME_DIGITS] = {
		Application::SCREEN_HALF_X - 64,
		Application::SCREEN_HALF_X - 32,
		Application::SCREEN_HALF_X + 32,
		Application::SCREEN_HALF_X + 64};

	TimeCount();
	~TimeCount() = default;

	void Load();
	void Init();
	void Update();
	void Draw();
	void Release();

private:

	//�摜
	int imgTimerGage_;
	int* imgNums_;

	//�^�C�}�[Y���W
	int posY_;

	//���Ԍo�ߗp�X�e�b�v
	float step_;
};

