/// <summary>
/// �Փ˔��胉�C�u����
/// </summary>
#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// ���Ƌ��̓����蔻��
/// </summary>
/// <param name="_sphereA">��A</param>
/// <param name="_sphereB">��B</param>
/// <returns>true:�q�b�g	false:�q�b�g����</returns>
bool CheckSphere2Sphere(const Sphere& _sphereA, const Sphere& _sphereB)
{
	// ��A��B�̒��S���W�̍����v�Z����
	Vector3 sub = _sphereB._center - _sphereA._center;

	float distanceSquare;

	// �O�����̒藝
	distanceSquare = sqrt(sub.x * sub.x + sub.y * sub.y + sub.z * sub.z);

	float radiusSquare;

	radiusSquare = _sphereA._radius + _sphereB._radius;

	radiusSquare = radiusSquare * radiusSquare;

	// ���������a�̘a���傫����Γ������Ă��Ȃ�
	if (distanceSquare > radiusSquare)
	{
		return false;
	}
	return true;
}