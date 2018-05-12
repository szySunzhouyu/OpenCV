
// OpenCVmfcDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// COpenCVmfcDlg 对话框




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


// COpenCVmfcDlg 消息处理程序

BOOL COpenCVmfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COpenCVmfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COpenCVmfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CvCapture* capture = NULL;

void COpenCVmfcDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
}

//打开图像
void COpenCVmfcDlg::OnBnClickedOpenpic()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(true,_T("*.bmp"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
                   _T("image file(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*|"),NULL);//弹出选择图片对话框
    dlg.m_ofn.lpstrTitle=_T("open Image");//打开文件对话框的标题名
	if(dlg.DoModal()!=IDOK)
		return;
	m_Path = dlg.GetPathName();//获取图片路径
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
//创建滚动条
void onTrackbarSlide(int pos)
{
	cvSetCaptureProperty(capture,CV_CAP_PROP_POS_FRAMES,pos);

}

//打开视频
void COpenCVmfcDlg::OnBnClickedVideo()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(true,_T("*.avi"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
                   _T("image file(*.avi)|*.avi|All Files(*.*)|*.*|"),NULL);//弹出选择视频对话框
    dlg.m_ofn.lpstrTitle=_T("open Video");//打开文件对话框的标题名
	if(dlg.DoModal()!=IDOK)  //判断是否获得视频
		return;
	
	m_Path = dlg.GetPathName();//获取视频路径
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
			"播放视频",
			&g_slider_position,
			frames,
			onTrackbarSlide
			);
	
	while(1){
		frame = cvQueryFrame(capture);

		if(!frame){
			break;
		}
		cvNamedWindow("播放视频");
		cvShowImage("播放视频",frame);

		char c = cvWaitKey(33);
		g_slider_position++;
		cvCreateTrackbar("position","播放视频",&g_slider_position,frames,onTrackbarSlide);
		
	}

	cvReleaseImage(&frame);
	cvReleaseCapture(&capture);
	cvDestroyWindow("视频播放");
	}
}

//灰度图
void COpenCVmfcDlg::OnBnClickedGray()
{
	// TODO: 在此添加控件通知处理程序代码
	IplImage *g_src;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	cvNamedWindow("灰度图");
	cvShowImage("灰度图",g_src);
	
	char k = cvWaitKey(0);
	if(k==27)//若输入ESC，则关闭当前窗口
		cvDestroyWindow("灰度图");
	if(k=='s')//若输入为's'，则保存图片
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));//格式化时间
		strcat(strTime,".jpg");
		cvSaveImage(strTime,g_src);//保存为年月日时分秒.jpg
	}
	cvReleaseImage(&g_src);
}

//canny边缘检测
IplImage* m_ipl2;
IplImage* g_pCannyImg;
int nThresholdEdge = 1;
const char *windowName = "CannyTitle";
void on_trackbar(int threshold)
{
	cvCanny(m_ipl2,g_pCannyImg,threshold,threshold*3,3); 
	cvShowImage(windowName, g_pCannyImg ); 

}
//canny边缘检测
void COpenCVmfcDlg::OnBnClickedCanny()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ipl2 = cvLoadImage((CT2CA)m_Path);
	g_pCannyImg = cvCreateImage(cvSize(m_ipl2->width,m_ipl2->height),IPL_DEPTH_8U,1);
	cvNamedWindow(windowName);
	cvCreateTrackbar(
			"参数值",
			windowName,
			&nThresholdEdge,
			120,
			on_trackbar
			);

	on_trackbar(1);

	char k = cvWaitKey(0);
	if(k==27)//若输入ESC，则关闭当前窗口
		cvDestroyWindow(windowName);
	if(k=='s')//若输入为's'，则保存图片
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));//格式化时间
		strcat(strTime,".jpg");
		cvSaveImage(strTime,g_pCannyImg);//保存为年月日时分秒.jpg
	}
	cvReleaseImage(&g_pCannyImg);
	cvReleaseImage(&m_ipl2);
}

//二值图

IplImage* m_grayImg;
IplImage* g_pBinaryImg;

//const char *windowName1 = "二值图";
void on_trackbar1(int pos)
{
	cvThreshold(m_grayImg,g_pBinaryImg,pos,255,CV_THRESH_BINARY); 
	cvShowImage("二值图", g_pBinaryImg ); 

}
void COpenCVmfcDlg::OnBnClickedBinary()
{
	// TODO: 在此添加控件通知处理程序代码
	IplImage* m_ipl3 = cvLoadImage((CT2CA)m_Path);
	//创建灰度图
	m_grayImg = cvCreateImage(cvGetSize(m_ipl3),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl3,m_grayImg,CV_BGR2GRAY);
	//创建二值图
	g_pBinaryImg = cvCreateImage(cvGetSize(m_grayImg),IPL_DEPTH_8U,1);
	
	cvNamedWindow( "二值图");
	int nThreshold = 0;//创建滑动条
	cvCreateTrackbar(
			"域值",
			 "二值图",
			&nThreshold,
			254,
			on_trackbar1
			);

	on_trackbar1(1);

	
	char k = cvWaitKey(0);
	if(k==27)//若输入ESC，则关闭当前窗口
		cvDestroyWindow("二值图");
	if(k=='s')//若输入为's'，则保存图片
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));//格式化时间
		strcat(strTime,".jpg");
		cvSaveImage(strTime,g_pBinaryImg);//保存为年月日时分秒.jpg
	}

	cvReleaseImage(&g_pCannyImg);
	cvReleaseImage(&m_grayImg);
	cvReleaseImage(&m_ipl3);
}

//对比度线性展宽
void COpenCVmfcDlg::OnBnClickedLinescale()
{
	// TODO: 在此添加控件通知处理程序代码
	IplImage *g_src,*dst;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);

	int tmp = 0;
	for(int y=0;y<dst->height;y++){//线性拉伸
		for(int x=0;x<dst->width;x++){
			//取原图第x行y列像素点的灰度值
			tmp=((UCHAR*)(g_src->imageData+g_src->widthStep*y))[x];
			//获取拉伸图像第x行y列像素点的指针
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
	cvNamedWindow("线性拉伸");
	cvShowImage("线性拉伸",dst);

	char k = cvWaitKey(0);
	if(k==27)//若输入ESC，则关闭当前窗口
		cvDestroyWindow("线性拉伸");
	if(k=='s')//若输入为's'，则保存图片
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));//格式化时间
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//保存为年月日时分秒.jpg
	}
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//非线性动态范围调整
void COpenCVmfcDlg::OnBnClickedLogscale()
{
	// TODO: 在此添加控件通知处理程序代码
	IplImage *g_src,*dst;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);

	int tmp = 0;
	for(int y=0;y<dst->height;y++){//线性拉伸
		for(int x=0;x<dst->width;x++){
			//取原图第x行y列像素点的灰度值
			tmp=((UCHAR*)(g_src->imageData+g_src->widthStep*y))[x];
			//获取拉伸图像第x行y列像素点的指针
			UCHAR* temp_ptr = &((UCHAR*)(dst->imageData+dst->widthStep*y))[x];
			temp_ptr[0]=(UCHAR)120*log10((float)(1+tmp));
		}
	}
	cvNamedWindow("非线性拉伸");
	cvShowImage("非线性拉伸",dst);
   
	char k = cvWaitKey(0);
	if(k==27)//若输入ESC，则关闭当前窗口
		cvDestroyWindow("非线性拉伸");
	if(k=='s')//若输入为's'，则保存图片
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));//格式化时间
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//保存为年月日时分秒.jpg
	}
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}


//直方图均衡化
void COpenCVmfcDlg::OnBnClickedHisteq()
{
	// TODO: 在此添加控件通知处理程序代码
	IplImage *g_src,*dst;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);

	cvEqualizeHist(g_src,dst);//直方图均衡
	cvNamedWindow("直方图均衡化图像");
	cvShowImage("直方图均衡化图像",dst);
	
	char k = cvWaitKey(0);
	if(k==27)//若输入ESC，则关闭当前窗口
		cvDestroyWindow("直方图均衡化图像");
	if(k=='s')//若输入为's'，则保存图片
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));//格式化时间
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//保存为年月日时分秒.jpg
	}
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//图像腐蚀
void COpenCVmfcDlg::OnBnClickedfushi()
{
	// TODO: 在此添加控件通知处理程序代码
	IplImage *g_src,*dst;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);

	IplConvKernel* M;
	M=cvCreateStructuringElementEx(3,3,0,0,CV_SHAPE_RECT);//创建结构元素
	cvErode(g_src,dst,M);

	cvNamedWindow("腐蚀后的图像");
	cvShowImage("腐蚀后的图像",dst);
	
	char k = cvWaitKey(0);
	if(k==27)//若输入ESC，则关闭当前窗口
		cvDestroyWindow("腐蚀后的图像");
	if(k=='s')//若输入为's'，则保存图片
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));//格式化时间
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//保存为年月日时分秒.jpg
	}
	cvReleaseStructuringElement(&M);
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//图像膨胀
void COpenCVmfcDlg::OnBnClickedDilate()
{
	// TODO: 在此添加控件通知处理程序代码
	IplImage *g_src,*dst;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);

	IplConvKernel* M;
	M=cvCreateStructuringElementEx(3,3,0,0,CV_SHAPE_RECT);//创建结构元素
	cvDilate(g_src,dst,M);

	cvNamedWindow("膨胀后的图像");
	cvShowImage("膨胀后的图像",dst);
	
	char k = cvWaitKey(0);
	if(k==27)//若输入ESC，则关闭当前窗口
		cvDestroyWindow("膨胀后的图像");
	if(k=='s')//若输入为's'，则保存图片
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));//格式化时间
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//保存为年月日时分秒.jpg
	}
	cvReleaseStructuringElement(&M);
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//开运算
void COpenCVmfcDlg::OnBnClickedMopen()
{
	// TODO: 在此添加控件通知处理程序代码
	IplImage *g_src,*dst;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);

	IplConvKernel* M;
	M=cvCreateStructuringElementEx(3,3,0,0,CV_SHAPE_RECT);//创建结构元素
	cvMorphologyEx(g_src,dst,NULL,M,CV_MOP_OPEN);//开运算

	cvNamedWindow("开运算后的图像");
	cvShowImage("开运算后的图像",dst);
	
	char k = cvWaitKey(0);
	if(k==27)//若输入ESC，则关闭当前窗口
		cvDestroyWindow("开运算后的图像");
	if(k=='s')//若输入为's'，则保存图片
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));//格式化时间
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//保存为年月日时分秒.jpg
	}
	cvReleaseStructuringElement(&M);
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//闭运算
void COpenCVmfcDlg::OnBnClickedMclose()
{
	// TODO: 在此添加控件通知处理程序代码
	IplImage *g_src,*dst;
	g_src = cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst = cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);

	IplConvKernel* M;
	M=cvCreateStructuringElementEx(3,3,0,0,CV_SHAPE_RECT);//创建结构元素
	cvMorphologyEx(g_src,dst,NULL,M,CV_MOP_CLOSE);//开运算

	cvNamedWindow("闭运算后的图像");
	cvShowImage("闭运算后的图像",dst);
	
	char k = cvWaitKey(0);
	if(k==27)//若输入ESC，则关闭当前窗口
		cvDestroyWindow("闭运算后的图像");
	if(k=='s')//若输入为's'，则保存图片
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));//格式化时间
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//保存为年月日时分秒.jpg
	}
	cvReleaseStructuringElement(&M);
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//色彩空间转换
void COpenCVmfcDlg::OnBnClickedColormode()
{
	// TODO: 在此添加控件通知处理程序代码
	IplImage* dst;
	dst=cvCreateImage(cvGetSize(m_ipl),m_ipl->depth,m_ipl->nChannels);
	UpdateData();//获取单选框的选择情况，更新m_ColorMode1的值
	
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
	cvNamedWindow("色彩空间转换");
	cvShowImage("色彩空间转换",dst);
	char k = cvWaitKey(0);
	if(k==27)//若输入ESC，则关闭当前窗口
		cvDestroyWindow("色彩空间转换");
	if(k=='s')//若输入为's'，则保存图片
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));//格式化时间
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//保存为年月日时分秒.jpg
	}
	cvReleaseImage(&dst);
}

//伪彩色
void COpenCVmfcDlg::OnBnClickedWcolor()
{
	// TODO: 在此添加控件通知处理程序代码
	IplImage *g_src,*dst;
	g_src=cvCreateImage(cvGetSize(m_ipl),IPL_DEPTH_8U,1);
	cvCvtColor(m_ipl,g_src,CV_RGB2GRAY);
	dst=cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,3);
	UpdateData();

	int tmp=0;

	switch(m_PseudoColorMode)
	{
		case 0://密度分层法
			for(int y=0;y<dst->height;y++)
			{
				for(int x=0;x<dst->width;x++)
				{
					tmp=((UCHAR*)(g_src->imageData + g_src->widthStep*y))[x];
					//获取拉伸图像第x行y列像素点的指针
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
					//获取拉伸图像第x行y列像素点的指针
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
			dst_R=cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);//存储伪彩色图像的R通道
			dst_G=cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);//存储伪彩色图像的G通道
			dst_B=cvCreateImage(cvGetSize(g_src),IPL_DEPTH_8U,1);//存储伪彩色图像的B通道
			dst_sobel=cvCreateImage(cvGetSize(g_src),IPL_DEPTH_16S,1);
			//存储sobel算子运算后的结果，由于sobel算子运算后的结果，sobel算子求完导数后会有负值，
			//还会有大于255的值，要16位有符号的，也即便IPL_DEPTH_16S
			cvSobel(g_src,dst_sobel,1,0,3);//使用sobel算子滤波
			cvConvertScaleAbs(dst_sobel,dst_R,1,0);//将sobel算子滤波后的结果转为8位无符号，并存入R通道

			cvSmooth(g_src,dst_G,CV_MEDIAN,3,3);//G通道使用中值滤波
			cvSmooth(g_src,dst_B,CV_GAUSSIAN);//B通道使用高斯滤波
			for(int y=0;y<dst->height;y++)//将R、G、B三通道的图像合成伪彩色图像
			{
				for(int x=0;x<dst->width;x++)
				{
					int tmp_R=((UCHAR*)(dst_R->imageData + dst_R->widthStep*y))[x];
					int tmp_G=((UCHAR*)(dst_G->imageData + dst_G->widthStep*y))[x];
					int tmp_B=((UCHAR*)(dst_B->imageData + dst_B->widthStep*y))[x];

					//获取拉伸图像第x行y列像素点的指针
					UCHAR* temp_ptr = &((UCHAR*)(dst->imageData+dst->widthStep*y))[x*3];

					temp_ptr[0]=tmp_B;//blue
					temp_ptr[1]=tmp_G;//green
					temp_ptr[2]=tmp_R;//red
				}
			
			}

			break;


	}

	cvNamedWindow("伪彩图");
	cvShowImage("伪彩图",dst);
	char k = cvWaitKey(0);
	if(k==27)//若输入ESC，则关闭当前窗口
		cvDestroyWindow("伪彩图");
	if(k=='s')//若输入为's'，则保存图片
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));//格式化时间
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//保存为年月日时分秒.jpg
	}
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//平滑处理
void COpenCVmfcDlg::OnBnClickedSmooth()
{
	// TODO: 在此添加控件通知处理程序代码
	IplImage* dst;
	dst=cvCreateImage(cvGetSize(m_ipl),m_ipl->depth,m_ipl->nChannels);
	UpdateData();//获取单选框的选择情况，更新m_ColorMode1的值
	switch(category)
	{
		case 0://中值模糊
			cvSmooth(m_ipl,dst,CV_MEDIAN,3,3);
			//cvNamedWindow("中值模糊");
			//cvShowImage("中值模糊",dst);
			//cvWaitKey(0);
			break;
		case 1://高斯模糊
			cvSmooth(m_ipl,dst,CV_GAUSSIAN,3,3);
			//cvNamedWindow("高斯模糊");
			//cvShowImage("高斯模糊",dst);
			//cvWaitKey(0);
			break;
		case 2://双边滤波
			cvSmooth(m_ipl,dst,CV_BILATERAL,3,3);
			//cvNamedWindow("双边滤波");
			//cvShowImage("双边滤波",dst);
			//cvWaitKey(0);
			break;
	}
	cvNamedWindow("平滑处理");
	cvShowImage("平滑处理",dst);
	char k = cvWaitKey(0);
	if(k==27)//若输入ESC，则关闭当前窗口
		cvDestroyWindow("平滑处理");
	if(k=='s')//若输入为's'，则保存图片
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));//格式化时间
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//保存为年月日时分秒.jpg
	}
	cvReleaseImage(&dst);
}

//锐化
void COpenCVmfcDlg::OnBnClickedShapen()
{
	// TODO: 在此添加控件通知处理程序代码
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
		//cvNamedWindow("Sobel锐化后图像");
		//cvShowImage("Sobel锐化后图像",dst);
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
		CvMat kernel = cvMat(2,3,CV_32F,m);//创建实现拉普拉斯算法的卷积核
		cvFilter2D(g_src,dst,&kernel,cvPoint(-1,-1));
		//cvNamedWindow("Laplace锐化后图像");
		//cvShowImage("Laplace锐化后图像",dst);
		//cvWaitKey(0);
		break;
	}
	cvNamedWindow("锐化处理");
	cvShowImage("锐化处理",dst);
	char k = cvWaitKey(0);
	if(k==27)//若输入ESC，则关闭当前窗口
		cvDestroyWindow("锐化处理");
	if(k=='s')//若输入为's'，则保存图片
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));//格式化时间
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//保存为年月日时分秒.jpg
	}
	cvReleaseImage(&g_src);
	cvReleaseImage(&dst);
}

//缩放
void COpenCVmfcDlg::OnBnClickedResize()
{
	// TODO: 在此添加控件通知处理程序代码
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
	cvNamedWindow("缩放后图像");
	cvShowImage("缩放后图像",dst);
	char k = cvWaitKey(0);
	if(k==27)
		cvDestroyWindow("缩放后图像");
	if(k=='s')
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//保存为年月日时分秒.jpg
	}
	cvReleaseImage(&dst);
}


//旋转函数
void COpenCVmfcDlg::bound(int x, int y, float ca, float sa, int *xmin, int *xmax, int *ymin, int *ymax)
/* int x,y;
 float ca,sa;
 int *xmin,*xmax,*ymin,*ymax;*/
{   
    int rx,ry;
    // 顺时针旋转
    rx = (int)floor(ca*(float)x+sa*(float)y);
    ry = (int)floor(-sa*(float)x+ca*(float)y);
    if (rx<*xmin) *xmin=rx; if (rx>*xmax) *xmax=rx;
    if (ry<*ymin) *ymin=ry; if (ry>*ymax) *ymax=ry;
}
//旋转
void COpenCVmfcDlg::OnBnClickedspin()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit* m_Edit_A = (CEdit*)GetDlgItem(IDC_Angle);
	CString cAngle;
	m_Edit_A->GetWindowText(cAngle);
	int angle = atoi((CT2CA)cAngle);
	//根据旋转角度计算旋转后图像尺寸
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
	sx = xmax-xmin+1;//旋转后图像的宽
	sy = ymax-ymin+1;//旋转后图像的高
	//得到旋转后图像尺寸后，使用OpenCV函数对原始图像进行旋转
	IplImage* dst;
	dst = cvCreateImage(cvSize(sx,sy),m_ipl->depth,m_ipl->nChannels);

	//创建变换矩阵，用于仿射变化
	float m[6];
	m[0] = ca;
	m[1] = sa;
	m[2] = -(float)xmin;
	m[3] = -m[1];
	m[4] = m[0];
	m[5] = -(float)ymin;
	CvMat M = cvMat(2,3,CV_32F,m);

	cvWarpAffine(m_ipl,dst,&M,CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS,cvScalarAll(0));

	cvNamedWindow("旋转后图像");
	cvShowImage("旋转后图像",dst);
	//cvWaitKey(0);
	char k = cvWaitKey(0);
	if(k==27)
		cvDestroyWindow("旋转后图像");
	if(k=='s')
	{
		//获取系统时间
		time_t t = time(NULL);
		char strTime[64];
		ZeroMemory(strTime,sizeof(strTime));
		strftime(strTime,64,"../处理后图片/%Y%m%d%H%M%S",localtime(&t));
		strcat(strTime,".jpg");
		cvSaveImage(strTime,dst);//保存为年月日时分秒.jpg
	}
	cvReleaseImage(&dst);


}

//打开摄像头
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
	// TODO: 在此添加控件通知处理程序代码
	Capture1 = cvCreateCameraCapture(0); //  
    if (Capture1==0)  
    {  
        MessageBox(_T("无法连接摄像头！！！"));  
        return;  
    }  
  
    frame1 = cvQueryFrame(Capture1); //从摄像头或者文件中抓取并返回一帧  
    pDC = GetDlgItem(IDC_PIC1)->GetDC();//GetDlgItem(IDC_PIC_STATIC)意思为获取显示控件的句柄（句柄就是指针），获取显示控件的DC  
    GetDlgItem(IDC_PIC1)->GetClientRect(&rect);  
    hDC = pDC->GetSafeHdc();//获取显示控件的句柄  
  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame1, 1); //复制该帧图像     
    m_CvvImage.DrawToHDC(hDC, &rect); //显示到设备的矩形框内  
    ReleaseDC(pDC);  
  
    SetTimer(1, 25, NULL); //定时器，定时时间和帧率一致
}


void COpenCVmfcDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	pDC = GetDlgItem(IDC_PIC1)->GetDC();//GetDlgItem(IDC_PIC_STATIC)意思为获取显示控件的句柄（句柄就是指针），获取显示控件的DC  
  
    GetDlgItem(IDC_PIC1)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//获取显示控件的句柄  
  
    frame1 = cvQueryFrame(Capture1); //从摄像头或者文件中抓取并返回一帧  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame1, 1); //复制该帧图像     
      
    m_CvvImage.DrawToHDC(hDC, &rect); //显示到设备的矩形框内  
      
    CDialogEx::OnTimer(nIDEvent);  
}

//关闭摄像头
void COpenCVmfcDlg::OnBnClickedClosev()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!Capture1)  
    {  
        MessageBox(_T("没有打开摄像头！！！"));  
        return;  
    }  
      
    cvReleaseCapture(&Capture1);  
  
    pDC = GetDlgItem(IDC_PIC1)->GetDC();//GetDlgItem(IDC_PIC_STATIC)意思为获取显示控件的句柄（句柄就是指针），获取显示控件的DC  
  
    GetDlgItem(IDC_PIC1)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//获取显示控件的句柄  
  
    frame1 = cvLoadImage("..\\捕获画面\\01.jpg"); //图片读取路径可以自己设定  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(frame1, 1); //复制该帧图像     
    m_CvvImage.DrawToHDC(hDC, &rect); //显示到设备的矩形框内  
    ReleaseDC(pDC);  
}

//捕获画面
void COpenCVmfcDlg::OnBnClickedGetv()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_grabframe = cvQueryFrame(Capture);  
    m_grabframe = frame1;  
    if (m_grabframe == 0)  
    {  
        MessageBox(_T("摄像头已关闭，无法捕捉图像！！！"));  
        return;  
    }  
      
    CString ImagePath=TEXT("..\\捕获画面\\");  
  
    //CString ImagePath = _T("..\\捕获画面\\"");  
  
    if (!PathIsDirectory(ImagePath))  
  
    {  
        CreateDirectory(ImagePath, 0);//不存在则创建  
        MessageBox(_T("标定图片文件夹已创建！！！"));  
        return;  
    }  
    char ImagesName[100];  
  
    ImgNum = ImgNum + 1;  
  
    sprintf_s(ImagesName, "%s%.2d%s", "..\\捕获画面\\", ImgNum, ".jpg");  
      
    IplImage * m_snap = cvCreateImage(cvGetSize(m_grabframe), m_grabframe->depth, m_grabframe->nChannels);  
    cvCopy(m_grabframe, m_snap, NULL);  
    cvSaveImage(ImagesName, m_snap); //把图像写入指定文件夹的文件中去  
  
    //以下代码是完成图像的显示过程  
    pDC = GetDlgItem(IDC_PIC)->GetDC();//GetDlgItem(IDC_PIC_STATIC)意思为获取显示控件的句柄（句柄就是指针），获取显示控件的DC  
  
    GetDlgItem(IDC_PIC)->GetClientRect(&rect);  
  
    hDC = pDC->GetSafeHdc();//获取显示控件的句柄  
  
    CvvImage m_CvvImage;  
    m_CvvImage.CopyOf(m_snap, 1); //复制该帧图像     
    m_CvvImage.DrawToHDC(hDC, &rect); //显示到设备环境的矩形框内  
}
