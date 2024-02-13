#include "Stage.h"
#include"Engine/Model.h"
#include"Engine/Camera.h"
#include"Engine/Input.h"
#include"Engine/CsvReader.h"
#include"Feed.h"

namespace {
	/*const int STAGE_X{ 15 };
	const int STAGE_Y{ 15 };*/
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
}

bool Stage::IsWall(int _x, int _y)
{
	assert(stageData_[_y][_x]>=-1);//_x,_yの配列の位置が配列の外側ならエラー
	if (stageData_[_y][_x]==STAGE_OBJ::WALL)
		return true;
	else
		return false;
}

Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage")
{
	CsvReader csv;
	csv.Load("stage2.csv");

	stageWidth_ = csv.GetWidth();    //１行に何個データがあるか
	stageHeight_ = csv.GetHeight();   //データが何行あるか

	for (int i = 0; i < stageWidth_; i++)
	{
		vector<int> sdata(stageHeight_, 0);//15の配列を0で初期化
		stageData_.push_back(sdata);
	}

	for (int j = 0; j < stageWidth_; j++)
	{
		for (int i = 0; i < stageHeight_; i++)
		{
			stageData_[j][i] = csv.GetValue(i, j);
		}
	}
	Instantiate<Feed>(this);
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

	for (int j = 0; j < stageWidth_; j++)
	{
		for (int i = 0; i < stageHeight_; i++)
		{
			floorTrans.position_ = { (float)i,0, (float)(14-j)};
			wallTrans.position_ = { (float)i,0, (float)(14-j)};
			if (stageData_[j][i] == 1)
			{
				Model::SetTransform(hWall_, wallTrans);
				Model::Draw(hWall_);
			}
			else
			{
				Model::SetTransform(hFloor_, floorTrans);
				Model::Draw(hFloor_);
			}
		}
	}
}



void Stage::Release()
{
	for (int i = 0; i < stageWidth_; i++)
	{
		stageData_[i].clear();
	}
	stageData_.clear();
}
