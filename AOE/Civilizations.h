#ifndef CIVILIZATIONS_H_INCLUDED
#define CIVILIZATIONS_H_INCLUDED
//#include "Civilizations.h"
class Civil;
class Civil_Player;
class Civil_Computer;
#include "vector"
#include "Game_Object.h"
#include "Init.h"
#include "Common_Function.h"
//class Game_Object;
using namespace std;
class Civil
{
public:
	Civil() {};
	~Civil() {};
	Civil(int Type_Control_Object_Value)
	{
		Type_Control_Object = Type_Control_Object_Value;
	};
	//void Train(int Unit_Type);
	void Set_Civil_Name();
	void Set_Civil_Index(int Index);
	void Set_Civil_Name(int Civil_Name);
	int Get_Civil_Name();
	void Set_Techs();
	void Set_Tech_Dt(); // Cài đặt vị trí các nút, giá tiền cho mỗi công nghệ
	// Ý tưởng để kiểm tra công nghệ yêu cầu để nâng cấp công nghệ khác nhanh hơn, tạo một vector trong Tech_Details chứa các công nghệ yêu cần cần có
	// Sau đó sử dụng vòng for duyệt Vector này, rồi check vector Techs_Available, nếu Tech trong Tech_Details mà khả dụng trong Tech_Available thì return true, một cái khác return false
	// Nếu Vector yêu cầu công nghệ rỗng, return tr                                                                                                     ue luôn
	// Còn bây giờ thì xử lý thí nghiệm Lý
	void Set_Unit_Dt(); // Cài đặt giá tiền, vị trí train, ion cho các đơn vị quân.
	void Set_Unit(int Unit_Type_Value, string Unit_Type_Name_Value, int Unit_Type_Property_Value, double Size_Number_Cell_Value, SDL_Rect Icon_Pos_Sor_Value, SDL_Rect Icon_Iso_Pos_Value, int Cost_Food_Value, int Cost_Gold_Value, int Cost_Wood_Value, int Cost_Stone_Value, int Weight_Value, int Height_Value,
		int Hit_Point_Value, int Damage_Value, int Armor_Value, int Attack_Range_Value, int Speed_Value, int T_N_Standing_Value, int T_N_Standing_Sprite_Value, int T_N_Moving_Value, int T_N_Moving_Sprite_Value,
		int T_N_Carry_Value, int T_N_Carry_Sprite_Value, int T_N_Working_Value, int T_N_Working_Sprite_Value, int T_N_Attacking_Value, int T_N_Attacking_Sprite_Value,
		int T_N_Death_Value, int T_N_Death_Sprite_Value, int T_N_Dead_Value, int T_N_Dead_Sprite_Value, int Train_Location_Value, int Time_Train_Value, int Sub_Menu_Required_Value);
	void Set_Button_Dt();
	void Disable_Tech(int Tech_Type);
	void Effect(int Tech_Type);
	void Enable_Unit(int Unit_Type);
	int Get_Civil_Index();
	int Get_Type_Control_Object();
	Tech_Details Get_Tech_Details(int Tech_Type);
	bool Check_Tech(int Tech_Type);
	bool Check_Tech_Available(int Tech_Type);
	bool Check_Tech_Researching(int Tech_Type); // Kiểm tra xem công nghệ nào đang được nghiên cứu, nếu đang được nghiên cứu sẽ không hiển thị để cho mình nghiên cứu nữa
	bool Check_Tech_Display(int Tech_Type, Choose_Object Choose_Object_Game); // Kiểm tra xem công nghệ này có thể hiển thị lên màn hình hay không, trong trường hợp nó đang được nâng cấp hoặc quốc gia này
	                                                                       // không tồn tại công nghệ này thì sẽ không hiển thị
	bool Check_Tech_to_Research(int Tech_Type, Choose_Object Choose_Object_Game, int x_Pos_Click, int y_Pos_Click, stack<int> Sub_Menu); // Kiểm tra công nghệ nào có thể nâng cấp nếu đủ lượng tài nguyên, đồng thời phải đúng vị trí cũng như nơi cần nghiên cứu, các công nghệ phụ để nghiên cứu
	void Enable_Tech_Researching(int Tech_Type);
	void Disable_Tech_Researching(int Tech_Type);
	bool Check_Unit(int Unit_Type);
	bool Check_Unit_Disable(int Unit_type);
	void Check_Unit_Display(int Unit_Type, Choose_Object Choose_Object_Game, stack<int> Sub_Menu); // Kiểm tra và hiển thị các Icon của các Unit khi chọn các nhà tương ứng.
	bool Check_Train_Game_Unit(int Unit_Type, Choose_Object Choose_Object_Game, int x_Pos_Click, int y_Pos_Click, stack<int> Sub_Menu, int Map_Layer_1[50][50], int Map_Layer_2[50][50], int Location_Position, Cell_Uniform_Grid Map_UG_Layer_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Layer_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map]); // Train đơn vị quân hoặc nhân dân 
	bool Check_Button_Perform(int Button_Type, int x_Pos_Click, int y_Pos_Click, stack<int> &Sub_Menu, Choose_Object Choose_Object_Game);
	bool Find_Locate_to_Train(SDL_Rect Train_Location, SDL_Rect& Output_Train_Location, Cell_Uniform_Grid Map_UG_Layer_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Layer_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map]);
	int Get_Pos_New_Object(); // Hàm trả về một vị trí thức hợp để thêm đối tượng vào trong List
	void Push_Object_to_Cell(Cell_Uniform_Grid Map_UG_Layer[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map], Game_Object* Game_Object_Push);
	int Get_Epoch();
	bool Check_Locate_Build_House(int Unit_Type_House_Build_Value, SDL_Rect Locate_Build_House, Cell_Uniform_Grid Map_UG_Layer_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Layer_2[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_UG_Check_Click[Number_Row_Map][Number_Col_Map]);
	vector<Game_Object*> Civil_Game_Object_List;
	vector<int> Pos_Town_Center_List; // Danh sách các Pos của nhà Town Center của quốc gia này
	vector<int> Pos_Barracks_List; // Danh sách các Pos của nhà Barracks trong quốc gia này
	int Number_Villager = 0;
	int Number_Clubman = 0;
	// Thông tin về những ô Map đã mở
	bool Map_Explore[50][50] = {};
	
	int Get_Amount_Food(); // Nhận thông tin hiện tại về lượng thực
	int Get_Amount_Wood();
	int Get_Amount_Gold();
	int Get_Amount_Stone();
	bool Pay_Money(int Amount_Food, int Amount_Gold, int Wood, int Stone);
	Tech_Details Tech_Dt[200]; // Chi tiết từng Tech, vị trí của Tech, giá tiền nâng,...
	Unit_Details Unit_Dt[200]; // Chi tiết về từng đơn vị cho từng quốc gia,...
	Button_Details Button_Dt[200]; // Chi tiết về các nut bấm cho từng quốc gia, thực ra chỉ người chơi mới cần tới nút bấm này
	bool Check_Button_Display(int Button_Type, stack<int> Sub_Menu, Choose_Object Choose_Object_Game);

	int Amount_Food = 1500; // Số lượng tài nguyên thực hiện có của quốc gia
	int Amount_Stone = 1500;
	int Amount_Wood = 1500;
	int Amount_Gold = 1500;
	int Get_Population();
	int Get_Population_Max();

	int Pos_in_Civil_List = -1; // Pos của nền văn minh này trong list các nền văn minh
	virtual void Civil_Develop(); 
	bool Civil_Train_Add_Unit(int Unit_Type_Train); // hàm này sẽ thực hiện những việc cần thiết khi có những đơn vị được sinh ra như tăng dân số lên 1, ...
protected:
	bool Unit[200]; // Các đơn vị trong nền văn minh
	bool Unit_Disable[200]; // Các đơn vị không có ở dân tộc này 
	bool Techs_Disable[200]; // Các công nghệ bị tắt đi, tức không có ở dân tộc này
	bool Techs_Available[200]; // Các công nghệ đã khả dụng
	bool Tech_Researching[200]; // Các công nghệ hiện đang nghiên cứu
	int Civil_Index = -1; // Là dân tộc thứ bao nhiêu , ví dụ Country 1 , Country 2, ...
	int Civil_Name = -1; // Tên dân tộc : Egyptian , Yamato, Greek,...
	int Population = 0; // Dân số hiện tại
	int Population_Max = 0; // Dân số tối đa có thể xin được tại thời điểm hiện tại
	int Population_Limit = 200; // Dân số giới hạn
	int Epoch = Epoch_Stone_Age; // Thời đại hay cấp độ của nền văn minh
	int Type_Control_Object = -1; // Loại điều khiển quôc gia này, Player hay Computer
};
class Civil_Computer : public Civil
{
public:
	Civil_Computer() {};
	~Civil_Computer() {};
	Civil_Computer(int Type_Control_Object_Value)
	{
		Type_Control_Object = Type_Control_Object_Value;
	};
	void Civil_Develop(); // Hàm phát triển cho Máy tính
private:
	int Number_Villager_Max = 5; // Số lượng nông dân max mà máy tính có thể xin ra
	int Number_Clubman_Max = 5; // Số lượng rìu bổ Max có thể xin ra
	void Train_Unit(int Unit_Train); // Train một loại quân được chỉ định sẵn
};
class Civil_Player : public Civil
{
public:
	Civil_Player() {};
	~Civil_Player() {};
	Civil_Player(int Type_Control_Object_Value)
	{
		Type_Control_Object = Type_Control_Object_Value;
	};
	void Handle_Event();
private:

};
#endif // !CIVILIZATIONS_H_INCLUDED
