#pragma once;
#include "ivconverterhead.h"
#include <afxtempl.h>

class BStreamFileToolkit;
class BBaseOpcodeHandler;
#define IvConv_API //__declspec(dllexport)

#define  INVALID_KEY         -1

//装配文件中的类型：
#define IVA_PART         1
#define IVA_ASM          0
#define IVA_CONSTRAINT   2
#define IVA_EXPLOSION    3 //爆炸节点



//几何类型
#define  IV_GE_POINT       0x00000001
#define  IV_GE_LINE        0x00000002
#define  IV_GE_ARC         0x00000004
#define  IV_GE_PLANE       0x00000008
#define  IV_GE_SPHERE      0x00000010
#define  IV_GE_CYLINDER    0x00000020
#define  IV_GE_CONE        0x00000040   //圆锥
#define  IV_GE_TORUS       0x00000080   //圆环
#define  IV_GE_FILLET	   0x00000100   //倒角


//装配约束类型
#define CONSTRAINT_MATE    0x00000001    //配合：  ：元素1，元素2 ，
#define CONSTRAINT_ANGLE   0x00000002    //夹角配合 定向：非定向 
#define CONSTRAINT_TANGENT 0x00000004    //相切配合
#define CONSTRAINT_INSERT  0x00000008    //插入配合  : inventor 专用

//配合类型记录格式定义：
/*
（配合）（正向T或反向F）（偏移距离）（元素1类型）（元素1标识）（元素1路径）（元素2类型）（元素2标识）（元素2路径）
（夹角）（定向T或非定向F）（夹角）（元素1类型）（元素1标识）（元素1路径）（元素2类型）（元素2标识）（元素2路径）
（相切）（内切T或外切F）（偏移距离）（元素1类型）（元素1标识）（元素1路径）（元素2类型）（元素2标识）（元素2路径）
（插入配合）（同向T或反向F）（偏移距离）（元素1类型）（元素1标识）（元素1路径）（元素2类型）（元素2标识）（元素2路径）
*/

#ifndef WRITEBUFFER
#define WRITEBUFFER(buffer, data, size) memcpy(buffer, data, size); buffer += size
#endif



//初始化
void IVCONVERTER_EXPORTS API_InitConverter(char *filename);
//转换结束
void IVCONVERTER_EXPORTS API_TerminateConverter();

//读注册表，判断是否重载CAD软件save，saveas命令，以保存为InteVue文件
//strName: 注册表名称
//UGToInteVue, PROEToInteVue, SEToInteVue, SldToInteVue, InvtToInteVue
//重载输出TRUE，否则输出FALSE
BOOL IVCONVERTER_EXPORTS API_GetSaveSetting(const char* strName);

//新建segment，name：segment name
void IVCONVERTER_EXPORTS API_OpenSegment( char *name = NULL);
//关闭segment
void IVCONVERTER_EXPORTS API_CloseSegment();

//rgb: 面的颜色
//p_count: 点的个数; points: 点的坐标; normals: 点的法矢
//flist_length: face_list长度;
//face_list: 面链表, 点索引从0开始，按如下顺序排列: 顶点个数, 第一点索引, 第二点索引, 第三点索引, ...如: 3 0 1 2 3 1 2 3 . . . 
//box: 面包围盒, size: 自定义数据长度, userdata: 用户自定义数据
void IVCONVERTER_EXPORTS API_WriteShell(int p_count, float *points, float *normals, int flist_length,
						   int *face_list, float *box, int size, char *userdata, double *rgb = NULL);

void IVCONVERTER_EXPORTS API_WriteShellWithHandle(int p_count, float *points, float *normals, int flist_length,
										int *face_list, float *box, int size, char *userdata, double *rgb = NULL,const char *cHandle=NULL);

void IVCONVERTER_EXPORTS API_WriteShellWithUserOption(int p_count, float *points, float *normals, int flist_length,
	int *face_list, float *box, int size, char *userdata, double *rgb = NULL,const char *userOptions=NULL);

void IVCONVERTER_EXPORTS API_WritePolyLine(int p_count, float *points, int size, char *userdata, double *rgb = NULL);
void IVCONVERTER_EXPORTS API_WritePoint(float const *p, int size, char *userdata);
void IVCONVERTER_EXPORTS API_WritePoint(float x, float y, float z, int size, char *userdata);


//注意以下函数调用之后buffer所申请的内存需要利用API_FreeBuffer()释放，否则将有内存泄漏
void IVCONVERTER_EXPORTS API_WritePlaneToBuffer(double *root, double *normal, int &size, char *&buffer);
void IVCONVERTER_EXPORTS API_WriteCylinderToBuffer(double *root, double *dir, double radius, int &size, char *&buffer);
void IVCONVERTER_EXPORTS API_WriteLineToBuffer(double *root, double *dir, int &size, char *&buffer);
void IVCONVERTER_EXPORTS API_WriteArcToBuffer(double *center, double *normal, double radius, int &size, char *&buffer);
void IVCONVERTER_EXPORTS API_WritePointToBuffer(double *coord, int &size, char *&buffer);
void IVCONVERTER_EXPORTS API_FreeBuffer(char *&buffer);


//装配文件转换
//void IvConv_API	API_InitConverterAsm();				//装配文件转换初始化
//void IvConv_API API_WriteVersion(FILE* fp);
//BOOL IvConv_API API_WriteNode(FILE* fp, int type, const char* name, const char* filename, 
//			 int childCount, double *rotate, double *trans,double *rgb = NULL);
//void IvConv_API API_TerminateConverterAsm();		//装配文件转换结束

static void  WriteObject(BBaseOpcodeHandler * handler, BStreamFileToolkit * tk, FILE * fp,
                        char * buffer, int size);


//BOOL IvConv_API ListBSearch( int start, int end, CList<LONG, LONG> *VertexList, LONG elem, int *index);
CString IVCONVERTER_EXPORTS GetInputPath();

//设置三角化精度
void IVCONVERTER_EXPORTS API_SetTesselationPrec(const char* strName);

//得到三角化精度
int IVCONVERTER_EXPORTS API_GetTesselationPrec(const char* strName);


//将约束写入buffer,注意buffer 需要利用API_FreeBuffer函数释放内存
//该函数支持配合、相切、角度、插入四种类型
void IVCONVERTER_EXPORTS API_WriteConstraintToBuffer(long lType,BOOL bFlage,double dValue,long lE1Type,long lE1ID,char *cE1Path,
											long lE2Type,long lE2ID,char *cE2Path,int &size, char *&buffer);


//可见性
void IVCONVERTER_EXPORTS API_SetVisibility(BOOL vis);
//线形
void IVCONVERTER_EXPORTS API_SetLineFont(int font);
//线宽
void IVCONVERTER_EXPORTS API_SetLineWeight(float weight);
//颜色
void IVCONVERTER_EXPORTS API_SetColor(float r, float g, float b);

//写入属性
//version：版本；type：类型；title：属性名；value：属性值
//该函数将不再使用
void IVCONVERTER_EXPORTS API_WriteAttribute(int version, int type, CStringList &title, CStringList &value,
								   CStringList &InteVueDataTitle, CStringList &InteVueData);
//用XML文件格式来记录用户自定义的一些信息
void IVCONVERTER_EXPORTS API_WriteInfo(const char *cBuffer,int iLength);

void IVCONVERTER_EXPORTS API_SetUserOptions(const char *name);
//添加一条线
void IVCONVERTER_EXPORTS API_WriteLine(float dStart_x,float dStart_y,float dStart_z,
									   float dEnd_x,float dEnd_y,float dEnd_z);
//添加一个文本
void IVCONVERTER_EXPORTS API_WriteText(float dPoint_x,float dPoint_y,float dPoint_z,const char *cText);

void IVCONVERTER_EXPORTS API_SetMatrix(float *dMatrix);
void IVCONVERTER_EXPORTS API_SetMatrix(double *dMatrix);
void IVCONVERTER_EXPORTS API_SetLineStyle(char *style);

void IVCONVERTER_EXPORTS API_WriteMarker(float x,float y,float z);

void IVCONVERTER_EXPORTS API_WriteArc(float start_x,float start_y,float start_z,
									  float mid_x,float mid_y,float mid_z,
									  float end_x,float end_y,float end_z);

void IVCONVERTER_EXPORTS API_WriteCircle(float start_x,float start_y,float start_z,
									  float mid_x,float mid_y,float mid_z,
									  float end_x,float end_y,float end_z);

void IVCONVERTER_EXPORTS API_WriteEllipse(float center_x,float center_y,float center_z,
										 float Major_x,float Major_y,float Major_z,
										 float Minor_x,float Minor_y,float Minor_z);

void IVCONVERTER_EXPORTS API_WriteEllipseArc(float center_x,float center_y,float center_z,
										  float Major_x,float Major_y,float Major_z,
										  float Minor_x,float Minor_y,float Minor_z,
										  float start_angle,float end_angle);

void IVCONVERTER_EXPORTS API_WritePloyLine(int iPointCount,float *pPoint);
void IVCONVERTER_EXPORTS API_WritePloyLine(int iPointCount,double *pPoint);

void IVCONVERTER_EXPORTS API_WritePloygon(int iPointCount,float *pPoint);
void IVCONVERTER_EXPORTS API_WritePloygon(int iPointCount,double *pPoint);

void IVCONVERTER_EXPORTS API_WriteNurbs(int degree, int control_count, const float *points, const float *weights, const float *knots, float start, float end);

void IVCONVERTER_EXPORTS API_WriteShell(int p_count, float *points, float *normals, int flist_length,
					int *face_list);
//类型定义参见hoops中 enum TKO_Geometry_Bits中的定义
void IVCONVERTER_EXPORTS API_SetColor(int iType,float r, float g, float b);

void IVCONVERTER_EXPORTS API_LineType(int iLineType);
//设置文字的字体
void IVCONVERTER_EXPORTS API_SetTextFont(char *fontName);
//设置文字是否变换
void IVCONVERTER_EXPORTS API_SetTextTransform(int iTransform=1);
//设置文字的大小
//TKO_Font_Size_Object = 0,  //!< object space
//TKO_Font_Size_Screen = 1,  //!< screen space
//TKO_Font_Size_Window = 2,  //!< window space
//TKO_Font_Size_Points = 3,  //!< points 
//TKO_Font_Size_Pixels = 4,  //!< pixels 
//TKO_Font_Size_Percent = 5  //!< used by tolerance

void IVCONVERTER_EXPORTS API_SetTextSize(float size,int iUnit);

//设置文字对齐方式
//TKO_Text_Alignment_Lower_Left       = 0,  //!< refer to ::HC_Set_Text_Alignment
// TKO_Text_Alignment_Upper_Left       = 1,  //!< refer to ::HC_Set_Text_Alignment
// TKO_Text_Alignment_Middle_Left      = 2,  //!< refer to ::HC_Set_Text_Alignment
// TKO_Text_Alignment_Lower_Right      = 3,  //!< refer to ::HC_Set_Text_Alignment
// TKO_Text_Alignment_Upper_Right      = 4,  //!< refer to ::HC_Set_Text_Alignment
// TKO_Text_Alignment_Middle_Right     = 5,  //!< refer to ::HC_Set_Text_Alignment
// TKO_Text_Alignment_Lower_Center     = 6,  //!< refer to ::HC_Set_Text_Alignment
// TKO_Text_Alignment_Upper_Center     = 7,  //!< refer to ::HC_Set_Text_Alignment
// TKO_Text_Alignment_Middle_Center    = 8,  //!< refer to ::HC_Set_Text_Alignment
// TKO_Text_Alignment_Insertion_Left   = 9,  //!< refer to ::HC_Set_Text_Alignment
// TKO_Text_Alignment_Insertion_Right  = 10, //!< refer to ::HC_Set_Text_Alignment
// TKO_Text_Alignment_Insertion_Center = 11, //!< refer to ::HC_Set_Text_Alignment
// TKO_Text_Alignment_Insertion        = 9,  //!< refer to ::HC_Set_Text_Alignment

void IVCONVERTER_EXPORTS API_SetTextAlignment(int index=0);

void IVCONVERTER_EXPORTS API_WritePolyCylinder(float dRadius,int iCount,float *pPoint,float *dStartNormal,float *dEndNormal);
void IVCONVERTER_EXPORTS API_WritePolyCylinder_v1(float dRadius,int iCount,float *pPoint,float *dStartNormal,float *dEndNormal,int iType);

// 设置文本书写方向
// void IVCONVERTER_EXPORTS API_SetTextPath(float x, float y, float z);
// 设置文本的旋转角度
// void IVCONVERTER_EXPORTS API_SetTextRotation(float r);

void IVCONVERTER_EXPORTS API_WriteConeToBuffer(double *coord,double *dDiretion,double dAngle,int &size,char *&buffer);

void IVCONVERTER_EXPORTS API_WriteSphereToBuffer(double *coord,double dRadius,int &size,char *&buffer);

void IVCONVERTER_EXPORTS API_WriteTorusToBuffer(double *coord,double *normal,double dRadius1,double dRadius2,int &size,char *&buffer);

void IVCONVERTER_EXPORTS API_SetVisiblityByValue(int iType,int iValue);

void IVCONVERTER_EXPORTS API_SetUnicodeUserOptions(const char *name);
//绘制一个球
void IVCONVERTER_EXPORTS API_WriteSphere(float *center,float dRadius);

//写几何的用户子定义属性
void IVCONVERTER_EXPORTS API_WriteGeometryHandle(const char *cHandle);
//写圆柱
//iType:			
//TKCYL_NONE   = 0,  //!< no caps
//TKCYL_FIRST  = 1,  //!< cap 'first' side
//TKCYL_SECOND = 2,  //!< cap 'second' side 
//TKCYL_BOTH   = 3   //!< cap both sides
void IVCONVERTER_EXPORTS API_WriteCylinder(float dRadius,float *pStart,float *dEnd,int iType);

void IVCONVERTER_EXPORTS API_WriteVariantPolyCylinder(int iRCount,float *dRadius,int iCount,float *pPoint,float *dStartNormal,float *dEndNormal,int iType);

void IVCONVERTER_EXPORTS API_WriteShellWithFaceNormal(int p_count, float *points, float *normals, int flist_length,
										int *face_list);

void IVCONVERTER_EXPORTS API_WriteRvmObjectName(const char *cName);

//写入一个几何的useroption
void IVCONVERTER_EXPORTS API_WriteGeometryOption(const char *cName);

void IVCONVERTER_EXPORTS API_WriteGeometryUnicodeOption(const char *cName);