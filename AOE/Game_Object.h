#ifndef GAME_OBJECT_H_INCLUDED
#define GAME_OBJECT_H_INCLUDED
//#include "Game_Object.h"
class Game_Object;
#include "Common_Function.h"
#include "Init.h"
#include <iostream>
#include <SDL.h>
#include <stack>
#include <math.h>
#include <queue>
using namespace std;
class Game_Object
{
public:
	Game_Object() {};
	~Game_Object() {};
	int Get_Unit_Type();
	virtual void Load_to_Screen(); // Load Image of Object Game to Screen
	virtual void Move(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*>& Civil_Computer_List, vector<Civil*>& Civil_Player_List, int Pos); // Move Object Game from X to Y
	virtual void Move_Cell_x_to_Cell_y(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*>Civil_Computer_List, vector<Civil*> Civil_Player_List, int Pos); // Hàm di chuyển đối tượng từ ô này sang ô khác
	virtual void Update_Cell(Cell_Uniform_Grid Map[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], int Pos_in_List_Game_Object); // Update các ô chứa đối tượng trong trường hợp đối tượng di chuyển
	virtual void Attack(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], vector<Civil*> Civil_Computer_List, vector<Civil*>Civil_Player_List, int Pos); // Tấn công đối tượng khác
	virtual void Work(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*> Civil_Computer_List, vector<Civil*>Civil_Player_List, int Pos); // Hàm giúp cho nông dân có khả năng làm việc : chặt gỗ, ăn quả, khai thác vàng, đá,...
	virtual void Take_Damage(Civil* Civil_Gaia_List, vector<Civil*>Civil_Player_List, vector<Civil*>Civil_Computer_List);
	virtual void Set(SDL_Rect Assign_Rect_Orth, SDL_Rect Assign_Rect_Iso, SDL_Rect Assign_Rect_Sor, int Unit_Type, int z, int Country, int Country_Name, int Selection_w, int Selection_h);
	virtual void Enable_Search_A_Star(); // Phương thức ảo : Phương thức này trong Gam_Object sẽ không tồn tại vì không có gì ngoài hai dấu {} :), nhưng trong Dynamic_Object :
										 // nó kế thừa từ Game_Object thì sẽ chuyển biến bool Search_A_Star thành true, tức khởi động việc tìm kiếm A*
	                                     // Sau nhiều lần xem xét tôi đã tối ưu thuật toán này hơn, chỉ search 1 lần và di chuyển tới đích, chỉ khi nào gặp chướng ngại vật và va chạm thì mới serach tiếp để tìm đường đi
	/*void Load_Sprite_Sheet(int Unit_Type, SDL_Rect& Orth_Pos, SDL_Rect& Pos_Sor, SDL_Rect& Orth_Pos_Work, int Direction,
		int Frame_Weight, int Frame_Height, int Number_Frame_Direc, int Time_Next_Sprite, int Last_Time, int Current_Time);*/
	// Load Sprite sheet cho các đối tượng chuyển động hoặc không chuyển động, nếu đối tượng đứng yên thì chỉ có 1 hướng
	virtual int Get_Hit_Point(); // Trả về Hit Point của đối tượng
	virtual int Get_Search_Radius(); // Trả về bán kính dò của các đơn vị
	virtual int Get_Unit_Type_Property(); 
	virtual void Set_Unit_Type_Property(int Unit_Type_Property_Value);
	virtual void Enable_Search_Move_To_Attack();
	virtual void Enable_Moving_To_Attack();
	bool Hit_Box_Activated = false; // Hit Box có đang bật hay không
	virtual Hit_Box Get_Hit_Box(); // Nhận thông tin về Hit Box
	virtual void Set_Hit_Box(int Row, int Col, int Damage, int Blast_Width, int Blast_Attack_Type); // Cài đặt vị trí và thông tin cho Hit B
	virtual bool Check_Hit_Box_Activated();
	virtual void Disable_Hit_Box();
	virtual void Change_Unit_Type(int Unit_Type_Value); //Hàm giúp chuyển đổi đối tượng, chỉ dùng cho nông dân, giúp chuyển từ dân làng sang người chặt gỗ, ....
	virtual void Change_Object_Status(int Object_Status_Value); // Thay đổi trạng thái của đối tượng, ví dụ từ đứng chuyển sang di chuyển, di chuyển sang làm việc ,...
	virtual SDL_Rect Get_Pos_Sor();
	virtual SDL_Rect Get_Orth_Pos();
	virtual SDL_Rect Get_Iso_Pos();
	virtual void Set_Orth_Pos_Object_Attack(vector<Civil*>Civil_Player_List, vector<Civil*>Civil_Computer_List, SDL_Rect Orth_Pos_Attack_Value, int Unit_Type_Object_Attack_Value, int Pos_Object_Attack_Value, int Country_Object_Attack_Value, int Type_Control_Object_Object_Attack_Value, int Pos_Control_Object_Object_Attack_Value);
	virtual void Set_Orth_Pos_Work(SDL_Rect Orth_Pos_Work_Value, int Unit_Type_Object_Work_Value, int Pos_Object_Work_Value, int Country_Object_Work_Value, int Unit_Type_Control_Work_Value, int Pos_Control_Work_Value);
	virtual void Get_Infor_Attack_Object(int Unit_Type_Attack_Object_Value, int Pos_Attack_Object_Value, int Country_Attack_Object_Value, int Type_Control_Object_Attack_Object_Value, int Pos_Control_Object_Attack_Object_Value);
	int Get_Country();
	int Get_Country_Name();
	int Set_Country_Name(int Country_Name_Value);
	void Change_Orth_Pos(SDL_Rect Orth_Pos_Next); // Hàm thay đổi tọa độ của đối tượng Game
	void Set_Orth_Pos_Move(SDL_Rect Orth_Pos_Move_Next); // Hàm thiết lập điểm đến cho đối tượng di chuyển.
	virtual void Research_Tech(Tech_Details Tech_Dt[], Civil* Civil_Gaia_List, vector<Civil*>& Civil_Computer_List, vector<Civil*>& Civil_Player_List);
	virtual void Set_Object_Properties(Unit_Details Unit_Dt[]); // Cài đặt các thông số cho đối tượng như máu, damage,...
	void Start_Researching_Tech(int Tech_Type);
	virtual void Cancel_Researching_Tech();
	virtual void Cancel_Training_Unit();
	virtual void Train_Unit(int Unit_Type, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*>& Civil_Computer_List, vector<Civil*>& Civil_Player_List);
	virtual void Add_to_Train_Unit_Queue(int Unit_Type);
	virtual int Get_Number_Unit_Train();
	virtual void Change_Unit_Type_Build(int Unit_Type_Build_Value);
	bool Training_Unit = false;
	int Training_Unit_Type = -1;
	int Percent_Training_Unit = -1;
	stack<int> Pos_Behind; // Position của vật thể đằng sau vật thể này trong Map List 2 của class Manager
	virtual void Build(int Unit_Type_Build, SDL_Rect Orth_Pos_Build, Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*> Civil_Computer_List, vector<Civil*>Civil_Player_List, int Pos);
	int z;
	double Size_Number_Cell = 0;
	bool Visit = false;
	bool Change_Status = false; // Nếu đổi tượng thay đổi trạng thái, biến này sẽ chuyển thành true
	//bool Research = false;
	int Percent_Tech_Researching = -1;
	int Percent_Complete_Build = 0; // Phần trăm công việc đã hoàn thiện khi xây nhà, nếu chưa đủ 100 % thì không thể sử dụng được
	int Last_Time = 0;
	int Current_Time = 0;
	int Current_Time_Move = 0;
	int Last_Time_Move = 0;
	int Current_Time_Attack = 0;
	int Last_Time_Attack = 0;
	int Current_Time_Research = 0;
	int Last_Time_Research = 0;
	bool Researching_Tech = false;
	int Researching_Tech_Type = -1;
	int Current_Time_Train = 0;
	int Last_Time_Train = 0;	
	//bool Standing = true;
	//bool Moving = false;
	//bool Working = false;
	//bool Attacking = false;
	int Direction = Direc_S;
	void Load_Sprite_Sheet(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*> Civil_Computer_List, vector<Civil*>Civil_Player_List);
		// Function kiểm tra va chạm giữa hai vật thể nhằm xác định xem một vật thể có thể di chuyển hay không, nếu va chạm nó không thể va chạm
	int Check_Collision(Cell_Uniform_Grid Map[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Game_Object* Game_Object_Check, Civil* Civil_Gaia_List, vector<Civil*>& Civil_Computer_List, vector<Civil*>& Civil_Player_List, int Pos);
	vector<Cell_Contain_Object> List_Cell_Contain_Object;
	vector<Cell_Contain_Object> List_Cell_Contain_Object_Click;

	bool Alive = true; // True nghĩa là đối tượng còn sống, false tức đã chết
	int Unit_Type_Control = -1; // Loại điều khiển đối tượng này : Máy tính hay người chơi
	int Pos_Control = -1; // Vị trí của đất nước điều khiển nó trong Civil Player List hay Civil Computer List
	int Pos_in_List_Object; // Vị trí của đối tượng trong list đối tượng của đất nước 
	SDL_Rect Iso_Pos_Selection = {}; // Tọa độ vẽ hình thoi biểu thị cho đối tượng đang được chọn

	int Object_Status = 0;
	bool Moving_To_Attack = false; // Di chuyển tới gần đối tượng hơn để tấn công
	bool Attack_Object; // Nếu biến này đúng thì phải tấn công đối tượng ngay
	int Unit_Type_Attack_Object = -1; // Đối tượng nào đang tấn công đối tượng này
	int Pos_Attack_Object = -1; // Vị trí của đối tượng đang tấn công đối tượng này trong List
	int Country_Attack_Object = -1; // Đất nước của đối tượng đang tấn công đối tượng này 
	int Type_Control_Object_Attack_Object = -1; // Ai đang điều khiển đối tượng này : Máy tính hay người chơi ? Từ đó xác định nó thuộc Computer List hay Player List
	int Pos_Control_Object_Attack_Object = -1; // Vị trí của đối tượng điều khiển trong Computer List hoặc Player List
	int Unit_Type_Object_Attack = -1; // Đối tượng nào mà "đối tượng này" đang tấn công
	int Pos_Object_Attack = -1; // Vị trí của đối tượng mà đối tượng này tấn công trong List
	int Country_Object_Attack = -1; // Đối tượng đó thuộc nền văn minh minh nào (Thứ bao nhiêu)
	int Type_Control_Object_Object_Attack = -1; // Loại điều khiển đối tượng mà đối tượng này tấn công 
	int Pos_Control_Object_Object_Attack = -1; // Vị trí của loại điều khiển đối tượng mà đối tượng này tấn công

	virtual void Enable_Find_to_Build_House(int Unit_Type_Build_Value);
	virtual void Disable_Find_to_Build_House();
	virtual bool Get_Find_to_Build_House();
	virtual int Get_Unit_Type_Build();
	bool Search_Moving_to_Work = false;
	bool Search_Going_to_return_resource = false;
	int Work_Range = 1; // Khoảng cách tối thiểu để đối tượng làm việc, nếu khoảng cách lớn hơn thì cần di chuyển gần hơn để làm việc
	int Resource_Capacity = 0; // Lượng tài nguyên lưu trong đối tượng, khi tài nguyên này về 0 thì tức đối tượng này sẽ bắt đầu bị phân hủy và xác chết, hay lượng tài nguyên tối đa mà nông dân có thể mang
	int Resource_Bearing; // Lượng tài nguyên đang mang theo
	bool Moving_To_Work = false; // Di chuyển tới vị trí làm việc
	bool Going_to_return_resource = false;
	// Phần liên quan tới làm việc : Ăn quả, săn, bắt cá, chặt gỗ,...
	int Unit_Type_Object_Work = -1; // Loại đối tượng làm việc, có thể là Tree hoặc Berry Bush, ....
	int Pos_Object_Work = -1; // Vị trí của nó trong Gaia List
	int Country_Object_Work = -1; // Không phải tất cả đối tượng làm việc chỉ ở trong Gaia List, nó cũng có thể là nhà cửa cần sửa và xây
	int Unit_Type_Control_Work = -1;
	int Pos_Control_Work = -1;
	SDL_Rect Orth_Pos_Work = {};
	SDL_Rect Orth_Pos_Capacity = {}; // Vị trí kho chứa tài nguyên để khi nông dân làm xong vào đó cất 
	int Current_Time_Work;
	int Last_Time_Work;
	int Unit_Type_Capacity = -1;
	int Pos_Capacity = -1; // Pos của nhà chứa đồ trong Civil Game Object List
	//
	bool Resource_Exploit = false; // Đối tượng này có thể khai thác tài nguyên được hay không
	int Resource_Decay_Speed; // Tốc độ phân hủy tài nguyên của đối tượng khi chết, là thời gian, qua mỗi vòng lặp hay sau mỗi khoảng thời gian này, đối tượng sẽ trừ đi 1 tài nguyên, bằng -1 tức đối tượng không hị phân hủy
	
	int Type_Resource_Capacity; // Loại tài nguyên lưu trữ trong đối tượng
	int Death_Decay_Speed; // Tốc độ phân hủy xác chết, cũng là khoảng thời gian để trạng thái phân hủy +1, >100 tức là biến mất
	int Death_Decay_Status; // Trạng thái > 100 tức là đối tượng sẽ phân hủy hoàn toàn và biến mất
	int Change_Hit_Point(int Value_Hit_Point); // Thay đổi máu của đối tượng
	void Add_Hit_Point(int Value_Hit_Point_Add); // Hàm giúp thăng thêm lượng máu cho đối tượng
protected:
	int Unit_Type = -1; // Loại đơn vị quân, ví dụ : Legion, Phalanx, Villager,...
	int Unit_Type_Property = -1; // Tính chất của loại đối tượng đó, ví dụ cận chiến hay kị binh ,...
	int Hit_Point = 10000; // Máu của đối tượng
	int Max_Hit_Point = 10000; // Lượng máu Max
	int Frame_Delay = 0; // Khoảng thời gian giữa các lần Load Sprite tiếp theo
	int Melee_Armor = 0; // Giáp cận chiến của đối tượng, giảm sát thương
	int Pierce_Armor = 0; // Giáp chống tên, giảm sát thương từ đơn vị cung
	int Search_Radius = 5; // Range of Search to Attack of Game Object
	int Max_Range = 0; // Max Range of Attack
	int Min_Range = 0; // Min Range of Attack	
	//int Current_Time; // Thời gian hiện tại
	//int Last_Time; // Thời gian trước
	int Weight = 0; // Chiều dài của đối tượng
	int Height = 0; // Chiều cao của đối tượng
	int Country = -1;
	int Country_Name = -1; // Tên dân tộc
	bool Search_Move_To_Attack = false;
	SDL_Rect Orth_Pos = {}; // Tọa độ trên hệ tọa độ Orth
	SDL_Rect Iso_Pos = {}; // Tọa độ trên hệ Orth sau khi chuyển sang Isometric
	SDL_Rect Pos_Sor = {}; // Thông số bức ảnh
	SDL_Rect Orth_Pos_Move = {}; // Tọa độ điểm đến trong hệ tọa độ Orth
	SDL_Rect Orth_Pos_Attack = {}; // Tọa độ đối tượng cần tấn công
	SDL_Rect Orth_Pos_Attack_Last = {}; // Tọa độ đối tượng cần tấn công cũ
	/*
	Mỗi khi di chuyển tới vị trí đối tượng cần tấn công, đối tượng cần kiểm tra xem liệu đối tượng đang cần tấn công có di chuyển 
	so với trước đó hay không để có thể xem xét xem có di chuyển tiếp không hay tìm kiếm lại đường đi rồi đi tiếp
	*/
	SDL_Rect Hit_Point_Pos = { 0,0,25,4 }; // Tọa độ thanh Hit Point
	SDL_Rect Hit_Point_Pos_Sor = { 0,0,51,8 };
};
// Những đối tượng trong tự nhiên như cây cối, cây ăn quả,...
class Nature_Object : public Game_Object 
{
public:
	Nature_Object() { };
	Nature_Object(double Size_Number_Cell_Value) { Size_Number_Cell = Size_Number_Cell_Value; };
	~Nature_Object() {};

private:
	//int Size_Number_Cell = 1;
	int Resource = 0; // Lượng tài nguyên đối tượng lữu trữ : Thịt, vàng, gỗ, đá.
};
//Những động vật trong tự nhiên như sư tử, voi, cá sấu,...
class Nature_Animal_Object : public Nature_Object 
{
public:
	Nature_Animal_Object() {};
	~Nature_Animal_Object() {};

private:
	int Attack_Damage = 0; // Sát thương của đối tượng : Voi, sư tử,...
	int Reload_Time = 0;
	stack<Pair> Path;
};
// Các công trình xây dựng như nhà cửa, thành
class Building_Object : public Game_Object 
{
public:
	Building_Object() { };
	Building_Object(double Size_Number_Cell_Value) { Size_Number_Cell = Size_Number_Cell_Value; };
	~Building_Object() {};
	void Research_Tech(Tech_Details Tech_Dt[], Civil* Civil_Gaia_List, vector<Civil*>& Civil_Computer_List, vector<Civil*>& Civil_Player_List);
	void Cancel_Researching_Tech();
	void Train_Unit(int Unit_Type, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*>& Civil_Computer_List, vector<Civil*>& Civil_Player_List); // Train quân đội hoặc nông dân
	void Add_to_Train_Unit_Queue(int Unit_Type); // Thêm đối tượng vào hàng đợi để train
	void Cancel_Training_Unit(); // Hủy việc
	int Get_Number_Unit_Train(); // Nhận thông tin về số lượng đang Train
	queue<int> Unit_Train_Queue;
	
private:
	 // Phần trăm xây dựng hoàn thiện, tức là nếu 100 % là đã xây xong, còn không thì không thể sử dụng được
	//Unit_Type_Building
};
// Đối tượng tháp canh, đối tượng này có khả năng tấn công lên cần phải có Class riêng
class Watch_Tower : public Building_Object
{
public:
	Watch_Tower() {};
	~Watch_Tower() {};

private:
	int Attack_Type = 0;
	int Attack_Damage = 0;
	int Reload_Time = 0; // Thời gian tối thiểu để lặp lại công việc, ví dụ thời gian tối thiểu để bắn lại sau khi đã bắn
};
// Các đối tượng di chuyển như người, quân lính, cẩu đá,...
class Dynamic_Object : public Game_Object 
{
public:
	Dynamic_Object() {};
	Dynamic_Object(double Size_Number_Cell_Value) { Size_Number_Cell = Size_Number_Cell_Value; };
	~Dynamic_Object() {};
	// Function dùng để di chuyển các đối tượng động như quân lính, nông dân, hươu, voi,...
	void Move(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*>& Civil_Computer_List, vector<Civil*>& Civil_Player_List, int Pos);
	void Move_Cell_x_to_Cell_y(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*>Civil_Computer_List, vector<Civil*> Civil_Player_List, int Pos);
	void Enable_Search_A_Star();
	//void Update_Cell(Cell_Uniform_Grid Map[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], int Pos_in_List_Game_Object);
	void Attack(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], vector<Civil*> Civil_Computer_List, vector<Civil*>Civil_Player_List, int Pos);
	Hit_Box Get_Hit_Box();
	void Set_Hit_Box(int Row, int Col, int Damage, int Blast_Width, int Blast_Attack_Type);
	bool Check_Hit_Box_Activated();
	void Disable_Hit_Box();
	stack<Pair> Path;
	Hit_Box Hit_Box_Damage;
protected:
	int Attack_Damage = 0;
	int Attack_Type = 0;
	int Reload_Time = 0;
	int Attack_Range = 1;
	bool Search_A_Star = false;
};
// Đối tượng dân làng, có khả năng làm ăn, thu hoạch tài nguyên,... Woodcutter cũng tính là nông dân
class Villager_Object : public Dynamic_Object 
{
public:
	Villager_Object() {};
	Villager_Object(double Size_Number_Cell_Value, int Weight_Value, int Height_Value)
	{
		Size_Number_Cell = Size_Number_Cell_Value;
		Weight = Weight_Value;
		Height = Height_Value;
	}
	~Villager_Object() {};
	void Set_Object_Properties(Unit_Details Unit_Dt[]);
	void Change_Unit_Type(int Unit_Type_Value);
	void Work(Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*> Civil_Computer_List, vector<Civil*>Civil_Player_List, int Pos);
	void Enable_Find_to_Build_House(int Unit_Type_Build_Value); // Chuyển trạng thái của biến Find Build House thành true
	void Disable_Find_to_Build_House();
	bool Get_Find_to_Build_House(); // Trả về trạng thái của biến Find build house
	void Change_Unit_Type_Build(int Unit_Type_Build_Value); // Thiết lập loại đối tượng mà nông dân cần xây
	int Get_Unit_Type_Build();
	void Build(int Unit_Type_Build, SDL_Rect Orth_Pos_Build, Unit_Details Unit_Dt[200], int Country, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Civil* Civil_Gaia_List, vector<Civil*> Civil_Computer_List, vector<Civil*>Civil_Player_List, int Pos);
private:
	int Work_Rate = 0; // Khẳ năng làm việc của nông dân
	int Resource_Capacity = 10; // Khả năng lưu trữ tài nguyên, dung lượng tài nguyên có thể lưu trữ
	bool Find_to_Build_House = false; // Biến nhằm xác định xem liệu nông dân có đang tìm chỗ xây nhà không 
	int Unit_Type_Build = -1; // Loại đối tượng sẽ xây dựng
};
#endif // !GAMEOBJECT_H_INCLUDED

