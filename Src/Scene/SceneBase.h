#pragma once
#include "../framework.h"
#include "../Application.h"

class SceneManager;
class InputManager;

//�ŒჍ�[�f�B���O����
constexpr float LOADING_TIME = 1.0f;

//�t�H���g�T�C�Y
constexpr int LOAD_FONT_SIZE = 28;

//���[�f�B���O
constexpr int COMMA_MAX_NUM = 5;			//�unow loading......�v�̃R���}�̐�
constexpr float COMMA_TIME = 0.3f;			//�unow loading......�v�̃R���}���𑝂₷����
constexpr int LOADING_STRING_POS_X = Application::SCREEN_SIZE_X - 200;	//�unow loading......�v�̍��WX
constexpr int LOADING_STRING_POS_Y = Application::SCREEN_SIZE_Y - LOAD_FONT_SIZE - 15;	//�unow loading......�v�̍��WY

class SceneBase
{

public:

	//�V�[���}�l�[�W���[
	SceneManager& sceneManager_;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scene"></param>�V�[���Ǘ��N���X
	SceneBase(SceneManager& scene);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~SceneBase() = 0;

	/// <summary>
	/// �ǂ݂���
	/// </summary>
	virtual void Load() = 0;

	/// <summary>
	/// ������
	/// </summary>
	virtual void Init() = 0;

	/// <summary>
	/// �X�V
	/// </summary>
	/// <param name="input"></param>���͊Ǘ��N���X
	virtual void Update(InputManager& input) = 0;

	/// <summary>
	/// �`��
	/// </summary>
	virtual void Draw() = 0;

	/// <summary>
	/// ��ʋ��ʕ`��
	/// </summary>
	virtual void CommonDraw() = 0;

	/// <summary>
	/// ���
	/// </summary>
	virtual void Release() = 0;

protected:

	//���[�f�B���O���`��t�H���g
	int loadFont_;

	//���[�f�B���O�o�ߎ���
	float loadingTime_;

	//�X�V���Ǘ�
	std::function<void(InputManager&)> updateFunc_;

	//�`�惒�Ǘ�
	std::function<void(void)> drawFunc_;
	
	//�unow loading......�v�̕`��
	void DrawNowLoading(void);

};
