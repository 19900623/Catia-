#pragma once;
#include "ivconverterhead.h"
#include <afxtempl.h>

class BStreamFileToolkit;
class BBaseOpcodeHandler;
#define IvConv_API //__declspec(dllexport)

#define  INVALID_KEY         -1

//װ���ļ��е����ͣ�
#define IVA_PART         1
#define IVA_ASM          0
#define IVA_CONSTRAINT   2
#define IVA_EXPLOSION    3 //��ը�ڵ�



//��������
#define  IV_GE_POINT       0x00000001
#define  IV_GE_LINE        0x00000002
#define  IV_GE_ARC         0x00000004
#define  IV_GE_PLANE       0x00000008
#define  IV_GE_SPHERE      0x00000010
#define  IV_GE_CYLINDER    0x00000020
#define  IV_GE_CONE        0x00000040   //Բ׶
#define  IV_GE_TORUS       0x00000080   //Բ��
#define  IV_GE_FILLET	   0x00000100   //����


//װ��Լ������
#define CONSTRAINT_MATE    0x00000001    //��ϣ�  ��Ԫ��1��Ԫ��2 ��
#define CONSTRAINT_ANGLE   0x00000002    //�н���� ���򣺷Ƕ��� 
#define CONSTRAINT_TANGENT 0x00000004    //�������
#define CONSTRAINT_INSERT  0x00000008    //�������  : inventor ר��

//������ͼ�¼��ʽ���壺
/*
����ϣ�������T����F����ƫ�ƾ��룩��Ԫ��1���ͣ���Ԫ��1��ʶ����Ԫ��1·������Ԫ��2���ͣ���Ԫ��2��ʶ����Ԫ��2·����
���нǣ�������T��Ƕ���F�����нǣ���Ԫ��1���ͣ���Ԫ��1��ʶ����Ԫ��1·������Ԫ��2���ͣ���Ԫ��2��ʶ����Ԫ��2·����
�����У�������T������F����ƫ�ƾ��룩��Ԫ��1���ͣ���Ԫ��1��ʶ����Ԫ��1·������Ԫ��2���ͣ���Ԫ��2��ʶ����Ԫ��2·����
��������ϣ���ͬ��T����F����ƫ�ƾ��룩��Ԫ��1���ͣ���Ԫ��1��ʶ����Ԫ��1·������Ԫ��2���ͣ���Ԫ��2��ʶ����Ԫ��2·����
*/

#ifndef WRITEBUFFER
#define WRITEBUFFER(buffer, data, size) memcpy(buffer, data, size); buffer += size
#endif



//��ʼ��
void IVCONVERTER_EXPORTS API_InitConverter(char *filename);
//ת������
void IVCONVERTER_EXPORTS API_TerminateConverter();

//��ע����ж��Ƿ�����CAD���save��saveas����Ա���ΪInteVue�ļ�
//strName: ע�������
//UGToInteVue, PROEToInteVue, SEToInteVue, SldToInteVue, InvtToInteVue
//�������TRUE���������FALSE
BOOL IVCONVERTER_EXPORTS API_GetSaveSetting(const char* strName);

//�½�segment��name��segment name
void IVCONVERTER_EXPORTS API_OpenSegment( char *name = NULL);
//�ر�segment
void IVCONVERTER_EXPORTS API_CloseSegment();

//rgb: �����ɫ
//p_count: ��ĸ���; points: �������; normals: ��ķ�ʸ
//flist_length: face_list����;
//face_list: ������, ��������0��ʼ��������˳������: �������, ��һ������, �ڶ�������, ����������, ...��: 3 0 1 2 3 1 2 3 . . . 
//box: ���Χ��, size: �Զ������ݳ���, userdata: �û��Զ�������
void IVCONVERTER_EXPORTS API_WriteShell(int p_count, float *points, float *normals, int flist_length,
						   int *face_list, float *box, int size, char *userdata, double *rgb = NULL);

void IVCONVERTER_EXPORTS API_WriteShellWithHandle(int p_count, float *points, float *normals, int flist_length,
										int *face_list, float *box, int size, char *userdata, double *rgb = NULL,const char *cHandle=NULL);

void IVCONVERTER_EXPORTS API_WriteShellWithUserOption(int p_count, float *points, float *normals, int flist_length,
	int *face_list, float *box, int size, char *userdata, double *rgb = NULL,const char *userOptions=NULL);

void IVCONVERTER_EXPORTS API_WritePolyLine(int p_count, float *points, int size, char *userdata, double *rgb = NULL);
void IVCONVERTER_EXPORTS API_WritePoint(float const *p, int size, char *userdata);
void IVCONVERTER_EXPORTS API_WritePoint(float x, float y, float z, int size, char *userdata);


//ע�����º�������֮��buffer��������ڴ���Ҫ����API_FreeBuffer()�ͷţ��������ڴ�й©
void IVCONVERTER_EXPORTS API_WritePlaneToBuffer(double *root, double *normal, int &size, char *&buffer);
void IVCONVERTER_EXPORTS API_WriteCylinderToBuffer(double *root, double *dir, double radius, int &size, char *&buffer);
void IVCONVERTER_EXPORTS API_WriteLineToBuffer(double *root, double *dir, int &size, char *&buffer);
void IVCONVERTER_EXPORTS API_WriteArcToBuffer(double *center, double *normal, double radius, int &size, char *&buffer);
void IVCONVERTER_EXPORTS API_WritePointToBuffer(double *coord, int &size, char *&buffer);
void IVCONVERTER_EXPORTS API_FreeBuffer(char *&buffer);


//װ���ļ�ת��
//void IvConv_API	API_InitConverterAsm();				//װ���ļ�ת����ʼ��
//void IvConv_API API_WriteVersion(FILE* fp);
//BOOL IvConv_API API_WriteNode(FILE* fp, int type, const char* name, const char* filename, 
//			 int childCount, double *rotate, double *trans,double *rgb = NULL);
//void IvConv_API API_TerminateConverterAsm();		//װ���ļ�ת������

static void  WriteObject(BBaseOpcodeHandler * handler, BStreamFileToolkit * tk, FILE * fp,
                        char * buffer, int size);


//BOOL IvConv_API ListBSearch( int start, int end, CList<LONG, LONG> *VertexList, LONG elem, int *index);
CString IVCONVERTER_EXPORTS GetInputPath();

//�������ǻ�����
void IVCONVERTER_EXPORTS API_SetTesselationPrec(const char* strName);

//�õ����ǻ�����
int IVCONVERTER_EXPORTS API_GetTesselationPrec(const char* strName);


//��Լ��д��buffer,ע��buffer ��Ҫ����API_FreeBuffer�����ͷ��ڴ�
//�ú���֧����ϡ����С��Ƕȡ�������������
void IVCONVERTER_EXPORTS API_WriteConstraintToBuffer(long lType,BOOL bFlage,double dValue,long lE1Type,long lE1ID,char *cE1Path,
											long lE2Type,long lE2ID,char *cE2Path,int &size, char *&buffer);


//�ɼ���
void IVCONVERTER_EXPORTS API_SetVisibility(BOOL vis);
//����
void IVCONVERTER_EXPORTS API_SetLineFont(int font);
//�߿�
void IVCONVERTER_EXPORTS API_SetLineWeight(float weight);
//��ɫ
void IVCONVERTER_EXPORTS API_SetColor(float r, float g, float b);

//д������
//version���汾��type�����ͣ�title����������value������ֵ
//�ú���������ʹ��
void IVCONVERTER_EXPORTS API_WriteAttribute(int version, int type, CStringList &title, CStringList &value,
								   CStringList &InteVueDataTitle, CStringList &InteVueData);
//��XML�ļ���ʽ����¼�û��Զ����һЩ��Ϣ
void IVCONVERTER_EXPORTS API_WriteInfo(const char *cBuffer,int iLength);

void IVCONVERTER_EXPORTS API_SetUserOptions(const char *name);
//���һ����
void IVCONVERTER_EXPORTS API_WriteLine(float dStart_x,float dStart_y,float dStart_z,
									   float dEnd_x,float dEnd_y,float dEnd_z);
//���һ���ı�
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
//���Ͷ���μ�hoops�� enum TKO_Geometry_Bits�еĶ���
void IVCONVERTER_EXPORTS API_SetColor(int iType,float r, float g, float b);

void IVCONVERTER_EXPORTS API_LineType(int iLineType);
//�������ֵ�����
void IVCONVERTER_EXPORTS API_SetTextFont(char *fontName);
//���������Ƿ�任
void IVCONVERTER_EXPORTS API_SetTextTransform(int iTransform=1);
//�������ֵĴ�С
//TKO_Font_Size_Object = 0,  //!< object space
//TKO_Font_Size_Screen = 1,  //!< screen space
//TKO_Font_Size_Window = 2,  //!< window space
//TKO_Font_Size_Points = 3,  //!< points 
//TKO_Font_Size_Pixels = 4,  //!< pixels 
//TKO_Font_Size_Percent = 5  //!< used by tolerance

void IVCONVERTER_EXPORTS API_SetTextSize(float size,int iUnit);

//�������ֶ��뷽ʽ
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

// �����ı���д����
// void IVCONVERTER_EXPORTS API_SetTextPath(float x, float y, float z);
// �����ı�����ת�Ƕ�
// void IVCONVERTER_EXPORTS API_SetTextRotation(float r);

void IVCONVERTER_EXPORTS API_WriteConeToBuffer(double *coord,double *dDiretion,double dAngle,int &size,char *&buffer);

void IVCONVERTER_EXPORTS API_WriteSphereToBuffer(double *coord,double dRadius,int &size,char *&buffer);

void IVCONVERTER_EXPORTS API_WriteTorusToBuffer(double *coord,double *normal,double dRadius1,double dRadius2,int &size,char *&buffer);

void IVCONVERTER_EXPORTS API_SetVisiblityByValue(int iType,int iValue);

void IVCONVERTER_EXPORTS API_SetUnicodeUserOptions(const char *name);
//����һ����
void IVCONVERTER_EXPORTS API_WriteSphere(float *center,float dRadius);

//д���ε��û��Ӷ�������
void IVCONVERTER_EXPORTS API_WriteGeometryHandle(const char *cHandle);
//дԲ��
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

//д��һ�����ε�useroption
void IVCONVERTER_EXPORTS API_WriteGeometryOption(const char *cName);

void IVCONVERTER_EXPORTS API_WriteGeometryUnicodeOption(const char *cName);