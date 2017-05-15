#include "Camera.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera(int width, int height)
{
	// �����o�ϐ��̏�����
	m_cameraView = Matrix::Identity;

	m_eyePos = Vector3(0, 0, 5);

	m_refPos = Vector3(0, 0, 0);

	m_upVec = Vector3(0, 10.0f, 0);

	m_cameraProj = Matrix::Identity;

	m_fovY = 0;

	m_aspect = 0;

	m_nearclip = 0;

	m_farclip = 0;
}

/// <summary>
/// �X�V����
/// </summary>
void Camera::Update()
{
	// �r���[�s��𐶐�
	m_cameraView = Matrix::CreateLookAt(m_eyePos, m_refPos, m_upVec);

	// �ˉe�s��̐���(�������e)
	m_cameraProj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);

}

/// <summary>
/// �r���[�s���Ԃ�
/// </summary>
/// <returns>�r���[�s��</returns>
const Matrix& Camera::GetViewMatrix()
{
	return m_cameraView;
}
const Matrix& Camera::GetProjectionMatrix()
{
	return m_cameraProj;
}

Vector3 Camera::GetUpVec()
{
	return m_upVec;
}

void Camera::SetEyePos(DirectX::SimpleMath::Vector3 eyePos)
{
	m_eyePos = eyePos;
}


void Camera::SetRefPos(Vector3 ref)
{
	m_refPos = ref;
}

void Camera::SetUpVec(const Vector3& upVec)
{
	m_upVec = upVec;
}

void Camera::SetFovY(float y)
{
	m_fovY = y;
}

void Camera::SetAspect(float aspect)
{
	m_aspect = aspect;
}

void Camera::SetNearclip(float nearclip)
{
	m_nearclip = nearclip;
}

void Camera::SetFarclip(float farclip)
{
	m_farclip = farclip;
}

Camera::~Camera()
{
	
}