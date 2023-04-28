#include "temp.h"

TmepObject::TmepObject(Scene* sc)
	:Object(sc)
	,hImages()
	,pos()
	,loadfilesCount(0)
	,keystop(true)
	,saveCount(0)
	,hImage(-1)
	,mouseWidth(2)
	,mouseHeight(1)
	,mouseKeystop(false)
	,HtoW(false)
	,mouseVol(0)
{}
TmepObject::~TmepObject(){
	
	for (int& aGraph : hImages)
		if (aGraph > 0)
			DeleteGraph(aGraph),
			aGraph = -1;
}
void TmepObject::Init(){
	hImages.clear();
	pos.clear();

}
void TmepObject::Update(){
	if (GetDragFileNum() > 0){
		char path[MAX_PATH];
		GetDragFilePath(path);

		hImage = LoadGraph(path);
		hImages.emplace_back(hImage);

		Vec2<float>p = {0+loadfilesCount*32,0};
		pos.emplace_back(p);

		loadfilesCount++;
	}

	MouseState();

	bool saveKey = CheckHitKey(KEY_INPUT_S);
	bool saveFlag = false;
	if (saveKey && !keystop) {
		saveFlag = true;
	}
	if (saveFlag) {

		int x = mouseWidth;
		int y = mouseHeight;
		int width = 0;
		int height = 0;
		GetGraphSize(hImage, &width, &height);

		int MapMaxSizeX = width;			//全体マップ横サイズ
		int MapMaxSizeY = height;			//全体マップ縦サイズ

		int SaveScreenH = MakeScreen(MapMaxSizeX, MapMaxSizeY, true);	//保存用スクリーン作成

		SetDrawScreen(SaveScreenH);

		for (int i = 0; i < x; i++)
			for (int j = 0; j < y; j++) {
				std::string str = "mario/saveGraph";
				str += std::to_string(saveCount);
				str += ".png";
				DrawGraph(0, 0, hImage, true);
				Vec2<int>p = { width / x,height / y };
				//192 256
				int index = i + j * y;
				SaveDrawScreenToPNG(p.x * i, p.y * j,
									p.x * i + p.x, p.y * j + p.y, str.c_str());
				saveCount++;
			}
		saveFlag = false;
		saveCount = 0;

		SetDrawScreen(DX_SCREEN_BACK);
		DeleteGraph(SaveScreenH);		//保存用スクリーンの後始末
	}
	keystop = saveKey;
}
void TmepObject::Draw(){
	//for (int i = 0; i < hImages.size(); i++) {
	//	DrawGraph(pos.at(i).x,pos.at(i).y,hImages.at(i),false);
	//}
	if(hImage>0)
	DrawGraph(pos.at(0).x, pos.at(0).y, hImage, false);
	printfDx("mouseWidth  =%d\n", mouseWidth);
	printfDx("mouseHeight =%d\n",mouseHeight	);
	printfDx(HtoW?"Width":"Height");

}

void TmepObject::MouseState(){
	bool MouseLeft = GetMouseInput() & MOUSE_INPUT_LEFT;
	bool MouseRight = GetMouseInput() & MOUSE_INPUT_RIGHT;
	bool MouseMid = GetMouseInput() & MOUSE_INPUT_MIDDLE;
	bool allKey = MouseLeft || MouseRight || MouseMid;

	if (MouseLeft && !mouseKeystop) {
		if (HtoW) {
			mouseWidth++;
		}
		else {
			mouseHeight++;
		}
	}

	if (MouseRight && !mouseKeystop) {
		if (HtoW) {
			mouseWidth--;
		}
		else {
			mouseHeight--;
		}
	}
	//if (MouseMid && !mouseKeystop) {
	//
	//}
	mouseVol= GetMouseWheelRotVol();
	if(mouseVol!=0)
	HtoW = mouseVol > 0;


	mouseKeystop = allKey;
}
