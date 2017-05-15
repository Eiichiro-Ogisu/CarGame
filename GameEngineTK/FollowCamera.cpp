#include "FollowCamera.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;

// �ÓI�����o�ϐ��̏�����
const float FollowCamera::CAMERA_DISTANCE = 5.0f;

FollowCamera::FollowCamera(int width, int height)
	:Camera(width,height)
{
	_targetPos = Vector3::Zero;

	_targetAngle = 0.0;
}

void FollowCamera::Update()
{
	// ���_,�Q�Ɠ_
	Vector3 eyepos, refpos;

	// ���@�̏��2m���Q�Ɠ_�Ƃ���
	refpos = _targetPos + Vector3(0, 2, 0);

	// �Q�Ɠ_�Ǝ��_�̍����̃x�N�g��
	Vector3 cameraV(0, 0, CAMERA_DISTANCE);

	// ���@�̌��ɉ�荞�ނ��߂̉�]�s��𐶐�
	Matrix rotmat = Matrix::CreateRotationY(_targetAngle);

	// �����x�N�g������]
	cameraV = Vector3::TransformNormal(cameraV, rotmat);

	// �J�������W���v�Z
	eyepos = refpos + cameraV;

	SetEyePos(eyepos);

	SetRefPos(refpos);

	// ���N���X�̍X�V
	Camera::Update();
}

void FollowCamera::SetTargetPos(DirectX::SimpleMath::Vector3 targetPos)
{
	_targetPos = targetPos;
}

void FollowCamera::SetTargetAngle(float targetAngles)
{
	_targetAngle = targetAngles;
}
