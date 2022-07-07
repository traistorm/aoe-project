#ifndef COMMON_FUNCTION_H_INCLUDED
#define COMMON_FUNCTION_H_INCLUDED
class Game_Object;
//#include "Common_Function.h"
//#include "Init.h"
//#include "Game_Object.h"
#include <stack>
#include "vector"
#include <list>
#include <iterator>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;
struct Country_Unit_Details_Texture;
static int Frame_North_y = 0, Frame_East_North_y = 0, Frame_East_y = 0, Frame_East_South_y = 0, Frame_South_y = 0, Frame_West_South_y = 0, Frame_West_y = 0, Frame_West_North_y = 0;
static int Frame_North_x = 4, Frame_East_North_x = 3, Frame_East_x = 2, Frame_East_South_x = 1, Frame_South_x = 0, Frame_West_South_x = 1, Frame_West_x = 2, Frame_West_North_x = 3;
// Các hướng tương ứng , các hướng này sẽ nhân với số khung hình của 1 hướng và độ dày của một Sprite để ra vị trí của hướng trong Sprite Sheet
// Ví dụ số Sprite của một hướng là 10, khi đó đoạn hình ảnh chứa hướng Nam sẽ là 0*10*Weight<=...<1*10*Weight, vì khi đó 1 là Frame_East_South rồi ! (Đây là theo tọa độ x)
// Tọa độ y của tất cả các hướng đều như nhau và ở trên cùng bức ảnh lên đều bằng không, muốn thay đổi hướng chỉ cần thay đổi x
// Có tất cả 8 hướng, nhưng chỉ cần có 5 Frame là vì hướng Tây Nam và hướng Đông Nam là tương tự nhau, vì khi Render đối xứng hướng Tây Nam được hướng Đông Nam
static const int Orth_Tile_Weight = 32;
static const int Orth_Tile_Height = 32;
extern SDL_Renderer* Renderer; // Con trỏ của Renderer
extern SDL_Window* Window; // Con trỏ của Window
extern SDL_Event Event; // Event
extern SDL_Texture* Country_Tech_Texture[8]; // Mảng Texture cho công nghệ các nước, lý do : Các nước sẽ có màu công nghệ là khác nhau
extern SDL_Texture* Country_Unit_Icon_Texture[8]; // Mảng Texture cho các Icon của các đơn vị quân, động vật: sư tử,...
extern SDL_Texture* Country_House_Icon_Texture_Construct_1[8];
extern SDL_Texture* Country_Button_Texture[8]; // Mảng Texture chứa các Button cho từng quốc gia
extern Country_Unit_Details_Texture Country_Unit_Details_Texture_List[8]; // Mảng chứa Texture cho các đơn vị quân, bao gồm đứng yên, di chuyển, tấn công và làm việc (đối với nông dân)
extern SDL_Surface* Texture_Surface; // Surface chung cho tất cả đối tượng
extern SDL_Texture* Grass_Texture; // Texture chứa dữ liệu của cỏ
extern SDL_Texture* Tree_Texture;
extern SDL_Texture* Berry_Bush_Texture; // Cây ăn quả
extern SDL_Texture* Villager_Texture; // Texture chứa dữ liệu hình ảnh của Villager;
extern SDL_Texture* Villager_Standing_Texture; // Texture dân làng lúc đứng
extern SDL_Texture* Town_Center_1_Texture; // Texture của nhà chủ đời 1
extern SDL_Texture* Siege_Workshop_Texture;
extern SDL_Texture* Elephant_Archer_Texture;
extern SDL_Texture* Infor_Texture;
extern SDL_Texture* Infor_Source_Texture;
extern SDL_Texture* Techs_Texture;
extern SDL_Texture* Hit_Point_Texture; // Texture cho Hit Point , hay còn gọi là thanh máu.
extern SDL_Texture* Attribute_Object_Texture; // Texture cho thuộc tính của các đối tượng, hiển thị máu, giáp, kiếm ,...
static const int Number_Row_Map = 50, Number_Col_Map = 50; // Số hàng và số cột của Map
typedef pair<int, int> Pair;
typedef pair<double, pair<int, int> > P_Pair;
static const int No_Def = -1;
static int Distance_X_to_O = 500; // Khoảng cách từ điểm O(0;0) trong hệ tọa độ Orth tới điểm O(0;0) trong hệ tọa độ Iso, nhưng là hệ tọa độ Iso trong Orth
// Khoảng cách này có thể đặt tùy ý, sao cho hợp lý
const int Cell_Size = 32; // Định nghĩa kích thước 1 ô cho Uniform Grid
enum Units_Type
{
	Grass, // Cỏ
	Villager, // Dân làng
	Forager, // Nông dân hái quả
	Woodcutter, // Nông dân chặt gỗ
	Hunter, // Nông dân đi săn
	Builder, // Nông dân xây nhà
	Repair_Man, // Nông dân sửa nhà
	Tree, // Cây
	Berry_Bush, // Cây lấy quả
	Town_Center_1_M_1, // Loại ô chính, tức gặp ô này mới load ảnh (M là main) (1_M_1 : Đời 1_Ô chính_Quốc gia 1
	Town_Center_1__E_1,
	Siege_Workshop_1_M_1,
	Elephant_Archer_1, // Nhà máy ném đá và ballista
	// Loại ô phụ, ô này chỉ có nhiệm vụ xác định đây là một phần của tòa nhà Town Center, nhằm mục đích xử lý va chạm
	//Villager,
	Tree_01, // Các loại cây, cây số 01, cây số 02,...
	Tree_02,
	Mine_Gold,
	Mine_Stone,
	Stone_Miner,
	Gold_Miner,
	Town_Center,
	House, // Nhà BE, H nghĩa là House
	Barracks,
	Granary,
	Storage_Pit,
	Dock,
	Archery_Range,
	Stable,
	Farm,
	Clubman,
	Build_House, // Nhà dân đời 1
	Build_1_1, // Kích thước là 1 * 1 : Móng thành
	Build_2_2, // Kích thước 2 * 2, có thể là nhà dân đời 2 3 4
	Build_3_3 // Kich thước 3*3
};
enum Tile_Generate_Map // enum cho từng loại tile để load map
{
	Grass_0,
	Tree_0_1, // Loại cây của Gaia và loại thứ 1
	Mine_Gold_0_1,
	Mine_Stone_0_1,
	Berry_Bush_0_1,
	Town_Center_1_1_1, // Nhà chính của Country 1, đời 1 và nền văn minh 1 (Có 4 nền văn minh tất cả)
	Town_Center_2_1_1, // 
	Barracks_1_1_1, // Nhà BB
	Barracks_2_1_1,
	Villager_1,
	Villager_2,
	Clubman_1,
	Clubman_2,
};
enum Countries
{
	Country_Gaia,
	Country_1,
	Country_2
};
enum Control_Object // Xác định xem đối tượng do Máy tính hay người chơi điều khiển, từ đó xác định đối tượng thuộc Computer List hay Player List
{
	Gaia,
	Computer,
	Player
};
enum Countries_Name
{
	Gaia_Civil,
	Egyptian,
	Yamato
};
enum Types_of_Tech
{
	House_H, // Nhà BE
	Barracks_H,
	Granary_H,
	Storage_Pit_H,
	Dock_H,
	Archery_Range_H,
	Stable_H,
	Farm_H,
	Stone_Age,
	Tool_Age,
	Bronze_Age,
	Iron_Age
};
enum Epoch_Types
{
	Epoch_Stone_Age,
	Epoch_Tool_Age,
	Epoch_Bronze_Age
};
enum Mouse_State_Type
{
	Mouse_Normal, // Trạng thái chuột ở vị trí bình thường, tương đương con trỏ chuột thông thường
	Mouse_Work, // Trạng thái chuột khi trỏ tới bãi quả mọng, cây gỗ, hay sửa nhà , đào vàng, đá ,...
	Mouse_Attack // Trạng thái khi yêu cầu đối tượng tấn công, hình cây kiếm
};
enum Units_Type_Property
{
	Building,
	Base_Pierce,
	Base_Melee,
	Priests,
	Cavalry,
	Infantry,
	Stone_Defense,
	Villager_Base
};
typedef struct Tech_Details // Cấu trúc chi tiết cho một công nghệ
{
	SDL_Rect Icon_Iso_Pos; // Chính là icon thứ bao nhiêu trong sprite Texture
	SDL_Rect Icon_Pos_Sor; // Chính là button nào khi hiện lên màn hình
	int Cost_Food; // Lượng thực cần để nghiên cứu công nghệ này
	int Cost_Wood;
	int Cost_Stone;
	int Cost_Gold;
	int Time_Research; // Thời gian nghiên cứu công nghệ này
	vector<int> Required_Tech; // Những công nghệ cần thiết để nghiên cứu công nghệ này
	int Research_Location = -1; // Nơi mà có thể nghiên cứu được công nghệ này
	int Sub_Menu_Required; // Menu hiển thị công nghệ này, tức là phải ở Menu này thì ấn vào vị trí đó mới nghiên cứu được công nghệ đó
} Tech_Details;
typedef struct Tech_List
{
	Tech_Details Tech_Dt[100];
} Tech_List;
typedef struct Button_Details // Cấu trúc chi tiết cho một Button
{
	SDL_Rect Button_Iso_Pos; 
	SDL_Rect Button_Pos_Sor;
	int Sub_Menu_Required; // Menu cần có để hiển thị Button này ra
	int Choose_Object_Required; // Loại đối tượng yêu cầu được chọn để xuất hiện Button này 
};
typedef struct Button_List
{
	Button_Details Button_Dt[100]; // Mảng chứa các Button
};
typedef struct Country_Tech_Details
{
	Tech_List Country_Tech[10];
} Country_Tech_Details;
typedef struct Unit_Details_Texture
{
	SDL_Texture* Standing_Texture = NULL;
	int Number_Standing_Direction_Frame;
	int Standing_Frame_Weight;
	int Standing_Frame_Height;
	int Standing_Next_Frame;
	SDL_Rect Focus_Point_Standing;
	SDL_Texture* Working_Texture = NULL;
	int Number_Working_Direction_Frame;
	int Working_Frame_Weight;
	int Working_Frame_Height;
	int Working_Next_Frame;
	SDL_Rect Focus_Point_Working;
	SDL_Texture* Carry_Texture = NULL;
	int Number_Carry_Direction_Frame;
	int Carry_Frame_Weight;
	int Carry_Frame_Height;
	int Carry_Next_Frame;
	SDL_Rect Focus_Point_Carry;
	SDL_Texture* Moving_Texture = NULL;
	int Number_Moving_Direction_Frame;
	int Moving_Frame_Weight;
	int Moving_Frame_Height;
	int Moving_Next_Frame;
	SDL_Rect Focus_Point_Moving;
	SDL_Texture* Attacking_Texture = NULL;
	int Number_Attacking_Direction_Frame;
	int Attacking_Frame_Weight;
	int Attacking_Frame_Height;
	int Attacking_Next_Frame;
	SDL_Rect Focus_Point_Attacking;
	SDL_Texture* Death_Texture = NULL;
	int Number_Death_Direction_Frame;
	int Death_Frame_Weight;
	int Death_Frame_Height;
	int Death_Next_Frame;
	SDL_Rect Focus_Point_Death;
	SDL_Texture* Dead_Texture = NULL;
	int Number_Dead_Direction_Frame;
	int Dead_Frame_Weight;
	int Dead_Frame_Height;
	int Dead_Next_Frame;
	SDL_Rect Focus_Point_Dead;
} Unit_Details_Texture;
typedef struct Unit_Details
{
	SDL_Rect Icon_Iso_Pos;
	SDL_Rect Icon_Pos_Sor;
	string Unit_Type_Name;
	int Unit_Type_Property; // Tính chất của đơn vị đó
	double Size_Number_Cell; // Số ô mà đối tượng đó chiếm
	int Cost_Food; // Lượng thực cần để train đơn vị này
	int Cost_Wood;
	int Cost_Stone;
	int Cost_Gold;
	int Time_Train;
	int Train_Location = -1;
	int Sub_Menu_Required = -1;
	int Damage;
	int Armor;
	int Attack_Range;
	int Hit_Point;
	int Speed;
	int Weight;
	int Height;
	int Time_Next_Standing = 0;
	int Time_Next_Standing_Sprite = 0;
	int Time_Next_Carry = 0;
	int Time_Next_Carry_Sprite = 0;
	int Time_Next_Attacking = 0;
	int Time_Next_Attacking_Sprite = 0;
	int Time_Next_Working = 0;
	int Time_Next_Working_Sprite;
	int Time_Next_Moving = 0;
	int Time_Next_Moving_Sprite = 0;
	int Time_Next_Death = 0;
	int Time_Next_Death_Sprite = 0;
	int Time_Next_Dead = 0;
	int Time_Next_Dead_Sprite = 0;

} Unit_Details;
typedef struct Country_Unit_Details_Texture
{
	Unit_Details_Texture Unit_Dt_Texture[50];
} Country_Unit_Details_Texture;
typedef struct Cell
{
	int Parent_i, Parent_j;
	float f, g, h;
} Cell;
typedef struct Hit_Box
{
	int Row;
	int Col;
	int Damage;
	int Blast_Width = 0;
	int Blast_Attack_Type = -1;
} Hit_Box;
typedef struct Choose_Object // Đối tượng được chọn
{
	int Unit_Choose = -1;
	int Country = -1;
	int Position;
	int Unit_Type_Control = -1;
	int Pos_Control = -1;
	int Country_Name;
	int Unit_Property = -1;
} Choose_Object;
enum Sub_Menu_Type
{
	Construct_Villager, // Menu về xây dựng : Xây nhà, sửa nhà,...
	Page_1_Build_Construct, // Trang thứ nhất của Menu Build
	Page_2_Build_Construct 
};
enum Buttons_Type
{
	Build, // Nút để chọn cho nông dân Build nhà
	Stop_Research, // Nút dừng hoạt động đang nghiên cứu lại
	Stop_Train // Nút dừng Train đơn cị hiện tại
};
// Định nghĩa các thuộc tính cần thiết của Uniform Grid : Phần bên dưới
// Nhược điểm : Dung lượng bộ nhớ xẽ cần phải sử dụng để khởi tạo Grid này, tức là khi dung lượng Map càng lớn thì đồng nghĩa với việc dung lượng Game sẽ lớn lên nhiều
typedef struct Cell_Contain_Object // Các ô có chứa đối tượng Game này, nó sẽ tạo thành 1 vector để biết những ô nào có chứa đối tượng
{
	int Row, Col;
	int Pos = -1;
} Cell_Contain_Object;
typedef struct Cell_Object // Lưu trữ thông tin về đối tượng có trong Cell
{
	int Object_Type = -1; // Loại đối tượng, -1 là không có đối tượng gì, khi một đối tượng bị xóa khỏi ô, chỉ số này được gán bằng -1 thay vì xóa đi để không làm ảnh hướng tới index của các đối tượng khác trong Cell
	int Pos; // Index của nó trong List Object in Cell, tôi thích dùng từ Pos hơn là từ Index 
	int Country; // Quốc tịch của đối tượng :))
	int Unit_Type_Control;
	int Pos_Control;
	SDL_Rect Orth_Pos; // Tọa độ của đối tượng này, Rect này để xử lý va chạm
} Cell_Object;
typedef struct Cell_Uniform_Grid // Các ô trong Uniform Grid
{
	vector<Cell_Object> List_Object_in_Cell;
} Cell_Uniform_Grid;
enum Object_Direction // Các hướng của đối tượng game
{
	Direc_S, // Hướng Nam
	Direc_W_S, // Hướng Tây Nam
	Direc_W, // Hướng Tây
	Direc_W_N, // Hướng Tây Bắc
	Direc_N, // Hướng Bắc
	Direc_E_N, // Hướng Đông Bắc
	Direc_E, // Hướng Đông
	Direc_E_S // Hướng Đông Nam
};
enum Game_Object_Status
{
	Standing,
	Moving,
	Carry,
	Attacking,
	Working,
	Death,
	Dead,
	Disappear // Đối tượng không còn tồn tại trên bản đồ nữa ( Xác cũng đã biến mất rồi )
};
void Move_x_to_y();
bool Check_Cell(int Row, int Col);
void Clear_Stack(stack<Pair>& S_Stack);
bool Check_UnBlock(Game_Object* Game_Object_Check, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], int Row, int Col, int Parent_Row, int Parent_Col); // Kiểm tra xem ô này có vật cản hay không
bool Check_Des(int Row, int Col, Pair& Dest); // Kiểm tra xem ô này có phải đích đến hay không
double Cal_H_Value(int Row, int Col, Pair& Dest);
double Cal_Distance(SDL_Rect X1, SDL_Rect X2);
void Convert(SDL_Rect& Iso_Des, SDL_Rect& Orth_Des, int z); // Chuyển đổi từ hệ tọa độ Orth sang hệ tọa độ Iso
void Reverse_Convert(int& Iso_Des_x, int& Iso_Des_y, int Weight, int Height); // Hàm chuyển đổi ngược
void Traced(Pair& Dest, stack<Pair>& Path, Cell Cell_Details[Number_Row_Map][Number_Col_Map]); // Truy dấu đường đi, từ điểm cuối sẽ push vào Stack các ô để dẫn tới điêm xuất phát
void A_Star_Search(Game_Object*Game_Object_need_Search_Path, Cell_Uniform_Grid Map_1[Number_Row_Map][Number_Col_Map], Cell_Uniform_Grid Map_2[Number_Row_Map][Number_Col_Map], SDL_Rect& Orth_Pos_Des, SDL_Rect& Orth_Pos_Move, stack<Pair>& Path, bool& Search_A);
//void Move_Cell_x_to_Cell_y(Unit_Details Unit_Dt[200], int Unit_Type, int Country, SDL_Rect& X, SDL_Rect& X_Iso, SDL_Rect& X_Sor, stack<Pair>& Path, bool& Moving_X_to_Y, int& Direc, int Current_Time, int Last_Time);
// ( Hàm di chuyển từ ô này sang ô kia)
//void Load_Sprite_Sheet(int Unit_Type, SDL_Rect& Orth_Pos, SDL_Rect& Pos_Sor, SDL_Rect& Orth_Pos_Work, int Direction,
	//bool Work, bool Moving, int Frame_Weight, int Frame_Height, int Number_Frame_Direc, int Time_Next_Sprite, int Last_Time, int Current_Time);
void Convert_Object(Game_Object* Game_Object_Convert, SDL_Rect& Iso_Des, SDL_Rect& Orth_Des, int Weight, int Height);
// hàm này sẽ chuyển đổi để đưa chính xác đối tượng về vị trí cân đối trên Map, cân đối so với Tile Ground
int Check_A_Behind_B(int Orth_A_x, int Orth_A_y, int Orth_A_z, int Orth_B_x, int Orth_B_y, int Orth_B_z,
	int A_Weight, int A_Height, int B_Weight, int B_Height, double Size_Number_Cell_A, double Size_Number_Cell_B);
void Load_Image_1(int Unit_Type, SDL_Rect& Pos_Sor, SDL_Rect& Orth_Pos, SDL_Rect& Iso_Pos); // Load hình ảnh từ Texture và tọa độ, copy tới Renderer để chuẩn bị vẽ
bool Check_Cell_Empty(Game_Object* Game_Object_Check, int Row, int Col, Cell_Uniform_Grid Map_UG_Layer[Number_Row_Map][Number_Col_Map]); // Kiểm tra xem ô này có rỗng không
bool Check_Cell_Empty_include_Object(int Row, int Col, Cell_Uniform_Grid Map_UG_Layer[Number_Row_Map][Number_Col_Map]);
// void Push_Object_to_Cell(Cell_Uniform_Grid Map_UG_Layer_1[Number_Row_Map][Number_Col_Map], Game_Object* Game_Object_Push, int Pos, int Object_Type, int Row, int Col);
void Load_and_Get_infor_image(Country_Unit_Details_Texture Unit_Dt_Texture[50], int Country_Index, int Unit_Type, const char* Unit_Standing_file_name, int Number_Frame_Standing, int Next_Frame_Standing, int Focus_Point_Standing_x, int Focus_Point_Standing_y,
	const char* Unit_Moving_file_name, int Number_Frame_Moving, int Next_Frame_Moving, int Focus_Point_Moving_x, int Focus_Point_Moving_y,
	const char* Unit_Carry_file_name, int Number_Frame_Carry, int Next_Frame_Carry, int Focus_Point_Carry_x, int Focus_Point_Carry_y,
	const char* Unit_Working_file_name, int Number_Frame_Working, int Next_Frame_Working, int Focus_Point_Working_x, int Focus_Point_Working_y,
	const char* Unit_Attacking_file_name, int Number_Frame_Attacking, int Next_Frame_Attacking, int Focus_Point_Attacking_x, int Focus_Point_Attacking_y,
	const char* Unit_Death_file_name, int Number_Frame_Death, int Next_Frame_Death, int Focus_Point_Death_x, int Focus_Point_Death_y,
	const char* Unit_Dead_file_name, int Number_Frame_Dead, int Next_Frame_Dead, int Focus_Point_Dead_x, int Focus_Point_Dead_y);
Uint32 get_pixel32(SDL_Surface* surface, int x, int y);
// Push thêm một đối tượng vào Cell
#endif // !COMMON_FUNCTION_H_INCLUDED

