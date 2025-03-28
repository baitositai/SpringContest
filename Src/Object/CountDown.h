#pragma once

class CountDown
{
public:

	//�Q�[���J�n�J�E���g�_�E��
	static constexpr float COUNTDOWN = 4.0f;
	static constexpr int SE_COUNT = 3;

	CountDown();
	~CountDown();

	void Load();
	void Init();
	void Update();
	void Draw();
	void Release();

	//�I�������画���Ԃ�
	inline const bool IsStart() const { return isStart_; }

private:

	//�摜
	int *imgNums_;

	//�J�E���g
	float cnt_;

	//�I������
	bool isStart_;

	//�J�E���g
	int seCnt_;

	//���ʉ��̍Đ�����
	void PlaySE();
	
};

