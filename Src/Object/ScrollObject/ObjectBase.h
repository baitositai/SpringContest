#pragma once
#include "../../framework.h"
#include "../Common/Transform.h"
#include "../Character/Player.h"

class ResourceManager;
class SceneManager;

class ObjectBase
{

public:

	//�ʏ피�a
	static constexpr float DEFAULT_RADIUS = 20.0f;

	//�����G�t�F�N�g���΍��W
	static constexpr VECTOR EXPLOSION_POS = { 0.0f, 0.0f, 0.0f };

	enum class STATE
	{
		NONE,
		SCROLL,
		HIT,
	};

	// �R���X�g���N�^
	ObjectBase();

	// �f�X�g���N�^
	~ObjectBase() = default;

	virtual void Load();
	virtual void Init();
	virtual void Update();
	virtual void Draw();	
	void Release();
	
	/// <summary>
	/// ��ԕύX
	/// </summary>
	/// <param name="state"></param>���̏��
	void ChangeState(const STATE state);

	/// <summary>
	/// �Փ˔����̏���
	/// </summary>
	/// <param name="player"></param>�v���C���[
	virtual void OnCollision(Player& player) = 0;

	//�g�����X�t�H�[����Ԃ�
	inline const Transform& GetTransform() const { return transform_; }

	//��Ԃ�Ԃ�
	inline const STATE& GetState()const { return state_; }

	//���a��Ԃ�
	inline const float& GetRadius()const { return radius_; }

protected:
	
	//���
	STATE state_;

	//�f�o�b�O�p�J���[
	int color_;

	//���a
	float radius_;

	// ���f������̊�{���
	Transform transform_;	
	
	// �V���O���g���Q��
	ResourceManager& resMng_;
	SceneManager& scnMng_;

private:

	// ��ԊǗ�(��ԑJ�ڎ���������)
	std::map<STATE, std::function<void()>> stateChanges_;

	// ��ԊǗ�(�X�V�X�e�b�v)
	std::function<void()> stateUpdate_;

	// ��ԑJ��
	void ChangeStateNone();
	void ChangeStateScroll();
	void ChangeStateHit();

	// �X�V�X�e�b�v
	void UpdateNone();
	void UpdateScroll();
	virtual void UpdateHit();

	//�ʒu�̃����_������
	void DecideRandPos();

	//���f���̏���������
	virtual void InitModel() = 0;
};