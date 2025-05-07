#pragma once
#include <DxLib.h>
class Transform;

class Capsule
{

public :

	// デバッグ時の簡易カプセル表示の色
	static constexpr int COLOR = 0xffffff;

	// コンストラクタ
	// カプセルをつけるオブジェクトを指定する
	Capsule(const Transform& parent);
	Capsule(const Capsule& base, const Transform& parent);

	// デストラクタ
	~Capsule();

	// 描画
	void Draw();

	// 親Transformからの相対位置を取得
	VECTOR GetLocalPosTop() const;
	VECTOR GetLocalPosDown() const;

	// 親Transformからの相対位置をセット
	void SetLocalPosTop(const VECTOR& pos);
	void SetLocalPosDown(const VECTOR& pos);

	// ワールド座標を取得
	VECTOR GetPosTop() const;
	VECTOR GetPosDown() const;

	// 相対座標を回転させてワールド座標で取得する
	VECTOR GetRotPos(const VECTOR& localPos) const;

	// 半径
	float GetRadius() const;
	void SetRadius(float radius);

	// 高さ
	float GetHeight() const;

	// カプセルの中心座標
	VECTOR GetCenter() const;

private :

	// カプセルをくっつける相手
	const Transform& transformParent_;

	// 親Transformからの相対位置(上側)
	VECTOR localPosTop_;

	// 親Transformからの相対位置(下側)
	VECTOR localPosDown_;

	// 半径
	float radius_;

};
