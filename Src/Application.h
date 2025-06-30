#pragma once
#include "framework.h"

class FpsControl;

class Application
{

public:

	//��16:9�ɂ���ꍇ 1280�~720
	//��4:3�ɂ���ꍇ  1024�~768
	// �X�N���[���T�C�Y
	static constexpr int SCREEN_SIZE_X = static_cast<int>(1024 * 1);
	static constexpr int SCREEN_SIZE_Y = static_cast<int>(768 * 1);
	
	// �X�N���[���T�C�Y�n�[�t
	static constexpr int SCREEN_HALF_X = SCREEN_SIZE_X / 2;
	static constexpr int SCREEN_HALF_Y = SCREEN_SIZE_Y / 2;

	//�J���[�r�b�g�[�x
	static constexpr int COLOR_BIT_DEPTH = 32;

	// �f�[�^�p�X�֘A
	//-------------------------------------------
	static const std::string PATH_IMAGE;
	static const std::string PATH_MODEL;
	static const std::string PATH_EFFECT;
	static const std::string PATH_FONT;
	static const std::string PATH_TEXT;
	static const std::string PATH_SOUND;
	static const std::string PATH_MOVIE;
	//-------------------------------------------

	/// <summary>
	///  �����I�ɃC���X�e���X�𐶐�����
	/// </summary>
	static void CreateInstance();

	/// <summary>
	/// �ÓI�C���X�^���X�̎擾
	/// </summary>
	/// <returns></returns>�A�v���P�[�V����
	static Application& GetInstance();

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// �Q�[�����[�v
	/// </summary>
	void Run();

	/// <summary>
	/// ���\�[�X�̔j��
	/// </summary>
	void Destroy();

	/// <summary>
	/// �����������̔���
	/// </summary>
	/// <returns></returns>���茋��
	bool IsInitFail() const;

	/// <summary>
	/// ��������̔���
	/// </summary>
	/// <returns></returns>���茋��
	bool IsReleaseFail() const;

private:

	// �ÓI�C���X�^���X
	static Application* instance_;

	// ���������s
	bool isInitFail_;

	// ������s
	bool isReleaseFail_;

	//FPS
	std::unique_ptr<FpsControl> fps_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	Application();

	// �R�s�[�R���X�g���N�^�����l
	Application(const Application&);

	// �f�X�g���N�^�����l
	~Application() = default;

};