#include "Init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include<Windows.h>
//#include "Game_Object.h"
//class Game_Object;

bool Manager::Init_Window_Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // if init suggess
	{
		
		cout << "Init suggess" << endl;
		Window = SDL_CreateWindow(Title, Window_Pos_x, Window_Pos_y, Window_Weight, Window_Height, SDL_WINDOW_RESIZABLE);
		if (Window != 0) // if Init window suggess
		{
			cout << "Init window suggess" << endl;
			Renderer = SDL_CreateRenderer(Window, -1, 0);
			if (Renderer != 0) // if Init renderer suggess
			{
				cout << "Init Renderer suggess" << endl;
				IMG_Init(IMG_INIT_PNG);
				TTF_Init();
				SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
				SDL_RenderClear(Renderer);
				return true;
			}
			else
			{
				cout << "Renderer fail" << endl;
				return false;
			}
		}
		else
		{
			cout << "Init window fail" << endl;
			return false;
		}
	}
	else
	{
		cout << "Init fail" << endl;
		return false;
	}
	//TTF_Init(); // Khởi tạo TTF để viết chữ
}

bool Manager::Load_Map_Game()
{
	memset(Manager::Map_Layer_1, -1, sizeof(Manager::Map_Layer_1));
	memset(Manager::Map_Layer_2, -1, sizeof(Manager::Map_Layer_2));
	int Row = 0;
	int Col = 0;
	int Tile_Number = 0;
	char Tile = 0;
	string Assign;
	FILE* F_FILE = NULL;
	errno_t Errno;
	Errno = fopen_s(&F_FILE,"Map.txt","r");
	if (Errno == 0)
	{
		cout << "can read file" << endl;
	}
	else
	{
		cout << "Can not read file" << endl;
		return false;
	}
	while (Tile != EOF)
	{
		Tile = fgetc(F_FILE);
		//cout << Tile;
		if (Tile != ' ' && Tile != '\n')
		{
			Assign.push_back(Tile);
			//Col++;
		}
		else if (Tile == ' ' || Tile == '\n')
		{
			stringstream Assign_1(Assign);
			Assign_1 >> Tile_Number;
			Assign.clear();
			
			
			if (Tile_Number == Grass_0)
			{
				Load_Tile(Grass, Row, Col, 66, 34, 0, 1, 0, Gaia_Civil);
			}
			else if (Tile_Number == Tree_0_1)
			{
				//cout << "1";
				Load_Tile(Tree_01, Row, Col, 63, 70, 0, 2, 0, Gaia_Civil);
			}
			else if (Tile_Number == Mine_Gold_0_1)
			{
				//cout << "1";
				Load_Tile(Mine_Gold, Row, Col, 71, 50, 0, 2, 0, Gaia_Civil);
			}
			else if (Tile_Number == Mine_Stone_0_1)
			{
				//cout << "1";
				Load_Tile(Mine_Stone, Row, Col, 79, 43, 0, 2, 0, Gaia_Civil);
			}
			else if (Tile_Number == Berry_Bush_0_1)
			{
				Load_Tile(Berry_Bush, Row, Col, 38, 32, 32, 2, 0, Gaia_Civil);
			}
			else if (Tile_Number == Town_Center_1_1_1)
			{
				Load_Tile(Town_Center, Row, Col, 165, 100, 0, 2, 1, Egyptian); // AOE 1 là 165 và 100, DE là 180 và 117
			}
			else if (Tile_Number == Town_Center_2_1_1)
			{
				Load_Tile(Town_Center, Row, Col, 165, 100, 0, 2, 2, Egyptian); // AOE 1 là 165 và 100, DE là 180 và 117
			}
			else if (Tile_Number == Barracks_2_1_1)
			{
				//cout << "Load Nha BB";
				Load_Tile(Barracks, Row, Col, 183, 126, 0, 2, 2, Egyptian); // Load Tile nhà BB
			}
			/*else if (Tile_Number == Siege_Workshop_1_M_1)
			{
				Load_Tile(Siege_Workshop_1_M_1, Row, Col, 184, 124, 0, 2, 1, Egyptian);
			}
			else if (Tile_Number == Elephant_Archer_1)
			{
				Load_Tile(Elephant_Archer_1, Row, Col, 77, 68, 0, 2, 1, Egyptian);
			}*/
			else if (Tile_Number == Clubman_2)
			{
				Load_Tile(Clubman, Row, Col, 21, 38, 0, 2, 2, Egyptian);
			}
			else if (Tile_Number == Villager_2)
			{
				//cout << Tile_Number << endl;
				//MessageBoxA();
				Load_Tile(Villager, Row, Col, 21, 38, 0, 2, 2, Egyptian);
			}
			if (Tile == ' ')
			{
				Col++;
			}
			else if (Tile == '\n')
			{
				Row++;
				Col = 0;
			}
		}
	}
	for (int i=0; i<Number_Row_Map; i++)
		for (int j = 0; j < Number_Col_Map; j++)
		{
			if (Manager::Map_Layer_1[i][j] == -1)
			{
				Load_Tile(Grass, i, j, 66, 34, 0, 1, 0, Gaia_Civil);
			}
		}
	return true;
}
void Manager::Load_Tile(int Unit_Type, int Row, int Col, int Weight, int Height, int z, int Map_Layer, int Country, int Country_Name)
{
	if (Map_Layer == 1)
	{
		Manager::Map_Layer_1[Row][Col] = Unit_Type;
	}
	else if (Map_Layer == 2)
	{
		Manager::Map_Layer_2[Row][Col] = Unit_Type;
	}
	SDL_Rect Assign_Rect_Sor;
	SDL_Rect Assign_Rect_Orth;
	SDL_Rect Assign_Rect_Iso{};
	Assign_Rect_Orth.x = Orth_Tile_Weight * Col;
	Assign_Rect_Orth.y = Orth_Tile_Height * Row;
	Assign_Rect_Orth.w = Weight;
	Assign_Rect_Orth.h = Height;
	Assign_Rect_Sor.x = 0;
	Assign_Rect_Sor.y = 0;
	Assign_Rect_Sor.w = Weight;
	Assign_Rect_Sor.h = Height;
	Game_Object* Object;
	if (Unit_Type == Tree_01 || Unit_Type == Berry_Bush)
	{
		Object = new Nature_Object(0.66);
		Object->Set(Assign_Rect_Orth, Assign_Rect_Iso, Assign_Rect_Sor, Unit_Type, z, Country, Country_Name, 80, 80);
		Object->Set_Country_Name(Civil_Gaia_List->Get_Civil_Name());
		Object->Resource_Capacity = 5;
		Civil_Gaia_List->Civil_Game_Object_List.push_back(Object);
	}
	else if (Unit_Type == Mine_Gold)
	{
		Object = new Nature_Object(0.9);
		Object->Object_Status = Death;
		Object->Set(Assign_Rect_Orth, Assign_Rect_Iso, Assign_Rect_Sor, Unit_Type, z, Country, Country_Name, 60, 60);
		Object->Resource_Capacity = 50;
		Object->Set_Country_Name(Civil_Gaia_List->Get_Civil_Name());
		Civil_Gaia_List->Civil_Game_Object_List.push_back(Object);
	}
	else if (Unit_Type == Mine_Stone)
	{
		Object = new Nature_Object(0.9);
		Object->Object_Status = Death;
		Object->Set(Assign_Rect_Orth, Assign_Rect_Iso, Assign_Rect_Sor, Unit_Type, z, Country, Country_Name, 60, 60);
		Object->Resource_Capacity = 50;
		Object->Set_Country_Name(Civil_Gaia_List->Get_Civil_Name());
		Civil_Gaia_List->Civil_Game_Object_List.push_back(Object);
	}
	else if (Unit_Type == Town_Center || Unit_Type == Barracks)
	{
		Object = new Building_Object(2.9);
		Object->Set(Assign_Rect_Orth, Assign_Rect_Iso, Assign_Rect_Sor, Unit_Type, z, Country, Country_Name, 170, 170);
		for (int j = 0; j < Civil_Player_List.size(); j++)
		{
			if (Civil_Player_List[j]->Get_Civil_Index() == Country)
			{
				Object->Pos_in_List_Object = Civil_Player_List[j]->Civil_Game_Object_List.size();
				Object->Unit_Type_Control = Player;
				Object->Pos_Control = j;
				Object->Set_Unit_Type_Property(Building);
				Object->Percent_Complete_Build = 100;
				Object->Set_Object_Properties(Civil_Player_List[j]->Unit_Dt);
				Object->Set_Country_Name(Civil_Player_List[j]->Get_Civil_Name());
				Civil_Player_List[j]->Civil_Game_Object_List.push_back(Object);
				if (Unit_Type == Town_Center)
				{
					//cout << Civil_Player_List[j]->Civil_Game_Object_List.size() - 1;
					Civil_Player_List[j]->Pos_Town_Center_List.push_back(Civil_Player_List[j]->Civil_Game_Object_List.size() - 1);
				}
				else if (Unit_Type == Barracks)
				{
					Civil_Player_List[j]->Pos_Barracks_List.push_back(Civil_Player_List[j]->Civil_Game_Object_List.size() - 1);
				}
				Civil_Player_List[j]->Civil_Train_Add_Unit(Unit_Type);
			}	
		}
		for (int j = 0; j < Civil_Computer_List.size(); j++)
		{
			if (Civil_Computer_List[j]->Get_Civil_Index() == Country)
			{
				Object->Pos_in_List_Object = Civil_Computer_List[j]->Civil_Game_Object_List.size();
				Object->Unit_Type_Control = Computer;
				Object->Pos_Control = j;
				Object->Set_Unit_Type_Property(Building);
				Object->Percent_Complete_Build = 100;
				Object->Set_Object_Properties(Civil_Computer_List[j]->Unit_Dt);
				Object->Set_Country_Name(Civil_Computer_List[j]->Get_Civil_Name());
				Civil_Computer_List[j]->Civil_Game_Object_List.push_back(Object);
				if (Unit_Type == Town_Center)
				{
					//cout << Civil_Player_List[j]->Civil_Game_Object_List.size() - 1;
					Civil_Computer_List[j]->Pos_Town_Center_List.push_back(Civil_Computer_List[j]->Civil_Game_Object_List.size() - 1);
				}
				else if (Unit_Type == Barracks)
				{
					//cout << "Load Nha BB";
					Civil_Computer_List[j]->Pos_Barracks_List.push_back(Civil_Computer_List[j]->Civil_Game_Object_List.size() - 1);
				}
				Civil_Computer_List[j]->Civil_Train_Add_Unit(Unit_Type);
			}
		}
	}
	else if (Unit_Type == Grass)
	{
		Object = new Game_Object();
		Object->Set(Assign_Rect_Orth, Assign_Rect_Iso, Assign_Rect_Sor, Unit_Type, z, Country, Country_Name, 30, 30);
		Object->Set_Country_Name(Civil_Gaia_List->Get_Civil_Name());
		Background_List.push_back(Object);
	}
	/*else if (Unit_Type == Elephant_Archer_1)
	{
		Object = new Dynamic_Object(0.96);
		Object->Set(Assign_Rect_Orth, Assign_Rect_Iso, Assign_Rect_Sor, Unit_Type, z, Country, Country_Name, 70, 70);
		for (int j = 0; j < Civil_Player_List.size(); j++)
		{
			Civil_Player_List[j]->Civil_Game_Object_List.push_back(Object);
		}
	}*/
	else if (Unit_Type == Villager)
	{
		//cout << "yes";
		Object = new Villager_Object(0.3, 21, 38);
		Object->Set(Assign_Rect_Orth, Assign_Rect_Iso, Assign_Rect_Sor, Unit_Type, z, Country, Country_Name, 40, 40);
		//cout << Civil_Computer_List.size() << endl;
		for (int j = 0; j < Civil_Player_List.size(); j++)
		{
			//cout << "Yes";
			if (Civil_Player_List[j]->Get_Civil_Index() == Country)
			{
				Object->Unit_Type_Control = Player;
				Object->Pos_Control = j;
				Object->Pos_in_List_Object = Civil_Player_List[j]->Civil_Game_Object_List.size();
				Object->Set_Object_Properties(Civil_Player_List[j]->Unit_Dt);
				Object->Set_Country_Name(Civil_Player_List[j]->Get_Civil_Name());
				
				Object->Set_Unit_Type_Property(Villager_Base);
				Civil_Player_List[j]->Civil_Game_Object_List.push_back(Object);
				Civil_Player_List[j]->Civil_Train_Add_Unit(Unit_Type);
				break;
			}
			//break;
		}
		for (int j = 0; j < Civil_Computer_List.size(); j++)
		{
			//cout << "Yes";
			if (Civil_Computer_List[j]->Get_Civil_Index() == Country)
			{
				Object->Unit_Type_Control = Computer;
				Object->Pos_Control = j;
				Object->Pos_in_List_Object = Civil_Computer_List[j]->Civil_Game_Object_List.size();
				Object->Set_Object_Properties(Civil_Computer_List[j]->Unit_Dt);
				Object->Set_Country_Name(Civil_Computer_List[j]->Get_Civil_Name());
				Object->Set_Unit_Type_Property(Villager_Base);
				Civil_Computer_List[j]->Civil_Game_Object_List.push_back(Object);
				Civil_Computer_List[j]->Civil_Train_Add_Unit(Unit_Type);

				break;
			}
			//break;
		}
	}
	else if (Unit_Type == Clubman)
	{
		Object = new Dynamic_Object(0.3);
		Object->Set(Assign_Rect_Orth, Assign_Rect_Iso, Assign_Rect_Sor, Unit_Type, z, Country, Country_Name, 40, 40);
		//cout << Civil_Computer_List.size() << endl;
		for (int j = 0; j < Civil_Player_List.size(); j++)
		{
			//cout << "Yes";
			if (Civil_Player_List[j]->Get_Civil_Index() == Country)
			{
				Object->Unit_Type_Control = Player;
				Object->Pos_Control = j;
				Object->Pos_in_List_Object = Civil_Player_List[j]->Civil_Game_Object_List.size();
				Object->Set_Object_Properties(Civil_Player_List[j]->Unit_Dt);
				Object->Set_Country_Name(Civil_Player_List[j]->Get_Civil_Name());
				Object->Set_Unit_Type_Property(Base_Melee);
				Civil_Player_List[j]->Civil_Game_Object_List.push_back(Object);
				Civil_Player_List[j]->Civil_Train_Add_Unit(Unit_Type);
				break;
			}
			//break;
		}
		for (int j = 0; j < Civil_Computer_List.size(); j++)
		{
			//cout << "Yes";
			if (Civil_Computer_List[j]->Get_Civil_Index() == Country)
			{
				Object->Unit_Type_Control = Computer;
				Object->Pos_Control = j;
				Object->Pos_in_List_Object = Civil_Computer_List[j]->Civil_Game_Object_List.size();
				Object->Set_Object_Properties(Civil_Computer_List[j]->Unit_Dt);
				Object->Set_Country_Name(Civil_Computer_List[j]->Get_Civil_Name());
				Object->Set_Unit_Type_Property(Base_Melee);
				Civil_Computer_List[j]->Civil_Game_Object_List.push_back(Object);
				Civil_Computer_List[j]->Civil_Train_Add_Unit(Unit_Type);

				break;
			}
			//break;
		}
	}
	else
	{
		Object = new Game_Object();
	}
	// Object->Set(Assign_Rect_Orth, Assign_Rect_Iso, Assign_Rect_Sor, Unit_Type, z);
	
}

void Manager::Load_Texture()
{
	Texture_Surface = IMG_Load("Grass.gif");
	Grass_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Tree.gif");
	Tree_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Berry_Bush.gif");
	Berry_Bush_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Town_Center_1.gif");
	Town_Center_1_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Siege_Workshop.gif");
	Siege_Workshop_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	// Load các thông số cho Villager, bao gồm các Texture Standing, Moving, Attacking, Working và các thông số về chiều rộng, chiều cao của Texture tương ứng ,...
	Texture_Surface = IMG_Load("Villager_Standing.png");
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Standing_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Standing_Frame_Weight = 21;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Standing_Frame_Height = 38;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Number_Standing_Direction_Frame = 6;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Standing_Next_Frame = 500;
	Texture_Surface = IMG_Load("Villager_Moving.png");
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Moving_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Moving_Frame_Weight = 40;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Moving_Frame_Height = 42;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Number_Moving_Direction_Frame = 15;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Moving_Next_Frame = 1;
	Texture_Surface = IMG_Load("Villager_Attacking.png");
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Attacking_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Attacking_Frame_Weight = 75;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Attacking_Frame_Height = 72;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Number_Attacking_Direction_Frame = 15;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Villager].Attacking_Next_Frame = 15;
	Texture_Surface = IMG_Load("Villager_2_Standing.png");
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Standing_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Standing_Frame_Weight = 21;
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Standing_Frame_Height = 38;
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Number_Standing_Direction_Frame = 6;
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Standing_Next_Frame = 500;
	//
	
	Texture_Surface = IMG_Load("Villager_2_Death.png");
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Death_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Death_Frame_Weight = 88;
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Death_Frame_Height = 56;
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Number_Death_Direction_Frame = 10;
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Death_Next_Frame = 50;
	//
	Texture_Surface = IMG_Load("Villager_2_Dead.png");
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Dead_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Dead_Frame_Weight = 89;
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Dead_Frame_Height = 40;
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Number_Dead_Direction_Frame = 6;
	Country_Unit_Details_Texture_List[2].Unit_Dt_Texture[Villager].Dead_Next_Frame = 500;
	//
	Texture_Surface = IMG_Load("Woodcutter_1_Work.png");
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Working_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Working_Frame_Weight = 53;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Working_Frame_Height = 65;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Number_Working_Direction_Frame = 11;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Working_Next_Frame = 20;
	//
	Texture_Surface = IMG_Load("Woodcutter_1_Walk.png");
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Moving_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Moving_Frame_Weight = 36;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Moving_Frame_Height = 44;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Number_Moving_Direction_Frame = 15;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Moving_Next_Frame = 20;
	//
	Texture_Surface = IMG_Load("Woodcutter_1_Carry_Lumber.png");
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Carry_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Carry_Frame_Weight = 37;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Carry_Frame_Height = 40;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Number_Carry_Direction_Frame = 15;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Carry_Next_Frame = 20;
	//
	Texture_Surface = IMG_Load("Woodcutter_1_Standing.png");
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Standing_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Standing_Frame_Weight = 44;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Standing_Frame_Height = 45;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Number_Standing_Direction_Frame = 6;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Woodcutter].Standing_Next_Frame = 20;
	//
	Texture_Surface = IMG_Load("Tree_01.gif");
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Standing_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Standing_Frame_Weight = 63;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Standing_Frame_Height = 70;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Number_Standing_Direction_Frame = 1;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Standing_Next_Frame = 0;
	//
	Texture_Surface = IMG_Load("Tree_Dead.png");
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Death_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Death_Frame_Weight = 56;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Death_Frame_Height = 37;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Number_Death_Direction_Frame = 1;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Death_Next_Frame = 20;
	//
	Texture_Surface = IMG_Load("Tree_Stump.png"); // Lúc này cây đã biến mất (Chỉ còn gôc cây)
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Dead_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Dead_Frame_Weight = 39;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Dead_Frame_Height = 28;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Number_Dead_Direction_Frame = 1;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Tree_01].Dead_Next_Frame = 20;
	//
	Texture_Surface = IMG_Load("Mine_Gold.png"); // Mỏ vàng
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Mine_Gold].Death_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Mine_Gold].Death_Frame_Weight = 71;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Mine_Gold].Death_Frame_Height = 50;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Mine_Gold].Number_Death_Direction_Frame = 1;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Mine_Gold].Death_Next_Frame = 20;
	//
	Texture_Surface = IMG_Load("Mine_Stone.png"); // Mỏ đá
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Mine_Stone].Death_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Mine_Stone].Death_Frame_Weight = 79;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Mine_Stone].Death_Frame_Height = 43;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Mine_Stone].Number_Death_Direction_Frame = 1;
	Country_Unit_Details_Texture_List[0].Unit_Dt_Texture[Mine_Stone].Death_Next_Frame = 20;
	//
	Texture_Surface = IMG_Load("Builder.png"); // Load hình ảnh nông dân xây nhà
	//Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Builder]
	//
	Texture_Surface = IMG_Load("Gold_Miner_Walk.png");
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Moving_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Moving_Frame_Weight = 37;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Moving_Frame_Height = 40;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Number_Moving_Direction_Frame = 15;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Moving_Next_Frame = 20;
	//
	Texture_Surface = IMG_Load("Gold_Miner_Standing.png");
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Standing_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Standing_Frame_Weight = 37;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Standing_Frame_Height = 40;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Number_Standing_Direction_Frame = 15;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Standing_Next_Frame = 20;
	//
	Texture_Surface = IMG_Load("Gold_Miner_Carry.png");
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Carry_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Carry_Frame_Weight = 37;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Carry_Frame_Height = 40;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Number_Carry_Direction_Frame = 15;
	Country_Unit_Details_Texture_List[1].Unit_Dt_Texture[Gold_Miner].Carry_Next_Frame = 20;
	//
	// Function load thông tin về các bức ảnh ở các trạng thái của các đối tượng
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_Gaia, Berry_Bush, "apple.gif", 1, 50, 0, 0, "Stone_Miner_Walking.png", 75, 20, 24, 19, "Stone_Miner_Carry.png", 75, 20, 15, 21, "Stone_Miner_Working.png", 65, 20, 29, 35, "Stone_Miner_Attacking.png", 75, 50, 20, 20, "Mine_Gold.png", 7, 200, 35, 20, "Stone_Miner_Dead.png", 1, 20, 50, 20);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_1, Builder, "Villager_1_Standing.png", 30, 50, 16, 34, "Builder_1_Walk.png", 75, 20, 24, 34, "Stone_Miner_Carry.png", 75, 20, 15, 33, "Builder_1_Work.png", 80, 20, 29, 48, "Villager_1_Attacking.png", 75, 50, 20, 20, "Villager_1_Death.png", 50, 20, 51, 45, "Villager_1_Dead.png", 30, 20, 50, 20);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_1, Stone_Miner, "Stone_Miner_Standing.png", 30, 50, 16, 34, "Stone_Miner_Walking.png", 75, 20, 24, 34, "Stone_Miner_Carry.png", 75, 20, 15, 33, "Stone_Miner_Working.png", 65, 20, 29, 48, "Villager_1_Attacking.png", 75, 50, 20, 20, "Stone_Miner_Death.png", 50, 20, 51, 45, "Stone_Miner_Dead.png", 30, 20, 50, 20);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_Gaia, Mine_Stone, "Mine_Stone.png", 30, 50, 16, 17, "Stone_Miner_Walking.png", 75, 20, 24, 19, "Stone_Miner_Carry.png", 75, 20, 15, 21, "Stone_Miner_Working.png", 65, 20, 29, 35, "Villager_1_Attacking.png", 75, 50, 20, 20, "Mine_Stone.png", 7, 200, 45, 20, "Stone_Miner_Dead.png", 1, 20, 50, 20);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_Gaia, Mine_Gold, "Stone_Miner_Standing.png", 30, 50, 16, 17, "Stone_Miner_Walking.png", 75, 20, 24, 19, "Stone_Miner_Carry.png", 75, 20, 15, 21, "Stone_Miner_Working.png", 65, 20, 29, 35, "Stone_Miner_Attacking.png", 75, 50, 20, 20, "Mine_Gold.png", 7, 200, 35, 20, "Stone_Miner_Dead.png", 1, 20, 50, 20);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_Gaia, Tree_01, "Tree_01.gif", 1, 50, 32, 57, "Stone_Miner_Walking.png", 75, 20, 24, 19, "Stone_Miner_Carry.png", 75, 20, 15, 21, "Stone_Miner_Working.png", 65, 20, 29, 35, "Stone_Miner_Attacking.png", 75, 50, 20, 20, "Tree_Dead.png", 1, 200, 25, 20, "Tree_Stump.png", 1, 20, 15, 10);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_1, Town_Center, "Town_Center_1_1_1.gif", 1, 50, 85, 20, "Stone_Miner_Walking.png", 75, 20, 24, 19, "Stone_Miner_Carry.png", 75, 20, 15, 21, "Stone_Miner_Working.png", 65, 20, 29, 35, "Stone_Miner_Attacking.png", 75, 50, 20, 20, "Stone_Miner_Death.png", 50, 20, 51, 31, "Stone_Miner_Dead.png", 30, 20, 50, 20);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_2, Town_Center, "Town_Center_1_1_1.gif", 1, 50, 85, 20, "Stone_Miner_Walking.png", 75, 20, 24, 19, "Stone_Miner_Carry.png", 75, 20, 15, 21, "Stone_Miner_Working.png", 65, 20, 29, 35, "Stone_Miner_Attacking.png", 75, 50, 20, 20, "Stone_Miner_Death.png", 50, 20, 51, 31, "Stone_Miner_Dead.png", 30, 20, 50, 20);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_1, Gold_Miner, "Stone_Miner_Standing.png", 30, 50, 16, 34, "Stone_Miner_Walking.png", 75, 20, 24, 34, "Gold_Miner_Carry.png", 75, 20, 15, 33, "Stone_Miner_Working.png", 65, 20, 29, 48, "Gold_Miner_Attacking.png", 75, 50, 20, 20, "Stone_Miner_Death.png", 50, 20, 51, 45, "Stone_Miner_Dead.png", 30, 20, 50, 20);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_2, Villager, "Villager_2_Standing.png", 30, 50, 11, 33, "Villager_2_Walk.png", 75, 20, 20, 35, "Villager_2_Carry.png", 75, 20, 0, 0, "Villager_2_Working.png", 75, 50, 0, 0, "Villager_2_Attacking.png", 75, 25, 48, 45, "Villager_2_Death.png", 50, 50, 39, 27, "Villager_2_Dead.png", 30, 1000, 40, 19);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_1, Villager, "Villager_1_Standing.png", 30, 50, 11, 33, "Villager_1_Moving.png", 75, 20, 20, 35, "Villager_1_Carry.png", 75, 20, 0, 0, "Villager_1_Working.png", 75, 50, 0, 0, "Villager_1_Attacking.png", 75, 25, 48, 45, "Villager_1_Death.png", 50, 50, 39, 27, "Villager_1_Dead.png", 30, 1000, 40, 19);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_2, Clubman, "Clubman_2_Standing.png", 30, 50, 20, 36, "Clubman_2_Walking.png", 75, 20, 20, 35, "Clubman_2_Carry.png", 75, 20, 0, 0, "Clubman_2_Working.png", 75, 50, 0, 0, "Clubman_2_Attacking.png", 75, 25, 40, 47, "Clubman_2_Death.png", 50, 50, 55, 43, "Clubman_2_Dead.png", 30, 1000, 55, 28);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_1, Clubman, "Clubman_1_Standing.png", 30, 50, 20, 36, "Clubman_1_Walking.png", 75, 20, 20, 35, "Clubman_1_Carry.png", 75, 20, 0, 0, "Clubman_1_Working.png", 75, 50, 0, 0, "Clubman_1_Attacking.png", 75, 25, 40, 47, "Clubman_1_Death.png", 50, 50, 55, 43, "Clubman_1_Dead.png", 30, 1000, 55, 28);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_2, Barracks, "Barrack_2_1_1.gif", 1, 50, 90, 30, "Stone_Miner_Walking.png", 75, 20, 24, 19, "Stone_Miner_Carry.png", 75, 20, 15, 21, "Stone_Miner_Working.png", 65, 20, 29, 35, "Stone_Miner_Attacking.png", 75, 50, 20, 20, "Stone_Miner_Death.png", 50, 20, 51, 31, "Stone_Miner_Dead.png", 30, 20, 50, 20);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_1, Barracks, "Barrack_1_1_1.gif", 1, 50, 90, 30, "Stone_Miner_Walking.png", 75, 20, 24, 19, "Stone_Miner_Carry.png", 75, 20, 15, 21, "Stone_Miner_Working.png", 65, 20, 29, 35, "Stone_Miner_Attacking.png", 75, 50, 20, 20, "Stone_Miner_Death.png", 50, 20, 51, 31, "Stone_Miner_Dead.png", 30, 20, 50, 20);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_1, House, "House_1.gif", 1, 50, 50, 5, "Stone_Miner_Walking.png", 75, 20, 24, 19, "Stone_Miner_Carry.png", 75, 20, 15, 21, "Stone_Miner_Working.png", 65, 20, 29, 35, "Stone_Miner_Attacking.png", 75, 50, 20, 20, "Stone_Miner_Death.png", 50, 20, 51, 31, "Stone_Miner_Dead.png", 30, 20, 50, 20);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_1, Build_House, "Build_House.png", 4, 50, 50, 0, "Stone_Miner_Walking.png", 75, 20, 24, 19, "Stone_Miner_Carry.png", 75, 20, 15, 21, "Stone_Miner_Working.png", 65, 20, 29, 35, "Stone_Miner_Attacking.png", 75, 50, 20, 20, "Stone_Miner_Death.png", 50, 20, 51, 31, "Stone_Miner_Dead.png", 30, 20, 50, 20);
	Load_and_Get_infor_image(Country_Unit_Details_Texture_List, Country_1, Build_3_3, "Build_3_3.png", 4, 50, 90, 40, "Stone_Miner_Walking.png", 75, 20, 24, 19, "Stone_Miner_Carry.png", 75, 20, 15, 21, "Stone_Miner_Working.png", 65, 20, 29, 35, "Stone_Miner_Attacking.png", 75, 50, 20, 20, "Stone_Miner_Death.png", 50, 20, 51, 31, "Stone_Miner_Dead.png", 30, 20, 50, 20);



	//
	Texture_Surface = IMG_Load("Elephant_Archer.gif");
	Elephant_Archer_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Infor.gif");
	Infor_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Infor_Source.gif");
	Infor_Source_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Techs.bmp");
	//Test_Texture = IMG_Load("Techs.bmp");
	if (Texture_Surface == NULL)
	{
		printf("Oh My Goodness, an error : %s", IMG_GetError());

	}
	Country_Tech_Texture[Country_1] = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Unit_Icon_Country_0.png");
	Country_Unit_Icon_Texture[Country_Gaia] = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Unit_Icon_Country_1.png");
	Country_Unit_Icon_Texture[Country_1] = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Unit_Icon_Country_2.png");
	Country_Unit_Icon_Texture[Country_2] = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Button.png");
	Country_Button_Texture[Country_1] = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Techs.png");
	Test_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Mouse_State.png");
	Texture_Surface = IMG_Load("House_Icon_Construct_1_1.png");
	Country_House_Icon_Texture_Construct_1[Country_1] = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("House_Icon_Construct_1_2.png");
	Country_House_Icon_Texture_Construct_1[Country_2] = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Mouse_State.png");
	Mouse_State_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Attribute_Object.png");
	Attribute_Object_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	Texture_Surface = IMG_Load("Hit_Point.png");
	Hit_Point_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	//Texture_Font=TTF_OpenFont("Arival",10)
	SDL_FreeSurface(Texture_Surface);
}
void Manager::Load_Image(Game_Object* Game_Object_Load_Image, int Unit_Type, int Object_Status, int Direction, int Country, int Hit_Point, int Max_Hit_Point, SDL_Rect& Pos_Sor, SDL_Rect& Orth_Pos, SDL_Rect& Iso_Pos, SDL_Rect& Hit_Point_Pos, SDL_Rect& Hit_Point_Pos_Sor)
{
	/* Đối tượng Game_Object sẽ có function Load_to_Screen và truyền vào hàm này thông qua biến toàn cục Manager_Game,
	Sau đó biến toàn cục sẽ tham chiếu tới hàm này để tùy thuộc vào loại đối tượng để load hình ảnh tương ứng,
	Nhưng điều đáng tiếc ở đây là Function này sẽ báo lỗi chưa cấp phát bộ nhớ con trỏ khi dùng những Texture được khai báo bên trong Class Unit,
	Sau nhiều ngày nghiên cứu và tìm hiểu, tôi vẫn chưa tìm được lỗi này và đã dường như đổ lỗi cho trình biên dịch,
	nhưng sau đó tôi tìm ra rằng biến Static chỉ có phạm vi trong một file, nghĩa là Manager_Game chỉ có giá trị đối với class Manager_Game vì nó khai báo trong file Init.h,
	và Manager_Game là một biến staic lên tôi đã gặp phải lỗi này, tôi đã tình cờ tìm ra nó trong một buổi tối khá giá lạnh,
	Cách giải quyết tôi đã tìm ra ngay sau khi biết nguyên nhân lỗi, dễ nhất là khai báo Extern để phạm vi nó là toàn chương trình, cách thứ 2 đó chính là thay vì dùng Manager_Game để tham chiếu hàm,
	Tôi có thê tạo một Function để duyệt qua các Game Object để lấy ra Unit_Type của nó rồi load tương ứng, như vậy đỡ phải dùng Manager_Game !
	*/
	//if (Unit_Type == Villager_2)
		//cout << "yes";
	//Convert_Object(Game_Object_Load_Image, Iso_Pos, Orth_Pos, Orth_Pos.w, Orth_Pos.h);
	int Row = Game_Object_Load_Image->Get_Orth_Pos().y / Orth_Tile_Height;
	int Col = Game_Object_Load_Image->Get_Orth_Pos().x / Orth_Tile_Weight;
	bool Check = false;
	if (!Civil_Player_List.empty())
	{
		if (Civil_Player_List[0]->Map_Explore[Row][Col])
		{
			Check = true;
		}
	}
	if (Game_Object_Load_Image->Unit_Type_Control == Player || Check)
	{
		if (Unit_Type == Villager || Unit_Type == Villager_2 || Unit_Type == Woodcutter || Unit_Type == Tree_01 || Unit_Type == Mine_Gold || Unit_Type == Mine_Stone ||
			Unit_Type == Gold_Miner || Unit_Type == Stone_Miner || Unit_Type == Town_Center || Unit_Type == Barracks || Unit_Type == Clubman || Unit_Type == Builder || Unit_Type == House)
		{
			//Convert_Object(Game_Object_Load_Image, Iso_Pos, Orth_Pos, Orth_Pos.w, Orth_Pos.h);
			if (Unit_Type == Town_Center)
			{
				//cout << Game_Object_Load_Image->Get_Unit_Type_Property() << endl;f
			}
			//cout << (((double)Hit_Point / Max_Hit_Point)) * 26 << endl;
			int Hit_Point_Level = (int)(26 - ((double)Hit_Point / Max_Hit_Point) * 26) * Hit_Point_Pos_Sor.w; // 26 là kích thước của một Sprite Hit Point
			Hit_Point_Pos_Sor.x = Hit_Point_Level;
			//cout << Hit_Point_Level << endl;
			Hit_Point_Pos.x = Iso_Pos.x + (Iso_Pos.w - Hit_Point_Pos.w) / 2;
			Hit_Point_Pos.y = Iso_Pos.y - 20;
			if (Country == Country_1)
			{
				//cout << "Chinh no do" << endl;
				//cout << Hit_Point << " " << Max_Hit_Point << endl;
				//cout << Hit_Point_Level << endl;
			}
			if (Game_Object_Load_Image->Get_Unit_Type_Property() == Building && Game_Object_Load_Image->Percent_Complete_Build < 100)
			{
				//cout << "yes";
				switch (Game_Object_Load_Image->Get_Unit_Type())
				{
				case House:
				{
					SDL_RenderCopy(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Build_House].Standing_Texture, &Pos_Sor, &Iso_Pos);
					break;
				}
				case Barracks:
				{
					SDL_RenderCopy(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Build_3_3].Standing_Texture, &Pos_Sor, &Iso_Pos);
					break;
				}
				default:
					break;
				}

				return;
			}
			if (Direction == Direc_E || Direction == Direc_E_N || Direction == Direc_E_S)
			{
				switch (Object_Status)
				{
				case Standing:
				{
					//cout << "yes";
					SDL_RenderCopyEx(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Standing_Texture, &Pos_Sor, &Iso_Pos, NULL, NULL, SDL_FLIP_HORIZONTAL);
					break;
				}
				case Carry:
				{
					SDL_RenderCopyEx(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Carry_Texture, &Pos_Sor, &Iso_Pos, NULL, NULL, SDL_FLIP_HORIZONTAL);
					break;
				}
				case Moving:
				{
					//cout << "ys";
					SDL_RenderCopyEx(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Moving_Texture, &Pos_Sor, &Iso_Pos, NULL, NULL, SDL_FLIP_HORIZONTAL);
					break;
				}
				case Attacking:
				{
					SDL_RenderCopyEx(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Attacking_Texture, &Pos_Sor, &Iso_Pos, NULL, NULL, SDL_FLIP_HORIZONTAL);
					break;
				}
				case Working:
				{
					//cout << "yes";
					SDL_RenderCopyEx(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Working_Texture, &Pos_Sor, &Iso_Pos, NULL, NULL, SDL_FLIP_HORIZONTAL);
					break;
				}
				case Death:
				{
					//cout << "yes";
					SDL_RenderCopyEx(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Death_Texture, &Pos_Sor, &Iso_Pos, NULL, NULL, SDL_FLIP_HORIZONTAL);
					break;
				}
				case Dead:
				{
					SDL_RenderCopyEx(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Dead_Texture, &Pos_Sor, &Iso_Pos, NULL, NULL, SDL_FLIP_HORIZONTAL);
					break;
				}
				}
			}
			else
			{
				switch (Object_Status)
				{
				case Standing:
				{
					//cout << "yes";
					SDL_RenderCopy(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Standing_Texture, &Pos_Sor, &Iso_Pos);
					break;
				}
				case Carry:
				{
					SDL_RenderCopy(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Carry_Texture, &Pos_Sor, &Iso_Pos);
					break;
				}
				case Moving:
				{
					//cout << "ys";

					SDL_RenderCopy(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Moving_Texture, &Pos_Sor, &Iso_Pos);
					break;
				}
				case Attacking:
				{
					SDL_RenderCopy(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Attacking_Texture, &Pos_Sor, &Iso_Pos);
					break;
				}
				case Working:
				{
					//cout << "yes";
					SDL_RenderCopy(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Working_Texture, &Pos_Sor, &Iso_Pos);
					break;
				}
				case Death:
				{
					//cout << "yes";
					SDL_RenderCopy(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Death_Texture, &Pos_Sor, &Iso_Pos);
					break;
				}
				case Dead:
				{
					SDL_RenderCopy(Renderer, Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Dead_Texture, &Pos_Sor, &Iso_Pos);
					break;
				}
				}
			}
		}


		if (Unit_Type == Grass)
		{
			SDL_RenderCopy(Renderer, Grass_Texture, &Pos_Sor, &Iso_Pos);
		}
		/*else if (Unit_Type == Tree)
		{
			SDL_RenderCopy(Renderer, Tree_Texture, &Pos_Sor, &Iso_Pos);
		}*/
		else if (Unit_Type == Berry_Bush)
		{
			SDL_RenderCopy(Renderer, Berry_Bush_Texture, &Pos_Sor, &Iso_Pos);
		}
		/*else if (Unit_Type == Town_Center_1_M_1)
		{
			SDL_RenderCopy(Renderer, Town_Center_1_Texture, &Pos_Sor, &Iso_Pos);
		}*/
		else if (Unit_Type == Siege_Workshop_1_M_1)
		{
			SDL_RenderCopy(Renderer, Siege_Workshop_Texture, &Pos_Sor, &Iso_Pos);
		}
		else if (Unit_Type == Elephant_Archer_1)
		{
			//cout << " In this";
			SDL_RenderCopy(Renderer, Elephant_Archer_Texture, &Pos_Sor, &Iso_Pos);
		}
		/*else if (Unit_Type == Villager)
		{
			//cout << " In this";
			SDL_RenderCopy(Renderer, Villager_Standing_Texture, &Pos_Sor, &Iso_Pos);
		}*/
		SDL_RenderCopy(Renderer, Hit_Point_Texture, &Hit_Point_Pos_Sor, &Hit_Point_Pos);
	}
	
}

void Manager::Load_Sprite_Sheet(int Unit_Type, SDL_Rect& Orth_Pos, SDL_Rect& Pos_Sor, SDL_Rect& Orth_Pos_Work, int Direction, int Frame_Weight, int Frame_Height, int Number_Frame_Direc, int Time_Next_Sprite, int Last_Time, int Current_Time)
{

}

void Manager::Render_List()
{
	SDL_Rect Orth_Pos_A;
	SDL_Rect Pos_Sor_A;
	SDL_Rect Orth_Pos_B;
	SDL_Rect Pos_Sor_B;
	//cout << Map_List_2.size();
	Map_List.clear();
	Map_List_1.clear();
	Map_List_2.clear();
	//cout << "Size : " << Map_UG_Layer_2[3][5].List_Object_in_Cell.size() << endl;
	//cout << "Khoang 1" << endl;
	for (int i = 0; i < Civil_Player_List.size(); i++)
	{
		for (int j = 0; j < Civil_Player_List[i]->Civil_Game_Object_List.size(); j++)
		{
			for (int k = 0; k < Civil_Player_List[i]->Civil_Game_Object_List[j]->List_Cell_Contain_Object.size(); k++)
			{
				int row_Ex = Civil_Player_List[i]->Civil_Game_Object_List[j]->List_Cell_Contain_Object[k].Row;
				int col_Ex = Civil_Player_List[i]->Civil_Game_Object_List[j]->List_Cell_Contain_Object[k].Col;
				
				int Radius = 0;
				Radius = Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Search_Radius();
				Radius = 5;
				
				
				for (int row_Radius = 0; row_Radius < Radius; row_Radius++)
				{
					for (int col_Radius = 0; col_Radius < Radius; col_Radius++)
					{
						if (row_Ex - row_Radius >= 0 && col_Ex - col_Radius >= 0)
						{
							Civil_Player_List[i]->Map_Explore[row_Ex - row_Radius][col_Ex - col_Radius] = true;
						}
						if (row_Ex + row_Radius <= 50 && col_Ex + col_Radius <= 50)
						{
							Civil_Player_List[i]->Map_Explore[row_Ex + row_Radius][col_Ex + col_Radius] = true;
						}
						if (row_Ex - row_Radius >= 0 && col_Ex + col_Radius <= 50)
						{
							Civil_Player_List[i]->Map_Explore[row_Ex - row_Radius][col_Ex + col_Radius] = true;
						}
						if (row_Ex + row_Radius <= 50 && col_Ex - col_Radius >= 0)
						{
							Civil_Player_List[i]->Map_Explore[row_Ex + row_Radius][col_Ex - col_Radius] = true;
						}
					}
				}
				
			}
			
			if (Civil_Player_List[i]->Civil_Game_Object_List[j]->Alive)
			{
				Civil_Player_List[i]->Civil_Game_Object_List[j]->Current_Time_Attack = SDL_GetTicks();
				Civil_Player_List[i]->Civil_Game_Object_List[j]->Current_Time_Work = SDL_GetTicks();
				Civil_Player_List[i]->Civil_Game_Object_List[j]->Research_Tech(Civil_Player_List[i]->Tech_Dt, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List);
				Civil_Player_List[i]->Civil_Game_Object_List[j]->Train_Unit(Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Unit_Type(), Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List);
				//cout << Civil_Player_List[i]->Civil_Game_Object_List.size();
				//cout << Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Unit_Type() << endl;
				//cout << "yes";
				if (Civil_Player_List[i]->Civil_Game_Object_List[j]->Object_Status == Moving || Civil_Player_List[i]->Civil_Game_Object_List[j]->Object_Status == Carry)
				{
					//cout << "yes";
					//cout << "Move";
					Civil_Player_List[i]->Civil_Game_Object_List[j]->Move(Civil_Player_List[i]->Unit_Dt, Civil_Player_List[i]->Get_Civil_Index(), Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click,
						Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, j);
				}
				//cout << "x";
				Civil_Player_List[i]->Civil_Game_Object_List[j]->Attack(Civil_Player_List[i]->Unit_Dt, Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Country(), Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click, Civil_Computer_List, Civil_Player_List, j);
				if (Civil_Player_List[i]->Civil_Game_Object_List[j]->Object_Status == Working || Civil_Player_List[i]->Civil_Game_Object_List[j]->Moving_To_Work || Civil_Player_List[i]->Civil_Game_Object_List[j]->Going_to_return_resource) // Nếu đối tượng có khả năng làm việc
				{
					//cout << "YWES";
					Civil_Player_List[i]->Civil_Game_Object_List[j]->Work(Civil_Player_List[i]->Unit_Dt, Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Country(), Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click,
						Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, j);
					if (Civil_Player_List[i]->Civil_Game_Object_List[j]->Current_Time_Work - Civil_Player_List[i]->Civil_Game_Object_List[j]->Last_Time_Work >= 1000 && !Civil_Player_List[i]->Civil_Game_Object_List[j]->Moving_To_Work)
					{
						// Giải thích ý nghĩa số 1500 : Số đó được căn để cho cân xứng với sprite, tức chỉ khi rìu được vung xuống dưới thì cây mới mất máu thôi, tuy nhiên ó khó có thể chuẩn vì còn phụ thuộc vào tốc độ vòng lặp
						// Một ý tưởng đó là chỉ khi nào hình ảnh ứng với Frame cuối của một hướng, cây mới mất máu !
						Civil_Player_List[i]->Civil_Game_Object_List[j]->Last_Time_Work = Civil_Player_List[i]->Civil_Game_Object_List[j]->Current_Time_Work;
						if (Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Unit_Type() == Builder)
						{
							int Hit_Point_Value_Add = 0;
							cout << Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Unit_Type_Build();
							Hit_Point_Value_Add = Civil_Player_List[i]->Unit_Dt[Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Unit_Type_Build()].Hit_Point / 20;
							//cout << Hit_Point_Value_Add;
							Civil_Player_List[i]->Civil_Game_Object_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Object_Work]->Add_Hit_Point(Hit_Point_Value_Add);
							Civil_Player_List[i]->Civil_Game_Object_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Object_Work]->Percent_Complete_Build += 5;
						}
						else
						{
							if (Civil_Gaia_List->Civil_Game_Object_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Object_Work]->Object_Status != Dead ||
								Civil_Gaia_List->Civil_Game_Object_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Object_Work]->Object_Status != Death) // nếu cây vẫn còn sống thì tiếp tục đốn hạ
							{
								//cout << "YES";
								if (Civil_Gaia_List->Civil_Game_Object_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Object_Work]->Get_Hit_Point() > 0)
								{
									Civil_Gaia_List->Civil_Game_Object_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Object_Work]->Take_Damage(Civil_Gaia_List, Civil_Player_List, Civil_Computer_List);
								}

							}
							if (Civil_Gaia_List->Civil_Game_Object_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Object_Work]->Object_Status == Death && Civil_Gaia_List->Civil_Game_Object_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Object_Work]->Resource_Capacity > 0 &&
								Civil_Player_List[i]->Civil_Game_Object_List[j]->Object_Status == Working)
							{
								Civil_Player_List[i]->Civil_Game_Object_List[j]->Resource_Bearing += 1;
								Civil_Gaia_List->Civil_Game_Object_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Object_Work]->Resource_Capacity -= 1;
								//cout << Gaia_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Object_Work]->Resource_Capacity << endl;
							}
						}
						
						//cout << "Stand";
						/*if (Civil_Gaia_List->Civil_Game_Object_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Object_Work]->Object_Status == Dead ||
							Civil_Gaia_List->Civil_Game_Object_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Object_Work]->Object_Status == Disappear)
						{
							//cout << "Stand";
							if (Civil_Player_List[i]->Civil_Game_Object_List[j]->Resource_Bearing > 0)
							{
								Civil_Player_List[i]->Civil_Game_Object_List[j]->Going_to_return_resource = true;
								Civil_Player_List[i]->Civil_Game_Object_List[j]->Search_Going_to_return_resource = true;
							}
							else
							{
								Civil_Player_List[i]->Civil_Game_Object_List[j]->Change_Object_Status(Standing);
							}
						}*/
						/*if (Civil_Gaia_List->Civil_Game_Object_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Object_Work]->Object_Status == Disappear)
						{
							cout << "Dis";
						}*/

					}
				}
				//cout << "Khoang 2 " << endl;
				//cout << "Mot";
				/*if (Civil_Player_List[i]->Civil_Game_Object_List[j]->Current_Time_Attack - Civil_Player_List[i]->Civil_Game_Object_List[j]->Last_Time_Attack >= 20)
				{
					//cout << "Lonhon";
				}*/
				//cout << "Hai";
				/*if (Civil_Player_List[i]->Civil_Game_Object_List[j]->Moving_To_Attack)
				{
					//cout << Civil_Player_List[i]->Civil_Game_Object_List[j]->Object_Status;
					//cout << "YES";
				}*/
				if ((Civil_Player_List[i]->Civil_Game_Object_List[j]->Object_Status == Attacking || Civil_Player_List[i]->Civil_Game_Object_List[j]->Moving_To_Attack))
				{
					//cout << "Yes";
				}

				if (((Civil_Player_List[i]->Civil_Game_Object_List[j]->Current_Time_Attack - Civil_Player_List[i]->Civil_Game_Object_List[j]->Last_Time_Attack) >= Civil_Player_List[i]->Unit_Dt[Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Unit_Type()].Time_Next_Attacking) &&
					(Civil_Player_List[i]->Civil_Game_Object_List[j]->Object_Status == Attacking || Civil_Player_List[i]->Civil_Game_Object_List[j]->Moving_To_Attack))
				{
					//cout << "yes";
					Civil_Player_List[i]->Civil_Game_Object_List[j]->Last_Time_Attack = Civil_Player_List[i]->Civil_Game_Object_List[j]->Current_Time_Attack;
					if (Civil_Player_List[i]->Civil_Game_Object_List[j]->Check_Hit_Box_Activated())
					{
						//cout << "Attack";
						//cout << "yes";
						bool Check = false;

						if (Civil_Player_List[i]->Civil_Game_Object_List[j]->Object_Status == Attacking || Civil_Player_List[i]->Civil_Game_Object_List[j]->Moving_To_Attack)
						{
							Check = true;
						}
						else
						{
							//cout << "yes";
							Civil_Player_List[i]->Civil_Game_Object_List[j]->Disable_Hit_Box();
						}
						if (Civil_Player_List[i]->Civil_Game_Object_List[j]->Type_Control_Object_Object_Attack == Computer)
						{
							if (!Civil_Computer_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Control_Object_Object_Attack]->Civil_Game_Object_List[Civil_Player_List[i]->Civil_Game_Object_List[j]->Pos_Object_Attack]->Alive)
							{
								Check = false;
								Civil_Player_List[i]->Civil_Game_Object_List[j]->Disable_Hit_Box();
							}
						}
						if (Check)
						{
							//cout << "Attack";	
							if (!Civil_Player_List[i]->Civil_Game_Object_List[j]->Moving_To_Attack)
							{
								//cout << "yss";
								//cout << "You are attacking" << endl;
								Hit_Box Hit_Box_Assign = Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Hit_Box();
								//cout << Hit_Box_Assign.Damage << endl;
								//cout << " Hang va Cot cua Hit Box : " << Hit_Box_Assign.Row << " " << Hit_Box_Assign.Col << endl;
								//cout << Map_UG_Layer_2[Hit_Box_Assign.Row][Hit_Box_Assign.Col].List_Object_in_Cell.size();
								for (int k = 0; k < Map_UG_Layer_2[Hit_Box_Assign.Row][Hit_Box_Assign.Col].List_Object_in_Cell.size(); k++)
								{
									//cout << "abcd";
									if (Map_UG_Layer_2[Hit_Box_Assign.Row][Hit_Box_Assign.Col].List_Object_in_Cell[k].Country != Country_1 && Map_UG_Layer_2[Hit_Box_Assign.Row][Hit_Box_Assign.Col].List_Object_in_Cell[k].Object_Type != -1)
									{
										for (int s = 0; s < Civil_Computer_List.size(); s++)
										{
											if (Civil_Computer_List[s]->Get_Civil_Index() == Country_2)
											{
												//cout << "yes";
												if (Map_UG_Layer_2[Hit_Box_Assign.Row][Hit_Box_Assign.Col].List_Object_in_Cell[k].Pos < Civil_Computer_List[s]->Civil_Game_Object_List.size())
												{
													Civil_Computer_List[s]->Civil_Game_Object_List[Map_UG_Layer_2[Hit_Box_Assign.Row][Hit_Box_Assign.Col].List_Object_in_Cell[k].Pos]->Take_Damage(Civil_Gaia_List, Civil_Player_List, Civil_Computer_List);
												}
												//cout << "Hit Box " << endl;

											}
										}
									}
								}
							}

						}

					}
				}
			}
			if (Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Unit_Type() != -1)
			{
				Civil_Player_List[i]->Civil_Game_Object_List[j]->Load_Sprite_Sheet(Civil_Player_List[i]->Unit_Dt, Civil_Player_List[i]->Get_Civil_Index(), Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List);
				//cout << Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Country();
				Map_List_2.push_back(Civil_Player_List[i]->Civil_Game_Object_List[j]);
			}

		}
	}
	//cout << "Khoang 2" << endl;
	for (int i = 0; i < Civil_Computer_List.size(); i++)
	{
		//cout << "yes" << endl;
		Civil_Computer_List[i]->Civil_Develop();
		for (int j = 0; j < Civil_Computer_List[i]->Civil_Game_Object_List.size(); j++)
		{
			//cout << Civil_Computer_List[i]->Civil_Game_Object_List[j]->Get_Orth_Pos().x << " " << Civil_Computer_List[i]->Civil_Game_Object_List[j]->Get_Orth_Pos().y << endl;
				
			if (Civil_Computer_List[i]->Civil_Game_Object_List[j]->Alive)
			{
				Civil_Computer_List[i]->Civil_Game_Object_List[j]->Current_Time_Attack = SDL_GetTicks();
				//Civil_Computer_List[i]->Civil_Game_Object_List[j]->Current_Time_Move = SDL_GetTicks();
				Civil_Computer_List[i]->Civil_Game_Object_List[j]->Current_Time_Work = SDL_GetTicks();
				Civil_Computer_List[i]->Civil_Game_Object_List[j]->Train_Unit(Civil_Computer_List[i]->Civil_Game_Object_List[j]->Get_Unit_Type(), Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List);
				if (Civil_Computer_List[i]->Civil_Game_Object_List[j]->Object_Status == Moving || Civil_Computer_List[i]->Civil_Game_Object_List[j]->Object_Status == Carry)
				{
					//cout << "yes";
					//cout << "Move";
					Civil_Computer_List[i]->Civil_Game_Object_List[j]->Move(Civil_Player_List[i]->Unit_Dt, Civil_Computer_List[i]->Get_Civil_Index(), Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click,
						Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, j);
				}
				Civil_Computer_List[i]->Civil_Game_Object_List[j]->Attack(Civil_Computer_List[i]->Unit_Dt, Civil_Computer_List[i]->Civil_Game_Object_List[j]->Get_Country(),
					Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click, Civil_Computer_List, Civil_Player_List, j);
				if (((Civil_Computer_List[i]->Civil_Game_Object_List[j]->Current_Time_Attack - Civil_Computer_List[i]->Civil_Game_Object_List[j]->Last_Time_Attack) >= Civil_Computer_List[i]->Unit_Dt[Civil_Computer_List[i]->Civil_Game_Object_List[j]->Get_Unit_Type()].Time_Next_Attacking) &&
					(Civil_Computer_List[i]->Civil_Game_Object_List[j]->Object_Status == Attacking || Civil_Computer_List[i]->Civil_Game_Object_List[j]->Moving_To_Attack))
				{
					//cout << "yes";
					Civil_Computer_List[i]->Civil_Game_Object_List[j]->Last_Time_Attack = Civil_Computer_List[i]->Civil_Game_Object_List[j]->Current_Time_Attack;
					if (Civil_Computer_List[i]->Civil_Game_Object_List[j]->Check_Hit_Box_Activated())
					{
						//cout << "Attack";
						//cout << "yes";
						bool Check = false;

						if (Civil_Computer_List[i]->Civil_Game_Object_List[j]->Object_Status == Attacking || Civil_Computer_List[i]->Civil_Game_Object_List[j]->Moving_To_Attack)
						{
							Check = true;
						}
						else
						{
							//cout << "yes";
							Civil_Computer_List[i]->Civil_Game_Object_List[j]->Disable_Hit_Box();
						}
						if (Civil_Computer_List[i]->Civil_Game_Object_List[j]->Type_Control_Object_Object_Attack == Player)
						{
							if (!Civil_Player_List[Civil_Computer_List[i]->Civil_Game_Object_List[j]->Pos_Control_Object_Object_Attack]->Civil_Game_Object_List[Civil_Computer_List[i]->Civil_Game_Object_List[j]->Pos_Object_Attack]->Alive)
							{
								Check = false;
								Civil_Computer_List[i]->Civil_Game_Object_List[j]->Disable_Hit_Box();
							}
						}
						if (Check)
						{
							//cout << "Attack";	
							if (!Civil_Computer_List[i]->Civil_Game_Object_List[j]->Moving_To_Attack)
							{
								//cout << "yss";
								//cout << "You are attacking" << endl;
								Hit_Box Hit_Box_Assign = Civil_Computer_List[i]->Civil_Game_Object_List[j]->Get_Hit_Box();
								//cout << Hit_Box_Assign.Damage << endl;
								//cout << " Hang va Cot cua Hit Box : " << Hit_Box_Assign.Row << " " << Hit_Box_Assign.Col << endl;
								//cout << Map_UG_Layer_2[Hit_Box_Assign.Row][Hit_Box_Assign.Col].List_Object_in_Cell.size();
								for (int k = 0; k < Map_UG_Layer_2[Hit_Box_Assign.Row][Hit_Box_Assign.Col].List_Object_in_Cell.size(); k++)
								{
									//cout << "abcd";
									if (Map_UG_Layer_2[Hit_Box_Assign.Row][Hit_Box_Assign.Col].List_Object_in_Cell[k].Country != Country_2 && Map_UG_Layer_2[Hit_Box_Assign.Row][Hit_Box_Assign.Col].List_Object_in_Cell[k].Object_Type != -1)
									{
										for (int s = 0; s < Civil_Player_List.size(); s++)
										{
											if (Civil_Player_List[s]->Get_Civil_Index() == Country_1)
											{
												//cout << "yes";
												if (Map_UG_Layer_2[Hit_Box_Assign.Row][Hit_Box_Assign.Col].List_Object_in_Cell[k].Pos < Civil_Player_List[s]->Civil_Game_Object_List.size())
												{
													//cout << "yes";
													Civil_Player_List[s]->Civil_Game_Object_List[Map_UG_Layer_2[Hit_Box_Assign.Row][Hit_Box_Assign.Col].List_Object_in_Cell[k].Pos]->Take_Damage(Civil_Gaia_List, Civil_Player_List, Civil_Computer_List);
												}
												//cout << "Hit Box " << endl;

											}
										}
									}
								}
							}

						}

					}
				}
			}
			if (Civil_Computer_List[i]->Civil_Game_Object_List[j]->Get_Unit_Type() != -1)
			{
				Civil_Computer_List[i]->Civil_Game_Object_List[j]->Load_Sprite_Sheet(Civil_Computer_List[i]->Unit_Dt, Civil_Computer_List[i]->Get_Civil_Index(), Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List);
				Map_List_2.push_back(Civil_Computer_List[i]->Civil_Game_Object_List[j]);
			}
		}
	}
	for (int i = 0; i < Civil_Gaia_List->Civil_Game_Object_List.size(); i++)
	{
		if (Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Unit_Type() != -1)
		{
			if (Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Unit_Type() != Grass)
			{
				Civil_Gaia_List->Civil_Game_Object_List[i]->Load_Sprite_Sheet(Civil_Gaia_List->Unit_Dt, Country_Gaia, Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List);
			}
			if (Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Unit_Type() == Grass)
			{
				Map_List_1.push_back(Civil_Gaia_List->Civil_Game_Object_List[i]);
			}
			else
			{
				Map_List_2.push_back(Civil_Gaia_List->Civil_Game_Object_List[i]);
			}
		}
		
		//Map_List.push_back(Gaia_List[i]);
	}
	for (int i = 0; i < Background_List.size(); i++)
	{
		Map_List_1.push_back(Background_List[i]);
	}
	for (int i = 0; i < Map_List_2.size(); i++)
	{
		Map_List_2[i]->Visit = false;
		while (!Map_List_2[i]->Pos_Behind.empty())
		{
			Map_List_2[i]->Pos_Behind.pop();
		}
	}
	for (int i = 0; i < Map_List_2.size(); i++)
	{
		//cout << Map_List_2[i]->Get_Unit_Type()<< endl;
		Orth_Pos_A = Map_List_2[i]->Get_Orth_Pos();
		Pos_Sor_A = Map_List_2[i]->Get_Pos_Sor();
		//cout << Map_List_2.size() << endl;
		for (int j = 0; j < Map_List_2.size(); j++)
		{
			if (i != j)
			{
				//cout << j << endl;
				Orth_Pos_B = Map_List_2[j]->Get_Orth_Pos();
				Pos_Sor_B = Map_List_2[j]->Get_Pos_Sor();
				if (Check_A_Behind_B(Orth_Pos_A.x, Orth_Pos_A.y, Map_List_2[i]->z, Orth_Pos_B.x, Orth_Pos_B.y, Map_List_2[j]->z,
					Pos_Sor_A.w, Pos_Sor_A.h, Pos_Sor_B.w, Pos_Sor_B.h, Map_List_2[i]->Size_Number_Cell, Map_List_2[j]->Size_Number_Cell) == (-1))
				{
					
					//cout << Map_List_2[i]->Get_Unit_Type() << " Behind " << Map_List_2[j]->Get_Unit_Type() << endl;
					Map_List_2[i]->Pos_Behind.push(j);
				}
			}
		}
		
	}
	//cout << "end" << endl;
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer);
	for (int i = 0; i < Manager::Map_List_1.size(); i++)
	{
		Map_List_1[i]->Load_to_Screen();
	}
	
	for (int i = 0; i < Manager::Choose_Object_Game.size(); i++)
	{
		switch (Manager::Choose_Object_Game[i].Country)
		{
		case Country_Gaia:
		{
			for (int j = 0; j < Civil_Gaia_List->Civil_Game_Object_List.size(); j++)
			{
					/*SDL_Rect Assign_Rect = Manager::Civil_Gaia_List->Civil_Game_Object_List[Manager::Choose_Object_Game[i].Position]->Get_Iso_Pos();
					Assign_Rect.w = Civil_Gaia_List->Unit_Dt[Choose_Object_Game[i].Unit_Choose].Weight;
					Assign_Rect.h = Civil_Gaia_List->Unit_Dt[Choose_Object_Game[i].Unit_Choose].Height;*/
					Draw_Slection(Civil_Gaia_List->Civil_Game_Object_List[Choose_Object_Game[i].Position]);
					break;
			}
			break;
		}
		case Country_1:
		{
			for (int j = 0; j < Civil_Player_List.size(); j++)
			{
				if (Civil_Player_List[j]->Get_Civil_Index() == Country_1)
				{
					Draw_Slection(Civil_Player_List[j]->Civil_Game_Object_List[Manager::Choose_Object_Game[i].Position]);
					break;
				}
			}
			break;
		}	
		case Country_2:
		{
			for (int j = 0; j < Civil_Computer_List.size(); j++)
			{
				if (Civil_Computer_List[j]->Get_Civil_Index() == Country_2)
				{
					//SDL_Rect Assign_Rect = Manager::Civil_Computer_List[j]->Civil_Game_Object_List[Manager::Choose_Object_Game[i].Position]->Get_Iso_Pos();
					//Assign_Rect.w = Civil_Computer_List[j]->Unit_Dt[Choose_Object_Game[i].Unit_Choose].Weight;
					//Assign_Rect.h = Civil_Computer_List[j]->Unit_Dt[Choose_Object_Game[i].Unit_Choose].Height;
					Draw_Slection(Civil_Computer_List[j]->Civil_Game_Object_List[Choose_Object_Game[i].Position]);
					//cout << " Toa do : " << Assign_Rect.x << " " << Assign_Rect.y << " " << Civil_Computer_List[j]->Civil_Game_Object_List[Choose_Object_Game[i].Position]->Iso_Pos_Selection.x << " " << Civil_Computer_List[j]->Civil_Game_Object_List[Choose_Object_Game[i].Position]->Iso_Pos_Selection.y << endl;
					//Draw_Slection(Assign_Rect);
					break;
				}
			}
			break;
		}
		default:
			break;
		}
		/*if (Manager::Choose_Object_Game[i].Country == Country_1)
		{
			SDL_Rect Assign_Rect = Manager::Civil_Player_List[0]->Civil_Game_Object_List[Manager::Choose_Object_Game[i].Position]->Get_Iso_Pos();
			Draw_Slection(Assign_Rect);
		}
		else if (Choose_Object_Game[i].Country == Country_2)
		{
			SDL_Rect Assign_Rect = Manager::Civil_Computer_List[0]->Civil_Game_Object_List[Manager::Choose_Object_Game[i].Position]->Get_Iso_Pos();
			Draw_Slection(Assign_Rect);
		}*/
	}
	for (int i = 0; i < Manager::Map_List_2.size(); i++)
	{
		Manager::Sort_Topological(Map_List_2[i]);
	}
	Manager::Load_Interfac();
	//Manager::Load_Test();
	/*for (int i = 0; i < Manager::Map_List_2.size(); i++)
	{
		Map_List_2[i]->Load_to_Screen();
	}*/
	// Phần load thông tin cho đối tượng được chọn	
	if (!Choose_Object_Game.empty())
	{
		Font = TTF_OpenFont("arial.ttf", 13);
		if (Font) // Nếu Font này mở thành công thì thực hiện hiển thị, sở dĩ tôi làm việc này thì tôi thấy có vẻ như TTF có khá nhiều lần mở lỗi phông chữ thì phải, nhiều lần nó trả về NULL mà tôi không rõ tại sao
		{
			//Unit_Details Unit_Dt_Value[300];
			SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
			SDL_Rect Rectangle_Infor = { 7,607,123,112 };
			SDL_RenderDrawRect(Renderer, &Rectangle_Infor);
			SDL_RenderFillRect(Renderer, &Rectangle_Infor);
			SDL_Rect Iso_Pos_Choose_Object_Icon = { 15,635,52,51 };
			SDL_Rect Pos_Sor_Choose_Object_Icon = {};
			SDL_Color Color_Alphabet = { 255,255,255 };
			int Damage = 0;
			int Healthy = 1; // Lượng máu hiện tại
			int Hit_Point = 0; // Lượng máu đầy đủ
			int Armor = 1;
			int Attack_Range = 0;
			string Alphabet_String;
			stringstream Alphabet_Assign;
			if (Choose_Object_Game[0].Unit_Type_Control == Player)
			{
				//Unit_Dt_Value = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt;
				Pos_Sor_Choose_Object_Icon = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Icon_Pos_Sor;
				Damage = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Damage;
				Armor = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Armor;
				Hit_Point = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Hit_Point;
				Healthy = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Hit_Point();
			}
			else if (Choose_Object_Game[0].Unit_Type_Control == Computer)
			{
				Pos_Sor_Choose_Object_Icon = Civil_Computer_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Icon_Pos_Sor;
				Damage = Civil_Computer_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Damage;
				Armor = Civil_Computer_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Armor;
				Hit_Point = Civil_Computer_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Hit_Point;
				Healthy = Civil_Computer_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Hit_Point();
				//cout << Healthy << endl;
			}
			else if (Choose_Object_Game[0].Unit_Type_Control == Gaia)
			{
				Pos_Sor_Choose_Object_Icon = Civil_Gaia_List->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Icon_Pos_Sor;
				Damage = Civil_Gaia_List->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Damage;
				Armor = Civil_Gaia_List->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Armor;
				Hit_Point = Civil_Gaia_List->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Hit_Point;
				Healthy = Civil_Gaia_List->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Hit_Point();
			}
			/*else if (Choose_Object_Game[0].Unit_Type_Control == Gaia)
			{
				Pos_Sor_Choose_Object_Icon = Civil_Computer_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Icon_Pos_Sor;
				Damage = Civil_Computer_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Damage;
				Armor = Civil_Computer_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Armor;
				Hit_Point = Civil_Computer_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Hit_Point;
				Healthy = Civil_Computer_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Hit_Point();
			}*/
			string Unit_Name_String;
			const char* Unit_Name_Char;
			string Country_Name_String;
			const char* Country_Name_Char;
			switch (Choose_Object_Game[0].Unit_Type_Control)
			{
			case Player:
			{
				Unit_Name_String = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Unit_Type_Name;
				break;
			}
			case Computer:
			{
				Unit_Name_String = Civil_Computer_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Unit_Type_Name;
				break;
			}
			case Gaia:
			{
				Unit_Name_String = Civil_Gaia_List->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Unit_Type_Name;
				break;
			}
			default:
				break;
			}
			switch (Choose_Object_Game[0].Country_Name)
			{
			case Egyptian:
			{
				Country_Name_String = "Egyptian";
				break;
			}
			case Yamato:
			{
				Country_Name_String = "Yamato";
				break;
			}
			default:
				break;
			}
			// Hiển thị tên Dân tộc
			//Font = TTF_OpenFont("arial.ttf", 13);
			Country_Name_Char = (char*)Country_Name_String.c_str();
			Surface_Font = TTF_RenderText_Blended(Font, Country_Name_Char, Color_Alphabet);
			Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
			SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Country_Name.w, &Iso_Pos_Country_Name.h);
			Pos_Sor_Country_Name.w = Iso_Pos_Country_Name.w;
			Pos_Sor_Country_Name.h = Iso_Pos_Country_Name.h;
			SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Country_Name, &Iso_Pos_Country_Name);
			SDL_FreeSurface(Surface_Font);
			SDL_DestroyTexture(Texture_Font);

			// Hiển thị tên đơn vị
			Unit_Name_Char = (char*)Unit_Name_String.c_str();
			Surface_Font = TTF_RenderText_Blended(Font, Unit_Name_Char, Color_Alphabet);
			Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
			SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Unit_Name.w, &Iso_Pos_Unit_Name.h);
			Pos_Sor_Unit_Name.w = Iso_Pos_Unit_Name.w;
			Pos_Sor_Unit_Name.h = Iso_Pos_Unit_Name.h;
			SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Unit_Name, &Iso_Pos_Unit_Name);
			SDL_FreeSurface(Surface_Font);
			SDL_DestroyTexture(Texture_Font);

			// Hiển thị Sức khỏe của đơn vị
			string Healthy_String = to_string(Healthy);
			Healthy_String += '/';
			Healthy_String += to_string(Hit_Point);
			const char* Healthy_Char = (char*)Healthy_String.c_str();
			Surface_Font = TTF_RenderText_Blended(Font, Healthy_Char, Color_Alphabet);
			Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
			SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Hit_Point_Ratio.w, &Iso_Pos_Hit_Point_Ratio.h);
			Pos_Sor_Hit_Point_Ratio.w = Iso_Pos_Hit_Point_Ratio.w;
			Pos_Sor_Hit_Point_Ratio.h = Iso_Pos_Hit_Point_Ratio.h;
			SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Hit_Point_Ratio, &Iso_Pos_Hit_Point_Ratio);
			SDL_FreeSurface(Surface_Font);
			SDL_DestroyTexture(Texture_Font);
			//SDL_RenderCopy(Renderer,)
			// Hiển thị Icon của đơn vị
			if (Choose_Object_Game[0].Unit_Property == Building)
			{
				//cout << "yes";
				SDL_RenderCopy(Renderer, Country_House_Icon_Texture_Construct_1[Choose_Object_Game[0].Country], &Pos_Sor_Choose_Object_Icon, &Iso_Pos_Choose_Object_Icon);
			}
			else
			{
				SDL_RenderCopy(Renderer, Country_Unit_Icon_Texture[Choose_Object_Game[0].Country], &Pos_Sor_Choose_Object_Icon, &Iso_Pos_Choose_Object_Icon);
			}

			if (Choose_Object_Game[0].Unit_Choose != Mine_Gold || Choose_Object_Game[0].Unit_Choose != Mine_Stone || Choose_Object_Game[0].Unit_Choose != Tree_01)
			{
				SDL_Rect Pos_Sor_Hit_Point = { 0,0,51,8 };
				SDL_Rect Iso_Pos_Hit_Point = { 15,690,51,8 };
				int Hit_Point_Level = (int)(26 - ((double)Healthy / Hit_Point) * 26) * Pos_Sor_Hit_Point.w; // 26 là kích thước của một Sprite Hit Point
				Pos_Sor_Hit_Point.x = Hit_Point_Level;
				//cout << 1 / 0;
				SDL_RenderCopy(Renderer, Hit_Point_Texture, &Pos_Sor_Hit_Point, &Iso_Pos_Hit_Point);
				//cout << Hit_Point_Level << endl;

			}
			
			if (Choose_Object_Game[0].Unit_Type_Control == Player)
			{

				if (Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Unit_Type_Property() != Building)
				{
					Alphabet_String = to_string(Damage); // Hiển thị số Damage của đối tượng được chọn
					//Alphabet_String = Alphabet_Assign.str();
					Alphabet = (char*)Alphabet_String.c_str();
					Surface_Font = TTF_RenderText_Blended(Font, Alphabet, Color_Alphabet);
					//TTF_CloseFont(Font);
					Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
					SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Damage_Attribute_Number.w, &Iso_Pos_Damage_Attribute_Number.h);
					Pos_Sor_Damage_Attribute_Number.w = Iso_Pos_Damage_Attribute_Number.w;
					Pos_Sor_Damage_Attribute_Number.h = Iso_Pos_Damage_Attribute_Number.h;
					SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Damage_Attribute_Number, &Iso_Pos_Damage_Attribute_Number);
					SDL_RenderCopy(Renderer, Attribute_Object_Texture, &Pos_Sor_Damage_Attribute, &Iso_Pos_Damage_Attribute);
					SDL_FreeSurface(Surface_Font);
					SDL_DestroyTexture(Texture_Font);


					if (Choose_Object_Game[0].Unit_Choose == Woodcutter || Choose_Object_Game[0].Unit_Choose == Stone_Miner || Choose_Object_Game[0].Unit_Choose == Gold_Miner)
					{
						int Resource_Bearing_Value = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Resource_Bearing;
						Alphabet_String = to_string(Resource_Bearing_Value); // Hiển thị số Armor của đối tượng được chọn
						Alphabet = (char*)Alphabet_String.c_str();
						Surface_Font = TTF_RenderText_Blended(Font, Alphabet, Color_Alphabet);
						//TTF_CloseFont(Font);
						Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
						SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Armor_Attribute_Number.w, &Iso_Pos_Armor_Attribute_Number.h);
						Pos_Sor_Armor_Attribute_Number.w = Iso_Pos_Armor_Attribute_Number.w; // Tại sao tôi lại lấy tọa độ của Armor Value ? Vì chúng cùng vị trí !
						Pos_Sor_Armor_Attribute_Number.h = Iso_Pos_Armor_Attribute_Number.h;
						SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Armor_Attribute_Number, &Iso_Pos_Armor_Attribute_Number);
						if (Choose_Object_Game[0].Unit_Choose == Woodcutter)
						{
							SDL_RenderCopy(Renderer, Attribute_Object_Texture, &Pos_Sor_Wood, &Iso_Pos_Wood);
						}
						else if (Choose_Object_Game[0].Unit_Choose == Stone_Miner)
						{
							SDL_RenderCopy(Renderer, Attribute_Object_Texture, &Pos_Sor_Stone, &Iso_Pos_Stone);
						}
						else if (Choose_Object_Game[0].Unit_Choose == Gold_Miner)
						{
							SDL_RenderCopy(Renderer, Attribute_Object_Texture, &Pos_Sor_Gold, &Iso_Pos_Gold);
						}
					}
					else
					{
						Alphabet_String = to_string(Armor); // Hiển thị số Armor của đối tượng được chọn
						Alphabet = (char*)Alphabet_String.c_str();
						Surface_Font = TTF_RenderText_Blended(Font, Alphabet, Color_Alphabet);
						//TTF_CloseFont(Font);
						Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
						SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Armor_Attribute_Number.w, &Iso_Pos_Armor_Attribute_Number.h);
						Pos_Sor_Armor_Attribute_Number.w = Iso_Pos_Armor_Attribute_Number.w;
						Pos_Sor_Armor_Attribute_Number.h = Iso_Pos_Armor_Attribute_Number.h;
						SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Armor_Attribute_Number, &Iso_Pos_Armor_Attribute_Number);

						Alphabet_String = to_string(Attack_Range); // Hiển thị phạm vị tấn công của đối tượng được chọn
						//Alphabet_String = Alphabet_Assign.str();
						Alphabet = (char*)Alphabet_String.c_str();
						Surface_Font = TTF_RenderText_Blended(Font, Alphabet, Color_Alphabet);
						Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
						SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Attack_Range_Attribute_Number.w, &Iso_Pos_Attack_Range_Attribute_Number.h);
						Pos_Sor_Attack_Range_Attribute_Number.w = Iso_Pos_Attack_Range_Attribute_Number.w;
						Pos_Sor_Attack_Range_Attribute_Number.h = Iso_Pos_Attack_Range_Attribute_Number.h;
						SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Attack_Range_Attribute_Number, &Iso_Pos_Attack_Range_Attribute_Number);

						SDL_RenderCopy(Renderer, Attribute_Object_Texture, &Pos_Sor_Armor_Attribute, &Iso_Pos_Armor_Attribute);
						SDL_RenderCopy(Renderer, Attribute_Object_Texture, &Pos_Sor_Attack_Range_Attribute, &Iso_Pos_Attack_Range_Attribute);
					}
				}
				else if (Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Unit_Type_Property() == Building)
				{
					if (Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Researching_Tech)
					{
						// Hiển thị phần trăm công nghệ đang nghiên cứu
						int Percent_Tech_Researching_Value = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Percent_Tech_Researching; // Phần trăm công nghệ đang được nghiên cứu, bằng 100 % tức là đơn vị đã được nghiên cứu xong
						Alphabet_String = to_string(Percent_Tech_Researching_Value) + "%";
						Alphabet = (char*)Alphabet_String.c_str();
						Surface_Font = TTF_RenderText_Blended(Font, Alphabet, Color_Alphabet);
						Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
						SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Percent.w, &Iso_Pos_Percent.h);
						Pos_Sor_Percent.w = Iso_Pos_Percent.w;
						Pos_Sor_Percent.h = Iso_Pos_Percent.h;
						SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Percent, &Iso_Pos_Percent);
						SDL_RenderCopy(Renderer, Attribute_Object_Texture, &Pos_Sor_Clock_Icon, &Iso_Pos_Clock_Icon);
						SDL_FreeSurface(Surface_Font);
						SDL_DestroyTexture(Texture_Font);

					}
					else if (Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Training_Unit)
					{
						// Hiển thị phần trăm hiện tại đang Train đơn vị, bằng 100 % tức đơn vị đã được Train xong, nó sẽ thêm vào trong Vector Game Object List tương ứng
						int Percent_Training_Unit_Value = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Percent_Training_Unit; // Phần trăm đang Train đơn vị
						Alphabet_String = to_string(Percent_Training_Unit_Value) + "%";
						Alphabet = (char*)Alphabet_String.c_str();
						Surface_Font = TTF_RenderText_Blended(Font, Alphabet, Color_Alphabet);
						Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
						SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Percent.w, &Iso_Pos_Percent.h);
						Pos_Sor_Percent.w = Iso_Pos_Percent.w;
						Pos_Sor_Percent.h = Iso_Pos_Percent.h;
						SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Percent, &Iso_Pos_Percent);
						SDL_RenderCopy(Renderer, Attribute_Object_Texture, &Pos_Sor_Clock_Icon, &Iso_Pos_Clock_Icon);
						SDL_FreeSurface(Surface_Font);
						SDL_DestroyTexture(Texture_Font);

						// Hiển thị số lượng đơn vị đang được Train
						int Number_Unit_Train = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Number_Unit_Train();
						Alphabet_String = to_string(Number_Unit_Train);
						Alphabet = (char*)Alphabet_String.c_str();
						Surface_Font = TTF_RenderText_Blended(Font, Alphabet, White_Color);
						Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
						Iso_Pos_Number_Unit_Train = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Training_Unit_Type].Icon_Iso_Pos; // Lấy ra vị trí Icon của đối tượng này
						Iso_Pos_Number_Unit_Train.x += 5; // Mục đích cộng thêm để được tọa độ hiển thị cho thích hợp
						Iso_Pos_Number_Unit_Train.y += 5;
						SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Number_Unit_Train.w, &Iso_Pos_Number_Unit_Train.h);
						Pos_Sor_Number_Unit_Train.w = Iso_Pos_Number_Unit_Train.w;
						Pos_Sor_Number_Unit_Train.h = Iso_Pos_Number_Unit_Train.h;
						SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Number_Unit_Train, &Iso_Pos_Number_Unit_Train);
						SDL_FreeSurface(Surface_Font);
						SDL_DestroyTexture(Texture_Font);

					}
				}


			}
			else if (Choose_Object_Game[0].Unit_Type_Control == Computer)
			{
				//cout << "yes";
				if (Civil_Computer_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Unit_Type_Property() != Building)
				{
					//cout << "yes";
					Alphabet_String = to_string(Armor); // Hiển thị số Armor của đối tượng được chọn
					Alphabet = (char*)Alphabet_String.c_str();
					Surface_Font = TTF_RenderText_Blended(Font, Alphabet, Color_Alphabet);
					//TTF_CloseFont(Font);
					Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
					SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Armor_Attribute_Number.w, &Iso_Pos_Armor_Attribute_Number.h);
					Pos_Sor_Armor_Attribute_Number.w = Iso_Pos_Armor_Attribute_Number.w;
					Pos_Sor_Armor_Attribute_Number.h = Iso_Pos_Armor_Attribute_Number.h;
					SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Armor_Attribute_Number, &Iso_Pos_Armor_Attribute_Number);
					SDL_FreeSurface(Surface_Font);
					SDL_DestroyTexture(Texture_Font);

					Alphabet_String = to_string(Damage); // Hiển thị số Damage của đối tượng được chọn
					//Alphabet_String = Alphabet_Assign.str();
					Alphabet = (char*)Alphabet_String.c_str();
					Surface_Font = TTF_RenderText_Blended(Font, Alphabet, Color_Alphabet);
					//TTF_CloseFont(Font);
					Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
					SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Damage_Attribute_Number.w, &Iso_Pos_Damage_Attribute_Number.h);
					Pos_Sor_Damage_Attribute_Number.w = Iso_Pos_Damage_Attribute_Number.w;
					Pos_Sor_Damage_Attribute_Number.h = Iso_Pos_Damage_Attribute_Number.h;
					SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Damage_Attribute_Number, &Iso_Pos_Damage_Attribute_Number);
					SDL_FreeSurface(Surface_Font);
					SDL_DestroyTexture(Texture_Font);

					Alphabet_String = to_string(Attack_Range); // Hiển thị phạm vị tấn công của đối tượng được chọn
					//Alphabet_String = Alphabet_Assign.str();
					Alphabet = (char*)Alphabet_String.c_str();
					Surface_Font = TTF_RenderText_Blended(Font, Alphabet, Color_Alphabet);
					Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
					SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Attack_Range_Attribute_Number.w, &Iso_Pos_Attack_Range_Attribute_Number.h);
					Pos_Sor_Attack_Range_Attribute_Number.w = Iso_Pos_Attack_Range_Attribute_Number.w;
					Pos_Sor_Attack_Range_Attribute_Number.h = Iso_Pos_Attack_Range_Attribute_Number.h;
					SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Attack_Range_Attribute_Number, &Iso_Pos_Attack_Range_Attribute_Number);

					SDL_RenderCopy(Renderer, Attribute_Object_Texture, &Pos_Sor_Damage_Attribute, &Iso_Pos_Damage_Attribute);
					SDL_RenderCopy(Renderer, Attribute_Object_Texture, &Pos_Sor_Armor_Attribute, &Iso_Pos_Armor_Attribute);
					SDL_RenderCopy(Renderer, Attribute_Object_Texture, &Pos_Sor_Attack_Range_Attribute, &Iso_Pos_Attack_Range_Attribute);
					SDL_FreeSurface(Surface_Font);
					SDL_DestroyTexture(Texture_Font);

				}
			}
			else if (Choose_Object_Game[0].Unit_Type_Control == Gaia)
			{
				int Resource_Capacity_Value = Civil_Gaia_List->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Resource_Capacity;
				Alphabet_String = to_string(Resource_Capacity_Value); // Hiển thị số lượng tài nguyên của đối tượng được chọn đang có
				Alphabet = (char*)Alphabet_String.c_str();
				Surface_Font = TTF_RenderText_Blended(Font, Alphabet, Color_Alphabet);
				//TTF_CloseFont(Font);
				Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
				SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Armor_Attribute_Number.w, &Iso_Pos_Armor_Attribute_Number.h);
				Pos_Sor_Armor_Attribute_Number.w = Iso_Pos_Armor_Attribute_Number.w;
				Pos_Sor_Armor_Attribute_Number.h = Iso_Pos_Armor_Attribute_Number.h;
				SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Armor_Attribute_Number, &Iso_Pos_Armor_Attribute_Number);
				SDL_FreeSurface(Surface_Font);
				SDL_DestroyTexture(Texture_Font);
				if (Choose_Object_Game[0].Unit_Choose == Mine_Gold)
				{
					SDL_RenderCopy(Renderer, Attribute_Object_Texture, &Pos_Sor_Gold, &Iso_Pos_Gold);
				}
				else if (Choose_Object_Game[0].Unit_Choose == Mine_Stone)
				{
					SDL_RenderCopy(Renderer, Attribute_Object_Texture, &Pos_Sor_Stone, &Iso_Pos_Stone);
				}
				
			}
		}
		TTF_CloseFont(Font);
	}

	Font = TTF_OpenFont("arial.ttf", 13);
	if (Font)
	{
		TTF_SetFontStyle(Font, TTF_STYLE_BOLD);
		string Alphabet_String;
		Alphabet_String = to_string(Civil_Player_List[0]->Amount_Food); // Render số lượng Food của dân tộc đang được điều khiển bởi người chơi lên màn hình
		Alphabet = (char*)Alphabet_String.c_str();
		Surface_Font = TTF_RenderText_Blended(Font, Alphabet, Black_Color);
		//TTF_CloseFont(Font);
		Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
		SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Amount_Food.w, &Iso_Pos_Amount_Food.h);
		Pos_Sor_Amount_Food.w = Iso_Pos_Amount_Food.w;
		Pos_Sor_Amount_Food.h = Iso_Pos_Amount_Food.h;
		SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Amount_Food, &Iso_Pos_Amount_Food);
		SDL_FreeSurface(Surface_Font);
		SDL_DestroyTexture(Texture_Font);

		Alphabet_String = to_string(Civil_Player_List[0]->Amount_Wood); // Render số lượng Wood của dân tộc đang được điều khiển bởi người chơi lên màn hình
		Alphabet = (char*)Alphabet_String.c_str();
		Surface_Font = TTF_RenderText_Blended(Font, Alphabet, Black_Color);
		//TTF_CloseFont(Font);
		Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
		SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Amount_Wood.w, &Iso_Pos_Amount_Wood.h);
		Pos_Sor_Amount_Wood.w = Iso_Pos_Amount_Wood.w;
		Pos_Sor_Amount_Wood.h = Iso_Pos_Amount_Wood.h;
		SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Amount_Food, &Iso_Pos_Amount_Wood);
		SDL_FreeSurface(Surface_Font);
		SDL_DestroyTexture(Texture_Font);

		Alphabet_String = to_string(Civil_Player_List[0]->Amount_Gold); // Render số lượng Gold của dân tộc đang được điều khiển bởi người chơi lên màn hình
		Alphabet = (char*)Alphabet_String.c_str();
		Surface_Font = TTF_RenderText_Blended(Font, Alphabet, Black_Color);
		//TTF_CloseFont(Font);
		Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
		SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Amount_Gold.w, &Iso_Pos_Amount_Gold.h);
		Pos_Sor_Amount_Gold.w = Iso_Pos_Amount_Gold.w;
		Pos_Sor_Amount_Gold.h = Iso_Pos_Amount_Gold.h;
		SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Amount_Gold, &Iso_Pos_Amount_Gold);
		SDL_FreeSurface(Surface_Font);
		SDL_DestroyTexture(Texture_Font);

		Alphabet_String = to_string(Civil_Player_List[0]->Amount_Stone); // Render số lượng Stone của dân tộc đang được điều khiển bởi người chơi lên màn hình
		Alphabet = (char*)Alphabet_String.c_str();
		Surface_Font = TTF_RenderText_Blended(Font, Alphabet, Black_Color);
		//TTF_CloseFont(Font);
		Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
		SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Amount_Stone.w, &Iso_Pos_Amount_Stone.h);
		Pos_Sor_Amount_Stone.w = Iso_Pos_Amount_Stone.w;
		Pos_Sor_Amount_Stone.h = Iso_Pos_Amount_Stone.h;
		SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Amount_Stone, &Iso_Pos_Amount_Stone);
		SDL_FreeSurface(Surface_Font);
		SDL_DestroyTexture(Texture_Font);
	}
	TTF_CloseFont(Font);
	//Trường hợp này để in ra màn hình ngôi nhà sẽ xây nếu đối tượng chọn chế độ xây nhà
	if (!Choose_Object_Game.empty())
	{
		if (Choose_Object_Game[0].Unit_Type_Control == Player)
		{
			if (Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Find_to_Build_House())
			{
				//cout << "yes" << endl;
				SDL_Texture* Texture_Unit_Build = NULL;
				int x_Pos_Mouse_Motion_Orth_Pos = x_Pos_Mouse_Motion;
				int y_Pos_Mouse_Motion_Orth_Pos = y_Pos_Mouse_Motion;
				Reverse_Convert(x_Pos_Mouse_Motion_Orth_Pos, y_Pos_Mouse_Motion_Orth_Pos, 0, 0);
				SDL_Rect Locate_Build_Value = { x_Pos_Mouse_Motion_Orth_Pos,y_Pos_Mouse_Motion_Orth_Pos,0,0 };
				SDL_Rect Icon_Build_House_Iso_Pos = { 0,0,0,0 }; // Tọa độ để in ra hình nhà, nhằm chọn vị trí để Build
				SDL_Rect Icon_Build_House_Pos_Sor = { 0,0,0,0 }; // Tọa độ để lấy hình ảnh của đối tượng nhà sẽ Build cần in ra
				Texture_Unit_Build = Country_Unit_Details_Texture_List[Choose_Object_Game[0].Country].Unit_Dt_Texture[Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Unit_Type_Build()].Standing_Texture;
				int Unit_Type_Build_Value = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Unit_Type_Build();
				if (Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Check_Locate_Build_House(Unit_Type_Build_Value, Locate_Build_Value, Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click))
				{
					//cout << "yes";
					SDL_SetTextureAlphaMod(Texture_Unit_Build, 200); // Trường hợp nếu vị trí này có thể xây nhà thì in ra biểu tượng ngôi nhà màu bình thường, nhưng mờ hơn, có thể nhìn xuyên qua được
				}
				else
				{
					SDL_SetTextureColorMod(Texture_Unit_Build, 238, 35, 35); // Trường hợp nếu vị trí đó không xây được sẽ hiện màu đỏ
				}
				
				Icon_Build_House_Iso_Pos.x = x_Pos_Mouse_Motion - 27; // Cộng sao cho hợp lý để in ra đúng vị trí
				Icon_Build_House_Iso_Pos.y = y_Pos_Mouse_Motion - 20;
				Icon_Build_House_Iso_Pos.w = Icon_Build_House_Pos_Sor.w = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Unit_Type_Build()].Weight;
				Icon_Build_House_Iso_Pos.h = Icon_Build_House_Pos_Sor.h = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Unit_Dt[Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Unit_Type_Build()].Height;
				SDL_RenderCopy(Renderer, Texture_Unit_Build, &Icon_Build_House_Pos_Sor, &Icon_Build_House_Iso_Pos);
				SDL_SetTextureColorMod(Texture_Unit_Build, 255, 255, 255);
				SDL_SetTextureAlphaMod(Texture_Unit_Build, 255);
			}
		}
	}
	
	// In con trỏ chuột ra màn hình
	Mouse_Iso_Pos.x = x_Pos_Mouse_Motion - 27;
	Mouse_Iso_Pos.y = y_Pos_Mouse_Motion - 20;
	SDL_RenderCopy(Renderer, Mouse_State_Texture, &Mouse_Pos_Sor, &Mouse_Iso_Pos);
	SDL_ShowCursor(SDL_DISABLE); // Ẩn con trỏ chuột đi, vì đã có con trỏ chuột khác trong game
	if (!Civil_Player_List.empty())
	{
		Font = TTF_OpenFont("arial.ttf", 13);
		if (Font)
		{
			TTF_SetFontStyle(Font, TTF_STYLE_BOLD);
			SDL_Rect Pos_Sor_Population = { 0,0,0,0 };
			SDL_Rect Iso_Pos_Population = { 400,30,0,0 };
			string Alphabet_String;
			Alphabet_String += "Population : ";
			Alphabet_String += to_string(Civil_Player_List[0]->Get_Population());
			Alphabet_String += "/";
			Alphabet_String += to_string(Civil_Player_List[0]->Get_Population_Max());
			Alphabet = (char*)Alphabet_String.c_str();
			Surface_Font = TTF_RenderText_Blended(Font, Alphabet, White_Color);
			//TTF_CloseFont(Font);
			Texture_Font = SDL_CreateTextureFromSurface(Renderer, Surface_Font);
			SDL_QueryTexture(Texture_Font, NULL, NULL, &Iso_Pos_Population.w, &Iso_Pos_Population.h);
			Pos_Sor_Population.w = Iso_Pos_Population.w;
			Pos_Sor_Population.h = Iso_Pos_Population.h;
			SDL_RenderCopy(Renderer, Texture_Font, &Pos_Sor_Population, &Iso_Pos_Population);
			SDL_FreeSurface(Surface_Font);
			SDL_DestroyTexture(Texture_Font);
		}
		TTF_CloseFont(Font);
	}
	
	SDL_RenderPresent(Renderer);
	//SDL_DestroyTexture(Texture_Unit_Build);
	//cout << Map_UG_Layer_2[3][5].List_Object_in_Cell.size();
	//cout << Check_Cell_Empty(3, 5, Map_UG_Layer_2);

	// In ra Population hiện tại
}
void Manager::Sort_Topological(Game_Object* Sprite) // Thuật toán tìm kiếm và vẽ sử dụng giải thuật Topologocal
{
	if (!Sprite->Visit)
	{
		Sprite->Visit = true;
		while (!Sprite->Pos_Behind.empty())
		{
			int Pos = Sprite->Pos_Behind.top();
			Sprite->Pos_Behind.pop();
			//cout << Pos << endl;
			Sort_Topological(Manager::Map_List_2[Pos]);
		}
		Sprite->Load_to_Screen();
	}
}

void Manager::Handle_Event(bool& Running) // Xử lý các sự kiện trong Game
{
	while (Running)
	{
		const Uint8* State = SDL_GetKeyboardState(NULL);
		SDL_PollEvent(&Event);
		switch (Event.type)
		{
		case SDL_QUIT:
			Running = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (Event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
				//cout << "yes";
				x_Pos_Click = Event.button.x;
				y_Pos_Click = Event.button.y;
				if (!Manager::Mouse_Button_Left)
				{
					Mouse_Button_Left = true;
					bool Choose = false;
					if (y_Pos_Click < 600)
					{
						if (!Choose_Object_Game.empty())
						{
							if (Choose_Object_Game[0].Unit_Type_Control == Player)
							{
								if (Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Find_to_Build_House()) // Trường hợp thiết lập thông số cho đối tượng xây nhà, trường hợp này là xây nhà !
								{
									SDL_Rect Locate_Build_House_Value = { x_Pos_Click,y_Pos_Click,0,0 };
									if (Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Check_Locate_Build_House(Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Unit_Type_Build(), Locate_Build_House_Value, Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click))
									{
										int Row_Cell_Click = y_Pos_Click / Orth_Tile_Height;
										int Col_Cell_Click = x_Pos_Click / Orth_Tile_Weight;
										int x_Pos_Click_Assign = x_Pos_Click;
										int y_Pos_Click_assign = y_Pos_Click;
										Reverse_Convert(x_Pos_Click_Assign, y_Pos_Click_assign, 0, 0);
										SDL_Rect Orth_Pos_Work_Value = { x_Pos_Click_Assign / Orth_Tile_Height * Orth_Tile_Height,y_Pos_Click_assign / Orth_Tile_Height * Orth_Tile_Height,0,0 };
										Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Change_Unit_Type(Builder); // Đối tượng sẽ chuyển thành người xây nhà

										Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Change_Object_Status(Working);
										int Unit_Type_Object_Work_Value = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Unit_Type_Build();
										int Pos_Object_Work_Value = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Get_Pos_New_Object();
										int Country_Object_Work_Value = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Country();
										int Unit_Type_Control = Player; // Vì người chơi yêu cầu xây nhà, lên Loại điều khiển Civil là Player
										int Pos_Control_Value = Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Pos_Control;
										Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Build(Unit_Type_Object_Work_Value, Orth_Pos_Work_Value, Civil_Player_List[0]->Unit_Dt, Civil_Player_List[0]->Get_Civil_Index(), Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Choose_Object_Game[0].Position);
										// Thiết lập các thông số đối tượng về nơi cần làm việc
										Civil_Player_List[Choose_Object_Game[0].Pos_Control]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Disable_Find_to_Build_House();
									}
								}
							}
						}
						for (int i = 0; i < Manager::Civil_Player_List.size(); i++)
						{
							for (int j = 0; j < Manager::Civil_Player_List[i]->Civil_Game_Object_List.size(); j++)
							{
								SDL_Rect Assign_Rect = Manager::Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Iso_Pos();
								if (Assign_Rect.x <= x_Pos_Click && x_Pos_Click <= Assign_Rect.x + Assign_Rect.w && Assign_Rect.y <= y_Pos_Click && y_Pos_Click <= Assign_Rect.y + Assign_Rect.h && y_Pos_Click < Interfac_y_Pos)
								{
									//cout << Choose_Object_Game.size();
									for (int k = 0; k < Choose_Object_Game.size(); k++)
									{
										if (Choose_Object_Game[k].Country == Civil_Player_List[i]->Get_Civil_Index() && Choose_Object_Game[k].Position == j)
										{
											Choose = true;
											goto Stop;
										}
									}
									Choose_Object Assign_Choose_Object;
									Assign_Choose_Object.Unit_Choose = Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Unit_Type();
									Assign_Choose_Object.Country = Civil_Player_List[i]->Get_Civil_Index();
									Assign_Choose_Object.Position = j;
									Assign_Choose_Object.Unit_Type_Control = Player;
									Assign_Choose_Object.Pos_Control = i;
									Assign_Choose_Object.Country_Name = Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Country_Name();
									Assign_Choose_Object.Unit_Property = Civil_Player_List[i]->Civil_Game_Object_List[j]->Get_Unit_Type_Property();
									//cout << Assign_Choose_Object.Position;
									Choose_Object_Game.push_back(Assign_Choose_Object);
									Choose = true;
									if (Choose_Object_Game[0].Unit_Choose == Villager)
									{
										Sub_Menu.push(Construct_Villager);
									}
									goto Stop;
								}
							}
							//goto Stop;
						}
						// Đoạn tiếp theo xác định xem có chọn các đối tượng của máy không
						for (int i = 0; i < Manager::Civil_Computer_List.size(); i++)
						{
							for (int j = 0; j < Manager::Civil_Computer_List[i]->Civil_Game_Object_List.size(); j++)
							{
								SDL_Rect Assign_Rect = Manager::Civil_Computer_List[i]->Civil_Game_Object_List[j]->Get_Iso_Pos();
								if (Assign_Rect.x <= x_Pos_Click && x_Pos_Click <= Assign_Rect.x + Assign_Rect.w && Assign_Rect.y <= y_Pos_Click && y_Pos_Click <= Assign_Rect.y + Assign_Rect.h && y_Pos_Click < Interfac_y_Pos)
								{
									//cout << Choose_Object_Game.size();
									for (int k = 0; k < Choose_Object_Game.size(); k++)
									{
										if (Choose_Object_Game[k].Country == Civil_Computer_List[i]->Get_Civil_Index() && Choose_Object_Game[k].Position == j)
										{
											Choose = true;
											goto Stop;
										}
									}
									Choose_Object Assign_Choose_Object;
									Assign_Choose_Object.Unit_Choose = Civil_Computer_List[i]->Civil_Game_Object_List[j]->Get_Unit_Type();
									Assign_Choose_Object.Country = Civil_Computer_List[i]->Get_Civil_Index();
									Assign_Choose_Object.Position = j;
									Assign_Choose_Object.Unit_Type_Control = Computer;
									Assign_Choose_Object.Pos_Control = i;
									Assign_Choose_Object.Country_Name = Civil_Computer_List[i]->Civil_Game_Object_List[j]->Get_Country_Name();
									Assign_Choose_Object.Unit_Property = Civil_Computer_List[i]->Civil_Game_Object_List[j]->Get_Unit_Type_Property();
									//cout << Assign_Choose_Object.Position;
									Choose_Object_Game.push_back(Assign_Choose_Object);
									Choose = true;
									goto Stop;
								}
							}
							//goto Stop;
						}
						for (int j = 0; j < Manager::Civil_Gaia_List->Civil_Game_Object_List.size(); j++)
						{
							if (Civil_Gaia_List->Civil_Game_Object_List[j]->Get_Unit_Type() != Grass)
							{
								SDL_Rect Assign_Rect = Manager::Civil_Gaia_List->Civil_Game_Object_List[j]->Get_Iso_Pos();
								if (Assign_Rect.x <= x_Pos_Click && x_Pos_Click <= Assign_Rect.x + Assign_Rect.w && Assign_Rect.y <= y_Pos_Click && y_Pos_Click <= Assign_Rect.y + Assign_Rect.h && y_Pos_Click < Interfac_y_Pos)
								{
									//cout << Choose_Object_Game.size();
									for (int k = 0; k < Choose_Object_Game.size(); k++)
									{
										if (Choose_Object_Game[k].Country == Gaia && Choose_Object_Game[k].Position == j)
										{
											Choose = true;
											goto Stop;
										}
									}
									Choose_Object Assign_Choose_Object;
									Assign_Choose_Object.Unit_Choose = Civil_Gaia_List->Civil_Game_Object_List[j]->Get_Unit_Type();
									Assign_Choose_Object.Country = Gaia;
									Assign_Choose_Object.Position = j;
									Assign_Choose_Object.Unit_Type_Control = Gaia;
									Assign_Choose_Object.Country_Name = Civil_Gaia_List->Civil_Game_Object_List[j]->Get_Country_Name();
									Assign_Choose_Object.Unit_Property = Civil_Gaia_List->Civil_Game_Object_List[j]->Get_Unit_Type_Property();
									//Assign_Choose_Object.Pos_Control = i;
									//cout << Assign_Choose_Object.Position;
									Choose_Object_Game.push_back(Assign_Choose_Object);
									Choose = true;
									goto Stop;
								}
							}

						}
						while (Sub_Menu.size() != 0)
						{
							//cout << "yes";
							Sub_Menu.pop();
						}
					}
					else if (y_Pos_Click > 600)
					{
						/*if (!Sub_Menu.empty())
						{
							/*if (Sub_Menu.top() == Construct_Villager)
							{
								for (int i = 0; i < Civil_Player_List.size(); i++)
								{
									SDL_Rect Build_Iso_Pos_Value = Civil_Player_List[i]->Button_Dt[Build].Button_Iso_Pos;
									//SDL_Rect Stop_Iso_Pos_Value = Civil_Player_List[Country_1]->Button_Dt[Stop].Button_Iso_Pos;
									if (Build_Iso_Pos_Value.x < x_Pos_Click && x_Pos_Click < Build_Iso_Pos_Value.x + Build_Iso_Pos_Value.w &&
										Build_Iso_Pos_Value.y < y_Pos_Click && y_Pos_Click < Build_Iso_Pos_Value.y + Build_Iso_Pos_Value.h)
									{
										//cout << "yes";
										Sub_Menu.push(Page_1_Build_Construct);
									}
								}
							}
						}*/
						
					}
				Stop:
					if (!Choose_Object_Game.empty())
					{
						if (Choose_Object_Game[0].Country == Country_1)
						{
							bool Check = true;
							if (Check)
							{
								for (int j = 0; j <= Iron_Age; j++) // Vòng lặp để kiểm tra sự kiện chuột xem người chơi nâng cấp công nghệ nào khi click vào các Icon tương ứng
								{
									if (Civil_Player_List[0]->Check_Tech_to_Research(j, Choose_Object_Game[0], x_Pos_Click, y_Pos_Click, Sub_Menu))
									{
										Check = false;
									}
								}
							}
							if (Check)
							{
								for (int j = 0; j <= Build_3_3; j++) // Vòng lặp để kiểm tra xem sự kiện chuột xem người chơi đã click vào train đối tượng Game nào
								{
									if (Civil_Player_List[0]->Check_Train_Game_Unit(j, Choose_Object_Game[0], x_Pos_Click, y_Pos_Click, Sub_Menu, Map_Layer_1, Map_Layer_2, Choose_Object_Game[0].Position, Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click))
									{
										Check = false;
									}
								}
							}

							if (Check)
							{
								for (int j = 0; j <= Stop_Train; j++)
								{
									Civil_Player_List[0]->Check_Button_Perform(j, x_Pos_Click, y_Pos_Click, Sub_Menu, Choose_Object_Game[0]);
								}
							}
							
							
							/*for (int j = 0; j <= Page_2_Build_Construct; j++)
							{
								Civil_Player_List[0]->Check_Button_Display(j, Sub_Menu, Choose_Object_Game[0]);
							}*/
						}
						/*switch (Choose_Object_Game[0].Unit_Choose)
						{
						case Town_Center_1_M_1:
							for (int i = 0; i < Civil_Player_List.size(); i++)
							{
								if (Civil_Player_List[i]->Get_Civil_Index() == Country_1)
								{
									for (int j = 0; j < Iron_Age; j++)
									{
										Civil_Player_List[i]->Check_Tech_to_Research(j,)
									}
									if (Civil_Player_List[i]->Get_Tech_Details(Tool_Age).Icon_Iso_Pos.x <= x_Pos_Click && x_Pos_Click <= Civil_Player_List[i]->Get_Tech_Details(Tool_Age).Icon_Iso_Pos.x + Civil_Player_List[i]->Get_Tech_Details(Tool_Age).Icon_Iso_Pos.w &&
										Civil_Player_List[i]->Get_Tech_Details(Tool_Age).Icon_Iso_Pos.y <= y_Pos_Click && y_Pos_Click <= Civil_Player_List[i]->Get_Tech_Details(Tool_Age).Icon_Iso_Pos.y + Civil_Player_List[i]->Get_Tech_Details(Tool_Age).Icon_Iso_Pos.h &&
										Civil_Player_List[i]->Check_Tech(Tool_Age) && !Civil_Player_List[i]->Check_Tech_Researching(Tool_Age))
									{

										if (Civil_Player_List[i]->Pay_Money(Civil_Player_List[i]->Get_Tech_Details(Tool_Age).Cost_Food, Civil_Player_List[i]->Get_Tech_Details(Tool_Age).Cost_Gold,
											Civil_Player_List[i]->Get_Tech_Details(Tool_Age).Cost_Wood, Civil_Player_List[i]->Get_Tech_Details(Tool_Age).Cost_Stone))
										{
											Civil_Player_List[i]->Enable_Tech_Researching(Tool_Age);
											Civil_Player_List[i]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Start_Researching_Tech(Tool_Age);
										}
									}
								}
							}
						}*/
					}
				
					if (y_Pos_Click >= Interfac_y_Pos)
					{
						Choose = true;
					}
					if (!Choose)
					{
						Manager::Choose_Object_Game.clear();
					}
					break;
				}
				break;
			}
			
			case SDL_BUTTON_RIGHT:
			{
				//cout << "no";
				x_Pos_Click = Event.button.x;
				y_Pos_Click = Event.button.y;
				//int x_Pos_Click_Assign = x_Pos_Click;
				//int y_Pos_Click_Assign = y_Pos_Click;
				//SDL_Rect W_H = Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Iso_Pos(); // Lấy ra thông tin về tọa độ và chiều cao, rộng của đối tượng đang được chọn
				//Reverse_Convert(x_Pos_Click_Assign, y_Pos_Click_Assign, W_H.w, W_H.h);
				//int Col_Cell_Click = x_Pos_Click_Assign / Orth_Tile_Weight;
				//int Row_Cell_Click = y_Pos_Click_Assign / Orth_Tile_Height;
				/*for (int i = 0; i < Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell.size(); i++)
				{
					//cout << Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Country;
					if (Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Country == Country_2 && Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Object_Type != -1)
					{
						//cout << "OKKKKKKKK";
					}
				}*/
				
				if (!Manager::Mouse_Button_Right)
				{
					Mouse_Button_Right = true;
					if (!Choose_Object_Game.empty())
					{
						if (!Civil_Player_List.empty() && Choose_Object_Game[0].Country == Country_1 && y_Pos_Click < 600)
						{
							
							//cout << "yes";
							int x_Pos_Click_Assign = x_Pos_Click;
							int y_Pos_Click_Assign = y_Pos_Click;
							SDL_Rect W_H = Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Iso_Pos(); // Lấy ra thông tin về tọa độ và chiều cao, rộng của đối tượng đang được chọn
							//Reverse_Convert(x_Pos_Click_Assign, y_Pos_Click_Assign, W_H.w, W_H.h);
							int Col_Cell_Click = x_Pos_Click_Assign / Orth_Tile_Weight;
							int Row_Cell_Click = y_Pos_Click_Assign / Orth_Tile_Height;
							//cout << Row_Cell_Click << " " << Col_Cell_Click << endl;
							//cout << "Size : " << Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell.size() << endl;
							int x = 21, y = 38, w = 50, h = 50;
							SDL_Rect Test_Convert_Orth = { 160,96,50,50 };
							SDL_Rect Test_Convert_Iso;
							//Convert_Object(Test_Convert_Iso, Test_Convert_Orth, Test_Convert_Orth.w, Test_Convert_Orth.h);
							//Reverse_Convert(Test_Convert_Iso.x, Test_Convert_Iso.y, Test_Convert_Orth.w, Test_Convert_Orth.h);
							//cout << " Gia tri sau khi reverse convert la : " << Test_Convert_Iso.x << " " << Test_Convert_Iso.y << endl;
							for (int i = 0; i < Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell.size(); i++)
							{
								//cout << Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Object_Type << endl;
								//cout << "yes";
								/* Map Check Click : Một loại Map theo màn hình hiển thị, tức màn hình của máy tính, các đối tượng trên màn hình này sẽ được đưa vào các ô tương ứng,
								( màn hình sẽ được chia vào thành các ô, mỗi đối tượng sẽ ở các ô tương ứng)
								Chuột Click vào vị trí nào thì sẽ tương ứng với ô đó trên màn hình hiển thị, và tát nhiên tọa độ chuột chọn sẽ tương ứng với Map game tương ứng của đối tượng
								*/
								if (Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Country == Country_1)
								{
									//cout << "yes";
									//cout << "yes" << endl;
									// Trường hợp này là trường hợp nếu đối tượng bị nhấn tấn công0 thuộc Country 1, tức là cùng nước ta thì không thể tấn công được, vì ai lại đi đánh đồng bào :v
									//goto Next;
								}
								else if (Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Country == Country_2 && Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Object_Type != -1)
								{
									cout << "Attack";
									//cout << Civil_Computer_List[j]->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Iso_Pos().w;
									// Ở đây tôi nghĩ cần điều kiện để xác định chính xác xem liệu con trỏ chuột có nhấn vào đối tượng hay không, nhưng hiện tại thì tôi sẽ coi như là nhấn vào ô có đối tượng nào là tấn công luôn đối tượng đó
									for (int j = 0; j < Civil_Computer_List.size(); j++)
									{
										if (Civil_Computer_List[j]->Get_Civil_Index() == Country_2)
										{
											cout << Civil_Computer_List[j]->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Iso_Pos().w;
											//cout << "yes" << endl;
											
											SDL_Rect Iso_Pos_Choose = Civil_Computer_List[j]->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Iso_Pos();
											if (Civil_Computer_List[j]->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Unit_Type() == Clubman)
											{
												cout << "Club Man" << endl;
											}
											//cout << " Toa do doi tuong se tan cong : " << Iso_Pos_Choose.x << " " << Iso_Pos_Choose.y << endl;
											//cout << "Toa do chuot da nhan : " << x_Pos_Click_Assign << " " << y_Pos_Click_Assign << endl;
											/* Ban đầu đúng tôi định xem xét tấn công không bằng cách nhận Orth_Pos, tức tọa độ ở hệ 2D, nhưng có vẻ nó sẽ gây sai lệch
											*/
											int Size_NS = Civil_Computer_List[j]->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Size_Number_Cell;
											if (Iso_Pos_Choose.x <= x_Pos_Click_Assign && x_Pos_Click_Assign <= (Iso_Pos_Choose.x + Iso_Pos_Choose.w) && Iso_Pos_Choose.y <= y_Pos_Click_Assign && y_Pos_Click_Assign <= Iso_Pos_Choose.y + Iso_Pos_Choose.h)
											{	
												//cout << "abc";
												cout << "Attack";
												cout << Civil_Computer_List[j]->Civil_Game_Object_List.size();
												int Damage = Civil_Player_List[0]->Unit_Dt[Choose_Object_Game[0].Unit_Choose].Damage;
												SDL_Rect Orth_Pos_Attack_Assign;
												Orth_Pos_Attack_Assign = Civil_Computer_List[j]->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Orth_Pos();
												Orth_Pos_Attack_Assign.x = Civil_Computer_List[j]->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Orth_Pos().x;
												Orth_Pos_Attack_Assign.y = Civil_Computer_List[j]->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Orth_Pos().y;
												Orth_Pos_Attack_Assign.x += Civil_Computer_List[j]->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Size_Number_Cell / 2 * Orth_Tile_Height;
												Orth_Pos_Attack_Assign.y += Civil_Computer_List[j]->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Size_Number_Cell / 2 * Orth_Tile_Height;
												//cout << "Attack" << endl;
												int Col_Cell_Click_Hit_Box = Orth_Pos_Attack_Assign.x / Orth_Tile_Weight;
												int Row_Cell_Click_Hit_Box = Orth_Pos_Attack_Assign.y / Orth_Tile_Height;
												//cout << " Hang va cot dat Hit Box la : " << Row_Cell_Click_Hit_Box << " " << Col_Cell_Click_Hit_Box << endl;
												//cout << Map_UG_Layer_2[Row_Cell_Click_Hit_Box][Col_Cell_Click_Hit_Box].List_Object_in_Cell.size();
												int Unit_Type_Object_Attack_Value = Civil_Computer_List[j]->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Unit_Type();
												int Pos_Object_Attack_Value = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos;
												int Country_Object_Attack_Value = Civil_Computer_List[j]->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Country();
												int Type_Control_Object_Object_Attack_Value = Civil_Computer_List[j]->Get_Type_Control_Object();
												//cout << "Pos : " << j << endl;
												int Pos_Control_Object_Object_Attack_Value = j;
												Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Set_Orth_Pos_Object_Attack(Civil_Player_List, Civil_Computer_List, Orth_Pos_Attack_Assign, Unit_Type_Object_Attack_Value, Pos_Object_Attack_Value, Country_Object_Attack_Value, Type_Control_Object_Object_Attack_Value, Pos_Control_Object_Object_Attack_Value);
												//Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Set_Hit_Box(Row_Cell_Click_Hit_Box, Col_Cell_Click_Hit_Box, Damage, 0, -1);
												// Các dòng lệnh tiếp theo sẽ đưa thông tin của đối tượng đang tấn công vào đối tượng bị tấn công
												int Unit_Type_Attack_Object_Value = Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Unit_Type();
												int Pos_Attack_Object_Value = Choose_Object_Game[0].Position;
												int Country_Attack_Object_Value = Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Country();
												int Type_Control_Object_Attack_Object_Value = Civil_Player_List[0]->Get_Type_Control_Object();
												int Pos_Control_Object_Attack_Object_Value = 0;
												Civil_Computer_List[j]->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Infor_Attack_Object(Unit_Type_Attack_Object_Value, Pos_Attack_Object_Value, Country_Attack_Object_Value, Type_Control_Object_Attack_Object_Value, Pos_Control_Object_Attack_Object_Value);
												Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Enable_Search_Move_To_Attack();
												goto Next_1; // Vì nó đã xác nhận sẽ tấn công đối tượng này lên bỏ qua phần di chuyển, đoạn code dưới để giúp đối tượng di chuyển tới một vị trí bất kì
											}
										}
									}

								}
								else if (Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Country == Country_Gaia && Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Object_Type != -1)
								{
									cout << "YES";
									SDL_Rect Iso_Pos_Choose = Civil_Gaia_List->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Iso_Pos();
									int Size_NS = Civil_Gaia_List->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Size_Number_Cell;
									if (Iso_Pos_Choose.x <= x_Pos_Click_Assign && x_Pos_Click_Assign <= (Iso_Pos_Choose.x + Iso_Pos_Choose.w) && Iso_Pos_Choose.y <= y_Pos_Click_Assign && y_Pos_Click_Assign <= Iso_Pos_Choose.y + Iso_Pos_Choose.h)
									{
										if (Civil_Gaia_List->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Unit_Type() == Tree_01)
										{
											Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Change_Unit_Type(Woodcutter); // Người chơi Click chuột phải vào cây, tức họ muốn nông dân này chặt gỗ, do đó đối tượng này chuyển đổi thành "Woodcutter"

											Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Change_Object_Status(Working);
											//Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Object_Status = Working;
											int Unit_Type_Object_Work_Value = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Object_Type;
											int Pos_Object_Work_Value = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos;
											int Country_Object_Work_Value = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Country;
											int Unit_Type_Control_Work = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Unit_Type_Control;
											int Pos_Control_Work = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos_Control;
											SDL_Rect Orth_Pos_Work_Value = Civil_Gaia_List->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Orth_Pos();
											Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Search_Moving_to_Work = true;
											Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Set_Orth_Pos_Work(Orth_Pos_Work_Value, Unit_Type_Object_Work_Value, Pos_Object_Work_Value, Country_Object_Work_Value, Unit_Type_Control_Work, Pos_Control_Work);
											goto Next_1;
										}
										else if (Civil_Gaia_List->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Unit_Type() == Mine_Gold)
										{
											//cout << "yes";
											Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Change_Unit_Type(Gold_Miner); // Người chơi Click chuột phải vào bãi vàng, tức họ muốn nông dân này đào vàng, do đó đối tượng này chuyển đổi thành "Gold_Miner"

											Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Change_Object_Status(Working);
											//Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Object_Status = Working;
											int Unit_Type_Object_Work_Value = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Object_Type;
											int Pos_Object_Work_Value = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos;
											int Country_Object_Work_Value = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Country;
											int Unit_Type_Control_Work = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Unit_Type_Control;
											int Pos_Control_Work = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos_Control;
											SDL_Rect Orth_Pos_Work_Value = Civil_Gaia_List->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Orth_Pos();
											Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Search_Moving_to_Work = true;
											Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Set_Orth_Pos_Work(Orth_Pos_Work_Value, Unit_Type_Object_Work_Value, Pos_Object_Work_Value, Country_Object_Work_Value, Unit_Type_Control_Work, Pos_Control_Work);
											goto Next_1;
										}
										else if (Civil_Gaia_List->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Unit_Type() == Mine_Stone)
										{
											//cout << "yes";
											Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Change_Unit_Type(Stone_Miner); // Chuyển đối tượng sang thợ đào đá

											Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Change_Object_Status(Working);
											//Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Object_Status = Working;
											int Unit_Type_Object_Work_Value = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Object_Type;
											int Pos_Object_Work_Value = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos;
											int Country_Object_Work_Value = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Country;
											int Unit_Type_Control_Work = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Unit_Type_Control;
											int Pos_Control_Work = Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos_Control;
											SDL_Rect Orth_Pos_Work_Value = Civil_Gaia_List->Civil_Game_Object_List[Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Pos]->Get_Orth_Pos();
											Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Search_Moving_to_Work = true;
											Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Set_Orth_Pos_Work(Orth_Pos_Work_Value, Unit_Type_Object_Work_Value, Pos_Object_Work_Value, Country_Object_Work_Value, Unit_Type_Control_Work, Pos_Control_Work);
											goto Next_1;
										}
									}
								}
								else //if (Map_UG_Check_Click[Row_Cell_Click][Col_Cell_Click].List_Object_in_Cell[i].Country == Country_Gaia) // Country Gaia, tức là thuộc tự nhiên, đoạn mã này kiểm tra xem liệu người chơi có cho nông dân đi ăn quả hay không.
								{
									cout << "Thoi tan cong" << endl;
									goto Next;
								}
							}
						}
						else
						{
							cout << "yes ........";
							goto Next;
						}
						cout << "OKKKKKKK";
						Next:
						if (!Civil_Player_List.empty() && Choose_Object_Game[0].Country == Country_1 && y_Pos_Click < 600)
						{
							if (Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Unit_Type_Property() != Building)
							{
								Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Disable_Hit_Box();
								Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Moving_To_Work = false;
								Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Going_to_return_resource = false;
								if (Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Resource_Bearing == 0)
								{
									Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Change_Object_Status(Moving);
								}
								else
								{
									Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Change_Object_Status(Carry);
								}
								//Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Object_Status = Moving;
								int x_Pos_Click_Assign = x_Pos_Click;
								int y_Pos_Click_Assign = y_Pos_Click;
								SDL_Rect W_H = Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Get_Orth_Pos();
								Reverse_Convert(x_Pos_Click_Assign, y_Pos_Click_Assign, W_H.w, W_H.h);
								SDL_Rect Orth_Pos_Move = { x_Pos_Click_Assign,y_Pos_Click_Assign,W_H.w,W_H.h };
								//cout << Orth_Pos_Move.y / Orth_Tile_Height << " " << Orth_Pos_Move.x / Orth_Tile_Height << endl;
								Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Set_Orth_Pos_Move(Orth_Pos_Move);
								Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Enable_Search_A_Star();
								Civil_Player_List[0]->Civil_Game_Object_List[Choose_Object_Game[0].Position]->Move(Civil_Player_List[0]->Unit_Dt, Civil_Player_List[0]->Get_Civil_Index(),
									Map_UG_Layer_1, Map_UG_Layer_2, Map_UG_Check_Click, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Choose_Object_Game[0].Position);
							}
						}
					Next_1:;
					}
				
				}
				//{}
			}
			break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (Event.button.button)
			{
			case SDL_BUTTON_LEFT:
				Mouse_Button_Left = false;
				break;
			case SDL_BUTTON_RIGHT:
				Mouse_Button_Right = false;
				break;
			}
			break;
		case SDL_MOUSEMOTION:
		{
			x_Pos_Mouse_Motion = Event.motion.x;
			y_Pos_Mouse_Motion = Event.motion.y;
		}
		}
		Manager::Render_List();
		SDL_Delay(1);
		//SDL_RenderPresent(Renderer);
		//cout << Manager_Game->Map_List_2[1]->Get_Unit_Type();
	}
}

void Manager::Load_Interfac() // Load các bảng bên trên và bên dưới, các bảng chứa thông tin
{
	SDL_Rect Infor_Pos_Sor; // Xác định tọa độ của các bảng trên và dưới
	SDL_Rect Infor_Iso_Pos;
	SDL_Rect Infor_Source_Pos_Sor;
	SDL_Rect Infor_Source_Iso_Sor;
	Infor_Pos_Sor.x = 0;
	Infor_Pos_Sor.y = 0;
	Infor_Pos_Sor.w = 1025;
	Infor_Pos_Sor.h = 127;
	Infor_Iso_Pos.x = 0;
	Infor_Iso_Pos.y = 600;
	Infor_Iso_Pos.w = 1025;
	Infor_Iso_Pos.h = 127;
	Infor_Source_Pos_Sor.x = 0;
	Infor_Source_Pos_Sor.y = 0;
	Infor_Source_Pos_Sor.w = 1025;
	Infor_Source_Pos_Sor.h = 21;
	Infor_Source_Iso_Sor.x = 0;
	Infor_Source_Iso_Sor.y = 0;
	Infor_Source_Iso_Sor.w = 1025;
	Infor_Source_Iso_Sor.h = 21;
	SDL_RenderCopy(Renderer, Infor_Source_Texture, &Infor_Source_Pos_Sor, &Infor_Source_Iso_Sor);
	SDL_RenderCopy(Renderer, Infor_Texture, &Infor_Pos_Sor, &Infor_Iso_Pos);
	if (!Choose_Object_Game.empty())
	{
		//cout << "NO";
		if (Choose_Object_Game[0].Unit_Type_Control == Player)
		{
			for (int i = 0; i < Civil_Player_List.size(); i++)
			{
				//cout << "NO";
				if (Civil_Player_List[i]->Get_Civil_Index() == Country_1)
				{
					for (int j = 0; j <= Iron_Age; j++)
					{
						Civil_Player_List[i]->Check_Tech_Display(j, Choose_Object_Game[0]);
					}
					for (int j = 0; j <= Build_3_3; j++)
					{
						Civil_Player_List[i]->Check_Unit_Display(j, Choose_Object_Game[0], Sub_Menu);
					}
					for (int j = 0; j <= Stop_Train; j++)
					{
						Civil_Player_List[i]->Check_Button_Display(j, Sub_Menu, Choose_Object_Game[0]);
					}

				}
			}
		}
	}
	
	/*for (int i = 0; i < Choose_Object_Game.size(); i++)
	{
		if (Choose_Object_Game[i].Country == Country_1)
		{
			for (int  j = 0; j < Civil_Player_List.size(); j++)
			{
				if (Civil_Player_List[j]->Get_Civil_Index() == Country_1 &&
					Civil_Player_List[j]->Civil_Game_Object_List[Choose_Object_Game[i].Position]->Get_Unit_Type() == Town_Center_1_M_1 &&
					Civil_Player_List[j]->Get_Epoch() == Epoch_Stone_Age &&
					i == 0)
				{
					if ()
					{
						SDL_Rect Assign_Rect = { 3380, 0, 52, 52 };
						//cout << Button_6.x << Button_6.y << Button_6.w << Button_6.h << endl;
						SDL_RenderCopy(Renderer, Techs_Texture, &Assign_Rect, &Button_6);
					}
					//cout << "yes";
					
				}
			}
		}
	}*/
}

void Manager::Draw_Slection(Game_Object* Game_Object_Draw) // Vẽ hình thoi màu trắng bên dưới đối tượng được chọn nhàm xác định đối tượng này đang được chọn
{
	/*Iso_Pos_Object.x += Iso_Pos_Object.w / 2;
	int x_A = Iso_Pos_Object.x; // Xác định hoành độ của A
	int y_A = Iso_Pos_Object.y + (Iso_Pos_Object.h - (Iso_Pos_Object.w / 2) * tan(3.14 / 6)); // Xác định tung độ của A
	int x_B = Iso_Pos_Object.x + Iso_Pos_Object.w / 2;
	int y_B = Iso_Pos_Object.y + (Iso_Pos_Object.h - (Iso_Pos_Object.w) * tan(3.14 / 6));
	int x_C = x_A + Iso_Pos_Object.w;
	int y_C = y_A;
	int x_D = x_A + Iso_Pos_Object.w / 2;
	int y_D = Iso_Pos_Object.y + Iso_Pos_Object.h;*/

	SDL_Rect Iso_Pos_Object = Game_Object_Draw->Iso_Pos_Selection;
	if (Game_Object_Draw->Get_Unit_Type_Property() != Building)
	{
		Iso_Pos_Object.y -= (Iso_Pos_Object.w / 2) * tan(3.14 / 6);
	}
	
	int x_A = Iso_Pos_Object.x; // Xác định hoành độ của A
	int y_A = Iso_Pos_Object.y; //+ (Iso_Pos_Object.h - (Iso_Pos_Object.w / 2) * tan(3.14 / 6)); // Xác định tung độ của A
	int x_B = Iso_Pos_Object.x + Iso_Pos_Object.w / 2;
	int y_B = Iso_Pos_Object.y + (Iso_Pos_Object.w / 2) * tan(3.14 / 6); // -(Iso_Pos_Object.w) * tan(3.14 / 6));
	int x_C = x_A; //+ Iso_Pos_Object.w;
	int y_C = y_A + (Iso_Pos_Object.w) * tan(3.14 / 6);
	int x_D = x_A - Iso_Pos_Object.w / 2;
	int y_D = Iso_Pos_Object.y + (Iso_Pos_Object.w / 2) * tan(3.14 / 6);

	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(Renderer, x_A, y_A, x_B, y_B); // Vẽ đoạn AB
	SDL_RenderDrawLine(Renderer, x_B, y_B, x_C, y_C);
	SDL_RenderDrawLine(Renderer, x_C, y_C, x_D, y_D);
	SDL_RenderDrawLine(Renderer, x_D, y_D, x_A, y_A);
}

void Manager::Load_Test()
{
	SDL_Rect Infor_Pos_Sor;
	SDL_Rect Infor_Iso_Pos;
	Infor_Pos_Sor.x = 0;
	Infor_Pos_Sor.y = 0;
	Infor_Pos_Sor.w = 1025;
	Infor_Pos_Sor.h = 127;
	Infor_Iso_Pos.x = 0;
	Infor_Iso_Pos.y = 600;
	Infor_Iso_Pos.w = 1025;
	Infor_Iso_Pos.h = 127;
	SDL_RenderCopy(Renderer, Test_Texture, &Infor_Pos_Sor, &Infor_Iso_Pos);
}

void Manager::Init_Map_UG() 
{
	// Map UG này xử lý va chạm
	for (int i = 0; i < Civil_Gaia_List->Civil_Game_Object_List.size(); i++) // Duyệt qua các đối tượng của Gaia, cây cối ,...
	{
		if (Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Unit_Type() != Grass)
		{
			//cout << Gaia_List[i]->Size_Number_Cell  << endl;
			//cout << Civil_Player_List[Civil_x]->Civil_Game_Object_List.size();
			int m = Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Orth_Pos().x / Cell_Size;
			int m_w = (Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Orth_Pos().x + Civil_Gaia_List->Civil_Game_Object_List[i]->Size_Number_Cell * Orth_Tile_Height) / Cell_Size;
			int n = Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Orth_Pos().y / Cell_Size;
			int n_h = (Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Orth_Pos().y + Civil_Gaia_List->Civil_Game_Object_List[i]->Size_Number_Cell * Orth_Tile_Height) / Cell_Size;
			for (int j = m; j <= m_w; j++)
			{
				for (int k = n; k <= n_h; k++)
				{
					Cell_Object Cell_Object_Assign;
					Cell_Object_Assign.Object_Type = Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Unit_Type();
					Cell_Object_Assign.Pos = i;
					Cell_Object_Assign.Country = Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Country(); // Đưa vào List Object trong Mảng thông số về Country
					Cell_Object_Assign.Orth_Pos = Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Orth_Pos(); // Đưa vào List Object trong ô của Mảng Uniform Grid thông số về tọa độ và vị trí của đối tượng
					Cell_Object_Assign.Unit_Type_Control = Civil_Gaia_List->Civil_Game_Object_List[i]->Unit_Type_Control;
					Cell_Object_Assign.Pos_Control = Civil_Gaia_List->Civil_Game_Object_List[i]->Pos_Control;
					Cell_Contain_Object Cell_Contain_Object_Assign;
					Cell_Contain_Object_Assign.Col = j;
					Cell_Contain_Object_Assign.Row = k;
					Cell_Contain_Object_Assign.Pos = Map_UG_Layer_2[k][j].List_Object_in_Cell.size();
					//Cell_Contain_Object_Assign.Object_Rect=List_Object[i]->Rect;
					Map_UG_Layer_2[k][j].List_Object_in_Cell.push_back(Cell_Object_Assign);
					Civil_Gaia_List->Civil_Game_Object_List[i]->List_Cell_Contain_Object.push_back(Cell_Contain_Object_Assign);
					//cout <<i<<" "<< k << " " << j << endl;
				}
			}
			
		}
	
	}

	for (int Civil_x = 0; Civil_x < Civil_Player_List.size(); Civil_x++) // Duyệt qua danh sách các nước của Computer, gán các đối tượng vào các ô tương ứng
	{
		for (int i = 0; i < Civil_Player_List[Civil_x]->Civil_Game_Object_List.size(); i++)
		{
			//cout << Civil_Player_List[Civil_x]->Civil_Game_Object_List.size();
			int m = Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Orth_Pos().x / Cell_Size;
			int m_w = (Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Orth_Pos().x + Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Size_Number_Cell * Orth_Tile_Height) / Cell_Size;
			int n = Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Orth_Pos().y / Cell_Size;
			int n_h = (Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Orth_Pos().y + Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Size_Number_Cell * Orth_Tile_Height) / Cell_Size;
			for (int j = m; j <= m_w; j++)
			{
				for (int k = n; k <= n_h; k++)
				{
					Cell_Object Cell_Object_Assign;
					Cell_Object_Assign.Object_Type = Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Unit_Type();
					Cell_Object_Assign.Pos = i;
					Cell_Object_Assign.Country = Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Country(); // Đưa vào List Object trong Mảng thông số về Country
					Cell_Object_Assign.Unit_Type_Control = Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Unit_Type_Control;
					Cell_Object_Assign.Pos_Control = Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Pos_Control;
					Cell_Object_Assign.Orth_Pos = Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Orth_Pos(); // Đưa vào List Object trong ô của Mảng Uniform Grid thông số về tọa độ và vị trí của đối tượng
					Cell_Contain_Object Cell_Contain_Object_Assign;
					Cell_Contain_Object_Assign.Col = j;
					Cell_Contain_Object_Assign.Row = k;
					Cell_Contain_Object_Assign.Pos = Map_UG_Layer_2[k][j].List_Object_in_Cell.size();
					//Cell_Contain_Object_Assign.Object_Rect=List_Object[i]->Rect;
					Map_UG_Layer_2[k][j].List_Object_in_Cell.push_back(Cell_Object_Assign);
					Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->List_Cell_Contain_Object.push_back(Cell_Contain_Object_Assign);
					//cout <<i<<" "<< j << " " << k << endl;
				}
			}
		}

	}
	for (int Civil_x = 0; Civil_x < Civil_Computer_List.size(); Civil_x++) // Duyệt qua danh sách các nước của người chơi, gán các đối tượng vào ô tương ứng
	{
		for (int i = 0; i < Civil_Computer_List[Civil_x]->Civil_Game_Object_List.size(); i++)
		{
			//cout << "OK";
			int m = Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Orth_Pos().x / Cell_Size; // Lấy ra ô đầu tiên thuộc đối tượng
			int m_w = (Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Orth_Pos().x + Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Size_Number_Cell * Orth_Tile_Height) / Cell_Size; // Lấy ra ô cuối cùng thuộc đối tượng, vì đối tượng là hình chữ nhật lên phân bố theo dọc các ô.
			int n = Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Orth_Pos().y / Cell_Size;
			int n_h = (Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Orth_Pos().y + Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Size_Number_Cell * Orth_Tile_Height) / Cell_Size;
			for (int j = m; j <= m_w; j++)
			{
				for (int k = n; k <= n_h; k++)
				{
					Cell_Object Cell_Object_Assign;
					Cell_Object_Assign.Object_Type = Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Unit_Type();
					Cell_Object_Assign.Pos = i;
					Cell_Object_Assign.Country = Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Country();
					Cell_Object_Assign.Orth_Pos = Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Orth_Pos(); // Đưa vào List Object trong ô của Mảng Uniform Grid thông số về tọa độ và vị trí của đối tượng
					Cell_Object_Assign.Unit_Type_Control = Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Unit_Type_Control;
					Cell_Object_Assign.Pos_Control = Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Pos_Control;
					Cell_Contain_Object Cell_Contain_Object_Assign;
					Cell_Contain_Object_Assign.Col = j;
					Cell_Contain_Object_Assign.Row = k;
					Cell_Contain_Object_Assign.Pos = Map_UG_Layer_2[k][j].List_Object_in_Cell.size();
					//Cell_Contain_Object_Assign.Object_Rect=List_Object[i]->Rect;
					Map_UG_Layer_2[k][j].List_Object_in_Cell.push_back(Cell_Object_Assign);
					Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->List_Cell_Contain_Object.push_back(Cell_Contain_Object_Assign);
					//cout << i << " " << j << " " << k << endl;
					//cout << Map_UG_Layer_2[k][j].List_Object_in_Cell.size() << endl;
					//cout << Map_UG_Layer_2[k][j].List_Object_in_Cell.size();
				}
			}
				
			//cout << n << " " << m << endl;
		}
	}
	// Phần này nhằm tạo Map_UG xử lý click chuột

	for (int i = 0; i < Civil_Gaia_List->Civil_Game_Object_List.size(); i++) // Duyệt qua các đối tượng của Gaia, cây cối ,...
	{
		if (Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Unit_Type() != Grass)
		{
			//cout << Civil_Player_List[Civil_x]->Civil_Game_Object_List.size();
			int m = Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Iso_Pos().x / Cell_Size;
			int m_w = (Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Iso_Pos().x + Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Orth_Pos().w) / Cell_Size;
			int n = Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Iso_Pos().y / Cell_Size;
			int n_h = (Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Iso_Pos().y + Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Orth_Pos().h) / Cell_Size;
			for (int j = m; j <= m_w; j++)
			{
				for (int k = n; k <= n_h; k++)
				{
					Cell_Object Cell_Object_Assign;
					Cell_Object_Assign.Object_Type = Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Unit_Type();
					Cell_Object_Assign.Pos = i;
					Cell_Object_Assign.Country = Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Country(); // Đưa vào List Object trong Mảng thông số về Country
					Cell_Object_Assign.Orth_Pos = Civil_Gaia_List->Civil_Game_Object_List[i]->Get_Orth_Pos(); // Đưa vào List Object trong ô của Mảng Uniform Grid thông số về tọa độ và vị trí của đối tượng
					Cell_Object_Assign.Unit_Type_Control = Civil_Gaia_List->Civil_Game_Object_List[i]->Unit_Type_Control;
					Cell_Object_Assign.Pos_Control = Civil_Gaia_List->Civil_Game_Object_List[i]->Pos_Control;
					Cell_Contain_Object Cell_Contain_Object_Assign;
					Cell_Contain_Object_Assign.Col = j;
					Cell_Contain_Object_Assign.Row = k;
					Cell_Contain_Object_Assign.Pos = Map_UG_Check_Click[k][j].List_Object_in_Cell.size();
					//Cell_Contain_Object_Assign.Object_Rect=List_Object[i]->Rect;
					Map_UG_Check_Click[k][j].List_Object_in_Cell.push_back(Cell_Object_Assign);
					Civil_Gaia_List->Civil_Game_Object_List[i]->List_Cell_Contain_Object_Click.push_back(Cell_Contain_Object_Assign);
					//cout <<i<<" "<< j << " " << k << endl;
				}
			}
		}
		
	}

	for (int Civil_x = 0; Civil_x < Civil_Player_List.size(); Civil_x++) // Duyệt qua danh sách các nước của Computer, gán các đối tượng vào các ô tương ứng
	{
		for (int i = 0; i < Civil_Player_List[Civil_x]->Civil_Game_Object_List.size(); i++)
		{
			//cout << Civil_Player_List[Civil_x]->Civil_Game_Object_List.size();
			int m = Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Iso_Pos().x / Cell_Size;
			int m_w = (Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Iso_Pos().x + Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Iso_Pos().w ) / Cell_Size;
			int n = Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Iso_Pos().y / Cell_Size;
			int n_h = (Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Iso_Pos().y + Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Iso_Pos().h ) / Cell_Size;
			for (int j = m; j <= m_w; j++)
			{
				for (int k = n; k <= n_h; k++)
				{
					Cell_Object Cell_Object_Assign;
					Cell_Object_Assign.Object_Type = Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Unit_Type();
					Cell_Object_Assign.Pos = i;
					Cell_Object_Assign.Country = Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Country(); // Đưa vào List Object trong Mảng thông số về Country
					Cell_Object_Assign.Orth_Pos = Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Get_Orth_Pos(); // Đưa vào List Object trong ô của Mảng Uniform Grid thông số về tọa độ và vị trí của đối tượng
					Cell_Object_Assign.Unit_Type_Control = Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Unit_Type_Control;
					Cell_Object_Assign.Pos_Control = Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->Pos_Control;
					Cell_Contain_Object Cell_Contain_Object_Assign;
					Cell_Contain_Object_Assign.Col = j;
					Cell_Contain_Object_Assign.Row = k;
					Cell_Contain_Object_Assign.Pos = Map_UG_Check_Click[k][j].List_Object_in_Cell.size();
					//Cell_Contain_Object_Assign.Object_Rect=List_Object[i]->Rect;
					Map_UG_Check_Click[k][j].List_Object_in_Cell.push_back(Cell_Object_Assign);
					Civil_Player_List[Civil_x]->Civil_Game_Object_List[i]->List_Cell_Contain_Object_Click.push_back(Cell_Contain_Object_Assign);
					//cout <<i<<" "<< j << " " << k << endl;
				}
			}
				
		}

	}
	for (int Civil_x = 0; Civil_x < Civil_Computer_List.size(); Civil_x++) // Duyệt qua danh sách các nước của người chơi, gán các đối tượng vào ô tương ứng
	{
		for (int i = 0; i < Civil_Computer_List[Civil_x]->Civil_Game_Object_List.size(); i++)
		{
			//cout << "OK";
			int m = Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Iso_Pos().x / Cell_Size; // Lấy ra ô đầu tiên thuộc đối tượng
			int m_w = (Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Iso_Pos().x + Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Iso_Pos().w ) / Cell_Size; // Lấy ra ô cuối cùng thuộc đối tượng, vì đối tượng là hình chữ nhật lên phân bố theo dọc các ô.
			int n = Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Iso_Pos().y / Cell_Size;
			int n_h = (Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Iso_Pos().y + Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Iso_Pos().h ) / Cell_Size;
			for (int j = m; j <= m_w; j++)
			{
				for (int k = n; k <= n_h; k++)
				{
					Cell_Object Cell_Object_Assign;
					Cell_Object_Assign.Object_Type = Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Unit_Type();
					Cell_Object_Assign.Pos = i;
					Cell_Object_Assign.Country = Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Country();
					Cell_Object_Assign.Orth_Pos = Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Get_Orth_Pos(); // Đưa vào List Object trong ô của Mảng Uniform Grid thông số về tọa độ và vị trí của đối tượng
					Cell_Object_Assign.Unit_Type_Control = Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Unit_Type_Control;
					Cell_Object_Assign.Pos_Control = Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->Pos_Control;
					Cell_Contain_Object Cell_Contain_Object_Assign;
					Cell_Contain_Object_Assign.Col = j;
					Cell_Contain_Object_Assign.Row = k;
					Cell_Contain_Object_Assign.Pos = Map_UG_Check_Click[k][j].List_Object_in_Cell.size();
					//Cell_Contain_Object_Assign.Object_Rect=List_Object[i]->Rect;
					Map_UG_Check_Click[k][j].List_Object_in_Cell.push_back(Cell_Object_Assign);
					Civil_Computer_List[Civil_x]->Civil_Game_Object_List[i]->List_Cell_Contain_Object_Click.push_back(Cell_Contain_Object_Assign);
					//cout << i << " " << j << " " << k << endl;
					//cout << Map_UG_Layer_2[k][j].List_Object_in_Cell.size();
				}
				//cout << n << " " << m << endl;
			}
				
		}
	}
	//cout << Check_Cell_Empty(3, 5, Map_UG_Layer_2) << endl;
	
}
/*void Update_Cell(Cell_Uniform_Grid Map[Number_Row_Map][Number_Col_Map], Game_Object* Game_Object_Check, int Pos_in_List_Game_Object) // Update các ô chứa đối tượng trong trường hợp đối tượng di chuyển
{
	cout << "Update";
	// Game Object Check : Đối tượng cần để kiểm tra xem
	int a = Game_Object_Check->Get_Orth_Pos().x / Cell_Size;
	int a_w = (Game_Object_Check->Get_Orth_Pos().x + Game_Object_Check->Get_Orth_Pos().w) / Cell_Size;
	int b = Game_Object_Check->Get_Orth_Pos().y / Cell_Size;
	int b_h = (Game_Object_Check->Get_Orth_Pos().y + Game_Object_Check->Get_Orth_Pos().h) / Cell_Size;
    vector<Cell_Contain_Object> Last_Cell;
    vector<Cell_Contain_Object> Current_Cell;
    bool Check=false;
	for (int s = 0; s < Game_Object_Check->List_Cell_Contain_Object.size(); s++)
        {
		Check = false;
		for (int p = a; p <= a_w; p++)
		{
			for (int q = b; q <= b_h; q++)
			{
				if (Game_Object_Check->List_Cell_Contain_Object[s].Col == p && Game_Object_Check->List_Cell_Contain_Object[s].Row == q)
				{
					Check = true;
				}
			}
		}	
		if (!Check)
            {
			for (int g = 0; g < Map[Game_Object_Check->List_Cell_Contain_Object[s].Row][Game_Object_Check->List_Cell_Contain_Object[s].Col].List_Object_in_Cell.size(); g++)
                {
					if (Map[Game_Object_Check->List_Cell_Contain_Object[s].Row][Game_Object_Check->List_Cell_Contain_Object[s].Col].List_Object_in_Cell[s].Pos == Pos_in_List_Game_Object)
                    {
						Map[Game_Object_Check->List_Cell_Contain_Object[s].Row][Game_Object_Check->List_Cell_Contain_Object[s].Col].List_Object_in_Cell[s].Object_Type = -1;
                    }
                }
            }
        }
	Check = false;
	for (int p = a; p <= a_w; p++)
	{
		for (int q = b; q <= b_h; q++)
		{
			Check = false;
			for (int s = 0; s < Game_Object_Check->List_Cell_Contain_Object.size(); s++)
			{
				if (Game_Object_Check->List_Cell_Contain_Object[s].Col == p && Game_Object_Check->List_Cell_Contain_Object[s].Row == q)
				{
					Check = true;
				}
			}
			if (!Check)
			{
				for (int k = 0; k < Map[q][p].List_Object_in_Cell.size(); k++)
				{
					if (Map[q][p].List_Object_in_Cell[k].Object_Type == -1)
					{
						Map[q][p].List_Object_in_Cell[k].Object_Type = Game_Object_Check->Get_Unit_Type();
						Map[q][p].List_Object_in_Cell[k].Pos = Pos_in_List_Game_Object;
					}
				}
			}
		}
	}
	Game_Object_Check->List_Cell_Contain_Object.clear();
	for (int p = a; p <= a_w; p++)
	{
		for (int q = b; q <= b_h; q++)
		{
			Cell_Contain_Object Cell_Contain_Object_Assign;
			Cell_Contain_Object_Assign.Col = p;
			Cell_Contain_Object_Assign.Row = q;
			Game_Object_Check->List_Cell_Contain_Object.push_back(Cell_Contain_Object_Assign);
		}
	}
}*/
