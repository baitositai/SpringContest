#pragma once
#include "../../framework.h"
#include "../Common/Transform.h"
#include "../Common/AnimationController.h"

class AnimationController;

class Player
{
public:

	//�ړ����x
	static constexpr float SPEED_MOVE = 5.0f;

	// �W�����v�֌W
	static constexpr float JUMP_HEIGHT = 100.0f;	//����
	static constexpr float JUMP_SPEED = 20.0f;		//�X�s�[�h
	static constexpr float RAD_PER_FRAME = 2 * DX_PI_F / 40; //1�t���[��������̃��W�A��

	// �W�����v��t����
	static constexpr float TIME_JUMP_IN = 0.5f;

	//�A�j���[�V�������x
	static constexpr float ANIM_SPEED = 40.0f;

	//�����̗�
	static constexpr int DEFAULT_LIFE = 3;

	//�����p���[
	static constexpr int DEFAULT_POWER = 4;

	//���a
	static constexpr float RADIUS = 30.0f;

	//�^�b�N������
	static constexpr float TACKLE_TIME = 1.5f;

	//���
	enum class STATE
	{
		NONE,
		ALIVE,
		DEATH,
	};

	//�A�j���[�V�������
	enum class ANIM_TYPE
	{
		NONE,
		IDLE,
		RUN,
		JUMP,
		TACKLE,
		DANCE,
		DEATH
	};

	Player();
	~Player() = default;

	void Load();
	void Init();
	void Update();
	void Draw();

	//�̗͂�������
	void AddLife(const int &life);

	//�͂�������
	void AddPower(const int& pow);

	//�^�b�N���ݒ�
	void SetIsTackle(const bool& isTackle);

	//�͂�Ԃ�
	inline const int& GetPower() const { return pow_; }

	//�^�b�N�������Ԃ�
	inline const bool& IsTackle() const { return isTackle_; }
	
	//�Փ˔���p���a��Ԃ�
	inline const float& GetRadius() const { return radius_; }

	//��Ԃ�Ԃ�
	inline const STATE& GetState() const { return state_; }

	//�g�����X�t�H�[����Ԃ�
	inline const Transform& GetTransform(void) const { return trans_; }

	//�f�o�b�O�`��
	void DebagDraw();

private:

	//���
	STATE state_;

	//�ړ����x
	float moveSpeed_;

	// �W�����v����
	bool isJump_;

	// �W�����v�̓��͎�t����
	float stepJump_;

	//�^�b�N���p���[
	int pow_;

	//�̗�
	int life_;

	//�Փ˔���p���a
	float radius_;

	//�^�b�N������
	bool isTackle_;

	//�^�b�N������
	float tackleTime_;

	//�g�����X�t�H�[��
	Transform trans_;

	// ��ԊǗ�(��ԑJ�ڎ���������)
	std::map<STATE, std::function<void(void)>> stateChanges_;

	// ��ԊǗ�(�X�V�X�e�b�v)
	std::function<void(void)> stateUpdate_;

	// �A�j���[�V����
	std::unique_ptr<AnimationController> animationController_;

	// ��ԑJ��
	void ChangeState(STATE state);
	void ChangeStateNone(void);
	void ChangeStateAlive(void);
	void ChangeStateDeath(void);

	// �X�V�X�e�b�v
	void UpdateNone(void);
	void UpdateAlive(void);
	void UpdateDeath(void);

	//�e�평���ݒ�
	void InitModel(void);
	void InitAnimation(void);

	//���쏈��
	void Process(void);

	//�W�����v
	void Jump(void);

	//�^�b�N��
	void Tackle();
};

