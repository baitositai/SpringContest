#pragma once
#include "../framework.h"
#include "../Utility/StaticSingleton.h"
#include "../Common/Vector2.h"

class PixelShader
	: public StaticSingleton<PixelShader>
{
public:

	// ピクセルシェーダ用オリジナル定数バッファの使用開始スロット
	static constexpr int CONSTANT_BUF_SLOT_BEGIN_PS = 3;
	
	// 頂点数
	static constexpr int NUM_VERTEX = 4;
	
	// 頂点インデックス数
	static constexpr int NUM_VERTEX_IDX = 6;
	
	// ポリゴン数
	static constexpr int NUM_POLYGON = 2;

	//バッファー数
	static constexpr int PS_CONST_FLOAT_COUNT = 8;

	enum class PS_TYPE
	{
		TEXTURE,
		COL_TX,
		FADE,
		FADE_TEXTURE,
		MAX
	};

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 解放
	/// </summary>
	void Destroy();

	/// <summary>
	/// 画像の通常描画
	/// </summary>
	/// <param name="pos"></param>位置
	/// <param name="handle"></param>画像
	void DrawGraph(
		const Vector2& pos, 
		const int& handle);

	/// <summary>
	/// サイズ指定描画
	/// </summary>
	/// <param name="pos"></param>座標
	/// <param name="size"></param>サイズ
	/// <param name="handle"></param>画像
	void DrawExtendGraphToShader(
		const Vector2& pos,
		const Vector2& size, 
		const int& handle);

	/// <summary>
	/// シェーダーを利用したサイズ指定描画
	/// </summary>
	/// <param name="pos"></param>座標
	/// <param name="size"></param>サイズ
	/// <param name="handle"></param>画像
	/// <param name="type"></param>シェーダー種類
	/// <param name="buf"></param>バッファー
	/// <param name="subBuf"></param>サブバッファー
	void DrawExtendGraphToShader(
		const Vector2& pos, 
		const Vector2& size,
		const int& handle, 
		const PS_TYPE& type,
		const COLOR_F& buf,
		const COLOR_F& subBuf = COLOR_F{});

private:

	//シングルトンの生成
	THIS_CLASS_IS_STATIC_SINGLETON(PixelShader);

	//頂点情報
	VERTEX2DSHADER vertex_[NUM_VERTEX];
	WORD index_[NUM_VERTEX_IDX];

	//シェーダー定数バッファ
	int psConstBuf_;

	//シェーダーのリソースマップ
	std::unordered_map< PS_TYPE, int>psMap_;

	//描画用の四角頂点の作成
	void MakeSquereVertex(Vector2 pos, Vector2 size);

	//シェーダーの読み込み
	void InitPS();

	//シェーダーの検索
	const int SearchPS(const PS_TYPE& ps)const;

	//コンストラクタ
	PixelShader();

	//デストラクタ
	~PixelShader() = default;

};

