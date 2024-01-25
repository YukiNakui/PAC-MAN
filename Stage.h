#pragma once
#include "Engine/GameObject.h"
#include"Engine/CsvReader.h"

class Stage :
    public GameObject
{
	CsvReader csv;
	int hFloor_;
	int hWall_;
public:
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

