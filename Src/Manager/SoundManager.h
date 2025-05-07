#pragma once
#include "../framework.h"
#include "../Utility/StaticSingleton.h"

class SoundManager : public StaticSingleton<SoundManager>
{
public:

	//�����p���ʍő�l
	static constexpr int VOLUME_MAX = 255;

	//�Đ��̎�ޕ�������Ƃ��Ɏg��
	enum class TYPE 
	{
		NONE,
		BGM,
		SE
	};

	//�T�E���h
	enum class SOUND
	{
		NONE,
		TITLE_BGM,
		SELECT_BGM,
		GAMEBGM1,
		GAMEBGM2,
		CHANGE_SCENE_SE,
		SWITCH_ON_SE,
		SWITCH_OFF_SE,
		TACKLE_SE,
		ITEM_GET_SE,
		DAMAGE_SE,
		COUNT_DOWN_SE,
		COUNT_3,
		COUNT_2,
		COUNT_1,
		COUNT_0,
		GO_SE,
		CLEAR_SE,
		JUMP_SE,
		BLAST_SE,
		ENEMY_DAMAGE_SE,
		SPEED_UP,
		HINDER_SE
	};

	struct SoundData
	{
		int data;		//�����f�[�^�i�[
		TYPE type;		//�����f�[�^�̎��	�����̗v�f�͍폜���邩��
		int playMode;	//�����f�[�^�̍Đ��^�C�v
	};

	//������
	void Init();

	//�T�E���h�̒ǉ�
	void Add(const TYPE type, const SOUND sound, const int data);

	//�����f�[�^
	void Play(const SOUND sound);

	//��~����
	void Stop(const SOUND sound);

	//���ʒ���
	void AdjustVolume(const SOUND sound, const int persent);

	//���
	void Destroy(void);

private:

	//�V���O���g��
	THIS_CLASS_IS_STATIC_SINGLETON(SoundManager);

	//�f�[�^�i�[�p
	std::unordered_map<SOUND, SoundData>sounds_;

	SoundManager();
	~SoundManager() = default;

	bool CheckSoundFile(const SOUND snd);

};

