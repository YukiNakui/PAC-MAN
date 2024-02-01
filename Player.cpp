#include "Player.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"
#include"Engine/Input.h"
#include"Engine/Debug.h"

namespace
{
	const float PLAYER_MOVE_SPEED{ 1.0f };
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
	transform_.position_.x = 0.5;
	transform_.position_.z = 1.5;
	//map[13][1]Ç™ÅA(map[y][x]ÇÃèÍçáÇÃ)èâä˙à íu
}

void Player::Update()
{
	/*enum Dir
	{
		RIGHT,LEFT,UP,DOWN,NONE
	};
	int moveDir = Dir::NONE;*/

	XMVECTOR vFront = { 0,0,1,0 };
	XMVECTOR move = { 0,0,0,0 };

	if (Input::IsKeyDown(DIK_RIGHT))
	{
		move = XMVECTOR{ 1,0,0,0 };
		//transform_.position_.x += 0.1f;
		//moveDir = Dir::RIGHT;
		//transform_.rotate_.y = 90.0f;
	}
	else if (Input::IsKeyDown(DIK_LEFT)) 
	{
		move = XMVECTOR{ -1,0,0,0 };
		//transform_.position_.x -= 0.1f;
		//moveDir = Dir::LEFT;
		//transform_.rotate_.y = -90.0f;
	}
	else if (Input::IsKeyDown(DIK_UP))
	{
		move = XMVECTOR{ 0,0,1,0 };
		//transform_.position_.z += 0.1f;
		//moveDir = Dir::UP;
		//transform_.rotate_.y = 0.0f;
	}
	else if (Input::IsKeyDown(DIK_DOWN))
	{
		move = XMVECTOR{ 0,0,-1,0 };
		//transform_.position_.z -= 0.1f;
		//moveDir = Dir::DOWN;
		//transform_.rotate_.y = 180.0f;
	}
	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	pos = pos + speed_ * move;
	Debug::Log("(X,Y)=");
	Debug::Log(XMVectorGetX(pos));
	Debug::Log(",");
	Debug::Log(XMVectorGetZ(pos),true);
	if(!XMVector3Equal(move,XMVectorZero())) {
		XMStoreFloat3(&(transform_.position_), pos);

		XMVECTOR vdot = XMVector3Dot(vFront, move);
		assert(XMVectorGetX(vdot) <= 1 && XMVectorGetX(vdot) >= -1);
		float angle = acos(XMVectorGetX(vdot));

		XMVECTOR vCross = XMVector3Cross(vFront, move);
		if (XMVectorGetY(vCross) < 0)
		{
			angle *= -1;
		}

		transform_.rotate_.y = XMConvertToDegrees(angle);
	}
	//float rotAngle[5]{ 90,-90,0,180,0 };
	//transform_.rotate_.y = rotAngle[moveDir];
	
	int xOfMap = transform_.position_.x + 0.5;
	int yOfMap = transform_.position_.z - 0.5;


}

void Player::Draw()
{
	Model::SetTransform(hPlayer_, transform_);
	Model::Draw(hPlayer_);
}

void Player::Release()
{
}