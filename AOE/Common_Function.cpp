#include "Common_Function.h"
#include "Game_Object.h"
#include "Init.h"
typedef struct Point // Định nghĩa Struct của một điểm trong không gian
{
	int x;
	int y;
	int z;
} Point;
void Move_x_to_y()
{

}

bool Check_Cell(int Row, int Col) // Hàm kiểm tra xem ô này có trong phạm vi trò chơi không !
{
	//cout << Row << " " << Col << endl;
	bool Test = ((Row >= 0 && Row < Number_Row_Map) && (Col >= 0 && Col < Number_Col_Map));
	//cout << Test << endl;
	return ((Row >= 0 && Row < Number_Row_Map) && (Col >= 0 && Col < Number_Col_Map));
}
void Clear_Stack(stack<Pair>& S_Stack)
{
	while (!S_Stack.empty())
	{
		S_Stack.pop();
	}
}
bool Check_UnBlock(Game_Object*Game_Object_Check ,Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], int Row, int Col, int Parent_Row, int Parent_Col) // Kiểm tra xem ô này có vật cản hay không
{
	//return false;
	/*if (Check_Cell_Empty(Row, Col, Map_2))
	{
		return true;
	}
	else
	{
		return false;
	}*/
	if (Row == Parent_Row || Col == Parent_Col)
	{
		if (Check_Cell_Empty(Game_Object_Check,Row, Col, Map_2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{  
		int Col_Assign = Col - Parent_Col;
		int Row_Assign = Row - Parent_Row;
		if (Check_Cell_Empty(Game_Object_Check, Row, Col, Map_2))
		{
			if (Check_Cell_Empty(Game_Object_Check, Parent_Row + Row_Assign, Parent_Col, Map_2) && Check_Cell_Empty(Game_Object_Check, Parent_Row, Parent_Col + Col_Assign, Map_2))
			{
				//cout << "DUNG";
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}
bool Check_Des(int Row, int Col, Pair& Dest) // Kiểm tra xem ô này có phải đích đến hay không
{
	bool Test = (Row == Dest.first && Col == Dest.second);
	//cout << Test;
	//cout << Dest.first << " " << Dest.second << endl;
	//cout << Row << " " << Col << endl;
	return (Row == Dest.first && Col == Dest.second);
}
double Cal_H_Value(int Row, int Col, Pair& Dest)
{
	int dx = fabs(Dest.second - Col);
	int dy = fabs(Dest.first - Row);
	return (1 * (dx + dy) + (1.4142 - 2 * 1) * min(fabs(Dest.first - Row), fabs(Dest.second - Col)));
}
double Cal_Distance(SDL_Rect X1, SDL_Rect X2)
{
	return sqrt((pow(X1.x - X2.x, 2) + pow(X1.y - X2.y, 2)));
}
void Traced(Pair& Dest, stack<Pair>& Path, Cell Cell_Details[Number_Row_Map][Number_Col_Map]) // Truy dấu đường đi, từ điểm cuối sẽ push vào Stack các ô để dẫn tới điêm xuất phát
{
	//cout << Path.size();
	int row_path = Dest.first; // Lấy ra hàng của ô đích
	int col_path = Dest.second; // Lấy ra cột của ô đích
	while (!((Cell_Details[row_path][col_path].Parent_i == row_path) && (Cell_Details[row_path][col_path].Parent_j == col_path)))
	{
		//cout<<Path.size()<<endl;
		//cout << row_path << " " << col_path << endl;
		Path.push(make_pair(row_path, col_path));
		int row_path_a = Cell_Details[row_path][col_path].Parent_i;
		int col_path_a = Cell_Details[row_path][col_path].Parent_j;
		row_path = row_path_a;
		col_path = col_path_a;
	}
	//Path.push(make_pair(row_path, col_path));
	
	//cout << Path.size();
	return;
}
void Convert(SDL_Rect& Iso_Des, SDL_Rect& Orth_Des,int z)
{
	Iso_Des.x = Distance_X_to_O + (Orth_Des.x - Orth_Des.y); // convert from Position of orthogonal to Position of isometric.
	Iso_Des.y = 100+(Orth_Des.x + Orth_Des.y) / 2 - z;
	Iso_Des.w = Orth_Des.w;
	Iso_Des.h = Orth_Des.h;
}
void Convert_Object(Game_Object* Game_Object_Convert, SDL_Rect& Iso_Des, SDL_Rect& Orth_Des, int Weight, int Height)
{
	//Iso_Des.x = Distance_X_to_O + (Orth_Des.x - Orth_Des.y) - (Weight / 2 - Orth_Tile_Weight); // convert from Position of orthogonal to Position of isometric.
	int Focus_Point_x = 0;
	int Focus_Point_y = 0;
	Iso_Des.x = Distance_X_to_O + (Orth_Des.x - Orth_Des.y); //- Weight / 2;
	Iso_Des.y = 100 + (Orth_Des.x + Orth_Des.y) / 2; //- (Height - Weight * tan(3.14 / 6)); // (Height - Weight * tan(3.14/6)) : Đây chính là chiều cao gần đúng của đối tượng suy ra từ ảnh dạng Isometric
	if (Game_Object_Convert->Object_Status == Standing)
	{
		Focus_Point_x = Country_Unit_Details_Texture_List[Game_Object_Convert->Get_Country()].Unit_Dt_Texture[Game_Object_Convert->Get_Unit_Type()].Focus_Point_Standing.x;
		Focus_Point_y = Country_Unit_Details_Texture_List[Game_Object_Convert->Get_Country()].Unit_Dt_Texture[Game_Object_Convert->Get_Unit_Type()].Focus_Point_Standing.y;
	}
	else if (Game_Object_Convert->Object_Status == Moving)
	{
		//cout << "yes";
		Focus_Point_x = Country_Unit_Details_Texture_List[Game_Object_Convert->Get_Country()].Unit_Dt_Texture[Game_Object_Convert->Get_Unit_Type()].Focus_Point_Moving.x;
		Focus_Point_y = Country_Unit_Details_Texture_List[Game_Object_Convert->Get_Country()].Unit_Dt_Texture[Game_Object_Convert->Get_Unit_Type()].Focus_Point_Moving.y;
	}
	else if (Game_Object_Convert->Object_Status == Attacking)
	{
		Focus_Point_x = Country_Unit_Details_Texture_List[Game_Object_Convert->Get_Country()].Unit_Dt_Texture[Game_Object_Convert->Get_Unit_Type()].Focus_Point_Attacking.x;
		Focus_Point_y = Country_Unit_Details_Texture_List[Game_Object_Convert->Get_Country()].Unit_Dt_Texture[Game_Object_Convert->Get_Unit_Type()].Focus_Point_Attacking.y;
	}
	else if (Game_Object_Convert->Object_Status == Carry)
	{
		Focus_Point_x = Country_Unit_Details_Texture_List[Game_Object_Convert->Get_Country()].Unit_Dt_Texture[Game_Object_Convert->Get_Unit_Type()].Focus_Point_Carry.x;
		Focus_Point_y = Country_Unit_Details_Texture_List[Game_Object_Convert->Get_Country()].Unit_Dt_Texture[Game_Object_Convert->Get_Unit_Type()].Focus_Point_Carry.y;
	}
	else if (Game_Object_Convert->Object_Status == Working)
	{
		Focus_Point_x = Country_Unit_Details_Texture_List[Game_Object_Convert->Get_Country()].Unit_Dt_Texture[Game_Object_Convert->Get_Unit_Type()].Focus_Point_Working.x;
		Focus_Point_y = Country_Unit_Details_Texture_List[Game_Object_Convert->Get_Country()].Unit_Dt_Texture[Game_Object_Convert->Get_Unit_Type()].Focus_Point_Working.y;
	}
	else if (Game_Object_Convert->Object_Status == Death)
	{
		Focus_Point_x = Country_Unit_Details_Texture_List[Game_Object_Convert->Get_Country()].Unit_Dt_Texture[Game_Object_Convert->Get_Unit_Type()].Focus_Point_Death.x;
		Focus_Point_y = Country_Unit_Details_Texture_List[Game_Object_Convert->Get_Country()].Unit_Dt_Texture[Game_Object_Convert->Get_Unit_Type()].Focus_Point_Death.y;
	}
	else if (Game_Object_Convert->Object_Status == Dead)
	{
		Focus_Point_x = Country_Unit_Details_Texture_List[Game_Object_Convert->Get_Country()].Unit_Dt_Texture[Game_Object_Convert->Get_Unit_Type()].Focus_Point_Dead.x;
		Focus_Point_y = Country_Unit_Details_Texture_List[Game_Object_Convert->Get_Country()].Unit_Dt_Texture[Game_Object_Convert->Get_Unit_Type()].Focus_Point_Dead.y;
	}
	Iso_Des.x -= Focus_Point_x;
	Iso_Des.y -= Focus_Point_y;
	if (Game_Object_Convert->Get_Country() == 2)
	{
		//cout << "Doi tuong 2" << Iso_Des.x << " " << Iso_Des.y << " Focus x y : " << Focus_Point_x << " " << Focus_Point_y << endl;
		//cout << Focus_Point_x << endl;
	}
	Iso_Des.w = Orth_Des.w;
	Iso_Des.h = Orth_Des.h;
	Game_Object_Convert->Iso_Pos_Selection.x = Iso_Des.x;
	Game_Object_Convert->Iso_Pos_Selection.y = Iso_Des.y;
	Game_Object_Convert->Iso_Pos_Selection.x += Focus_Point_x;
	Game_Object_Convert->Iso_Pos_Selection.y += Focus_Point_y;
}
void Reverse_Convert(int& Iso_Des_x, int& Iso_Des_y, int Weight, int Height) // Ở đây thì Weight và Height là của đối tượng cần xác định xem chúng có phải đối tượng được chọn không
{
	/* Tôi đã tính toán vị trí này rất nhiều, tôi viết hàm này mục đích nhằm đổi tọa độ chuột sang tọa độ Orthogonal, nhưng có vẻ nó không được đúng cho lắm vì đơn giản
	chính là khi chuyển sang tọa độ thường thì để đúng ô chứa vật thể, tọa độ click chuột phải ở trong vòng 1 ô, tức nó chỉ chênh lệch 32 pixel, như vậy nếu đối tượng to tới đâu, tọa độ click vẫn chỉ được bằng số ô của đối tượng mà thôi.
	nhưng nếu mà đối tượng quá to, nhưng nó vẫn chỉ nằm trong một ô, và lúc này những cú click sẽ không đúng lắm.
	Tôi nảy ra một ý tưởng, đó là tạo tiếp một Map UG để chứa kích thước thật cho đối tượng.
	*/
	double A = Weight / 2 - Orth_Tile_Weight;
	double B = Height - Weight * tan(3.14 / 6);
	double x = (Iso_Des_x + 2 * Iso_Des_y - 200 - Distance_X_to_O + A + 2 * B) / 2;
	double y = 2 * Iso_Des_y - x - 200 + 2 * B;
	Iso_Des_x = x;
	Iso_Des_y = y;
	/*int A = Weight / 2 - Orth_Tile_Weight;
	int B = Height - Weight * tan(3.14 / 6);
	double x = (Iso_Des_x + 2 * Iso_Des_y - 200 - Distance_X_to_O) / 2;
	double y = 2 * Iso_Des_y - x - 200;
	Iso_Des_x = x;
	Iso_Des_y = y;*/
};
void A_Star_Search(Game_Object* Game_Object_need_Search_Path, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], SDL_Rect& Orth_Pos_Des, SDL_Rect& Orth_Pos_Move, stack<Pair>& Path, bool& Search_A)
// Thuật toán tìm đường A*, tìm đường dựa trên quét các ô xung quanh
{
	//cout << "yes";
	double T_L = SDL_GetTicks();
	double T_C;
	int Number_Node_Open = 1; // Số lượng ô đã thêm vào Open List
	int Max_Number_Node_Open = 30; // Số lượng ô tối đa có thể thêm vào Open List, mục đích để giới hạn lại số lượng ô có thể mở, tránh trường hợp mở toàn bộ ô trên bản đồ khi không tìm thấy đường đi gây Drop Fps
	P_Pair Cell_has_f_Min; // Ô có trọng số f là Max, để trường hợp không thấy đường thì sẽ đi thẳng tới ô này
	Cell_has_f_Min.first = FLT_MAX;

	if (Search_A) // Nếu chưa thực hiện A* thì thực hiện
	{
		Clear_Stack(Path);
		Pair Src; // Tọa độ ô bắt đầu (ô đích) , Src.first là Cột, Src.second là hàng
		Pair Des; // Tọa độ ô kết thúc
		Des.second = Orth_Pos_Move.x / Orth_Tile_Weight; // Đưa vào Src và Des thông tin về hàng cột của ô bắt đầu và kết thúc
		Des.first = Orth_Pos_Move.y / Orth_Tile_Height; // Hàng của ô kết thúc
		Src.second = Orth_Pos_Des.x / Orth_Tile_Weight; // Cột của ô bắt đầu
		Src.first = Orth_Pos_Des.y / Orth_Tile_Height; // Hàng
		// Kiểm tra nếu ô ban đầu là ô đích thì return luôn.
		// Qua xử lý và tìm bug, tôi thấy nếu không có hàm kiểm tra ô đích là ô nguồn này thì hàm A* này sẽ không trả về và tiếp tục tìm kiếm, khi đó ô đích cần tìm sẽ chính là ô nguồn và chạy hàm Traced, gây ra lỗi bộ nhớ ram tăng vọt lên và chương trình bị Crash
		// Còn nguyên nhân thì tôi vẫn đang tìm hiểu :) !
		// Oh tôi đã có một suy nghĩ rất nhanh và nó gần như sẽ đúng, khi ô đích là ô nguồn và tôi không trả về luôn để kết thúc hàm, hàm này sẽ cứ kiểm tra và thêm các ô xung quanh vào open list,
		// tất nhiên nó sẽ không bao giờ kiểm tra ô nguồn nữa và kích thước open list cứ tăng vọt lên theo thời gian !
		if (Check_Des(Src.first, Src.second, Des)) 
		{
			Search_A = false;
			cout << " No la o ban dau roi ban";
			return;
		}
		//cout << Src.first << " " << Src.second << endl;
		//cout << "search";
		//cout<<Src.first<<" "<<Src.second<<endl;
		bool Closed_List[Number_Row_Map][Number_Col_Map]; // Danh sách các ô đã mở, nếu Flase là chưa sử dụng, True là đã sử dụng ô đó
		bool Push_Open_List[Number_Row_Map][Number_Col_Map]; // Danh các ô đã thêm vào open list, tức đã thêm vào thì không thêm vào lại nữa
		memset(Closed_List, false, sizeof(Closed_List)); // Đặt tất cả các giá trị của mảng thành false
		memset(Push_Open_List, false, sizeof(Push_Open_List)); // Đặt tất cả thành false, tức chưa ô nào được mở cả
		Cell Cell_Details[Number_Row_Map][Number_Col_Map]; // Danh sách tất cả các ô trong Map được đưa vào mảng
		int r, c;
		for (r = 0; r < Number_Row_Map; r++)
		{
			for (c = 0; c < Number_Col_Map; c++)
			{
				Cell_Details[r][c].f = FLT_MAX; // Tổng chi phí : = g + h
				Cell_Details[r][c].g = FLT_MAX; // Khoảng cách từ Cell ban đầu tới Cell đang xét, ví dụ hai ô thẳng hàng nhau và sát nhau thì g = 1*Orth_Tile_Height
				// Còn nếu hai ô chéo nhau liên tiếp, nó sẽ là 1,41 * Orth_Tile_Height !
				Cell_Details[r][c].h = FLT_MAX; // Approximation Heuristics : Chi phí 
				Cell_Details[r][c].Parent_i = No_Def; // Ô trước (bố mẹ) của các ô phía sau, tức phải đi từ ô bố(mẹ) mới tới được ô này
				Cell_Details[r][c].Parent_j = No_Def; // Tất cả thiết lập thành No_Def vì chưa ô nào có bố mẹ
				// Đoạn mã này thiết lập cho các ô đều có chi phí là như nhau, đều là vô cùng
			}
		}
		r = Src.first; // r là hàng : Được gán bằng hàng của ô bắt đầu
		c = Src.second; // c là cột : Được gán bằng cột của ô bắt đầu
		//cout<<c<<endl;
		Cell_Details[r][c].f = 0.0; // Tất cả đều được đặt bằng 0, vì chúng t phải luôn đi từ ô bắt đầu lên các thông số này của ô bắt đầu là không quan trọng
		Cell_Details[r][c].g = 0.0;
		Cell_Details[r][c].h = 0.0;
		Cell_Details[r][c].Parent_i = r; // Ô này là ô bắt đầu, lên Parent chính là nó
		Cell_Details[r][c].Parent_j = c;
		list<P_Pair> Open_List; // Vector chứa danh sách các ô trong danh sách mở
		//cout << Open_List.size() << endl;
		Open_List.push_back(make_pair(0.0, make_pair(r, c))); // Đưa ô bắt đầu này vào danh sách mở
		// make_pair : đặt giá trị cho pair : giá trị đầu tiên là f, cặp sau là giá trị của hàng và cột
		bool Found_Des = false; // Biến bool để xác định xem đích đến đã được tìm thấy chưa
		//cout << "yes";
		//cout << " O bat dau : " << Src.first << " " << Src.second << endl;
		//cout << " O Ket thuc : " << Des.first << " " << Des.second << endl;
		//cout << " Check 7 4 : " << Check_Cell_Empty(Game_Object_need_Search_Path, 7, 4, Map_2) << endl;
		if (!Map_2[7][4].List_Object_in_Cell.empty())
		{
			//cout << Map_2[7][4].List_Object_in_Cell[0].Country << endl;
		}
		while (!Open_List.empty())
		{
			Number_Node_Open++; // Do mở thêm một ô lên số lượng ô đã mở tăng lên 1 
			if (Number_Node_Open > Max_Number_Node_Open) // Nếu số lượng ô đã mở vượt mức cho phép thì dừng tìm kiếm lại
			{
				Pair New_Des; // Một đích đến mới, nếu trường hợp không tìm thấy đường tới ô đích, hay chính xác số ô mở vượt quá số lượng quy định
				New_Des.first = Cell_has_f_Min.second.first;
				New_Des.second = Cell_has_f_Min.second.second;
				Traced(New_Des, Path, Cell_Details);
				Search_A = false;
				T_C = SDL_GetTicks();
				cout << " Thoi gian A* neu khong tim thay duong de di : " << T_C - T_L << " So O da mo ra : " << Number_Node_Open << endl;
				return;
			}
			//if (Number)
			float Min = FLT_MAX;
			//int Min_Pos = 0;
			list< P_Pair>::iterator It;
			list<P_Pair>::iterator Min_Pos;
			for (It = Open_List.begin(); It != Open_List.end(); It++)
			{
				P_Pair Value = *It;
				if (Value.first < Min)
				{
					Min = Value.first;
					Min_Pos = It;
				}
			}
			//cout << endl;
			//cout << "yes";
			//cout<<(!Closed_List[9][13] && Check_UnBlock(9,13))<<endl;
			//cout<<"l"<<endl;
			P_Pair P = *Min_Pos; // Lấy phần tử đầu tiên ra khỏi List
			Open_List.erase(Min_Pos); // Xóa phần tử vừa lấy ra khỏi List
			r = P.second.first; // Lấy giá trị hàng và cột tương ứng
			c = P.second.second;
			//cout<<P.second.first<<" "<<P.second.second<<endl;
			//cout<<"P"<<endl;
			//cout<<Cell_Details[P.second.first][P.second.second].Parent_i<<" "<<Cell_Details[P.second.first][P.second.second].Parent_j<<endl;
			double g_new, h_new, f_new;
			Closed_List[r][c] = true; // Ô này đã mở lên trong danh sách đóng ô này đã được đóng và không còn đưa vào trong lần sau nữa
			//Direction North-East
			if (Check_Cell(r - 1, c + 1))
			{
				if (Check_Des(r - 1, c + 1, Des)) // if src is Des
				{
					Cell_Details[r - 1][c + 1].Parent_i = r;
					Cell_Details[r - 1][c + 1].Parent_j = c;
					Traced(Des, Path, Cell_Details);
					Found_Des = true;
					Search_A = false;
					T_C = SDL_GetTicks();
					cout << " Thoi gian A* : " << T_C - T_L << endl;
					cout << " So luong o da mo la " << Number_Node_Open << endl;
					return;
				}
				else if (!Closed_List[r - 1][c + 1] && Check_UnBlock(Game_Object_need_Search_Path, Map_1, Map_2, r - 1, c + 1, r, c))
				{
					g_new = Cell_Details[r][c].g + 1.414;
					h_new = Cal_H_Value(r - 1, c + 1, Des);
					f_new = g_new + h_new;
					if (Cell_has_f_Min.first > f_new) // Nếu trường hợp ô có trọng số max có trọng số nhỏ hơn ô mới này
					{
						P_Pair Cell_has_f_Max_Value = make_pair(f_new, make_pair(r - 1, c + 1)); // Ô có trọng số f max bằng ô này
						Cell_has_f_Min = Cell_has_f_Max_Value;
					}
					if ((Cell_Details[r - 1][c + 1].f == FLT_MAX) || (Cell_Details[r - 1][c + 1].f > f_new))
					{
						//cout << r << " " << c << endl;
						//cout << r - 1 << " " << c + 1 << endl;
						if (!Push_Open_List[r - 1][c + 1])
						{
							//Number_Node_Open++;
							Open_List.push_back(make_pair(f_new, make_pair(r - 1, c + 1)));
							Push_Open_List[r - 1][c + 1] = true;
						}
						Cell_Details[r - 1][c + 1].g = g_new;
						Cell_Details[r - 1][c + 1].h = h_new;
						Cell_Details[r - 1][c + 1].f = f_new;
						Cell_Details[r - 1][c + 1].Parent_i = r;
						Cell_Details[r - 1][c + 1].Parent_j = c;
					}
					//Closed_List[r - 1][c + 1] = true;
				}
			}
			//Direction North-West
			if (Check_Cell(r - 1, c - 1))
			{
				if (Check_Des(r - 1, c - 1, Des)) // if src is Des
				{
					Cell_Details[r - 1][c - 1].Parent_i = r;
					Cell_Details[r - 1][c - 1].Parent_j = c;
					Traced(Des, Path, Cell_Details);
					Found_Des = true;
					Search_A = false;
					T_C = SDL_GetTicks();
					cout << " Thoi gian A* : " << T_C - T_L << endl;
					cout << " So luong o da mo la " << Number_Node_Open << endl;
					return;
				}
				else if (!Closed_List[r - 1][c - 1] && Check_UnBlock(Game_Object_need_Search_Path, Map_1, Map_2, r - 1, c - 1, r, c))
				{
					g_new = Cell_Details[r][c].g + 1.414;
					h_new = Cal_H_Value(r - 1, c - 1, Des);
					f_new = g_new + h_new;
					if (Cell_has_f_Min.first > f_new)
					{
						P_Pair Cell_has_f_Max_Value = make_pair(f_new, make_pair(r - 1, c - 1));
						Cell_has_f_Min = Cell_has_f_Max_Value;
					}
					if ((Cell_Details[r - 1][c - 1].f == FLT_MAX) || (Cell_Details[r - 1][c - 1].f > f_new))
					{
						//cout << r << " " << c << endl;
						//cout << r - 1 << " " << c - 1 << endl;
						if (!Push_Open_List[r - 1][c - 1])
						{
							//Number_Node_Open++;
							Open_List.push_back(make_pair(f_new, make_pair(r - 1, c - 1)));
							Push_Open_List[r - 1][c - 1] = true;
						}
						Cell_Details[r - 1][c - 1].g = g_new;
						Cell_Details[r - 1][c - 1].h = h_new;
						Cell_Details[r - 1][c - 1].f = f_new;
						Cell_Details[r - 1][c - 1].Parent_i = r;
						Cell_Details[r - 1][c - 1].Parent_j = c;
					}
					//Closed_List[r - 1][c - 1] = true;
				}
			}
			//Direction East-South
			if (Check_Cell(r + 1, c + 1))
			{
				if (Check_Des(r + 1, c + 1, Des)) // if src is Des
				{
					Cell_Details[r + 1][c + 1].Parent_i = r;
					Cell_Details[r + 1][c + 1].Parent_j = c;
					Traced(Des, Path, Cell_Details);
					Found_Des = true;
					Search_A = false;
					T_C = SDL_GetTicks();
					cout << " Thoi gian A* : " << T_C - T_L << endl;
					cout << " So luong o da mo la " << Number_Node_Open << endl;
					return;
				}
				else if (!Closed_List[r + 1][c + 1] && Check_UnBlock(Game_Object_need_Search_Path, Map_1, Map_2, r + 1, c + 1, r, c))
				{
					
					g_new = Cell_Details[r][c].g + 1.414;
					h_new = Cal_H_Value(r + 1, c + 1, Des);
					f_new = g_new + h_new;
					if (Cell_has_f_Min.first > f_new)
					{
						P_Pair Cell_has_f_Max_Value = make_pair(f_new, make_pair(r + 1, c + 1));
						Cell_has_f_Min = Cell_has_f_Max_Value;
					}
					if ((Cell_Details[r + 1][c + 1].f == FLT_MAX) || (Cell_Details[r + 1][c + 1].f > f_new))
					{
						//cout << r << " " << c << endl;
						//cout << r + 1 << " " << c + 1 << endl;
						if (!Push_Open_List[r + 1][c + 1])
						{
							//Number_Node_Open++;
							Open_List.push_back(make_pair(f_new, make_pair(r + 1, c + 1)));
							Push_Open_List[r + 1][c + 1] = true;
						}
						Cell_Details[r + 1][c + 1].g = g_new;
						Cell_Details[r + 1][c + 1].h = h_new;
						Cell_Details[r + 1][c + 1].f = f_new;
						Cell_Details[r + 1][c + 1].Parent_i = r;
						Cell_Details[r + 1][c + 1].Parent_j = c;
					}
					//Closed_List[r + 1][c + 1] = true;
				}
			}
			//Direction West-South
			if (Check_Cell(r + 1, c - 1))
			{
				if (Check_Des(r + 1, c - 1, Des)) // if src is Des
				{
					Cell_Details[r + 1][c - 1].Parent_i = r;
					Cell_Details[r + 1][c - 1].Parent_j = c;
					Traced(Des, Path, Cell_Details);
					Found_Des = true;
					Search_A = false;
					T_C = SDL_GetTicks();
					cout << " Thoi gian A* : " << T_C - T_L << endl;
					cout << " So luong o da mo la " << Number_Node_Open << endl;
					return;
				}
				else if (!Closed_List[r + 1][c - 1] && Check_UnBlock(Game_Object_need_Search_Path, Map_1, Map_2, r + 1, c - 1, r, c))
				{

					g_new = Cell_Details[r][c].g + 1.414;
					h_new = Cal_H_Value(r + 1, c - 1, Des);
					f_new = g_new + h_new;
					if (Cell_has_f_Min.first > f_new)
					{
						P_Pair Cell_has_f_Max_Value = make_pair(f_new, make_pair(r + 1, c - 1));
						Cell_has_f_Min = Cell_has_f_Max_Value;
					}
					if ((Cell_Details[r + 1][c - 1].f == FLT_MAX) || (Cell_Details[r + 1][c - 1].f > f_new))
					{
						//cout << r << " " << c << endl;
						//cout << r + 1 << " " << c - 1 << endl;
						if (!Push_Open_List[r + 1][c - 1])
						{
							//Number_Node_Open++;
							Open_List.push_back(make_pair(f_new, make_pair(r + 1, c - 1)));
							Push_Open_List[r + 1][c - 1] = true;
						}
						Cell_Details[r + 1][c - 1].g = g_new;
						Cell_Details[r + 1][c - 1].h = h_new;
						Cell_Details[r + 1][c - 1].f = f_new;
						Cell_Details[r + 1][c - 1].Parent_i = r;
						Cell_Details[r + 1][c - 1].Parent_j = c;
					}
					//Closed_List[r + 1][c - 1] = true;
				}
			}
			// Direction : North
			if (Check_Cell(r - 1, c)) // Kiểm tra ô này xem nó có trong phạm vi trò chơi không
			{

				if (Check_Des(r - 1, c, Des)) // Kiểm tra xem ô này có phải là ô đích không
				{
					Cell_Details[r - 1][c].Parent_i = r; // Nếu nó là ô đích thì gán bố mẹ nó là ô vừa mở
					Cell_Details[r - 1][c].Parent_j = c;
					Traced(Des, Path, Cell_Details); // Truy vết đường đi từ ô này tới ô bắt đầu
					Found_Des = true; // Đưa Found Des = true, để biết là đã tìm thấy ô đích
					Search_A = false;
					T_C = SDL_GetTicks();
					cout << " Thoi gian A* : " << T_C - T_L << endl;
					cout << " So luong o da mo la " << Number_Node_Open << endl;
					return; // Kết thúc hàm search A*

				}
				else if (!Closed_List[r - 1][c] && Check_UnBlock(Game_Object_need_Search_Path, Map_1, Map_2, r - 1, c, r, c)) // Trường hợp nếu nó chưa phải ô đích
				{
					//cout<<((Cell_Details[r-1][c].f==FLT_MAX) || (Cell_Details[r-1][c].f>f_new))<<endl;
					g_new = Cell_Details[r][c].g + 1.0; // Tính toán g
					h_new = Cal_H_Value(r - 1, c, Des); // Tính toán h
					f_new = g_new + h_new; // Tính toán f
					if (Cell_has_f_Min.first > f_new)
					{
						P_Pair Cell_has_f_Max_Value = make_pair(f_new, make_pair(r - 1, c));
						Cell_has_f_Min = Cell_has_f_Max_Value;
					}
					if ((Cell_Details[r - 1][c].f == FLT_MAX) || (Cell_Details[r - 1][c].f > f_new))
					{
						//cout << r << " " << c << endl;
						//cout << r - 1 << " " << c  << endl;
						if (!Push_Open_List[r - 1][c])
						{
							//Number_Node_Open++;
							Open_List.push_back(make_pair(f_new, make_pair(r - 1, c)));
							Push_Open_List[r - 1][c] = true;
						}
						Cell_Details[r - 1][c].g = g_new;
						Cell_Details[r - 1][c].h = h_new;
						Cell_Details[r - 1][c].f = f_new;
						Cell_Details[r - 1][c].Parent_i = r;
						Cell_Details[r - 1][c].Parent_j = c;

					}
					//Closed_List[r - 1][c - 1] = true;
				}
			}
			//Direction South
			if (Check_Cell(r + 1, c))
			{
				if (Check_Des(r + 1, c, Des)) // if src is Des
				{
					Cell_Details[r + 1][c].Parent_i = r;
					Cell_Details[r + 1][c].Parent_j = c;
					Traced(Des, Path, Cell_Details);
					Found_Des = true;
					Search_A = false;
					T_C = SDL_GetTicks();
					cout << " Thoi gian A* : " << T_C - T_L << endl;
					cout << " So luong o da mo la " << Number_Node_Open << endl;
					return;
				}

				else if (!Closed_List[r + 1][c] && Check_UnBlock(Game_Object_need_Search_Path, Map_1, Map_2, r + 1, c, r, c))
				{
					g_new = Cell_Details[r][c].g + 1.0;
					h_new = Cal_H_Value(r + 1, c, Des);
					f_new = g_new + h_new;
					if (Cell_has_f_Min.first > f_new)
					{
						P_Pair Cell_has_f_Max_Value = make_pair(f_new, make_pair(r + 1, c));
						Cell_has_f_Min = Cell_has_f_Max_Value;
					}
					if ((Cell_Details[r + 1][c].f == FLT_MAX) || (Cell_Details[r + 1][c].f > f_new))
					{
						//cout << r << " " << c << endl;
						//cout << r + 1 << " " << c  << endl;
						if (!Push_Open_List[r + 1][c])
						{
							//Number_Node_Open++;
							Open_List.push_back(make_pair(f_new, make_pair(r + 1, c)));
							Push_Open_List[r + 1][c] = true;
						}
						Cell_Details[r + 1][c].g = g_new;
						Cell_Details[r + 1][c].h = h_new;
						Cell_Details[r + 1][c].f = f_new;
						Cell_Details[r + 1][c].Parent_i = r;
						Cell_Details[r + 1][c].Parent_j = c;
					}
				}
			}
			// Direction East
			if (Check_Cell(r, c + 1))
			{
				if (Check_Des(r, c + 1, Des)) // if src is Des
				{
					Cell_Details[r][c + 1].Parent_i = r;
					Cell_Details[r][c + 1].Parent_j = c;
					Traced(Des, Path, Cell_Details);
					Found_Des = true;
					Search_A = false;
					T_C = SDL_GetTicks();
					cout << " Thoi gian A* : " << T_C - T_L << endl;
					cout << " So luong o da mo la " << Number_Node_Open << endl;
					return;
				}
				else if (!Closed_List[r][c + 1] && Check_UnBlock(Game_Object_need_Search_Path, Map_1, Map_2, r, c + 1, r, c))
				{
					g_new = Cell_Details[r][c].g + 1.0;
					h_new = Cal_H_Value(r, c + 1, Des);
					f_new = g_new + h_new;
					if (Cell_has_f_Min.first > f_new)
					{
						P_Pair Cell_has_f_Max_Value = make_pair(f_new, make_pair(r, c + 1));
						Cell_has_f_Min = Cell_has_f_Max_Value;
					}
					if ((Cell_Details[r][c + 1].f == FLT_MAX) || (Cell_Details[r][c + 1].f > f_new))
					{
						//cout << r << " " << c << endl;
						//cout << r  << " " << c + 1 << endl;
						if (!Push_Open_List[r][c + 1])
						{
							//Number_Node_Open++;
							Open_List.push_back(make_pair(f_new, make_pair(r, c + 1)));
							Push_Open_List[r][c + 1] = true;
						}
						Cell_Details[r][c + 1].g = g_new;
						Cell_Details[r][c + 1].h = h_new;
						Cell_Details[r][c + 1].f = f_new;
						Cell_Details[r][c + 1].Parent_i = r;
						Cell_Details[r][c + 1].Parent_j = c;
					}
				}
			}
			//Direction West
			if (Check_Cell(r, c - 1))
			{
				if (Check_Des(r, c - 1, Des)) // if src is Des
				{
					Cell_Details[r][c - 1].Parent_i = r;
					Cell_Details[r][c - 1].Parent_j = c;
					Traced(Des, Path, Cell_Details);
					Found_Des = true;
					Search_A = false;
					T_C = SDL_GetTicks();
					cout << " Thoi gian A* : " << T_C - T_L << endl;
					cout << " So luong o da mo la " << Number_Node_Open << endl;
					return;
				}
				else if (!Closed_List[r][c - 1] && Check_UnBlock(Game_Object_need_Search_Path, Map_1, Map_2, r, c - 1, r, c))
				{
					g_new = Cell_Details[r][c].g + 1.0;
					h_new = Cal_H_Value(r, c - 1, Des);
					f_new = g_new + h_new;
					if (Cell_has_f_Min.first > f_new)
					{
						P_Pair Cell_has_f_Max_Value = make_pair(f_new, make_pair(r, c - 1));
						Cell_has_f_Min = Cell_has_f_Max_Value;
					}
					if ((Cell_Details[r][c - 1].f == FLT_MAX) || (Cell_Details[r][c - 1].f > f_new))
					{
						//cout << r << " " << c << endl;
						//cout << r  << " " << c - 1 << endl;
						if (!Push_Open_List[r][c - 1])
						{
							//Number_Node_Open++;
							Open_List.push_back(make_pair(f_new, make_pair(r, c - 1)));
							Push_Open_List[r][c - 1] = true;
						}
						Cell_Details[r][c - 1].g = g_new;
						Cell_Details[r][c - 1].h = h_new;
						Cell_Details[r][c - 1].f = f_new;
						Cell_Details[r][c - 1].Parent_i = r;
						Cell_Details[r][c - 1].Parent_j = c;
					}
				}
			}
			
		}
		//cout << "yes";
	}
	T_C = SDL_GetTicks();
	cout << " Thoi gian A* neu khong tim thay duong de di : " << T_C - T_L << " So O da mo ra : " << Number_Node_Open << endl;
}
void Load_Image_1(int Unit_Type, SDL_Rect& Pos_Sor, SDL_Rect& Orth_Pos, SDL_Rect& Iso_Pos)
{
	if (Unit_Type == Grass)
	{
		if (Grass_Texture != NULL)
		{
			//cout << "yes";
		}
		SDL_RenderCopy(Renderer, Grass_Texture, &Pos_Sor, &Iso_Pos);
	}
	else if (Unit_Type == Tree)
	{
		if (Tree_Texture != NULL) //cout << "yes";
		SDL_RenderCopy(Renderer, Tree_Texture, &Pos_Sor, &Iso_Pos);
	}
	else if (Unit_Type == Town_Center_1_M_1)
	{
		SDL_RenderCopy(Renderer, Town_Center_1_Texture, &Pos_Sor, &Iso_Pos);
	}
	else if (Unit_Type == Siege_Workshop_1_M_1)
	{
		SDL_RenderCopy(Renderer, Siege_Workshop_Texture, &Pos_Sor, &Iso_Pos);
	}
}
/*void Load_Sprite_Sheet(int Unit_Type, SDL_Rect& Orth_Pos, SDL_Rect& Pos_Sor, SDL_Rect& Orth_Pos_Work, int Direction,
	bool Working, bool Moving, int Frame_Weight, int Frame_Height, int Number_Frame_Direc, int Time_Next_Sprite, int Last_Time, int Current_Time)
// Time_Next_Sprite : Thời gian load Sprite tiếp theo trong cùng một hướng (Bắc, Nam, ...)
// Hàm này nhằm load Sprite sheet cho đối tượng để đối tượng có thể nhìn như đang chuyển động
{
	if (Working)
	{
		Orth_Pos.w = Pos_Sor.w = Frame_Weight;
		Orth_Pos.h = Pos_Sor.h = Frame_Height;
		if ((Current_Time - Last_Time) > Time_Next_Sprite)
		{
			if (Orth_Pos.x < Orth_Pos_Work.x && Orth_Pos.y < Orth_Pos_Work.y)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				Direction = Direc_S;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_South_x)
				{
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_South_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Orth_Pos.x == Orth_Pos_Work.x && Orth_Pos.y < Orth_Pos_Work.y)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				Direction = Direc_W_S;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_South_x)
				{
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_South_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Orth_Pos.x > Orth_Pos_Work.x&& Orth_Pos.y < Orth_Pos_Work.y)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				Direction = Direc_W;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_x)
				{
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Orth_Pos.x > Orth_Pos_Work.x&& Orth_Pos.y == Orth_Pos_Work.y)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				Direction = Direc_W_N;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_West_North_x)
				{
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_West_North_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Orth_Pos.x > Orth_Pos_Work.x&& Orth_Pos.y > Orth_Pos_Work.y)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				Direction = Direc_N;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_North_x)
				{
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_North_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Orth_Pos.x == Orth_Pos_Work.x && Orth_Pos.y > Orth_Pos_Work.y)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				Direction = Direc_E_N;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_North_x)
				{
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_North_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Orth_Pos.x<Orth_Pos_Work.x && Orth_Pos.y>Orth_Pos_Work.y)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				Direction = Direc_E;
				if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_East_x)
				{
					Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_East_x;
				}
				else
				{
					Pos_Sor.x += Frame_Weight;
				}
			}
			else if (Orth_Pos.x < Orth_Pos_Work.x && Orth_Pos.y == Orth_Pos_Work.y)
			{
				//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
				Direction = Direc_E_S;
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
	}
	else if (!Working && Moving)
	{
	Orth_Pos.w = Pos_Sor.w = Frame_Weight;
	Orth_Pos.h = Pos_Sor.h = Frame_Height;
	if ((Current_Time - Last_Time) > Time_Next_Sprite)
	{
		if (Direction = Direc_S)
		{
			//((int)(X_Sor.x+Weight)/(Weight*Number_Frame_Direc)!=Frame_East_South_x)
			if ((int)(Pos_Sor.x + Frame_Weight) / (Frame_Weight * Number_Frame_Direc) != Frame_South_x)
			{
				Pos_Sor.x = Frame_Weight * Number_Frame_Direc * Frame_South_x;
			}
			else
			{
				Pos_Sor.x += Frame_Weight;
			}
		}
		else if (Direction = Direc_W_S)
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
		else if (Direction = Direc_W)
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
		else if (Direction = Direc_W_N)
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
		else if (Direction = Direc_N)
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
		else if (Direction = Direc_E_N)
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
		else if (Direction = Direc_E)
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
		else if (Direction = Direc_E_S)
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
    }
}*/
/*void Move_Cell_x_to_Cell_y(Unit_Details Unit_Dt[200], int Unit_Type, int Country, SDL_Rect& X, SDL_Rect& X_Iso, SDL_Rect& X_Sor, stack<Pair>& Path, bool& Moving_X_to_Y, int& Direc, int Current_Time, int Last_Time)
{
	Current_Time = SDL_GetTicks();
	int Frame_Delay = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Moving_Next_Frame;
	int Number_Frame_Direc = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Number_Moving_Direction_Frame;
	bool Move = ((Current_Time - Last_Time) > Frame_Delay);
	int Weight = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Moving_Frame_Weight;
	int Height = Country_Unit_Details_Texture_List[Country].Unit_Dt_Texture[Unit_Type].Moving_Frame_Height;
	X.w = X_Sor.w = Weight;
	X.h = X_Sor.h = Height;
	int Speed = Unit_Dt[Unit_Type].Speed;
	if (!Path.empty() && Moving_X_to_Y && Move)
	{
		if (X.y / Orth_Tile_Weight == Path.top().first && X.x / Orth_Tile_Weight < Path.top().second)
		{
			X.x += Speed;
			Direc = Direc_E_S;
			X_Sor.y = Frame_East_South_y;
			if ((int)(X_Sor.x + Weight) / (Weight * Number_Frame_Direc) != Frame_East_South_x)
			{
				X_Sor.x = Frame_East_South_x * Weight * Number_Frame_Direc;
			}
			else
			{
				X_Sor.x += Weight;
			}
		}
		else if (X.y / Orth_Tile_Weight == Path.top().first && X.x / Orth_Tile_Weight > Path.top().second)
		{
			X.x -= Speed;
			Direc = Direc_W_N;
			X_Sor.y = Frame_West_North_y;
			if ((int)(X_Sor.x + Weight) / (Weight * Number_Frame_Direc) != Frame_West_North_x)
			{
				X_Sor.x = Frame_West_North_x * Weight * Number_Frame_Direc;
			}
			else
			{
				X_Sor.x += Weight;
			}
		}
		else if (X.x / Orth_Tile_Weight == Path.top().second && X.y / Orth_Tile_Weight < Path.top().first)
		{
			X.y += Speed;
			Direc = Direc_W_S;
			if ((int)(X_Sor.x + Weight) / (Weight * Number_Frame_Direc) != Frame_West_South_x)
			{
				X_Sor.x = Frame_West_South_x * Weight * Number_Frame_Direc;
			}
			else
			{
				X_Sor.x += Weight;
			}
			X_Sor.y = Frame_West_South_y;
		}
		else if (X.x / Orth_Tile_Weight == Path.top().second && X.y / Orth_Tile_Weight > Path.top().first)
		{
			X.y -= Speed;
			Direc = Direc_E_N;
			if ((int)(X_Sor.x + Weight) / (Weight * Number_Frame_Direc) != Frame_East_North_x)
			{
				X_Sor.x = Frame_East_North_x * Weight * Number_Frame_Direc;
			}
			else
			{
				X_Sor.x += Weight;
			}
			X_Sor.y = Frame_East_North_y;
		}
		else if (X.y / Orth_Tile_Weight < Path.top().first && X.x / Orth_Tile_Weight < Path.top().second)
		{
			X.x += Speed;
			X.y += Speed;
			Direc = Direc_S;
			if ((int)(X_Sor.x + Weight) / (Weight * Number_Frame_Direc) != Frame_South_x)
			{
				X_Sor.x = Frame_South_x * Weight * Number_Frame_Direc;
			}
			else
			{
				X_Sor.x += Weight;
			}
			X_Sor.y = Frame_South_y;
		}
		else if (X.y / Orth_Tile_Weight > Path.top().first&& X.x / Orth_Tile_Weight < Path.top().second)
		{
			X.x += Speed;
			X.y -= Speed;
			Direc = Direc_E;
			if ((int)(X_Sor.x + Weight) / (Weight * Number_Frame_Direc) != Frame_East_x)
			{
				X_Sor.x = Frame_East_x * Weight * Number_Frame_Direc;
			}
			else
			{
				X_Sor.x += Weight;
			}
			X_Sor.y = Frame_East_y;
		}
		else if (X.y / Orth_Tile_Weight > Path.top().first&& X.x / Orth_Tile_Weight > Path.top().second)
		{
			X.x -= Speed;
			X.y -= Speed;
			Direc = Direc_N;
			if ((int)(X_Sor.x + Weight) / (Weight * Number_Frame_Direc) != Frame_North_x)
			{
				X_Sor.x = Frame_North_x * Weight * Number_Frame_Direc;
			}
			else
			{
				X_Sor.x += Weight;
			}
			X_Sor.y = Frame_North_y;
		}
		else if (X.y / Orth_Tile_Weight<Path.top().first && X.x / Orth_Tile_Weight>Path.top().second)
		{
			X.x -= Speed;
			X.y += Speed;
			Direc = Direc_W;
			if ((int)(X_Sor.x + Weight) / (Weight * Number_Frame_Direc) != Frame_West_x)
			{
				X_Sor.x = Frame_West_x * Weight * Number_Frame_Direc;
			}
			else
			{
				X_Sor.x += Weight;
			}
			X_Sor.y = Frame_West_y;
		}
		if (X.x / Orth_Tile_Weight == Path.top().second && X.y / Orth_Tile_Weight == Path.top().first)
		{
			Moving_X_to_Y = false;
			Path.pop();
		}
		Convert(X_Iso, X, 0);
		Last_Time = Current_Time;
	}
	if (!Path.empty() && !Moving_X_to_Y)
	{
		Moving_X_to_Y = true;
	}
	if (Path.empty())
	{
		Moving_X_to_Y = false;
	}
}*/
int Check_A_Behind_B(int Orth_A_x, int Orth_A_y, int Orth_A_z, int Orth_B_x, int Orth_B_y, int Orth_B_z,
	int A_Weight, int A_Height, int B_Weight, int B_Height, double Size_Number_Cell_A, double Size_Number_Cell_B)
{
	int z_A = (A_Height - A_Weight * tan(3.14 / 6));
	int z_B = (B_Height - B_Weight * tan(3.14 / 6));
	int A_Weight_ = Size_Number_Cell_A * Orth_Tile_Weight; //((A_Weight/2)/cos(3.1415/6))/sqrt(5/4);
	// Lý do trừ đi 1 : Phải trừ đi 1: Ví dụ ô 0,0 có chiều dài, rộng chiếm 1 Tile. Nếu không trừ đi 1 thì lúc này chiều dài của nó sẽ là 32, tức điểm cuối của nó sẽ là 32,32 và đè lên ô tiếp theo, tức chúng đã va chạm !\
	// Một cách khác để không phải trừ 1 đó là cho Size Number Cell là số thập phân nhỏ hơn 1
	Point Point_A;
	Point Point_A_;
	int B_Weight_ = Size_Number_Cell_B * Orth_Tile_Weight; //((B_Weight/2)/cos(3.1415/6))/sqrt(5/4);
	Point Point_B;
	Point Point_B_;
	Point_A.x = Orth_A_x;
	Point_A.y = Orth_A_y;
	Point_A.z = Orth_A_z;
	Point_A_.x = Orth_A_x + A_Weight_;
	Point_A_.y = Orth_A_y + A_Weight_;
	Point_A_.z = Orth_A_z + z_A;
	Point_B.x = Orth_B_x;
	Point_B.y = Orth_B_y;
	Point_B.z = Orth_B_z;
	Point_B_.x = Orth_B_x + B_Weight_;
	Point_B_.y = Orth_B_y + B_Weight_;
	Point_B_.z = Orth_B_z + z_B;
	int a_1 = Point_A.x - Point_A_.y;
	int a_2 = Point_A_.x - Point_A.y;
	int a_3 = Point_A.x - Point_A_.z;
	int a_4 = Point_A_.x - Point_A.z;
	int a_5 = Point_A.z - Point_A_.y;
	int a_6 = Point_A_.z - Point_A.y;
	int b_1 = Point_B.x - Point_B_.y;
	int b_2 = Point_B_.x - Point_B.y;
	int b_3 = Point_B.x - Point_B_.z;
	int b_4 = Point_B_.x - Point_B.z;
	int b_5 = Point_B.z - Point_B_.y;
	int b_6 = Point_B_.z - Point_B.y;
	bool Check_1 = (a_1 <= b_1 && b_1 <= a_2) || (a_1 <= b_2 && b_2 <= a_2) || (b_1 <= a_1 && a_1 <= b_2) || (b_1 <= a_2 && a_2 <= b_2);
	bool Check_2 = (a_3 <= b_3 && b_3 <= a_4) || (a_3 <= b_4 && b_4 <= a_4) || (b_3 <= a_3 && a_3 <= b_4) || (b_3 <= a_4 && a_4 <= b_4);
	bool Check_3 = (a_5 <= b_5 && b_5 <= a_6) || (a_5 <= b_6 && b_6 <= a_6) || (b_5 <= a_5 && a_5 <= b_6) || (b_5 <= a_6 && a_6 <= b_6);
	//cout << Orth_A_y << " " << A_Weight_ << endl;
	//cout << Orth_A_x << endl;
	/*cout << a_1 << " " << a_2 << endl;
	cout << a_3 << " " << a_4 << endl;
	cout << a_5 << " " << a_6 << endl;
	cout << b_1 << " " << b_2 << endl;
	cout << b_3 << " " << b_4 << endl;
	cout << b_5 << " " << b_6 << endl;*/
	if (!(Check_1 && Check_2 && Check_3))
	{
		//cout << "Nothing Behind" << endl;
		return 0;
	}
	else
	{
		if (Point_A_.x < Point_B.x || Point_A_.y < Point_B.y || Point_A_.z < Point_B.z)
		{
			//cout << "A behind B" << endl;
			return 1;
		}

		else  if (Point_B_.x < Point_A.x || Point_B_.y < Point_A.y || Point_B_.z < Point_A.z)
		{
			/*cout << Point_B_.x << " " << Point_A.x << endl;
			cout << Point_B_.y << " " << Point_A.y << endl;
			cout << Point_B_.z << " " << Point_A.z << endl;
			cout << "B behind A" << endl;*/
			return -1;
		}
	}
}

bool Check_Cell_Empty(Game_Object*Game_Object_Check ,int Row, int Col, Cell_Uniform_Grid Map_UG_Layer[Number_Row_Map][Number_Col_Map]) // Kiểm tra xem Cell trong Map Uniform Grid này có rỗng không, nếu tất cả phần tử bằng -1 hoặc Cell này rỗng thì return true.
{
	bool Check = true;
	if (Map_UG_Layer[Row][Col].List_Object_in_Cell.empty())
	{
		//cout << "yes";
		return true;
	}
	for (int i = 0; i < Map_UG_Layer[Row][Col].List_Object_in_Cell.size(); i++)
	{
		if (Map_UG_Layer[Row][Col].List_Object_in_Cell[i].Object_Type != -1)
		{
			if (Map_UG_Layer[Row][Col].List_Object_in_Cell[i].Country == Game_Object_Check->Get_Country() &&
				Map_UG_Layer[Row][Col].List_Object_in_Cell[i].Object_Type == Game_Object_Check->Get_Unit_Type() &&
				Map_UG_Layer[Row][Col].List_Object_in_Cell[i].Pos == Game_Object_Check->Pos_in_List_Object)
			{
				continue;
			}
			//cout << "yes";
			Check = false;
			break;
		}
	}
	if (Check)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Function dưới xét cả đối tượng, tức nếu có đối tượng trong ô đó thì ô đó không trống
bool Check_Cell_Empty_include_Object(int Row, int Col, Cell_Uniform_Grid Map_UG_Layer[Number_Row_Map][Number_Col_Map]) // Kiểm tra xem Cell trong Map Uniform Grid này có rỗng không, nếu tất cả phần tử bằng -1 hoặc Cell này rỗng thì return true.
{
	bool Check = true;
	if (Map_UG_Layer[Row][Col].List_Object_in_Cell.empty())
	{
		//cout << "yes";
		return true;
	}
	for (int i = 0; i < Map_UG_Layer[Row][Col].List_Object_in_Cell.size(); i++)
	{
		if (Map_UG_Layer[Row][Col].List_Object_in_Cell[i].Object_Type != -1)
		{
			//cout << "yes";
			Check = false;
			break;
		}
	}
	if (Check)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Load_and_Get_infor_image(Country_Unit_Details_Texture Unit_Dt_Texture[50], int Country_Index, int Unit_Type, const char* Unit_Standing_file_name, int Number_Frame_Standing, int Next_Frame_Standing, int Focus_Point_Standing_x, int Focus_Point_Standing_y,
	const char* Unit_Moving_file_name, int Number_Frame_Moving, int Next_Frame_Moving, int Focus_Point_Moving_x, int Focus_Point_Moving_y,
	const char* Unit_Carry_file_name, int Number_Frame_Carry, int Next_Frame_Carry, int Focus_Point_Carry_x, int Focus_Point_Carry_y,
	const char* Unit_Working_file_name, int Number_Frame_Working, int Next_Frame_Working, int Focus_Point_Working_x, int Focus_Point_Working_y,
	const char* Unit_Attacking_file_name, int Number_Frame_Attacking, int Next_Frame_Attacking, int Focus_Point_Attacking_x, int Focus_Point_Attacking_y,
	const char* Unit_Death_file_name, int Number_Frame_Death, int Next_Frame_Death, int Focus_Point_Death_x, int Focus_Point_Death_y,
	const char* Unit_Dead_file_name, int Number_Frame_Dead, int Next_Frame_Dead, int Focus_Point_Dead_x, int Focus_Point_Dead_y)
{
	SDL_Surface* Texture_Surface = IMG_Load(Unit_Standing_file_name);
	SDL_Rect Size;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Standing_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	SDL_QueryTexture(Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Standing_Texture, NULL, NULL, &Size.w, &Size.h);
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Standing_Frame_Weight = Size.w / Number_Frame_Standing;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Standing_Frame_Height = Size.h;
	if (Number_Frame_Standing == 1)
	{
		cout << "yes";
		Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Number_Standing_Direction_Frame = 1;
	}
	else
	{
		Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Number_Standing_Direction_Frame = Number_Frame_Standing / 5;
	}
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Standing_Next_Frame = Next_Frame_Standing;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Focus_Point_Standing.x = Focus_Point_Standing_x;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Focus_Point_Standing.y = Focus_Point_Standing_y;

	Texture_Surface = IMG_Load(Unit_Moving_file_name);
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Moving_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	SDL_QueryTexture(Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Moving_Texture, NULL, NULL, &Size.w, &Size.h);
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Moving_Frame_Weight = Size.w / Number_Frame_Moving;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Moving_Frame_Height = Size.h;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Number_Moving_Direction_Frame = Number_Frame_Moving / 5;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Moving_Next_Frame = Next_Frame_Moving;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Focus_Point_Moving.x = Focus_Point_Moving_x;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Focus_Point_Moving.y = Focus_Point_Moving_y;

	Texture_Surface = IMG_Load(Unit_Carry_file_name);
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Carry_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	SDL_QueryTexture(Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Carry_Texture, NULL, NULL, &Size.w, &Size.h);
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Carry_Frame_Weight = Size.w / Number_Frame_Carry;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Carry_Frame_Height = Size.h;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Number_Carry_Direction_Frame = Number_Frame_Carry / 5;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Carry_Next_Frame = Next_Frame_Carry;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Focus_Point_Carry.x = Focus_Point_Carry_x;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Focus_Point_Carry.y = Focus_Point_Carry_y;

	Texture_Surface = IMG_Load(Unit_Working_file_name);
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Working_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	SDL_QueryTexture(Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Working_Texture, NULL, NULL, &Size.w, &Size.h);
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Working_Frame_Weight = Size.w / Number_Frame_Working;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Working_Frame_Height = Size.h;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Number_Working_Direction_Frame = Number_Frame_Working / 5;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Working_Next_Frame = Next_Frame_Working;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Focus_Point_Working.x = Focus_Point_Working_x;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Focus_Point_Working.y = Focus_Point_Working_y;

	Texture_Surface = IMG_Load(Unit_Attacking_file_name);
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Attacking_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	SDL_QueryTexture(Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Attacking_Texture, NULL, NULL, &Size.w, &Size.h);
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Attacking_Frame_Weight = Size.w / Number_Frame_Attacking;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Attacking_Frame_Height = Size.h;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Number_Attacking_Direction_Frame = Number_Frame_Attacking / 5;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Attacking_Next_Frame = Next_Frame_Attacking;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Focus_Point_Attacking.x = Focus_Point_Attacking_x;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Focus_Point_Attacking.y = Focus_Point_Attacking_y;

	Texture_Surface = IMG_Load(Unit_Death_file_name);
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Death_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	SDL_QueryTexture(Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Death_Texture, NULL, NULL, &Size.w, &Size.h);
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Death_Frame_Weight = Size.w / Number_Frame_Death;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Death_Frame_Height = Size.h;
	if (Number_Frame_Death == 1)
	{
		//cout << "yes";
		Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Number_Death_Direction_Frame = 1;
	}
	else
	{
		Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Number_Death_Direction_Frame = Number_Frame_Death / 5;
	}
	//Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Number_Death_Direction_Frame = Number_Frame_Death / 5;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Death_Next_Frame = Next_Frame_Death;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Focus_Point_Death.x = Focus_Point_Death_x;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Focus_Point_Death.y = Focus_Point_Death_y;

	Texture_Surface = IMG_Load(Unit_Dead_file_name);
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Dead_Texture = SDL_CreateTextureFromSurface(Renderer, Texture_Surface);
	SDL_QueryTexture(Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Dead_Texture, NULL, NULL, &Size.w, &Size.h);
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Dead_Frame_Weight = Size.w / Number_Frame_Dead;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Dead_Frame_Height = Size.h;
	if (Number_Frame_Dead == 1)
	{
		//cout << "yes";
		Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Number_Dead_Direction_Frame = 1;
	}
	else
	{
		Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Number_Dead_Direction_Frame = Number_Frame_Dead / 5;
	}
	//Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Number_Dead_Direction_Frame = Number_Frame_Dead / 5;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Dead_Next_Frame = Next_Frame_Dead;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Focus_Point_Dead.x = Focus_Point_Dead_x;
	Unit_Dt_Texture[Country_Index].Unit_Dt_Texture[Unit_Type].Focus_Point_Dead.y = Focus_Point_Dead_y;

	Texture_Surface = IMG_Load("s.png");
	SDL_Color rgb = {};
	//SDL_LockSurface(Texture_Surface);
	Uint32 data = get_pixel32(Texture_Surface, 710, 279);
	//SDL_UnlockSurface(Texture_Surface);
	SDL_GetRGB(data, Texture_Surface->format, &rgb.r, &rgb.g, &rgb.b);
	printf(" RGB : %d %d %d \n", rgb.r, rgb.g, rgb.b);
	//cout << " RGB : " << (int)rgb.r << " " << rgb.g << " " << rgb.b << endl;
	//SDL_Color
}

Uint32 get_pixel32(SDL_Surface* surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;

	case 2:
		return *(Uint16*)p;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;

	case 4:
		return *(Uint32*)p;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}

