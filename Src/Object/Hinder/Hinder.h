#pragma once
#include "../../framework.h"
#include "../../Application.h"

class Hinder
{
public:
	
	//�摜�T�C�Y
	static constexpr int HINDER_SIZE_X = 180;
	static constexpr int HINDER_SIZE_Y = 68;

	//�`��ʒu
	static constexpr int HINDER_GAGE_POS_X = Application::SCREEN_HALF_X - HINDER_SIZE_X / 2;
	static constexpr int HINDER_GAGE_POS_Y = 200;

	static constexpr int HINDER_POS_X = HINDER_GAGE_POS_X - HINDER_SIZE_X / 2;
	static constexpr int HINDER_POS_Y = HINDER_GAGE_POS_Y - HINDER_SIZE_Y / 2 + 20;

	//�X�R�A�l���ڈ���
	static constexpr int ACHIEVEMENT_SCORE = 5000;


	Hinder();
	~Hinder() = default;

	void Load();
	void Init();
	void Update();
	void Draw();

	/// <summary>
	/// �W�Q���J�n�����Ԃ�
	/// </summary>
	/// <returns></returns>�W�Q�J�n����
	inline bool IsStart() const { return isStart_; }

	/// <summary>
	/// �W�Q�J�n�ݒ�
	/// </summary>
	/// <param name="isStart"></param>�W�Q�J�n
	inline void SetStart(const bool isStart) { isStart_ = isStart; }

private:

	//�摜�ǂݍ���
	int imgHinder_;
	int imgHinderGage_;
	int imgItem_;
	int imgItemGage_; 	
	
	//���ʔ�������
	bool isStart_;
};

