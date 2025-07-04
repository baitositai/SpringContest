#pragma once
#include "../../Common/Vector2.h"
#include "../../framework.h"
#include "../../Application.h"

class HinderObject
{
public:

	//画像サイズ
	static constexpr int IMG_SIZE = 96;

	//速度
	static constexpr float SPEED = 4.0f;

	//初期角度
	static constexpr float ANGLE = 45.0f;

	//RAND範囲
	static constexpr int RAND_RANGE = 359;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	HinderObject();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~HinderObject() = default;

	/// <summary>
	/// 読み込み
	/// </summary>
	void Load();

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// オブジェクトを追加
	/// </summary>
	/// <param name="num"></param>追加値
	void AddObject(const int num);

private:

	struct Object
	{
		int type_;		//画像種類
		Vector2 pos_;	//位置
		Vector2 vec_;	//移動ベクトル
	};

	//画像
	int* imgs_;

	//オブジェクト配列
	std::vector<Object> objs_;
	
	//反射処理
	void Reflect(Vector2& vec, float nx, float ny);

};

