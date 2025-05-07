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

	TitlePlayer();
	~TitlePlayer() = default;

	void Load();
	void Init();
	void Update();
	void Draw();

private:

	//�g�����X�t�H�[��
	Transform trans_;
	
	//�A�j���[�V�����R���g���[���[
	std::unique_ptr< AnimationController> animController_;
	
	//�A�j���[�V�����ݒ�
	void InitAnim();
};
