#include "Car.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Car::Car()
{
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Car::~Car()
{
}

/// <summary>
/// ������
/// </summary>
void Car::Initialize()
{
	// ���@�p�[�c�̓ǂݍ���
	_obj.resize(CAR_PARTS_NUM);
	_obj[CAR_BODY].LoadModel(L"Resources\\body.cmo");
	_obj[CAR_TIRE].LoadModel(L"Resources\\tire.cmo");

	// �p�[�c�̐e�q�֌W���Z�b�g
	_obj[CAR_TIRE].SetParent(
		&_obj[CAR_BODY]);



	// �e����̃I�t�Z�b�g
	// �{�f�B�̍��W�����������̈ʒu��
	_obj[CAR_BODY].SetTransform(Vector3(0, 0, 0));
	_obj[CAR_BODY].SetScale(Vector3(0.025f, 0.025f, 0.025f));

	//_obj[CAR_BODY].SetRotation(Vector3(0.0f, 180.0f, 0.0f));

	// ��������������
	_obj[CAR_TIRE].SetScale(Vector3(1.0f, 1.0f, 1.0f));

	// TODO
		//{// �e�ۗp�̓����蔻���ݒ�
		//_collisionNodeBullet.Initialize();
		//		// �e�p�[�c���w��
		//_collisionNodeBullet.SetParent(&_obj[PLAYER_PARTS_HAND]);
		//_collisionNodeBullet.SetTrans(Vector3(0, 0, 0));
		//_collisionNodeBullet.SetLocalRadius(0.5f);
		//}

	_carSpeed = 0.0f;

	_isMove = false;

	// DXTK���Ǘ�����C���X�^���X���擾
	DXTK::DXTKResources& dxtk = DXTK::DXTKResources::singleton();

	dxtk.m_buttons.Reset();
}

/// <summary>
/// �X�V����
/// </summary>
void Car::Update()
{
	// DXTK���Ǘ�����C���X�^���X���擾
	DXTK::DXTKResources& dxtk = DXTK::DXTKResources::singleton();

	// �L�[�{�[�h�̏��(�����������g��)
	auto state = dxtk.m_gamePad->GetState(0);

	dxtk.m_buttons.Update(state);

	//dxtk.UpdateInputState();

	// �L-�{�[�h�̏��
	Keyboard::State keyboardState = dxtk.m_keyboard->GetState();

	//// �Q�[���p�b�h�̏��
	//GamePad::State gamepadState = dxtk.m_gamePad->GetState(0);

	// �L�[����
	if (keyboardState.W)
	{
		// �ړ���
		Vector3 moveV = Vector3(0.0f, 0.0f, -0.1f);

		float angle = _obj[CAR_BODY].GetRotation().y;

		Matrix rotmat = Matrix::CreateRotationY(angle);

		moveV = Vector3::TransformNormal(moveV, rotmat);

		// ���@�ړ�
		Vector3 pos = _obj[CAR_BODY].GetTranslation();
		_obj[CAR_BODY].SetTransform(pos += moveV);
	}

	if (keyboardState.S)
	{
		// �ړ���
		Vector3 moveV = Vector3(0.0f, 0.0f, 0.1f);

		float angle = _obj[CAR_BODY].GetRotation().y;

		Matrix rotmat = Matrix::CreateRotationY(angle);

		moveV = Vector3::TransformNormal(moveV, rotmat);

		// ���@�ړ�
		Vector3 pos = _obj[CAR_BODY].GetTranslation();
		_obj[CAR_BODY].SetTransform(pos += moveV);
	}

	if (keyboardState.A)
	{
		// ��]��
		float angle = _obj[CAR_BODY].GetRotation().y;
		_obj[CAR_BODY].SetRotation(Vector3(0, angle + 0.03f, 0));
	}

	if (keyboardState.D)
	{
		// ��]��
		//float rot = -0.03f;
		float angle = _obj[CAR_BODY].GetRotation().y;
		_obj[CAR_BODY].SetRotation(Vector3(0, angle - 0.03f, 0));
	}

	/// <summary>
	/// �Q�[���p�b�h����
	/// </summary>
	
	if (state.IsConnected())
	{
		// A�{�^���������ꂽ��
		if (dxtk.m_buttons.a)
		{
			// ����
			Acceleration();
		}

	}
	
	/// <summary>
	/// �ړ����ɍs���鏈��
	/// </summary>
	// �ړ����Ă���Ȃ�
	if (_isMove)
	{
		AddSpeed();

		// �ړ����Ă���Ƃ��̂݉�]�\��
		SteeringOperation();
	}

	// �ړ����Ă���Ȃ猸����������
	if (_isMove && dxtk.m_buttons.a == !GamePad::ButtonStateTracker::PRESSED)
	{
		// �Ԃ̑��x�����X�ɗ��Ƃ��Ă���
		Deceleration();
	}

	/// <summary>
	/// �Ԃ̃X�s�[�h�����ȉ��ɂȂ������~������
	/// </summary>
	if (dxtk.m_buttons.a == !GamePad::ButtonStateTracker::PRESSED &&
		_carSpeed < 0.02f && _isMove)
	{
		_isMove = false;
	}

	// �����蔻��̍X�V
	_collisionNodeBullet.Update();


	if (keyboardState.Space)
	{
		FireBullet();

		isFire = true;
	}

	Calc();
}

void Car::Draw()
{
	for (std::vector<Obj3d>::iterator it = _obj.begin(); 
		it != _obj.end();
		it++)
	{
		it->Draw();
	}
	_collisionNodeBullet.Draw();

	_collisionNodeBody.Draw();
}

void Car::FireBullet()
{
}

void Car::ResetBullet()
{
}

const DirectX::SimpleMath::Vector3 & Car::GetPosition()
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	return _obj[CAR_BODY].GetTranslation();
}

void Car::Calc()
{
	for (std::vector<Obj3d>::iterator it = _obj.begin();
		it != _obj.end();
		it++)
	{
		it->Update();
	}

	_collisionNodeBody.Update();

	_collisionNodeBullet.Update();
}

void Car::SetPosition(const DirectX::SimpleMath::Vector3 & trans)
{
	_obj[CAR_BODY].SetTransform(trans);
}

const DirectX::SimpleMath::Matrix & Car::GetLocalWorld()
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	return _obj[CAR_BODY].GetWorld();

}

const DirectX::SimpleMath::Vector3 & Car::GetRot()
{
	// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	return _obj[CAR_BODY].GetRotation();
}

/// <summary>
/// �ړ��J�n
/// </summary>
void Car::Acceleration()
{
	_carSpeed += MOVE_SPEED_FIRST;

	// �ړ��t���O�I����
	_isMove = true;
}

/// <summary>
/// �ړ��I��
/// </summary>
void Car::Breaking()
{
	// TODO: �u���[�L�̎���
	//_carSpeed = 0.0f;
}

/// <summary>
/// ��������
/// </summary>
void Car::Deceleration()
{
	_carSpeed *= DECELERATION_VALUE;
}

/// <summary>
/// ��������
/// </summary>
void Car::AddSpeed()
{
	// �i�s�����x�N�g���̐ݒ�
	Vector3 moveVec = Vector3(0.0f, 0.0f, -1.0f);

	// ��]�擾
	float angle = _obj[CAR_BODY].GetRotation().y;

	// ���[���h���W�n�ɕϊ�
	Matrix rotmat = Matrix::CreateRotationY(angle);

	moveVec = Vector3::TransformNormal(moveVec, rotmat);

	Vector3 carVelocity = moveVec * _carSpeed;

	// ���@�ړ�
	Vector3 pos = _obj[CAR_BODY].GetTranslation();

	_obj[CAR_BODY].SetTransform(pos += carVelocity);
}

/// <summary>
/// �Ԃ̃n���h������
/// </summary>
void Car::SteeringOperation()
{
	// DXTK���Ǘ�����C���X�^���X���擾
	DXTK::DXTKResources& dxtk = DXTK::DXTKResources::singleton();

	// �L�[�{�[�h�̏��(�����������g��)
	auto state = dxtk.m_gamePad->GetState(0);

	// �����X�e�B�b�N�̍��E����
	float dirX = state.thumbSticks.leftX;

	// ��]��
	float angle = _obj[CAR_BODY].GetRotation().y;
	_obj[CAR_BODY].SetRotation(Vector3(0, angle - dirX *0.01f, 0));
}
