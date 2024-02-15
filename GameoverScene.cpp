#include "GameoverScene.h"
#include"Engine/Image.h"
#include"Engine/Input.h"
#include"Engine/SceneManager.h"

GameoverScene::GameoverScene(GameObject* parent)
	:GameObject(parent, "GameoverScene"), hPict_(-1)
{
}

void GameoverScene::Initialize()
{
	hPict_ = Image::Load("GAMEOVER.png");
	assert(hPict_ >= 0);
}

void GameoverScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void GameoverScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

void GameoverScene::Release()
{
}
