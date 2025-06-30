#pragma once
#include "ObjectBase.h"

class LifeItem : public ObjectBase
{
public:

	//�X�P�[��
	static constexpr VECTOR SCALE = { 0.3f,0.3f ,0.3f };

	//�̗͉񕜗�
	static constexpr int LIFE_HEAL = 1;

	//�X�R�A��
	static constexpr int SCORE = 100;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	LifeItem();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~LifeItem();

	/// <summary>
	/// ���f��������
	/// </summary>
	void InitModel() override;

	/// <summary>
	/// �Փˌ�̏���
	/// </summary>
	/// <param name="player"></param>�v���C���[
	void OnCollision(Player& player) override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

};

