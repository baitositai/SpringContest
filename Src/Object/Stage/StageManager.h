#pragma once
#include "../../framework.h"	//ここにDXLib等の様々なライブラリをまとめてる(プロジェクトが大きいゲームの場合このやり方はお勧めしないよ)

class StageBase;

class StageManager
{
public:

	//コンストラクタ
	StageManager();

	//デストラクタ(特に書くことがない時はdefaultを入れとく)
	~StageManager() = default;

	void Load();	//モデルや画像,音楽等の読み込み
	void Init();	//変数等の初期化
	void Update();	//更新処理
	void Draw();	//描画処理
	void Release();	//解放処理

private:

	//ステージの動的配列
	std::vector<StageBase*> stages_;

	//ステージの出現カウント
	int stageSpawnCounter_;

	//ステージの数
	int stageSpawn_;
};

