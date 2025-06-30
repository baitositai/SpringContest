#pragma once
#include "../framework.h"
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Common/Vector2.h"
#include "UI/DrawSpeedUp.h"

class DrawSpeedUp;

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
	static constexpr int TIMER_POS_Y = 64;		//�ʏ�
	static constexpr int VS_TIMER_POS_Y = 350;	//VS

	//�ǉ��X�R�A
	static constexpr int ADD_SCORE = 100;

	//�ꕪ������̕b��
	static constexpr int SECONDS_PER_MINUTE = 60;

	static constexpr int TIME_CNTS_POS_X[TIME_DIGITS] = {
		Application::SCREEN_HALF_X - 64,
		Application::SCREEN_HALF_X - 32,
		Application::SCREEN_HALF_X + 32,
		Application::SCREEN_HALF_X + 64};

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TimeCount();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TimeCount() = default;

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
	/// ���
	/// </summary>
	void Release();

	/// <summary>
	/// ���
	/// </summary>
	void CommonDraw();

private:

	//�摜
	int imgTimerGage_;
	int* imgNums_;

	//�^�C�}�[Y���W
	int posY_;

	//���Ԍo�ߗp�X�e�b�v
	float step_;
	int preStep_;
	float scrCnt_;

	//���x�㏸UI
	std::unique_ptr<DrawSpeedUp> speedUi_;

};

