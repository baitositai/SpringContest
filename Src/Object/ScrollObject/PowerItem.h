#pragma once
#include "ObjectBase.h"

class PowerItem : public ObjectBase
{
public:

	//�X�P�[��
	static constexpr VECTOR SCALE = { 0.3f,0.3f ,0.3f };

	//�p���[�̉񕜗�
	static constexpr int POWER_HEAL = 1;

	//�X�R�A��
	static constexpr int SCORE = 100;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PowerItem();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PowerItem();

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

