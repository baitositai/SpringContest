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

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="manager"></param>�V�[���Ǘ��N���X
	MovieScene(SceneManager& manager);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MovieScene() = default;

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

	//����
	int movie_;	//�����ID

	//�X�V�֐�
	void LoadingUpdate(InputManager& ins);	//�ǂݍ��ݒ�����
	void NormalUpdate(InputManager& ins);	//�Q�[��������

	//�`��֐� 
	void LoadingDraw();		//�ǂݍ��ݒ��`��
	void NormalDraw();		//�Q�[�����`��(��{�͂����ɏ����Ă�)

};

