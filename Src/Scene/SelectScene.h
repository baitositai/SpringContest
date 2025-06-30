#pragma once
#include "../framework.h"
#include "SceneBase.h"

class SelectScene : public SceneBase
{
public:

	//����
	static constexpr int VOLUME = 70;

	//�`��ʒu
	static constexpr int ON_POS_X = 350;
	static constexpr int ON_POS_Y = 520;
	static constexpr int OFF_POS_X = 500;
	static constexpr int OFF_POS_Y = 520;
	static constexpr int SPEECH_POS_X = 875;
	static constexpr int SPEECH_POS_Y = 520;

	// �㉺�h��̐U���i�傫���j
	static constexpr float AMPLITUDE = 10.0f;

	// �㉺�h��̎����i�h��鑬���j
	static constexpr float PERIOD = 0.05f;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="manager"></param>�V�[���Ǘ��N���X
	SelectScene(SceneManager& manager);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <param name=""></param>
	~SelectScene(void) = default;

	/// <summary>
	/// �ǂݍ���
	/// </summary>
	void Load() override;

	/// <summary>
	/// ������
	/// </summary>
	void Init() override;

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="ins"></param>���͊Ǘ��N���X
	void Update(InputManager& ins) override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

	/// <summary>
	/// ���
	/// </summary>
	void Release() override;

	/// <summary>
	/// ���ʕ`��
	/// </summary>
	void CommonDraw() override;

private:

	// �X�V�֐�
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	//�`��֐� 
	void LoadingDraw();		//�ǂݍ��ݒ��`��
	void NormalDraw();		//�Q�[�����`��

	//�v���C���[�̎����U���̗L���𒲂ׂ�
	void CheckPlayerTackle();

	//�摜
	int image_;
	int imgSelect_;
	int imgSpeech_;

	//�X�V�p�X�e�b�v
	float step_;

};

