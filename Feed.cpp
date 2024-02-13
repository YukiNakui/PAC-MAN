#include "Feed.h"
#include"Engine/Model.h"

Feed::Feed(GameObject* parent)
	:GameObject(parent,"Feed"),hModel_(-1)
{
}

void Feed::Initialize()
{
	hModel_ = Model::Load("Model\\Bullet.fbx");
	assert(hModel_ >= 0);
	transform_.scale_ = { transform_.scale_.x / 2.0f,transform_.scale_.y / 2.0f, transform_.scale_.z / 2.0f };
}

void Feed::Update()
{
}

void Feed::Draw()
{
	Model::SetTransform(hModel_,transform_);
	Model::Draw(hModel_);
}

void Feed::Release()
{
}
