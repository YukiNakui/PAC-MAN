#include "Stage.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"
#include"Engine/Input.h"

const int STAGE_X{ 15 };
const int STAGE_Y{ 15 };

//int stage[STAGE_X][STAGE_Y]
//{
//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
//};

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage")
{
}

void Stage::Initialize()
{
	csv.Load("stage.csv");
	hFloor_ = Model::Load("Model\\Floor.fbx");
	assert(hFloor_ >= 0);
	hWall_ = Model::Load("Model\\Wall.fbx");
	assert(hWall_ >= 0);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Transform floorTrans;
	Transform wallTrans;
	//for (int j = 0; j < 15; j++)
	//{
	//	for (int i = 0; i < 15; i++)
	//	{
	//		floorTrans.position_ = { 1.0f * j,0, 1.0f * i };
	//		wallTrans.position_ = { 1.0f * j,0, 1.0f * i };
	//		if ((j == 0 || j == 14) || (i == 0 || i == 14))
	//		{
	//			Model::SetTransform(hWall_, wallTrans);
	//			Model::Draw(hWall_);
	//		}
	//		Model::SetTransform(hFloor_, floorTrans);
	//		Model::Draw(hFloor_);
	//	}
	//}
	int w = csv.GetWidth();    //１行に何個データがあるか
	int h = csv.GetHeight();   //データが何行あるか
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			int stage = csv.GetValue(j, i);
			floorTrans.position_ = { 1.0f * j,0, 1.0f * i };
			wallTrans.position_ = { 1.0f * j,0, 1.0f * i };
			if (stage == 1)
			{
				Model::SetTransform(hWall_, wallTrans);
				Model::Draw(hWall_);
			}
			if (stage == 0)
			{
				Model::SetTransform(hFloor_, floorTrans);
				Model::Draw(hFloor_);
			}
		}
	}
}



void Stage::Release()
{
}
