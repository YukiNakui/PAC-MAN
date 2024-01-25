#include "Player.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"
#include"Engine/Input.h"

Player::Player(GameObject* parent)
	:GameObject(parent,"Player")
{
}

void Player::Initialize()
{
	hPlayer_ = Model::Load("Model\\Player.fbx");
	assert(hPlayer_ >= 0);
	
	Camera::SetPosition(XMFLOAT3(6.5, 10, -5));
	Camera::SetTarget(XMFLOAT3(6.5, 0, 5.5));
	transform_.position_ = { 5.0f,0,5.0f };
}

void Player::Update()
{
	if (Input::IsKey(DIK_RIGHT))
		transform_.position_.x += 0.1f;
	if (Input::IsKey(DIK_LEFT))
		transform_.position_.x -= 0.1f;
	if (Input::IsKey(DIK_UP))
		transform_.position_.z += 0.1f;
	if (Input::IsKey(DIK_DOWN))
		transform_.position_.z -= 0.1f;
}

void Player::Draw()
{
	Model::SetTransform(hPlayer_, transform_);
	Model::Draw(hPlayer_);
}

void Player::Release()
{
}