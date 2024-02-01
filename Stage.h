#pragma once
#include<vector>
#include "Engine/GameObject.h"
#include"Engine/CsvReader.h"

using std::vector;

enum STAGE_OBJ {
	FLOOR,
	WALL,
};

class Stage :
    public GameObject
{
	vector<vector<int>> stageData_;
	int hFloor_;
	int hWall_;
	int stageWidth_, stageHeight_;
public:
	int GetStageWidth() { return stageWidth_; }
	int GetStageHeight() { return stageHeight_; }
	bool IsWall(int _x, int _y);//privateにあるステージデータの中身を聞くための関数
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Stage(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

