#pragma once
#include "../Utility/StaticSingleton.h"
#include "SceneManager.h"

class DataBank : public StaticSingleton<DataBank>
{
public:

	struct SYSTEM_INFO
	{
		SceneManager::MODE mode_;	//ゲームモード
		bool autoTackle_;			//タックルの自動化
	};

	//初期化処理
	void Init();

	//データを入力
	void Input(const SceneManager::MODE& mode);
	void Input(const bool& autoTackle);

	//出力
	inline const SYSTEM_INFO& Output()const { return systemInfo_; }

private:

	//シングルトン
	THIS_CLASS_IS_STATIC_SINGLETON(DataBank);

	//システム情報
	SYSTEM_INFO systemInfo_;

	DataBank();
	~DataBank() = default;
};

