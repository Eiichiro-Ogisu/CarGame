/// <summary>
/// �Փ˔��胉�C�u����
/// </summary>

#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

// ��
class Sphere
{
public:
	DirectX::SimpleMath::Vector3 _center;	// ���S���W

	float _radius;	// ���a

	// �R���X�g���N�^
	Sphere()
	{
		_radius = 1.0f;
	}
};

// ����
class Segment
{
public:
	DirectX::SimpleMath::Vector3 Start;	// �n�_���W
	DirectX::SimpleMath::Vector3 End;	// �I�_���W
};

// �J�v�Z��
class Capsule
{
public:
	Segment _segment;	// �c��
	float _radius;		// ���a

	// �R���X�g���N�^
	Capsule()
	{
		_segment.Start = DirectX::SimpleMath::Vector3(0, 0, 0);
		_segment.End = DirectX::SimpleMath::Vector3(0, 1, 0);
		_radius = 1.0f;
	}
};

bool CheckSphere2Sphere(const Sphere & _sphereA, const Sphere & _sphereB);
