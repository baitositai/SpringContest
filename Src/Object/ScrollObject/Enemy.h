#pragma once
#include "ObjectBase.h"

class AnimationController;

class Enemy : public ObjectBase
{
public:

	//�X�P�[��
	static constexpr VECTOR SCALE = { 0.8f,0.8f ,0.8f };

	//�_���[�W
	static constexpr int DAMAGE = -1;

	//�p���[�����
	static constexpr int POWER_CONSUME = -1;

	//�X�R�A��
	static constexpr int HIT_SCORE = 300;
	static constexpr int DAMAGE_SCORE = -500;

	//�A�j���[�V�������x
	static constexpr float ANIM_SPEED = 40.0f;

	//������ё��x
	static constexpr float SMASH_SPEED = 5.0f;

	//�`�F���W����
	static constexpr float CHANGE_SECOND = 1.5f;


	//�A�j���[�V�������
	enum class ANIM_TYPE
	{
		NONE,
		IDLE,
		RUN,
		DEATH
	};

	Enemy();
	~Enemy();

	void InitModel() override;
	void Load() override;
	void Update()override;
	void UpdateHit(void) override;
	void Draw() override;	
	void OnCollision(Player& player) override;

	//�A�j���[�V�����̏���������
	void InitAnimation(void);

	//�Փ˃A�j���[�V�����֌W�̏�����
	void ResetHitAnim();

private:

	// �A�j���[�V����
	std::unique_ptr<AnimationController> animationController_;

	//�J�E���^
	float cnt_;

	//��������p
	float moveDirX_;
};

