#include "scenechanger.h"
#include"scene.h"
#include"farstonescene.h"

#include"../title.h"
#include"../gamescene.h"

Scene* SceneChanger::StartScene(){
	return new FarstOneScene();
}

Scene* SceneChanger::Changer(std::string name){
	if (name == "Title") {
		return new Title();
	}
	else if (name=="Game") {
		return new GameScene();
	}
	MessageBox(NULL, ("作ってないシーンをご指名だ！\nシーン名：" + name).c_str(), "称号獲得『未だ無いシーンを求める者』", MB_ICONERROR | MB_OK);
	assert(false);
	return nullptr;
}
