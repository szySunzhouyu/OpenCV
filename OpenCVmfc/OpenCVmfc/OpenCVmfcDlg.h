
// OpenCVmfcDlg.h : 头文件
//

#pragma once
#include "CvvImage.h"
#include "cv.h"
#include "highgui.h"

// COpenCVmfcDlg 对话框
class COpenCVmfcDlg : public CDialogEx
{
// 构造
public:
	COpenCVmfcDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_OPENCVMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	IplImage* m_ipl;
	CString m_Path;
	int sx;
	int sy;
	int m_ColorMode1;
	int m_PseudoColorMode;
	void bound(int x, int y, float ca, float sa, int *xmin, int *xmax, int *ymin, int *ymax);
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedOpenpic();
	
	afx_msg void OnBnClickedVideo();
	afx_msg void OnBnClickedGray();
	afx_msg void OnBnClickedCanny();
	afx_msg void OnBnClickedBinary();
	afx_msg void OnBnClickedLinescale();
	afx_msg void OnBnClickedLogscale();
	afx_msg void OnBnClickedHisteq();
	afx_msg void OnBnClickedfushi();
	afx_msg void OnBnClickedDilate();
	afx_msg void OnBnClickedMopen();
	afx_msg void OnBnClickedMclose();
	afx_msg void OnBnClickedColormode();
	
	afx_msg void OnBnClickedWcolor();
	
	afx_msg void OnBnClickedSmooth();
	int category;
	afx_msg void OnBnClickedShapen();
	int m_ShapenType;
	afx_msg void OnBnClickedResize();
	afx_msg void OnBnClickedspin();
	afx_msg void OnBnClickedOpenv();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedClosev();
	afx_msg void OnBnClickedGetv();
};
