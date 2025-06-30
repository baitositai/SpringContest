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

	//�_���[�W����
	static constexpr float DAMAGE_TIME = 2.0f;

	//�^�b�N���G�t�F�N�g�̑��΍��W
	static constexpr VECTOR TACKLE_EFK_LOCAL_POS = { 0,100,100 };

	//�^�b�N���̃G�t�F�N�g�T�C�Y
	static constexpr float TACKLE_FEK_SIZE = 10.0f;

	//����A�j���[�V��������
	static constexpr int GET_ANIM_MAX = 35;

	//�G�t�F�N�g���x
	static constexpr float EFK_SPEED = 1.0f;

	//�G�t�F�N�g�̊g�嗦
	static constexpr float EFK_RATE = 2.0f;

	//���
	enum class STATE
	{
		NONE,
		ALIVE,
		DEATH,
		WIN,
	};

	//�v���C���[�̐������
	enum class ALIVE_STATE
	{
		NONE,
		RUN,
		TACKLE,
		DAMAGE
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

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player() = default;

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

	/// <summary>
	/// ���
	/// </summary>
	void Release();

	/// <summary>
	/// �̗͂�������
	/// </summary>
	/// <param name="life"></param>�ǉ����C�t
	void AddLife(const int life);

	/// <summary>
	/// �p���[��������
	/// </summary>
	/// <param name="pow"></param>�ǉ��p���[
	void AddPower(const int pow);	
	
	/// <summary>
	/// ��Ԃ̕ύX
	/// </summary>
	/// <param name="state"></param>�ύX��̏��
	void ChangeState(const STATE state);

	/// <summary>
	/// �������̏�Ԃ̕ύX
	/// </summary>
	/// <param name="state"></param>�ύX��̏��
	void ChangeAliveState(const ALIVE_STATE state);

	/// <summary>
	/// �L�[�̐ݒ�
	/// </summary>
	/// <param name="right"></param>�E�ړ�
	/// <param name="left"></param>���ړ�
	/// <param name="jump"></param>�W�����v
	/// <param name="tackle"></param>�U��
	void SetKey(
		const int right, 
		const int left, 
		const int jump, 
		const int tackle);

	/// <summary>
	/// ���C�t��Ԃ�
	/// </summary>
	/// <returns></returns>���C�t
	inline const int& GetLife() const { return life_; }

	/// <summary>
	/// �p���[��Ԃ�
	/// </summary>
	/// <returns></returns>�p���[
	inline const int& GetPower() const { return pow_; }
	
	/// <summary>
	/// �Փ˔���p���a��Ԃ�
	/// </summary>
	/// <returns></returns>���a
	inline const float& GetRadius() const { return radius_; }

	/// <summary>
	/// �^�b�N�����Ԃ�Ԃ�
	/// </summary>
	/// <returns></returns>�^�b�N������
	inline const float& GetTackleTime() const { return tackleTime_; }

	/// <summary>
	/// ��Ԃ�Ԃ�
	/// </summary>
	/// <returns></returns>���
	inline const STATE& GetState() const { return state_; }

	/// <summary>
	/// ������Ԃ�Ԃ�
	/// </summary>
	/// <returns></returns>�������
	inline const ALIVE_STATE& GetAliveState() const { return aliveState_; }

	/// <summary>
	/// �g�����X�t�H�[����Ԃ�
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>�g�����X�t�H�[��
	inline const Transform& GetTransform(void) const { return trans_; }

	/// <summary>
	/// �f�o�b�O�`��
	/// </summary>
	void DebagDraw(); 

private:

	//�G�t�F�N�g�p�摜
	int* imgTackleEfk_;
	int* imgHitEfk_;

	//����L�[
	struct Key
	{
		int right_;
		int left_;
		int jump_;
		int tackle_;
	};

	//���
	STATE state_;

	//�������
	ALIVE_STATE aliveState_;

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
	float tackleTime_;

	//�_���[�W����
	float damageTime_;

	//�g�����X�t�H�[��
	Transform trans_;

	//�L�[
	Key key_;

	// ��ԊǗ�(��ԑJ�ڎ���������)
	std::map<STATE, std::function<void()>> stateChanges_;
	std::map<ALIVE_STATE, std::function<void()>> aliveStateChanges_;

	// ��ԊǗ�(�X�V�X�e�b�v)
	std::function<void()> stateUpdate_;
	std::function<void()> aliveStateUpdate_;

	// �A�j���[�V����
	std::unique_ptr<AnimationController> animationController_;

	// ��ԑJ��
	void ChangeStateNone();
	void ChangeStateAlive();
	void ChangeStateDeath();
	void ChangeStateWin();

	void ChangeAliveStateRun();
	void ChangeAliveStateTackle();
	void ChangeAliveStateDamage();

	// �X�V�X�e�b�v
	void UpdateNone();
	void UpdateAlive();
	void UpdateDeath();
	void UpdateWin();

	//�e�평���ݒ�
	void InitModel();
	void InitAnimation();

	//���쏈��
	void Process();

	//�W�����v
	void Jump();

	//������ԕʂ̍X�V����
	void Run();
	void Tackle();
	void Damage();
};

