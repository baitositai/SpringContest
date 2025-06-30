#pragma once
#include "../../framework.h"
#include "../../Manager/SceneManager.h"
#include "Hinder.h"
#include "HinderObject.h"

class Hinder;
class HinderObject;

class HinderManager
{
public:

	//�ǉ���
	static constexpr int ADD_OBJS = 2;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	HinderManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~HinderManager() = default;

	/// <summary>
	/// �ǂݍ���
	/// </summary>
	void Load();

	/// <summary>
	/// ������
	/// </summary>
	void Init();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:

	//�ז�
	std::unique_ptr<Hinder> hinders_[SceneManager::PLAYER_MAX];
	std::unique_ptr<HinderObject> objs_[SceneManager::PLAYER_MAX];

	//�W�Q���󂯂邩���ׂ�
	void CheckHinder();

};

