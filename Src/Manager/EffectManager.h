#pragma once
#include "../framework.h"
#include "../Common/Quaternion.h"
#include "../Utility/StaticSingleton.h"
#include "SoundManager.h"


class EffectManager : public StaticSingleton<EffectManager>
{
public:

	enum class EFFECT
	{
		NONE,
	};

	//������
	void Init();

	//�ǉ�
	void Add(const EFFECT& efc, int data);

	//�Đ�
	void Play(const EFFECT& efc,
		const VECTOR& pos, 
		const Quaternion& qua,
		const float& size,
		const SoundManager::SOUND sound);

	//��~
	void Stop(const EFFECT& efc);

	//�G�t�F�N�g�̊e�p�����[�^����
	void SyncEffect(const EFFECT& efc, const VECTOR& pos, const Quaternion& qua, const float& size);

	//�G�t�F�N�g�̍Đ��m�F
	bool IsPlayEffect(const EFFECT& efc);

	//���
	void Destroy();

private:

	//�V���O���g���̐���
	THIS_CLASS_IS_STATIC_SINGLETON(EffectManager);

	//�G�t�F�N�g�f�[�^�i�[�p
	std::unordered_map<EFFECT, int> effectRes_;		//�����f�[�^
	std::unordered_map<EFFECT, int> effectPlay_;	//�Đ��f�[�^
	std::unordered_map<EFFECT, int> effectMax_;		//�Đ��f�[�^�̍ő及����

	EffectManager();
	~EffectManager() = default;
};