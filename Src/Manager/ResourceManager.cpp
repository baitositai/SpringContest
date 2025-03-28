#include "../Application.h"
#include "ResourceManager.h"


void ResourceManager::Init(void)
{
	std::unique_ptr<Resource> res;
	std::string path_Omuretu = "Character/Omuretu/";
	std::string path_Stage = "Stage/";

	//�^�C�g���摜
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "GameLogo.png");
	resourcesMap_.emplace(SRC::TITLE, std::move(res));

	//�^�C�g������
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "PushSpace.png");
	resourcesMap_.emplace(SRC::TITLE_UI, std::move(res));

	//�^�C�g���w�i
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "TitleBackGround.png");
	resourcesMap_.emplace(SRC::TITLE_BACKGROUND, std::move(res));

	// �v���C���[�e
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Shadow.png");
	resourcesMap_.emplace(SRC::PLAYER_SHADOW, std::move(res));

	//�I�����c(����)
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "Alphabet.png",
		ALPHABET_NUM_X, ALPHABET_NUM_Y, ALPHABET_SIZE_X, ALPHABET_SIZE_Y);
	resourcesMap_.emplace(SRC::ALPHABET, std::move(res));

	//�v���C���[
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "Player/Player.mv1");
	resourcesMap_.emplace(SRC::PLAYER, std::move(res));

	//�X�e�[�W
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "Stage/MainPlanet.mv1");
	resourcesMap_.emplace(SRC::STAGE, std::move(res));

	//�X�J�C�h�[��
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "SkyDome/Skydome.mv1");
	resourcesMap_.emplace(SRC::SKY_DOME, std::move(res));

	//�G
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "Enemy/Zombie Cartoon_01.mv1");
	resourcesMap_.emplace(SRC::ENEMY, std::move(res));

	//���e
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "ScrollObject/Bomb.mv1");
	resourcesMap_.emplace(SRC::BOMB, std::move(res));

	//�n�[�g
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "ScrollObject/Heart.mv1");
	resourcesMap_.emplace(SRC::HEART, std::move(res));

	//�|�[�V����
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "ScrollObject/Potion.mv1");
	resourcesMap_.emplace(SRC::POTION, std::move(res));

	//�v���C���[�A�C�R��
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "PlayerIcons.png",
		PLAYER_ICONS_NUM_X, PLAYER_ICONS_NUM_Y, PLAYER_ICONS_SIZE, PLAYER_ICONS_SIZE);
	resourcesMap_.emplace(SRC::PLAYER_ICONS, std::move(res));

	//���C�tUI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "LifeUi.png");
	resourcesMap_.emplace(SRC::LIFE_UI, std::move(res));

	//�p���[UI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "PowerUi.png");
	resourcesMap_.emplace(SRC::POWER_UI, std::move(res));

	//�X�R�AUI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "ScoreUi.png");
	resourcesMap_.emplace(SRC::SCORE_UI, std::move(res));

	//���ז�UI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Hinder.png");
	resourcesMap_.emplace(SRC::HINDER, std::move(res));

	//���ז��Q�[�WUI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "HinderGage.png");
	resourcesMap_.emplace(SRC::HINDER_GAGE, std::move(res));

	//�����摜
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "Numbers.png",
		NUMBERS_NUM_X, NUMBERS_NUM_Y, NUMBERS_SIZE, NUMBERS_SIZE);
	resourcesMap_.emplace(SRC::NUMBER, std::move(res));

	//�����摜2
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "Numbers2.png",
		NUMBERS2_NUM_X, NUMBERS2_NUM_Y, NUMBERS2_SIZE, NUMBERS2_SIZE);
	resourcesMap_.emplace(SRC::NUMBER2, std::move(res));

	//���C�t
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Life.png");
	resourcesMap_.emplace(SRC::LIFE, std::move(res));

	//�p���[
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Power.png");
	resourcesMap_.emplace(SRC::POWER, std::move(res));

	//�v���C���[UI
	res = std::make_unique<Resource>(Resource::TYPE::IMGS, Application::PATH_IMAGE + "PlayersUI.png",
		PLAYER_UI_NUM_X, PLAYER_UI_NUM_Y, PLAYER_UI_SIZE_X, PLAYER_UI_SIZE_Y);
	resourcesMap_.emplace(SRC::PLAYER_UI, std::move(res));

	//�^�C�}�[UI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Timer.png");
	resourcesMap_.emplace(SRC::TIMER_UI, std::move(res));

	//����UI
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Win.png");
	resourcesMap_.emplace(SRC::WIN_UI, std::move(res));

	//��������
	res = std::make_unique<Resource>(Resource::TYPE::IMG, Application::PATH_IMAGE + "Draw.png");
	resourcesMap_.emplace(SRC::DRAW, std::move(res));

	//�^�b�N���G�t�F�N�g
	res = std::make_unique<Resource>(Resource::TYPE::EFFEKSEER, Application::PATH_EFFECT + "Tackle/Tackle.efkefc");
	resourcesMap_.emplace(SRC::TACKLE_EFK, std::move(res));

	//���o�G�t�F�N�g�i�����p�j
	res = std::make_unique<Resource>(Resource::TYPE::EFFEKSEER, Application::PATH_EFFECT + "StarDust/StarDust.efkefc");
	resourcesMap_.emplace(SRC::STAR_DUST_EFK, std::move(res));

	//�^�C�g��BGM
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Title.mp3");
	resourcesMap_.emplace(SRC::TITLE_BGM, std::move(res));

	//�Z���N�g�V�[��BGM
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Select.mp3");
	resourcesMap_.emplace(SRC::SELECT_BGM, std::move(res));

	//�Q�[���V�[��BGM1
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Game1.mp3");
	resourcesMap_.emplace(SRC::GAMEBGM1, std::move(res));

	//�Q�[���V�[��BGM2
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Game2.mp3");
	resourcesMap_.emplace(SRC::GAMEBGM2, std::move(res));

	//�V�[���J��SE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "SceneChange.mp3");
	resourcesMap_.emplace(SRC::CHANGE_SCENE_SE, std::move(res));

	//�X�C�b�`�I��
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "SwitchOn.mp3");
	resourcesMap_.emplace(SRC::SWITCH_ON_SE, std::move(res));

	//�X�C�b�`�I�t
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "SwitchOff.mp3");
	resourcesMap_.emplace(SRC::SWITCH_OFF_SE, std::move(res));

	//�J�E���g3
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Count3.mp3");
	resourcesMap_.emplace(SRC::COUNT_3, std::move(res));

	//�J�E���g2
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Count2.mp3");
	resourcesMap_.emplace(SRC::COUNT_2, std::move(res));

	//�J�E���g1
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Count1.mp3");
	resourcesMap_.emplace(SRC::COUNT_1, std::move(res));

	//�J�E���g0
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Count0.mp3");
	resourcesMap_.emplace(SRC::COUNT_0, std::move(res));

	//GOSE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Go.mp3");
	resourcesMap_.emplace(SRC::GO_SE, std::move(res));

	//�A�C�e��GetSE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "ItemGet.mp3");
	resourcesMap_.emplace(SRC::ITEM_GET_SE, std::move(res));

	//�^�b�N��SE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Tackle.mp3");
	resourcesMap_.emplace(SRC::TACKLE_SE, std::move(res));

	//�_���[�WSE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Damage.mp3");
	resourcesMap_.emplace(SRC::DAMAGE_SE, std::move(res));

	//�N���ASE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Clear.mp3");
	resourcesMap_.emplace(SRC::CLEAR_SE, std::move(res));

	//�W�����vSE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Jump.mp3");
	resourcesMap_.emplace(SRC::JUMP_SE, std::move(res));

	//����SE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "Blast.mp3");
	resourcesMap_.emplace(SRC::BLAST_SE, std::move(res));

	//����SE
	res = std::make_unique<Resource>(Resource::TYPE::SOUND, Application::PATH_SOUND + "EnemyDamage.mp3");
	resourcesMap_.emplace(SRC::ENEMY_DAMAGE_SE, std::move(res));

}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	resourcesMap_.clear();
}

Resource &ResourceManager::Load(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return dummy_;
	}
	return res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
	Init();
}

Resource& ResourceManager::_Load(SRC src)
{
	// ���[�h�ς݃`�F�b�N
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return lPair->second;
	}

	// ���\�[�X�o�^�`�F�b�N
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// �o�^����Ă��Ȃ�
		return dummy_;
	}

	// ���[�h����
	rPair->second->Load();

	// �O�̂��߃R�s�[�R���X�g���N�^
	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;
}
