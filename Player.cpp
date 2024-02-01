#include "Player.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"
#include"Engine/Input.h"
#include"Engine/Debug.h"
#include"Stage.h"

namespace
{
	const float PLAYER_MOVE_SPEED{ 1.0f };
}

Player::Player(GameObject* parent)
	:GameObject(parent,"Player"),hPlayer_(-1),speed_(PLAYER_MOVE_SPEED),pStage_(nullptr)
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
	pStage_ = (Stage*)FindObject("Stage");//基底クラスから派生クラスへ -> ダウンキャスト
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
	//pos = pos + speed_ * move;
	XMVECTOR posTmp = XMVectorZero();//ゼロベクトルで初期化
	posTmp = pos + speed_ * move;

	int tx, ty;
	tx = (int)(XMVectorGetX(pos) + 0.5);
	ty = pStage_->GetStageWidth() - (int)(XMVectorGetZ(pos) + 0.5); //配列のインデックス
	//仮に配列をmap[][]とする
	//移動先がフロア(STAGE_OBJ::FLOOR => 0)だったら動く
	if (!(pStage_->IsWall(tx,ty))) {
		pos = posTmp;
	}
	/*Debug::Log("(X,Z)=");
	Debug::Log(XMVectorGetX(pos));
	Debug::Log(",");
	Debug::Log(XMVectorGetZ(pos),true);*/
	
	Debug::Log("(iX,iZ)=");
	Debug::Log(tx);
	Debug::Log(",");
	Debug::Log(ty);
	Debug::Log(":");
	Debug::Log(pStage_->IsWall(tx, ty),true);


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
}

void Player::Draw()
{
	Model::SetTransform(hPlayer_, transform_);
	Model::Draw(hPlayer_);
}

void Player::Release()
{
}