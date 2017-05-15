#pragma once
#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
public:
	// �����o�֐�
	Camera(int width, int height);

	virtual ~Camera();

	// �X�V
	virtual void Update();

	// �r���[�s��̎擾
	const DirectX::SimpleMath::Matrix& GetViewMatrix();

	// �ˉe�s����擾
	const DirectX::SimpleMath::Matrix& GetProjectionMatrix();

	DirectX::SimpleMath::Vector3 GetUpVec();

	// ���_���Z�b�g
	void SetEyePos(DirectX::SimpleMath::Vector3 eyePos);

	void SetRefPos(DirectX::SimpleMath::Vector3 ref);

	void SetUpVec(const DirectX::SimpleMath::Vector3& upVec);

	void SetFovY(float y);

	void SetAspect(float aspect);

	void SetNearclip(float nearclip);

	void SetFarclip(float farclip);
protected:
	// �ޗ��͂�����

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_cameraView;
	// ���_
	DirectX::SimpleMath::Vector3 m_eyePos;

	// �����_
	DirectX::SimpleMath::Vector3 m_refPos;

	// �ǂ��炪��ʏ������
	DirectX::SimpleMath::Vector3 m_upVec;

	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_cameraProj;

	// ������������p
	float m_fovY;

	// �A�X�y�N�g��
	float m_aspect;

	// ��O�̕\�����E
	float m_nearclip;

	// ���̕\�����E
	float m_farclip;
};
