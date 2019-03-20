#pragma once
//����Intevue�����ļ��ı��湤��
//Intevue��iva�ļ�����Ϊѹ����xml�ļ���ʽ��
//CIvFile���ڽ�xmlѹ�������浽�ļ�����ȡxml�ļ����������ڴ��ж�ȡ�ļ�
class  CIvFile
{
public:
	CIvFile(void);
	~CIvFile(void);


public: //static

	static CComPtr<IXMLDOMDocument> CreateXmlDoc();

	//static long SaveXMLZipFile(const char *cFileName,const char *cXmlFile,long lFileSize);
	//����xml�ļ���ѹ���ļ���
	//cFileName,ѹ������ļ�����
	//pDoc,XmlDocle����
	//static BOOL SaveXMLDocToZipFile(const char *cFileName,CComPtr<IXMLDOMDocument> pDoc); 
	//���ַ���д�뵽ѹ���ļ���ʽ��
	//static BOOL WriteStringToZipFile(const char *cFileName,BSTR bstrString);
	//��ȡ�ļ�,��ȡ�ļ��������ڴ棬Ȼ����Ҫͨ��FreeMemory�ͷ��ڴ�

	//static long LoadFile(const char *cFileName,char *&cXmlFile,long lFileSize);
	//�ͷ��ڴ�
	//static void FreeMemory(void * pPoint);
	//��CFile�ļ��ж�ȡ��Ϣ��Ȼ���ѹ������ѹ֮����ļ������ڴ��ļ��У�
	//static long UnzipFileFromCFile(CFile *hInputFile,CMemFile &hMemFile);
	//���ڴ��ļ��д���XMLDoc����
	static CComPtr<IXMLDOMDocument> LoadXmlDocFromMemFile(CMemFile &hMemFile);
	//��CFile�ж�ȡXml�ļ���hInputDoc ������CFile��Ҳ������CMemFile

	static CComPtr<IXMLDOMDocument> LoadXmlDocFromCFile(CFile *hInputDoc);

	//�ж��ļ��Ƿ�Ϊ�µ��ļ���ʽ
	static BOOL IsNewAsmFile(CString strFileName); 

	//��ȡXML�ļ�����xmldoc��
	static CComPtr<IXMLDOMDocument> LoadXMLFile(const char *cFileName);
	//���ַ����ж�ȡxml�ļ���Ϣ��
	static CComPtr<IXMLDOMDocument> LoadXMLFileFromString(const char *cXmlFile);
	//��xml�ļ�������һ���ڵ�	
	static CComPtr<IXMLDOMElement> XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName);
	static CComPtr<IXMLDOMElement> XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,CString strText);
	static CComPtr<IXMLDOMElement> XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,double dText);
	static CComPtr<IXMLDOMElement> XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,float dText);
	static CComPtr<IXMLDOMElement> XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,int dText);
	static CComPtr<IXMLDOMElement> XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,long dText);

	//���ýڵ������ֵ
	static void XmlSetAttribute(CComPtr<IXMLDOMElement> pElement,CString strName,CString strValue);
	static CComPtr<IXMLDOMElement> XmlGetFirstChild(CComPtr<IXMLDOMElement> pElement);
	static CComPtr<IXMLDOMElement> XmlGetFirstChild(CComPtr<IXMLDOMDocument> pElement);
	static CComPtr<IXMLDOMElement> XmlGetNextNode(CComPtr<IXMLDOMElement> pElement);
	static CString XmlGetElementName(CComPtr<IXMLDOMElement> pElement);
	static CString XmlGetElementText(CComPtr<IXMLDOMElement> pElement);
	static CString XmlGetElementAttribute(CComPtr<IXMLDOMElement> pElement,CString strName);
	//�Ƚ������ļ��������ļ������·��
	static CString GetRelatePath(CString strFrom,CString strTo);
	//�������·���õ��ļ���������·��
	static CString GetPathByRelate(CString strFileName,CString strRelation);
};
