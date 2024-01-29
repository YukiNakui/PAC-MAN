#include "Player.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"
#include"Engine/Input.h"

namespace
{
	const float PLAYER_MOVE_SPEED{ 0.1f };
}

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hPlayer_(-1),speed_(PLAYER_MOVE_SPEED)
{
}

void Player::Initialize()
{
	hPlayer_ = Model::Load("Model\\Player.fbx");
	assert(hPlayer_ >= 0);
	
	Camera::SetPosition(XMFLOAT3(6.5, 15, -3));
	Camera::SetTarget(XMFLOAT3(6.5, 0, 5.5));
	transform_.position_ = { 6.5,0,7.5 };
	transform_.rotate_ = { 0,0,0 };
}

void Player::Update()
{
	/*enum Dir
	{
		RIGHT,LEFT,UP,DOWN,NONE
	};
	int moveDir = Dir::NONE;*/

	XMVECTOR vFront = { 0,0,1,0 };
	XMVECTOR move = { 0,0,1,0 };

	if (Input::IsKey(DIK_RIGHT))
	{
		move = XMVECTOR{ 1.0,0,0,0 };
		//transform_.position_.x += 0.1f;
		//moveDir = Dir::RIGHT;
		//transform_.rotate_.y = 90.0f;
	}
	else if (Input::IsKey(DIK_LEFT)) 
	{
		move = XMVECTOR{ -1.0,0,0,0 };
		//transform_.position_.x -= 0.1f;
		//moveDir = Dir::LEFT;
		//transform_.rotate_.y = -90.0f;
	}
	else if (Input::IsKey(DIK_UP))
	{
		move = XMVECTOR{ 0,0,1,0 };
		//transform_.position_.z += 0.1f;
		//moveDir = Dir::UP;
		//transform_.rotate_.y = 0.0f;
	}
	else if (Input::IsKey(DIK_DOWN))
	{
		move = XMVECTOR{ 0,0,-1,0 };
		//transform_.position_.z -= 0.1f;
		//moveDir = Dir::DOWN;
		//transform_.rotate_.y = 180.0f;
	}
	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	pos = pos + speed_ * move;
	XMStoreFloat3(&(transform_.position_), pos);

	XMVECTOR vdot = XMVector3Dot(vFront, move);
	float angle = acos(XMVectorGetX(vdot));

	XMVECTOR vCloss = XMVector3Dot(vFront, move);
	if (XMVectorGetY(vCloss)<0)
	{
		angle *= -1;
	}

	transform_.rotate_.y = XMConvertToDegrees(angle);

	//float rotAngle[5]{ 90,-90,0,180,0 };
	//transform_.rotate_.y = rotAngle[moveDir];
	

	/*if (transform_.position_.x > 12.5f)
		transform_.position_.x = 12.5f;
	if (transform_.position_.x < 0.5f)
		transform_.position_.x = 0.5f;
	if (transform_.position_.z > 13.5f)
		transform_.position_.z = 13.5f;
	if (transform_.position_.z < 1.5f)
		transform_.position_.z = 1.5f;*/
}

void Player::Draw()
{
	Model::SetTransform(hPlayer_, transform_);
	Model::Draw(hPlayer_);
}

void Player::Release()
{
}