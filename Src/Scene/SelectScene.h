#pragma once
#include "../framework.h"
#include "SceneBase.h"

class SelectScene : public SceneBase
{
public:


	// �R���X�g���N�^
	SelectScene(SceneManager& manager);

	// �f�X�g���N�^
	~SelectScene(void);

	void Load(void) override;
	void Init(void) override;
	void Update(InputManager& input) override;
	void Draw(void) override;
	void CommonDraw(void) override;
	void Release(void) override;

private:

	// �X�V�֐�
	void LoadingUpdate(InputManager& ins);
	void NormalUpdate(InputManager& ins);

	//�`��֐� 
	void LoadingDraw(void);		//�ǂݍ��ݒ��`��
	void NormalDraw(void);		//�Q�[�����`��

	//�v���C���[�̎����U���̗L���𒲂ׂ�
	void CheckPlayerTackle();

	//�摜
	int image_;

};

