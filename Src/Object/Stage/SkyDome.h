#pragma once
#include "../../framework.h"
#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Utility/Utility.h"
#include "../Common/Transform.h"

class SkyDome
{
public:

	static constexpr float ROT_SPEED = 0.01f;

	// ���
	enum class STATE
	{
		NONE,
		STAY,
		FOLLOW
	};

	//�X�P�[���T�C�Y
	static constexpr VECTOR SCALE = { 100.0f, 100.0f, 100.0f };

	SkyDome();
	~SkyDome() = default;

	void Load();
	void Init();
	void Update();
	void Draw();

private:

	//���f���ǂݍ���
	void SetModel();

	//�g�����X�t�H�[��
	Transform transform_;

	// ���
	STATE state_;

	// ��ԊǗ�(��ԑJ�ڎ���������)
	std::map<STATE, std::function<void()>> stateChanges_;

	// ��ԊǗ�(�X�V�X�e�b�v)
	std::function<void()> stateUpdate_;

	// ��ԑJ��
	void ChangeState(STATE state);
	void ChangeStateNone();
	void ChangeStateStay();
	void ChangeStateFollow();

	// �X�V�X�e�b�v
	void UpdateNone();
	void UpdateStay();
	void UpdateFollow();

};