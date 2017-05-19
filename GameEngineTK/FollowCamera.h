/// <summary>
/// ���@�ɒǏ]����J�����N���X
/// </summary>
#pragma once

#include "Camera.h"
#include <Keyboard.h>

class FollowCamera :public Camera
{
public:
	// ���@�ƃJ�����̋���
	static const float CAMERA_DISTANCE;

	// �R���X�g���N�^
	FollowCamera(int width, int height);

	// ���t���[���X�V
	void Update()override;

	// TPS�J�����̏�����
	void InitializeTPS();

	// �Ǐ]�Ώۂ̍��W���Z�b�g
	void SetTargetPos(DirectX::SimpleMath::Vector3 & targetPos);

	// �Ǐ]�Ώۂ̊p�x���Z�b�g
	void SetTargetAngle(float targetAngles);

	// �L�[�{�[�h���Z�b�g
	void SetKeyboard(DirectX::Keyboard* keyboard);

protected:
	// ���@�̍��W
	DirectX::SimpleMath::Vector3 _targetPos;

	// �Ǐ]�Ώۂ̉�]�p
	float _targetAngle;

	// �L�[�{�[�h
	DirectX::Keyboard* _keyboard;

	// �L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

	bool isFPS = false;
};