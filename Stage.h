#pragma once
#include<vector>
#include "Engine/GameObject.h"
#include"Engine/CsvReader.h"

using std::vector;

class Stage :
    public GameObject
{
	vector<vector<int>> stageData_;
	int hFloor_;
	int hWall_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

