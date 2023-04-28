#pragma once

#include"libs/object.h"
class TmepObject :public Object {
public:
	TmepObject(Scene* sc);
	~TmepObject()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:
	void MouseState();
	std::vector<int>hImages;
	int hImage;
	std::vector<Vec2<float>>pos;
	int loadfilesCount;
	bool keystop;
	int saveCount;
	int mouseWidth;
	int mouseHeight;
	bool mouseKeystop;
	bool HtoW;
	int mouseVol;
};