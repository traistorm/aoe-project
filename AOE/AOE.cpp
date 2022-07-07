// AOE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Civilizations.h"
#include "Init.h"
#include "Game_Object.h"
#include "Common_Function.h"
using namespace std;
//#include "Manager.h"
//#include "Manager.cpp"
Manager* Manager_Game = NULL;
SDL_Renderer* Renderer = NULL; // Con trỏ của Renderer
SDL_Window* Window = NULL; // Con trỏ của Window
SDL_Event Event; // Event
SDL_Texture* Country_Tech_Texture[8] = { NULL }; // Mảng Texture cho công nghệ các nước, lý do : Các nước sẽ có màu công nghệ là khác nhau
SDL_Texture* Country_Unit_Icon_Texture[8] = { NULL };
SDL_Texture* Country_House_Icon_Texture_Construct_1[8] = { NULL }; // Icon cho các loại nhà, tùy theo nền kiến trúc, có tất cả 4 loại kiến trúc
SDL_Texture* Country_Button_Texture[8] = { NULL };
Country_Unit_Details_Texture Country_Unit_Details_Texture_List[8];
SDL_Surface* Texture_Surface; // Surface chung cho tất cả đối tượng
SDL_Texture* Grass_Texture; // Texture chứa dữ liệu của cỏ
SDL_Texture* Tree_Texture;
SDL_Texture* Berry_Bush_Texture; // Cây ăn quả
SDL_Texture* Villager_Texture; // Texture chứa dữ liệu hình ảnh của Villager;
SDL_Texture* Villager_Standing_Texture; // Texture dân làng lúc đứng
SDL_Texture* Town_Center_1_Texture; // Texture của nhà chủ đời 1
SDL_Texture* Siege_Workshop_Texture;
SDL_Texture* Elephant_Archer_Texture;
SDL_Texture* Infor_Texture;
SDL_Texture* Infor_Source_Texture;
SDL_Texture* Techs_Texture = NULL; // Một Spritesheet chứa các hình ảnh về các công nghệ có thể nâng cấp
SDL_Texture* Hit_Point_Texture; // Texture cho Hit Point , hay còn gọi là thanh máu.
SDL_Texture* Attribute_Object_Texture;
int main(int argc, char* argv[])
{
	bool Running = true;
	Manager_Game = new Manager();
	Manager_Game->Civil_Gaia_List = new Civil(Gaia);
	Manager_Game->Civil_Gaia_List->Set_Unit_Dt();
	Manager_Game->Init_Window_Game();
	Civil* Civil_Player_1;
	Civil_Player_1 = new Civil_Player(Player);
	Civil_Player_1->Pos_in_Civil_List = 0;
	Civil_Player_1->Set_Civil_Index(Country_1);
	Civil_Player_1->Set_Civil_Name(Egyptian);
	Civil_Player_1->Set_Techs();
	Civil_Player_1->Set_Tech_Dt();
	Civil_Player_1->Set_Unit_Dt();
	Civil_Player_1->Set_Button_Dt();
	Civil* Civil_Computer_1;
	Civil_Computer_1 = new Civil_Computer(Computer);
	Civil_Computer_1->Pos_in_Civil_List = 0;
	Civil_Computer_1->Set_Civil_Index(Country_2);
	Civil_Computer_1->Set_Civil_Name(Yamato);
	Civil_Computer_1->Set_Techs();
	Civil_Computer_1->Set_Tech_Dt();
	Civil_Computer_1->Set_Unit_Dt();
	Manager_Game->Civil_Player_List.push_back(Civil_Player_1);
	Manager_Game->Civil_Computer_List.push_back(Civil_Computer_1);
	Manager_Game->Load_Texture();
	Manager_Game->Load_Map_Game();
	Manager_Game->Init_Map_UG();
	Manager_Game->Handle_Event(Running);
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
