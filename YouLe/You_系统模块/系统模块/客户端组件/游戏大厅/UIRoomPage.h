#pragma once
#include "UIPngButton.h"

namespace YouLe
{
	/////////////////////////////////////////////////////////
	//房间构造
	////////////////////////////////////////////////////////
	class UIRoomItem : public UIWidget, public UIProcess
	{
	public:
		UIRoomItem(void);

		virtual ~UIRoomItem(void);

		// 创建控件
		virtual	BOOL		Create(INT nID, INT nDestX, INT nDestY, CWnd* pAttach, UIProcess* pProcess, UIWidget* pParent);
		// 绘制控件
		virtual BOOL		Draw(CDC* pDC);
	public:
		// 响应页控件
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);

	protected:
		CPngImage			m_PngBill;
		UIPngButton*		m_pJoinBtn; 

	public:
		tagGameServer*		m_pGameServer;
	};


	/////////////////////////////////////////////////////////
	//房间视图构造
	////////////////////////////////////////////////////////
	class UIRoomPage : public UIWidget, public UIProcess
	{
	public:
		UIRoomPage(void);

		virtual ~UIRoomPage(void);

		// 创建控件
		virtual	BOOL		Create(INT nID, const RECT& rect, CWnd* pAttach, 
			UIProcess* pProcess, UIWidget* pParent);
		
		// 绘制
		virtual BOOL		Draw(CDC* pDC);

	public:
		// 响应页控件
		virtual	BOOL		OnClicked(UIWidget* pWidget, const CPoint& cPt);

	public:
		// 
		UIRoomItem*			m_pRoomItem[MAX_GICOL*MAX_GIROW];
		// 返回按钮
		UIPngButton*		m_pBtBack;
		// 标题
		CPngImage			m_TilteImage;
		// 标题名称（游戏名字）
		TCHAR				szKindName[KIND_LEN];
	};


}