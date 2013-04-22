#include "StdAfx.h"
#include "Resource.h"
#include "ApplyUserList.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CApplyUser, CDialog)
	ON_WM_SIZE()
	ON_MESSAGE(WM_LBTUP,OnLBtUp)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//构造函数
CApplyUser::CApplyUser() : CDialog(IDD_DLG_GAME_RECORD)
{
	m_viewHandle = NULL;
}

//析构函数
CApplyUser::~CApplyUser()
{
}
void CApplyUser::MySetRect(CRect aRect)
{
}
//控件绑定
void CApplyUser::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RECORD_LIST, m_AppyUserList);
}

//初始化函数
BOOL CApplyUser::OnInitDialog()
{
	__super::OnInitDialog();

	//设置背景
	TCHAR szBuffer[_MAX_PATH];     
	::GetModuleFileName(AfxGetInstanceHandle(), szBuffer, _MAX_PATH);

	CString strPath;
	strPath.Format(_T("res://%s/#2/#193"),szBuffer);

	LVBKIMAGE bki;
	bki.ulFlags			=   LVBKIF_STYLE_TILE|LVBKIF_SOURCE_URL;   
	bki.pszImage		=   strPath.GetBuffer(strPath.GetLength());   
	bki.cchImageMax		=   strPath.GetLength();   
	BOOL bSuccess		=	m_AppyUserList.SetBkImage(   &bki);  
	
	m_AppyUserList.SetTextBkColor(-1);
	m_AppyUserList.SetTextColor(RGB(232, 245, 3));

	SCROLLINFO info;
	info.cbSize = 20;
	info.fMask = 3;
	info.nMax = 200;
	info.nMin  = 4;
	info.nPage = 1;
	info.nPos = 0;
	info.nTrackPos = 8;
	CRect windowRect;
	GetWindowRect(&windowRect);
	CWnd* pParent = GetParent();
	m_AppyUserList.Init(m_OrtRect,pParent);
	m_AppyUserList.m_viewHandle  = m_hWnd;

	//插入列表
	m_AppyUserList.InsertColumn(0,TEXT("申请玩家"),LVCFMT_LEFT,100);
	m_AppyUserList.InsertColumn(1,TEXT("银子"),LVCFMT_LEFT,100);

	return FALSE;
}

//插入列表
void CApplyUser::InserUser(tagApplyUser & ApplyUser)
{
	//变量定义
	WORD wListIndex=0;
	WORD wColumnCount=1;
	TCHAR szBuffer[256]=TEXT("");

	//游戏玩家
	INT nItemIndex=m_AppyUserList.InsertItem(m_AppyUserList.GetItemCount(),ApplyUser.strUserName);

	//玩家金币
	_snprintf(szBuffer,CountArray(szBuffer),TEXT("%I64d"),ApplyUser.lUserScore);
	m_AppyUserList.SetItem(nItemIndex,wColumnCount++,LVIF_TEXT,szBuffer,0,0,0,0);

	return;
}

//位置变化
void CApplyUser::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	//列表控件
	if (m_AppyUserList.m_hWnd!=NULL)
	{
		m_AppyUserList.MoveWindow(0,0,cx,cy);
	}

	return;
}

//删除列表
void CApplyUser::DeleteUser(tagApplyUser & ApplyUser)
{
	//构造变量
	LVFINDINFO lvFindInfo;
	ZeroMemory( &lvFindInfo, sizeof( lvFindInfo ) );
	lvFindInfo.flags = LVFI_STRING;
	lvFindInfo.psz = (LPCTSTR)ApplyUser.strUserName;

	//查找子项
	int nItem = m_AppyUserList.FindItem( &lvFindInfo );

	//删除子项
	if ( nItem != -1 ) m_AppyUserList.DeleteItem( nItem );
}

//更新列表
void CApplyUser::UpdateUser( tagApplyUser & ApplyUser )
{
		//构造变量
	LVFINDINFO lvFindInfo;
	ZeroMemory( &lvFindInfo, sizeof( lvFindInfo ) );
	lvFindInfo.flags = LVFI_STRING;
	lvFindInfo.psz = (LPCTSTR)ApplyUser.strUserName;

	//查找子项
	int nItem = m_AppyUserList.FindItem( &lvFindInfo );

	//删除子项
	if ( nItem != -1 ) 
	{
		TCHAR szBuffer[256]=TEXT("");

		//玩家金币
		_snprintf(szBuffer,CountArray(szBuffer),TEXT("%I64d"),ApplyUser.lUserScore);
		m_AppyUserList.SetItem(nItem,1,LVIF_TEXT,szBuffer,0,0,0,0);
	}
}

//清空列表
void CApplyUser::ClearAll()
{
	m_AppyUserList.DeleteAllItems();
}

int CApplyUser::GetItemCount()
{
	return m_AppyUserList.GetItemCount();
}

LRESULT CApplyUser::OnLBtUp( WPARAM wParam,LPARAM lParam )
{
	::SendMessage(m_viewHandle,WM_VIEWLBTUP,wParam,lParam);
	return 1;
}

//////////////////////////////////////////////////////////////////////////
