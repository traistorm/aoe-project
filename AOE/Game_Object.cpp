#include "Game_Object.h"
//#include "Init.h"

int Game_Object::Get_Unit_Type()
{
	return Game_Object::Unit_Type;
}

void Game_Object::Load_to_Screen()
{
	//Manager_Game = new Manager();
	Manager_Game->Load_Image(this, Game_Object::Unit_Type, Object_Status, Direction, Country, Hit_Point, Max_Hit_Point, Game_Object::Pos_Sor, Game_Object::Orth_Pos, Game_Object::Iso_Pos, Game_Object::Hit_Point_Pos, Hit_Point_Pos_Sor);

}

void Game_Object::Move(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*>& Civil_Computer_List, vector<Civil*>& Civil_Player_List, int Pos)
{
	//cout << "co ve dung";
}

void Game_Object::Attack(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], vector<Civil*> Civil_Computer_List, vector<Civil*>Civil_Player_List, int Pos)
{
}

void Game_Object::Work(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*> Civil_Computer_List, vector<Civil*>Civil_Player_List, int Pos)
{
}

void Game_Object::Take_Damage(Civil* Civil_Gaia_List, vector<Civil*>Civil_Player_List, vector<Civil*>Civil_Computer_List)
{
	if (Unit_Type != Death && Unit_Type != Dead && Unit_Type != Disappear)
	{
		int Damage = -1;
		/*if (Unit_Type_Control == Player)
		{
			cout << "yes";
		}*/
		if (Type_Control_Object_Attack_Object == Player)
		{
			//cout << "yes";
			//cout << Pos_Control_Object_Attack_Object;
			Damage = Civil_Player_List[Pos_Control_Object_Attack_Object]->Unit_Dt[Unit_Type_Attack_Object].Damage;
		}
		if (Type_Control_Object_Attack_Object == Computer)
		{
			//cout << "yes";
			Damage = Civil_Computer_List[Pos_Control_Object_Attack_Object]->Unit_Dt[Unit_Type_Attack_Object].Damage;
		}
		Hit_Point -= Damage;
		if (Hit_Point <= 0)
		{
			/*if (Unit_Type == Clubman)
			{
				cout << "Chet";
			}*/
			Alive = false;
			Change_Object_Status(Death);
			return;
			//Object_Status = Death;
		}
		if (Object_Status == Standing && Unit_Type != Mine_Gold && Unit_Type != Mine_Stone && Unit_Type != Tree_01 && Unit_Type_Property != Building)
		{
			//cout << "yes";
			if (Unit_Type_Property == Building)
			{
				//cout << "OKKKKKKKKKKKKKKKK";
			}
			SDL_Rect Orth_Pos_Attack_Value = {};
			if (Type_Control_Object_Attack_Object == Player)
			{
				Orth_Pos_Attack_Value = Civil_Player_List[Pos_Control_Object_Attack_Object]->Civil_Game_Object_List[Pos_Attack_Object]->Get_Orth_Pos();
				//Civil_Player_List[Pos_Control_Object_Attack_Object]->Civil_Game_Object_List[Pos_Attack_Object]->Get_Infor_Attack_Object(Unit_Type_Object_Attack)
				//cout << "Orth : " << Orth_Pos_Attack_Value.x << " " << Orth_Pos_Attack_Value.y << endl;
				Set_Orth_Pos_Object_Attack(Civil_Player_List, Civil_Computer_List, Orth_Pos_Attack_Value, Unit_Type_Attack_Object, Pos_Attack_Object, Country_Attack_Object, Type_Control_Object_Attack_Object, Pos_Control_Object_Attack_Object);
			}
			
			if (Type_Control_Object_Attack_Object == Player)
			{
				//cout << "yes";
				Civil_Player_List[Pos_Control_Object_Attack_Object]->Civil_Game_Object_List[Pos_Attack_Object]->Get_Infor_Attack_Object(Unit_Type, Pos_in_List_Object, Country, Unit_Type_Control, Pos_Control);
			}
		}
	}
	
}

void Game_Object::Set(SDL_Rect Assign_Rect_Orth, SDL_Rect Assign_Rect_Iso, SDL_Rect Assign_Rect_Sor, int Unit_Type, int z, int Country, int Country_Name, int Selection_w, int Selection_h)
{
	if (Country == 2)
	{
		//cout << "DUNG" << endl;
	}
	Game_Object::Unit_Type = Unit_Type; //cout << Unit_Type << endl;
	//cout << Game_Object::Unit_Type;
	Orth_Pos = Assign_Rect_Orth;
	Pos_Sor = Assign_Rect_Sor;
	//Game_Object::Iso_Pos = Assign_Rect_Iso;
	Game_Object::Weight = Assign_Rect_Sor.w;
	Game_Object::Height = Assign_Rect_Sor.h;
	Iso_Pos_Selection.w = Selection_w;
	Iso_Pos_Selection.h = Selection_h;
	Game_Object::z = z;
	this->Country = Country;
	this->Country_Name = Country_Name;
	if (Unit_Type == Grass)
	{
		Convert(Iso_Pos, Assign_Rect_Orth, z);
	}
	else
	{
		Convert_Object(this, Iso_Pos, Orth_Pos, Assign_Rect_Sor.w, Assign_Rect_Sor.h);
	}
	//Game_Object::Iso_Pos = Assign_Rect_Iso;
	/*if (Unit_Type == Grass)
	{
		Convert(Iso_Pos, Orth_Pos, z);
	}
	else
	{
		Convert_Object(this, Iso_Pos, Orth_Pos, Assign_Rect_Sor.w, Assign_Rect_Sor.h);
	}*/
	//cout << Game_Object::Iso_Pos.x;
}

void Game_Object::Enable_Search_A_Star()
{
	
}

int Game_Object::Get_Hit_Point()
{
	return Hit_Point;
}

int Game_Object::Get_Search_Radius()
{
	return Search_Radius;
}

int Game_Object::Get_Unit_Type_Property()
{
	return Unit_Type_Property;
}

void Game_Object::Set_Unit_Type_Property(int Unit_Type_Property_Value)
{
	//Percent_Complete_Build = 100;
	Unit_Type_Property = Unit_Type_Property_Value;
}

void Game_Object::Enable_Search_Move_To_Attack()
{
	Search_Move_To_Attack = true;
}

void Game_Object::Enable_Moving_To_Attack()
{
	Moving_To_Attack = true;
}

Hit_Box Game_Object::Get_Hit_Box()
{
	return Hit_Box();
}

void Game_Object::Set_Hit_Box(int Row, int Col, int Damage, int Blast_Width, int Blast_Attack_Type)
{
	//cout << "Hit";
}

bool Game_Object::Check_Hit_Box_Activated()
{
	return false;
}

void Game_Object::Disable_Hit_Box()
{
}

void Game_Object::Change_Unit_Type(int Unit_Type_Value)
{
	
}

void Game_Object::Change_Object_Status(int Object_Status_Value)
{
	if (Object_Status_Value == Disappear)
	{
		if (Unit_Type != Tree_01)
		{
			Object_Status = Object_Status_Value;
			Unit_Type = -1;
		}
		else
		{
			return;
		}
	}
	if (Object_Status_Value == Dead)
	{
		/*if (Unit_Type == Mine_Gold || Unit_Type == Mine_Stone)
		{
			Object_Status = Disappear;
			Unit_Type = -1;
			return;
		}*/
	}
	/*if (Object_Status_Value == Attacking)
	{
		if (Moving_To_Attack)
		{
			return;
		}
		else
		{
			Object_Status = Attacking;
		}
	}*/
	if (Object_Status != Object_Status_Value)
	{
		Change_Status = true;
	}
	else
	{
		Change_Status = false;
	}
	Object_Status = Object_Status_Value;
}

SDL_Rect Game_Object::Get_Pos_Sor()
{
	return Game_Object::Pos_Sor;
}

SDL_Rect Game_Object::Get_Orth_Pos()
{
	return Game_Object::Orth_Pos;
}

SDL_Rect Game_Object::Get_Iso_Pos()
{
	return Iso_Pos;
}

void Game_Object::Set_Orth_Pos_Object_Attack(vector<Civil*>Civil_Player_List, vector<Civil*>Civil_Computer_List,
	SDL_Rect Orth_Pos_Attack_Value, int Unit_Type_Object_Attack_Value, int Pos_Object_Attack_Value, int Country_Object_Attack_Value, int Type_Control_Object_Object_Attack_Value, int Pos_Control_Object_Object_Attack_Value)
{
	Orth_Pos_Attack = Orth_Pos_Attack_Value;
	Orth_Pos_Attack_Last = Orth_Pos_Attack_Value;
	Unit_Type_Object_Attack = Unit_Type_Object_Attack_Value;
	Pos_Object_Attack = Pos_Object_Attack_Value;
	Country_Object_Attack = Country_Object_Attack_Value;
	Type_Control_Object_Object_Attack = Type_Control_Object_Object_Attack_Value;
	Pos_Control_Object_Object_Attack = Pos_Control_Object_Object_Attack_Value;
	if (Moving_To_Attack)
	{
		
	}
	else
	{
		Search_Move_To_Attack = true;
		Change_Object_Status(Attacking);
	}
	
	//Object_Status = Attacking;
	//cout << "yes";
	if (Type_Control_Object_Object_Attack == Computer)
	{
		//cout << "yes";
		//cout << "Orth : " << Pos_Control_Object_Object_Attack << endl;
		SDL_Rect Orth_Pos_Value = Civil_Computer_List[Pos_Control_Object_Object_Attack]->Civil_Game_Object_List[Pos_Object_Attack]->Get_Orth_Pos();
		int Row_Cell_Click_Hit_Box = Orth_Pos_Value.y / Orth_Tile_Height;
		int Col_Cell_Click_Hit_Box = Orth_Pos_Value.x / Orth_Tile_Weight;
		int Damage = -1;
		if (Unit_Type_Control == Player)
		{
			Damage = Civil_Player_List[Pos_Control]->Unit_Dt[Unit_Type].Damage;
		}
		else if (Unit_Type_Control == Computer)
		{
			Damage = Civil_Computer_List[Pos_Control]->Unit_Dt[Unit_Type].Damage;
		}
		Set_Hit_Box(Row_Cell_Click_Hit_Box, Col_Cell_Click_Hit_Box, Damage, 0, -1);
	}
	else if (Type_Control_Object_Object_Attack == Player)
	{
		SDL_Rect Orth_Pos_Value = Civil_Player_List[Pos_Control_Object_Object_Attack]->Civil_Game_Object_List[Pos_Object_Attack]->Get_Orth_Pos();
		int Row_Cell_Click_Hit_Box = Orth_Pos_Value.y / Orth_Tile_Height;
		int Col_Cell_Click_Hit_Box = Orth_Pos_Value.x / Orth_Tile_Weight;
		int Damage = -1;
		if (Unit_Type_Control == Player)
		{
			Damage = Civil_Player_List[Pos_Control]->Unit_Dt[Unit_Type].Damage;
		}
		else if (Unit_Type_Control == Computer)
		{
			Damage = Civil_Computer_List[Pos_Control]->Unit_Dt[Unit_Type].Damage;
		}
		Set_Hit_Box(Row_Cell_Click_Hit_Box, Col_Cell_Click_Hit_Box, Damage, 0, -1);
	}
}

void Game_Object::Set_Orth_Pos_Work(SDL_Rect Orth_Pos_Work_Value, int Unit_Type_Object_Work_Value, int Pos_Object_Work_Value, int Country_Object_Work_Value, int Unit_Type_Control_Work_Value, int Pos_Control_Work_Value)
{
	Orth_Pos_Work = Orth_Pos_Work_Value;
	Unit_Type_Object_Work = Unit_Type_Object_Work_Value;
	Pos_Object_Work = Pos_Object_Work_Value;
	Country_Object_Work = Country_Object_Work_Value;
	Unit_Type_Control_Work = Unit_Type_Control_Work_Value;
	Pos_Control_Work = Pos_Control_Work_Value;
}

void Game_Object::Get_Infor_Attack_Object(int Unit_Type_Attack_Object_Value, int Pos_Attack_Object_Value, int Country_Attack_Object_Value, int Type_Control_Object_Attack_Object_Value, int Pos_Control_Object_Attack_Object_Value)
{
	Unit_Type_Attack_Object = Unit_Type_Attack_Object_Value;
	Pos_Attack_Object = Pos_Attack_Object_Value;
	Country_Attack_Object = Country_Attack_Object_Value;
	Type_Control_Object_Attack_Object = Type_Control_Object_Attack_Object_Value;
	Pos_Control_Object_Attack_Object = Pos_Control_Object_Attack_Object_Value;
}

int Game_Object::Get_Country()
{
	return Country;
}

int Game_Object::Get_Country_Name()
{
	return Country_Name;
}

int Game_Object::Set_Country_Name(int Country_Name_Value)
{
	Country_Name = Country_Name_Value;
	return 0;
}

void Game_Object::Change_Orth_Pos(SDL_Rect Orth_Pos_Next)
{
	Orth_Pos = Orth_Pos_Next;
}

void Game_Object::Set_Orth_Pos_Move(SDL_Rect Orth_Pos_Move_Next)
{
	Orth_Pos_Move = Orth_Pos_Move_Next;
}

void Game_Object::Research_Tech(Tech_Details Tech_Dt[], Civil* Civil_Gaia_List, vector<Civil*>& Civil_Computer_List, vector<Civil*>& Civil_Player_List)
{

}

void Game_Object::Set_Object_Properties(Unit_Details Unit_Dt[])
{
	Hit_Point = Max_Hit_Point = Unit_Dt[Unit_Type].Hit_Point;
	//Attack_Damage = Unit_Dt[Unit_Type].Damage;
	//cout << "hex" << endl;
}

void Game_Object::Start_Researching_Tech(int Tech_Type)
{
	Researching_Tech = true;
	Researching_Tech_Type = Tech_Type;
}

void Game_Object::Cancel_Researching_Tech()
{

}

void Game_Object::Cancel_Training_Unit()
{
}

void Game_Object::Train_Unit(int Unit_Type, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*>& Civil_Computer_List, vector<Civil*>& Civil_Player_List)
{

}

void Game_Object::Add_to_Train_Unit_Queue(int Unit_Type)
{

}

int Game_Object::Get_Number_Unit_Train()
{
	return 0;
}

void Game_Object::Change_Unit_Type_Build(int Unit_Type_Build_Value)
{
}

void Game_Object::Build(int Unit_Type_Build, SDL_Rect Orth_Pos_Build, Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*> Civil_Computer_List, vector<Civil*> Civil_Player_List, int Pos)
{
}

void Game_Object::Load_Sprite_Sheet(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*> Civil_Computer_List, vector<Civil*>Civil_Player_List)
{
	if (Unit_Type_Property == Building) // Nếu là công trình xây dựng
	{
		int Frame_Weight = 0;
		int Frame_Height = 0;
		int Time_Next_Sprite = 0;
		int Number_Frame_Direc = 0;
		int Focus_Point_x = 0;
		int Focus_Point_y = 0;
		if (Percent_Complete_Build < 100)
		{
			if (Get_Unit_Type() == House)
			{
				Frame_Weight = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[House].Standing_Frame_Weight;
				Frame_Height = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[House].Standing_Frame_Height;
				Time_Next_Sprite = Unit_Dt[Unit_Type].Time_Next_Standing_Sprite;
				Number_Frame_Direc = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[House].Number_Standing_Direction_Frame;
				Focus_Point_x = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[House].Focus_Point_Standing.x;
				Focus_Point_y = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[House].Focus_Point_Standing.y;
			}
			else
			{ 
				Frame_Weight = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Build_3_3].Standing_Frame_Weight;
				Frame_Height = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Build_3_3].Standing_Frame_Height;
				Time_Next_Sprite = Unit_Dt[Unit_Type].Time_Next_Standing_Sprite;
				Number_Frame_Direc = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Build_3_3].Number_Standing_Direction_Frame;
				Focus_Point_x = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Build_3_3].Focus_Point_Standing.x;
				Focus_Point_y = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Build_3_3].Focus_Point_Standing.y;
			}
		}
		else
		{
			Frame_Weight = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Standing_Frame_Weight;
			Frame_Height = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Standing_Frame_Height;
			Time_Next_Sprite = Unit_Dt[Unit_Type].Time_Next_Standing_Sprite;
			Number_Frame_Direc = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Number_Standing_Direction_Frame;
			Focus_Point_x = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Standing.x;
			Focus_Point_y = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Standing.y;
		}
		
		
		//cout << Pos_Sor.h << endl;
		Orth_Pos.w = Pos_Sor.w = Iso_Pos.w = Frame_Weight;
		Orth_Pos.h = Pos_Sor.h = Iso_Pos.h = Frame_Height;
		if (Percent_Complete_Build < 25)
		{
			Pos_Sor.x = 0;
		}
		else if (Percent_Complete_Build < 50)
		{
			Pos_Sor.x = Frame_Weight;
		}
		else if (Percent_Complete_Build < 75)
		{
			Pos_Sor.x = Frame_Weight * 2;
		}
		else if (Percent_Complete_Build < 100)
		{
			Pos_Sor.x = Frame_Weight * 3;
		}
		else if (Percent_Complete_Build == 100)
		{
			Pos_Sor.x = 0;
		}
		return;
	}
	//cout << "Yes";
	if (Unit_Type == Villager)
	{
		if (Change_Status)
		{
			//cout << "yes";
		}
	}
	Current_Time = SDL_GetTicks();
	switch (Object_Status)
	{
	case Standing:
	{
		//cout << "yes";
		
		int Frame_Weight = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Standing_Frame_Weight;
		int Frame_Height = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Standing_Frame_Height;
		int Time_Next_Sprite = Unit_Dt[Unit_Type].Time_Next_Standing_Sprite;
		int Number_Frame_Direc = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Number_Standing_Direction_Frame;
		int Focus_Point_x = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Standing.x;
		int Focus_Point_y = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Standing.y;
		//cout << Pos_Sor.h << endl;
		Orth_Pos.w = Pos_Sor.w = Iso_Pos.w = Frame_Weight;
		Orth_Pos.h = Pos_Sor.h = Iso_Pos.h = Frame_Height;
		if (Unit_Type == Clubman)
		{
			//cout << Orth_Pos.x << endl;
			//cout << Frame_Height << endl;
			//cout << "Iso Pos : " << Iso_Pos.x << " " << Iso_Pos.y << endl;
			//cout << "Iso Pos : " << Iso_Pos.x << " " << Iso_Pos.y << endl;
		}
		
		// Hey : Tại sao chỗ này tôi lại tôi lại phải đặt lại nhưng Frame trong bức ảnh ( Hay hiểu là tôi cài đặt lại tọa độ ở bức ảnh)
		/* Tới đây, tôi gặp một lỗi khá khó chịu, lại là một lỗi liên quan đến không load được hình ảnh :v
		   Lỗi là thế này : Khi tôi đang cho nông dân di chuyển, và di chuyển xong, nông dân đột ngột biến mất :), một lúc sau lại hiện ra, tôi mất tới gần 2 tiếng đồng hồ để xử lý cái bug khó chịu này
		   Tôi cũng đã có để ý lỗi này chỉ xảy ra khi tôi di chuyển theo một số hướng nhất định, và tôi không nhận ra gì từ việc này cả
		   Cuối cùng tôi mới phát hiện ra, bức ảnh Moving cho nông dân của tôi là 3000, nó dài hơn kha khó so với bức ảnh Standing của nông dân. như vậy đúng là khi tôi di chuyển theo hướng gần cuối bức ảnh
		   Tức tọa độ của Pos.x đã gần bằng 3000, và tôi đã không cài đặt lại tọa độ bức ảnh này khi vào trường hợp Standing, và nó vượt qua phạm vi này của bức ảnh lên chả hiển ra hình ảnh gì.
		   Còn tại sao nó lại biến mất ?
		   Thực ra là tôi có sử dụng thời gian, sau một thời gian nhất định, lệnh này sẽ set lại tọa độ cho đúng với hướng nếu sai, tôi cài nó bằng 500 dẫn tới việc sau 500 ms tọa độ mới được đặt lại cho đúng
		   Và lý do tôi có phần set lại như vậy để tọa độ cho đúng thôi ! :)
		*/
		if (Change_Status)
		{
			if (Direction == Direc_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_South_x;
			}
			else if (Direction == Direc_W_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
			}
			else if (Direction == Direc_W)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_x;
			}
			else if (Direction == Direc_W_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_North_x;
			}
			else if (Direction == Direc_N)
			{
				//cout << "OK";
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_North_x;
			}
			else if (Direction == Direc_E_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_North_x;
			}
			else if (Direction == Direc_E)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_x;
			}
			else if (Direction == Direc_E_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
			}
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
			Change_Status = false;
		}
		//cout << Pos_Sor.h << endl;
		//cout << Time_Next_Sprite;
		//Orth_Pos.h = Pos_Sor.h = Frame_Height;
		if ((Current_Time - Last_Time) > Time_Next_Sprite)
		{
			//cout << "Yep";
			if (Direction == Direc_S)
			{
				//cout << "yes";
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_South_x)
				{
					//cout << "yes";
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_South_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_W_S)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_South_x)
				{
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_W)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_x)
				{
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_W_N)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_North_x)
				{
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_North_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_N)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_North_x)
				{
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_North_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_E_N)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_North_x)
				{
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_North_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_E)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_x)
				{
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_E_S)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_South_x)
				{
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			Last_Time = Current_Time;
		}
		//Convert_Object(Iso_Pos, Orth_Pos, Frame_Weight, Frame_Height);
		break;
	}
	case Working:
	{
		int Frame_Weight = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Working_Frame_Weight;
		int Frame_Height = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Working_Frame_Height;
		int Time_Next_Sprite = Unit_Dt[Unit_Type].Time_Next_Working_Sprite;
		int Number_Frame_Direc = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Number_Working_Direction_Frame;
		int Focus_Point_x = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Working.x;
		int Focus_Point_y = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Working.y;
		//cout << Pos_Sor.h << endl;
		Orth_Pos.w = Pos_Sor.w = Iso_Pos.w = Frame_Weight;
		Orth_Pos.h = Pos_Sor.h = Iso_Pos.h = Frame_Height;
		if (Change_Status)
		{
			if (Direction == Direc_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_South_x;
			}
			else if (Direction == Direc_W_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
			}
			else if (Direction == Direc_W)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_x;
			}
			else if (Direction == Direc_W_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_North_x;
			}
			else if (Direction == Direc_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_North_x;
			}
			else if (Direction == Direc_E_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_North_x;
			}
			else if (Direction == Direc_E)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_x;
			}
			else if (Direction == Direc_E_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
			}
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
			Change_Status = false;
		}
		if ((Current_Time - Last_Time) > Time_Next_Sprite)
		{
			if (Orth_Pos.x < Orth_Pos_Work.x && Orth_Pos.y == Orth_Pos_Work.y)
			{
				Direction = Direc_E_S;
				Pos_Sor.y = Frame_East_South_y;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_South_x)
				{
					Pos_Sor.x = Frame_East_South_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Orth_Pos.x > Orth_Pos_Work.x&& Orth_Pos.y == Orth_Pos_Work.y)
			{
				Direction = Direc_W_N;
				Pos_Sor.y = Frame_West_North_y;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_North_x)
				{
					Pos_Sor.x = Frame_West_North_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Orth_Pos.x == Orth_Pos_Work.x && Orth_Pos.y < Orth_Pos_Work.y)
			{
				Direction = Direc_W_S;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_South_x)
				{
					Pos_Sor.x = Frame_West_South_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_West_South_y;
			}
			else if (Orth_Pos.x == Orth_Pos_Work.x && Orth_Pos.y > Orth_Pos_Work.y)
			{
				Direction = Direc_E_N;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_North_x)
				{
					Pos_Sor.x = Frame_East_North_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_East_North_y;
			}
			else if (Orth_Pos.x < Orth_Pos_Work.x && Orth_Pos.y < Orth_Pos_Work.y)
			{
				Direction = Direc_S;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_South_x)
				{
					Pos_Sor.x = Frame_South_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_South_y;
			}
			else if (Orth_Pos.x < Orth_Pos_Work.x && Orth_Pos.y > Orth_Pos_Work.y)
			{
				Direction = Direc_E;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_x)
				{
					Pos_Sor.x = Frame_East_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_East_y;
			}
			else if (Orth_Pos.x > Orth_Pos_Work.x&& Orth_Pos.y > Orth_Pos_Work.y)
			{
				Direction = Direc_N;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_North_x)
				{
					Pos_Sor.x = Frame_North_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_North_y;
			}
			else if (Orth_Pos.x > Orth_Pos_Work.x&& Orth_Pos.y < Orth_Pos_Work.y)
			{
				Direction = Direc_W;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_x)
				{
					Pos_Sor.x = Frame_West_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_West_y;
			}
			Last_Time = Current_Time;
		}
		break;
	}
	case Carry:
	{
		int Frame_Weight = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Carry_Frame_Weight;
		int Frame_Height = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Carry_Frame_Height;
		int Time_Next_Sprite = Unit_Dt[Unit_Type].Time_Next_Carry_Sprite;
		int Number_Frame_Direc = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Number_Carry_Direction_Frame;
		int Focus_Point_x = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Carry.x;
		int Focus_Point_y = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Carry.y;
		Orth_Pos.w = Pos_Sor.w = Iso_Pos.w = Frame_Weight;
		Orth_Pos.h = Pos_Sor.h = Iso_Pos.h = Frame_Height;
		if (Change_Status)
		{
			if (Direction == Direc_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_South_x;
			}
			else if (Direction == Direc_W_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
			}
			else if (Direction == Direc_W)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_x;
			}
			else if (Direction == Direc_W_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_North_x;
			}
			else if (Direction == Direc_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_North_x;
			}
			else if (Direction == Direc_E_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_North_x;
			}
			else if (Direction == Direc_E)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_x;
			}
			else if (Direction == Direc_E_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
			}
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
			Change_Status = false;
		}
		if ((Current_Time - Last_Time) > Time_Next_Sprite)
		{
			if (Direction == Direc_E_S)
			{
				Pos_Sor.y = Frame_East_South_y;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_South_x)
				{
					Pos_Sor.x = Frame_East_South_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_W_N)
			{
				Pos_Sor.y = Frame_West_North_y;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_North_x)
				{
					Pos_Sor.x = Frame_West_North_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_W_S)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_South_x)
				{
					Pos_Sor.x = Frame_West_South_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_West_South_y;
			}
			else if (Direction == Direc_E_N)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_North_x)
				{
					Pos_Sor.x = Frame_East_North_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_East_North_y;
			}
			else if (Direction == Direc_S)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_South_x)
				{
					Pos_Sor.x = Frame_South_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_South_y;
			}
			else if (Direction == Direc_E)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_x)
				{
					Pos_Sor.x = Frame_East_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_East_y;
			}
			else if (Direction == Direc_N)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_North_x)
				{
					Pos_Sor.x = Frame_North_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_North_y;
			}
			else if (Direction == Direc_W)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_x)
				{
					Pos_Sor.x = Frame_West_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_West_y;
			}
			Last_Time = Current_Time;
		}
		break;
	}
	case Moving:
	{
		//cout << "Yes";
		int Frame_Weight = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Moving_Frame_Weight;
		int Frame_Height = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Moving_Frame_Height;
		int Time_Next_Sprite = Unit_Dt[Unit_Type].Time_Next_Moving_Sprite;
		int Number_Frame_Direc = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Number_Moving_Direction_Frame;
		int Focus_Point_x = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Moving.x;
		int Focus_Point_y = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Moving.y;
		Orth_Pos.w = Pos_Sor.w = Iso_Pos.w = Frame_Weight;
		Orth_Pos.h = Pos_Sor.h = Iso_Pos.h = Frame_Height;
		if (Change_Status)
		{
			if (Direction == Direc_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_South_x;
			}
			else if (Direction == Direc_W_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
			}
			else if (Direction == Direc_W)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_x;
			}
			else if (Direction == Direc_W_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_North_x;
			}
			else if (Direction == Direc_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_North_x;
			}
			else if (Direction == Direc_E_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_North_x;
			}
			else if (Direction == Direc_E)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_x;
			}
			else if (Direction == Direc_E_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
			}
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
			Change_Status = false;
		}
		if ((Current_Time - Last_Time) > Time_Next_Sprite)
		{
			if (Direction == Direc_E_S)
			{
				Pos_Sor.y = Frame_East_South_y;
				// cout << "Loai doi tuong bi loi la : " << Unit_Type << endl;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_South_x)
				{
					Pos_Sor.x = Frame_East_South_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_W_N)
			{
				Pos_Sor.y = Frame_West_North_y;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_North_x)
				{
					Pos_Sor.x = Frame_West_North_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_W_S)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_South_x)
				{
					Pos_Sor.x = Frame_West_South_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_West_South_y;
			}
			else if (Direction == Direc_E_N)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_North_x)
				{
					Pos_Sor.x = Frame_East_North_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_East_North_y;
			}
			else if (Direction == Direc_S)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_South_x)
				{
					Pos_Sor.x = Frame_South_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_South_y;
			}
			else if (Direction == Direc_E)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_x)
				{
					Pos_Sor.x = Frame_East_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_East_y;
			}
			else if (Direction == Direc_N)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_North_x)
				{
					Pos_Sor.x = Frame_North_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_North_y;
			}
			else if (Direction == Direc_W)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_x)
				{
					Pos_Sor.x = Frame_West_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_West_y;
			}
			Last_Time = Current_Time;
		}
		break;
		//Convert_Object(Iso_Pos, Orth_Pos, Frame_Weight, Frame_Height);
	}
	case Attacking:
	{
		//cout << Orth_Pos.x << endl;
		int Frame_Weight = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Attacking_Frame_Weight;
		int Frame_Height = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Attacking_Frame_Height;
		int Time_Next_Sprite = Unit_Dt[Unit_Type].Time_Next_Attacking_Sprite;
		int Number_Frame_Direc = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Number_Attacking_Direction_Frame;
		int Focus_Point_x = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Attacking.x;
		int Focus_Point_y = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Attacking.y;
		//cout << Pos_Sor.h << endl;
		Orth_Pos.w = Pos_Sor.w = Iso_Pos.w = Frame_Weight;
		Orth_Pos.h = Pos_Sor.h = Iso_Pos.h = Frame_Height;
		if (Change_Status)
		{
			
			if (Direction == Direc_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_South_x;
			}
			else if (Direction == Direc_W_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
			}
			else if (Direction == Direc_W)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_x;
			}
			else if (Direction == Direc_W_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_North_x;
			}
			else if (Direction == Direc_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_North_x;
			}
			else if (Direction == Direc_E_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_North_x;
			}
			else if (Direction == Direc_E)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_x;
			}
			else if (Direction == Direc_E_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
			}
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
			Change_Status = false;
		}
		if ((Current_Time - Last_Time) > Time_Next_Sprite)
		{
			//cout << "yes";
			//cout << Pos_Sor.x << endl;
			if (Orth_Pos.x == Orth_Pos_Attack.x && Orth_Pos.y == Orth_Pos_Attack.y)
			{
				//cout << "yes";
			}
			if (Orth_Pos.x < Orth_Pos_Attack.x && Orth_Pos.y == Orth_Pos_Attack.y)
			{
				Direction = Direc_E_S;
				Pos_Sor.y = Frame_East_South_y;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_South_x)
				{
					Pos_Sor.x = Frame_East_South_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Orth_Pos.x > Orth_Pos_Attack.x && Orth_Pos.y == Orth_Pos_Attack.y)
			{
				Direction = Direc_W_N;
				Pos_Sor.y = Frame_West_North_y;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_North_x)
				{
					Pos_Sor.x = Frame_West_North_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Orth_Pos.x == Orth_Pos_Attack.x && Orth_Pos.y < Orth_Pos_Attack.y)
			{
				Direction = Direc_W_S;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_South_x)
				{
					Pos_Sor.x = Frame_West_South_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_West_South_y;
			}
			else if (Orth_Pos.x == Orth_Pos_Attack.x && Orth_Pos.y > Orth_Pos_Attack.y)
			{
				Direction = Direc_E_N;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_North_x)
				{
					Pos_Sor.x = Frame_East_North_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_East_North_y;
			}
			else if (Orth_Pos.x < Orth_Pos_Attack.x && Orth_Pos.y < Orth_Pos_Attack.y)
			{
				Direction = Direc_S;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_South_x)
				{
					Pos_Sor.x = Frame_South_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_South_y;
			}
			else if (Orth_Pos.x < Orth_Pos_Attack.x && Orth_Pos.y > Orth_Pos_Attack.y)
			{
				Direction = Direc_E;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_x)
				{
					Pos_Sor.x = Frame_East_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_East_y;
			}
			else if (Orth_Pos.x > Orth_Pos_Attack.x && Orth_Pos.y > Orth_Pos_Attack.y)
			{
				Direction = Direc_N;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_North_x)
				{
					Pos_Sor.x = Frame_North_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_North_y;
			}
			else if (Orth_Pos.x > Orth_Pos_Attack.x && Orth_Pos.y < Orth_Pos_Attack.y)
			{
				Direction = Direc_W;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_x)
				{
					Pos_Sor.x = Frame_West_x * Frame_Weight * Number_Frame_Direc;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_West_y;
			}
			//cout << Pos_Sor.x << endl;
			Last_Time = Current_Time;
		}
		
		break;
	}
	case Death:
	{
		if (Resource_Capacity == 0)
		{
			//cout << "Mat";
		}
		int Frame_Weight = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Death_Frame_Weight;
		int Frame_Height = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Death_Frame_Height;
		int Time_Next_Sprite = Unit_Dt[Unit_Type].Time_Next_Death_Sprite;
		int Number_Frame_Direc = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Number_Death_Direction_Frame;
		int Focus_Point_x = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Death.x;
		int Focus_Point_y = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Death.y;
		//cout << Pos_Sor.h << endl;
		Orth_Pos.w = Pos_Sor.w = Iso_Pos.w = Frame_Weight;
		Orth_Pos.h = Pos_Sor.h = Iso_Pos.h = Frame_Height;
		if (Change_Status)
		{
			if (Direction == Direc_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_South_x;
			}
			else if (Direction == Direc_W_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
			}
			else if (Direction == Direc_W)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_x;
			}
			else if (Direction == Direc_W_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_North_x;
			}
			else if (Direction == Direc_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_North_x;
			}
			else if (Direction == Direc_E_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_North_x;
			}
			else if (Direction == Direc_E)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_x;
			}
			else if (Direction == Direc_E_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
			}
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
			Change_Status = false;
		}
		if ((Current_Time - Last_Time) > Time_Next_Sprite)
		{
			if (Direction == Direc_E_S)
			{
				Pos_Sor.y = Frame_East_South_y;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_South_x)
				{
					if (Resource_Capacity <= 0)
					{
						Change_Object_Status(Dead);
						//Object_Status = Dead;
					}
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_W_N)
			{
				Pos_Sor.y = Frame_West_North_y;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_North_x)
				{
					if (Resource_Capacity <= 0)
					{
						Change_Object_Status(Dead);
						//Object_Status = Dead;
					}
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_W_S)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_South_x)
				{
					if (Resource_Capacity <= 0)
					{
						Change_Object_Status(Dead);
					}
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_West_South_y;
			}
			else if (Direction == Direc_E_N)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_North_x)
				{
					if (Resource_Capacity <= 0)
					{
						Change_Object_Status(Dead);
					}
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_East_North_y;
			}
			else if (Direction == Direc_S)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_South_x)
				{
					if (Resource_Capacity <= 0)
					{
						Change_Object_Status(Dead);
					}
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_South_y;
			}
			else if (Direction == Direc_E)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_x)
				{
					if (Resource_Capacity <= 0)
					{
						Change_Object_Status(Dead);
					}
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_East_y;
			}
			else if (Direction == Direc_N)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_North_x)
				{
					if (Resource_Capacity <= 0)
					{
						Change_Object_Status(Dead);
					}
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_North_y;
			}
			else if (Direction == Direc_W)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_x)
				{
					if (Resource_Capacity <= 0)
					{
						Change_Object_Status(Dead);
					}
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_West_y;
			}
			Last_Time = Current_Time;
		}
		
		break;
	}

	case Dead:
	{	
		int Frame_Weight = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Dead_Frame_Weight;
		int Frame_Height = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Dead_Frame_Height;
		int Time_Next_Sprite = Unit_Dt[Unit_Type].Time_Next_Dead_Sprite;
		int Number_Frame_Direc = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Number_Dead_Direction_Frame;
		int Focus_Point_x = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Dead.x;
		int Focus_Point_y = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Get_Unit_Type()].Focus_Point_Dead.y;
		//cout << Pos_Sor.h << endl;
		Orth_Pos.w = Pos_Sor.w = Iso_Pos.w = Frame_Weight;
		Orth_Pos.h = Pos_Sor.h = Iso_Pos.h = Frame_Height;
		if (Change_Status)
		{
			if (Direction == Direc_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_South_x;
			}
			else if (Direction == Direc_W_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
			}
			else if (Direction == Direc_W)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_x;
			}
			else if (Direction == Direc_W_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_North_x;
			}
			else if (Direction == Direc_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_North_x;
			}
			else if (Direction == Direc_E_N)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_North_x;
			}
			else if (Direction == Direc_E)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_x;
			}
			else if (Direction == Direc_E_S)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
			}
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
			Change_Status = false;
		}
		if ((Current_Time - Last_Time) > Time_Next_Sprite)
		{
			if (Direction == Direc_E_S)
			{
				Pos_Sor.y = Frame_East_South_y;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_South_x)
				{
					Change_Object_Status(Disappear);
					Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
					//Object_Status = Disappear;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_W_N)
			{
				Pos_Sor.y = Frame_West_North_y;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_North_x)
				{
					Change_Object_Status(Disappear);
					Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Direction == Direc_W_S)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_South_x)
				{
					Change_Object_Status(Disappear);
					Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_West_South_y;
			}
			else if (Direction == Direc_E_N)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_North_x)
				{
					Change_Object_Status(Disappear);
					Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_East_North_y;
			}
			else if (Direction == Direc_S)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_South_x)
				{
					Change_Object_Status(Disappear);
					Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_South_y;
			}
			else if (Direction == Direc_E)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_x)
				{
					Change_Object_Status(Disappear);
					Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_East_y;
			}
			else if (Direction == Direc_N)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_North_x)
				{
					Change_Object_Status(Disappear);
					Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_North_y;
			}
			else if (Direction == Direc_W)
			{
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_x)
				{
					Change_Object_Status(Disappear);
					Update_Cell(Map_2, Map_UG_Check_Click, Pos_in_List_Object);
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
				Pos_Sor.y = Frame_West_y;
			}
			Last_Time = Current_Time;
		}
		
		break;
	}
	//Convert_Object(Iso_Pos, Orth_Pos, Pos_Sor.w, Pos_Sor.h);
	}
}

void Game_Object::Move_Cell_x_to_Cell_y(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*> Civil_Computer_List, vector<Civil*>Civil_Player_List, int Pos)
{
	//cout << "ok";
}

void Game_Object::Update_Cell(Cell_Uniform_Grid Map[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], int Pos_in_List_Game_Object)
{
	if (!Alive)
	{
		if (Country == Gaia)
		{
			cout << " Xac nhan" << endl;
		}
		for (int i = 0; i < List_Cell_Contain_Object.size(); i++)
		{
			for (int j = 0; j < Map[List_Cell_Contain_Object[i].Row][List_Cell_Contain_Object[i].Col].List_Object_in_Cell.size(); j++)
			{
				if (Map[List_Cell_Contain_Object[i].Row][List_Cell_Contain_Object[i].Col].List_Object_in_Cell[j].Country == Country &&
					Map[List_Cell_Contain_Object[i].Row][List_Cell_Contain_Object[i].Col].List_Object_in_Cell[j].Pos == Pos_in_List_Game_Object)
				{
					Map[List_Cell_Contain_Object[i].Row][List_Cell_Contain_Object[i].Col].List_Object_in_Cell[j].Object_Type = -1;
					break;
				}
			}
		}

		for (int i = 0; i < List_Cell_Contain_Object_Click.size(); i++)
		{
			for (int j = 0; j < Map_UG_Check_Click[List_Cell_Contain_Object_Click[i].Row][List_Cell_Contain_Object_Click[i].Col].List_Object_in_Cell.size(); j++)
			{
				if (Map_UG_Check_Click[List_Cell_Contain_Object_Click[i].Row][List_Cell_Contain_Object_Click[i].Col].List_Object_in_Cell[j].Country == Country &&
					Map_UG_Check_Click[List_Cell_Contain_Object_Click[i].Row][List_Cell_Contain_Object_Click[i].Col].List_Object_in_Cell[j].Pos == Pos_in_List_Game_Object)
				{
					Map_UG_Check_Click[List_Cell_Contain_Object_Click[i].Row][List_Cell_Contain_Object_Click[i].Col].List_Object_in_Cell[j].Object_Type = -1;
					break;
				}
			}
		}
	}
	else
	{
		int a = this->Get_Orth_Pos().x / Cell_Size;
		int a_w = (this->Get_Orth_Pos().x + this->Size_Number_Cell * Orth_Tile_Height) / Cell_Size;
		int b = this->Get_Orth_Pos().y / Cell_Size;
		int b_h = (this->Get_Orth_Pos().y + this->Size_Number_Cell * Orth_Tile_Weight) / Cell_Size;
		vector<Cell_Contain_Object> Last_Cell;
		vector<Cell_Contain_Object> Current_Cell;
		bool Check = false;
		for (int s = 0; s < this->List_Cell_Contain_Object.size(); s++)
		{
			//cout << List_Cell_Contain_Object.size();
			Check = false;
			for (int p = a; p <= a_w; p++)
			{
				for (int q = b; q <= b_h; q++)
				{
					if (this->List_Cell_Contain_Object[s].Col == p && this->List_Cell_Contain_Object[s].Row == q)
					{
						Check = true;
					}
				}
			}
			//cout << List_Cell_Contain_Object[s].Row;
			if (!Check)
			{
				for (int g = 0; g < Map[this->List_Cell_Contain_Object[s].Row][this->List_Cell_Contain_Object[s].Col].List_Object_in_Cell.size(); g++)
				{
					if (Map[this->List_Cell_Contain_Object[s].Row][this->List_Cell_Contain_Object[s].Col].List_Object_in_Cell[g].Pos == Pos_in_List_Game_Object &&
						Map[this->List_Cell_Contain_Object[s].Row][this->List_Cell_Contain_Object[s].Col].List_Object_in_Cell[g].Country == Country)
					{
						Map[this->List_Cell_Contain_Object[s].Row][this->List_Cell_Contain_Object[s].Col].List_Object_in_Cell[g].Object_Type = -1;
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
				for (int s = 0; s < this->List_Cell_Contain_Object.size(); s++)
				{
					if (this->List_Cell_Contain_Object[s].Col == p && this->List_Cell_Contain_Object[s].Row == q)
					{
						Check = true;
					}
				}
				if (!Check)
				{
					bool Push = false;
					for (int k = 0; k < Map[q][p].List_Object_in_Cell.size(); k++)
					{
						if (Map[q][p].List_Object_in_Cell[k].Object_Type == -1)
						{
							Map[q][p].List_Object_in_Cell[k].Object_Type = this->Get_Unit_Type();
							Map[q][p].List_Object_in_Cell[k].Pos = Pos_in_List_Game_Object;
							Map[q][p].List_Object_in_Cell[k].Country = this->Get_Country();
							Map[q][p].List_Object_in_Cell[k].Unit_Type_Control = this->Unit_Type_Control;
							Map[q][p].List_Object_in_Cell[k].Pos_Control = this->Pos_Control;
							Push = true;
						}
					}
					if (!Push)
					{
						Cell_Object Cell_Object_Assign;
						Cell_Object_Assign.Object_Type = this->Get_Unit_Type();
						Cell_Object_Assign.Pos = Pos_in_List_Game_Object;
						Cell_Object_Assign.Country = this->Get_Country();
						Cell_Object_Assign.Unit_Type_Control = this->Unit_Type_Control;
						Cell_Object_Assign.Pos_Control = this->Pos_Control;
						Map[q][p].List_Object_in_Cell.push_back(Cell_Object_Assign);
					}
				}
			}
		}
		this->List_Cell_Contain_Object.clear();
		//cout << List_Cell_Contain_Object.size();
		for (int p = a; p <= a_w; p++)
		{
			for (int q = b; q <= b_h; q++)
			{
				Cell_Contain_Object Cell_Contain_Object_Assign;
				Cell_Contain_Object_Assign.Col = p;
				Cell_Contain_Object_Assign.Row = q;
				this->List_Cell_Contain_Object.push_back(Cell_Contain_Object_Assign);
			}
		}
		// Update chúng tới Map để xử lý click chuột
		a = this->Get_Iso_Pos().x / Cell_Size;
		a_w = (this->Get_Iso_Pos().x + this->Get_Iso_Pos().w) / Cell_Size;
		b = this->Get_Iso_Pos().y / Cell_Size;
		b_h = (this->Get_Iso_Pos().y + this->Get_Iso_Pos().h) / Cell_Size;
		//vector<Cell_Contain_Object> Last_Cell;
		//vector<Cell_Contain_Object> Current_Cell;
		Check = false;
		for (int s = 0; s < this->List_Cell_Contain_Object_Click.size(); s++)
		{
			//cout << List_Cell_Contain_Object.size();
			Check = false;
			for (int p = a; p <= a_w; p++)
			{
				for (int q = b; q <= b_h; q++)
				{
					if (this->List_Cell_Contain_Object_Click[s].Col == p && this->List_Cell_Contain_Object_Click[s].Row == q)
					{
						Check = true;
					}
				}
			}
			//cout << List_Cell_Contain_Object[s].Row;
			if (!Check)
			{
				for (int g = 0; g < Map_UG_Check_Click[this->List_Cell_Contain_Object_Click[s].Row][this->List_Cell_Contain_Object_Click[s].Col].List_Object_in_Cell.size(); g++)
				{
					if (Map_UG_Check_Click[this->List_Cell_Contain_Object_Click[s].Row][this->List_Cell_Contain_Object_Click[s].Col].List_Object_in_Cell[g].Pos == Pos_in_List_Game_Object &&
						Map_UG_Check_Click[this->List_Cell_Contain_Object_Click[s].Row][this->List_Cell_Contain_Object_Click[s].Col].List_Object_in_Cell[g].Country == Country)
					{
						/*if (this->Country != Map_UG_Check_Click[this->List_Cell_Contain_Object_Click[s].Row][this->List_Cell_Contain_Object_Click[s].Col].List_Object_in_Cell[g].Country)
						{
							cout << "Sai roi";
						}*/
						Map_UG_Check_Click[this->List_Cell_Contain_Object_Click[s].Row][this->List_Cell_Contain_Object_Click[s].Col].List_Object_in_Cell[g].Object_Type = -1;
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
				for (int s = 0; s < this->List_Cell_Contain_Object_Click.size(); s++)
				{
					if (this->List_Cell_Contain_Object_Click[s].Col == p && this->List_Cell_Contain_Object_Click[s].Row == q)
					{
						Check = true;
					}
				}
				if (!Check)
				{
					bool Push = false;
					for (int k = 0; k < Map_UG_Check_Click[q][p].List_Object_in_Cell.size(); k++)
					{
						if (Map_UG_Check_Click[q][p].List_Object_in_Cell[k].Object_Type == -1)
						{
							Map_UG_Check_Click[q][p].List_Object_in_Cell[k].Object_Type = this->Get_Unit_Type();
							Map_UG_Check_Click[q][p].List_Object_in_Cell[k].Pos = Pos_in_List_Game_Object;
							Map_UG_Check_Click[q][p].List_Object_in_Cell[k].Country = Country;
							Map_UG_Check_Click[q][p].List_Object_in_Cell[k].Unit_Type_Control = this->Unit_Type_Control;
							Map_UG_Check_Click[q][p].List_Object_in_Cell[k].Pos_Control = this->Pos_Control;
							Push = true;
						}
					}
					if (!Push)
					{
						Cell_Object Cell_Object_Assign;
						Cell_Object_Assign.Object_Type = this->Get_Unit_Type();
						Cell_Object_Assign.Pos = Pos_in_List_Game_Object;
						Cell_Object_Assign.Country = Country;
						Cell_Object_Assign.Unit_Type_Control = this->Unit_Type_Control;
						Cell_Object_Assign.Pos_Control = this->Pos_Control;
						Map_UG_Check_Click[q][p].List_Object_in_Cell.push_back(Cell_Object_Assign);
					}
				}
			}
		}
		this->List_Cell_Contain_Object_Click.clear();
		//cout << List_Cell_Contain_Object.size();
		for (int p = a; p <= a_w; p++)
		{
			for (int q = b; q <= b_h; q++)
			{
				Cell_Contain_Object Cell_Contain_Object_Assign;
				Cell_Contain_Object_Assign.Col = p;
				Cell_Contain_Object_Assign.Row = q;
				this->List_Cell_Contain_Object_Click.push_back(Cell_Contain_Object_Assign);
			}
		}
	}
}

/*void Dynamic_Object::Update_Cell(Cell_Uniform_Grid Map[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], int Pos_in_List_Game_Object)
{
	//cout << "Update";
	// Game Object Check : Đối tượng cần để kiểm tra xem


}*/

void Dynamic_Object::Attack(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], vector<Civil*> Civil_Computer_List, vector<Civil*>Civil_Player_List, int Pos)
{
	/*if (Unit_Type_Control == Computer)
	{
		cout << "yes";
	}*/
	//cout << "yes";
	if (Unit_Type != Villager) // Đối tượng thực hiện tìm kiếm này là quân lính, không phải nông dân
	{
		//cout << "yes" << endl;
		//cout << "yes";
		if (Object_Status == Standing) // Nếu đối tượng đang đứng yên thì thực hiện tìm kiếm này để tấn công đối tượng khác
		{
			int Row_Current = Orth_Pos.y / Orth_Tile_Height; // Tính hàng hiện tại đối tượng đang ở
			int Col_Current = Orth_Pos.x / Orth_Tile_Weight; // Tính cột hiện tại đối tượng đang ở
			//cout << "yes";
			for (int i = Row_Current - 2; i <= Row_Current + 2; i++) // Vì tôi hiện tại tôi chỉ xét vùng tìm kiếm (Search Radius) bằng 1, lên duyệt qua 9 ô xung quanh đối tượng, bao gồm cả ô chứa đối tượng
			{
				for (int j = Col_Current - 2; j <= Col_Current + 2; j++)
				{
					for (int k = 0; k < Map_2[i][j].List_Object_in_Cell.size(); k++)
					{
						//cout << "yes";
						if (Map_2[i][j].List_Object_in_Cell[k].Country != Country && Map_2[i][j].List_Object_in_Cell[k].Country != Country_Gaia && Map_2[i][j].List_Object_in_Cell[k].Object_Type != -1)
						{
							// Lấy các thông tin của đối tượng cần tấn công
							int Unit_Type_Object_Attack_Value = Map_2[i][j].List_Object_in_Cell[k].Object_Type;
							int Country_Object_Attack_Value = Map_2[i][j].List_Object_in_Cell[k].Country;
							int Pos_Object_Attack_Value = Map_2[i][j].List_Object_in_Cell[k].Pos;
							int Unit_Type_Control_Object_Attack_Value = Map_2[i][j].List_Object_in_Cell[k].Unit_Type_Control;
							int Pos_Control_Object_Attack_Value = Map_2[i][j].List_Object_in_Cell[k].Pos_Control;
							SDL_Rect Orth_Pos_Object_Attack_Value;
							if (Unit_Type_Control_Object_Attack_Value == Player)
							{
								Civil_Player_List[Pos_Control_Object_Attack_Value]->Civil_Game_Object_List[Pos_Object_Attack_Value]->Get_Infor_Attack_Object(Unit_Type, Pos_in_List_Object, Country, Unit_Type_Control, Pos_Control);
								Orth_Pos_Object_Attack_Value = Civil_Player_List[Pos_Control_Object_Attack_Value]->Civil_Game_Object_List[Pos_Object_Attack_Value]->Get_Orth_Pos();
								Set_Orth_Pos_Object_Attack(Civil_Player_List, Civil_Computer_List, Orth_Pos_Object_Attack_Value, Unit_Type_Object_Attack_Value, Pos_Object_Attack_Value, Country_Object_Attack_Value, Unit_Type_Control_Object_Attack_Value, Pos_Control_Object_Attack_Value); // Thiết đặt cho đối tượng này các thông tin về đối tượng sẽ tấn công
								Enable_Search_Move_To_Attack();
							}
							
						}
					}
				}
			}
		}
	}
	if (Hit_Box_Activated && (Object_Status != Death || Object_Status != Dead || Object_Status != Disappear))
	{
		//cout << "yes";
		SDL_Rect Orth_Pos_Attack_New = {};
		double Size_Number_Cell_Object_Attack = 0;
		if (Unit_Type_Control == Computer)
		{
			//cout << Moving_To_Attack;
		}
		if (Type_Control_Object_Object_Attack == Player) // Nếu đối tượng này tấn công đối tượng mà được Player điều khiển
		{
			//cout << "yes";
			Size_Number_Cell_Object_Attack = Civil_Player_List[Pos_Control_Object_Object_Attack]->Civil_Game_Object_List[Pos_Object_Attack]->Size_Number_Cell;
			Orth_Pos_Attack_New = Civil_Player_List[Pos_Control_Object_Object_Attack]->Civil_Game_Object_List[Pos_Object_Attack]->Get_Orth_Pos();
			Orth_Pos_Attack_New.x += Civil_Player_List[Pos_Control_Object_Object_Attack]->Civil_Game_Object_List[Pos_Object_Attack]->Size_Number_Cell / 2 * Orth_Tile_Height;
			Orth_Pos_Attack_New.y += Civil_Player_List[Pos_Control_Object_Object_Attack]->Civil_Game_Object_List[Pos_Object_Attack]->Size_Number_Cell / 2 * Orth_Tile_Height;
		}
		else if (Type_Control_Object_Object_Attack == Computer)
		{
			//cout << "yes1";
			Size_Number_Cell_Object_Attack = Civil_Computer_List[Pos_Control_Object_Object_Attack]->Civil_Game_Object_List[Pos_Object_Attack]->Size_Number_Cell;
			Orth_Pos_Attack_New = Civil_Computer_List[Pos_Control_Object_Object_Attack]->Civil_Game_Object_List[Pos_Object_Attack]->Get_Orth_Pos();
			cout << "Toa do ban dau" << Orth_Pos_Attack.x << endl;
			cout << "Toa do goc" << Orth_Pos_Attack_New.x << endl;
			Orth_Pos_Attack_New.x += Civil_Computer_List[Pos_Control_Object_Object_Attack]->Civil_Game_Object_List[Pos_Object_Attack]->Size_Number_Cell / 2 * Orth_Tile_Height;
			Orth_Pos_Attack_New.y += Civil_Computer_List[Pos_Control_Object_Object_Attack]->Civil_Game_Object_List[Pos_Object_Attack]->Size_Number_Cell / 2 * Orth_Tile_Height;
			cout << "Toa do goc moi" << Orth_Pos_Attack_New.x << endl;
		}
		if (Orth_Pos_Attack_New.x != Orth_Pos_Attack.x || Orth_Pos_Attack_New.y != Orth_Pos_Attack.y)
		{
			cout << "Reset" << endl;
			Orth_Pos_Attack = Orth_Pos_Attack_New;
			//Orth_Pos_Attack_New.x += 190;
			//Orth_Pos_Attack_New.y += 190;
			Search_Move_To_Attack = true;
			Moving_To_Attack = true;
			Set_Orth_Pos_Object_Attack(Civil_Player_List, Civil_Computer_List, Orth_Pos_Attack_New, Unit_Type_Object_Attack, Pos_Object_Attack, Country_Object_Attack, Type_Control_Object_Object_Attack, Pos_Control_Object_Object_Attack);
		}
		//Orth_Pos_Attack.x += 90;
		//Orth_Pos_Attack.y += 90;
		//Last_Time_Attack = Current_Time_Attack;
		if (Object_Status == Attacking || Moving_To_Attack)
		{
			if (Unit_Type_Control == Computer)
			{
				//cout << "Checked";
			}
			//cout << "yes";
			//cout << fabs(Orth_Pos.x / Orth_Tile_Height - Orth_Pos_Attack.x / Orth_Tile_Height) << " " << fabs(Orth_Pos.y / Orth_Tile_Height - Orth_Pos_Attack.y / Orth_Tile_Height) << endl;
			//cout << ((fabs(Orth_Pos.x / Orth_Tile_Height - Orth_Pos_Attack.x / Orth_Tile_Height) <= Attack_Range) && (fabs(Orth_Pos.y / Orth_Tile_Height - Orth_Pos_Attack.y / Orth_Tile_Height) <= Attack_Range)) << endl;
			//cout << Attack_Range << endl;

			if (Cal_Distance(Orth_Pos, Orth_Pos_Attack) <= (1.0 + Size_Number_Cell_Object_Attack / 2) * Orth_Tile_Height || Attack_Object)
			{
				if (Unit_Type_Control == Computer)
				{
					//cout << "Checked";
				}
				//cout << "Checked" << endl;
				if ((fabs(Orth_Pos.x / Orth_Tile_Height - Orth_Pos_Attack.x / Orth_Tile_Height) >= 3 || fabs(Orth_Pos.y / Orth_Tile_Height - Orth_Pos_Attack.y / Orth_Tile_Height) >= 3))
				{
					cout << "Reset";
					Moving_To_Attack = true;
					Attack_Object = false;
					return;
				}
				//Attack_Object = true;
				if (Object_Status != Attacking)
				{
					Change_Object_Status(Attacking);
				}
				
				Hit_Box_Activated = true;
				Moving_To_Attack = false;
			}
			else
			{
				if (Unit_Type_Control == Computer)
				{
					if (Moving_To_Attack)
					{
						//cout << "Checked";
					}
					
				}
				//cout << "Check";
				Enable_Moving_To_Attack();
				//cout << "Yes" << endl;
				
				if (Search_Move_To_Attack)
				{
					Search_A_Star = true;
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Attack, Path, Search_A_Star);
					Search_Move_To_Attack = false;
				}
				Change_Object_Status(Moving); // Chuyển trạng thái của đối tượng để đối tượng có thể di chuyển tới mục tiêu
				//Move(Unit_Dt, Country, Map_1, Map_2, Map_UG_Check_Click, Civil_Computer_List, Civil_Player_List, Pos);
			}
		}
	}
	
	
}

Hit_Box Dynamic_Object::Get_Hit_Box()
{
	return Hit_Box_Damage;
}

void Dynamic_Object::Set_Hit_Box(int Row, int Col, int Damage, int Blast_Width, int Blast_Attack_Type)
{
	//cout << "Hit Box";
	Hit_Box_Damage.Row = Row;
	Hit_Box_Damage.Col = Col;
	Hit_Box_Damage.Damage = Damage;
	Hit_Box_Damage.Blast_Width = Blast_Width;
	Hit_Box_Damage.Blast_Attack_Type = Blast_Attack_Type;
	Hit_Box_Activated = true;
}

bool Dynamic_Object::Check_Hit_Box_Activated()
{
	return Hit_Box_Activated;
}

void Dynamic_Object::Disable_Hit_Box()
{
	Moving_To_Attack = false;
	Attack_Object = false;
	Change_Object_Status(Standing);
	//Object_Status = Standing;
	Hit_Box_Activated = false;
}

/*void Dynamic_Object::1_Cell_x_to_Cell_y(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], vector<Game_Object*> List_Game_Object, int Pos)
{
	Current_Time = SDL_GetTicks();
	int Frame_Delay = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Moving_Next_Frame;
	int Number_Frame_Direc = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Number_Moving_Direction_Frame;
	bool Move = ((Current_Time - Last_Time) > Frame_Delay);
	int Weight = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Moving_Frame_Weight;
	int Height = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Moving_Frame_Height;
	Orth_Pos.w = Iso_Pos.w = Weight;
	Orth_Pos.h = Iso_Pos.h = Height;
	int Speed = Unit_Dt[Unit_Type].Speed;
	//cout << "yes";
	if (!Path.empty() && Moving && Move)
	{
		//cout << "yes";
		if (Orth_Pos.y / Orth_Tile_Weight == Path.top().first && Orth_Pos.x / Orth_Tile_Weight < Path.top().second)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.x += Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Game_Object_Test, List_Game_Object, Pos))
			{
				return;
			}
			Orth_Pos.x += Speed;
			Update_Cell( Map_2,Pos);
			Direction = Direc_E_S;
		}
		else if (Orth_Pos.y / Orth_Tile_Weight == Path.top().first && Orth_Pos.x / Orth_Tile_Weight > Path.top().second)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.x -= Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Game_Object_Test, List_Game_Object, Pos))
			{
				return;
			}
			Orth_Pos.x -= Speed;
			Update_Cell(Map_2, Pos);
			Direction = Direc_W_N;
		}
		else if (Orth_Pos.x / Orth_Tile_Weight == Path.top().second && Orth_Pos.y / Orth_Tile_Weight < Path.top().first)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.y += Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Game_Object_Test, List_Game_Object, Pos))
			{
				return;
			}
			Orth_Pos.y += Speed;
			Update_Cell(Map_2, Pos);
			Direction = Direc_W_S;
			
		}
		else if (Orth_Pos.x / Orth_Tile_Weight == Path.top().second && Orth_Pos.y / Orth_Tile_Weight > Path.top().first)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.y -= Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Game_Object_Test, List_Game_Object, Pos))
			{
				return;
			}
			Orth_Pos.y -= Speed;
			Update_Cell(Map_2, Pos);
			Direction = Direc_E_N; //*...............
		}
		else if (Orth_Pos.y / Orth_Tile_Weight < Path.top().first && Orth_Pos.x / Orth_Tile_Weight < Path.top().second)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.x += Speed;
			Orth_Pos_Test.y += Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Game_Object_Test, List_Game_Object, Pos))
			{
				return;
			}
			Orth_Pos.x += Speed;
			Orth_Pos.y += Speed;
			Update_Cell(Map_2, Pos);
			Direction = Direc_S;
			
		}
		else if (Orth_Pos.y / Orth_Tile_Weight > Path.top().first&& Orth_Pos.x / Orth_Tile_Weight < Path.top().second)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.x += Speed;
			Orth_Pos_Test.y -= Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Game_Object_Test, List_Game_Object, Pos))
			{
				return;
			}
			Orth_Pos.x += Speed;
			Orth_Pos.y -= Speed;
			Update_Cell(Map_2, Pos);
			Direction = Direc_E;
			
		}
		else if (Orth_Pos.y / Orth_Tile_Weight > Path.top().first&& Orth_Pos.x / Orth_Tile_Weight > Path.top().second)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.x -= Speed;
			Orth_Pos_Test.y -= Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Game_Object_Test, List_Game_Object, Pos))
			{
				return;
			}
			Orth_Pos.x -= Speed;
			Orth_Pos.y -= Speed;
			Update_Cell(Map_2, Pos);
			Direction = Direc_N;
			
		}
		else if (Orth_Pos.y / Orth_Tile_Weight<Path.top().first && Orth_Pos.x / Orth_Tile_Weight>Path.top().second)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.x -= Speed;
			Orth_Pos_Test.y += Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Game_Object_Test, List_Game_Object, Pos))
			{
				return;
			}
			Orth_Pos.x -= Speed;
			Orth_Pos.y += Speed;
			Update_Cell(Map_2, Pos);
			Direction = Direc_W;
		}
		if (Orth_Pos.x / Orth_Tile_Weight == Path.top().second && Orth_Pos.y / Orth_Tile_Weight == Path.top().first)
		{
			//cout << "yes";
			Moving = false;
			Path.pop();
			//cout << "EX";
		}
		Convert_Object(Iso_Pos, Orth_Pos, Weight, Height);
		Last_Time = Current_Time;
	}
	if (!Path.empty() && !Moving)
	{
		Moving = true;
	}
	if (Path.empty())
	{
		//cout << "OK";
		//cout << "yes";
		Standing = true;
		Moving = false;
	}
}*/

void Dynamic_Object::Move_Cell_x_to_Cell_y(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*> Civil_Computer_List, vector<Civil*>Civil_Player_List, int Pos)
{
	//cout << "um";
	Current_Time_Move = SDL_GetTicks();
	int Frame_Delay = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Moving_Next_Frame;
	int Number_Frame_Direc = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Number_Moving_Direction_Frame;
	bool Move = ((Current_Time_Move - Last_Time_Move) > 20);
	int Weight = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Moving_Frame_Weight;
	int Height = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Moving_Frame_Height;
	Orth_Pos.w = Pos_Sor.w = Iso_Pos.w = Weight;
	Orth_Pos.h = Pos_Sor.h = Iso_Pos.h = Height;
	int Speed = Unit_Dt[Unit_Type].Speed;
	if (Path.empty())
	{
		//return;
	}
		//cout << "Yes";
	//cout << "yes";
	if (Path.empty())
	{
		//cout << "Rong" << endl;
		//cout << "OK";
		//cout << "yes";
		//Update_Cell(Map_2, Pos);
		//cout << Orth_Pos.y / Orth_Tile_Height << " " << Orth_Pos.x / Orth_Tile_Height << endl;
		//cout << Check_Cell_Empty(List_Cell_Contain_Object[0].Row, List_Cell_Contain_Object[0].Col, Map_2);
		//cout << List_Cell_Contain_Object[0].Row << List_Cell_Contain_Object[0].Col << endl;
		//cout << Check_Cell_Empty(List_Cell_Contain_Object[0].Row, List_Cell_Contain_Object[0].Col, Map_2) << endl;
		if (Moving_To_Attack)
		{
			//cout << "OK";
			if (Orth_Pos.x / Orth_Tile_Height == Orth_Pos_Attack.x / Orth_Tile_Height && Orth_Pos.y / Orth_Tile_Height == Orth_Pos_Attack.y / Orth_Tile_Height) // Nếu nó đã ở ô cần tới thì đưa nó về trạng thái ngừng di chuyển
			{
				Search_A_Star = false;
				Change_Object_Status(Attacking);
			}
			else
			{
				Search_A_Star = true;
			}
			//Object_Status = Attacking;
			//Moving_To_Attack = false;
		}
		else if (Moving_To_Work)
		{
			if (Orth_Pos.x / Orth_Tile_Height == Orth_Pos_Work.x / Orth_Tile_Height && Orth_Pos.y / Orth_Tile_Height == Orth_Pos_Work.y / Orth_Tile_Height) // Nếu nó đã ở ô cần tới thì đưa nó về trạng thái ngừng di chuyển
			{
				Search_A_Star = false;
				Change_Object_Status(Working);
			}
			else
			{
				//cout << "yes";
				Search_A_Star = true;
			}
		}
		else if (Going_to_return_resource)
		{
			//cout << "OK";
			
			//Moving_To_Attack = false;
		}
		else
		{
			//cout << "dung" << endl;
			if (Orth_Pos.x / Orth_Tile_Height == Orth_Pos_Move.x / Orth_Tile_Height && Orth_Pos.y / Orth_Tile_Height == Orth_Pos_Move.y / Orth_Tile_Height) // Nếu nó đã ở ô cần tới thì đưa nó về trạng thái ngừng di chuyển
			{
				Search_A_Star = false;
				Change_Object_Status(Standing);
			}
			else
			{
				//cout << "yes";
				Search_A_Star = true;
			}
			
			//Object_Status = Standing;
		}
		
		return;
		//Convert_Object(Iso_Pos, Orth_Pos, Weight, Height);
	}
	//Convert_Object(Iso_Pos, Orth_Pos, Weight, Height);
	//cout << ((!Path.empty()) && (Object_Status == Moving) && Move);
	if ((!Path.empty()) && (Object_Status == Moving || Object_Status == Carry) && Move)
	{
		//cout << "yes";
		//cout << "yes";
		//Orth_Pos.y / Orth_Tile_Weight == Path.top().first && Orth_Pos.x / Orth_Tile_Weight < Path.top().second
		//ut << Check_Cell_Empty(this, 7, 4, Map_2) << endl;
		//cout << "Vi tri ban dau : " << (Orth_Pos.y / Orth_Tile_Height) << " " << (Orth_Pos.x / Orth_Tile_Weight) << endl;
		//cout << "Vi tri cuoi cung : " << (Orth_Pos_Capacity.y / Orth_Tile_Height) << " " << (Orth_Pos_Capacity.x / Orth_Tile_Weight) << endl;
		//cout << Path.top().first << " " << Path.top().second << endl;
		if (Orth_Pos.y == Path.top().first * Orth_Tile_Height && Orth_Pos.x < Path.top().second * Orth_Tile_Weight)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell); // Tạo ra một đối tượng gán nhằm thử xem nếu đối tượng này di chuyển một đoạn như vậy thì có va chạm không
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.x += Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 0)
			{
				Search_A_Star = true;
				if (Going_to_return_resource)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Capacity, Path, Search_A_Star);
				}
				else if (Moving_To_Work)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Work, Path, Search_A_Star);
				}
				else
				{
					A_Star_Search(this, Map_1, Map_2, Dynamic_Object::Orth_Pos, Dynamic_Object::Orth_Pos_Move, Dynamic_Object::Path, Dynamic_Object::Search_A_Star);
				}

				return;
			}
			else if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 1)
			{
				Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
				Update_Cell(Map_2, Map_UG_Check_Click, Pos);
				Direction = Direc_E_S;
				return;
			}
			//else
			delete(Game_Object_Test);
			Orth_Pos.x += Speed;
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos);
			Direction = Direc_E_S;
		}
		else if (Orth_Pos.y == Path.top().first * Orth_Tile_Height && Orth_Pos.x > Path.top().second* Orth_Tile_Weight)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.x -= Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 0)
			{
				Search_A_Star = true;
				if (Going_to_return_resource)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Capacity, Path, Search_A_Star);
				}
				else if (Moving_To_Work)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Work, Path, Search_A_Star);
				}
				else
				{
					A_Star_Search(this, Map_1, Map_2, Dynamic_Object::Orth_Pos, Dynamic_Object::Orth_Pos_Move, Dynamic_Object::Path, Dynamic_Object::Search_A_Star);
				}
				return;
			}
			else if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 1)
			{
				Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
				Update_Cell(Map_2, Map_UG_Check_Click, Pos);
				Direction = Direc_W_N;
				return;
			}
			delete(Game_Object_Test);
			Orth_Pos.x -= Speed;
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos);
			Direction = Direc_W_N;
		}
		else if (Orth_Pos.y < Path.top().first * Orth_Tile_Height && Orth_Pos.x == Path.top().second * Orth_Tile_Weight)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.y += Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 0)
			{
				Search_A_Star = true;
				if (Going_to_return_resource)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Capacity, Path, Search_A_Star);
				}
				else if (Moving_To_Work)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Work, Path, Search_A_Star);
				}
				else
				{
					A_Star_Search(this, Map_1, Map_2, Dynamic_Object::Orth_Pos, Dynamic_Object::Orth_Pos_Move, Dynamic_Object::Path, Dynamic_Object::Search_A_Star);
				}
				return;
			}
			else if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 1)
			{
				Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
				Update_Cell(Map_2, Map_UG_Check_Click, Pos);
				Direction = Direc_W_S;
				return;
			}
			delete(Game_Object_Test);
			Orth_Pos.y += Speed;
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos);
			Direction = Direc_W_S;

		}
		else if (Orth_Pos.y > Path.top().first* Orth_Tile_Height&& Orth_Pos.x == Path.top().second * Orth_Tile_Weight)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.y -= Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 0)
			{
				Search_A_Star = true;
				if (Going_to_return_resource)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Capacity, Path, Search_A_Star);
				}
				else if (Moving_To_Work)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Work, Path, Search_A_Star);
				}
				else
				{
					A_Star_Search(this, Map_1, Map_2, Dynamic_Object::Orth_Pos, Dynamic_Object::Orth_Pos_Move, Dynamic_Object::Path, Dynamic_Object::Search_A_Star);
				}
				return;
			}
			else if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 1)
			{
				Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
				Update_Cell(Map_2, Map_UG_Check_Click, Pos);
				Direction = Direc_E_N;
				return;
			}
			delete(Game_Object_Test);
			Orth_Pos.y -= Speed;
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos);
			Direction = Direc_E_N; //*...............
		}
		else if (Orth_Pos.y < Path.top().first * Orth_Tile_Height && Orth_Pos.x < Path.top().second * Orth_Tile_Weight)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.x += Speed;
			Orth_Pos_Test.y += Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 0)
			{
				Search_A_Star = true;
				if (Going_to_return_resource)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Capacity, Path, Search_A_Star);
				}
				else if (Moving_To_Work)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Work, Path, Search_A_Star);
				}
				else
				{
					A_Star_Search(this, Map_1, Map_2, Dynamic_Object::Orth_Pos, Dynamic_Object::Orth_Pos_Move, Dynamic_Object::Path, Dynamic_Object::Search_A_Star);
				}
				return;
			}
			else if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 1)
			{
				Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
				Update_Cell(Map_2, Map_UG_Check_Click, Pos);
				Direction = Direc_S;
				return;
			}
			delete(Game_Object_Test);
			Orth_Pos.x += Speed;
			Orth_Pos.y += Speed;
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos);
			Direction = Direc_S;

		}
		else if (Orth_Pos.y > Path.top().first* Orth_Tile_Height&& Orth_Pos.x < Path.top().second * Orth_Tile_Weight)
		{
			//cout << "yes";
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.x += Speed;
			Orth_Pos_Test.y -= Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 0)
			{
				Search_A_Star = true;
				if (Going_to_return_resource)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Capacity, Path, Search_A_Star);
				}
				else if (Moving_To_Work)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Work, Path, Search_A_Star);
				}
				else
				{
					A_Star_Search(this, Map_1, Map_2, Dynamic_Object::Orth_Pos, Dynamic_Object::Orth_Pos_Move, Dynamic_Object::Path, Dynamic_Object::Search_A_Star);
				}
				return;
			}
			else if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 1)
			{
				Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
				Update_Cell(Map_2, Map_UG_Check_Click, Pos);
				Direction = Direc_E;
				return;
			}
			delete(Game_Object_Test);
			Orth_Pos.x += Speed;
			Orth_Pos.y -= Speed;
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos);
			Direction = Direc_E;

		}
		else if (Orth_Pos.y > Path.top().first* Orth_Tile_Height&& Orth_Pos.x > Path.top().second* Orth_Tile_Weight)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.x -= Speed;
			Orth_Pos_Test.y -= Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 0)
			{
				Search_A_Star = true;
				if (Going_to_return_resource)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Capacity, Path, Search_A_Star);
				}
				else if (Moving_To_Work)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Work, Path, Search_A_Star);
				}
				else
				{
					A_Star_Search(this, Map_1, Map_2, Dynamic_Object::Orth_Pos, Dynamic_Object::Orth_Pos_Move, Dynamic_Object::Path, Dynamic_Object::Search_A_Star);
				}
				return;
			}
			else if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 1)
			{
				Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
				Update_Cell(Map_2, Map_UG_Check_Click, Pos);
				Direction = Direc_N;
				return;
			}
			delete Game_Object_Test;
			Orth_Pos.x -= Speed;
			Orth_Pos.y -= Speed;
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos);
			Direction = Direc_N;
			//cout << Path.size();
			//cout << "yes";
		}
		else if (Orth_Pos.y < Path.top().first * Orth_Tile_Height && Orth_Pos.x > Path.top().second* Orth_Tile_Weight)
		{
			Game_Object* Game_Object_Test = new Dynamic_Object(Size_Number_Cell);
			SDL_Rect Orth_Pos_Test = Get_Orth_Pos();
			Orth_Pos_Test.x -= Speed;
			Orth_Pos_Test.y += Speed;
			Game_Object_Test->Change_Orth_Pos(Orth_Pos_Test);
			if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 0)
			{
				Search_A_Star = true;
				if (Going_to_return_resource)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Capacity, Path, Search_A_Star);
				}
				else if (Moving_To_Work)
				{
					A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Work, Path, Search_A_Star);
				}
				else
				{
					A_Star_Search(this, Map_1, Map_2, Dynamic_Object::Orth_Pos, Dynamic_Object::Orth_Pos_Move, Dynamic_Object::Path, Dynamic_Object::Search_A_Star);
				}
				return;
			}
			else if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, Game_Object_Test, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos) == 1)
			{
				Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
				Update_Cell(Map_2, Map_UG_Check_Click, Pos);
				Direction = Direc_W;
				return;
			}
			delete(Game_Object_Test);
			Orth_Pos.x -= Speed;
			Orth_Pos.y += Speed;
			Convert_Object(this, Iso_Pos, Orth_Pos, Weight, Height);
			Update_Cell(Map_2, Map_UG_Check_Click, Pos);
			Direction = Direc_W;
		}
		if (Orth_Pos.y == Path.top().first * Orth_Tile_Height && Orth_Pos.x == Path.top().second * Orth_Tile_Weight)
		{
			//cout << "yes";
			Path.pop();
			/*if (Path.empty())
			{
				cout << "yes";
				Object_Status = Standing;
			}
			//cout << Path.size();
			//cout << "EX";*/
		}
		//Convert_Object(Iso_Pos, Orth_Pos, Weight, Height);
		Last_Time_Move = Current_Time_Move;
	}
	//cout << Orth_Pos.x << endl;
	
}

void Dynamic_Object::Enable_Search_A_Star()
{

	Search_A_Star = true;
}

int Game_Object::Check_Collision(Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Game_Object* Game_Object_Check, Civil* Civil_Gaia_List, vector<Civil*>& Civil_Computer_List, vector<Civil*>& Civil_Player_List, int Pos)
{
	int a = Game_Object_Check->Orth_Pos.x / Cell_Size;
	int a_w = (Game_Object_Check->Orth_Pos.x + Game_Object_Check->Size_Number_Cell * Orth_Tile_Height) / Cell_Size;
	int b = Game_Object_Check->Orth_Pos.y / Cell_Size;
	int b_h = (Game_Object_Check->Orth_Pos.y + Game_Object_Check->Size_Number_Cell * Orth_Tile_Height) / Cell_Size;
	vector<Cell_Object> List_Cell_Object_Return;
	for (int p = a; p <= a_w; p++)
	{
		for (int q = b; q <= b_h; q++)
		{
			for (int s = 0; s < Map_2[q][p].List_Object_in_Cell.size(); s++)
			{
				if (Map_2[q][p].List_Object_in_Cell[s].Object_Type != -1 && Map_2[q][p].List_Object_in_Cell[s].Pos != Pos)
				{
					List_Cell_Object_Return.push_back(Map_2[q][p].List_Object_in_Cell[s]);
				}

			}
		}
	}
	//cout << List_Cell_Object_Return.size();
	//cout << Civil_Computer_List[0]->Civil_Game_Object_List.size();
	for (int i = 0; i < List_Cell_Object_Return.size(); i++)
	{
		for (int j = 0; j < Civil_Player_List.size(); j++)
		{
			//cout << Civil_Player_List[j]->Get_Civil_Index() << endl;
			if (Civil_Player_List[j]->Get_Civil_Index() == List_Cell_Object_Return[i].Country)
			{
				SDL_Rect A = Civil_Player_List[j]->Civil_Game_Object_List[List_Cell_Object_Return[i].Pos]->Get_Orth_Pos();
				double S_N_Cell_A = Civil_Player_List[j]->Civil_Game_Object_List[List_Cell_Object_Return[i].Pos]->Size_Number_Cell;
				SDL_Rect B = Game_Object_Check->Get_Orth_Pos();
				double S_N_Cell_B = Game_Object_Check->Size_Number_Cell;
				bool Overlap_x = A.x<=B.x + S_N_Cell_B * Orth_Tile_Weight && A.x + S_N_Cell_A * Orth_Tile_Weight>=B.x;
				bool Overlap_y = A.y<=B.y + S_N_Cell_B * Orth_Tile_Height && A.y + S_N_Cell_A * Orth_Tile_Height>=B.y;
				bool OverLap = Overlap_x && Overlap_y;
				if (OverLap)
				{
					if (Moving_To_Attack)
					{
						//cout << "yes";
						if (Unit_Type_Object_Attack == Civil_Player_List[j]->Civil_Game_Object_List[List_Cell_Object_Return[i].Pos]->Get_Unit_Type() &&
							Pos_Object_Attack == Civil_Player_List[j]->Civil_Game_Object_List[List_Cell_Object_Return[i].Pos]->Pos_in_List_Object &&
							Country_Object_Attack == Civil_Player_List[j]->Get_Civil_Index() &&
							Type_Control_Object_Object_Attack == Player)
						{
							cout << "Toi luc can tan cong" << endl;
							Moving_To_Attack = false;
							Change_Object_Status(Attacking);
							
							Attack_Object = true;
							return 1;
						}
					}
					else if (Going_to_return_resource)
					{
						if (Unit_Type_Capacity == Civil_Player_List[j]->Civil_Game_Object_List[List_Cell_Object_Return[i].Pos]->Get_Unit_Type() &&
							Pos_Capacity == Civil_Player_List[j]->Civil_Game_Object_List[List_Cell_Object_Return[i].Pos]->Pos_in_List_Object)
						{
							return 3;
						}
					}
					
					cout << " Va cham roi aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa " << endl;
					return 0;
				}
			}
			
		}
		for (int j = 0; j < Civil_Computer_List.size(); j++)
		{
			//cout << "Size" << Civil_Computer_List.size() << endl;
			//cout <<"Country "<< List_Cell_Object_Return[i].Country << endl;
			//cout << Civil_Computer_List[j]->Get_Civil_Index() << endl;
			if (Civil_Computer_List[j]->Get_Civil_Index() == List_Cell_Object_Return[i].Country)
			{
				//cout << "uhm";
				SDL_Rect A = Civil_Computer_List[j]->Civil_Game_Object_List[List_Cell_Object_Return[i].Pos]->Get_Orth_Pos();
				double S_N_Cell_A = Civil_Computer_List[j]->Civil_Game_Object_List[List_Cell_Object_Return[i].Pos]->Size_Number_Cell;
				SDL_Rect B = Game_Object_Check->Get_Orth_Pos();
				double S_N_Cell_B = Game_Object_Check->Size_Number_Cell;
				bool Overlap_x = A.x<=B.x + S_N_Cell_B * Orth_Tile_Weight && A.x + S_N_Cell_A * Orth_Tile_Weight>=B.x;
				bool Overlap_y = A.y<=B.y + S_N_Cell_B * Orth_Tile_Height && A.y + S_N_Cell_A * Orth_Tile_Height>=B.y;
				bool OverLap = Overlap_x && Overlap_y;
				/*cout << "A X : " << A.x << endl;
				cout << "A Y : " << A.y << endl;
				cout << "A W : " << A.w << endl;
				cout << "A H : " << A.h << endl;
				cout << "B X : " << B.x << endl;
				cout << "B Y : " << B.y << endl;
				cout << "B W : " << B.w << endl;
				cout << "B H : " << B.h << endl;*/
				if (OverLap)
				{
					if (Moving_To_Attack)
					{
						if (Unit_Type_Object_Attack == Civil_Computer_List[j]->Civil_Game_Object_List[List_Cell_Object_Return[i].Pos]->Get_Unit_Type() &&
							Pos_Object_Attack == Civil_Computer_List[j]->Civil_Game_Object_List[List_Cell_Object_Return[i].Pos]->Pos_in_List_Object &&
							Country_Object_Attack == Civil_Computer_List[j]->Get_Civil_Index() &&
							Type_Control_Object_Object_Attack == Computer)
						{
							cout << "Toi luc can tan cong" << endl;
							Moving_To_Attack = false;
							Change_Object_Status(Attacking);
							Attack_Object = true;
							return 1;
						}
					}
					//cout << "OK";
					cout << " Va cham roi " << endl;
					return 0;
				}
			}
			
		}
		for (int j = 0; j < Civil_Gaia_List->Civil_Game_Object_List.size(); j++)
		{
			if (List_Cell_Object_Return[i].Country == Gaia)
			{
				//cout << "uhm";
				SDL_Rect A = Civil_Gaia_List->Civil_Game_Object_List[List_Cell_Object_Return[i].Pos]->Get_Orth_Pos();
				double S_N_Cell_A = Civil_Gaia_List->Civil_Game_Object_List[List_Cell_Object_Return[i].Pos]->Size_Number_Cell;
				SDL_Rect B = Game_Object_Check->Get_Orth_Pos();
				double S_N_Cell_B = Game_Object_Check->Size_Number_Cell;
				bool Overlap_x = A.x<B.x + S_N_Cell_B * Orth_Tile_Weight && A.x + S_N_Cell_A * Orth_Tile_Weight>B.x;
				bool Overlap_y = A.y<B.y + S_N_Cell_B * Orth_Tile_Height && A.y + S_N_Cell_A * Orth_Tile_Height>B.y;
				bool OverLap = Overlap_x && Overlap_y;
				/*cout << "A X : " << A.x << endl;
				cout << "A Y : " << A.y << endl;
				cout << "A W : " << A.w << endl;
				cout << "A H : " << A.h << endl;
				cout << "B X : " << B.x << endl;
				cout << "B Y : " << B.y << endl;
				cout << "B W : " << B.w << endl;
				cout << "B H : " << B.h << endl;*/
				if (OverLap)
				{
					//cout << "OK";
					cout << " Va cham roi " << endl;
					return 0;
				}
			}
		}
		//cout << List_Cell_Object_Return.size();
		
	}
	return -1;
}

void Game_Object::Enable_Find_to_Build_House(int Unit_Type_Build_Value)
{

}

void Game_Object::Disable_Find_to_Build_House()
{
}

bool Game_Object::Get_Find_to_Build_House()
{
	return false;
}

int Game_Object::Get_Unit_Type_Build()
{
	return 0;
}

int Game_Object::Change_Hit_Point(int Value_Hit_Point)
{
	Hit_Point = Value_Hit_Point;
	return 0;
}

void Game_Object::Add_Hit_Point(int Value_Hit_Point_Add)
{
	Hit_Point += Value_Hit_Point_Add;
}

void Dynamic_Object::Move(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*>& Civil_Computer_List, vector<Civil*>& Civil_Player_List, int Pos)
{
	//Clear_Stack(Path);
	//cout << Path.size();
	//cout << "co ve dung";
	//cout << Orth_Pos_Move.x << endl;
	//cout << Orth_Pos_Move.y << endl;
	//Search_A_Star = true;
	if (Search_A_Star)
	{
		if (Moving_To_Work)
		{
			A_Star_Search(this, Map_1, Map_2, Dynamic_Object::Orth_Pos, Dynamic_Object::Orth_Pos_Work, Dynamic_Object::Path, Dynamic_Object::Search_A_Star);
		}
		else if (Going_to_return_resource)
		{
			A_Star_Search(this, Map_1, Map_2, Dynamic_Object::Orth_Pos, Dynamic_Object::Orth_Pos_Capacity, Dynamic_Object::Path, Dynamic_Object::Search_A_Star);
		}
		else if (Moving_To_Attack)
		{
			A_Star_Search(this, Map_1, Map_2, Dynamic_Object::Orth_Pos, Dynamic_Object::Orth_Pos_Attack, Dynamic_Object::Path, Dynamic_Object::Search_A_Star);
		}
		else
		{
			A_Star_Search(this, Map_1, Map_2, Dynamic_Object::Orth_Pos, Dynamic_Object::Orth_Pos_Move, Dynamic_Object::Path, Dynamic_Object::Search_A_Star);
		}
	}
	Move_Cell_x_to_Cell_y(Unit_Dt, Country, Map_1, Map_2, Map_UG_Check_Click, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos);
}
void Building_Object::Research_Tech(Tech_Details Tech_Dt[], Civil* Civil_Gaia_List, vector<Civil*>& Civil_Computer_List, vector<Civil*>& Civil_Player_List)
{
	if (Researching_Tech)
	{
		//cout << "yes";
		Current_Time_Research = SDL_GetTicks();
		if (Current_Time_Research - Last_Time_Research >= (Tech_Dt[Researching_Tech_Type].Time_Research))
		{
			//cout << "yes";
			if (Percent_Tech_Researching < 100)
			{
				Percent_Tech_Researching += 1;
			}
			else
			{
				//cout << "yes";
				if (Unit_Type_Control == Player)
				{
					//cout << "yes";
					Civil_Player_List[Pos_Control]->Effect(Researching_Tech_Type);
					Percent_Tech_Researching = 0;
					Researching_Tech = false;
					Researching_Tech_Type = -1;
				}
			}
			Last_Time_Research = Current_Time_Research;
		}
	}
}

void Building_Object::Cancel_Researching_Tech()
{
	if (Researching_Tech)
	{
		Percent_Tech_Researching = 0;
		Researching_Tech = false;
		Researching_Tech_Type = -1;
	}
}

void Building_Object::Train_Unit(int Unit_Type, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*>& Civil_Computer_List, vector<Civil*>& Civil_Player_List)
{
	Current_Time_Train = SDL_GetTicks();
	//cout << "yes";
	if (!Unit_Train_Queue.empty() && Training_Unit_Type == -1)
	{
		//cout << "yes";
		Training_Unit_Type = Unit_Train_Queue.front();
		Unit_Train_Queue.pop();
		Training_Unit = true;
	}
	if (Training_Unit_Type != -1)
	{
		//cout << "yes";
		if (Unit_Type_Control == Player)
		{
			//cout << "yes";
			if (Current_Time_Train - Last_Time_Train > Civil_Player_List[Pos_Control]->Unit_Dt[Training_Unit_Type].Time_Train / 100)
			{
				if (Percent_Training_Unit < 100)
				{
					if (Civil_Player_List[Pos_Control]->Get_Population() < Civil_Player_List[Pos_Control]->Get_Population_Max())
					{
						Percent_Training_Unit += 1;
					}
					//cout << "OKKKKKKKKKK" << endl;
					
				}
				else
				{
					//cout << "Train";
					SDL_Rect Assign_Pos_Sor;
					SDL_Rect Assign_Orth_Pos;
					if (!Civil_Player_List[Pos_Control]->Find_Locate_to_Train(Civil_Player_List[Pos_Control]->Civil_Game_Object_List[Pos_in_List_Object]->Get_Orth_Pos(), Assign_Orth_Pos, Map_1, Map_2, Map_UG_Check_Click))
					{
						cout << " Khong the Train loai quan nay duoc, sorry !" << endl;
						return;
					}
					
					SDL_Rect Assign_Iso_Pos = {};
					//cout << Tech_Dt[Tech_Type].Icon_Iso_Pos.x << " " << Tech_Dt[Tech_Type].Icon_Iso_Pos.x + Tech_Dt[Tech_Type].Icon_Iso_Pos.w <<" "<<x_Pos_Click <<endl;
					//cout << "yes";
					Assign_Pos_Sor.x = Assign_Pos_Sor.y = 0;
					Assign_Pos_Sor.w = Assign_Orth_Pos.w = Civil_Player_List[Pos_Control]->Unit_Dt[Training_Unit_Type].Weight;
					Assign_Pos_Sor.h = Assign_Orth_Pos.h = Civil_Player_List[Pos_Control]->Unit_Dt[Training_Unit_Type].Height;
					Game_Object* Object;
					switch (Training_Unit_Type)
					{
					case Villager:
						//cout << "Dung";
						Object = new Villager_Object(0.3, 21, 38);
						//cout << Unit_Type << endl;
						Object->Set(Assign_Orth_Pos, Assign_Iso_Pos, Assign_Pos_Sor, Villager, 0, Country, Country_Name, 40, 40);
						Object->Set_Object_Properties(Civil_Player_List[Pos_Control]->Unit_Dt);
						Object->Unit_Type_Control = Unit_Type_Control;
						Object->Pos_Control = Pos_Control;
						Object->Pos_in_List_Object = Civil_Player_List[Pos_Control]->Get_Pos_New_Object();
						Civil_Player_List[Pos_Control]->Number_Villager++;
						
						//cout << Object->Get_Unit_Type();
						//Object->Set();
						break;
					case Clubman:
					{
						cout << Assign_Orth_Pos.w << Assign_Orth_Pos.h << endl;
						//cout << "yes";
						Object = new Dynamic_Object(0.3);
						//Object = new Dynamic_Object(0.3);
						//cout << Unit_Type << endl;
						Object->Set(Assign_Orth_Pos, Assign_Iso_Pos, Assign_Pos_Sor, Clubman, 0, Country, Country_Name, 40, 40);
						Object->Set_Object_Properties(Civil_Player_List[Pos_Control]->Unit_Dt);
						Object->Unit_Type_Control = Unit_Type_Control;
						Object->Pos_Control = Pos_Control;
						Object->Pos_in_List_Object = Civil_Player_List[Pos_Control]->Get_Pos_New_Object();
						Civil_Player_List[Pos_Control]->Number_Clubman++;
						break;
					}
					default:
						Object = new Game_Object();
						break;
					}
					Civil_Player_List[Pos_Control]->Push_Object_to_Cell(Map_2, Map_UG_Check_Click, Object);
					Civil_Player_List[Pos_Control]->Civil_Game_Object_List.push_back(Object);
					Civil_Player_List[Pos_Control]->Civil_Train_Add_Unit(Training_Unit_Type);
					Percent_Training_Unit = 0;
					Training_Unit = false;
					Training_Unit_Type = -1;
					//cout << Civil_Game_Object_List.size();
				}
				Last_Time_Train = Current_Time_Train;
			}
		}
		else if (Unit_Type_Control == Computer)
		{
			//cout << "yes";
			if (Current_Time_Train - Last_Time_Train > Civil_Computer_List[Pos_Control]->Unit_Dt[Training_Unit_Type].Time_Train / 100)
			{
				//cout << "OKKKKKKKKKK" << endl;
				if (Civil_Computer_List[Pos_Control]->Get_Population() < Civil_Computer_List[Pos_Control]->Get_Population_Max())
				{
					Percent_Training_Unit += 1;
				}
				else
				{
					//cout << "Train";
					SDL_Rect Assign_Pos_Sor;
					SDL_Rect Assign_Orth_Pos;
					if (!Civil_Computer_List[Pos_Control]->Find_Locate_to_Train(Civil_Computer_List[Pos_Control]->Civil_Game_Object_List[Pos_in_List_Object]->Get_Orth_Pos(), Assign_Orth_Pos, Map_1, Map_2, Map_UG_Check_Click))
					{
						cout << " Khong the Train loai quan nay duoc, sorry !" << endl;
						return;
					}
					
					SDL_Rect Assign_Iso_Pos = {};
					//cout << Tech_Dt[Tech_Type].Icon_Iso_Pos.x << " " << Tech_Dt[Tech_Type].Icon_Iso_Pos.x + Tech_Dt[Tech_Type].Icon_Iso_Pos.w <<" "<<x_Pos_Click <<endl;
					//cout << "yes";
					Assign_Pos_Sor.x = Assign_Pos_Sor.y = 0;
					Assign_Pos_Sor.w = Assign_Iso_Pos.w = Assign_Orth_Pos.w = Civil_Computer_List[Pos_Control]->Unit_Dt[Training_Unit_Type].Weight;
					Assign_Pos_Sor.h = Assign_Iso_Pos.w = Assign_Orth_Pos.h = Civil_Computer_List[Pos_Control]->Unit_Dt[Training_Unit_Type].Height;
					Game_Object* Object;
					switch (Training_Unit_Type)
					{
					case Villager:
						//cout << "Dung";
						Object = new Villager_Object(0.3, 21, 38);
						//cout << Unit_Type << endl;
						Object->Set(Assign_Orth_Pos, Assign_Iso_Pos, Assign_Pos_Sor, Villager, 0, Country, Country_Name, 40, 40);
						Object->Set_Object_Properties(Civil_Computer_List[Pos_Control]->Unit_Dt);
						Object->Unit_Type_Control = Unit_Type_Control;
						Object->Pos_Control = Pos_Control;
						Object->Pos_in_List_Object = Civil_Computer_List[Pos_Control]->Get_Pos_New_Object();
						Civil_Computer_List[Pos_Control]->Number_Villager++;
						//Civil_Computer_List[Pos_Control]->Civil_Train_Add_Unit();

						//cout << Object->Get_Unit_Type();
						//Object->Set();
						break;
					case Clubman:
					{
						cout << Assign_Orth_Pos.w << Assign_Orth_Pos.h << endl;
						//cout << "yes";
						Object = new Dynamic_Object(0.3);
						//Object = new Dynamic_Object(0.3);
						//cout << Unit_Type << endl;
						Object->Set(Assign_Orth_Pos, Assign_Iso_Pos, Assign_Pos_Sor, Clubman, 0, Country, Country_Name, 40, 40);
						Object->Set_Object_Properties(Civil_Computer_List[Pos_Control]->Unit_Dt);
						Object->Unit_Type_Control = Unit_Type_Control;
						Object->Pos_Control = Pos_Control;
						Object->Pos_in_List_Object = Civil_Computer_List[Pos_Control]->Get_Pos_New_Object();
						Civil_Computer_List[Pos_Control]->Number_Clubman++;
						//Civil_Computer_List[Pos_Control]->Civil_Train_Add_Unit();

						//cout << Object->Get_Unit_Type();
						//Object->Set();
						break;
					}
					default:
						Object = new Game_Object();
						break;
					}
					Civil_Computer_List[Pos_Control]->Push_Object_to_Cell(Map_2, Map_UG_Check_Click, Object);
					Civil_Computer_List[Pos_Control]->Civil_Game_Object_List.push_back(Object);
					Civil_Computer_List[Pos_Control]->Civil_Train_Add_Unit(Training_Unit_Type);
					//Civil_Computer_List[Pos_Control]->Number_Villager += 1;
					Percent_Training_Unit = 0;
					Training_Unit = false;
					Training_Unit_Type = -1;
					//cout << Civil_Game_Object_List.size();
				}
				Last_Time_Train = Current_Time_Train;
			}
		}
		
	}
}

void Building_Object::Add_to_Train_Unit_Queue(int Unit_Type)
{
	Unit_Train_Queue.push(Unit_Type);
	Training_Unit = true;
}

void Building_Object::Cancel_Training_Unit()
{
	while (!Unit_Train_Queue.empty())
	{
		Unit_Train_Queue.pop();
	}
	Training_Unit = false;
	Training_Unit_Type = -1;
	Percent_Training_Unit = 0;
}

int Building_Object::Get_Number_Unit_Train()
{
	return Unit_Train_Queue.size();
}

void Villager_Object::Set_Object_Properties(Unit_Details Unit_Dt[])
{
	//cout << "ex" << endl;
	Hit_Point = Max_Hit_Point = Unit_Dt[Unit_Type].Hit_Point;
	Attack_Damage = Unit_Dt[Unit_Type].Damage;
}

void Villager_Object::Change_Unit_Type(int Unit_Type_Value)
{
	Unit_Type = Unit_Type_Value;
}

void Villager_Object::Work(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*> Civil_Computer_List, vector<Civil*>Civil_Player_List, int Pos)
{
	//cout << "Pos Work : " << Orth_Pos_Work.x << " " << Orth_Pos_Work.y << endl;
	//cout << " Kiem tra "<<Going_to_return_resource << endl;
	//cout << "okkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";
	for (int i = 0; i < Civil_Player_List.size(); i++)
	{
		//cout << "okkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk";
		if (Civil_Player_List[i]->Get_Civil_Index() == Country)
		{
			//cout << "yessss";
			int Distance_Min = INT_MAX;
			for (int j = 0; j < Civil_Player_List[i]->Pos_Town_Center_List.size(); j++)
			{
				//cout << "yesss";
				int Size_Number_Cell_Capacity;
				Size_Number_Cell_Capacity = Civil_Player_List[i]->Civil_Game_Object_List[Civil_Player_List[i]->Pos_Town_Center_List[j]]->Size_Number_Cell;
				SDL_Rect Orth_Pos_Capacity_New = Civil_Player_List[i]->Civil_Game_Object_List[Civil_Player_List[i]->Pos_Town_Center_List[j]]->Get_Orth_Pos();
				int Distance = sqrt(pow((Orth_Pos.x - Orth_Pos_Capacity_New.x), 2) + pow((Orth_Pos.y - Orth_Pos_Capacity_New.y), 2));
				//cout << Distance_Min;
				//cout << (Distance < Distance_Min);
				if (Distance < Distance_Min)
				{
					//cout << "yessss";
					Distance_Min = Distance;
					Unit_Type_Capacity = Town_Center;
					Pos_Capacity = Civil_Player_List[i]->Pos_Town_Center_List[j];
					Orth_Pos_Capacity = Orth_Pos_Capacity_New;
					//cout << Pos_Capacity;
				}
				// Cần duyệt và xem xét xem đối tượng gần chỗ nào của nhà chính hơn, có thể góc thứ nhất, thứ hai,... hoặc chi tiết hơn là giữa góc thứ nhất và thứ 2, tránh cho đối tượng đi sát vào mà không trả đồ, lại đi vòng
				Distance = sqrt(pow((Orth_Pos.x - (Orth_Pos_Capacity_New.x + Size_Number_Cell_Capacity * Orth_Tile_Height)), 2) + pow((Orth_Pos.y - (Orth_Pos_Capacity_New.y)), 2));
				if (Distance < Distance_Min)
				{
					//cout << "yessss";
					Orth_Pos_Capacity.x += Size_Number_Cell_Capacity * Orth_Tile_Height;
					//Orth_Pos_Capacity.y += 100;
					Distance_Min = Distance;
				}
			}
			//Orth_Pos_Capacity = Civil_Player_List[i]->Civil_Game_Object_List[Pos_Capacity]->Get_Orth_Pos();
			//Orth_Pos_Capacity.x += 32;
			//Orth_Pos_Capacity.y += 32;
			//cout << Orth_Pos_Capacity.x << endl;
			//cout << "yes";
			break;
		}
	}
	if ((Object_Status == Working || Moving_To_Work) && !Going_to_return_resource)
	{
		//cout << "yes";
		//cout << fabs(Orth_Pos.x / Orth_Tile_Height - Orth_Pos_Attack.x / Orth_Tile_Height) << " " << fabs(Orth_Pos.y / Orth_Tile_Height - Orth_Pos_Attack.y / Orth_Tile_Height) << endl;
		//cout << ((fabs(Orth_Pos.x / Orth_Tile_Height - Orth_Pos_Attack.x / Orth_Tile_Height) <= Attack_Range) && (fabs(Orth_Pos.y / Orth_Tile_Height - Orth_Pos_Attack.y / Orth_Tile_Height) <= Attack_Range)) << endl;
		//cout << Attack_Range << endl;
		if (fabs(Orth_Pos.x / Orth_Tile_Height - Orth_Pos_Work.x / Orth_Tile_Height) <= Work_Range && fabs(Orth_Pos.y / Orth_Tile_Height - Orth_Pos_Work.y / Orth_Tile_Height) <= Work_Range)
		{
			//cout << "Checked" << endl;
			Change_Object_Status(Working);
			//Object_Status = Working;
			Moving_To_Work = false;
			if (Unit_Type == Builder)
			{
				if (Get_Country() == Country_Object_Work)
				{
					if (Unit_Type_Control == Player)
					{
						if (Civil_Player_List[Pos_Control]->Civil_Game_Object_List[Pos_Object_Work]->Percent_Complete_Build == 100)
						{
							int Max_Hit_Point_Value = Civil_Player_List[Pos_Control]->Unit_Dt[Get_Unit_Type_Build()].Hit_Point;
							Civil_Player_List[Pos_Control]->Civil_Game_Object_List[Pos_Object_Work]->Change_Hit_Point(Max_Hit_Point_Value);
							Change_Object_Status(Standing);
							return;
							//Civil_Player_List[Pos_Control]->Civil_Game_Object_List[Pos_Object_Work]->Percent_Complete_Build++;
							//Civil_Player_List[Pos_Control]->Civil_Game_Object_List[Pos_Object_Work]->Add_Hit_Point(3);
						}
						
					}
				}
			}
			else
			{
				if (Resource_Bearing >= 10)
				{
					Going_to_return_resource = true;
					Search_Going_to_return_resource = true; // Nếu chưa bật tìm kiếm đường trả tài nguyên thì bật tìm đường lên
				}
				else if (Resource_Bearing > 0 && (Civil_Gaia_List->Civil_Game_Object_List[Pos_Object_Work]->Object_Status == Dead || Civil_Gaia_List->Civil_Game_Object_List[Pos_Object_Work]->Object_Status == Disappear))
				{
					//cout << "yes";
					Going_to_return_resource = true;
					Search_Going_to_return_resource = true;
				}
				else if (Resource_Bearing == 0 && (Civil_Gaia_List->Civil_Game_Object_List[Pos_Object_Work]->Object_Status == Dead || Civil_Gaia_List->Civil_Game_Object_List[Pos_Object_Work]->Object_Status == Disappear))
				{
					//cout << "Yes";
					Change_Object_Status(Standing);
					//Object_Status = Standing;
				}
			}
			
		}
		else
		{
			//cout << "yes" << endl;
			Moving_To_Work = true;
			//cout << "Yes" << endl;
			SDL_Rect Orth_Pos_Work_New = {};
			if (Unit_Type_Object_Work == Tree_01 || Unit_Type_Object_Work == Mine_Gold || Unit_Type_Object_Work == Mine_Stone) // Trường hợp đối tượng khai thác trong tự nhiên
			{
				Orth_Pos_Work_New = Civil_Gaia_List->Civil_Game_Object_List[Pos_Object_Work]->Get_Orth_Pos();
				//cout << "yes";
			}
			else // Trường hợp đối tượng làm việc là nhà cửa : Xây nhà , ...
			{
				Orth_Pos_Work_New = Civil_Player_List[Pos_Control]->Civil_Game_Object_List[Pos_Object_Work]->Get_Orth_Pos();
			}
			if (Search_Moving_to_Work)
			{
				//cout << "uuu";
				Search_A_Star = true;
				A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Work, Path, Search_A_Star);
				Search_Moving_to_Work = false;
			}
			else if (Orth_Pos_Work_New.x != Orth_Pos_Work.x || Orth_Pos_Work_New.y != Orth_Pos_Work.y)
			{
				cout << "Reset" << endl;
				Orth_Pos_Work = Orth_Pos_Work_New;
				Search_Moving_to_Work = true;
			}
			if (Resource_Bearing == 0)
			{
				Change_Object_Status(Moving);
			}
			else
			{
				Change_Object_Status(Carry);
			}
			//Object_Status = Moving;
		}
	}
	else if (Going_to_return_resource)
	{
		//cout << "yes";
		//cout << Orth_Pos_Capacity.y << endl;
		//cout << fabs(Orth_Pos.x / Orth_Tile_Height - Orth_Pos_Capacity.x / Orth_Tile_Height) << " " << fabs(Orth_Pos.y / Orth_Tile_Height - Orth_Pos_Capacity.y / Orth_Tile_Height);
		/*if ((fabs(Orth_Pos.x - Orth_Pos_Capacity.x) / Orth_Tile_Height <= 1 && fabs(Orth_Pos.y - Orth_Pos_Capacity.y) / Orth_Tile_Height <= 1) ||  // Trường hợp này tức đối tượng đã trả xong tài nguyên, và quay trở lại làm việc
			(fabs(Orth_Pos.x + Orth_Tile_Height - Orth_Pos_Capacity.x) / Orth_Tile_Height <= 1 && fabs(Orth_Pos.y - Orth_Pos_Capacity.y) / Orth_Tile_Height <= 1) ||
			(fabs(Orth_Pos.x - Orth_Pos_Capacity.x) / Orth_Tile_Height <= 1 && fabs(Orth_Pos.y + Orth_Tile_Height - Orth_Pos_Capacity.y) / Orth_Tile_Height <= 1) ||
			(fabs(Orth_Pos.x + Orth_Tile_Height - Orth_Pos_Capacity.x) / Orth_Tile_Height <= 1 && fabs(Orth_Pos.y + Orth_Tile_Height - Orth_Pos_Capacity.y) / Orth_Tile_Height <= 1))
		{*/
		cout << Orth_Pos_Capacity.x << endl;
		if (Check_Collision(Map_1, Map_2, Map_UG_Check_Click, this, Civil_Gaia_List, Civil_Computer_List, Civil_Player_List, Pos_in_List_Object) == 3)
		{
			//cout << "Checked" << endl;
			if (Unit_Type_Control == Player)
			{
				if (Unit_Type == Stone_Miner)
				{
					Civil_Player_List[Pos_Control]->Amount_Stone += Resource_Bearing;
				}
				else if (Unit_Type == Gold_Miner)
				{
					Civil_Player_List[Pos_Control]->Amount_Gold += Resource_Bearing;
				}
				else if (Unit_Type == Woodcutter)
				{
					Civil_Player_List[Pos_Control]->Amount_Wood += Resource_Bearing;
				}
				else if (Unit_Type == Forager)
				{
					Civil_Player_List[Pos_Control]->Amount_Food += Resource_Bearing;
				}
			}
			if (Unit_Type_Control == Computer)
			{
				if (Unit_Type == Stone_Miner)
				{
					Civil_Computer_List[Pos_Control]->Amount_Stone += Resource_Bearing;
				}
				else if (Unit_Type == Gold_Miner)
				{
					Civil_Computer_List[Pos_Control]->Amount_Gold += Resource_Bearing;
				}
				else if (Unit_Type == Woodcutter)
				{
					Civil_Computer_List[Pos_Control]->Amount_Wood += Resource_Bearing;
				}
				else if (Unit_Type == Forager)
				{
					Civil_Computer_List[Pos_Control]->Amount_Food += Resource_Bearing;
				}
			}
			Change_Object_Status(Moving);
			//Object_Status = Working;
			Going_to_return_resource = false;
			Resource_Bearing = 0;
			Moving_To_Work = true;
			Search_Moving_to_Work = true;
		}
		else // Nếu đối tượng vẫn đang đi trả tài nguyên, tiếp tục đi tới nơi chứa để trả
		{
			Going_to_return_resource = true;
			Search_Going_to_return_resource = true;
			//cout << "Yes" << endl;
			if (Search_Going_to_return_resource)
			{
				//cout << "uuu";
				Search_A_Star = true;
				//cout << Orth_Pos_Capacity.y;
				A_Star_Search(this, Map_1, Map_2, Orth_Pos, Orth_Pos_Capacity, Path, Search_A_Star);
				Search_Going_to_return_resource = false;
			}
			/*else if (Orth_Pos_Work_New.x != Orth_Pos_Work.x || Orth_Pos_Work_New.y != Orth_Pos_Work.y) // Nếu vị trí nhà chứa đồ thay đổi thì tìm kiếm lại
			{
				cout << "Reset" << endl;
				Orth_Pos_Work = Orth_Pos_Work_New;
				Search_Moving_to_Work = true;
			}*/
			if (Resource_Bearing == 0)
			{
				Change_Object_Status(Moving);
			}
			else
			{
				Change_Object_Status(Carry);
			}
			//Object_Status = Moving;
		}
	}
}

void Villager_Object::Enable_Find_to_Build_House(int Unit_Type_Build_Value)
{
	Find_to_Build_House = true;
	Unit_Type_Build = Unit_Type_Build_Value;
}

void Villager_Object::Disable_Find_to_Build_House()
{
	Find_to_Build_House = false;
	//Unit_Type_Build = -1;
}

bool Villager_Object::Get_Find_to_Build_House()
{
	return Find_to_Build_House;
}

void Villager_Object::Change_Unit_Type_Build(int Unit_Type_Build_Value)
{
	Unit_Type_Build = Unit_Type_Build_Value;
}

int Villager_Object::Get_Unit_Type_Build()
{
	return Unit_Type_Build;
}

void Villager_Object::Build(int Unit_Type_Build, SDL_Rect Orth_Pos_Build, Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*> Civil_Computer_List, vector<Civil*> Civil_Player_List, int Pos)
{
	if (Unit_Type_Control == Player)
	{
		SDL_Rect Assign_Pos_Sor;
		SDL_Rect Assign_Orth_Pos;
		SDL_Rect Assign_Iso_Pos = {};
		int Unit_Type_Object_Work_Value = Civil_Player_List[Pos_Control]->Civil_Game_Object_List[Pos_in_List_Object]->Get_Unit_Type_Build();
		int Pos_Object_Work_Value = Civil_Player_List[Pos_Control]->Get_Pos_New_Object();
		int Country_Object_Work_Value = Civil_Player_List[Pos_Control]->Civil_Game_Object_List[Pos_in_List_Object]->Get_Country();
		int Unit_Type_Control = Player; // Vì người chơi yêu cầu xây nhà, lên Loại điều khiển Civil là Player
		int Pos_Control_Value = Civil_Player_List[Pos_Control]->Civil_Game_Object_List[Pos_in_List_Object]->Pos_Control;
		//cout << Tech_Dt[Tech_Type].Icon_Iso_Pos.x << " " << Tech_Dt[Tech_Type].Icon_Iso_Pos.x + Tech_Dt[Tech_Type].Icon_Iso_Pos.w <<" "<<x_Pos_Click <<endl;
		//cout << "yes";
		Assign_Orth_Pos = Orth_Pos_Build;
		Assign_Pos_Sor.x = Assign_Pos_Sor.y = 0;
		Assign_Pos_Sor.w = Assign_Orth_Pos.w = Civil_Player_List[Pos_Control]->Unit_Dt[Unit_Type_Object_Work_Value].Weight;
		Assign_Pos_Sor.h = Assign_Orth_Pos.h = Civil_Player_List[Pos_Control]->Unit_Dt[Unit_Type_Object_Work_Value].Height;
		Game_Object* Object;

		Object = new Building_Object(Civil_Player_List[Pos_Control]->Unit_Dt[Unit_Type_Object_Work_Value].Size_Number_Cell);
		//cout << Unit_Type << endl;
		if (Unit_Type_Build == House)
		{
			Object->Set(Assign_Orth_Pos, Assign_Iso_Pos, Assign_Pos_Sor, Unit_Type_Build, 0, Country, Country_Name, 80, 80);

		}
		else
		{
			Object->Set(Assign_Orth_Pos, Assign_Iso_Pos, Assign_Pos_Sor, Unit_Type_Build, 0, Country, Country_Name, 170, 170);
		}
		//cout << "iso " << Assign_Iso_Pos.x << Assign_Iso_Pos.y << endl;
		Object->Set_Object_Properties(Civil_Player_List[Pos_Control]->Unit_Dt);
		Object->Unit_Type_Control = Unit_Type_Control;
		Object->Pos_Control = Pos_Control;
		Object->Pos_in_List_Object = Civil_Player_List[Pos_Control]->Civil_Game_Object_List.size();
		Object->Change_Hit_Point(0);
		Object->Set_Unit_Type_Property(Building);
		//Civil_Player_List[Pos_Control]->Number_Villager++;
		Civil_Player_List[Pos_Control]->Civil_Game_Object_List.push_back(Object);
		Civil_Player_List[Pos_Control]->Push_Object_to_Cell(Map_2, Map_UG_Check_Click, Object); // Kết luận sau 5-6 tiếng tìm bug, giá trị orth Pos chưa được khởi tạo và dẫn tới sai !
		Civil_Player_List[Pos_Control]->Civil_Game_Object_List[Pos_in_List_Object]->Search_Moving_to_Work = true;
		Set_Orth_Pos_Work(Orth_Pos_Build, Unit_Type_Object_Work_Value, Pos_Object_Work_Value, Country_Object_Work_Value, Unit_Type_Control, Pos_Control_Value);
		Civil_Player_List[Pos_Control]->Civil_Train_Add_Unit(Unit_Type_Build);
	}
	// hàm này giúp nông dân xây dựng
	
}
