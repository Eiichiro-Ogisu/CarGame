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

	_carVelocity = Vector3::Zero;
}

/// <summary>
/// �X�V����
/// </summary>
void Car::Update()
{
	// DXTK���Ǘ�����C���X�^���X���擾
	DXTK::DXTKResources& dxtk = DXTK::DXTKResources::singleton();

	dxtk.UpdateInputState();

	// �L-�{�[�h�̏��
	Keyboard::State keyboardState = dxtk.m_keyboard->GetState();

	// �Q�[���p�b�h�̏��
	GamePad::State gamepadState = dxtk.m_gamePad->GetState(0);

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
	
	if (gamepadState.IsConnected())
	{
		// A�L�[
		if (gamepadState.IsAPressed())
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

		// ���X�e�B�b�N�̉E����
		float dirX = gamepadState.thumbSticks.leftX;

		// ��]��
		float angle = _obj[CAR_BODY].GetRotation().y;
		_obj[CAR_BODY].SetRotation(Vector3(0, angle - dirX *0.025f, 0));

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
	//// ���˂���p�[�c�̃��[���h�s����擾
	//Matrix worldm = _obj[PLAYER_PARTS_HAND].GetWorld();

	//Matrix worldm2 = _obj[PLAYER_PARTS_HAND2].GetWorld();


	// ���[���h�s�񂩂�e�v�f�𒊏o
	Vector3 scale;			// ���[���h�X�P�[�����O
	Quaternion rotation;	// ���[���h��]
	Vector3 translation;	// ���[���h���W

	//worldm.Decompose(scale,rotation, translation);

	//// ���˂�p�[�c��e���番�����ēƗ�
	//_obj[PLAYER_PARTS_HAND].SetParent(nullptr);
	//_obj[PLAYER_PARTS_HAND].SetScale(scale);
	//_obj[PLAYER_PARTS_HAND].SetRotationQ(rotation);
	//_obj[PLAYER_PARTS_HAND].SetTransform(translation);

	//worldm2.Decompose(scale, rotation, translation);

	//_obj[PLAYER_PARTS_HAND2].SetParent(nullptr);
	//_obj[PLAYER_PARTS_HAND2].SetScale(scale);
	//_obj[PLAYER_PARTS_HAND2].SetRotationQ(rotation);
	//_obj[PLAYER_PARTS_HAND2].SetTransform(translation);


	//// �e�ۂ̑��x��ݒ�
	//_bulletVel = Vector3(0, 0, -0.5f);
	//_bulletVel = Vector3::Transform(_bulletVel, rotation);
}

void Car::ResetBullet()
{
		//_obj[PLAYER_PARTS_HAND].SetParent(&_obj[PLAYER_PARTS_BODY]);
		//_obj[PLAYER_PARTS_HAND2].SetParent(&_obj[PLAYER_PARTS_BODY]);

		//_obj[PLAYER_PARTS_HAND].SetTransform(Vector3(-0.5, 0.6, -0.2));
		//_obj[PLAYER_PARTS_HAND].SetRotation(Vector3(0, 0, 0));
		//_obj[PLAYER_PARTS_HAND].SetScale(Vector3(0.25, 0.25, 0.75));


		//_obj[PLAYER_PARTS_HAND2].SetTransform(Vector3(0.5, 0.6, -0.2));
		//_obj[PLAYER_PARTS_HAND2].SetRotation(Vector3(0,0,0));
		//_obj[PLAYER_PARTS_HAND2].SetScale(Vector3(0.25, 0.25, 0.75));

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

