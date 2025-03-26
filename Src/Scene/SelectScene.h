#pragma once
#include "../framework.h"
#include "SceneBase.h"


constexpr int FONT_SIZE_X = 400;
constexpr int FONT_SIZE_Y = 400;

class SelectScene : public SceneBase
{
public:


	// �R���X�g���N�^
	SelectScene(SceneManager& manager);

	// �f�X�g���N�^
	~SelectScene(void) = default;

	void Load(void) override;
	void Init(void) override;
	void Update(InputManager& input) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// �X�V�֐�
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	//�`��֐� 
	void LoadingDraw(void);		//�ǂݍ��ݒ��`��
	void NormalDraw(void);		//�Q�[�����`��

	int image_;

};

