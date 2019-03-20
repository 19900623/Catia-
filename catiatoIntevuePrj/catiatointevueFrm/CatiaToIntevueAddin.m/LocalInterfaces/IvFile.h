#pragma once
//用于Intevue所有文件的保存工作
//Intevue中iva文件保存为压缩的xml文件格式；
//CIvFile用于将xml压缩，保存到文件，读取xml文件，包括从内存中读取文件
class  CIvFile
{
public:
	CIvFile(void);
	~CIvFile(void);


public: //static

	static CComPtr<IXMLDOMDocument> CreateXmlDoc();

	//static long SaveXMLZipFile(const char *cFileName,const char *cXmlFile,long lFileSize);
	//保存xml文件到压缩文件中
	//cFileName,压缩后的文件名；
	//pDoc,XmlDocle数据
	//static BOOL SaveXMLDocToZipFile(const char *cFileName,CComPtr<IXMLDOMDocument> pDoc); 
	//将字符串写入到压缩文件格式中
	//static BOOL WriteStringToZipFile(const char *cFileName,BSTR bstrString);
	//读取文件,读取文件将分配内存，然后需要通过FreeMemory释放内存

	//static long LoadFile(const char *cFileName,char *&cXmlFile,long lFileSize);
	//释放内存
	//static void FreeMemory(void * pPoint);
	//从CFile文件中读取信息，然后解压，将解压之后的文件放在内存文件中；
	//static long UnzipFileFromCFile(CFile *hInputFile,CMemFile &hMemFile);
	//从内存文件中创建XMLDoc对象
	static CComPtr<IXMLDOMDocument> LoadXmlDocFromMemFile(CMemFile &hMemFile);
	//从CFile中读取Xml文件；hInputDoc 可以是CFile，也可以是CMemFile

	static CComPtr<IXMLDOMDocument> LoadXmlDocFromCFile(CFile *hInputDoc);

	//判断文件是否为新的文件格式
	static BOOL IsNewAsmFile(CString strFileName); 

	//读取XML文件返回xmldoc；
	static CComPtr<IXMLDOMDocument> LoadXMLFile(const char *cFileName);
	//从字符串中读取xml文件信息；
	static CComPtr<IXMLDOMDocument> LoadXMLFileFromString(const char *cXmlFile);
	//在xml文件中增加一个节点	
	static CComPtr<IXMLDOMElement> XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName);
	static CComPtr<IXMLDOMElement> XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,CString strText);
	static CComPtr<IXMLDOMElement> XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,double dText);
	static CComPtr<IXMLDOMElement> XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,float dText);
	static CComPtr<IXMLDOMElement> XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,int dText);
	static CComPtr<IXMLDOMElement> XmlAddChild(CComPtr<IXMLDOMDocument> pDoc,CComPtr<IXMLDOMElement> pParent,CString strChildName,long dText);

	//设置节点的属性值
	static void XmlSetAttribute(CComPtr<IXMLDOMElement> pElement,CString strName,CString strValue);
	static CComPtr<IXMLDOMElement> XmlGetFirstChild(CComPtr<IXMLDOMElement> pElement);
	static CComPtr<IXMLDOMElement> XmlGetFirstChild(CComPtr<IXMLDOMDocument> pElement);
	static CComPtr<IXMLDOMElement> XmlGetNextNode(CComPtr<IXMLDOMElement> pElement);
	static CString XmlGetElementName(CComPtr<IXMLDOMElement> pElement);
	static CString XmlGetElementText(CComPtr<IXMLDOMElement> pElement);
	static CString XmlGetElementAttribute(CComPtr<IXMLDOMElement> pElement,CString strName);
	//比较两个文件，返回文件的相对路径
	static CString GetRelatePath(CString strFrom,CString strTo);
	//根据相对路径得到文件的完整的路径
	static CString GetPathByRelate(CString strFileName,CString strRelation);
};
