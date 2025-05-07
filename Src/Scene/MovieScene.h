#pragma once
#include "../framework.h"
#include "SceneBase.h"


class MovieScene : public SceneBase
{
public:

	//���[�r�[�̏��
	enum class MOVIE_STATE
	{
		NONE,
		START,	//�J�E���g�_�E��
		PLAY,	//�v���C
		RESULT,	//����
	};

	//���[�r�[�̏����ʒu
	static constexpr VECTOR DEFAULT_PLAYER_POS = { 0,0,0 };

	// �R���X�g���N�^
	MovieScene(SceneManager& manager);

	// �f�X�g���N�^
	~MovieScene() = default;

	void Load() override;
	void Init() override;
	void Update(InputManager& input) override;
	void Draw() override;
	void Release() override;

	//���ʕ`��
	void CommonDraw() override;

private:

	//����
	int movie_;	//�����ID

	//�X�V�֐�
	void LoadingUpdate(InputManager& ins);	//�ǂݍ��ݒ�����
	void NormalUpdate(InputManager& ins);	//�Q�[��������

	//�`��֐� 
	void LoadingDraw();		//�ǂݍ��ݒ��`��
	void NormalDraw();		//�Q�[�����`��(��{�͂����ɏ����Ă�)

};

