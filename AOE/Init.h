#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED
//#define _CRT_SECURE_NO_WARNINGS
//#include "Init.h"
#include "Civilizations.h"
#include "Game_Object.h"
#include "Common_Function.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "vector"
#include <sstream>
#include <stdlib.h>
#include <string>
#include <string.h>
//class Civil;
//class Game_Object;
class Manager;
using namespace std;
class Manager
{
public:
	Manager() {};
	~Manager() {};
	bool Init_Window_Game(); // Khởi tạo cửa sổ Game,...
	bool Load_Map_Game(); // Khởi tạo bản đồ cho Game
	void Load_Texture(); //Load Texture cho từng đơn vị quân
	void Load_Image(Game_Object* Game_Object_Load_Image, int Unit_Type, int Object_Status, int Direction, int Country, int Hit_Point, int Max_Hit_Point, SDL_Rect& Pos_Sor, SDL_Rect& Orth_Pos, SDL_Rect& Iso_Pos, SDL_Rect& Hit_Point_Pos, SDL_Rect& Hit_Point_Pos_Sor);
	void Load_Sprite_Sheet(int Unit_Type, SDL_Rect& Orth_Pos, SDL_Rect& Pos_Sor, SDL_Rect& Orth_Pos_Work, int Direction,
		int Frame_Weight, int Frame_Height, int Number_Frame_Direc, int Time_Next_Sprite, int Last_Time, int Current_Time);
	void Render_List();
	void Load_Tile(int Unit_Type, int Row, int Col, int Weight, int Height, int z, int Map_Layer, int Country, int Country_Name);
	//Load các Tile trong file Map.txt, đồng thời truyên vào Map_List_1 hoặc Map_List_2 các giá trị về Unit_Type, dộ cao, rộng, dài,...
	//int Get_Number_Row_Map(); // Trả về số hàng của Map
	//int Get_Number_Col_Map(); //Trả về số cột của Map
	//int Get_Orth_Tile_Weight(); // Trả về độ rộng của Tile
	//int Get_Orth_Tile_Height(); // Trả về độ dài của Tile
	void Sort_Topological(Game_Object* Sprite);
	void Handle_Event(bool &Running); // Hàm xử lý sự kiện
	void Load_Interfac(); // Load các bảng hiển thị thông tin
	void Draw_Slection(Game_Object* Game_Object_Draw);
	void Load_Test();
	void Init_Map_UG(); // Khởi tạo Map Uniform Grid và đưa các đối tượng vào các ô tương ứng
	//bool Check_Cell_Empty(int Row, int Col, int Layer); // Kiểm tra xem Cell có rỗng hay không, nếu tất cả các phần tử trong Cell có chỉ số -1 hoặc Cell không có phần tử thì trả về true
public:
	int Orth_Tile_Weight = 32; // Chiều rộng của một Tile trong tọa độ Orth
	int Orth_Tile_Height = 32; // Chiều dài của một Tile trong hệ tọa dộ Orth
	int Map_Layer_1[Number_Row_Map][Number_Col_Map] = {  };
	int Map_Layer_2[Number_Row_Map][Number_Col_Map] = {  };
	Cell_Uniform_Grid Map_UG_Layer_1[Number_Row_Map][Number_Col_Map] = {};
	Cell_Uniform_Grid Map_UG_Layer_2[Number_Row_Map][Number_Col_Map] = {};
	Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map] = {};
	vector<Game_Object*> Map_List_1;
	vector<Game_Object*> Map_List_2;
	vector<Game_Object*> Map_List;
	//vector<Game_Object*> Gaia_List;
	vector<Game_Object*> Background_List;
	vector<Game_Object*> Gaia_Civil_Game_Object_List; // Các đối tượng Game trong tự nhiên : Cây cối, voi, hươu,...
	Civil* Civil_Gaia_List = NULL;
	vector<Civil*> Civil_Computer_List;
	vector<Civil*> Civil_Player_List;
	vector<Choose_Object> Choose_Object_Game; // Chứa các đối tượng được chọn trong game
	vector<int> Choose_Button; // Danh sách các button được chọn, ví dụ chọn nông dân, xong chọn "Button Build" rồi chọn tiếp button sang phải, do danh sách dài lên cần chia ra
	stack<int> Sub_Menu; // Một Menu phụ để xử lý trong trò chơi, ví dụ khi nhấn xây nhà rồi nhấn sang trái, cần một Menu để biết khi nào 
	//Tech_Details Manager_Tech[100];
	SDL_Texture* Test_Texture = NULL;
	char* Alphabet = new char;
	TTF_Font* Font = NULL; 
	SDL_Surface* Surface_Font = NULL;
	SDL_Texture* Texture_Font = NULL;
protected:
	SDL_Rect Mouse_Pos_Sor = { 0,0,64,58 };
	SDL_Rect Mouse_Iso_Pos = { 0,0,64,58 };
	SDL_Texture* Mouse_State_Texture = NULL;
	SDL_Rect Button_1 = { 135,605,52,52 };
	SDL_Rect Button_2 = { 135,665,52,52 };
	SDL_Rect Button_3 = { 135,665,52,52 };
	SDL_Rect Button_6 = { 135,665,52,52 };
	SDL_Rect Pos_Sor_Damage_Attribute = {259,0,37,28};
	SDL_Rect Iso_Pos_Damage_Attribute = { 75,605,37,28 };
	SDL_Rect Pos_Sor_Damage_Attribute_Number = { 0,0,37,28 };
	SDL_Rect Iso_Pos_Damage_Attribute_Number = { 110,608,37,28 }; // Số hiển thị lên, ứng với số lượng kiếm
	SDL_Rect Pos_Sor_Armor_Attribute = { 296,0,37,28 };
	SDL_Rect Iso_Pos_Armor_Attribute = { 75,640,37,28 };
	SDL_Rect Pos_Sor_Armor_Attribute_Number = { 0,0,37,28 };
	SDL_Rect Iso_Pos_Armor_Attribute_Number = { 110,643,37,28 };
	SDL_Rect Pos_Sor_Attack_Range_Attribute = {222,0,37,28};
	SDL_Rect Iso_Pos_Attack_Range_Attribute = { 75,675,37,28 };
	SDL_Rect Pos_Sor_Attack_Range_Attribute_Number = { 0,0,37,28 };
	SDL_Rect Iso_Pos_Attack_Range_Attribute_Number = { 110,678,37,28 };
	SDL_Rect Pos_Sor_Unit_Name = { 0,0,0,0 };
	SDL_Rect Iso_Pos_Unit_Name = { 15,605,0,0 };
	SDL_Rect Pos_Sor_Hit_Point_Ratio = { 0,0,0,0 };
	SDL_Rect Iso_Pos_Hit_Point_Ratio = { 15,698,0,0 };
	SDL_Rect Pos_Sor_Country_Name = { 0,0,0,0 };
	SDL_Rect Iso_Pos_Country_Name = { 15,618,0,0 };
	SDL_Rect Pos_Sor_Percent = { 0,0,0,0 };
	SDL_Rect Iso_Pos_Percent = { 102,645,0,0 };
	SDL_Rect Pos_Sor_Clock_Icon = { 333,0,37,28 };
	SDL_Rect Iso_Pos_Clock_Icon = { 70,640,37,28 }; // Biểu tượng hiển thị thời gian Researching hoặc Training
	SDL_Rect Pos_Sor_Amount_Food = { 0,0,0,0 };
	SDL_Rect Iso_Pos_Amount_Food = { 100,2,0,0 };
	SDL_Rect Pos_Sor_Amount_Wood = { 0,0,0,0 };
	SDL_Rect Iso_Pos_Amount_Wood = { 35,2,0,0 };
	SDL_Rect Pos_Sor_Amount_Gold = { 0,0,0,0 };
	SDL_Rect Iso_Pos_Amount_Gold = { 166,2,0,0 };
	SDL_Rect Pos_Sor_Amount_Stone = { 0,0,0,0 };
	SDL_Rect Iso_Pos_Amount_Stone = { 232,2,0,0 };
	SDL_Rect Pos_Sor_Gold = { 111,0,37,28 };
	SDL_Rect Iso_Pos_Gold = { 75,640,37,28 };
	SDL_Rect Pos_Sor_Wood = { 0,0,37,28 };
	SDL_Rect Iso_Pos_Wood = { 75,640,37,28 };
	SDL_Rect Pos_Sor_Stone = { 37,0,37,28 };
	SDL_Rect Iso_Pos_Stone = { 75,640,37,28 };
	SDL_Rect Pos_Sor_Food = { 74,0,37,28 };
	SDL_Rect Iso_Pos_Food = { 75,640,37,28 };
	SDL_Rect Pos_Sor_Number_Unit_Train = {};
	SDL_Rect Iso_Pos_Number_Unit_Train = {};
	SDL_Color Black_Color = { 0,0,0,255 };
	SDL_Color White_Color = { 255,255,255,255 };
	
	int Window_Weight = 1025; // The Weight of window
	int Window_Height = 727; // The Height of window
	int Window_Pos_x = 50; // The x Position of Window
	int Window_Pos_y = 50; // The y Position of Window
	int flag = 0; // Flags Window
	const char* Title = "Traistorm"; // The Name of window
	int Interfac_y_Pos = 600;
	int x_Pos_Click = 0;
	int y_Pos_Click = 0;
	int x_Pos_Mouse_Motion = 0; // Tọa độ chuột hiện tại theo x	
	int y_Pos_Mouse_Motion = 0; // Tọa độ chuột hiện tại theo y
	bool Mouse_Button_Left = false; // Biến xác định trạng thái nút chuột trái, xem nút này có đang được nhấn hay không.
	bool Mouse_Button_Right = false;
	int Tech_Frame_Weight = 52;
	int Tech_Frame_Height = 52;
	int Sprite_Sheet_Tech_Weight = 5252;
	/*SDL_Surface* Texture_Surface; // Surface chung cho tất cả đối tượng
	SDL_Texture* Grass_Texture; // Texture chứa dữ liệu của cỏ
	
	SDL_Texture* Berry_Bush_Texture = NULL; // Cây ăn quả
	SDL_Texture* Villager_Texture = NULL; // Texture chứa dữ liệu hình ảnh của Villager;
	SDL_Texture* Villager_Standing_Texture = NULL; // Texture dân làng lúc đứng*/
	
	// Cần kiểm tra tại sao khái báo Texture ở đây thì lỗi
};
extern Manager* Manager_Game;
#endif // 

