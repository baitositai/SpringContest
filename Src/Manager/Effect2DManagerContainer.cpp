#include "DataBank.h"
#include "SceneManager.h"
#include "Effect2DManager.h"
#include "Effect2DManagerContainer.h"


void Effect2DManagerContainer::Init()
{
    //初期化
    managers_.clear();

    //インスタンス生成数の確認
    int num = 1;
    if (DataBank::GetInstance().Output().mode_ == SceneManager::MODE::VS) { num = SceneManager::PLAYER_MAX; }

    //生成
    for (int i = 0; i < num; i++) { managers_[i] = std::make_unique<Effect2DManager>(); }
}

void Effect2DManagerContainer::Update()
{
    for (auto& it : managers_)
    {
        it.second->Update();
    }
}

Effect2DManager* Effect2DManagerContainer::GetManager(const int playerId)
{
    auto it = managers_.find(playerId);
    if (it != managers_.end())
    {
        return it->second.get();
    }
    return nullptr;
}

Effect2DManagerContainer::Effect2DManagerContainer()
{
    Init();
}