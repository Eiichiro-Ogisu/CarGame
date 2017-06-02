#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
}

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize()
{
	// 自機パーツの読み込み
	_obj.resize(PLAYER_PARTS_NUM);
	_obj[PLAYER_PARTS_LEG].LoadModel(L"Resources\\leg.cmo");
	_obj[PLAYER_PARTS_BODY].LoadModel(L"Resources\\body.cmo");
	_obj[PLAYER_PARTS_BATTERY].LoadModel(L"Resources\\battery.cmo");
	_obj[PLAYER_PARTS_BATTERY2].LoadModel(L"Resources\\battery.cmo");
	_obj[PLAYER_PARTS_HAND].LoadModel(L"Resources\\hand.cmo");
	_obj[PLAYER_PARTS_HAND2].LoadModel(L"Resources\\hand.cmo");
	_obj[PLAYER_PARTS_HEAD].LoadModel(L"Resources\\head.cmo");

	// パーツの親子関係をセット
	_obj[PLAYER_PARTS_HEAD].SetParent(
		&_obj[PLAYER_PARTS_BODY]);

	_obj[PLAYER_PARTS_HAND].SetParent(
		&_obj[PLAYER_PARTS_BODY]);

	_obj[PLAYER_PARTS_HAND2].SetParent(
		&_obj[PLAYER_PARTS_BODY]);

	_obj[PLAYER_PARTS_LEG].SetParent(
		&_obj[PLAYER_PARTS_BODY]);

	_obj[PLAYER_PARTS_BATTERY].SetParent(
		&_obj[PLAYER_PARTS_BODY]);

	_obj[PLAYER_PARTS_BATTERY2].SetParent(
		&_obj[PLAYER_PARTS_BODY]);

	// 親からのオフセット
	// ボディの座標をいい感じの位置に
	_obj[PLAYER_PARTS_BODY].SetTransform(Vector3(0, 0.25, 0));

	// 足をいい感じに
	_obj[PLAYER_PARTS_LEG].SetScale(Vector3(0.8, 0.25, 0.5));

	_obj[PLAYER_PARTS_LEG].SetTransform(Vector3(0, -0.25, 0));

	// 両手をいい感じに
	_obj[PLAYER_PARTS_HAND].SetTransform(Vector3(-0.5, 0.6, -0.2));
	_obj[PLAYER_PARTS_HAND].SetScale(Vector3(0.25, 0.25, 0.75));

	_obj[PLAYER_PARTS_HAND2].SetTransform(Vector3(0.5, 0.6, -0.2));
	_obj[PLAYER_PARTS_HAND2].SetScale(Vector3(0.25, 0.25, 0.75));

	// 頭をいい感じに
	_obj[PLAYER_PARTS_HEAD].SetTransform(Vector3(0, 1, 0));
	_obj[PLAYER_PARTS_HEAD].SetScale(Vector3(1.5, 1.5, 1.5));

	// タンクをいい感じに
	_obj[PLAYER_PARTS_BATTERY].SetRotation(Vector3(0, 135, -0.55));
	_obj[PLAYER_PARTS_BATTERY].SetTransform(Vector3(-0.5, 0.9, -0.15));
	_obj[PLAYER_PARTS_BATTERY].SetScale(Vector3(0.5, 0.5, 0.5));


	_obj[PLAYER_PARTS_BATTERY2].SetRotation(Vector3(0, 135, 0.55));
	_obj[PLAYER_PARTS_BATTERY2].SetTransform(Vector3(0.5, 0.9, -0.15));
	_obj[PLAYER_PARTS_BATTERY2].SetScale(Vector3(0.5, 0.5, 0.5));

}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{
	// DXTKを管理するインスタンスを取得
	DXTK::DXTKResources& dxtk = DXTK::DXTKResources::singleton();

	dxtk.UpdateInputState();

	// キ-ボードの状態
	Keyboard::State keyboardState = dxtk.m_keyboard->GetState();

	// キー操作
	if (keyboardState.W)
	{
		// 移動量
		Vector3 moveV = Vector3(0.0f, 0.0f, -0.1f);

		float angle = _obj[PLAYER_PARTS_BODY].GetRotation().y;

		Matrix rotmat = Matrix::CreateRotationY(angle);

		moveV = Vector3::TransformNormal(moveV, rotmat);

		// 自機移動
		Vector3 pos = _obj[PLAYER_PARTS_BODY].GetTranslation();
		_obj[PLAYER_PARTS_BODY].SetTransform(pos + moveV);
	}

	if (keyboardState.S)
	{
		// 移動量
		Vector3 moveV = Vector3(0.0f, 0.0f, 0.1f);

		float angle = _obj[PLAYER_PARTS_BODY].GetRotation().y;

		Matrix rotmat = Matrix::CreateRotationY(angle);

		moveV = Vector3::TransformNormal(moveV, rotmat);

		// 自機移動
		Vector3 pos = _obj[PLAYER_PARTS_BODY].GetTranslation();
		_obj[PLAYER_PARTS_BODY].SetTransform(pos + moveV);
	}

	if (keyboardState.A)
	{
		// 回転量
		float angle = _obj[PLAYER_PARTS_BODY].GetRotation().y;
		_obj[PLAYER_PARTS_BODY].SetRotation(Vector3(0, angle + 0.03f, 0));
	}

	if (keyboardState.D)
	{
		// 回転量
		//float rot = -0.03f;
		float angle = _obj[PLAYER_PARTS_BODY].GetRotation().y;
		_obj[PLAYER_PARTS_BODY].SetRotation(Vector3(0, angle - 0.03f, 0));

	}
	for (std::vector<Obj3d>::iterator it = _obj.begin();
		it != _obj.end();
		it++)
	{
		it->Update();
	}
}

void Player::Draw()
{
	for (std::vector<Obj3d>::iterator it = _obj.begin(); 
		it != _obj.end();
		it++)
	{
		it->Draw();
	}
}

const DirectX::SimpleMath::Vector3 & Player::GetPosition()
{
	// TODO: return ステートメントをここに挿入します
	return _obj[PLAYER_PARTS_BODY].GetTranslation();
}

void Player::SetPosition(const DirectX::SimpleMath::Vector3 & trans)
{
	_obj[PLAYER_PARTS_BODY].SetTransform(trans);
}

const DirectX::SimpleMath::Matrix & Player::GetLocalWorld()
{
	// TODO: return ステートメントをここに挿入します
	return _obj[PLAYER_PARTS_BODY].GetWorld();

}

const DirectX::SimpleMath::Vector3 & Player::GetAngle()
{
	// TODO: return ステートメントをここに挿入します
	return _obj[PLAYER_PARTS_BODY].GetRotation();
}

