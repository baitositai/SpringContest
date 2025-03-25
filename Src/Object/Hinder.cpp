#include "../Manager/ResourceManager.h"
#include "Hinder.h"

Hinder::Hinder()
{
}

void Hinder::Load()
{
	//‰æ‘œ“Ç‚İ‚İ
	ResourceManager& res = ResourceManager::GetInstance();
	imgHinder_ = res.Load(ResourceManager::SRC::HINDER).handleId_;
	imgHinderGage_ = res.Load(ResourceManager::SRC::HINDER_GAGE).handleId_;
}

void Hinder::Init()
{
}

void Hinder::Update()
{
}

void Hinder::Draw()
{
}

void Hinder::Release()
{
}
