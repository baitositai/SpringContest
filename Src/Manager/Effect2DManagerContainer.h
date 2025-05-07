#pragma once
#include "../framework.h"
#include "../Common/Vector2.h"
#include "../Utility/StaticSingleton.h"
#include "SoundManager.h"

class Effect2DManager;

class Effect2DManagerContainer : public StaticSingleton<Effect2DManagerContainer>
{
public:

	//����������
	void Init();

	//�X�V����(�v���C���[���܂Ƃ߂čs��)
	void Update();

	//�w�肵���v���C���[�̃G�t�F�N�g�}�l�[�W���[���擾
	Effect2DManager* GetManager(const int playerId);

private:

	std::unordered_map<int, std::unique_ptr<Effect2DManager>> managers_;

	//�V���O���g���̐���
	THIS_CLASS_IS_STATIC_SINGLETON(Effect2DManagerContainer);

	Effect2DManagerContainer();
	~Effect2DManagerContainer() = default;
};

