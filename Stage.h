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
	bool IsWall(int _x, int _y);//private�ɂ���X�e�[�W�f�[�^�̒��g�𕷂����߂̊֐�
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

