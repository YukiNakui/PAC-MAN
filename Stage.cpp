#include "Stage.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"
#include"Engine/Input.h"
#include"Engine/CsvReader.h"

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
	CsvReader csv;
	csv.Load("stage3.csv");
	int w = csv.GetWidth();    //１行に何個データがあるか
	int h = csv.GetHeight();   //データが何行あるか

	for (int i = 0; i < STAGE_Y; i++)
	{
		vector<int> sdata(STAGE_X, 0);//15の配列を0で初期化
		stageData_.push_back(sdata);
	}

	for (int j = 0; j < STAGE_Y; j++)
	{
		for (int i = 0; i < STAGE_X; i++)
		{
			stageData_[j][i] = csv.GetValue(i, j);
		}
	}
}

void Stage::Initialize()
{
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

	for (int j = 0; j < STAGE_Y; j++)
	{
		for (int i = 0; i < STAGE_X; i++)
		{
			floorTrans.position_ = { (float)j,0, (float)i};
			wallTrans.position_ = { (float)j,0, (float)i};
			if (stageData_[j][i] == 1)
			{
				Model::SetTransform(hWall_, wallTrans);
				Model::Draw(hWall_);
			}
			if (stageData_[j][i] == 0)
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
