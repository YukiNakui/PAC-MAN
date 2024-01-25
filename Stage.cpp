#include "Stage.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"
#include"Engine/Input.h"
Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage")
{
}

void Stage::Initialize()
{
	hPlayer_ = Model::Load("Model\\Player.fbx");
	assert(hPlayer_ >= 0);
	hFloor_ = Model::Load("Model\\Floor.fbx");
	assert(hFloor_ >= 0);
	hWall_ = Model::Load("Model\\Wall.fbx");
	assert(hWall_ >= 0);
	Camera::SetPosition(XMFLOAT3(6.5, 10, -5));
	Camera::SetTarget(XMFLOAT3(6.5, 0, 5.5));
	transform_.position_ = { 5.0f,0,5.0f };
}

void Stage::Update()
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

void Stage::Draw()
{
	Transform floorTrans;
	Transform wallTrans;
	for (int j = 0; j < 15; j++)
	{
		for (int i = 0; i < 15; i++)
		{
			floorTrans.position_ = { 1.0f * j,0, 1.0f * i };
			wallTrans.position_ = { 1.0f * j,0, 1.0f * i };
			if ((j == 0 || j == 14) || (i == 0 || i == 14))
			{
				Model::SetTransform(hWall_, wallTrans);
				Model::Draw(hWall_);
			}
			Model::SetTransform(hFloor_, floorTrans);
			Model::Draw(hFloor_);
		}
	}
	Model::SetTransform(hPlayer_, transform_);
	Model::Draw(hPlayer_);
}



void Stage::Release()
{
}
