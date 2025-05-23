#include <DxLib.h>
#include "../../Utility/Utility.h"
#include "Transform.h"

Transform::Transform(void)
{
	modelId = -1;

	scl = Utility::VECTOR_ONE;
	rot = Utility::VECTOR_ZERO;
	pos = Utility::VECTOR_ZERO;
	localPos = Utility::VECTOR_ZERO;

	matScl = MGetIdent();
	matRot = MGetIdent();
	matPos = MGetIdent();
	quaRot = Quaternion();
	quaRotLocal = Quaternion();

	collider = nullptr;
}

Transform::Transform(int model)
{
	modelId = model;

	scl = Utility::VECTOR_ONE;
	rot = Utility::VECTOR_ZERO;
	pos = Utility::VECTOR_ZERO;
	localPos = Utility::VECTOR_ZERO;

	matScl = MGetIdent();
	matRot = MGetIdent();
	matPos = MGetIdent();
	quaRot = Quaternion();
	quaRotLocal = Quaternion();

	collider = nullptr;

}

Transform::~Transform()
{
}

void Transform::Update()
{

	// 大きさ
	matScl = MGetScale(scl);

	// 回転
	rot = quaRot.ToEuler();
	matRot = quaRot.ToMatrix();

	// 位置
	matPos = MGetTranslate(pos);

	// 行列の合成
	MATRIX mat = MGetIdent();
	mat = MMult(mat, matScl);
	Quaternion q = quaRot.Mult(quaRotLocal);
	mat = MMult(mat, q.ToMatrix());
	mat = MMult(mat, matPos);

	// 行列をモデルに判定
	if (modelId != -1)
	{
		MV1SetMatrix(modelId, mat);
	}

	// 衝突判定の更新
	if (collider != nullptr)
	{
		MV1RefreshCollInfo(modelId);
	}


}

void Transform::SetModel(int model)
{
	modelId = model;
}

void Transform::MakeCollider(Collider::TYPE type)
{

	if (modelId == -1)
	{
		return;
	}

	collider = std::make_shared<Collider>(type, modelId);
	int ret = MV1SetupCollInfo(modelId, -1, 1, 1, 1);

}

VECTOR Transform::GetForward() const
{
	return GetDir(Utility::DIR_F);
}

VECTOR Transform::GetBack() const
{
	return GetDir(Utility::DIR_B);
}

VECTOR Transform::GetRight() const
{
	return GetDir(Utility::DIR_R);
}

VECTOR Transform::GetLeft() const
{
	return GetDir(Utility::DIR_L);
}

VECTOR Transform::GetUp() const
{
	return GetDir(Utility::DIR_U);
}

VECTOR Transform::GetDown() const
{
	return GetDir(Utility::DIR_D);
}

VECTOR Transform::GetDir(const VECTOR& vec) const
{
	return quaRot.PosAxis(vec);
}
