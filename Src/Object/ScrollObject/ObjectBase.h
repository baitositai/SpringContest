#pragma once
#include "../../framework.h"
#include "../Common/Transform.h"

class ResourceManager;
class SceneManager;

class ObjectBase
{

public:

	//�ʏ피�a
	static constexpr float DEFAULT_RADIUS = 20.0f;

	enum class STATE
	{
		NONE,
		SCROLL,
		HIT,
	};

	// �R���X�g���N�^
	ObjectBase(void);

	// �f�X�g���N�^
	~ObjectBase(void);

	virtual void Load(void);
	virtual void Init(void);
	virtual void Update(void);
	virtual void Draw(void);	
	
	//��ԕύX
	void ChangeState(STATE state);

	//�Փ˔����̏���
	virtual void OnCollision(Player& player) = 0;

	//�g�����X�t�H�[����Ԃ�
	inline const Transform& GetTransform(void) const { return transform_; }

	//��Ԃ�Ԃ�
	inline const STATE& GetState()const { return state_; }

	//���a��Ԃ�
	inline const float& GetRadius()const { return radius_; }

protected:

	//�f�o�b�O�p�J���[
	int color_;

	//���a
	float radius_;

public:

	//���
	STATE state_;

	// ��ԊǗ�(��ԑJ�ڎ���������)
	std::map<STATE, std::function<void(void)>> stateChanges_;

	// ��ԊǗ�(�X�V�X�e�b�v)
	std::function<void(void)> stateUpdate_;

	// �V���O���g���Q��
	ResourceManager& resMng_;
	SceneManager& scnMng_;

	// ���f������̊�{���
	Transform transform_;

	// ��ԑJ��
	void ChangeStateNone(void);
	void ChangeStateScroll(void);
	void ChangeStateHit(void);

	// �X�V�X�e�b�v
	void UpdateNone(void);
	void UpdateScroll(void);
	void UpdateHit(void);

	//�ʒu�̃����_������
	void DecideRandPos();
};