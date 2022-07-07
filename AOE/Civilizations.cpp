#include "Civilizations.h"

void Civil_Computer::Civil_Develop()
{
	if (Number_Villager < Number_Villager_Max)
	{
		Train_Unit(Villager);
	}
	if (Number_Clubman < Number_Clubman_Max)
	{
		//cout << "yes";
		Train_Unit(Clubman);
	}
}

void Civil_Computer::Train_Unit(int Unit_Train)
{
	cout << Amount_Food << endl;
	switch (Unit_Train)
	{
	case Villager:
	{
		//cout << "yes";
		if (!Pos_Town_Center_List.empty())
		{
			if (Number_Villager < Number_Villager_Max)
			{
				
				if (Pay_Money(Unit_Dt[Villager].Cost_Food, Unit_Dt[Villager].Cost_Gold, Unit_Dt[Villager].Cost_Wood, Unit_Dt[Villager].Cost_Stone))
				{
					Civil_Game_Object_List[Pos_Town_Center_List[0]]->Add_to_Train_Unit_Queue(Villager);
					Number_Villager++;
				}

			}
		}
		break;
	}
	case Clubman:
	{
		if (!Pos_Barracks_List.empty())
		{
			if (Number_Clubman < Number_Clubman_Max)
			{

				if (Pay_Money(Unit_Dt[Clubman].Cost_Food, Unit_Dt[Clubman].Cost_Gold, Unit_Dt[Clubman].Cost_Wood, Unit_Dt[Clubman].Cost_Stone))
				{
					//cout << "yes";
					Civil_Game_Object_List[Pos_Barracks_List[0]]->Add_to_Train_Unit_Queue(Clubman);
					Number_Clubman++;
				}

			}
		}
		break;
	}
	default:
		break;
	}
	return;
}

void Civil_Player::Handle_Event()
{
}

void Civil::Set_Civil_Name()
{
}

void Civil::Set_Civil_Index(int Index)
{
	Civil::Civil_Index = Index;
}

void Civil::Set_Civil_Name(int Civil_Name)
{
	this->Civil_Name = Civil_Name;
}

int Civil::Get_Civil_Name()
{
	return Civil_Name;
}

void Civil::Set_Techs()
{
	memset(Civil::Techs_Disable, false, sizeof(Techs_Disable));
	memset(Civil::Tech_Researching, false, sizeof(Tech_Researching));
	memset(Civil::Techs_Available, false, sizeof(Techs_Available));
}

void Civil::Set_Tech_Dt()
{
	Tech_Dt[Tool_Age].Cost_Food = 500;
	Tech_Dt[Tool_Age].Cost_Gold = 0;
	Tech_Dt[Tool_Age].Icon_Iso_Pos = { 135,665,52,52 };
	Tech_Dt[Tool_Age].Icon_Pos_Sor = { 3380,0,52,52 };
	Tech_Dt[Tool_Age].Research_Location = Town_Center;
	Tech_Dt[Tool_Age].Sub_Menu_Required = -1;
	Tech_Dt[Tool_Age].Time_Research = 20;

	Tech_Dt[Bronze_Age].Cost_Food = 800;
	Tech_Dt[Bronze_Age].Icon_Iso_Pos = { 135,665,52,52 };
	Tech_Dt[Bronze_Age].Icon_Pos_Sor = { 3432,0,52,52 };
	Tech_Dt[Bronze_Age].Research_Location = Town_Center;
	Tech_Dt[Bronze_Age].Required_Tech.push_back(Tool_Age);
	Tech_Dt[Bronze_Age].Sub_Menu_Required = -1;
}

void Civil::Set_Unit_Dt()
{
	memset(Unit, true, sizeof(Unit));
	memset(Unit_Disable, false, sizeof(Unit_Disable));
	/*Unit_Dt[Villager].Cost_Food = 50;
	Unit_Dt[Villager].Cost_Gold = 0;
	Unit_Dt[Villager].Cost_Stone = 0;
	Unit_Dt[Villager].Cost_Wood = 0;
	Unit_Dt[Villager].Damage = 3;
	Unit_Dt[Villager].Hit_Point = 200;
	Unit_Dt[Villager].Speed = 1;
	Unit_Dt[Villager].Height = 38;
	Unit_Dt[Villager].Weight = 21;
	Unit_Dt[Villager].Icon_Pos_Sor = { 0,0,52,51 };
	Unit_Dt[Villager].Icon_Iso_Pos = { 135,605,52,51 };
	Unit_Dt[Villager].Train_Location = Town_Center;
	Unit_Dt[Villager].Time_Train = 20;
	Unit_Dt[Villager].Time_Next_Attacking = 2000;
	Unit_Dt[Villager].Time_Next_Attacking_Sprite = 200;*/
	SDL_Rect Icon_Pos_Sor = { 0,0,52,51 };
	SDL_Rect Icon_Iso_Pos = { 135,605,52,51 };
	Set_Unit(Villager, "Villager", Villager_Base, 0.3, Icon_Pos_Sor, Icon_Iso_Pos, 50, 0, 0, 0, 21, 38, 100, 3, 0, 0, 1, 200, 200, 300, 30, 300, 30, 300, 30, 270, 30, 100, 30, 20000, 2000, Town_Center, 2000, -1);
	if (Civil_Name == Egyptian)
	{
		Unit_Dt[Villager].Damage = 10;
	}
	Set_Unit(Woodcutter, "Woodcutter", Villager_Base, 0.3, Icon_Pos_Sor, Icon_Iso_Pos, 50, 0, 0, 0, 21, 38, 25, 3, 0, 0, 1, 200, 200, 300, 30, 300, 30, 300, 30, 270, 30, 100, 30, 20000, 2000, -1, 2000, -1);
	Set_Unit(Builder, "Builder", Villager_Base, 0.3, Icon_Pos_Sor, Icon_Iso_Pos, 50, 0, 0, 0, 21, 38, 25, 3, 0, 0, 1, 200, 200, 300, 30, 300, 30, 300, 30, 270, 30, 100, 30, 20000, 2000, -1, 2000, -1);
	Set_Unit(Stone_Miner, "Stone Miner", Villager_Base, 0.3, Icon_Pos_Sor, Icon_Iso_Pos, 50, 0, 0, 0, 21, 38, 25, 3, 0, 0, 1, 200, 200, 300, 30, 300, 30, 300, 30, 270, 30, 100, 30, 20000, 2000, -1, 2000, -1);
	Set_Unit(Gold_Miner, "Gold Miner", Villager_Base, 0.3,Icon_Pos_Sor, Icon_Iso_Pos, 50, 0, 0, 0, 21, 38, 25, 3, 0, 0, 1, 200, 200, 300, 30, 300, 30, 300, 30, 270, 30, 100, 30, 20000, 2000, -1, 2000, -1);
	Icon_Pos_Sor = { 104,0,52,51 };
	Icon_Iso_Pos = { 135,605,52,51 };
	Set_Unit(Clubman, "Clubman", Base_Melee, 0.3, Icon_Pos_Sor, Icon_Iso_Pos, 50, 0, 0, 0, 34, 44, 25, 3, 0, 0, 1, 200, 200, 300, 30, 300, 30, 300, 30, 270, 30, 100, 30, 20000, 2000, Barracks, 200, -1);
	Icon_Pos_Sor = { 156,0,52,52 };
	Icon_Iso_Pos = { 190,605,52,52 };
	Set_Unit(Barracks, "Barracks", Building, 2.9, Icon_Pos_Sor, Icon_Iso_Pos, 120, 0, 0, 0, 34, 44, 350, 0, 0, 0, 1, 200, 200, 300, 30, 300, 30, 300, 30, 270, 30, 100, 30, 20000, 2000, Villager, 2000, Page_1_Build_Construct);
	Icon_Pos_Sor = { 1716,0,52,52 };
	Icon_Iso_Pos = { 135,605,52,52 };
	Set_Unit(Town_Center, "Town Center", Building, 2.9,Icon_Pos_Sor, Icon_Iso_Pos, 200, 0, 0, 0, 165, 100, 600, 3, 0, 0, 1, 200, 200, 300, 30, 300, 30, 300, 30, 270, 30, 100, 30, 20000, 2000, -1, 2000, Page_1_Build_Construct);
	Icon_Pos_Sor = { 780,0,52,52 };
	Icon_Iso_Pos = { 135,605,52,52 };
	Set_Unit(House, "House", Building, 0.9, Icon_Pos_Sor, Icon_Iso_Pos, 0, 0, 30, 0, 81, 42, 75, 3, 0, 0, 0, 200, 200, 300, 30, 300, 30, 300, 30, 270, 30, 100, 30, 20000, 2000, Villager, 2000, Page_1_Build_Construct);
	Icon_Pos_Sor = { 780,0,52,52 };
	Icon_Iso_Pos = { 135,605,52,52 };
	Set_Unit(House, "House", Building, 0.9, Icon_Pos_Sor, Icon_Iso_Pos, 0, 0, 30, 0, 81, 42, 75, 3, 0, 0, 0, 200, 200, 300, 30, 300, 30, 300, 30, 270, 30, 100, 30, 20000, 2000, Villager, 2000, Page_1_Build_Construct);


	/*Unit_Dt[House].Cost_Food = 0;
	Unit_Dt[House].Unit_Type_Property = Building;
	Unit_Dt[House].Cost_Gold = 0;
	Unit_Dt[House].Cost_Stone = 0;
	Unit_Dt[House].Cost_Wood = 30;
	Unit_Dt[House].Damage = 0;
	Unit_Dt[House].Hit_Point = 75;
	Unit_Dt[House].Speed = 0;
	Unit_Dt[House].Height = 42;
	Unit_Dt[House].Weight = 81;
	Unit_Dt[House].Icon_Pos_Sor = { 780,0,52,52 };
	Unit_Dt[House].Icon_Iso_Pos = { 135,605,52,52 };
	Unit_Dt[House].Train_Location = Villager;
	Unit_Dt[House].Sub_Menu_Required = Page_1_Build_Construct;*/
	/*Unit_Dt[Town_Center].Cost_Food = 0;
	Unit_Dt[Town_Center].Cost_Gold = 0;
	Unit_Dt[Town_Center].Cost_Stone = 0;
	Unit_Dt[Town_Center].Cost_Wood = 200;
	Unit_Dt[Town_Center].Damage = 0;
	Unit_Dt[Town_Center].Hit_Point = 200;
	Unit_Dt[Town_Center].Speed = 0;
	Unit_Dt[Town_Center].Height = 52;
	Unit_Dt[Town_Center].Weight = 52;
	Unit_Dt[Town_Center].Icon_Pos_Sor = { 1716,0,52,52 };
	Unit_Dt[Town_Center].Icon_Iso_Pos = { 135,605,52,52 };
	Unit_Dt[Town_Center].Train_Location = Villager;
	Unit_Dt[Town_Center].Sub_Menu_Required = Page_1_Build_Construct;*/
	Unit_Dt[Mine_Gold].Cost_Food = 0;
	Unit_Dt[Mine_Gold].Cost_Gold = 0;
	Unit_Dt[Mine_Gold].Cost_Stone = 0;
	Unit_Dt[Mine_Gold].Cost_Wood = 200;
	Unit_Dt[Mine_Gold].Damage = 0;
	Unit_Dt[Mine_Gold].Hit_Point = 200;
	Unit_Dt[Mine_Gold].Speed = 0;
	Unit_Dt[Mine_Gold].Height = 52;
	Unit_Dt[Mine_Gold].Weight = 52;
	Unit_Dt[Mine_Gold].Icon_Pos_Sor = { 2028,0,52,52 };
	Unit_Dt[Mine_Gold].Icon_Iso_Pos = { 135,605,52,52 };
	Unit_Dt[Mine_Stone].Icon_Pos_Sor = { 1976,0,52,52 };
	Unit_Dt[Mine_Stone].Icon_Iso_Pos = { 135,605,52,52 };
	Unit_Dt[Tree_01].Weight = 63;
	Unit_Dt[Tree_01].Height = 70;
	//Unit_Dt[Mine_Gold].Train_Location = Villager;
	//Unit_Dt[Mine_Gold].Sub_Menu_Required = Page_1_Build_Construct;
}

void Civil::Set_Unit(int Unit_Type_Value, string Unit_Type_Name_Value, int Unit_Type_Property_Value, double Size_Number_Cell_Value, SDL_Rect Icon_Pos_Sor_Value, SDL_Rect Icon_Iso_Pos_Value, int Cost_Food_Value, int Cost_Gold_Value, int Cost_Wood_Value, int Cost_Stone_Value, int Weight_Value, int Height_Value, int Hit_Point_Value, int Damage_Value, int Armor_Value, int Attack_Range_Value, int Speed_Value, int T_N_Standing_Value, int T_N_Standing_Sprite_Value, int T_N_Moving_Value, int T_N_Moving_Sprite_Value, int T_N_Carry_Value, int T_N_Carry_Sprite_Value, int T_N_Working_Value, int T_N_Working_Sprite_Value, int T_N_Attacking_Value, int T_N_Attacking_Sprite_Value, int T_N_Death_Value, int T_N_Death_Sprite_Value, int T_N_Dead_Value, int T_N_Dead_Sprite_Value, int Train_Location_Value, int Time_Train_Value, int Sub_Menu_Required_Value)
{
	Unit_Dt[Unit_Type_Value].Unit_Type_Name = Unit_Type_Name_Value;
	Unit_Dt[Unit_Type_Value].Unit_Type_Property = Unit_Type_Property_Value;
	Unit_Dt[Unit_Type_Value].Size_Number_Cell = Size_Number_Cell_Value;
	Unit_Dt[Unit_Type_Value].Icon_Iso_Pos = Icon_Iso_Pos_Value;
	Unit_Dt[Unit_Type_Value].Icon_Pos_Sor = Icon_Pos_Sor_Value;
	Unit_Dt[Unit_Type_Value].Cost_Food = Cost_Food_Value;
	Unit_Dt[Unit_Type_Value].Cost_Gold = Cost_Gold_Value;
	Unit_Dt[Unit_Type_Value].Cost_Wood = Cost_Wood_Value;
	Unit_Dt[Unit_Type_Value].Cost_Stone = Cost_Stone_Value;
	Unit_Dt[Unit_Type_Value].Weight = Weight_Value;
	Unit_Dt[Unit_Type_Value].Height = Height_Value;
	Unit_Dt[Unit_Type_Value].Hit_Point = Hit_Point_Value;
	Unit_Dt[Unit_Type_Value].Damage = Damage_Value;
	Unit_Dt[Unit_Type_Value].Armor = Armor_Value;
	Unit_Dt[Unit_Type_Value].Attack_Range = Attack_Range_Value;
	Unit_Dt[Unit_Type_Value].Speed = Speed_Value;
	Unit_Dt[Unit_Type_Value].Time_Next_Standing = T_N_Standing_Value;
	Unit_Dt[Unit_Type_Value].Time_Next_Standing_Sprite = T_N_Standing_Sprite_Value;
	Unit_Dt[Unit_Type_Value].Time_Next_Moving = T_N_Moving_Value;
	Unit_Dt[Unit_Type_Value].Time_Next_Moving_Sprite = T_N_Moving_Sprite_Value;
	Unit_Dt[Unit_Type_Value].Time_Next_Carry = T_N_Carry_Value;
	Unit_Dt[Unit_Type_Value].Time_Next_Carry_Sprite = T_N_Carry_Sprite_Value;
	Unit_Dt[Unit_Type_Value].Time_Next_Working = T_N_Working_Value;
	Unit_Dt[Unit_Type_Value].Time_Next_Working_Sprite = T_N_Working_Sprite_Value;
	Unit_Dt[Unit_Type_Value].Time_Next_Attacking = T_N_Attacking_Value;
	Unit_Dt[Unit_Type_Value].Time_Next_Attacking_Sprite = T_N_Attacking_Sprite_Value;
	Unit_Dt[Unit_Type_Value].Time_Next_Death = T_N_Death_Value;
	Unit_Dt[Unit_Type_Value].Time_Next_Death_Sprite = T_N_Death_Sprite_Value;
	Unit_Dt[Unit_Type_Value].Time_Next_Dead = T_N_Dead_Value;
	Unit_Dt[Unit_Type_Value].Time_Next_Dead_Sprite = T_N_Dead_Sprite_Value;
	Unit_Dt[Unit_Type_Value].Train_Location = Train_Location_Value;
	Unit_Dt[Unit_Type_Value].Time_Train = Time_Train_Value;
	Unit_Dt[Unit_Type_Value].Sub_Menu_Required = Sub_Menu_Required_Value;
}

void Civil::Set_Button_Dt()
{
	Button_Dt[Build].Button_Iso_Pos = { 135,605,51,52 };
	Button_Dt[Build].Button_Pos_Sor = { 102,0,51,52 };
	Button_Dt[Build].Choose_Object_Required = Villager;
	Button_Dt[Build].Sub_Menu_Required = Construct_Villager;

	Button_Dt[Stop_Research].Button_Iso_Pos = { 135,605,51,52 };
	Button_Dt[Stop_Research].Button_Pos_Sor = { 153,0,51,52 };
	Button_Dt[Stop_Research].Choose_Object_Required = -1;
	Button_Dt[Stop_Research].Sub_Menu_Required = -1;

	Button_Dt[Stop_Train].Button_Iso_Pos = { 135,665,51,52 };
	Button_Dt[Stop_Train].Button_Pos_Sor = { 153,0,51,52 };
	Button_Dt[Stop_Train].Choose_Object_Required = -1;
	Button_Dt[Stop_Train].Sub_Menu_Required = -1;
}

void Civil::Disable_Tech(int Tech_Type)
{
	Techs_Disable[Tech_Type] = true;
}

void Civil::Effect(int Tech_Type)
{
	switch (Tech_Type)
	{
	case Tool_Age:
		Civil::Epoch = Epoch_Bronze_Age;
		Techs_Available[Tool_Age] = true;
		cout << "Upgrade Suggess" << endl;
		break;
	default:
		break;
	}
}

void Civil::Enable_Unit(int Unit_Type)
{
	Unit[Unit_Type] = true;
}

int Civil::Get_Civil_Index()
{
	return Civil::Civil_Index;
}

int Civil::Get_Type_Control_Object()
{
	return Type_Control_Object;
}

Tech_Details Civil::Get_Tech_Details(int Tech_Type)
{
	return Tech_Dt[Tech_Type];
}

bool Civil::Check_Tech(int Tech_Type)
{
	return Techs_Disable[Tech_Type];
}

bool Civil::Check_Tech_Available(int Tech_Type)
{
	return Techs_Available[Tech_Type];
}

bool Civil::Check_Tech_Researching(int Tech_Type)
{
	return Tech_Researching[Tech_Type];
}

bool Civil::Check_Tech_to_Research(int Tech_Type, Choose_Object Choose_Object_Game, int x_Pos_Click, int y_Pos_Click, stack<int> Sub_Menu)
{
	int Check = true;
	if (Civil_Game_Object_List[Choose_Object_Game.Position]->Researching_Tech)
	{
		return false;
	}
	else if (Civil_Game_Object_List[Choose_Object_Game.Position]->Training_Unit)
	{
		return false;
	}
	else
	{
		if (!Techs_Disable[Tech_Type] && !Tech_Researching[Tech_Type] && !Techs_Available[Tech_Type])
		{
			if (Tech_Dt[Tech_Type].Research_Location == Choose_Object_Game.Unit_Choose)
			{
				for (int index = 0; index < Tech_Dt[Tech_Type].Required_Tech.size(); index++)
				{
					if (!Techs_Available[Tech_Dt[Tech_Type].Required_Tech[index]]) // Kiểm tra xem công nghệ yêu cầu này đã khả dụng chưa, tức đã được nghiên cứu xong chưa
					{
						Check = false;
						break;
					}
				}
				if (Sub_Menu.empty())
				{
					if (Tech_Dt[Tech_Type].Sub_Menu_Required != -1)
					{
						return false;
					}
				}
				else
				{
					if (Sub_Menu.top() != Tech_Dt[Tech_Type].Sub_Menu_Required)
					{
						if (Tech_Dt[Tech_Type].Sub_Menu_Required == -1)
						{
							Check = true;
						}
						else
						{
							Check = false;
							return false;
						}
					}
				}

				if (Check)
				{
					if (Tech_Dt[Tech_Type].Icon_Iso_Pos.x <= x_Pos_Click && x_Pos_Click <= (Tech_Dt[Tech_Type].Icon_Iso_Pos.x + Tech_Dt[Tech_Type].Icon_Iso_Pos.w) &&
						Tech_Dt[Tech_Type].Icon_Iso_Pos.y <= y_Pos_Click && y_Pos_Click <= (Tech_Dt[Tech_Type].Icon_Iso_Pos.y + Tech_Dt[Tech_Type].Icon_Iso_Pos.h))
					{
						//cout << Tech_Dt[Tech_Type].Icon_Iso_Pos.x << " " << Tech_Dt[Tech_Type].Icon_Iso_Pos.x + Tech_Dt[Tech_Type].Icon_Iso_Pos.w <<" "<<x_Pos_Click <<endl;
						if (Pay_Money(Tech_Dt[Tech_Type].Cost_Food, Tech_Dt[Tech_Type].Cost_Gold, Tech_Dt[Tech_Type].Cost_Wood, Tech_Dt[Tech_Type].Cost_Stone))
						{
							//cout << "yes";

							//Tech_Researching[Tech_Type] = true; // Tạm thời cho nghiên cứu xong luôn, sau khi thao tác với thời gian thì sẽ cần hàm duyệt qua các đối tượng để xem chỗ nào đã nghiên cứu xong thì nạp hiệu ứng
							//Tech_Researching[Tech_Type] = true;
							Civil_Game_Object_List[Choose_Object_Game.Position]->Start_Researching_Tech(Tech_Type);
							return true;
						}

					}
				}
				else
				{
					return false;
				}
			}
		}
		return false;
	}
	
}

void Civil::Enable_Tech_Researching(int Tech_Type)
{
	Tech_Researching[Tech_Type] = true;
}

void Civil::Disable_Tech_Researching(int Tech_Type)
{
	Tech_Researching[Tech_Type] = false;
}

bool Civil::Check_Unit(int Unit_Type)
{
	return Unit[Unit_Type];
}

bool Civil::Check_Unit_Disable(int Unit_type)
{
	return Unit_Disable[Unit_type];
}

void Civil::Check_Unit_Display(int Unit_Type, Choose_Object Choose_Object_Game, stack<int> Sub_Menu)
{
	if (Civil_Game_Object_List[Choose_Object_Game.Position]->Researching_Tech)
	{
		return;
	}
	else
	{
		if (Unit[Unit_Type] && !Unit_Disable[Unit_Type])
		{
			if (Unit_Dt[Unit_Type].Train_Location == Choose_Object_Game.Unit_Choose)
			{
				if (Sub_Menu.empty())
				{
					if (Unit_Dt[Unit_Type].Sub_Menu_Required != -1)
					{
						return;
					}
				}
				else
				{
					if (Unit_Dt[Unit_Type].Sub_Menu_Required != Sub_Menu.top())
					{
						if (Unit_Dt[Unit_Type].Sub_Menu_Required != -1)
						{
							return;
						}
						
					}
				}
				//cout << "tes" << endl;
				if (Unit_Type == House || Unit_Type == Granary || Unit_Type == Barracks)
				{
					//cout << "ýe";
					SDL_RenderCopy(Renderer, Country_House_Icon_Texture_Construct_1[Civil_Index], &Unit_Dt[Unit_Type].Icon_Pos_Sor, &Unit_Dt[Unit_Type].Icon_Iso_Pos);
				}
				else
				{
					if (Unit_Type == Mine_Gold)
					{
						//cout << "yes";
					}
					SDL_RenderCopy(Renderer, Country_Unit_Icon_Texture[Civil_Index], &Unit_Dt[Unit_Type].Icon_Pos_Sor, &Unit_Dt[Unit_Type].Icon_Iso_Pos);
				}

			}
		}
	}
	
}

bool Civil::Check_Train_Game_Unit(int Unit_Type, Choose_Object Choose_Object_Game, int x_Pos_Click, int y_Pos_Click, stack<int> Sub_Menu, int Map_Layer_1[50][50], int Map_Layer_2[50][50], int Location_Position, Cell_Uniform_Grid Map_UG_Layer_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Layer_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map]) // Index của Location, nơi sẽ Train đối tượng Game trong List Game Object của quốc gia này
{
	if (Civil_Game_Object_List[Choose_Object_Game.Position]->Researching_Tech)
	{
		return false;
	}
	else
	{
		if (Unit[Unit_Type] && !Unit_Disable[Unit_Type])
		{
			if (Unit_Dt[Unit_Type].Train_Location == Choose_Object_Game.Unit_Choose)
			{
				if (Sub_Menu.empty())
				{
					if (Unit_Dt[Unit_Type].Sub_Menu_Required != -1)
					{
						return false;
					}
				}
				else
				{
					if (Unit_Dt[Unit_Type].Sub_Menu_Required != Sub_Menu.top())
					{
						return false;
					}
				}
				if (Unit_Type == House)
				{
					//cout << "yes";
				}
				if (Unit_Dt[Unit_Type].Icon_Iso_Pos.x <= x_Pos_Click && x_Pos_Click <= (Unit_Dt[Unit_Type].Icon_Iso_Pos.x + Unit_Dt[Unit_Type].Icon_Iso_Pos.w) &&
					Unit_Dt[Unit_Type].Icon_Iso_Pos.y <= y_Pos_Click && y_Pos_Click <= (Unit_Dt[Unit_Type].Icon_Iso_Pos.y + Unit_Dt[Unit_Type].Icon_Iso_Pos.h))
				{
					//cout << "yes";
					//cout << Tech_Dt[Tech_Type].Icon_Iso_Pos.x << " " << Tech_Dt[Tech_Type].Icon_Iso_Pos.x + Tech_Dt[Tech_Type].Icon_Iso_Pos.w <<" "<<x_Pos_Click <<endl;
					if (Pay_Money(Unit_Dt[Unit_Type].Cost_Food, Unit_Dt[Unit_Type].Cost_Gold, Unit_Dt[Unit_Type].Cost_Wood, Unit_Dt[Unit_Type].Cost_Stone))
					{
						if (Unit_Dt[Unit_Type].Unit_Type_Property == Building)
						{
							if (Choose_Object_Game.Unit_Type_Control == Player)
							{
								//cout << "yes" << endl;
								Civil_Game_Object_List[Choose_Object_Game.Position]->Enable_Find_to_Build_House(Unit_Type);
								//Civil_Game_Object_List[Choose_Object_Game.Position]->
							}
						}
						else
						{
							Civil_Game_Object_List[Choose_Object_Game.Position]->Add_to_Train_Unit_Queue(Unit_Type);
						}
						
						return true;
					}
				}
			}
		}
	}
	
}

bool Civil::Check_Button_Perform(int Button_Type, int x_Pos_Click, int y_Pos_Click, stack<int> &Sub_Menu, Choose_Object Choose_Object_Game)
{
	if (Button_Dt[Button_Type].Button_Iso_Pos.x < x_Pos_Click && x_Pos_Click < Button_Dt[Button_Type].Button_Iso_Pos.x + Button_Dt[Button_Type].Button_Iso_Pos.y &&
		Button_Dt[Button_Type].Button_Iso_Pos.y < y_Pos_Click && y_Pos_Click < Button_Dt[Button_Type].Button_Iso_Pos.y + Button_Dt[Button_Type].Button_Iso_Pos.h)
	{
		switch (Button_Type)
		{
		case Build:
		{
			if (Choose_Object_Game.Unit_Choose == Villager && Sub_Menu.top() == Construct_Villager)
			{
				Sub_Menu.push(Page_1_Build_Construct);
				return true;
			}
			break;
		}
		case Stop_Research:
		{
			if (Civil_Game_Object_List[Choose_Object_Game.Position]->Researching_Tech)
			{
				Civil_Game_Object_List[Choose_Object_Game.Position]->Cancel_Researching_Tech();
				return true;
			}
			break;
		}
		case Stop_Train:
		{
			if (Civil_Game_Object_List[Choose_Object_Game.Position]->Training_Unit)
			{
				Civil_Game_Object_List[Choose_Object_Game.Position]->Cancel_Training_Unit();
				return true;
			}
			break;
		}
		default:
			break;
		}
	}
	return false;
}

bool Civil::Find_Locate_to_Train(SDL_Rect Train_Location, SDL_Rect& Output_Train_Location, Cell_Uniform_Grid Map_UG_Layer_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Layer_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map])
{
	//Output Train Location : Vị trí quân sẽ được sinh ra nếu còn chỗ Train hoặc số lượng quân vẫn còn cho phép, Function này sẽ trả về false nếu không tìm được vị trí thích họp !
	int x_1_const;
	int y_1_const;
	int x_1 = x_1_const = Train_Location.x / Orth_Tile_Height; //cout << x_1 << endl;
	int y_1 = y_1_const = Train_Location.y / Orth_Tile_Weight;
	SDL_Rect Location_Rect = {};
	bool Check = false;
	for (int i1 = x_1 - 1; i1 < x_1 + 4; i1++)
		for (int j1 = y_1 - 1; j1 < y_1 + 4; j1++)
		{
			if ((i1 != x_1_const - 1 && i1 != x_1_const + 3) && (j1 != y_1_const - 1 && j1 != y_1_const + 3))
			{
				//cout << i1 << " " << j1 << endl;
				continue;
			}
			//cout << "yes" << endl;
			if (Check_Cell_Empty_include_Object(j1,i1,Map_UG_Layer_2))
			{
				//int Pos = Get_Pos_New_Object();
				//cout << "yes";
				//Map_Layer_2[j1][i1] = Villager;
				//cout << Map_Layer_2[j1][i1] << endl;
				//Push_Object_to_Cell(Map_UG_Layer_2, Pos, Game_Object_Train->Get_Unit_Type(), j1, i1);
				Location_Rect.x = i1 * Orth_Tile_Height; //cout << "yes" << endl;
				Location_Rect.y = j1 * Orth_Tile_Weight;
				//cout << j1 << i1 << endl;
				Check = true;
				goto Stop;
			}
		}
	Stop:
	if (Check)
	{
		Output_Train_Location = Location_Rect;
		return true;
	}
	else
	{
		return false;
	}
}

int Civil::Get_Epoch()
{
	return Epoch;
}

bool Civil::Check_Locate_Build_House(int Unit_Type_House_Build_Value, SDL_Rect Locate_Build_House, Cell_Uniform_Grid Map_UG_Layer_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Layer_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map])
{
	int Row_Start_Value = Locate_Build_House.y / Orth_Tile_Height;
	int Col_Start_Value = Locate_Build_House.x / Orth_Tile_Weight;
	int Size_Number_Cell_Value = ceil(Unit_Dt[Unit_Type_House_Build_Value].Size_Number_Cell);
	for (int Row = Row_Start_Value; Row < Row_Start_Value + Size_Number_Cell_Value; Row++)
	{
		for (int Col = Col_Start_Value; Col < Col_Start_Value + Size_Number_Cell_Value; Col++)
		{
			if (!Check_Cell_Empty_include_Object(Row, Col, Map_UG_Layer_2))
			{
				return false;
			}
		}
	}
	return true;
}

int Civil::Get_Amount_Food()
{
	return Civil::Amount_Food;
}

int Civil::Get_Amount_Wood()
{
	return Civil::Amount_Wood;
}

int Civil::Get_Amount_Gold()
{
	return Civil::Amount_Gold;
}

int Civil::Get_Amount_Stone()
{
	return Civil::Amount_Stone;
}

bool Civil::Pay_Money(int Food, int Gold, int Wood, int Stone)
{
	Amount_Food -= Food;
	Amount_Gold -= Gold;
	Amount_Stone -= Stone;
	Amount_Wood -= Wood;
	if (Amount_Food >= 0 && Amount_Gold >= 0 && Amount_Stone >= 0 && Amount_Wood >= 0)
	{
		cout << "You can buy" << endl;
		return true;
	}
	else
	{
		Amount_Food += Food;
		Amount_Gold += Gold;
		Amount_Stone += Stone;
		Amount_Wood += Wood;
		cout << "You cann't buy it, sorry" << endl;
		return false;
	}
}

bool Civil::Check_Tech_Display(int Tech_Type, Choose_Object Choose_Object_Game)
{
	if (Civil_Game_Object_List[Choose_Object_Game.Position]->Researching_Tech)
	{
		return false;
	}
	else if (Civil_Game_Object_List[Choose_Object_Game.Position]->Training_Unit)
	{
		return false;
	}
	else
	{
		bool Check = true;
		if (!Techs_Disable[Tech_Type] && !Techs_Available[Tech_Type])
		{
			if (Tech_Dt[Tech_Type].Research_Location == Choose_Object_Game.Unit_Choose)
			{
				for (int index = 0; index < Tech_Dt[Tech_Type].Required_Tech.size(); index++)
				{
					if (!Techs_Available[Tech_Dt[Tech_Type].Required_Tech[index]])
					{
						Check = false;
						break;
					}
				}
				if (Check)
				{
					switch (Tech_Type)
					{
					case Tool_Age:
					{
						SDL_Rect Assign_Rect = { 3380, 0, 52, 52 };
						//cout << "yes";
						//cout << Button_6.x << Button_6.y << Button_6.w << Button_6.h << endl;
						SDL_RenderCopy(Renderer, Country_Tech_Texture[Civil_Index], &Tech_Dt[Tech_Type].Icon_Pos_Sor, &Tech_Dt[Tool_Age].Icon_Iso_Pos);
						break;
					}
					case Bronze_Age:
					{
						SDL_Rect Assign_Rect = { 3432, 0, 52, 52 };
						//cout << "yes";
						//cout << Button_6.x << Button_6.y << Button_6.w << Button_6.h << endl;
						SDL_RenderCopy(Renderer, Country_Tech_Texture[Civil_Index], &Tech_Dt[Tech_Type].Icon_Pos_Sor, &Tech_Dt[Tool_Age].Icon_Iso_Pos);
						break;
					}
					default:
						break;
					}
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		return false;
	}
	
}
bool Civil::Check_Button_Display(int Button_Type, stack<int> Sub_Menu, Choose_Object Choose_Object_Game)
{
	//cout << "yes";
	bool Check = true;
	if (Button_Type == Build)
	{
		if (!Sub_Menu.empty())
		{
			if (Choose_Object_Game.Unit_Choose == Villager && Sub_Menu.top() == Construct_Villager)
			{
				SDL_RenderCopy(Renderer, Country_Button_Texture[Civil_Index], &Button_Dt[Build].Button_Pos_Sor, &Button_Dt[Build].Button_Iso_Pos);
			}
		}
		//if (Choose_Object_Game.Unit_Choose == Villager && Su)
	}
	else if (Button_Type == Stop_Research)
	{
		if (Civil_Game_Object_List[Choose_Object_Game.Position]->Researching_Tech)
		{
			SDL_RenderCopy(Renderer, Country_Button_Texture[Civil_Index], &Button_Dt[Button_Type].Button_Pos_Sor, &Button_Dt[Button_Type].Button_Iso_Pos);
		}
	}
	else if (Button_Type == Stop_Train)
	{
		if (Civil_Game_Object_List[Choose_Object_Game.Position]->Training_Unit)
		{
			SDL_RenderCopy(Renderer, Country_Button_Texture[Civil_Index], &Button_Dt[Button_Type].Button_Pos_Sor, &Button_Dt[Button_Type].Button_Iso_Pos);
		}
	}
	else
	{
		if (Sub_Menu.empty())
		{
			//cout << "yes";
			if (Button_Dt[Button_Type].Sub_Menu_Required != -1)
			{
				return false;
			}
		}
		if (!Sub_Menu.empty())
		{
			if (Button_Type == Construct_Villager)
			{
				//cout << Sub_Menu.top() << endl;
			}
			if (Sub_Menu.top() != Button_Dt[Button_Type].Sub_Menu_Required)
			{
				//cout << "yes";
				Check = false;
				return false;
			}
			if (Button_Dt[Button_Type].Choose_Object_Required != Choose_Object_Game.Unit_Choose);
			{
				Check = false;
				return false;
			}
			if (Check)
			{
				SDL_RenderCopy(Renderer, Country_Button_Texture[Civil_Index], &Button_Dt[Button_Type].Button_Pos_Sor, &Button_Dt[Button_Type].Button_Iso_Pos);
			}
		}

	}
}
int Civil::Get_Population()
{
	return Population;
}
int Civil::Get_Population_Max()
{
	return Population_Max;
}
void Civil::Civil_Develop()
{
}
bool Civil::Civil_Train_Add_Unit(int Unit_Type_Build)
{
	if (Unit_Type_Build == House)
	{
		if (Population_Max < Population_Limit)
		{
			Population_Max += 2;
		}
		return true;
	}
	else if (Unit_Type_Build == Town_Center)
	{
		if (Population_Max < Population_Limit)
		{
			Population_Max += 4;
		}
		return true;
	}
	else if (Unit_Type_Build != Barracks)
	{
		if (Population < Population_Max)
		{
			Population++;
		}
		else
		{
			//cout << " Build House to continue training" << endl;
			return false;
		}
	}
}
int Civil::Get_Pos_New_Object() // Có một cách cải tiến thuật toán này, đó là duyệt qua từng phần tử để biết đâu là đối tượng có Unit Type là -1 thì mỗi khi đối tượng nào chết sẽ đưa chỉ số của nó vào trong một list để có thể lấy ra dễ dàng.
{
	for (int i = 0; i < Civil_Game_Object_List.size(); i++)
	{
		if (Civil_Game_Object_List[i]->Get_Unit_Type() == -1)
		{
			return i;
		}
	}
	return Civil_Game_Object_List.size();
}
void Civil::Push_Object_to_Cell(Cell_Uniform_Grid Map_UG_Layer[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Game_Object* Game_Object_Push)
{
	int m = Game_Object_Push->Get_Orth_Pos().x / Cell_Size;
	int m_w = (Game_Object_Push->Get_Orth_Pos().x + Game_Object_Push->Size_Number_Cell * Orth_Tile_Height) / Cell_Size;
	int n = Game_Object_Push->Get_Orth_Pos().y / Cell_Size;
	int n_h = (Game_Object_Push->Get_Orth_Pos().y + Game_Object_Push->Size_Number_Cell * Orth_Tile_Height) / Cell_Size;
	cout << "k " << m << " j " << n << endl;
	int Pos = Get_Pos_New_Object();
	//cout<<Pos;
	for (int j = m; j <= m_w; j++)
	{
		for (int k = n; k <= n_h; k++)
		{
			 // Kết luận, sai i và j
			Cell_Object Cell_Object_Assign;
			Cell_Object_Assign.Object_Type = Game_Object_Push->Get_Unit_Type();
			Cell_Object_Assign.Pos = Game_Object_Push->Pos_in_List_Object;
			Cell_Object_Assign.Orth_Pos = Game_Object_Push->Get_Orth_Pos();
			Cell_Object_Assign.Country = Game_Object_Push->Get_Country();
			Cell_Object_Assign.Unit_Type_Control = Game_Object_Push->Unit_Type_Control;
			Cell_Object_Assign.Pos_Control = Game_Object_Push->Pos_Control;
			Cell_Contain_Object Cell_Contain_Object_Assign;
			Cell_Contain_Object_Assign.Col = j;
			Cell_Contain_Object_Assign.Row = k;
			Cell_Contain_Object_Assign.Pos = Pos;
			//Cell_Contain_Object_Assign.Object_Rect=List_Object[i]->Rect;
			Map_UG_Layer[k][j].List_Object_in_Cell.push_back(Cell_Object_Assign);
			//cout << "Dung";

			Game_Object_Push->List_Cell_Contain_Object.push_back(Cell_Contain_Object_Assign);

			//cout << k << " " << j << endl;
		}
	}
	cout << "Build" << endl;
	m = Game_Object_Push->Get_Iso_Pos().x / Cell_Size;
	m_w = (Game_Object_Push->Get_Iso_Pos().x + Game_Object_Push->Get_Iso_Pos().w) / Cell_Size;
	n = Game_Object_Push->Get_Iso_Pos().y / Cell_Size;
	n_h = (Game_Object_Push->Get_Iso_Pos().y + Game_Object_Push->Get_Iso_Pos().h) / Cell_Size;

	Pos = Get_Pos_New_Object();

	//cout<<Pos;
	for (int j = m; j <= m_w; j++)
	{
		for (int k = n; k <= n_h; k++)
		{
			Cell_Object Cell_Object_Assign;
			Cell_Object_Assign.Object_Type = Game_Object_Push->Get_Unit_Type();
			Cell_Object_Assign.Pos = Game_Object_Push->Pos_in_List_Object;
			Cell_Object_Assign.Orth_Pos = Game_Object_Push->Get_Orth_Pos();
			Cell_Object_Assign.Country = Game_Object_Push->Get_Country();
			Cell_Object_Assign.Unit_Type_Control = Game_Object_Push->Unit_Type_Control;
			Cell_Object_Assign.Pos_Control = Game_Object_Push->Pos_Control;
			Cell_Contain_Object Cell_Contain_Object_Assign;
			Cell_Contain_Object_Assign.Col = j;
			Cell_Contain_Object_Assign.Row = k;
			Cell_Contain_Object_Assign.Pos = Pos;
			//Cell_Contain_Object_Assign.Object_Rect=List_Object[i]->Rect;
			Map_UG_Check_Click[k][j].List_Object_in_Cell.push_back(Cell_Object_Assign);
			Game_Object_Push->List_Cell_Contain_Object_Click.push_back(Cell_Contain_Object_Assign);
			//cout << k << " " << j << endl;
		}
	}
	
}
