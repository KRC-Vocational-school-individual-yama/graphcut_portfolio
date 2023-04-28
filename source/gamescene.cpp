#include "gamescene.h"

#include"libs/scenemanager.h"
#include<DxLib.h>
#include"temp.h"

GameScene::GameScene()
	:keystop(true)
{
	Create<TmepObject>();
}
GameScene::~GameScene(){

}

void GameScene::Update(){
	Scene::Update();
	bool backKey = CheckHitKey(KEY_INPUT_SPACE);
	if (backKey&&!keystop) {
		SceneManager::ChangeScene("Title");
	}
	keystop = backKey;
}

void GameScene::Draw(){
	Scene::Draw();
	printfDx("�����Ȃ��̂�\n�X�y�[�X�L�[��\n�߂��Ă����\n");
}

