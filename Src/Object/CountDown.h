#pragma once

class CountDown
{
public:

	//�Q�[���J�n�J�E���g�_�E��
	static constexpr float COUNTDOWN = 4.0f;

	//�J�E���g�_�E�������l
	static constexpr int SE_COUNT = 3;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CountDown();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CountDown() = default;

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
	/// �I�������画���Ԃ�
	/// </summary>
	/// <returns></returns>
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

