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

	// �R���X�g���N�^
	SelectScene(SceneManager& manager);

	// �f�X�g���N�^
	~SelectScene() = default;

	void Load() override;
	void Init() override;
	void Update(InputManager& input) override;
	void Draw() override;
	void CommonDraw() override;
	void Release() override;

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

