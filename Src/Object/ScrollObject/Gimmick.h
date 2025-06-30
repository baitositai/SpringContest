#pragma once
#include "ObjectBase.h"
#include "../../Utility/Utility.h"

class Gimmick : public ObjectBase
{
public:

	//�X�P�[��
	static constexpr VECTOR SCALE = { 0.3f,0.3f ,0.3f };

	//�_���[�W��
	static constexpr int DAMAGE = -1;

	//�X�R�A��
	static constexpr int SCORE = -500;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Gimmick();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Gimmick();

	/// <summary>
	/// ���f���̏�����
	/// </summary>
	void InitModel() override;

	/// <summary>
	/// �Փˌ�̏�������
	/// </summary>
	/// <param name="player"></param>
	void OnCollision(Player& player) override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() override;

};
