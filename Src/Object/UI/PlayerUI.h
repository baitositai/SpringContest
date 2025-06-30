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

	//��������ʒu
	static constexpr int EXPLAN_POS_X = 0;
	static constexpr int EXPLAN_POS_Y = 128;

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

	//�X�R�A�w�i���W�ʒu
	static constexpr int SCORE_UI_X = Application::SCREEN_SIZE_X - 320;
	static constexpr int SCORE_UI_Y = 100;

	static constexpr int REZALT_SCORE_UI_X = Application::SCREEN_HALF_X - 160;
	static constexpr int REZALT_SCORE_UI_Y = Application::SCREEN_HALF_Y - 40;

	//�X�R�A����
	static constexpr int SCORE_DIGIT = 5;

	//�^�b�N���Q�[�W����
	static constexpr int GAGE_SIZE_X = 128;
	static constexpr int GAGE_SIZE_Y = 50;

	//�N���A��UI�ʒu
	static constexpr int CLEAR_PLAYER_POS_Y = Application::SCREEN_HALF_Y - 64;

	//�N���A���b�ZUI�ʒu
	static constexpr int CLEAR_MES_POS_Y = Application::SCREEN_HALF_Y + 64;

	//�X�R�A�̍��W�ʒu
	static constexpr int RESULT_SCORE_INTERVAL = 35;
	static constexpr int SCORE_UI_POS_X = SCORE_UI_X + 120;
	static constexpr int SCORE_UI_POS_Y = SCORE_UI_Y + 10;
	static constexpr int RESULT_SCORE_POS_X = REZALT_SCORE_UI_X + 120;
	static constexpr int RESULT_SCORE_POS_Y = REZALT_SCORE_UI_Y + 10;

	//UI�`��p�I�t�Z�b�g
	static constexpr int UI_OFFSET = 35;
	
	PlayerUI();
	~PlayerUI() = default;

	void Load();
	void Init();
	void Update();
	void Draw(const Player & player);

	//������ԕύX
	void ChangeWinState(const WIN_STATE& state);

	//�N���A��Ԃ̕`��
	void ResultDraw();

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
	int imgTackleGage_;	//�^�b�N���Q�[�W
	int* imgPlayers_;	//�v���C���[
	int* imgExplan_;	//�������

	//����
	int *imgNumbers_;

	//�X�R�A
	int scoreDigits_[SCORE_DIGIT];

	//���[�h�ʕ`��
	std::function<void()> drawModeFunc_;

	//���U���g���
	std::function<void()> drawResultFunc_;

	//������ԕʕ`��
	std::function<void()> drawWinFunc_;

	//���[�h�ʕ`��
	void DrawMarathon();
	void DrawVS();

	//������ԕʕ`��
	void DrawNone();
	void DrawP1Win();
	void DrawP2Win();
	void DrawDraw();

	//�}���\�����U���g�`��
	void DrawResultScore();

	//�N���AUI�̕`��
	void VSClearDraw();
};

