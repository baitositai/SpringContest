#include "ResourceManager.h"

void ResourceManager::Init(void)
{
	std::unique_ptr<Resource> res;
	std::string path_Omuretu = "Character/Omuretu/";
	std::string path_Stage = "Stage/";

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

	//�X�J�C�h�[��
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "SkyDome/Skydome.mv1");
	resourcesMap_.emplace(SRC::SKY_DOME, std::move(res));

	//�G
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "Enemy/Zombie Cartoon_01.mv1");
	resourcesMap_.emplace(SRC::ENEMY, std::move(res));

	//�X�e�[�W
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "Stage/stage.mv1");
	resourcesMap_.emplace(SRC::STAGE, std::move(res));


	//�E��
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "Stage/stageRight.mv1");
	resourcesMap_.emplace(SRC::STAGERIGHT, std::move(res));

	//����
	res = std::make_unique<Resource>(Resource::TYPE::MODEL, Application::PATH_MODEL + "Stage/stageLeft.mv1");
	resourcesMap_.emplace(SRC::STAGELEFT, std::move(res));

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
