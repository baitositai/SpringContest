#pragma once
#include "../../framework.h"
#include "../../Application.h"

class Player;

class PlayerUI
{
public:

	//�������
	enum class WIN_STATE
	{
		NONE,
		P1_WIN,
		P2_WIN,
		DRAW
	};

	//�A�C�R�����W�ʒu
	static constexpr int ICON_POS_X = 0;
	static constexpr int ICON_POS_Y = 0;

	//���C�tUI���W�ʒu
	static constexpr int LIFE_UI_X = 128;
	static constexpr int LIFE_UI_Y = 0;

	//���C�t���W�ʒu
	static constexpr int LIFE_X = 128;
	static constexpr int LIFE_Y = 32;

	//�p���[UI���W�ʒu
	static constexpr int POWER_UI_X = 128;
	static constexpr int POWER_UI_Y = 64;

	//�p���[���W�ʒu
	static constexpr int POWER_X = 128;
	static constexpr int POWER_Y = 96;

	//�X�R�A���W�ʒu
	static constexpr int SCORE_UI_X = Application::SCREEN_SIZE_X - 320;
	static constexpr int SCORE_UI_Y = 100;

	//�X�R�A����
	static constexpr int SCORE_DIGIT = 5;

	PlayerUI();
	~PlayerUI() = default;

	void Load();
	void Init();
	void Update();
	void Draw(const Player & player);
	void Release();

	//������ԕύX
	void ChangeWinState(const WIN_STATE& state);

	//�N���A��Ԃ̕`��
	void VSClearDraw();

private:

	//�������
	WIN_STATE winState_;

	//�A�C�R���摜
	int *imgPlayerIcons_;

	//���b�Z�[�W�摜
	int imgLife_;		//�̗�
	int imgPow_;		//�p���[
	int imgLifeMes_;	//�̗�UI
	int imgPowMes_;		//�p���[UI
	int imgScoreMes_;	//�X�R�A
	int imgWin_;		//����
	int imgDraw_;		//��������
	int* imgPlayers_;	//�v���C���[

	//����
	int *imgNumbers_;

	//�X�R�A
	int scoreDigits_[SCORE_DIGIT];

	//���[�h�ʕ`��
	std::function<void(void)> drawModeFunc_;

	//������ԕʕ`��
	std::function<void(void)> drawWinFunc_;

	//���[�h�ʕ`��
	void DrawMarason();
	void DrawVS();

	//������ԕʕ`��
	void DrawNone();
	void DrawP1Win();
	void DrawP2Win();
	void DrawDraw();
};

