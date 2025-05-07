#pragma once
#include "../framework.h"
#include "SoundManager.h"


class Effect2DManager
{
public:

	//�G�t�F�N�g�̃A�j���[�V�������x
	static constexpr float DEFAULT_ANIM_SPEED = 3.0f;

	//���S�ɍ��킹��悤
	static constexpr float CENTER = 0.5f;

	enum class EFFECT
	{
		NONE,
		TACKLE,
		DAMAGE,
		GET,
		BLAST,
	};	
	
	Effect2DManager();
	~Effect2DManager() = default;

	//�X�V����
	void Update();

	/// <summary>
	/// �ǉ�
	/// </summary>
	/// <param name="efc"></param>���
	/// <param name="image"></param>���\�[�X
	/// <param name="animMax"></param>�A�j���[�V��������
	/// <param name="animSpeed"></param>�A�j���[�V�������x
	void Add(
		const EFFECT& efc, 
		int* image,
		const int& animMax,
		const float& animSpeed = DEFAULT_ANIM_SPEED);

	/// <summary>
	/// �Đ�
	/// </summary>
	/// <param name="efc"></param>���
	/// <param name="pos"></param>���W
	/// <param name="rate"></param>�g�嗦
	/// <param name="angle"></param>�p�x
	/// <param name="sound"></param>�T�E���h
	void Play(
		const EFFECT& efc,
		const VECTOR& pos,
		const float& rate = 1.0f,
		const float& angle = 0.0f,
		const SoundManager::SOUND& sound = SoundManager::SOUND::NONE);

	/// <summary>
	/// �G�t�F�N�g�̓���
	/// </summary>
	/// <param name="efc"></param>���
	/// <param name="pos"></param>���W
	/// <param name="rate"></param>�g�嗦
	/// <param name="angle"></param>�p�x
	void Sync(
		const EFFECT& efc, 
		const VECTOR& pos,
		const float& rate = 1.0f,
		const float& angle =0.0f);	
	
	/// <summary>
	/// ��~
	/// </summary>
	/// <param name="efc"></param>�G�t�F�N�g�^�C�v
	void Stop(const EFFECT& efc);

	//���
	void Destroy();

	/// <summary>
	/// �G�t�F�N�g�̃X�N���[���`��
	/// </summary>
	/// <param name="efc"></param>���
	void DrawScreenEffect(const EFFECT& efc);

	/// <summary>
	/// �r���{�[�h�`��
	/// </summary>
	/// <param name="efc"></param>���
	void DrawBillboard(const EFFECT& efc);

	/// <summary>
	/// �G�t�F�N�g�̍Đ��m�F
	/// </summary>
	/// <param name="efc"></param>���
	/// <returns></returns>�Đ����Ȃ�true,�Ⴄ�ꍇfalse
	inline const bool IsPlayEffect(const EFFECT& efc) { return effects_[efc].isPlay_; }

private:

	struct Efc
	{
		int* image_;	//�摜	
		int animMax_;	//�A�j���[�V��������
		int animNum_;	//���݂̃A�j���[�V�����ԍ�
		float animSpeed_;	//�A�j���[�V�������x
		VECTOR pos_;	//���W�ʒu
		float rate_;	//�g�嗦
		float angle_;	//�p�x		
		float step_;	//�X�V�p�X�e�b�v
		bool isPlay_;	//�J�n
	};

	//�G�t�F�N�g�f�[�^�i�[�p
	std::unordered_map<EFFECT, Efc> effects_;	//�G�t�F�N�g�f�[�^

};

