#pragma once
#include "../Utility/StaticSingleton.h"
#include "SceneManager.h"

class DataBank : public StaticSingleton<DataBank>
{
public:

	struct SYSTEM_INFO
	{
		int playerId_;				//プレイヤーID
		int playerNum_;				//プレイヤー人数
		SceneManager::MODE mode_;	//ゲームモード
		bool autoTackle_;			//タックルの自動化
	};

	//初期化処理
	void Init();

	/// <summary>
	/// プレイヤー番号を入力(プレイヤーごとで処理を分ける用)
	/// </summary>
	/// <param name="playerId"></param>プレイヤーの番号
	void Input(const int& playerId);

	/// <summary>
	/// プレイヤー人数を設定
	/// </summary>
	/// <param name="playerNum"></param>人数
	void InputPlayNum(const int& playerNum);

	/// <summary>
	/// ゲームモードを設定
	/// </summary>
	/// <param name="mode"></param>ゲームモード
	void Input(const SceneManager::MODE& mode);

	/// <summary>
	/// 自動攻撃の設定
	/// </summary>
	/// <param name="autoTackle"></param>trueの場合あり、falseの場合なし
	void Input(const bool& autoTackle);

	/// <summary>
	/// システム情報を返す
	/// </summary>
	/// <returns></returns>システム情報
	inline const SYSTEM_INFO& Output()const { return systemInfo_; }

private:

	//シングルトン
	THIS_CLASS_IS_STATIC_SINGLETON(DataBank);

	//システム情報
	SYSTEM_INFO systemInfo_;

	DataBank();
	~DataBank() = default;
};

