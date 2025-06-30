#pragma once
#include "../../framework.h"
#include "../Common/Transform.h"
#include "../Common/AnimationController.h"

class AnimationController;

class TitlePlayer
{
public:

	//�A�j���[�V�������
	enum class ANIM_TYPE
	{
		NONE,
		IDLE,
		RUN,
	};
	//�ʒu
	static constexpr VECTOR POS = { 500,100,-100 };

	//�X�P�[��
	static constexpr VECTOR SCALE = { 1.f,1.f,1.f };

	//�A�j���[�V�������x
	static constexpr float IDLE_SPEED = 10.0f;
	static constexpr float RUN_SPEED = 40.0f;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TitlePlayer();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TitlePlayer() = default;

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

private:

	//�g�����X�t�H�[��
	Transform trans_;
	
	//�A�j���[�V�����R���g���[���[
	std::unique_ptr< AnimationController> animController_;
	
	//�A�j���[�V�����ݒ�
	void InitAnim();
};
