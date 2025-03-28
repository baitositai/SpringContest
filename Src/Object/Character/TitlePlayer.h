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
		DANCE,
	};

	//�X�P�[��
	static constexpr VECTOR SCALE = { 1.f,1.f,1.f };

	TitlePlayer();
	~TitlePlayer();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	//�g�����X�t�H�[��
	Transform trans_;
	
	//�A�j���[�V�����R���g���[���[
	std::unique_ptr< AnimationController> animController_;
	
	//�A�j���[�V�����ݒ�
	void InitAnim();
};
