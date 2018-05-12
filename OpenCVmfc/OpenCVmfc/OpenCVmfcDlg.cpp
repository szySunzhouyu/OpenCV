
// OpenCVmfcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OpenCVmfc.h"
#include "OpenCVmfcDlg.h"
#include "afxdialogex.h"
#include "cv.h"
#include "highgui.h"
#include "cxcore.h"
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpenCVmfcDlg �Ի���




COpenCVmfcDlg::COpenCVmfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COpenCVmfcDlg::IDD, pParent)
	, m_ipl(NULL)
	, m_Path(_T(""))
	, sx(0)
	, sy(0)
	, m_ColorMode1(0)
	, m_PseudoColorMode(0)
	, category(0)
	, m_ShapenType(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenCVmfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO9, m_ColorMode1);
	DDX_Radio(pDX, IDC_RADIO1, m_PseudoColorMode);
	DDX_Radio(pDX, IDC_RADIO6, category);
	DDX_Radio(pDX, IDC_RADIO4, m_ShapenType);
}

BEGIN_MESSAGE_MAP(COpenCVmfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO3, &COpenCVmfcDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_OpenPic, &COpenCVmfcDlg::OnBnClickedOpenpic)
	ON_BN_CLICKED(IDC_Video, &COpenCVmfcDlg::OnBnClickedVideo)
	ON_BN_CLICKED(IDC_Gray, &COpenCVmfcDlg::OnBnClickedGray)
	ON_BN_CLICKED(IDC_Canny, &COpenCVmfcDlg::OnBnClickedCanny)
	ON_BN_CLICKED(IDC_Binary, &COpenCVmfcDlg::OnBnClickedBinary)
	ON_BN_CLICKED(IDC_LineScale, &COpenCVmfcDlg::OnBnClickedLinescale)
	ON_BN_CLICKED(IDC_LogScale, &COpenCVmfcDlg::OnBnClickedLogscale)
	ON_BN_CLICKED(IDC_HistEq, &COpenCVmfcDlg::OnBnClickedHisteq)
	ON_BN_CLICKED(IDC_fushi, &COpenCVmfcDlg::OnBnClickedfushi)
	ON_BN_CLICKED(IDC_Dilate, &COpenCVmfcDlg::OnBnClickedDilate)
	ON_BN_CLICKED(IDC_MOpen, &COpenCVmfcDlg::OnBnClickedMopen)
	ON_BN_CLICKED(IDC_Mclose, &COpenCVmfcDlg::OnBnClickedMclose)
	ON_BN_CLICKED(IDC_ColorMode, &COpenCVmfcDlg::OnBnClickedColormode)
	ON_BN_CLICKED(IDC_WColor, &COpenCVmfcDlg::OnBnClickedWcolor)
	ON_BN_CLICKED(IDC_Smooth, &COpenCVmfcDlg::OnBnClickedSmooth)
	ON_BN_CLICKED(IDC_Shapen, &COpenCVmfcDlg::OnBnClickedShapen)
	ON_BN_CLICKED(IDC_Resize, &COpenCVmfcDlg::OnBnClickedResize)
	ON_BN_CLICKED(IDC_spin, &COpenCVmfcDlg::OnBnClickedspin)
	ON_BN_CLICKED(IDC_OpenV, &COpenCVmfcDlg::OnBnClickedOpenv)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CloseV, &COpenCVmfcDlg::OnBnClickedClosev)
	ON_BN_CLICKED(IDC_GetV, &COpenCVmfcDlg::OnBnClickedGetv)
END_MESSAGE_MAP()


// COpenCVmfcDlg ��Ϣ�������

BOOL COpenCVmfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void COpenCVmfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COpenCVmfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR COpenCVmfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CvCapture* capture = NULL;

void COpenCVmfcDlg::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//��ͼ��
void COpenCVmfcDlg::OnBnClickedOpenpic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(true,_T("*.bmp"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
                   _T("image file(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*|"),NULL);//����ѡ��ͼƬ�Ի���
    dlg.m_ofn.lpstrTitle=_T("open Image");//���ļ��Ի���ı�����
	if(dlg.DoModal()!=IDOK)
		return;
	m_Path = dlg.GetPathName();//��ȡͼƬ·��
	m_Path.Replace(_T("//"),_T("////"));

	m_ipl = cvLoadImage((CT2CA)m_Path);
	if(!m_ipl)
		return;
	CDC* pDC=GetDlgItem(IDC_PIC)->GetDC();
    HDC hDC=pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(IDC_PIC)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(m_ipl);
	cimg.DrawToHDC(hDC,&rect);
	ReleaseDC(pDC);
}

int g_slider_position=0;
//����������
void onTrackbarSlide(int pos)
{
	cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,pos);

}

//����Ƶ
void COpenCVmfcDlg::OnBnClickedVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(true,_T("*.avi"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
                   _T("image file(*.avi)|*.avi|All Files(*.*)|*.*|"),NULL);//����ѡ����Ƶ�Ի���
    dlg.m_ofn.lpstrTitle=_T("open Video");//���ļ��Ի���ı�����
	if(dlg.DoModal()!=IDOK)  //�ж��Ƿ�����Ƶ
		return;
	
	m_Path = dlg.GetPathName();//��ȡ��Ƶ·��
	m_Path.Replace(_T("//"),_T("////"));
	
	capture = cvCreateFileCapture((CT2CA)m_Path);
	IplImage* frame;
	int frames = (int)cvGetCaptureProperty(
				capture,
				CV_CAP_PROP_FRAME_COUNT
				);
	if(frames!=0)
	{
		cvCreateTrackbar(
			"position",
			"������Ƶ",
			&g_slider_position,
			frames,
			onTrackbarSlide
			);
	
	while(1){
		frame = cvQueryFrame(capture);

		if(!frame){
			break;
		}
		cvNamedWindow("������Ƶ");
		cvShowImage("������Ƶ",frame);

		char c = cvWaitKey(33);
		g_slider_position++;
		cvCreateTrackbar("position","������Ƶ",&g_slider_position,frames,onTrackbarSlide);
		
	}

	cvReleaseImage(&frame);
	cvReleaseCapture(&capture);
	cvDestroyWindow("��Ƶ����");
	}
}

//�Ҷ�ͼ
void COpenCVmfcDlg::OnBnClickedGray()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IplImage *g_src;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	cvNamedWindow("�Ҷ�ͼ");
	cvShowImage("�Ҷ�ͼ",g_src);
	
	char k = cvWaitKey(0);
	if(k==27)//������ESC����رյ�ǰ����
		cvDestroyWindow("�Ҷ�ͼ");
	if(k=='s')//������Ϊ's'���򱣴�ͼƬ
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));//��ʽ��ʱ��
		strcat(strTime,".jpg");
		cvSaveImage(strTime,g_src);//����Ϊ������ʱ����.jpg
	}
	cvReleaseImage(&g_src);
}

//canny��Ե���
IplImage* m_ipl2;
IplImage* g_pCannyImg;
int nThresholdEdge = 1;
const char *windowName = "CannyTitle";
void on_trackbar(int threshold)
{
	cvCanny(m_ipl2,g_pCannyImg,threshold,threshold*3,3); 
	cvShowImage(windowName, g_pCannyImg ); 

}
//canny��Ե���
void COpenCVmfcDlg::OnBnClickedCanny()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ipl2 = cvLoadImage((CT2CA)m_Path);
	g_pCannyImg = cvCreateImage(cvSize(m_ipl2->width,m_ipl2->height),IPL_DEPTH_8U,1);
	cvNamedWindow(windowName);
	cvCreateTrackbar(
			"����ֵ",
			windowName,
			&nThresholdEdge,
			120,
			on_trackbar
			);

	on_trackbar(1);

	char k = cvWaitKey(0);
	if(k==27)//������ESC����رյ�ǰ����
		cvDestroyWindow(windowName);
	if(k=='s')//������Ϊ's'���򱣴�ͼƬ
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));//��ʽ��ʱ��
		strcat(strTime,".jpg");
		cvSaveImage(strTime,g_pCannyImg);//����Ϊ������ʱ����.jpg
	}
	cvReleaseImage(&g_pCannyImg);
	cvReleaseImage(&m_ipl2);
}

//��ֵͼ

IplImage* m_grayImg;
IplImage* g_pBinaryImg;

//const char *windowName1 = "��ֵͼ";
void on_trackbar1(int pos)
{
	cvThreshold(m_grayImg,g_pBinaryImg,pos,255,CV_THRESH_BINARY); 
	cvShowImage("��ֵͼ", g_pBinaryImg ); 

}
void COpenCVmfcDlg::OnBnClickedBinary()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IplImage* m_ipl3 = cvLoadImage((CT2CA)m_Path);
	//�����Ҷ�ͼ
	m_grayImg = cvCreateImage(cvGetSize(m_ipl3),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl3,m_grayImg,CV_BGR2GRAY);
	//������ֵͼ
	g_pBinaryImg = cvCreateImage(cvGetSize(m_grayImg),IPL_DEPTH_8U,1);
	
	cvNamedWindow( "��ֵͼ");
	int nThreshold = 0;//����������
	cvCreateTrackbar(
			"��ֵ",
			 "��ֵͼ",
			&nThreshold,
			254,
			on_trackbar1
			);

	on_trackbar1(1);

	
	char k = cvWaitKey(0);
	if(k==27)//������ESC����رյ�ǰ����
		cvDestroyWindow("��ֵͼ");
	if(k=='s')//������Ϊ's'���򱣴�ͼƬ
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));//��ʽ��ʱ��
		strcat(strTime,".jpg");
		cvSaveImage(strTime,g_pBinaryImg);//����Ϊ������ʱ����.jpg
	}

	cvReleaseImage(&g_pCannyImg);
	cvReleaseImage(&m_grayImg);
	cvReleaseImage(&m_ipl3);
}

//�Աȶ�����չ��
void COpenCVmfcDlg::OnBnClickedLinescale()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IplImage *g_src,*dst;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);

	int tmp = 0;
	for(int y=0;y<dst->height;y++){//��������
		for(int x=0;x<dst->width;x++){
			//ȡԭͼ��x��y�����ص�ĻҶ�ֵ
			tmp=((UCHAR*)(g_src->imageData+g_src->widthStep*y))[x];
			//��ȡ����ͼ���x��y�����ص��ָ��
			UCHAR* temp_ptr = &((UCHAR*)(dst->imageData+dst->widthStep*y))[x];

			if(tmp<64){
				temp_ptr[0]=tmp/2;
			}else if(tmp<192){
				temp_ptr[0]=tmp+tmp/2;
			}else{
				temp_ptr[0]=tmp/2;
			}

		}
	}
	cvNamedWindow("��������");
	cvShowImage("��������",dst);

	char k = cvWaitKey(0);
	if(k==27)//������ESC����رյ�ǰ����
		cvDestroyWindow("��������");
	if(k=='s')//������Ϊ's'���򱣴�ͼƬ
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));//��ʽ��ʱ��
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//����Ϊ������ʱ����.jpg
	}
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//�����Զ�̬��Χ����
void COpenCVmfcDlg::OnBnClickedLogscale()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IplImage *g_src,*dst;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);

	int tmp = 0;
	for(int y=0;y<dst->height;y++){//��������
		for(int x=0;x<dst->width;x++){
			//ȡԭͼ��x��y�����ص�ĻҶ�ֵ
			tmp=((UCHAR*)(g_src->imageData+g_src->widthStep*y))[x];
			//��ȡ����ͼ���x��y�����ص��ָ��
			UCHAR* temp_ptr = &((UCHAR*)(dst->imageData+dst->widthStep*y))[x];
			temp_ptr[0]=(UCHAR)120*log10((float)(1+tmp));
		}
	}
	cvNamedWindow("����������");
	cvShowImage("����������",dst);
   
	char k = cvWaitKey(0);
	if(k==27)//������ESC����رյ�ǰ����
		cvDestroyWindow("����������");
	if(k=='s')//������Ϊ's'���򱣴�ͼƬ
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));//��ʽ��ʱ��
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//����Ϊ������ʱ����.jpg
	}
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}


//ֱ��ͼ���⻯
void COpenCVmfcDlg::OnBnClickedHisteq()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IplImage *g_src,*dst;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);

	cvEqualizeHist(g_src,dst);//ֱ��ͼ����
	cvNamedWindow("ֱ��ͼ���⻯ͼ��");
	cvShowImage("ֱ��ͼ���⻯ͼ��",dst);
	
	char k = cvWaitKey(0);
	if(k==27)//������ESC����رյ�ǰ����
		cvDestroyWindow("ֱ��ͼ���⻯ͼ��");
	if(k=='s')//������Ϊ's'���򱣴�ͼƬ
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));//��ʽ��ʱ��
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//����Ϊ������ʱ����.jpg
	}
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//ͼ��ʴ
void COpenCVmfcDlg::OnBnClickedfushi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IplImage *g_src,*dst;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);

	IplConvKernel* M;
	M=cvCreateStructuringElementEx(3,3,0,0,CV_SHAPE_RECT);//�����ṹԪ��
	cvErode(g_src,dst,M);

	cvNamedWindow("��ʴ���ͼ��");
	cvShowImage("��ʴ���ͼ��",dst);
	
	char k = cvWaitKey(0);
	if(k==27)//������ESC����رյ�ǰ����
		cvDestroyWindow("��ʴ���ͼ��");
	if(k=='s')//������Ϊ's'���򱣴�ͼƬ
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));//��ʽ��ʱ��
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//����Ϊ������ʱ����.jpg
	}
	cvReleaseStructuringElement(&M);
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//ͼ������
void COpenCVmfcDlg::OnBnClickedDilate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IplImage *g_src,*dst;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);

	IplConvKernel* M;
	M=cvCreateStructuringElementEx(3,3,0,0,CV_SHAPE_RECT);//�����ṹԪ��
	cvDilate(g_src,dst,M);

	cvNamedWindow("���ͺ��ͼ��");
	cvShowImage("���ͺ��ͼ��",dst);
	
	char k = cvWaitKey(0);
	if(k==27)//������ESC����رյ�ǰ����
		cvDestroyWindow("���ͺ��ͼ��");
	if(k=='s')//������Ϊ's'���򱣴�ͼƬ
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));//��ʽ��ʱ��
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//����Ϊ������ʱ����.jpg
	}
	cvReleaseStructuringElement(&M);
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//������
void COpenCVmfcDlg::OnBnClickedMopen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IplImage *g_src,*dst;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);

	IplConvKernel* M;
	M=cvCreateStructuringElementEx(3,3,0,0,CV_SHAPE_RECT);//�����ṹԪ��
	cvMorphologyEx(g_src,dst,NULL,M,CV_MOP_OPEN);//������

	cvNamedWindow("��������ͼ��");
	cvShowImage("��������ͼ��",dst);
	
	char k = cvWaitKey(0);
	if(k==27)//������ESC����رյ�ǰ����
		cvDestroyWindow("��������ͼ��");
	if(k=='s')//������Ϊ's'���򱣴�ͼƬ
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));//��ʽ��ʱ��
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//����Ϊ������ʱ����.jpg
	}
	cvReleaseStructuringElement(&M);
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//������
void COpenCVmfcDlg::OnBnClickedMclose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IplImage *g_src,*dst;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);

	IplConvKernel* M;
	M=cvCreateStructuringElementEx(3,3,0,0,CV_SHAPE_RECT);//�����ṹԪ��
	cvMorphologyEx(g_src,dst,NULL,M,CV_MOP_CLOSE);//������

	cvNamedWindow("��������ͼ��");
	cvShowImage("��������ͼ��",dst);
	
	char k = cvWaitKey(0);
	if(k==27)//������ESC����رյ�ǰ����
		cvDestroyWindow("��������ͼ��");
	if(k=='s')//������Ϊ's'���򱣴�ͼƬ
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));//��ʽ��ʱ��
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//����Ϊ������ʱ����.jpg
	}
	cvReleaseStructuringElement(&M);
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//ɫ�ʿռ�ת��
void COpenCVmfcDlg::OnBnClickedColormode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IplImage* dst;
	dst=cvCreateImage(cvGetSize(m_ipl),m_ipl->depth,m_ipl->nChannels);
	UpdateData();//��ȡ��ѡ���ѡ�����������m_ColorMode1��ֵ
	
	switch(m_ColorMode1)
	{
		case 0://RGB->XYZ
			cvCvtColor(m_ipl,dst,CV_RGB2XYZ);
		//	cvNamedWindow("RGB");
		//	cvShowImage("RGB",dst);
			break;

		case 1://RGB->YCrCb
			cvCvtColor(m_ipl,dst,CV_BGR2YCrCb);
			//cvNamedWindow("YCrCb");
			//cvShowImage("YCrCb",dst);
			//cvWaitKey(0);
			break;
		case 2://RGB->HSV
			cvCvtColor(m_ipl,dst,CV_BGR2HSV);
		//	cvNamedWindow("HSV");
			//cvShowImage("HSV",dst);
			//cvWaitKey(0);
			break;
	}
	cvNamedWindow("ɫ�ʿռ�ת��");
	cvShowImage("ɫ�ʿռ�ת��",dst);
	char k = cvWaitKey(0);
	if(k==27)//������ESC����رյ�ǰ����
		cvDestroyWindow("ɫ�ʿռ�ת��");
	if(k=='s')//������Ϊ's'���򱣴�ͼƬ
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));//��ʽ��ʱ��
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//����Ϊ������ʱ����.jpg
	}
	cvReleaseImage(&dst);
}

//α��ɫ
void COpenCVmfcDlg::OnBnClickedWcolor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IplImage *g_src,*dst;
	g_src=cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst=cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,3);
	UpdateData();

	int tmp=0;

	switch(m_PseudoColorMode)
	{
		case 0://�ܶȷֲ㷨
			for(int y=0;y<dst->height;y++)
			{
				for(int x=0;x<dst->width;x++)
				{
					tmp=((UCHAR*)(g_src->imageData + g_src->widthStep*y))[x];
					//��ȡ����ͼ���x��y�����ص��ָ��
					UCHAR* temp_ptr = &((UCHAR*)(dst->imageData+dst->widthStep*y))[x*3];

					if(tmp<60){
						temp_ptr[0]=255;//blue
						temp_ptr[1]=0;//green
						temp_ptr[2]=0;//red
					}
					else if(tmp<200)
					{
						temp_ptr[0]=0;//blue
						temp_ptr[1]=255;//green
						temp_ptr[2]=0;//red
					}
					else
					{
						temp_ptr[0]=0;//blue
						temp_ptr[1]=0;//green
						temp_ptr[2]=255;//red
					}
				}
			}
			break;
		case 1:
			for(int y=0;y<dst->height;y++)
			{
				for(int x=0;x<dst->width;x++)
				{
					tmp=((UCHAR*)(g_src->imageData + g_src->widthStep*y))[x];
					//��ȡ����ͼ���x��y�����ص��ָ��
					UCHAR* temp_ptr = &((UCHAR*)(dst->imageData+dst->widthStep*y))[x*3];

					if(tmp<64){
						temp_ptr[0]=255;//blue
						temp_ptr[1]=tmp;//green
						temp_ptr[2]=0;//red
					}
					else if(tmp<128)
					{
						temp_ptr[0]=tmp;//blue
						temp_ptr[1]=255;//green
						temp_ptr[2]=0;//red
					}
					else if(tmp<192)
					{
						temp_ptr[0]=0;//blue
						temp_ptr[1]=255;//green
						temp_ptr[2]=tmp;//red
					}
					else
					{
						temp_ptr[0]=0;//blue
						temp_ptr[1]=tmp;//green
						temp_ptr[2]=255;//red
					} 
				}
				
			}
			break;
		case 2:
			IplImage *dst_R,*dst_G,*dst_B,*dst_sobel;
			dst_R=cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);//�洢α��ɫͼ���Rͨ��
			dst_G=cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);//�洢α��ɫͼ���Gͨ��
			dst_B=cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);//�洢α��ɫͼ���Bͨ��
			dst_sobel=cvCreateImage(cvGetSize(g_src),IPL_DEPTH_16S,1);
			//�洢sobel���������Ľ��������sobel���������Ľ����sobel�������굼������и�ֵ��
			//�����д���255��ֵ��Ҫ16λ�з��ŵģ�Ҳ����IPL_DEPTH_16S
			cvSobel(g_src,dst_sobel,1,0,3);//ʹ��sobel�����˲�
			cvConvertScaleAbs(dst_sobel,dst_R,1,0);//��sobel�����˲���Ľ��תΪ8λ�޷��ţ�������Rͨ��

			cvSmooth(g_src,dst_G,CV_MEDIAN,3,3);//Gͨ��ʹ����ֵ�˲�
			cvSmooth(g_src,dst_B,CV_GAUSSIAN);//Bͨ��ʹ�ø�˹�˲�
			for(int y=0;y<dst->height;y++)//��R��G��B��ͨ����ͼ��ϳ�α��ɫͼ��
			{
				for(int x=0;x<dst->width;x++)
				{
					int tmp_R=((UCHAR*)(dst_R->imageData + dst_R->widthStep*y))[x];
					int tmp_G=((UCHAR*)(dst_G->imageData + dst_G->widthStep*y))[x];
					int tmp_B=((UCHAR*)(dst_B->imageData + dst_B->widthStep*y))[x];

					//��ȡ����ͼ���x��y�����ص��ָ��
					UCHAR* temp_ptr = &((UCHAR*)(dst->imageData+dst->widthStep*y))[x*3];

					temp_ptr[0]=tmp_B;//blue
					temp_ptr[1]=tmp_G;//green
					temp_ptr[2]=tmp_R;//red
				}
			
			}

			break;


	}

	cvNamedWindow("α��ͼ");
	cvShowImage("α��ͼ",dst);
	char k = cvWaitKey(0);
	if(k==27)//������ESC����رյ�ǰ����
		cvDestroyWindow("α��ͼ");
	if(k=='s')//������Ϊ's'���򱣴�ͼƬ
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));//��ʽ��ʱ��
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//����Ϊ������ʱ����.jpg
	}
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//ƽ������
void COpenCVmfcDlg::OnBnClickedSmooth()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IplImage* dst;
	dst=cvCreateImage(cvGetSize(m_ipl),m_ipl->depth,m_ipl->nChannels);
	UpdateData();//��ȡ��ѡ���ѡ�����������m_ColorMode1��ֵ
	switch(category)
	{
		case 0://��ֵģ��
			cvSmooth(m_ipl,dst,CV_MEDIAN,3,3);
			//cvNamedWindow("��ֵģ��");
			//cvShowImage("��ֵģ��",dst);
			//cvWaitKey(0);
			break;
		case 1://��˹ģ��
			cvSmooth(m_ipl,dst,CV_GAUSSIAN,3,3);
			//cvNamedWindow("��˹ģ��");
			//cvShowImage("��˹ģ��",dst);
			//cvWaitKey(0);
			break;
		case 2://˫���˲�
			cvSmooth(m_ipl,dst,CV_BILATERAL,3,3);
			//cvNamedWindow("˫���˲�");
			//cvShowImage("˫���˲�",dst);
			//cvWaitKey(0);
			break;
	}
	cvNamedWindow("ƽ������");
	cvShowImage("ƽ������",dst);
	char k = cvWaitKey(0);
	if(k==27)//������ESC����رյ�ǰ����
		cvDestroyWindow("ƽ������");
	if(k=='s')//������Ϊ's'���򱣴�ͼƬ
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));//��ʽ��ʱ��
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//����Ϊ������ʱ����.jpg
	}
	cvReleaseImage(&dst);
}

//��
void COpenCVmfcDlg::OnBnClickedShapen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IplImage *g_src,*dst;
	g_src=cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst=cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);
	UpdateData();

	switch(m_ShapenType)
	{
	case 0:
		IplImage *dst_sobel;
		dst_sobel = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_16S,1);
		cvSobel(g_src,dst_sobel,1,0,3);
		cvConvertScaleAbs(dst_sobel,dst,1,0);
		//cvNamedWindow("Sobel�񻯺�ͼ��");
		//cvShowImage("Sobel�񻯺�ͼ��",dst);
		//cvWaitKey(0);
		break;
	case 1:
		float m[9];
		m[0] = 0;
		m[1] = 1;
		m[2] = 0;
		m[3] = -1;
		m[4] = 4;
		m[5] = -1;
		m[6] = 0;
		m[7] = -1;
		m[8] = 0;
		CvMat kernel = cvMat(2,3,CV_32F,m);//����ʵ��������˹�㷨�ľ����
		cvFilter2D(g_src,dst,&kernel,cvPoint(-1,-1));
		//cvNamedWindow("Laplace�񻯺�ͼ��");
		//cvShowImage("Laplace�񻯺�ͼ��",dst);
		//cvWaitKey(0);
		break;
	}
	cvNamedWindow("�񻯴���");
	cvShowImage("�񻯴���",dst);
	char k = cvWaitKey(0);
	if(k==27)//������ESC����رյ�ǰ����
		cvDestroyWindow("�񻯴���");
	if(k=='s')//������Ϊ's'���򱣴�ͼƬ
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));//��ʽ��ʱ��
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//����Ϊ������ʱ����.jpg
	}
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//����
void COpenCVmfcDlg::OnBnClickedResize()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit* m_Edit_H = (CEdit*)GetDlgItem(IDC_Height);
	CString Height;
	m_Edit_H->GetWindowText(Height);
	int nH = atoi((CT2CA)Height);

	CEdit* m_Edit_W = (CEdit*)GetDlgItem(IDC_Width);
	CString Width;
	m_Edit_W->GetWindowText(Width);
	int nW = atoi((CT2CA)Width);

	IplImage* dst = cvCreateImage(cvSize(nW,nH),IPL_DEPTH_8U,3);
	cvResize(m_ipl,dst,CV_INTER_LINEAR);
	cvNamedWindow("���ź�ͼ��");
	cvShowImage("���ź�ͼ��",dst);
	char k = cvWaitKey(0);
	if(k==27)
		cvDestroyWindow("���ź�ͼ��");
	if(k=='s')
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//����Ϊ������ʱ����.jpg
	}
	cvReleaseImage(&dst);
}


//��ת����
void COpenCVmfcDlg::bound(int x, int y, float ca, float sa, int *xmin, int *xmax, int *ymin, int *ymax)
/* int x,y;
 float ca,sa;
 int *xmin,*xmax,*ymin,*ymax;*/
{   
    int rx,ry;
    // ˳ʱ����ת
    rx = (int)floor(ca*(float)x+sa*(float)y);
    ry = (int)floor(-sa*(float)x+ca*(float)y);
    if (rx<*xmin) *xmin=rx; if (rx>*xmax) *xmax=rx;
    if (ry<*ymin) *ymin=ry; if (ry>*ymax) *ymax=ry;
}
//��ת
void COpenCVmfcDlg::OnBnClickedspin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CEdit* m_Edit_A = (CEdit*)GetDlgItem(IDC_Angle);
	CString cAngle;
	m_Edit_A->GetWindowText(cAngle);
	int angle = atoi((CT2CA)cAngle);
	//������ת�Ƕȼ�����ת��ͼ��ߴ�
	int nx,ny;
	float ca,sa;
	int xmin,xmax,ymin,ymax;
	ca = (float)cos((double)(angle)*CV_PI/180.0);
	sa = (float)sin((double)(angle)*CV_PI/180.0);
	nx = m_ipl->width;
	ny = m_ipl->height;
	xmin = xmax = ymin = ymax = 0;
	bound(nx-1,0,ca,sa,&xmin,&xmax,&ymin,&ymax);
	bound(0,ny-1,ca,sa,&xmin,&xmax,&ymin,&ymax);
	bound(nx-1,ny-1,ca,sa,&xmin,&xmax,&ymin,&ymax);
	sx = xmax-xmin+1;//��ת��ͼ��Ŀ�
	sy = ymax-ymin+1;//��ת��ͼ��ĸ�
	//�õ���ת��ͼ��ߴ��ʹ��OpenCV������ԭʼͼ�������ת
	IplImage* dst;
	dst = cvCreateImage(cvSize(sx,sy),m_ipl->depth,m_ipl->nChannels);

	//�����任�������ڷ���仯
	float m[6];
	m[0] = ca;
	m[1] = sa;
	m[2] = -(float)xmin;
	m[3] = -m[1];
	m[4] = m[0];
	m[5] = -(float)ymin;
	CvMat M = cvMat(2,3,CV_32F,m);

	cvWarpAffine(m_ipl,dst,&M,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS,cvScalarAll(0));

	cvNamedWindow("��ת��ͼ��");
	cvShowImage("��ת��ͼ��",dst);
	//cvWaitKey(0);
	char k = cvWaitKey(0);
	if(k==27)
		cvDestroyWindow("��ת��ͼ��");
	if(k=='s')
	{
		//��ȡϵͳʱ��
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../�����ͼƬ/%Y%m%d%H%M%S",localtime(&t));
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//����Ϊ������ʱ����.jpg
	}
	cvReleaseImage(&dst);


}

//������ͷ
CvCapture* Capture1;
CvCapture* m_Video;
IplImage* frame1;
IplImage* m_grabframe;
CRect rect;
CDC *pDC;
HDC hDC;
CWnd *pwnd;
int ImgNum = 0;
void COpenCVmfcDlg::OnBnClickedOpenv()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Capture1 = cvCreateCameraCapture(0); //  
    if (Capture1==0)  
    {  
        MessageBox(_T("�޷���������ͷ������"));  
        return;  
    }  
  
    frame1 = cvQueryFrame(Capture1); //������ͷ�����ļ���ץȡ������һ֡  
    pDC = GetDlgItem(IDC_PIC1)->GetDC();//GetDlgItem(IDC_PIC_STATIC)��˼Ϊ��ȡ��ʾ�ؼ��ľ�����������ָ�룩����ȡ��ʾ�ؼ���DC  
    GetDlgItem(IDC_PIC1)->GetClientRect(&rect);  
    hDC = pDC->GetSafeHdc();//��ȡ��ʾ�ؼ��ľ��  
  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame1, 1); //���Ƹ�֡ͼ��     
    m_CvvImage.DrawToHDC(hDC, &rect); //��ʾ���豸�ľ��ο���  
    ReleaseDC(pDC);  
  
    SetTimer(1, 25, NULL); //��ʱ������ʱʱ���֡��һ��
}


void COpenCVmfcDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	pDC = GetDlgItem(IDC_PIC1)->GetDC();//GetDlgItem(IDC_PIC_STATIC)��˼Ϊ��ȡ��ʾ�ؼ��ľ�����������ָ�룩����ȡ��ʾ�ؼ���DC  
  
    GetDlgItem(IDC_PIC1)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//��ȡ��ʾ�ؼ��ľ��  
  
    frame1 = cvQueryFrame(Capture1); //������ͷ�����ļ���ץȡ������һ֡  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame1, 1); //���Ƹ�֡ͼ��     
      
    m_CvvImage.DrawToHDC(hDC, &rect); //��ʾ���豸�ľ��ο���  
      
    CDialogEx::OnTimer(nIDEvent);  
}

//�ر�����ͷ
void COpenCVmfcDlg::OnBnClickedClosev()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!Capture1)  
    {  
        MessageBox(_T("û�д�����ͷ������"));  
        return;  
    }  
      
    cvReleaseCapture(&Capture1);  
  
    pDC = GetDlgItem(IDC_PIC1)->GetDC();//GetDlgItem(IDC_PIC_STATIC)��˼Ϊ��ȡ��ʾ�ؼ��ľ�����������ָ�룩����ȡ��ʾ�ؼ���DC  
  
    GetDlgItem(IDC_PIC1)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//��ȡ��ʾ�ؼ��ľ��  
  
    frame1 = cvLoadImage("..\\������\\01.jpg"); //ͼƬ��ȡ·�������Լ��趨  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame1, 1); //���Ƹ�֡ͼ��     
    m_CvvImage.DrawToHDC(hDC, &rect); //��ʾ���豸�ľ��ο���  
    ReleaseDC(pDC);  
}

//������
void COpenCVmfcDlg::OnBnClickedGetv()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_grabframe = cvQueryFrame(Capture);  
    m_grabframe = frame1;  
    if (m_grabframe == 0)  
    {  
        MessageBox(_T("����ͷ�ѹرգ��޷���׽ͼ�񣡣���"));  
        return;  
    }  
      
    CString ImagePath=TEXT("..\\������\\");  
  
    //CString ImagePath = _T("..\\������\\"");  
  
    if (!PathIsDirectory(ImagePath))  
  
    {  
        CreateDirectory(ImagePath, 0);//�������򴴽�  
        MessageBox(_T("�궨ͼƬ�ļ����Ѵ���������"));  
        return;  
    }  
    char ImagesName[100];  
  
    ImgNum = ImgNum + 1;  
  
    sprintf_s(ImagesName, "%s%.2d%s", "..\\������\\", ImgNum, ".jpg");  
      
    IplImage * m_snap = cvCreateImage(cvGetSize(m_grabframe), m_grabframe->depth, m_grabframe->nChannels);  
    cvCopy(m_grabframe, m_snap, NULL);  
    cvSaveImage(ImagesName, m_snap); //��ͼ��д��ָ���ļ��е��ļ���ȥ  
  
    //���´��������ͼ�����ʾ����  
    pDC = GetDlgItem(IDC_PIC)->GetDC();//GetDlgItem(IDC_PIC_STATIC)��˼Ϊ��ȡ��ʾ�ؼ��ľ�����������ָ�룩����ȡ��ʾ�ؼ���DC  
  
    GetDlgItem(IDC_PIC)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//��ȡ��ʾ�ؼ��ľ��  
  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(m_snap, 1); //���Ƹ�֡ͼ��     
    m_CvvImage.DrawToHDC(hDC, &rect); //��ʾ���豸�����ľ��ο���  
}
