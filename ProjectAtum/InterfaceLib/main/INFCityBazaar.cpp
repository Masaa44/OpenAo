// INFCityBazaar.cpp: implementation of the CINFCityBazaar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AtumApplication.h"
#include "INFCityBazaar.h"
#include "INFCityBase.h"
#include "INFScrollbar.h"
#include "INFImage.h"
#include "D3dHanFont.h"
#include "ItemInfo.h"
#include "ShuttleChild.h"
#include "CharacterChild.h"				// 2005-07-21 by ispark
#include "FieldWinSocket.h"
#include "GameDataLast.h"
#include "StoreData.h"
#include "WeaponItemInfo.h"
#include "INFWindow.h"
#include "INFGameMain.h"
#include "INFItemInfo.h"
#include "RangeTime.h"
#include "INFInven.h"
#include "INFIcon.h"
#include "AtumDatabase.h"
#include "dxutil.h"
#include "Chat.h"
#include "INFComboBoxEX.h"
#include "Interface.h"
#include "INFGameMainChat.h"
#include "ChatTab_t.h"
#include "SceneData.h"
#include "EnemyData.h"
#include "AtumSound.h"
#include "ChatMoveData.h"
#include "INFImageEx.h"	 		
#include "INFGroupImage.h"					   // 2011. 10. 10 by jskim UI�ý��� ����
#include "INFGroupManager.h"				   // 2011. 10. 10 by jskim UI�ý��� ����
#include "INFToolTip.h"

#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	#define SHOP_ITEM_SLOT_NUMBER			5

	#define CITY_SHOP_START_X				(CITY_BASE_NPC_BOX_START_X + 230)
	#define CITY_SHOP_START_Y				(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y - 9)

	// 2006-08-29 by dgwoo 
	#define BAZAAR_SHOP_MINIBAR_W			210
	#define	BAZAAR_SHOP_MINIBAR_H			18
	#define BAZAAR_SHOP_MINIBAR_Y			(g_pD3dApp->GetBackBufferDesc().Height - 84 - BAZAAR_SHOP_MINIBAR_H)
	#define BAZAAR_SHOP_MINIBAR_X			((g_pD3dApp->GetBackBufferDesc().Width-BAZAAR_SHOP_MINIBAR_W))

	#define BAZAAR_SHOP_WINDOW_X			(CITY_SHOP_START_X + 194)
	#define BAZAAR_SHOP_WINDOW_Y			(CITY_SHOP_START_Y + 9)
	#define BAZAAR_SHOP_WINDOW_W			339
	#define BAZAAR_SHOP_WINDOW_H			275

	#define BAZAAR_SHOP_TAB_START_X			(BAZAAR_SHOP_WINDOW_X)
	#define BAZAAR_SHOP_TAB_START_Y			(BAZAAR_SHOP_WINDOW_Y + 20)
	#define BAZAAR_SHOP_TAB_W				98
	#define BAZAAR_SHOP_TAB_H				24
	#define BAZAAR_SHOP_TAB_BACK_W			316
	#define BAZAAR_SHOP_TAB_BACK_H			208

	#define BAZAAR_SHOP_OPEN_TOTAL_PRICE_X	(BAZAAR_SHOP_WINDOW_X + 35)
	#define BAZAAR_SHOP_OPEN_TOTAL_PRICE_Y	(BAZAAR_SHOP_WINDOW_Y + 326)
	#define BAZAAR_SHOP_OPEN_TOTAL_PRICE_W	166


	#define BAZAAR_OPEN_NAME_X				BAZAAR_SHOP_WINDOW_X + 34
	#define BAZAAR_OPEN_NAME_Y				BAZAAR_SHOP_WINDOW_Y + 38

	#define BAZAAR_SHOP_OPEN_START_X		(BAZAAR_SHOP_WINDOW_X + 314)
	#define BAZAAR_SHOP_OPEN_START_Y		(BAZAAR_SHOP_WINDOW_Y + 324)
	#define BAZAAR_SHOP_OPEN_STOP_X			(BAZAAR_SHOP_WINDOW_X + 353)
	#define BAZAAR_SHOP_OPEN_STOP_Y			BAZAAR_SHOP_OPEN_START_Y


	#define BAZAAR_SHOP_ITEM_X				(BAZAAR_SHOP_WINDOW_X + 35)
	#define BAZAAR_SHOP_ITEM_Y				(BAZAAR_SHOP_WINDOW_Y + 108)
	#define BAZAAR_SHOP_ITEM_W				340
	#define BAZAAR_SHOP_ITEM_H				38
	#define BAZAAR_SHOP_SELITEM_X			(BAZAAR_SHOP_WINDOW_X + 16)
	#define BAZAAR_SHOP_SELITEM_Y			(BAZAAR_SHOP_WINDOW_Y + 50)

	//�ּ�ȭ Ȱ��ȭ ��ư.
	#define	BAZAAR_SHOP_MIN_X				(BAZAAR_SHOP_WINDOW_X + 397)
	#define	BAZAAR_SHOP_MIN_Y				(BAZAAR_SHOP_WINDOW_Y + 5)
	#define BAZAAR_SHOP_ACT_X				(BAZAAR_SHOP_MINIBAR_X + 195)
	#define BAZAAR_SHOP_ACT_Y				(BAZAAR_SHOP_MINIBAR_Y + 3)
	#define	BAZAAR_SHOP_MIN_H				12
	#define BAZAAR_SHOP_MIN_W				10

	#define BAZAAR_SHOP_ICON_X				(BAZAAR_SHOP_ITEM_X + 10)
	#define BAZAAR_SHOP_ICON_Y				(BAZAAR_SHOP_ITEM_Y + 8)
	#define BAZAAR_SHOP_ICON_WH				28

	#define BAZAAR_SHOP_RIGHT_BTN_X			(BAZAAR_SHOP_WINDOW_X + 332)
	#define BAZAAR_SHOP_RIGHT_BTN_Y			(BAZAAR_SHOP_WINDOW_Y + 118)

	#define BAZAAR_SHOP_LOG_STRING_LENGTH	300
	#define BAZAAR_SHOP_LOG_X				(BAZAAR_SHOP_WINDOW_X + 48)
	#define BAZAAR_SHOP_LOG_Y				(BAZAAR_SHOP_WINDOW_Y + 115)
	#define BAZAAR_SHOP_LOG_LINE_COUNT		12

	//|-------------------------------------------------|
	//|		1	  			|			2		   	    |
	//|-------------------------------------------------|
	//|		3				|			4			    |
	//|-------------------------------------------------|

	#define BAZAAR_OPEN_1_BUY_X				(BAZAAR_SHOP_ITEM_X+50)
	#define BAZAAR_OPEN_1_SEL_X				(BAZAAR_SHOP_ITEM_X+90)
	#define BAZAAR_OPEN_1_Y					(BAZAAR_SHOP_ITEM_Y+7)
	#define BAZAAR_OPEN_1_BUY_W				85
	#define BAZAAR_OPEN_1_SEL_W				67
	#define BAZAAR_OPEN_1_H					13

	#define BAZAAR_OPEN_2_SEL_X				(BAZAAR_SHOP_ITEM_X+200)
	#define BAZAAR_OPEN_2_BUY_X				(BAZAAR_SHOP_ITEM_X+200)
	#define BAZAAR_OPEN_2_Y					(BAZAAR_SHOP_ITEM_Y+6)
	#define	BAZAAR_OPEN_2_SEL_W				85
	#define	BAZAAR_OPEN_2_BUY_W				BAZAAR_OPEN_2_SEL_W
	#define BAZAAR_OPEN_3_BUY_X				(BAZAAR_SHOP_ITEM_X+36)
	#define BAZAAR_OPEN_3_Y					(BAZAAR_SHOP_ITEM_Y+23)
	#define BAZAAR_OPEN_4_SEL_X				BAZAAR_OPEN_2_SEL_X
	#define BAZAAR_OPEN_4_BUY_X				BAZAAR_OPEN_2_SEL_X
	#define BAZAAR_OPEN_4_Y					(BAZAAR_SHOP_ITEM_Y+22)



	//�޺� �ڽ��� �����ϱ� ���� ������.
	#define BAZAAR_OPEN_1_ICON_X			(BAZAAR_SHOP_ITEM_X+158)
	#define BAZAAR_OPEN_1_ICON_Y			(BAZAAR_SHOP_ITEM_Y+9)
	#define BAZAAR_OPEN_1_ICON_W			124
	#define BAZAAR_OPEN_2_ICON_X			(BAZAAR_SHOP_ITEM_X+158)
	#define BAZAAR_OPEN_2_ICON_Y			(BAZAAR_SHOP_ITEM_Y+BAZAAR_OPEN_1_H+9)

	//�޺� �ڽ��� ������� �ڸ�.
	#define BAZAAR_OPEN_COMBO_KIND_X		BAZAAR_OPEN_1_X
	#define BAZAAR_OPEN_COMBO_KIND_Y		(BAZAAR_OPEN_1_Y+BAZAAR_OPEN_1_H)
	#define BAZAAR_OPEN_COMBO_NAME_X		BAZAAR_OPEN_1_X
	#define BAZAAR_OPEN_COMBO_NAME_Y		(BAZAAR_OPEN_1_Y+BAZAAR_OPEN_1_H+BAZAAR_OPEN_1_H)

	#define BAZAAR_SHOP_BTN_W				36
	#define BAZAAR_SHOP_BTN_H				19
	#define BAZAAR_SHOP_BTN_OUT_W			48

	#define BAZAAR_SHOP_SCROLL_MAX_LINE		(BAZAARSHOP_ITEMCOUNT - SHOP_ITEM_SLOT_NUMBER)
	#define BAZAAR_SHOP_OPEN_SCROLL_X		(BAZAAR_SHOP_WINDOW_X + 367)
	#define BAZAAR_SHOP_SCROLL_Y			(BAZAAR_SHOP_WINDOW_Y + 106)
	#define BAZAAR_SHOP_SCROLL_W			11
	#define BAZAAR_SHOP_SCROLL_H			23
	#define BAZAAR_SHOP_SCROLL_LINE_LENGTH	(192 - BAZAAR_SHOP_SCROLL_H)


	/*--------------------------------------------------------------------------*/
	//   Visit
	#define BAZAAR_VISIT_TOTAL_PRICE_X	(BAZAAR_SHOP_WINDOW_X + 35)
	#define BAZAAR_VISIT_TOTAL_PRICE_Y	(BAZAAR_SHOP_WINDOW_Y + 326)
	#define BAZAAR_VISIT_TOTAL_PRICE_W	169

	#define	BAZAAR_VISIT_TEXT_H             13

	#define BAZAAR_VISIT_NAME_X				(BAZAAR_SHOP_ITEM_X+43)
	#define BAZAAR_VISIT_NAME_Y				(BAZAAR_SHOP_ITEM_Y+6)
	#define BAZAAR_VISIT_NAME_W				208

	#define BAZAAR_VISIT_OUT_X				(BAZAAR_SHOP_WINDOW_X + 353)
	#define BAZAAR_VISIT_OUT_Y				BAZAAR_SHOP_OPEN_START_Y

	#define BAZAAR_SHOP_VISIT_SCROLL_X			(BAZAAR_SHOP_TAB_START_X + 367)

	//SEL
	#define	BAZAAR_VISIT_SEL_PRICE_X		(BAZAAR_SHOP_ITEM_X+82)
	#define	BAZAAR_VISIT_SEL_PRICE_Y		(BAZAAR_SHOP_ITEM_Y+21)
	#define	BAZAAR_VISIT_SEL_PRICE_W		85

	#define BAZAAR_VISIT_SEL_COUNT_X		(BAZAAR_SHOP_ITEM_X+222)
	#define BAZAAR_VISIT_SEL_COUNT_Y		(BAZAAR_SHOP_ITEM_Y+21)
	#define BAZAAR_VISIT_SEL_COUNT_W		64

	#define BAZAAR_VISIT_SEL_ITEM_COUNT_X	(BAZAAR_SHOP_ICON_X + 25)
	#define BAZAAR_VISIT_SEL_ITEM_COUNT_Y	BAZAAR_SHOP_ICON_Y - 2

	//BUY
	#define	BAZAAR_VISIT_BUY_PRICE_X		(BAZAAR_SHOP_ITEM_X+80)
	#define	BAZAAR_VISIT_BUY_PRICE_Y		(BAZAAR_SHOP_ITEM_Y+21)
	#define	BAZAAR_VISIT_BUY_PRICE_W		70

	#define BAZAAR_VISIT_BUY_COUNT_X		(BAZAAR_SHOP_ITEM_X+223)
	#define BAZAAR_VISIT_BUY_COUNT_Y		(BAZAAR_SHOP_ITEM_Y+21)
	#define BAZAAR_VISIT_BUY_COUNT_W		64

	#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
	#define STRING_CULL ::StringCullingUserData_ToBlank
	#else
	#define STRING_CULL ::StringCullingUserDataEx
	#endif
#else
#define CITY_SHOP_START_X				(CITY_BASE_NPC_BOX_START_X + 230)
#define CITY_SHOP_START_Y				(CITY_BASE_NPC_BOX_START_Y - SIZE_NORMAL_WINDOW_Y - 9)

// 2006-08-29 by dgwoo 
#define BAZAAR_SHOP_MINIBAR_W			210
#define	BAZAAR_SHOP_MINIBAR_H			18
#define BAZAAR_SHOP_MINIBAR_Y			(g_pD3dApp->GetBackBufferDesc().Height - 39 - BAZAAR_SHOP_MINIBAR_H)
#define BAZAAR_SHOP_MINIBAR_X			((g_pD3dApp->GetBackBufferDesc().Width-BAZAAR_SHOP_MINIBAR_W))

#define BAZAAR_SHOP_WINDOW_X			(CITY_SHOP_START_X + 194)
#define BAZAAR_SHOP_WINDOW_Y			(CITY_SHOP_START_Y + 9)
#define BAZAAR_SHOP_WINDOW_W			339
#define BAZAAR_SHOP_WINDOW_H			275

#define BAZAAR_SHOP_TAB_START_X			(BAZAAR_SHOP_WINDOW_X + 11)
#define BAZAAR_SHOP_TAB_START_Y			(BAZAAR_SHOP_WINDOW_Y + 30)
#define BAZAAR_SHOP_TAB_W				46
#define BAZAAR_SHOP_TAB_H				14
#define BAZAAR_SHOP_TAB_BACK_W			316
#define BAZAAR_SHOP_TAB_BACK_H			208

#define BAZAAR_SHOP_OPEN_TOTAL_PRICE_X	(BAZAAR_SHOP_WINDOW_X + 181)
#define BAZAAR_SHOP_OPEN_TOTAL_PRICE_Y	(BAZAAR_SHOP_WINDOW_Y + 22)
#define BAZAAR_SHOP_OPEN_TOTAL_PRICE_W	132


#define BAZAAR_OPEN_NAME_X				BAZAAR_VISIT_TOTAL_PRICE_X
#define BAZAAR_OPEN_NAME_Y				BAZAAR_VISIT_TOTAL_PRICE_Y

#define BAZAAR_SHOP_OPEN_START_X		(BAZAAR_SHOP_WINDOW_X + 253)
#define BAZAAR_SHOP_OPEN_START_Y		(BAZAAR_SHOP_WINDOW_Y + 243)
#define BAZAAR_SHOP_OPEN_STOP_X			(BAZAAR_SHOP_WINDOW_X + 292)
#define BAZAAR_SHOP_OPEN_STOP_Y			BAZAAR_SHOP_OPEN_START_Y


#define BAZAAR_SHOP_ITEM_X				(BAZAAR_SHOP_WINDOW_X + 17)
#define BAZAAR_SHOP_ITEM_Y				(BAZAAR_SHOP_WINDOW_Y + 51)
#define BAZAAR_SHOP_ITEM_W				290
#define BAZAAR_SHOP_ITEM_H				36
#define BAZAAR_SHOP_SELITEM_X			(BAZAAR_SHOP_WINDOW_X + 16)
#define BAZAAR_SHOP_SELITEM_Y			(BAZAAR_SHOP_WINDOW_Y + 50)

//�ּ�ȭ Ȱ��ȭ ��ư.
#define	BAZAAR_SHOP_MIN_X				(BAZAAR_SHOP_WINDOW_X + 316)
#define	BAZAAR_SHOP_MIN_Y				(BAZAAR_SHOP_WINDOW_Y + 5)
#define BAZAAR_SHOP_ACT_X				(BAZAAR_SHOP_MINIBAR_X + 195)
#define BAZAAR_SHOP_ACT_Y				(BAZAAR_SHOP_MINIBAR_Y + 4)
#define	BAZAAR_SHOP_MIN_H				12
#define BAZAAR_SHOP_MIN_W				10

#define BAZAAR_SHOP_ICON_X				(BAZAAR_SHOP_ITEM_X + 4)
#define BAZAAR_SHOP_ICON_Y				(BAZAAR_SHOP_ITEM_Y + 4)
#define BAZAAR_SHOP_ICON_WH				28

#define BAZAAR_SHOP_RIGHT_BTN_X			(BAZAAR_SHOP_WINDOW_X + 267)
#define BAZAAR_SHOP_RIGHT_BTN_Y			(BAZAAR_SHOP_WINDOW_Y + 60)

#define BAZAAR_SHOP_LOG_STRING_LENGTH	282
#define BAZAAR_SHOP_LOG_X				(BAZAAR_SHOP_WINDOW_X + 21)
#define BAZAAR_SHOP_LOG_Y				(BAZAAR_SHOP_WINDOW_Y + 51)
#define BAZAAR_SHOP_LOG_LINE_COUNT		12

//|-------------------------------------------------|
//|		1	  			|			2		   	    |
//|-------------------------------------------------|
//|		3				|			4			    |
//|-------------------------------------------------|

#define BAZAAR_OPEN_1_BUY_X				(BAZAAR_SHOP_ITEM_X+40)
#define BAZAAR_OPEN_1_SEL_X				(BAZAAR_SHOP_ITEM_X+62)
#define BAZAAR_OPEN_1_Y					(BAZAAR_SHOP_ITEM_Y+2)
#define BAZAAR_OPEN_1_BUY_W				75
#define BAZAAR_OPEN_1_SEL_W				67
#define BAZAAR_OPEN_1_H					13

#define BAZAAR_OPEN_2_SEL_X				(BAZAAR_SHOP_ITEM_X+160)
#define BAZAAR_OPEN_2_BUY_X				(BAZAAR_SHOP_ITEM_X+161)
#define BAZAAR_OPEN_2_Y					(BAZAAR_SHOP_ITEM_Y+2)
#define	BAZAAR_OPEN_2_SEL_W				85
#define	BAZAAR_OPEN_2_BUY_W				BAZAAR_OPEN_2_SEL_W
#define BAZAAR_OPEN_3_BUY_X				(BAZAAR_SHOP_ITEM_X+40)
#define BAZAAR_OPEN_3_Y					(BAZAAR_SHOP_ITEM_Y+16)
#define BAZAAR_OPEN_4_SEL_X				BAZAAR_OPEN_2_SEL_X
#define BAZAAR_OPEN_4_BUY_X				BAZAAR_OPEN_2_SEL_X
#define BAZAAR_OPEN_4_Y					(BAZAAR_SHOP_ITEM_Y+16)



//�޺� �ڽ��� �����ϱ� ���� ������.
#define BAZAAR_OPEN_1_ICON_X			(BAZAAR_SHOP_ITEM_X+118)
#define BAZAAR_OPEN_1_ICON_Y			(BAZAAR_SHOP_ITEM_Y+7)
#define BAZAAR_OPEN_1_ICON_W			100
#define BAZAAR_OPEN_2_ICON_X			(BAZAAR_SHOP_ITEM_X+118)
#define BAZAAR_OPEN_2_ICON_Y			(BAZAAR_SHOP_ITEM_Y+BAZAAR_OPEN_1_H+8)

//�޺� �ڽ��� ������� �ڸ�.
#define BAZAAR_OPEN_COMBO_KIND_X		BAZAAR_OPEN_1_X
#define BAZAAR_OPEN_COMBO_KIND_Y		(BAZAAR_OPEN_1_Y+BAZAAR_OPEN_1_H)
#define BAZAAR_OPEN_COMBO_NAME_X		BAZAAR_OPEN_1_X
#define BAZAAR_OPEN_COMBO_NAME_Y		(BAZAAR_OPEN_1_Y+BAZAAR_OPEN_1_H+BAZAAR_OPEN_1_H)

#define BAZAAR_SHOP_BTN_W				36
#define BAZAAR_SHOP_BTN_H				19
#define BAZAAR_SHOP_BTN_OUT_W			48

#define BAZAAR_SHOP_SCROLL_MAX_LINE		(BAZAARSHOP_ITEMCOUNT - SHOP_ITEM_SLOT_NUMBER)
#define BAZAAR_SHOP_OPEN_SCROLL_X		(BAZAAR_SHOP_TAB_START_X + 301)
#define BAZAAR_SHOP_SCROLL_Y			(BAZAAR_SHOP_WINDOW_Y + 52)
#define BAZAAR_SHOP_SCROLL_W			11
#define BAZAAR_SHOP_SCROLL_H			38
#define BAZAAR_SHOP_SCROLL_LINE_LENGTH	(181 - BAZAAR_SHOP_SCROLL_H)


/*--------------------------------------------------------------------------*/
//   Visit
#define BAZAAR_VISIT_TOTAL_PRICE_X	(BAZAAR_SHOP_WINDOW_X + 11)
#define BAZAAR_VISIT_TOTAL_PRICE_Y	(BAZAAR_SHOP_WINDOW_Y + 243)
#define BAZAAR_VISIT_TOTAL_PRICE_W	230

#define	BAZAAR_VISIT_TEXT_H             13

#define BAZAAR_VISIT_NAME_X				(BAZAAR_SHOP_ITEM_X+38)
#define BAZAAR_VISIT_NAME_Y				(BAZAAR_SHOP_ITEM_Y+2)
#define BAZAAR_VISIT_NAME_W				208

#define BAZAAR_VISIT_OUT_X				(BAZAAR_SHOP_WINDOW_X + 279)
#define BAZAAR_VISIT_OUT_Y				BAZAAR_SHOP_OPEN_START_Y

#define BAZAAR_SHOP_VISIT_SCROLL_X			(BAZAAR_SHOP_TAB_START_X + 300)

//SEL
#define	BAZAAR_VISIT_SEL_PRICE_X		(BAZAAR_SHOP_ITEM_X+66)
#define	BAZAAR_VISIT_SEL_PRICE_Y		(BAZAAR_SHOP_ITEM_Y+17)
#define	BAZAAR_VISIT_SEL_PRICE_W		85

#define BAZAAR_VISIT_SEL_COUNT_X		(BAZAAR_SHOP_ITEM_X+201)
#define BAZAAR_VISIT_SEL_COUNT_Y		(BAZAAR_SHOP_ITEM_Y+17)
#define BAZAAR_VISIT_SEL_COUNT_W		45

#define BAZAAR_VISIT_SEL_ITEM_COUNT_X	(BAZAAR_SHOP_ICON_X + 25)
#define BAZAAR_VISIT_SEL_ITEM_COUNT_Y	BAZAAR_SHOP_ICON_Y

//BUY
#define	BAZAAR_VISIT_BUY_PRICE_X		(BAZAAR_SHOP_ITEM_X+67)
#define	BAZAAR_VISIT_BUY_PRICE_Y		(BAZAAR_SHOP_ITEM_Y+17)
#define	BAZAAR_VISIT_BUY_PRICE_W		70

#define BAZAAR_VISIT_BUY_COUNT_X		(BAZAAR_SHOP_ITEM_X+182)
#define BAZAAR_VISIT_BUY_COUNT_Y		(BAZAAR_SHOP_ITEM_Y+17)
#define BAZAAR_VISIT_BUY_COUNT_W		64

#if defined(LANGUAGE_ENGLISH) || defined(LANGUAGE_VIETNAM)|| defined(LANGUAGE_THAI)// 2008-04-30 by bhsohn �±� ���� �߰�
#define STRING_CULL ::StringCullingUserData_ToBlank
#else
#define STRING_CULL ::StringCullingUserDataEx
#endif
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CINFCityBazaar::CINFCityBazaar()
{
	m_pGameData			= NULL;
	m_byBazaarType		= 0;
	m_byBazaarTypeState	= 0;

	m_bLButtonDown		= FALSE;
	m_bScrollLock		= FALSE;

	m_nScrollBtn		= 0;

	m_bBazaarShopStart  = FALSE;
	m_bBazaarShopEnd	= FALSE;

	g_pInterface->SetWindowOrder(WNDBazaarShop);
}

CINFCityBazaar::~CINFCityBazaar()
{

}

int CINFCityBazaar::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return INF_MSGPROC_NORMAL;
}

int CINFCityBazaar::GetShopItemCount(UID64_t itemUID)
{
	return 0;
}

CItemInfo *	CINFCityBazaar::GetShopItemInfo(UID64_t itemUID)
{
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
int	CINFCityBazaar::GetScrollLine()
{
	int ntemp = m_nScrollMaxCount - m_nScrollMaxLine;

	if(ntemp < 0)
	{
		ntemp = 0;
	}
	return ntemp;
}

int	CINFCityBazaar::GetScrollLineNumber(float nLength)
{
	int ntemp = GetScrollLine();
	float fLineNum = (nLength * ntemp) / BAZAAR_SHOP_SCROLL_LINE_LENGTH;

	return (int)fLineNum;
}

float CINFCityBazaar::GetScrollLineInterval(int nScrollLineNum)
{
	int ntemp = GetScrollLine();
	float fLineNum = 0.0f;
	if(ntemp)
		fLineNum = (BAZAAR_SHOP_SCROLL_LINE_LENGTH * nScrollLineNum) / ntemp;

	return fLineNum;
}

void CINFCityBazaar::SetScrollEndLine()
{
	m_nScrollPosition = 0;
	m_nScrollLine = GetScrollLine();
	if(m_nScrollLine)
		m_nScrollPosition = BAZAAR_SHOP_SCROLL_LINE_LENGTH;
}

void CINFCityBazaar::InitScrollLine()
{
	m_nScrollPosition = 0;
	m_nScrollLine = 0;
}

///////////////////////////////////////////////////////////////////////////////
/// \class		void CINFCityBazaar::UnderBarDrawText(CD3DHanFont *pHanFont,FLOAT sx,FLOAT sy,DWORD dwColor,TCHAR* strText,DWORD dwFlags)
/// \brief		����ٰ� �ڵ����� �����Ǵ� �Լ�
///
/// \author		dgwoo
/// \version	
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaar::UnderBarDrawText(CD3DHanFont *pHanFont,FLOAT sx,FLOAT sy,DWORD dwColor,TCHAR* strText,DWORD dwFlags)
{
	char buftemp[256] = {0,};

	wsprintf(buftemp,"%s_",strText);
	pHanFont->DrawText(sx,sy,dwColor,buftemp,dwColor);
	return ;
}
BOOL CINFCityBazaar::GetPointInType(POINT &pt,int type,int Num)
{
	
	// visit buy
	//--------------------------------------------------------------------------
	if(type == BAZAAR_VISIT_BUY_COUNT)
	{
		if(pt.x > BAZAAR_VISIT_BUY_COUNT_X &&
			pt.x < BAZAAR_VISIT_BUY_COUNT_X +BAZAAR_VISIT_BUY_COUNT_W &&
			pt.y > BAZAAR_VISIT_BUY_COUNT_Y + (BAZAAR_SHOP_ITEM_H * Num) &&
			pt.y < BAZAAR_VISIT_BUY_COUNT_Y + (BAZAAR_SHOP_ITEM_H * Num) + BAZAAR_VISIT_TEXT_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_BTN)
	{
		if(	pt.x >= BAZAAR_SHOP_RIGHT_BTN_X &&
				pt.x <= BAZAAR_SHOP_RIGHT_BTN_X + BAZAAR_SHOP_BTN_W &&
				pt.y >= BAZAAR_SHOP_RIGHT_BTN_Y + (Num * BAZAAR_SHOP_ITEM_H) &&
				pt.y <= BAZAAR_SHOP_RIGHT_BTN_Y + (Num * BAZAAR_SHOP_ITEM_H)+ BAZAAR_SHOP_BTN_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_BTN_VISIT_OUT)
	{
		if(pt.x >= BAZAAR_VISIT_OUT_X &&
			pt.x <= BAZAAR_VISIT_OUT_X + BAZAAR_SHOP_BTN_OUT_W &&
			pt.y >= BAZAAR_VISIT_OUT_Y &&
			pt.y <= BAZAAR_VISIT_OUT_Y + BAZAAR_SHOP_BTN_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	// visit sell
	//--------------------------------------------------------------------------
	else if(type == BAZAAR_ICON)
	{
		if(pt.x >= BAZAAR_SHOP_ICON_X &&
				pt.x <= BAZAAR_SHOP_ICON_X + BAZAAR_SHOP_ICON_WH &&
				pt.y >= BAZAAR_SHOP_ITEM_Y &&
				pt.y <= BAZAAR_SHOP_ITEM_Y + (BAZAAR_SHOP_ITEM_H * SHOP_ITEM_SLOT_NUMBER))
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_VISIT_SEL_COUNT)
	{
		if(pt.x > BAZAAR_VISIT_SEL_COUNT_X &&
					pt.x < BAZAAR_VISIT_SEL_COUNT_X +BAZAAR_VISIT_SEL_COUNT_W &&
					pt.y > BAZAAR_VISIT_SEL_COUNT_Y + (BAZAAR_SHOP_ITEM_H * Num) &&
					pt.y < BAZAAR_VISIT_SEL_COUNT_Y + (BAZAAR_SHOP_ITEM_H * Num) + BAZAAR_VISIT_TEXT_H)
		{
			return TRUE;	
		}
		return FALSE;
	}
	// open buy
	//--------------------------------------------------------------------------
	else if(type == BAZAAR_OPEN_1_BUY)
	{
		if( pt.x > BAZAAR_OPEN_1_BUY_X &&
					pt.x < BAZAAR_OPEN_1_BUY_X + BAZAAR_OPEN_1_ICON_W &&
					pt.y > BAZAAR_OPEN_1_Y + (BAZAAR_SHOP_ITEM_H * Num)&&
					pt.y < BAZAAR_OPEN_1_Y + (BAZAAR_SHOP_ITEM_H * Num) + BAZAAR_OPEN_1_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_OPEN_3_BUY)
	{
		if(pt.x > BAZAAR_OPEN_3_BUY_X &&
					pt.x < BAZAAR_OPEN_3_BUY_X + BAZAAR_OPEN_1_ICON_W &&
					pt.y > BAZAAR_OPEN_3_Y + (BAZAAR_SHOP_ITEM_H *Num)&&
					pt.y < BAZAAR_OPEN_3_Y + (BAZAAR_SHOP_ITEM_H *Num) + BAZAAR_OPEN_1_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_OPEN_2_BUY)
	{
		if(pt.x > BAZAAR_OPEN_2_BUY_X &&
					pt.x < BAZAAR_OPEN_2_BUY_X + BAZAAR_OPEN_1_BUY_W &&
					pt.y > BAZAAR_OPEN_2_Y + (BAZAAR_SHOP_ITEM_H *Num)&&
					pt.y < BAZAAR_OPEN_2_Y + (BAZAAR_SHOP_ITEM_H *Num) + BAZAAR_OPEN_1_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_OPEN_4_BUY)
	{
		if(pt.x > BAZAAR_OPEN_4_BUY_X &&
					pt.x < BAZAAR_OPEN_4_BUY_X + BAZAAR_OPEN_1_BUY_W &&
					pt.y > BAZAAR_OPEN_4_Y + (BAZAAR_SHOP_ITEM_H *Num)&&
					pt.y < BAZAAR_OPEN_4_Y + (BAZAAR_SHOP_ITEM_H *Num) + BAZAAR_OPEN_1_H)
	{
			return TRUE;
		}
		return FALSE;
	}
	// open sell
	//--------------------------------------------------------------------------
	else if(type == BAZAAR_OPEN_2_SEL)
	{
		if(pt.x > BAZAAR_OPEN_2_SEL_X &&
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
					pt.x < BAZAAR_OPEN_2_SEL_X + BAZAAR_OPEN_2_SEL_W &&
#else 
					pt.x < BAZAAR_OPEN_2_SEL_X + BAZAAR_OPEN_1_SEL_W &&
#endif
					pt.y > BAZAAR_OPEN_2_Y + (BAZAAR_SHOP_ITEM_H * Num)&&
					pt.y < BAZAAR_OPEN_2_Y + (BAZAAR_SHOP_ITEM_H * Num) + BAZAAR_OPEN_1_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_OPEN_3_SEL)
	{
		if(pt.x > BAZAAR_OPEN_1_SEL_X &&
					pt.x < BAZAAR_OPEN_1_SEL_X + BAZAAR_OPEN_1_SEL_W &&
					pt.y > BAZAAR_OPEN_3_Y + (BAZAAR_SHOP_ITEM_H * Num)&&
					pt.y < BAZAAR_OPEN_3_Y + (BAZAAR_SHOP_ITEM_H * Num) + BAZAAR_OPEN_1_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	//�׿� ������ ��ġ�� ��ư��..
	//--------------------------------------------------------------------------//
	else if(type == BAZAAR_SHOP_WINDOW)
	{
		if(pt.x >= BAZAAR_SHOP_WINDOW_X &&
				pt.x <= BAZAAR_SHOP_WINDOW_X + BAZAAR_SHOP_WINDOW_W &&
				pt.y >= BAZAAR_SHOP_WINDOW_Y &&
				pt.y <= BAZAAR_SHOP_WINDOW_Y + BAZAAR_SHOP_WINDOW_H)
		{
			return TRUE;
		}
		return FALSE;
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	}else if(type == BAZAAR_SHOP_TAB)
	{
		if(pt.x >= (BAZAAR_SHOP_TAB_START_X + 31 + (Num * BAZAAR_SHOP_TAB_W)) && 
			pt.x <= (BAZAAR_SHOP_TAB_START_X + 31 + ((Num + 1) * BAZAAR_SHOP_TAB_W)) &&
			pt.y >= BAZAAR_SHOP_TAB_START_Y + 55 && 
			pt.y <= BAZAAR_SHOP_TAB_START_Y + 55 + BAZAAR_SHOP_TAB_H)
		{
			return TRUE;
		}
		return FALSE;
	}
#else
	}else if(type == BAZAAR_SHOP_TAB)
	{
		if(pt.x >= (BAZAAR_SHOP_TAB_START_X + (Num * BAZAAR_SHOP_TAB_W)) && 
					pt.x <= (BAZAAR_SHOP_TAB_START_X + ((Num + 1) * BAZAAR_SHOP_TAB_W)) &&
					pt.y >= BAZAAR_SHOP_TAB_START_Y && 
					pt.y <= BAZAAR_SHOP_TAB_START_Y + BAZAAR_SHOP_TAB_H)
		{
			return TRUE;
		}
		return FALSE;
	}
#endif

	else if(type == BAZAAR_SHOP_SCROLL)
	{
		if(pt.x >= BAZAAR_SHOP_OPEN_SCROLL_X &&
				pt.x <= BAZAAR_SHOP_OPEN_SCROLL_X + BAZAAR_SHOP_SCROLL_W &&
				pt.y >= BAZAAR_SHOP_SCROLL_Y + Num &&
				pt.y <= BAZAAR_SHOP_SCROLL_Y + Num + BAZAAR_SHOP_SCROLL_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_VISIT_SCROLL)
	{
		if(pt.x >= BAZAAR_SHOP_VISIT_SCROLL_X &&
				pt.x <= BAZAAR_SHOP_VISIT_SCROLL_X + BAZAAR_SHOP_SCROLL_W &&
				pt.y >= BAZAAR_SHOP_SCROLL_Y + Num &&
				pt.y <= BAZAAR_SHOP_SCROLL_Y + Num + BAZAAR_SHOP_SCROLL_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_TAB_WHEEL)
	{
		if(pt.x >= BAZAAR_SHOP_TAB_START_X &&
				pt.x <= BAZAAR_SHOP_TAB_START_X + BAZAAR_SHOP_TAB_BACK_W &&
				pt.y >= BAZAAR_SHOP_TAB_START_Y &&
				pt.y <= BAZAAR_SHOP_TAB_START_Y + BAZAAR_SHOP_TAB_BACK_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_OPEN_START)
	{
		if(pt.x >= BAZAAR_SHOP_OPEN_START_X &&
				pt.x <= BAZAAR_SHOP_OPEN_START_X + BAZAAR_SHOP_BTN_W &&
				pt.y >= BAZAAR_SHOP_OPEN_START_Y  &&
				pt.y <= BAZAAR_SHOP_OPEN_START_Y + BAZAAR_SHOP_BTN_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_OPEN_STOP)
	{
		if(pt.x >= BAZAAR_SHOP_OPEN_STOP_X &&
					pt.x <= BAZAAR_SHOP_OPEN_STOP_X + BAZAAR_SHOP_BTN_W &&
					pt.y >= BAZAAR_SHOP_OPEN_STOP_Y &&
					pt.y <= BAZAAR_SHOP_OPEN_STOP_Y + BAZAAR_SHOP_BTN_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_ITEM)
	{
		if(pt.x >= BAZAAR_SHOP_ITEM_X &&
					pt.x <= BAZAAR_SHOP_ITEM_X + BAZAAR_SHOP_ITEM_W &&
					pt.y >= BAZAAR_SHOP_ITEM_Y + (Num * BAZAAR_SHOP_ITEM_H)&&
					pt.y <= BAZAAR_SHOP_ITEM_Y + ((Num + 1) * BAZAAR_SHOP_ITEM_H))
		{
			return TRUE;
		}
		return FALSE;
	}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	else if(type == BAZAAR_OPEN_NAME)
	{
		if(pt.x >= BAZAAR_OPEN_NAME_X + 51 &&
			pt.x <= BAZAAR_OPEN_NAME_X + 346 &&
			pt.y >= BAZAAR_OPEN_NAME_Y &&
			pt.y <= BAZAAR_OPEN_NAME_Y + 21)
		{
			return TRUE;
		}
		return FALSE;
	}
#else
	else if(type == BAZAAR_OPEN_NAME)
	{
		if(pt.x >= BAZAAR_OPEN_NAME_X + 38 &&
					pt.x <= BAZAAR_OPEN_NAME_X + 231 &&
					pt.y >= BAZAAR_OPEN_NAME_Y &&
					pt.y <= BAZAAR_OPEN_NAME_Y + 18)
		{
			return TRUE;
		}
		return FALSE;
	}
#endif
	else if(type == BAZAAR_SHOP_ITEM_AREA)
	{
		if(pt.x > BAZAAR_SHOP_ITEM_X &&
				pt.x < BAZAAR_SHOP_ITEM_X + BAZAAR_SHOP_ITEM_W &&
				pt.y > BAZAAR_SHOP_ITEM_Y &&
				pt.y < BAZAAR_SHOP_ITEM_Y + BAZAAR_SHOP_ITEM_H * SHOP_ITEM_SLOT_NUMBER)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_MIN)
	{
		if(pt.x > BAZAAR_SHOP_MIN_X &&
				pt.x < BAZAAR_SHOP_MIN_X + BAZAAR_SHOP_MIN_W &&
				pt.y > BAZAAR_SHOP_MIN_Y &&
				pt.y < BAZAAR_SHOP_MIN_Y + BAZAAR_SHOP_MIN_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	else if(type == BAZAAR_SHOP_ACT)
	{
		if(pt.x > BAZAAR_SHOP_MINIBAR_X &&
				pt.x < BAZAAR_SHOP_MINIBAR_X + BAZAAR_SHOP_MINIBAR_W &&
				pt.y > BAZAAR_SHOP_MINIBAR_Y &&
				pt.y < BAZAAR_SHOP_MINIBAR_Y + BAZAAR_SHOP_MINIBAR_H)
		{
			return TRUE;
		}
		return FALSE;
	}
	
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::SetItemInfo(CItemInfo* pSelectItem, int x, int y)
/// \brief		������ ���� �����ֱ�
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaar::SetItemInfo(CItemInfo* pSelectItem, int x, int y)
{
	if(m_pCurrentItemInfo != pSelectItem) 
	{
		if(pSelectItem) 
		{
			// 2009-02-03 by bhsohn ���� ������ �� ����
			//g_pGameMain->m_pItemInfo->SetItemInfoUser( pSelectItem, x, y );
			g_pGameMain->SetItemInfoUser( pSelectItem, x, y );
			// end 2009-02-03 by bhsohn ���� ������ �� ����
		}
		else 
		{
			g_pGameMain->SetItemInfo( 0, 0, 0, 0); 
		}
		m_pCurrentItemInfo = pSelectItem;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::InitVisitData()
/// \brief		
/// \author		// 2007-11-01 by bhsohn ���� �̿��߿� ���� ó��
/// \date		2007-11-01 ~ 2007-11-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void	CINFCityBazaar::CloseVisitShop()
{

}

//////////////////////////////////////////////////////////////////////////
// ���� ���� ������
CINFCityBazaarOpen::CINFCityBazaarOpen(CAtumNode* pParent, CGameData* pGameData, int nBazaarType)
{
	m_pParent			= pParent;	// CGameMain*
	m_pGameData			= pGameData;

	m_byBazaarType		= nBazaarType;
	m_byTabIndex		= 0;

	m_nStartBtnState	= BTN_STATE_NORMAL;
	m_nStopBtnState		= BTN_STATE_NORMAL;
	m_nOutBtnState		= BTN_STATE_NORMAL;
	m_nMinBtnState		= BTN_STATE_NORMAL;

	m_byFocusText		= TEXT_NON;
	m_nScrollPosition	= 0;
	m_nScrollLine		= 0;
	m_nSelectIndex		= -1;

	memset(m_nComboState,0,sizeof(m_nComboState));

	m_nTotal			= 0;

	// �ʱ�
	m_nScrollMaxCount	= BAZAARSHOP_ITEMCOUNT;
	m_nScrollMaxLine	= SHOP_ITEM_SLOT_NUMBER;

	m_ClientIndex		= 0;
	m_nComboActive		= 0;
	m_nLogMaxCount		= 0;

	m_byBazaarTypeState	= 1;
	m_bSelectItem		= FALSE;
//	m_bBazaarMinAct		= FALSE;
	m_bBazaarMinAct		= TRUE;

	POINT pt;
	pt.x = pt.y = 0;
	SetSelectItem(NULL, pt);
}

CINFCityBazaarOpen::~CINFCityBazaarOpen()
{

}

HRESULT CINFCityBazaarOpen::InitDeviceObjects()
{
	int i;
	char buf[16] = {0,};
	DataHeader	* pDataHeader;
	
	CheckBtnState();
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	pDataHeader = g_pGameMain->m_GruopImagemanager->FindResource("Psh");
	m_pBackWindow = g_pGameMain->m_GruopImagemanager->GetGroupImage( pDataHeader );
	m_pBackWindow->InitDeviceObjects( g_pD3dApp->m_pImageList );

	m_pSelectBar = new CINFImageEx;
	pDataHeader = FindResource("Selitem");
	m_pSelectBar->InitDeviceObjects(pDataHeader );
#else
	m_pBackWindow = new CINFImageEx;
	wsprintf(buf,"sellback");
	pDataHeader = FindResource(buf);
	m_pBackWindow->InitDeviceObjects(pDataHeader );
#endif
	for(i = 0 ; i < 4; i++)
	{
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
		//��� ��ư
		m_pDelItemBtn[i] = new CINFImageEx;
		wsprintf(buf, "cans0%d",i);
		pDataHeader = FindResource(buf);
		m_pDelItemBtn[i]->InitDeviceObjects(pDataHeader );
		
		//��� ��ư
		m_pPutItemBtn[i] = new CINFImageEx;
		wsprintf(buf, "Oapp%d",i);
		pDataHeader = FindResource(buf);
		m_pPutItemBtn[i]->InitDeviceObjects(pDataHeader );
		
		//���� ��ư.
		m_pStartBtn[i] = new CINFImageEx;
		wsprintf(buf, "oks0%d",i);
		pDataHeader = FindResource(buf);
		m_pStartBtn[i]->InitDeviceObjects(pDataHeader );

		//�ߴ� ��ư.
		m_pStopBtn[i] = new CINFImageEx;
		wsprintf(buf, "cans0%d",i);
		pDataHeader = FindResource(buf);
		m_pStopBtn[i]->InitDeviceObjects(pDataHeader );
	
		//�ּ�ȭ.
		m_pMinBtn[i] = new CINFImageEx;
		pDataHeader = FindResource("w_wMin");
		m_pMinBtn[i]->InitDeviceObjects( pDataHeader );

		//Ȱ��ȭ.
		m_pActBtn[i] = new CINFImageEx;
		pDataHeader = FindResource("w_wMax");
		m_pActBtn[i]->InitDeviceObjects(pDataHeader );
#else
		//��� ��ư
		m_pDelItemBtn[i] = new CINFImageEx;
		wsprintf(buf, "canBtn_%d",i);
		pDataHeader = FindResource(buf);
		m_pDelItemBtn[i]->InitDeviceObjects(pDataHeader );

		//��� ��ư
		m_pPutItemBtn[i] = new CINFImageEx;
		wsprintf(buf, "putBtn_%d",i);
		pDataHeader = FindResource(buf);
		m_pPutItemBtn[i]->InitDeviceObjects(pDataHeader );

		//���� ��ư.
		m_pStartBtn[i] = new CINFImageEx;
		wsprintf(buf, "startBtn_%d",i);
		pDataHeader = FindResource(buf);
		m_pStartBtn[i]->InitDeviceObjects(pDataHeader );

		//�ߴ� ��ư.
		m_pStopBtn[i] = new CINFImageEx;
		wsprintf(buf, "stopBtn_%d",i);
		pDataHeader = FindResource(buf);
		m_pStopBtn[i]->InitDeviceObjects(pDataHeader );
	
		//�ּ�ȭ.
		m_pMinBtn[i] = new CINFImageEx;
		wsprintf(buf,"c_down0%d",i);
		pDataHeader = FindResource(buf);
		m_pMinBtn[i]->InitDeviceObjects(pDataHeader );

		//Ȱ��ȭ.
		m_pActBtn[i] = new CINFImageEx;
		wsprintf(buf,"c_up0%d",i);
		pDataHeader = FindResource(buf);
		m_pActBtn[i]->InitDeviceObjects(pDataHeader );
#endif


		
	}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	//�ּ�ȭ ��.
	m_pMinBar = new CINFImageEx;
	wsprintf(buf, "buyTab_0");
	pDataHeader = FindResource(buf);
	m_pMinBar->InitDeviceObjects(pDataHeader );

	m_pMinBar1 = new CINFImageEx;
	wsprintf(buf, "sellTab_0");
	pDataHeader = FindResource(buf);
	m_pMinBar1->InitDeviceObjects( pDataHeader );
#else
	//�ּ�ȭ ��.
	m_pMinBar = new CINFImageEx;
	wsprintf(buf, "selbar");
	pDataHeader = FindResource(buf);
	m_pMinBar->InitDeviceObjects(pDataHeader );
#endif


	//���� .
	m_pShopName = new CINFImageEx;
	wsprintf(buf, "BackName");
	pDataHeader = FindResource(buf);
	m_pShopName->InitDeviceObjects(pDataHeader );

	//�Ѿ� ���.
	m_pBackTotal = new CINFImageEx;
	wsprintf(buf, "BackTotal");
	pDataHeader = FindResource(buf);
	m_pBackTotal->InitDeviceObjects(pDataHeader );

	// ��ũ�� ��ư
	m_pScrollButton = new CINFImageEx;
	pDataHeader = FindResource("c_scrlb");
	m_pScrollButton->InitDeviceObjects(pDataHeader ) ;	

	/*--------------------------------------------------------------------------*/
	// ���� ���� Ÿ�Կ� ���� �̹���
	//�� ���
	m_pBackTab[0] = new CINFImageEx;
	wsprintf(buf, "BackTab_%d", m_byBazaarType - 1);
	pDataHeader = FindResource(buf);
	m_pBackTab[0]->InitDeviceObjects(pDataHeader );

	//������ ���.
	m_pBackItem = new CINFImageEx;
	wsprintf(buf, "BackItem_%d", m_byBazaarType - 1);
	pDataHeader = FindResource(buf);
	m_pBackItem->InitDeviceObjects(pDataHeader );

#ifndef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	// ���� ���
	m_pSelectBar = new CINFImageEx;
	wsprintf(buf, "SelItem_%d", m_byBazaarType - 1);
	pDataHeader = FindResource(buf);
	m_pSelectBar->InitDeviceObjects(pDataHeader );
#endif

	if(m_byBazaarType == 1)
	{
		//�ΰ�
		m_pBackTab[1] = new CINFImageEx;
		wsprintf(buf, "sellLogTab");
		pDataHeader = FindResource(buf);
		m_pBackTab[1]->InitDeviceObjects(pDataHeader );

		//����Ʈ ���.
		m_pBackList = new CINFImageEx;
		wsprintf(buf, "BackList_0");
		pDataHeader = FindResource(buf);
		m_pBackList->InitDeviceObjects(pDataHeader );
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
		m_pBackListBox = new CINFImageEx;
		wsprintf(buf, "BackList");
		pDataHeader = FindResource(buf);
		m_pBackListBox->InitDeviceObjects( pDataHeader );		
#endif
	}
	else if(m_byBazaarType == 2)
	{
		//�ΰ�
		m_pBackTab[1] = new CINFImageEx;
		wsprintf(buf, "buyLogTab");
		pDataHeader = FindResource(buf);
		m_pBackTab[1]->InitDeviceObjects(pDataHeader );

		//����Ʈ ���.
		m_pBackList = new CINFImageEx;
		wsprintf(buf, "BackList");
		pDataHeader = FindResource(buf);
		m_pBackList->InitDeviceObjects(pDataHeader );

#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
		m_pBackListBox = new CINFImageEx;
		wsprintf(buf, "BackList");
		pDataHeader = FindResource(buf);
		m_pBackListBox->InitDeviceObjects( pDataHeader );		
#endif

		//comboBox ������.
		m_pArrowIcon[0] = new CINFImageEx;
		wsprintf(buf,"mnQdn00");
		pDataHeader = FindResource(buf);
		m_pArrowIcon[0]->InitDeviceObjects(pDataHeader );
		m_pArrowIcon[1] = new CINFImageEx;
		wsprintf(buf,"mnQdn01");
		pDataHeader = FindResource(buf);
		m_pArrowIcon[1]->InitDeviceObjects(pDataHeader );

		// ���� ������ �̸� �Ѱ� ��� �غ� �Ѵ�.
		OnReadyBuyItem();
	}
	/*--------------------------------------------------------------------------*/
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	//m_pFontItemPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_OPEN_2_SEL_W,32);
	m_pFontItemPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemPrice->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_OPEN_1_BUY_W,32);
	m_pFontItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemCount->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemSum = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_OPEN_2_SEL_W,32);
	m_pFontItemSum = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemSum->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,70,32);
	//m_pFontItemName->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_OPEN_1_SEL_W,32);
	m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemName->InitDeviceObjects(g_pD3dDev);
	//m_pFontName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,190,32);
	m_pFontName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,256,32);
	m_pFontName->InitDeviceObjects(g_pD3dDev);
	//m_pFontTotal = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,107,32);
	m_pFontTotal = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontTotal->InitDeviceObjects(g_pD3dDev);
	//m_pFontLogMsg = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_SHOP_LOG_STRING_LENGTH,32);
	m_pFontLogMsg = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,512,32);
	m_pFontLogMsg->InitDeviceObjects(g_pD3dDev);
	//m_pFontShopType= new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_SHOP_LOG_STRING_LENGTH,32);
	m_pFontShopType= new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,512,32);
	m_pFontShopType->InitDeviceObjects(g_pD3dDev);
#else
	//m_pFontItemPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_OPEN_2_SEL_W,32);
	m_pFontItemPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemPrice->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_OPEN_1_BUY_W,32);
	m_pFontItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemCount->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemSum = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_OPEN_2_SEL_W,32);
	m_pFontItemSum = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemSum->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,70,32);
	//m_pFontItemName->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_OPEN_1_SEL_W,32);
	m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemName->InitDeviceObjects(g_pD3dDev);
	//m_pFontName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,190,32);
	m_pFontName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,256,32);
	m_pFontName->InitDeviceObjects(g_pD3dDev);
	//m_pFontTotal = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,107,32);
	m_pFontTotal = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontTotal->InitDeviceObjects(g_pD3dDev);
	//m_pFontLogMsg = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_SHOP_LOG_STRING_LENGTH,32);
	m_pFontLogMsg = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,512,32);
	m_pFontLogMsg->InitDeviceObjects(g_pD3dDev);
	//m_pFontShopType= new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_SHOP_LOG_STRING_LENGTH,32);
	m_pFontShopType= new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,512,32);
	m_pFontShopType->InitDeviceObjects(g_pD3dDev);
#endif

#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	m_pComboKindEx = new CINFComboBoxEX(this, m_pGameData);
	m_pComboKindEx->CreateImage("Name","SelName","c_scrlb");
	m_pComboKindEx->InitDeviceObjects();
	m_pComboNameEx = new CINFComboBoxEX(this, m_pGameData);
	m_pComboNameEx->CreateImage("Name","SelName","c_scrlb");
	m_pComboNameEx->InitDeviceObjects();
#else
	m_pComboKindEx = new CINFComboBoxEX(this, m_pGameData);
	m_pComboKindEx->CreateImage("Name","SelName","Sm-Scroll");
	m_pComboKindEx->InitDeviceObjects();
	m_pComboNameEx = new CINFComboBoxEX(this, m_pGameData);
	m_pComboNameEx->CreateImage("Name","SelName","Sm-Scroll");
	m_pComboNameEx->InitDeviceObjects();
#endif

	return S_OK;
}

HRESULT CINFCityBazaarOpen::RestoreDeviceObjects()
{
	int i;
	m_pBackWindow->RestoreDeviceObjects();
	for(i = 0; i < 4; i++)
	{
		m_pDelItemBtn[i]->RestoreDeviceObjects();
		m_pPutItemBtn[i]->RestoreDeviceObjects();
		m_pStartBtn[i]->RestoreDeviceObjects();
		m_pStopBtn[i]->RestoreDeviceObjects();

		m_pMinBtn[i]->RestoreDeviceObjects();
		m_pActBtn[i]->RestoreDeviceObjects();
	}
	m_pMinBar->RestoreDeviceObjects();
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	m_pMinBar1->RestoreDeviceObjects();
#endif

	for(i = 0; i < 2; i++)
	{
		m_pBackTab[i]->RestoreDeviceObjects();
	}
	
	m_pFontItemPrice->RestoreDeviceObjects();
	m_pFontItemCount->RestoreDeviceObjects();
	m_pFontItemName->RestoreDeviceObjects();
	m_pFontItemSum->RestoreDeviceObjects();
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	m_pBackListBox->RestoreDeviceObjects();
#endif
	m_pBackList->RestoreDeviceObjects();
	m_pBackItem->RestoreDeviceObjects();
	m_pShopName->RestoreDeviceObjects();
	m_pBackTotal->RestoreDeviceObjects();
	m_pScrollButton->RestoreDeviceObjects();
	m_pSelectBar->RestoreDeviceObjects();


	m_pFontName->RestoreDeviceObjects();
	m_pFontTotal->RestoreDeviceObjects();
	m_pFontLogMsg->RestoreDeviceObjects();
	m_pFontShopType->RestoreDeviceObjects();

	if(m_byBazaarType == 2)
	{
		for(i = 0; i < 2; i++)
		{
			m_pArrowIcon[i]->RestoreDeviceObjects();
		}
		m_pComboKindEx->RestoreDeviceObject();
		m_pComboNameEx->RestoreDeviceObject();
	}
	
	return S_OK;
}

HRESULT CINFCityBazaarOpen::DeleteDeviceObjects()
{
	int i;
	m_pBackWindow->DeleteDeviceObjects();
	for(i = 0; i < 4; i++)
	{
		m_pDelItemBtn[i]->DeleteDeviceObjects();
		m_pPutItemBtn[i]->DeleteDeviceObjects();
		m_pStartBtn[i]->DeleteDeviceObjects();
		m_pStopBtn[i]->DeleteDeviceObjects();
		util::del(m_pDelItemBtn[i]);
		util::del(m_pPutItemBtn[i]);
		util::del(m_pStartBtn[i]);
		util::del(m_pStopBtn[i]);
	
		m_pMinBtn[i]->DeleteDeviceObjects();
		m_pActBtn[i]->DeleteDeviceObjects();
		util::del(m_pMinBtn[i]);
		util::del(m_pActBtn[i]);
	}
	m_pMinBar->DeleteDeviceObjects();
	util::del(m_pMinBar);
	
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	m_pMinBar1->DeleteDeviceObjects();
	util::del(m_pMinBar1);
#endif
	
	for(i = 0; i < 2; i++)
	{
		m_pBackTab[i]->DeleteDeviceObjects();
		util::del(m_pBackTab[i]);
	}

	m_pShopName->DeleteDeviceObjects();
	m_pBackTotal->DeleteDeviceObjects();
	m_pBackList->DeleteDeviceObjects();
	m_pBackItem->DeleteDeviceObjects();
	m_pScrollButton->DeleteDeviceObjects();
	m_pSelectBar->DeleteDeviceObjects();
	util::del(m_pShopName);
	util::del(m_pBackTotal);
	util::del(m_pBackList);
	util::del(m_pBackItem);
	util::del(m_pScrollButton);
	util::del(m_pSelectBar);

#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	m_pBackListBox->DeleteDeviceObjects();
	util::del( m_pBackListBox );
#endif

	m_pFontItemName->DeleteDeviceObjects();
	m_pFontItemPrice->DeleteDeviceObjects();
	m_pFontItemCount->DeleteDeviceObjects();
	m_pFontItemSum->DeleteDeviceObjects();
	m_pFontName->DeleteDeviceObjects();
	m_pFontTotal->DeleteDeviceObjects();
	m_pFontLogMsg->DeleteDeviceObjects();
	m_pFontShopType->DeleteDeviceObjects();
	util::del(m_pFontItemName);
	util::del(m_pFontItemPrice);
	util::del(m_pFontItemCount);
	util::del(m_pFontName);
	util::del(m_pFontTotal);
	util::del(m_pFontLogMsg);
	util::del(m_pFontShopType);

	if(m_byBazaarType == 2)
	{
		for(i = 0; i < 2; i++)
		{
			m_pArrowIcon[i]->DeleteDeviceObjects();
			util::del(m_pArrowIcon[i]);
		}
		m_pComboKindEx->DeleteDeviceObject();
		m_pComboNameEx->DeleteDeviceObject();
	}

	InitOpenData();

	if(g_pGameMain)
		g_pGameMain->SetItemInfo( 0, 0, 0, 0); 

	if(g_pCharacterChild)
	{
		g_pCharacterChild->DeleteChatMoveShop();
	}

	return S_OK;
}

HRESULT CINFCityBazaarOpen::InvalidateDeviceObjects()
{
	int i;

	m_pBackWindow->InvalidateDeviceObjects();
	for(i = 0; i < 4; i++)
	{
		m_pDelItemBtn[i]->InvalidateDeviceObjects();
		m_pPutItemBtn[i]->InvalidateDeviceObjects();
		m_pStartBtn[i]->InvalidateDeviceObjects();
		m_pStopBtn[i]->InvalidateDeviceObjects();
	
		m_pMinBtn[i]->InvalidateDeviceObjects();
		m_pActBtn[i]->InvalidateDeviceObjects();
	}
	m_pMinBar->InvalidateDeviceObjects();
	
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	m_pMinBar1->InvalidateDeviceObjects();
#endif
	
	for(i = 0; i < 2; i++)
	{
		m_pBackTab[i]->InvalidateDeviceObjects();
	}

	m_pBackList->InvalidateDeviceObjects();
	m_pBackItem->InvalidateDeviceObjects();
	m_pShopName->InvalidateDeviceObjects();
	m_pBackTotal->InvalidateDeviceObjects();
	m_pScrollButton->InvalidateDeviceObjects();
	m_pSelectBar->InvalidateDeviceObjects();
	
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	m_pBackListBox->InvalidateDeviceObjects();
#endif
	
	m_pFontItemName->InvalidateDeviceObjects();
	m_pFontItemPrice->InvalidateDeviceObjects();
	m_pFontItemCount->InvalidateDeviceObjects();
	m_pFontItemSum->InvalidateDeviceObjects();
	m_pFontName->InvalidateDeviceObjects();
	m_pFontTotal->InvalidateDeviceObjects();
	m_pFontLogMsg->InvalidateDeviceObjects();
	m_pFontShopType->InvalidateDeviceObjects();

	if(m_byBazaarType == 2)
	{
		for(i = 0; i < 2; i++)
		{
			m_pArrowIcon[i]->InvalidateDeviceObjects();
		}

		m_pComboKindEx->InitDeviceObjects();
		m_pComboNameEx->InitDeviceObjects();
	}
	
	return S_OK;
}

void CINFCityBazaarOpen::SetDataCombo(int nComboActive)
{
	if(nComboActive == 1)
	{
		if(m_pComboKindEx->m_vecData.size() == 0)
		{
			int i = 0, count = 0;
			while(g_arrItemKindString[i].byItemKind0 != ITEMKIND_UNKNOWN)
			{
				ComboData Data;
				
				if(g_arrItemKindString[i].bIsBazaarItemKind)
				{
					
					wsprintf(Data.DataName,"%s",g_arrItemKindString[i].szItemKindName);
					Data.nData = g_arrItemKindString[i].byItemKind0;
					m_pComboKindEx->m_vecData.push_back(Data);
					count++;
				}
				i++;
			}
			
			sort(m_pComboKindEx->m_vecData.begin(), m_pComboKindEx->m_vecData.end());
			m_pComboKindEx->SetScrollBarInfo(214,5,119,9,30);
			m_pComboKindEx->SetComboInfo(count,8,204,15);
		}
	}
	else if(nComboActive == 2)
	{
		// ���� ����Ÿ�� ���� �� ���� �Ѵ�.
		int nInputItemIndex = m_vecOpenBazaarItem.size() - 1;
		if(nInputItemIndex >= 0)
		{
			if(m_vecOpenBazaarItem[nInputItemIndex].pItemBase)
			{
				util::del(m_vecOpenBazaarItem[nInputItemIndex].pItemBase);
			}
		}

		vectorItemInfoList ItemList;
		g_pDatabase->GetServerItemInfo(&ItemList, m_pComboKindEx->m_vecData[m_pComboKindEx->m_nSelectDataIndex].nData);

		m_pComboNameEx->m_vecData.clear();
		int i = 0, count = 0;
		vectorItemInfoList::iterator itItem = ItemList.begin();
		while(itItem != ItemList.end())
		{
			ComboData Data;
	
			if(COMPARE_BIT_FLAG((*itItem)->ItemAttribute, ITEM_ATTR_BAZAAR_ITEM))
			{
				wsprintf(Data.DataName,"%s", (*itItem)->ItemName);
				Data.nData = (*itItem)->ItemNum;
				m_pComboNameEx->m_vecData.push_back(Data);
				count++;
			}
			
			itItem++;
		}
		
		sort(m_pComboNameEx->m_vecData.begin(), m_pComboNameEx->m_vecData.end());
		m_pComboNameEx->SetScrollBarInfo(214,5,119,9,30);
		m_pComboNameEx->SetComboInfo(count,8,204,15);
	}		
}

void CINFCityBazaarOpen::Render()
{
	// 2006-08-29 by dgwoo ���ژ��?Ȱ��ȭ&��Ȱ��ȭ���� .
	if(!m_bBazaarMinAct)
	{//��Ȱ��ȭ��.
		Render_Disable();
		return;
	}

	// ������ �κ��丮
	g_pGameMain->m_pInven->RenderOnCityBase();

	//����
	m_pBackWindow->Move(BAZAAR_SHOP_WINDOW_X, BAZAAR_SHOP_WINDOW_Y);
	m_pBackWindow->Render();

	if(m_byTabIndex == 1)
	{
		// �ΰ� ��
		Render_Log();
	}
	else 
	{
		// �Ϲ� ��
		/*--------------------------------------------------------------------------*/
		// ���� �̹���
		Render_Common();

		/*--------------------------------------------------------------------------*/
		// Ÿ�Ժ� �̹���
		if(m_byBazaarType == 1)
		{
			Render_Sell();
		}
		else if(m_byBazaarType == 2)
		{
			Render_Buy();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \class		void CINFCityBazaarOpen::RenderDisabled()
/// \brief		��Ȱ��ȭ�� �̴Ϲٿ� Ȱ��ȭ��ư���� �׸���.
///
/// \author		dgwoo
/// \version	
/// \date		2006-08-29 ~ 2006-08-29
/// \warning	
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Render_Disable()
{
	char temp[64] = {0,};
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	if(m_byBazaarType == 1)
	{
		m_pMinBar1->Move(BAZAAR_SHOP_MINIBAR_X,BAZAAR_SHOP_MINIBAR_Y);
		m_pMinBar1->Render();
	}
	else
	{
	m_pMinBar->Move(BAZAAR_SHOP_MINIBAR_X,BAZAAR_SHOP_MINIBAR_Y);
	m_pMinBar->Render();
	}	
#else
	m_pMinBar->Move(BAZAAR_SHOP_MINIBAR_X,BAZAAR_SHOP_MINIBAR_Y);
	m_pMinBar->Render();

	if(m_byBazaarType == 1)
		wsprintf(temp,STRMSG_C_060829_0100);
	else
		wsprintf(temp,STRMSG_C_060829_0101);
	m_pFontShopType->DrawText(BAZAAR_SHOP_MINIBAR_X + 5,BAZAAR_SHOP_MINIBAR_Y + 2,GUI_FONT_COLOR_W,temp,0L);
#endif	
	m_pActBtn[m_nMinBtnState]->Move(BAZAAR_SHOP_ACT_X,BAZAAR_SHOP_ACT_Y);
	m_pActBtn[m_nMinBtnState]->Render();
}

void CINFCityBazaarOpen::Render_Common()
{
	m_pBackTab[0]->Move(BAZAAR_SHOP_TAB_START_X, BAZAAR_SHOP_TAB_START_Y);
	m_pBackTab[0]->Render();


#ifndef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	m_pBackList->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y);
	m_pBackList->Render();
#endif

	//�ּ�ȭ ��ư.
	m_pMinBtn[m_nMinBtnState]->Move(BAZAAR_SHOP_MIN_X,BAZAAR_SHOP_MIN_Y);
	m_pMinBtn[m_nMinBtnState]->Render();
	

	//�Ѿ� �̹���
	m_pBackTotal->Move(BAZAAR_SHOP_OPEN_TOTAL_PRICE_X, BAZAAR_SHOP_OPEN_TOTAL_PRICE_Y);
	m_pBackTotal->Render();
	
	// �Ѿ� ����.
	char temp1[64];
	char temp2[64];
	wsprintf( temp1, "%d", m_nTotal );
	MakeCurrencySeparator( temp2, temp1, 3, ',' );
	//������ ������ ����..
	SIZE texSize = m_pFontTotal->GetStringSize(temp2);
	m_pFontTotal->DrawText(BAZAAR_SHOP_OPEN_TOTAL_PRICE_X+BAZAAR_SHOP_OPEN_TOTAL_PRICE_W-texSize.cx,BAZAAR_SHOP_OPEN_TOTAL_PRICE_Y, GUI_FONT_COLOR_W,temp2, 0L);

// 	//���� 
	m_pShopName->Move(BAZAAR_OPEN_NAME_X, BAZAAR_OPEN_NAME_Y);
	m_pShopName->Render();

#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	if(m_byFocusText == TEXT_NAME)
		UnderBarDrawText(m_pFontName,BAZAAR_OPEN_NAME_X+51, BAZAAR_OPEN_NAME_Y + 4,GUI_FONT_COLOR_W,m_strInputMessage,0L);
	else
	 	m_pFontName->DrawText(BAZAAR_OPEN_NAME_X+51, BAZAAR_OPEN_NAME_Y + 4,GUI_FONT_COLOR_W,m_strInputMessage,0L);
#else
 	if(m_byFocusText == TEXT_NAME)
		UnderBarDrawText(m_pFontName,BAZAAR_OPEN_NAME_X+40, BAZAAR_OPEN_NAME_Y,GUI_FONT_COLOR_W,m_strInputMessage,0L);
	else
	m_pFontName->DrawText(BAZAAR_OPEN_NAME_X+40, BAZAAR_OPEN_NAME_Y,GUI_FONT_COLOR_W,m_strInputMessage,0L);
#endif

// 	//��ư ����.
	m_pStartBtn[m_nStartBtnState]->Move(BAZAAR_SHOP_OPEN_START_X, BAZAAR_SHOP_OPEN_START_Y);
	m_pStartBtn[m_nStartBtnState]->Render();
// 
	m_pStopBtn[m_nStopBtnState]->Move(BAZAAR_SHOP_OPEN_STOP_X, BAZAAR_SHOP_OPEN_STOP_Y);
	m_pStopBtn[m_nStopBtnState]->Render();
// 
// 	// ��ũ��
	m_pScrollButton->Move(BAZAAR_SHOP_OPEN_SCROLL_X, BAZAAR_SHOP_SCROLL_Y + m_nScrollPosition);
	m_pScrollButton->Render();
}

void CINFCityBazaarOpen::Render_Sell()
{
	/*--------------------------------------------------------------------------*/
	//������ ��� �ִ� �� ����.	
	int i = 0;
	int nItemCount = m_vecOpenBazaarItem.size();
#ifndef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	if(nItemCount < m_nScrollLine)
		return;
#endif
	
	vector<OPEN_BAZAAR_ITEM>::iterator ite = m_vecOpenBazaarItem.begin();
	while(ite != m_vecOpenBazaarItem.end())
	{
		int nLineCount = i - m_nScrollLine;
		if(nLineCount >= 0)
		{
			if(nLineCount >= SHOP_ITEM_SLOT_NUMBER)
			{
				break;
			}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
			m_pBackListBox->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + ( nLineCount * BAZAAR_SHOP_ITEM_H ) );
			m_pBackListBox->Render();

			m_pBackItem->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
			m_pBackItem->Render();
			// ����
			if(m_nSelectIndex == i)
			{
				m_pSelectBar->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pSelectBar->Render();
			}
#else
			// ����
			if(m_nSelectIndex == i)
			{
				m_pSelectBar->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pSelectBar->Render();
			}
			else
			{
				m_pBackItem->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pBackItem->Render();
			}
#endif


			// ������
			char buf[64] = {0,};
			char buf1[64] = {0,};
			//�ε����� ������ ���� �߰�..


			// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

			//wsprintf(buf, "%08d", ite->pItemBase->ItemInfo->SourceIndex);
			if( !ite->pItemBase->ShapeItemNum )
				wsprintf(buf, "%08d", ite->pItemBase->ItemInfo->SourceIndex);
			else
			{
				ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( ite->pItemBase->ShapeItemNum );
				if( pShapeItem )
					wsprintf( buf, "%08d", pShapeItem->SourceIndex );
				else
					wsprintf(buf, "%08d", ite->pItemBase->ItemInfo->SourceIndex);
			}

			// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

			g_pGameMain->m_pIcon->SetIcon(buf, BAZAAR_SHOP_ICON_X, BAZAAR_SHOP_ICON_Y + (nLineCount * BAZAAR_SHOP_ITEM_H), 1.0f);
			g_pGameMain->m_pIcon->Render();


			// 2010. 02. 11 by ckPark �ߵ��� ����������
			if( (*ite).pItemBase->ItemInfo->InvokingDestParamID
				|| (*ite).pItemBase->ItemInfo->InvokingDestParamIDByUse )
			{
				char buf[128];

				if( GetString_CoolTime( (*ite).pItemBase, buf ) )
				{
					int nFontPosX = BAZAAR_SHOP_ICON_X;
					int nFontPosY = BAZAAR_SHOP_ICON_Y + (nLineCount * BAZAAR_SHOP_ITEM_H) + 6;

					m_pFontItemName->DrawText( nFontPosX, nFontPosY, GUI_FONT_COLOR, buf, 0L );
				}
			}
			// end 2010. 02. 11 by ckPark �ߵ��� ����������


			// ������ �̸�
			vector<string> vecChatMessage;
			vecChatMessage.clear();
			STRING_CULL(ite->pItemBase->ItemInfo->ItemName, BAZAAR_OPEN_1_SEL_W, &vecChatMessage, m_pFontItemName);
			wsprintf(buf1,"%s",(char*)vecChatMessage[0].c_str());
			m_pFontItemName->DrawText(BAZAAR_OPEN_1_SEL_X,BAZAAR_OPEN_1_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);

			wsprintf( buf1, "%d", ite->nItemCount);
			SIZE size = m_pFontItemCount->GetStringSize(buf1);
			if(size.cx > BAZAAR_OPEN_1_SEL_W)
				size.cx = BAZAAR_OPEN_1_SEL_W;
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
			if(m_byFocusText == TEXT_COUNT && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemName,BAZAAR_OPEN_1_SEL_X + BAZAAR_OPEN_1_SEL_W - size.cx - 5,BAZAAR_OPEN_3_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			else
			    m_pFontItemName->DrawText(BAZAAR_OPEN_1_SEL_X + BAZAAR_OPEN_1_SEL_W - size.cx - 5,BAZAAR_OPEN_3_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);

			wsprintf( buf1, "%d", ite->nItemPrice);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontItemPrice->GetStringSize(buf);
			if(size.cx > BAZAAR_OPEN_2_SEL_W)
				size.cx = BAZAAR_OPEN_2_SEL_W;
			if(m_byFocusText == TEXT_PRICE && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemPrice,BAZAAR_OPEN_2_SEL_X+BAZAAR_OPEN_2_SEL_W-size.cx,BAZAAR_OPEN_2_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);
			else
			    m_pFontItemPrice->DrawText(BAZAAR_OPEN_2_SEL_X+BAZAAR_OPEN_2_SEL_W-size.cx,BAZAAR_OPEN_2_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);
#else
if(m_byFocusText == TEXT_COUNT && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemName,BAZAAR_OPEN_1_SEL_X,BAZAAR_OPEN_3_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			else
			    m_pFontItemName->DrawText(BAZAAR_OPEN_1_SEL_X+(BAZAAR_OPEN_1_SEL_W-size.cx)/2,BAZAAR_OPEN_3_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);

			wsprintf( buf1, "%d", ite->nItemPrice);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontItemPrice->GetStringSize(buf);
			if(size.cx > BAZAAR_OPEN_2_SEL_W)
				size.cx = BAZAAR_OPEN_2_SEL_W;
			if(m_byFocusText == TEXT_PRICE && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemPrice,BAZAAR_OPEN_2_SEL_X,BAZAAR_OPEN_2_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);
			else
			    m_pFontItemPrice->DrawText(BAZAAR_OPEN_2_SEL_X+BAZAAR_OPEN_2_SEL_W-size.cx,BAZAAR_OPEN_2_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);
#endif

			wsprintf( buf1, "%d", ite->nItemTotal);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontItemSum->GetStringSize(buf);
			if(size.cx > BAZAAR_OPEN_2_SEL_W)
				size.cx = BAZAAR_OPEN_2_SEL_W;
			m_pFontItemSum->DrawText(BAZAAR_OPEN_4_SEL_X+BAZAAR_OPEN_2_SEL_W-size.cx,BAZAAR_OPEN_4_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);

			//��ư ����.
			if(ite->bRegister)
			{
				m_pDelItemBtn[m_nPutDelState[nLineCount]]->Move(BAZAAR_SHOP_RIGHT_BTN_X, BAZAAR_SHOP_RIGHT_BTN_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pDelItemBtn[m_nPutDelState[nLineCount]]->Render();
			}
			else
			{
				m_pPutItemBtn[m_nPutDelState[nLineCount]]->Move(BAZAAR_SHOP_RIGHT_BTN_X, BAZAAR_SHOP_RIGHT_BTN_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pPutItemBtn[m_nPutDelState[nLineCount]]->Render();
			}
		}

		ite++;
		i++;
	}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	int j = i - m_nScrollLine;
	if(j < 0)
		j = 0;
	for(j; j < SHOP_ITEM_SLOT_NUMBER; j++)
	{
		m_pBackListBox->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y +  j * BAZAAR_SHOP_ITEM_H);
		m_pBackListBox->Render();
		m_pBackList->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y +  j * BAZAAR_SHOP_ITEM_H);
		m_pBackList->Render();
	}
#endif
}

void CINFCityBazaarOpen::Render_Buy()
{
	/*--------------------------------------------------------------------------*/
	//������ ��� �ִ� �� ����.	
	int i = 0;
	SIZE size;
	char buf[64] = {0,};
	char buf1[64] = {0,};
	int nItemCount = m_vecOpenBazaarItem.size();
#ifndef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	if(nItemCount < m_nScrollLine)
		return;
#endif
	
	vector<OPEN_BAZAAR_ITEM>::iterator ite = m_vecOpenBazaarItem.begin();
	while(ite != m_vecOpenBazaarItem.end())
	{
		int nLineCount = i - m_nScrollLine;
		if(nLineCount >= 0)
		{
			if(nLineCount >= SHOP_ITEM_SLOT_NUMBER)
			{
				break;
			}

#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
			m_pBackListBox->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + ( nLineCount * BAZAAR_SHOP_ITEM_H ) );
			m_pBackListBox->Render();
			
			m_pBackItem->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
			m_pBackItem->Render();
			// ����
			if(m_nSelectIndex == i)
			{
				m_pSelectBar->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pSelectBar->Render();
			}
#else
			// ����
			if(m_nSelectIndex == i)
			{
				m_pSelectBar->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pSelectBar->Render();

			}
			else
			{
				m_pBackItem->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pBackItem->Render();
			}
#endif

			//�޺��ڽ��� �ִ� ���� ������ ���̱�
			if(m_nComboState[nLineCount][0] == COMBO_UNDER)
			{
				m_pArrowIcon[0]->Move(BAZAAR_OPEN_1_ICON_X,BAZAAR_OPEN_1_ICON_Y+(nLineCount * BAZAAR_SHOP_ITEM_H));
					m_pArrowIcon[0]->Render();
			}
			else if(m_nComboState[nLineCount][0] == COMBO_CLICK)
			{
				m_pArrowIcon[1]->Move(BAZAAR_OPEN_1_ICON_X,BAZAAR_OPEN_1_ICON_Y+(nLineCount * BAZAAR_SHOP_ITEM_H));
					m_pArrowIcon[1]->Render();
			}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
			else
			{
				m_pArrowIcon[0]->Move(BAZAAR_OPEN_1_ICON_X,BAZAAR_OPEN_1_ICON_Y+(nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pArrowIcon[0]->Render();
			}
#endif
			if(m_nComboState[nLineCount][1] == COMBO_UNDER)
			{
				m_pArrowIcon[0]->Move(BAZAAR_OPEN_2_ICON_X,BAZAAR_OPEN_2_ICON_Y+(nLineCount * BAZAAR_SHOP_ITEM_H));
					m_pArrowIcon[0]->Render();
			}
			else if(m_nComboState[nLineCount][1] == COMBO_CLICK)
			{
				m_pArrowIcon[1]->Move(BAZAAR_OPEN_2_ICON_X,BAZAAR_OPEN_2_ICON_Y+(nLineCount * BAZAAR_SHOP_ITEM_H));
					m_pArrowIcon[1]->Render();
			}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
			else
			{
				m_pArrowIcon[0]->Move(BAZAAR_OPEN_2_ICON_X,BAZAAR_OPEN_2_ICON_Y+(nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pArrowIcon[0]->Render();
			}
#endif

			if(ite->pItemBase)
			{
				// ������

				// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

				//wsprintf(buf, "%08d", ite->pItemBase->ItemInfo->SourceIndex);
				if( !ite->pItemBase->ShapeItemNum )
					wsprintf(buf, "%08d", ite->pItemBase->ItemInfo->SourceIndex);
				else
				{
					ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( ite->pItemBase->ShapeItemNum );
					if( pShapeItem )
						wsprintf( buf, "%08d", pShapeItem->SourceIndex );
					else
						wsprintf(buf, "%08d", ite->pItemBase->ItemInfo->SourceIndex);
				}

				// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����


				g_pGameMain->m_pIcon->SetIcon(buf, BAZAAR_SHOP_ICON_X, BAZAAR_SHOP_ICON_Y + (nLineCount * BAZAAR_SHOP_ITEM_H), 1.0f);
				g_pGameMain->m_pIcon->Render();

				vector<string> vecChatMessage;
				vecChatMessage.clear();
				wsprintf( buf1, "%s", CAtumSJ::GetItemKindName(ite->pItemBase->ItemInfo->Kind));
				STRING_CULL(buf1, BAZAAR_OPEN_1_BUY_W, &vecChatMessage, m_pFontItemCount);
				size = m_pFontItemCount->GetStringSize((char*)vecChatMessage[0].c_str());
				m_pFontItemCount->DrawText(BAZAAR_OPEN_1_BUY_X,BAZAAR_OPEN_1_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,(char*)vecChatMessage[0].c_str(),0L);
				
				vecChatMessage.clear();
				STRING_CULL(ite->pItemBase->ItemInfo->ItemName, BAZAAR_OPEN_1_BUY_W, &vecChatMessage, m_pFontItemCount);
				wsprintf(buf1,"%s",(char*)vecChatMessage[0].c_str());
				size = m_pFontItemCount->GetStringSize(buf1);
				m_pFontItemCount->DrawText(BAZAAR_OPEN_1_BUY_X,BAZAAR_OPEN_3_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			}

			wsprintf( buf1, "%d", ite->nItemCount);
			size = m_pFontItemPrice->GetStringSize(buf1);
			if(size.cx > BAZAAR_OPEN_2_BUY_W)
				size.cx = BAZAAR_OPEN_2_BUY_W;
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
			if(m_byFocusText == TEXT_COUNT && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemPrice,BAZAAR_OPEN_2_BUY_X + BAZAAR_OPEN_2_BUY_W - size.cx - 5,BAZAAR_OPEN_2_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			else
			    m_pFontItemPrice->DrawText(BAZAAR_OPEN_2_BUY_X + BAZAAR_OPEN_2_BUY_W - size.cx,BAZAAR_OPEN_2_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);

			wsprintf( buf1, "%d", ite->nItemPrice);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontItemPrice->GetStringSize(buf);
			if(size.cx > BAZAAR_OPEN_2_BUY_W)
				size.cx = BAZAAR_OPEN_2_BUY_W;
			if(m_byFocusText == TEXT_PRICE && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemPrice,BAZAAR_OPEN_4_BUY_X + BAZAAR_OPEN_2_BUY_W-size.cx - 5,BAZAAR_OPEN_4_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);
			else
			    m_pFontItemPrice->DrawText(BAZAAR_OPEN_4_BUY_X + BAZAAR_OPEN_2_BUY_W-size.cx,BAZAAR_OPEN_4_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);
#else 
	if(m_byFocusText == TEXT_COUNT && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemPrice,BAZAAR_OPEN_2_BUY_X,BAZAAR_OPEN_2_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			else
			    m_pFontItemPrice->DrawText(BAZAAR_OPEN_2_BUY_X+(BAZAAR_OPEN_2_BUY_W-size.cx)/2,BAZAAR_OPEN_2_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);

			wsprintf( buf1, "%d", ite->nItemPrice);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontItemPrice->GetStringSize(buf);
			if(size.cx > BAZAAR_OPEN_2_BUY_W)
				size.cx = BAZAAR_OPEN_2_BUY_W;
			if(m_byFocusText == TEXT_PRICE && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemPrice,BAZAAR_OPEN_4_BUY_X,BAZAAR_OPEN_4_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);
			else
			    m_pFontItemPrice->DrawText(BAZAAR_OPEN_4_BUY_X+BAZAAR_OPEN_2_BUY_W-size.cx,BAZAAR_OPEN_4_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);
#endif
			//��ư ����.
			if(ite->bRegister)
			{
				m_pDelItemBtn[m_nPutDelState[nLineCount]]->Move(BAZAAR_SHOP_RIGHT_BTN_X, BAZAAR_SHOP_RIGHT_BTN_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pDelItemBtn[m_nPutDelState[nLineCount]]->Render();
			}
			else
			{
				m_pPutItemBtn[m_nPutDelState[nLineCount]]->Move(BAZAAR_SHOP_RIGHT_BTN_X, BAZAAR_SHOP_RIGHT_BTN_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pPutItemBtn[m_nPutDelState[nLineCount]]->Render();
			}
		}

		ite++;
		i++;
	}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	int j = i - m_nScrollLine;
	if(j < 0)
		j = 0;
	for(j; j < SHOP_ITEM_SLOT_NUMBER; j++)
	{
		m_pBackListBox->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y +  j * BAZAAR_SHOP_ITEM_H);
		m_pBackListBox->Render();
		m_pBackList->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y +  j * BAZAAR_SHOP_ITEM_H);
		m_pBackList->Render();
	}
#endif

	// ����
	int nBuyItemIndex = nItemCount - 1;
	int nRenderIndex = nBuyItemIndex - m_nScrollLine;
	if(nRenderIndex >= 0 &&
		nRenderIndex < SHOP_ITEM_SLOT_NUMBER)
	{
		if(m_vecOpenBazaarItem[nBuyItemIndex].pItemBase == NULL &&
			m_pComboKindEx->m_nSelectDataIndex != -1)
		{
			vector<string> vecChatMessage;
			vecChatMessage.clear();
			wsprintf( buf1, "%s", CAtumSJ::GetItemKindName(m_pComboKindEx->m_vecData[m_pComboKindEx->m_nSelectDataIndex].nData));
			STRING_CULL(buf1, BAZAAR_OPEN_1_BUY_W, &vecChatMessage, m_pFontItemCount);
			size = m_pFontItemCount->GetStringSize((char*)vecChatMessage[0].c_str());
			m_pFontItemCount->DrawText(BAZAAR_OPEN_1_BUY_X,BAZAAR_OPEN_1_Y+(nRenderIndex * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,(char*)vecChatMessage[0].c_str(),0L);
		}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����

		else if(m_vecOpenBazaarItem[nBuyItemIndex].pItemBase == NULL &&
				m_pComboKindEx->m_nSelectDataIndex == -1)
		{
			size = m_pFontItemCount->GetStringSize(STRMSG_C_060801_0100);
			m_pFontItemCount->DrawText(BAZAAR_OPEN_1_BUY_X,BAZAAR_OPEN_1_Y+(nRenderIndex * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,STRMSG_C_060801_0100,0L);
		}
		if(m_vecOpenBazaarItem[nBuyItemIndex].pItemBase == NULL)
		{
			m_pFontItemCount->DrawText(BAZAAR_OPEN_1_BUY_X, BAZAAR_OPEN_3_Y+(nRenderIndex * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,STRMSG_C_060801_0101,0L);
		}
#else
		else if(m_vecOpenBazaarItem[nBuyItemIndex].pItemBase == NULL &&
			m_pComboKindEx->m_nSelectDataIndex == -1)
		{
			m_pFontItemCount->DrawText(BAZAAR_OPEN_1_BUY_X + ( BAZAAR_OPEN_1_BUY_W - size.cx ) / 2,BAZAAR_OPEN_1_Y+(nRenderIndex * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,STRMSG_C_060801_0100,0L);
		}
		if(m_vecOpenBazaarItem[nBuyItemIndex].pItemBase == NULL)
		{
			m_pFontItemCount->DrawText(BAZAAR_OPEN_3_BUY_X + ( BAZAAR_OPEN_1_BUY_W - size.cx ) / 2,BAZAAR_OPEN_3_Y+(nRenderIndex * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,STRMSG_C_060801_0101,0L);
		}
#endif
	}

	//�޺� �ڽ��� �׷��ش�.
	if(m_nComboActive== 1)
	{
		m_pComboKindEx->ComboRender();
	}
	else if(m_nComboActive == 2)
	{
		m_pComboNameEx->ComboRender();
	}
}

void CINFCityBazaarOpen::Render_Log()
{
	m_pBackTab[1]->Move(BAZAAR_SHOP_TAB_START_X, BAZAAR_SHOP_TAB_START_Y);
	m_pBackTab[1]->Render();

	// ��ũ��
	m_pScrollButton->Move(BAZAAR_SHOP_OPEN_SCROLL_X, BAZAAR_SHOP_SCROLL_Y + m_nScrollPosition);
	m_pScrollButton->Render();

	//�ּ�ȭ ��ư.
	m_pMinBtn[m_nMinBtnState]->Move(BAZAAR_SHOP_MIN_X,BAZAAR_SHOP_MIN_Y);
 	m_pMinBtn[m_nMinBtnState]->Render();

	// ��ũ�� ����
	int j = 0;
	int nMaxLineCount = 0;
	int nRenderIndex = m_nScrollLine;
	int nRenderedLineCounts	= 0;
	int nMaxRenderLineCounts = BAZAAR_SHOP_LOG_LINE_COUNT;

	if(0 >= m_LogChat.m_nStoredLineCounts ||
		nRenderIndex >= m_LogChat.m_nStoredLineCounts)
		return;

	int pFontTexWidth = m_pFontLogMsg->GetStringSize(m_LogChat.GetChatLine(nRenderIndex)).cx;

	for(j = 0; j < BAZAAR_SHOP_LOG_LINE_COUNT; j++)
	{
		m_pFontLogMsg->DrawText(BAZAAR_SHOP_LOG_X
			, BAZAAR_SHOP_LOG_Y + (CHAT_FONT_LINE_HEIGHT * nRenderedLineCounts)
			, m_LogChat.GetColorType(nRenderIndex)
			, m_LogChat.GetChatLine(nRenderIndex)
			, 0L);

		nRenderedLineCounts++;
		nRenderIndex++;

		if(m_LogChat.m_nStoredLineCounts <= nRenderIndex ||
			nMaxRenderLineCounts <= nRenderedLineCounts)
		{
			break;
		}						

	}
}

///////////////////////////////////////////////////////////////////////////////
/// \class		void CINFCityBazaarOpen::Render_Combo()
/// \brief		�޺� �ڽ��� ���
///
/// \author		dgwoo
/// \version	
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///////////////////////////////////////////////////////////////////////////////


void CINFCityBazaarOpen::Tick()
{

}

int CINFCityBazaarOpen::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nResultProc = INF_MSGPROC_NORMAL;
	int i;
	// 2006-08-29 by dgwoo ��Ȱ��ȭ�� ��� �޽����� ���´�.
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	if( !m_bBazaarMinAct )
#else
	if(!m_bBazaarMinAct && m_byTabIndex == 0)
#endif
	{//��Ȱ��ȭ��.
		if(INF_MSGPROC_BREAK == WndProc_Disable(uMsg, wParam,  lParam))
		{
			return INF_MSGPROC_BREAK;
		}
		return INF_MSGPROC_NORMAL;
	}
	//�޺� �ڽ��� Ȱ��ȭ �Ǿ��ִ� ���¿����� �޺� �ڽ��� �ֿ켱 ó���Ѵ�.
	if(m_byTabIndex == 0 && m_nComboActive != 0)
	{
		if(m_nComboActive == 1)
		{
			if(INF_MSGPROC_BREAK == m_pComboKindEx->WndProc(uMsg, wParam, lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
		else if(m_nComboActive == 2)
		{
			if(INF_MSGPROC_BREAK == m_pComboNameEx->WndProc(uMsg, wParam, lParam))
			{
				return INF_MSGPROC_BREAK;
			}
		}
	}

	/*--------------------------------------------------------------------------*/
	// ���� �޼���
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			m_bScrollLock = FALSE;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(GetPointInType(pt,BAZAAR_SHOP_WINDOW))
			{
				g_pInterface->SetWindowOrder(WNDBazaarShop);
			}
			
			// ��
			int nOldTab = m_byTabIndex;
			for(i = 0; i < 2; i++)
			{
				if(GetPointInType(pt,BAZAAR_SHOP_TAB,i))
				{
					m_byTabIndex = i;
					if(m_byTabIndex == 0)
					{
						// ��ũ�� ���� ����
						m_nScrollMaxCount = BAZAARSHOP_ITEMCOUNT;
						m_nScrollMaxLine  = SHOP_ITEM_SLOT_NUMBER;
						InitScrollLine();
					}
					else if(m_byTabIndex == 1)
					{
						m_nScrollMaxCount = m_LogChat.m_nStoredLineCounts;
						m_nScrollMaxLine  = BAZAAR_SHOP_LOG_LINE_COUNT;
						SetScrollEndLine();
					}

					return INF_MSGPROC_BREAK;
				}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
				if(m_nStopBtnState != BTN_STATE_DEACTIVE &&
						GetPointInType(pt,BAZAAR_SHOP_MIN))
				{//�ּ�ȭ ��ư�� ��������.
					m_nMinBtnState = BTN_STATE_NORMAL;
					m_bBazaarMinAct = FALSE;
					
					g_pGameMain->m_pInven->ShowAllInven(FALSE);
					
					return INF_MSGPROC_BREAK;
				}
#endif
			}

			// ��ũ��
			if(GetPointInType(pt,BAZAAR_SHOP_SCROLL,m_nScrollPosition))
			{
				m_nScrollBtn = pt.y - (BAZAAR_SHOP_SCROLL_Y + m_nScrollPosition);
				m_bScrollLock = TRUE;
				return INF_MSGPROC_BREAK;
			}			

		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			// ��ũ��
			if(m_bScrollLock &&
				pt.x >= BAZAAR_SHOP_OPEN_SCROLL_X - 5 && 
				pt.x <= BAZAAR_SHOP_OPEN_SCROLL_X + BAZAAR_SHOP_SCROLL_W + 5)
			{
				int nScrollBtnY = pt.y - m_nScrollBtn;
				if(nScrollBtnY >= BAZAAR_SHOP_SCROLL_Y &&
					nScrollBtnY <= BAZAAR_SHOP_SCROLL_Y + BAZAAR_SHOP_SCROLL_LINE_LENGTH)
				{
					m_nScrollPosition = nScrollBtnY - BAZAAR_SHOP_SCROLL_Y;
					m_nScrollLine = GetScrollLineNumber(m_nScrollPosition);
				}
				else if(nScrollBtnY < BAZAAR_SHOP_SCROLL_Y)
				{
					InitScrollLine();
				}
				else if(nScrollBtnY > BAZAAR_SHOP_SCROLL_Y + BAZAAR_SHOP_SCROLL_LINE_LENGTH)
				{
					SetScrollEndLine();
				}
			}
		}
		break;
		case WM_MOUSEWHEEL:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);

			if(GetPointInType(pt,BAZAAR_SHOP_ITEM_AREA))
			{
				if((int)wParam<0)
				{
					m_nScrollLine++;
					if(m_nScrollLine > GetScrollLine())
					{
						SetScrollEndLine();
					}
					else
					{
						m_nScrollPosition = GetScrollLineInterval(m_nScrollLine);
					}
				}
				else
				{
					m_nScrollLine--;
					if(m_nScrollLine < 0)
					{
						InitScrollLine();
					}
					else
					{
						m_nScrollPosition = GetScrollLineInterval(m_nScrollLine);
					}
				}

				return INF_MSGPROC_BREAK;
			}
			
		}
	}
	/*--------------------------------------------------------------------------*/
	// �Ǹ�, ���� �� �޼���
	if(m_byTabIndex == 0)
	{
		if(WndProc_Common(uMsg, wParam, lParam) == INF_MSGPROC_BREAK)
			return INF_MSGPROC_BREAK;

		/*--------------------------------------------------------------------------*/
		// �� �޼���
		if(m_byBazaarType == 1)
		{
			nResultProc = WndProc_Sell(uMsg, wParam, lParam);
		}
		else if(m_byBazaarType == 2)
		{
			nResultProc = WndProc_Buy(uMsg, wParam, lParam);
		}
	}
	return nResultProc;
}

int CINFCityBazaarOpen::WndProc_Disable(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_LBUTTONUP:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);
				
				if(GetPointInType(pt,BAZAAR_SHOP_ACT))
				{
					m_nMinBtnState = BTN_STATE_NORMAL;
					m_bBazaarMinAct = TRUE;
					// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
					g_pGameMain->m_pInven->ShowAllInven(TRUE); // �������ִ°� �ٽ� ���̰���
				}

			}
			break;
		case WM_LBUTTONDOWN:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);
				if(GetPointInType(pt,BAZAAR_SHOP_ACT))
				{
					m_nMinBtnState = BTN_STATE_CLICK;
				}

			}
			break;
		case WM_MOUSEMOVE:
			{
				POINT pt;
				pt.x = LOWORD(lParam);
				pt.y = HIWORD(lParam);
				CheckMouseReverse(&pt);

				if(GetPointInType(pt,BAZAAR_SHOP_ACT))
				{
					if(m_nMinBtnState != BTN_STATE_CLICK)
						m_nMinBtnState = BTN_STATE_OVER;
				}
				else
				{
					m_nMinBtnState = BTN_STATE_NORMAL;
				}
			}
			break;
			
	}
	return INF_MSGPROC_NORMAL;
}
int CINFCityBazaarOpen::WndProc_Common(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int i;

	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(m_nStartBtnState != BTN_STATE_DEACTIVE &&
				GetPointInType(pt,BAZAAR_SHOP_OPEN_START))
			{
				m_nStartBtnState = BTN_STATE_NORMAL;
				OnButtonClicked(OPEN_START);
			}
			else if(m_nStopBtnState != BTN_STATE_DEACTIVE &&
				GetPointInType(pt,BAZAAR_SHOP_OPEN_STOP))
			{
				m_nStopBtnState = BTN_STATE_NORMAL;
				OnButtonClicked(OPEN_END);
			}
			else if(m_nStopBtnState != BTN_STATE_DEACTIVE &&
				GetPointInType(pt,BAZAAR_SHOP_MIN))
			{//�ּ�ȭ ��ư�� ��������.
				m_nMinBtnState = BTN_STATE_NORMAL;
				m_bBazaarMinAct = FALSE;

				// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
				g_pGameMain->m_pInven->ShowAllInven(FALSE);

				return INF_MSGPROC_BREAK;
			}
	
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
		
			m_bLButtonDown = TRUE;
			m_byFocusText = TEXT_NON;
			g_pD3dApp->m_bChatMode = FALSE;			

			// 2009-02-26 by bhsohn Japan IME
			int nOldSelectIndex = m_nSelectIndex;
			// end 2009-02-26 by bhsohn Japan IME

			if(m_nStartBtnState != BTN_STATE_DEACTIVE &&
				GetPointInType(pt,BAZAAR_SHOP_OPEN_START))
			{
				m_nStartBtnState = BTN_STATE_CLICK;
			}
			else if(m_nStopBtnState != BTN_STATE_DEACTIVE &&
				GetPointInType(pt,BAZAAR_SHOP_OPEN_STOP))
			{
				m_nStopBtnState = BTN_STATE_CLICK;
			}
			else if(m_nStopBtnState != BTN_STATE_DEACTIVE &&
				GetPointInType(pt,BAZAAR_SHOP_MIN))
			{
				m_nMinBtnState = BTN_STATE_CLICK;
			}
		
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				//�������� ��ư�� ���¸� �������ش�.
				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
					GetPointInType(pt,BAZAAR_BTN,i))
				{
					m_nPutDelState[i] = BTN_STATE_CLICK;
				}

				// ����
				if(!g_pGameMain->m_stSelectItem.pSelectItem && 
					GetPointInType(pt,BAZAAR_SHOP_ITEM,i))
				{
					int nItemIndex = GetItemIndexByPos(pt.y);
					if(nItemIndex != -1)
					{
						m_nSelectIndex = nItemIndex;
						break;
					}
					else
					{
						m_nSelectIndex = -1;
					}
				}
				else
				{
					m_nSelectIndex = -1;
				}
			}

			// �̸� �Է� ����(����)
			if(m_bBazaarShopStart == FALSE &&
				GetPointInType(pt,BAZAAR_OPEN_NAME))
			{
				if(m_byFocusText != TEXT_NAME)
				{
				//	memset(m_strInputMessage,0x00,sizeof(m_strInputMessage));
				}
				m_byFocusText = TEXT_NAME;
				g_pD3dApp->m_bChatMode = TRUE;
				
				
				return INF_MSGPROC_BREAK;
			}
			else
			{
				//���� ������ ���������ÿ� Name�� �����Ҽ� ����.
				if(//!(m_nStartBtnState != BTN_STATE_DEACTIVE &&
					m_bBazaarShopStart  ||
					GetPointInType(pt,BAZAAR_SHOP_OPEN_START))
				{
					//memset(m_strInputMessage,0x00,sizeof(m_strInputMessage));
					//g_pD3dApp->CleanText();
				}
				else
				{
					memset(m_strInputMessage,0x00,sizeof(m_strInputMessage));
					g_pD3dApp->CleanText();
				}
			}
		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(m_nStartBtnState != BTN_STATE_DEACTIVE)
			{
				if(GetPointInType(pt,BAZAAR_SHOP_OPEN_START))//BAZAAR_SHOP_OPEN_START
				{
					if(m_nStartBtnState != BTN_STATE_CLICK)
						m_nStartBtnState = BTN_STATE_OVER;
				}
				else
				{
					m_nStartBtnState = BTN_STATE_NORMAL;
				}
		
				if(GetPointInType(pt,BAZAAR_SHOP_OPEN_STOP))//BAZAAR_SHOP_OPEN_STOP
				{
					if(m_nStopBtnState != BTN_STATE_CLICK)
						m_nStopBtnState = BTN_STATE_OVER;
				}
				else
				{
					m_nStopBtnState = BTN_STATE_NORMAL;
				}
				
			}
			if(GetPointInType(pt,BAZAAR_SHOP_MIN))
			{
				if(m_nMinBtnState != BTN_STATE_CLICK)
					m_nMinBtnState = BTN_STATE_OVER;
			}
			else
			{
				m_nMinBtnState = BTN_STATE_NORMAL;
			}

			//�������� ��ư�� ���¸� �������ش�.
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE)
				{
					if(GetPointInType(pt,BAZAAR_BTN,i))//BAZAAR_BTN
					{
						if(m_nPutDelState[i] != BTN_STATE_CLICK)
							m_nPutDelState[i] = BTN_STATE_OVER;
					}
					else
					{
						m_nPutDelState[i] = BTN_STATE_NORMAL;
					}
				}
			}

			// ������ ����
			if(!g_pGameMain->m_stSelectItem.pSelectItem)
			{
				SetItemInfo(NULL, 0 ,0);
				
				if(GetPointInType(pt,BAZAAR_ICON))
				{
					int nItemIndex = GetItemIndexByPos(pt.y);
					if(nItemIndex != -1)
					{
						SetItemInfo((CItemInfo *)(m_vecOpenBazaarItem[nItemIndex].pItemBase), pt.x, pt.y);
					}
				}
			}
		}
		break;
		case WM_MOUSEWHEEL:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);
		}
		break;
		case WM_IME_STARTCOMPOSITION:
		case WM_IME_COMPOSITION:
		case WM_INPUTLANGCHANGE:	
		case WM_IME_ENDCOMPOSITION:
		case WM_IME_SETCONTEXT:	
		case WM_CHAR:
		{
			if( m_byFocusText == TEXT_NAME && g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
			{
				int bFlag = FALSE;
				if(INF_MSGPROC_BREAK == g_pD3dApp->m_inputkey.KeyMapping(g_pD3dApp->GetHwnd(), uMsg, wParam, lParam))
					bFlag = TRUE;

				//////////////////////////////////////////////////////////////////////////
				char text[256];
				char stringtext[512];
				ZERO_MEMORY(text);
				ZERO_MEMORY(stringtext);

				
				// 2007-11-06 by bhsohn ��Ʈ�� ���ڻ�������  �Է�Ű �ȵǴ� ���� ó��
				//int strlenInput = g_input.GetInput(text, sizeof(text));
				int nLanguageConversion = g_pD3dApp->m_inputkey.GetInputLanguage();					
				int strlenInput = g_input.GetInput(text, sizeof(text), nLanguageConversion);

				strcpy(stringtext, text);
				ZERO_MEMORY(text);
				int strlenComp = g_input.GetComp(text, sizeof(text));
				strcat(stringtext, text);
				
				if( strlenInput+strlenComp >= SIZE_MAX_BAZAAR_NAME )
				{
					keybd_event(VK_BACK, 0, KEYEVENTF_EXTENDEDKEY, 0);
				}	
				else if(strlen(stringtext) > 0)
				{
						memset(m_strInputMessage,0x00,sizeof(m_strInputMessage));
					strncpy(m_strInputMessage,stringtext,strlen(stringtext));
				}
				else if(strlen(m_strInputMessage))
				{
					memset(m_strInputMessage,0x00,sizeof(m_strInputMessage));
				}

				g_pD3dApp->m_pSound->PlayD3DSound(SOUND_INPUT_CHAT, g_pShuttleChild->m_vPos, FALSE);
				if(TRUE == bFlag)
					return INF_MSGPROC_BREAK;

			}
			else if(!g_pD3dApp->m_bChatMode)
			{
				// 2009-01-30 by bhsohn ���� ���� ���� �Է� ��Ʈ�� ����
				//g_pD3dApp->CleanText();
			}
		}
		break;
		// 2007-06-11 by bhsohn China IME Working
	case WM_KEYDOWN:
		{
			#ifdef LANGUAGE_CHINA
			if( m_byFocusText == TEXT_NAME && g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
			{
				return g_pD3dApp->m_inputkey.OnIMEKeyDown(g_pD3dApp->GetHwnd(), uMsg, wParam, lParam);
			}
			#endif			
		}
		break;
	}

	return INF_MSGPROC_NORMAL;
}

int CINFCityBazaarOpen::WndProc_Sell(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int i;
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(g_pGameMain->m_stSelectItem.pSelectItem &&
				g_pGameMain->m_stSelectItem.bySelectType == ITEM_BAZAAR_POS)
			{
				m_bSelectItem = TRUE;
			}

		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
		
			m_bLButtonDown = FALSE;
			m_byFocusText = TEXT_NON;

			if(g_pGameMain->m_stSelectItem.pSelectItem &&
				g_pGameMain->m_stSelectItem.bySelectType == ITEM_BAZAAR_POS)
			{
				m_bSelectItem = TRUE;
			}

			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				// ������ ��� Ȯ��
				if(m_bBazaarShopStart == FALSE &&
					m_nSelectIndex == m_nScrollLine + i &&
					!m_vecOpenBazaarItem[m_nSelectIndex].bRegister)
				{
					if(GetPointInType(pt,BAZAAR_OPEN_2_SEL,i))
					{
						m_byFocusText = TEXT_PRICE;
						g_pD3dApp->m_bChatMode = TRUE;
						break;
					}
					else if(GetPointInType(pt,BAZAAR_OPEN_3_SEL,i))//BAZAAR_OPEN_3_SEL
					{
						// ���� ������ üũ
						if(IS_COUNTABLE_ITEM(m_vecOpenBazaarItem[m_nSelectIndex].pItemBase->Kind))
						{
							m_byFocusText = TEXT_COUNT;
							g_pD3dApp->m_bChatMode = TRUE;
							m_vecOpenBazaarItem[m_nSelectIndex].nItemCount = 0;
						}
						break;
					}
				}
				else 
				{
				}

				// ������ ����
				if(!g_pGameMain->m_stSelectItem.pSelectItem && m_bSelectItem == FALSE)
				{
					if(pt.x >= BAZAAR_SHOP_ICON_X &&
						pt.x <= BAZAAR_SHOP_ICON_X + BAZAAR_SHOP_ICON_WH &&
						pt.y >= BAZAAR_SHOP_ITEM_Y &&
						pt.y <= BAZAAR_SHOP_ITEM_Y + BAZAAR_SHOP_ITEM_H + (i * BAZAAR_SHOP_ITEM_H))
					{
						int nItemIndex = GetItemIndexByPos(pt.y);
						if(nItemIndex != -1 && m_vecOpenBazaarItem[nItemIndex].bRegister == FALSE)
						{
							POINT ptIcon;
							ptIcon.x = pt.x - BAZAAR_SHOP_ICON_X + 1;
							ptIcon.y = pt.y - (BAZAAR_SHOP_ICON_Y + (i * BAZAAR_SHOP_ITEM_H)) + 1;
							SetSelectItem(m_vecOpenBazaarItem[nItemIndex].pItemBase, ptIcon);
							SetItemInfo(NULL, 0 ,0);
							break;
						}
					}
				}
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			if(m_bBazaarShopStart == FALSE &&
				GetPointInType(pt,BAZAAR_SHOP_ITEM_AREA)&&	//BAZAAR_SHOP_ITEM_AREA
				g_pGameMain->m_stSelectItem.pSelectItem &&
				g_pGameMain->m_stSelectItem.bySelectType == ITEM_INVEN_POS)
			{
				OnSellItem((CItemInfo *)g_pGameMain->m_stSelectItem.pSelectItem->pItem);
				
				// 2008-08-22 by bhsohn EP3 �κ��丮 ó��
				if(g_pGameMain && g_pGameMain->m_pInven)
				{
					// �ʱ�ȭ
					g_pGameMain->SetToolTip(NULL, 0, 0);
					g_pGameMain->m_pInven->SetItemInfo(NULL, 0, 0);						
					g_pGameMain->m_pInven->SetSelectItem(NULL);
				}					
				// end 2008-08-22 by bhsohn EP3 �κ��丮 ó��
			}
			
			//�������� ��ư ó��
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
					GetPointInType(pt,BAZAAR_BTN,i))//BAZAAR_BTN
				{
					int nCurrentItemIndex = GetItemIndexByPos(pt.y);
					m_nPutDelState[i] = BTN_STATE_NORMAL;
					// ������ �Ͱ� �ٸ��� ���
					if(nCurrentItemIndex == m_nSelectIndex)
					{
						if(m_vecOpenBazaarItem[m_nSelectIndex].bRegister)
						{
							// ������ ��� ���
							OnButtonClicked(OPEN_CANCEL);
							return INF_MSGPROC_BREAK;
						}
						else
						{
							// ������ ���
							OnButtonClicked(OPEN_REGISTER);
							return INF_MSGPROC_BREAK;
						}
					}
				}
			}

			// �κ� �丮 ��ġ�� ���̸�
			if(m_bSelectItem &&
				g_pGameMain->m_stSelectItem.pSelectItem &&
				g_pGameMain->m_stSelectItem.bySelectType == ITEM_BAZAAR_POS)
			{
				if(pt.x >= CITY_BASE_NPC_BOX_START_X &&
					pt.x <= BAZAAR_SHOP_WINDOW_X &&
					pt.y >= BAZAAR_SHOP_WINDOW_Y &&
					pt.y <= BAZAAR_SHOP_WINDOW_Y + BAZAAR_SHOP_WINDOW_H)
				{
					OnSellDelItem(g_pGameMain->m_stSelectItem.pSelectItem->pItem->UniqueNumber);
				}

				POINT ptIcon;
				ptIcon.x = 0;
				ptIcon.y = 0;
				SetSelectItem(NULL, ptIcon);
				m_bSelectItem = FALSE;
			}
		}
		break;
		// 2009-01-30 by bhsohn ���� ���� �Է� ��� ����
//	case WM_CHAR:
// 		{
// 			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
// 			{
// 				char code = wParam;
// 				INT64 nTotal;
// 				if(m_byFocusText == TEXT_PRICE)
// 				{
// 					if(code >= '0' && code <= '9' )
// 					{
// 						if(m_nSelectIndex != -1)
// 						{
// 							INT64 nPrice;
// 							nPrice = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
// 					
// 							nPrice *= 10;
// 							nPrice += code - '0';
// 							nTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount * nPrice;
// 							if(nPrice > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
// 								nPrice = MAX_ITEM_COUNTS;
// 							}
// 							else if(nTotal > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
// 								break;
// 							}
// 							else if( nTotal < 0)
// 							{
// 								break;
// 							}
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice = nPrice;
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = nPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 						}
// 					}
// 					else if(code == VK_BACK)
// 					{
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice /= 10;
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 					}
// 				}
// 				else if(m_byFocusText == TEXT_COUNT)
// 				{
// 					if(code >= '0' && code <= '9' )
// 					{
// 						if(m_nSelectIndex != -1)
// 						{
// 							INT64 nCount;
// 							nCount = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 					
// 							nCount *= 10;
// 							nCount += code - '0';
// 							nTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * nCount;
// 							if(nCount > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_050913_0002, _MESSAGE);		// "�������� �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20�ﰳ)"
// 								nCount = MAX_ITEM_COUNTS;
// 							}
// 							else if(nTotal > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
// 								break;
// 							}
// 							else if( nTotal < 0)
// 							{
// 								break;
// 							}
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemCount = nCount;
// 							CheckSellItemCount();				// ������ ���� üũ
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 						}
// 					}
// 					else if(code == VK_BACK)
// 					{
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemCount /= 10;
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 					}
// 				}
// 			}
// 		}
//		break;
	case WM_KEYDOWN:
		{
			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
			{
				DWORD dwCode = lParam;
				INT64 nTotal;
				if(m_byFocusText == TEXT_PRICE)
				{
					int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
					if(nNumber != -1 )
					{
						if(m_nSelectIndex != -1)
						{
							INT64 nPrice;
							nPrice = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
							
							nPrice *= 10;
							nPrice += nNumber;
							nTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount * nPrice;
							if(nPrice > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
								nPrice = MAX_ITEM_COUNTS;
							}
							else if(nTotal > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
								break;
							}
							else if( nTotal < 0)
							{
								break;
							}
							m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice = nPrice;
							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = nPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
						}
					}
					else if(0x000e0001 == dwCode)
					{
						m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice /= 10;
						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
					}
				}
				else if(m_byFocusText == TEXT_COUNT)
				{
					int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
					if(nNumber != -1 )
					{
						if(m_nSelectIndex != -1)
						{
							INT64 nCount;
							nCount = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
							
							nCount *= 10;
							nCount += nNumber;
							nTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * nCount;
							if(nCount > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_050913_0002, _MESSAGE);		// "�������� �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20�ﰳ)"
								nCount = MAX_ITEM_COUNTS;
							}
							else if(nTotal > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
								break;
							}
							else if( nTotal < 0)
							{
								break;
							}
							m_vecOpenBazaarItem[m_nSelectIndex].nItemCount = nCount;
							CheckSellItemCount();				// ������ ���� üũ
							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
						}
					}
					else if(0x000e0001 == dwCode)
					{
						m_vecOpenBazaarItem[m_nSelectIndex].nItemCount /= 10;
						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
					}
				}
			}
		}
		break;
		// end 2009-01-30 by bhsohn ���� ���� ���� �Է� ��� ����
	}
	return INF_MSGPROC_NORMAL;
}

int CINFCityBazaarOpen::WndProc_Buy(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int i;
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			memset(m_nComboState,0,sizeof(m_nComboState));

			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
			
				//������ �������߿� ����Ʈâ�� Ŭ���ߴ��� ��.
				if( GetPointInType(pt,BAZAAR_OPEN_1_BUY,i))
				
				{
					m_nComboState[i][0] = COMBO_UNDER;
				}
				else if(GetPointInType(pt,BAZAAR_OPEN_3_BUY,i))
				{
					//m_byFocusText = TEXT_COUNT;
					m_nComboState[i][1] = COMBO_UNDER;
				}
					
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			memset(m_nComboState,0,sizeof(m_nComboState));
			m_bLButtonDown = FALSE;
			//�޺� �ڽ��� �������� �ʾҴٸ�.
			RenderRect rt;
			if(m_nComboActive == 1)
			{
				rt = m_pComboKindEx->GetComboRect();
				if(!PointInRect(pt,rt))
					m_nComboActive = 0;
			}
			else if(m_nComboActive == 2)
			{
				rt = m_pComboNameEx->GetComboRect();
				if(!PointInRect(pt,rt))
					m_nComboActive = 0;
			}
		
		
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				if(m_bBazaarShopStart == FALSE &&
					m_nSelectIndex == m_nScrollLine + i &&
					!m_vecOpenBazaarItem[m_nSelectIndex].bRegister)
				{
					//������ �������߿� ����Ʈâ�� Ŭ���ߴ��� ��.
					if(GetPointInType(pt,BAZAAR_OPEN_1_BUY,i))
					{
						m_nComboState[i][0] = COMBO_CLICK;
						if(!m_nComboActive)
						{
							m_nComboActive = 1;
							m_pComboKindEx->m_nSelectDataIndex = -1;
							SetDataCombo(m_nComboActive);
							m_pComboKindEx->SetComboPt(BAZAAR_OPEN_1_BUY_X,BAZAAR_OPEN_1_Y + (BAZAAR_SHOP_ITEM_H *i) + BAZAAR_OPEN_1_H);
						}
						break;
					}
					else if(GetPointInType(pt,BAZAAR_OPEN_2_BUY,i))
					{
						// ���� ������ üũ
						if(	m_vecOpenBazaarItem[m_nSelectIndex].pItemBase)
						{
							int nKind =  m_vecOpenBazaarItem[m_nSelectIndex].pItemBase->Kind;
							if(IS_COUNTABLE_ITEM(m_vecOpenBazaarItem[m_nSelectIndex].pItemBase->Kind))
							{
								m_byFocusText = TEXT_COUNT;
								g_pD3dApp->m_bChatMode = TRUE;
								// 2006-08-01 by dgwoo ����â�� Ȱ��ȭ�� 1 -> 0���� ����.
								m_vecOpenBazaarItem[m_nSelectIndex].nItemCount = 0;

							}
						}
						break;
					}
					else if(GetPointInType(pt,BAZAAR_OPEN_3_BUY,i))
					{
						//m_byFocusText = TEXT_COUNT;
						m_nComboState[i][1] = COMBO_CLICK;
						if(!m_nComboActive &&
							m_pComboKindEx->m_nSelectDataIndex >= 0)
						{
							m_nComboActive = 2;
							m_pComboNameEx->m_nSelectDataIndex = -1;
							m_pComboNameEx->SetComboPt(BAZAAR_OPEN_3_BUY_X,BAZAAR_OPEN_3_Y + (BAZAAR_SHOP_ITEM_H *i) + BAZAAR_OPEN_1_H);
						}
						break;
					}
					else if(GetPointInType(pt,BAZAAR_OPEN_4_BUY,i))
					{
						m_byFocusText = TEXT_PRICE;
						g_pD3dApp->m_bChatMode = TRUE;
						break;
					}
					else
					{
						m_byFocusText = TEXT_NON;
					}
				}
				else
				{

					m_byFocusText = TEXT_NON;
				}
			}
			
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			//�������� ��ư ó��
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
					GetPointInType(pt,BAZAAR_BTN,i))
				{
					int nCurrentItemIndex = GetItemIndexByPos(pt.y);
					// ������ �Ͱ� �ٸ��� ���
					if(nCurrentItemIndex == m_nSelectIndex)
					{
						if(m_vecOpenBazaarItem[m_nSelectIndex].bRegister)
						{
							// ������ ��� ���
							OnButtonClicked(OPEN_CANCEL);
						}
						else
						{
							// ������ ���
							OnButtonClicked(OPEN_REGISTER);
						}
					}
					
					m_nPutDelState[i] = BTN_STATE_NORMAL;
				}
			}

			// �޺� �ڽ� �˻�
			if(m_nComboActive == 1)
			{
				if(m_pComboKindEx->m_nSelectDataIndex >= 0)
				{
					// ù��° �޺� ������ �Է� �Ϸ�
					SetDataCombo(2);
					m_nComboActive = 0;
				}
			}
			else if(m_nComboActive == 2)
			{
				if(m_pComboNameEx->m_nSelectDataIndex >= 0)
				{
					m_nComboActive = 0;
					int nItemNum = m_pComboNameEx->m_vecData[m_pComboNameEx->m_nSelectDataIndex].nData;
					int nItemKind = m_pComboKindEx->m_vecData[m_pComboKindEx->m_nSelectDataIndex].nData;
					OnBuyItem(nItemNum, nItemKind);
				}
			}


		}
		break;
		// 2009-01-30 by bhsohn ���� ���� �Է� ��� ����
//	case WM_CHAR:
// 		{
// 			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
// 			{
// 				char code = wParam;
// 				INT64 nTotal;
// 				if(m_byFocusText == TEXT_PRICE)
// 				{
// 					if(code >= '0' && code <= '9' )
// 					{
// 						if(m_nSelectIndex != -1)
// 						{
// 							INT64 nPrice;
// 							nPrice = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
// 							nPrice *= 10;
// 							nPrice += code - '0';
// 							nTotal = nPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 
// 							//������ ������ �ִ� ���Ǻ��� ������ ���Է��� �����ش�.
// 							if(nPrice > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
// 								nPrice = MAX_ITEM_COUNTS;
// 							}
// 							else if(nTotal > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
// 								break;
// 							}
// 							else if( nTotal < 0)
// 							{
// 								break;
// 							}
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice = nPrice;
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = nPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 						}
// 					}
// 					else if(code == VK_BACK)
// 					{
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice /= 10;
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 					}
// 				}
// 				else if(m_byFocusText == TEXT_COUNT)
// 				{
// 					if(code >= '0' && code <= '9' )
// 					{
// 						if(m_nSelectIndex != -1)
// 						{
// 							INT64 nCount;
// 							nCount = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 							nCount *= 10;
// 							nCount += code - '0';
// 
// 							nTotal = nCount * m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
// 
// 							//������ ������ �ִ� ���Ǻ��� ������ ���Է��� �����ش�.
// 							if(nCount > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_050913_0002, _MESSAGE);		// "�������� �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20�ﰳ)"
// 								nCount = MAX_ITEM_COUNTS;
// 							}
// 							else if(nTotal > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
// 								break;
// 							}
// 							else if( nTotal < 0)
// 							{
// 								break;
// 							}
// 							
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemCount = nCount;
// 							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = nCount * m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
// 							// 2006-07-28 by dgwoo ���Կ��� �ʿ����.
// 							//CheckSellItemCount();				// ������ ���� üũ
// 						}
// 					}
// 					else if(code == VK_BACK)
// 					{
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemCount /= 10;
// 						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
// 					}
// 				}
// 			}
// 		}
//		break;
	case WM_KEYDOWN:
		{
			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
			{
				DWORD dwCode = lParam;
				INT64 nTotal;
				if(m_byFocusText == TEXT_PRICE)
				{
					int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
					if(nNumber != -1 )
					{
						if(m_nSelectIndex != -1)
						{
							INT64 nPrice;
							nPrice = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
							nPrice *= 10;
							nPrice += nNumber;
							nTotal = nPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
							
							//������ ������ �ִ� ���Ǻ��� ������ ���Է��� �����ش�.
							if(nPrice > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
								nPrice = MAX_ITEM_COUNTS;
							}
							else if(nTotal > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
								break;
							}
							else if( nTotal < 0)
							{
								break;
							}
							m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice = nPrice;
							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = nPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
						}
					}
					else if(0x000e0001 == dwCode)
					{
						m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice /= 10;
						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
					}
				}
				else if(m_byFocusText == TEXT_COUNT)
				{
					int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
					if(nNumber != -1 )
					{
						if(m_nSelectIndex != -1)
						{
							INT64 nCount;
							nCount = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
							nCount *= 10;
							nCount += nNumber;
							
							nTotal = nCount * m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
							
							//������ ������ �ִ� ���Ǻ��� ������ ���Է��� �����ش�.
							if(nCount > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_050913_0002, _MESSAGE);		// "�������� �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20�ﰳ)"
								nCount = MAX_ITEM_COUNTS;
							}
							else if(nTotal > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
								break;
							}
							else if( nTotal < 0)
							{
								break;
							}
							
							m_vecOpenBazaarItem[m_nSelectIndex].nItemCount = nCount;
							m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = nCount * m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
							// 2006-07-28 by dgwoo ���Կ��� �ʿ����.
							//CheckSellItemCount();				// ������ ���� üũ
						}
					}
					else if(0x000e0001 == dwCode)
					{
						m_vecOpenBazaarItem[m_nSelectIndex].nItemCount /= 10;
						m_vecOpenBazaarItem[m_nSelectIndex].nItemTotal = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice * m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
					}
				}
			}
		}
		break;
	}
	return INF_MSGPROC_NORMAL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::CheckBtnState()
/// \brief		��ư ���� üũ
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::CheckBtnState()
{
	// 2006-07-28 by ispark, ������ ���� ��ư ����
	int i = 0;
	if(m_bBazaarShopStart)
	{
		m_nStartBtnState = BTN_STATE_DEACTIVE;
		m_nStopBtnState = BTN_STATE_NORMAL;

		for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
		{
			m_nPutDelState[i] = BTN_STATE_DEACTIVE;
		}
	}
	else
	{
		m_nStartBtnState = BTN_STATE_NORMAL;
		m_nStopBtnState = BTN_STATE_NORMAL;

		for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
		{
			m_nPutDelState[i] = BTN_STATE_NORMAL;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_RegSellItemOK(MSG_FC_BAZAAR_SELL_PUT_ITEM_OK* pMsg)
/// \brief		������ ���
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_RegSellItemOK(MSG_FC_BAZAAR_SELL_PUT_ITEM_OK* pMsg)
{
	// ������ ��� �Ϸ�
 	OPEN_BAZAAR_ITEM * pItemInfo = FindItem(pMsg->itemUID);
	if(!pItemInfo)
		return;
		
	pItemInfo->bRegister = TRUE;	
	pItemInfo->pItemBase->CurrentCount = pItemInfo->nItemCount;
	// 2007-11-14 by bhsohn ���� ������ ���⸦ �÷ȴ� ��ҽ�, ���� �Ѿ� ���� �߸������� ���� ����	
	if(IS_WEAPON(pItemInfo->pItemBase->Kind))
	{
		// �Ѿ� Ÿ���̴�.
		pItemInfo->pItemBase->CurrentCount = pItemInfo->nBulletCount;
	}

	// �κ��丮 ������ ����
	if(IS_COUNTABLE_ITEM(pItemInfo->pItemBase->Kind))
	{
		CItemInfo* pOrgItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber(pItemInfo->pItemBase->UniqueNumber);
		g_pStoreData->UpdateItemCount(pItemInfo->pItemBase->UniqueNumber, pOrgItemInfo->CurrentCount - pItemInfo->nItemCount);
	}
	else
	{
		g_pStoreData->DeleteItem(pItemInfo->pItemBase->UniqueNumber);
	}

	// �� ���� ���
	CalTotalPrice();

	g_pD3dApp->m_bRequestEnable = TRUE;			// ���� �޼��� �Ϸ�
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_RegBuyItemOK(MSG_FC_BAZAAR_BUY_PUT_ITEM_OK* pMsg)
/// \brief		������ ���
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_RegBuyItemOK(MSG_FC_BAZAAR_BUY_PUT_ITEM_OK* pMsg)
{
	// ������ ��� �Ϸ�
	OPEN_BAZAAR_ITEM * pItemInfo = FindItem(pMsg->itemNum0, 1, TRUE);
	if(!pItemInfo)
		return;
		
	pItemInfo->bRegister = TRUE;
	pItemInfo->nItemIndex = pMsg->nBuyItemIndex0;

	// �� ���� ���
	CalTotalPrice(); 	

	// ���� ��� �غ�
	OnReadyBuyItem();

	m_pComboKindEx->m_nSelectDataIndex = -1;
	g_pD3dApp->m_bRequestEnable = TRUE;			// ���� �޼��� �Ϸ�
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_DelSellItemOK(MSG_FC_BAZAAR_SELL_CANCEL_ITEM_OK* pMsg)
/// \brief		������ ����
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_DelSellItemOK(MSG_FC_BAZAAR_SELL_CANCEL_ITEM_OK* pMsg)
{
	vector<OPEN_BAZAAR_ITEM>::iterator it = FindItemItr(pMsg->itemUID);
	OPEN_BAZAAR_ITEM * item = &*it;

	// �κ��丮 �� ���
	if (IS_COUNTABLE_ITEM(item->pItemBase->Kind))
	{
		CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByItemNum(item->pItemBase->ItemNum);
		if( pItemInfo )
		{
			pItemInfo->CurrentCount += item->pItemBase->CurrentCount;
		}
		else
		{
			g_pStoreData->AddItemDataToUniqueNumberAndWindowPosition(item->pItemBase);
		}
	}
	else
	{
		g_pStoreData->AddItemDataToUniqueNumberAndWindowPosition(item->pItemBase);
	}

	g_pShuttleChild->ResortingItem();
	g_pShuttleChild->SetShuttleData(5);
	g_pGameMain->m_pInven->SetAllIconInfo();
	
	// ����
	if (item)
	{
		m_vecOpenBazaarItem.erase(it);

		// 2010. 02. 11 by ckPark �ߵ��� ����������
		SetItemInfo( NULL, 0, 0 );
		// end 2010. 02. 11 by ckPark �ߵ��� ����������
	}

	//������ �ٽ� ������ش�.
	CalTotalPrice();
	
	g_pD3dApp->m_bRequestEnable = TRUE;			// ���� �޼��� �Ϸ�
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_DelBuyItemOK(MSG_FC_BAZAAR_BUY_CANCEL_ITEM_OK* pMsg)
/// \brief		������ ����
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_DelBuyItemOK(MSG_FC_BAZAAR_BUY_CANCEL_ITEM_OK* pMsg)
{
	// ����
	vector<OPEN_BAZAAR_ITEM>::iterator it = FindItemItr(pMsg->nBuyItemIndex0, 2);
	OPEN_BAZAAR_ITEM * item = &*it;
	if (item)
	{
		util::del(item->pItemBase);
		m_vecOpenBazaarItem.erase(it);

		// 2010. 02. 11 by ckPark �ߵ��� ����������
		SetItemInfo( NULL, 0, 0 );
		// end 2010. 02. 11 by ckPark �ߵ��� ����������
	}

	//������ �ٽ� ������ش�.
	CalTotalPrice();
	
	g_pD3dApp->m_bRequestEnable = TRUE;			// ���� �޼��� �Ϸ�
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::OnSellItem(CItemInfo* pSelectItem)
/// \brief		������ ��� �غ�
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::OnSellItem(CItemInfo* pSelectItem)
{
	// 2006-08-04 by ispark, �Ǹ� ������ ��� �������� ����
	if(!CheckOnSellItem(pSelectItem))
	{
		return;
	}

	// ������ �Է�
	OPEN_BAZAAR_ITEM stSellItem;

	stSellItem.pItemBase = new CItemInfo((ITEM_GENERAL*)pSelectItem);
	stSellItem.pItemBase->ChangeRareInfo(pSelectItem->PrefixCodeNum, pSelectItem->SuffixCodeNum);

	// 2013-06-13 by ssjung ���� ���� �÷��� ����ó�� �߰�(���� ������ �ȵǾ� �� �κп� ���� ������ �ȵ� �� �ֵ���)
#ifdef SC_COLLECTION_ARMOR_JHSEOL_BCKIM
	if(stSellItem.pItemBase->FixedTermShape.nStatShapeItemNum && stSellItem.pItemBase->FixedTermShape.nStatLevel)
	{
		g_pStoreData->RqCollectionShapeChange(stSellItem.pItemBase->UniqueNumber,0);	
	}
#endif
	// end 2013-06-13 by ssjung ���� ���� �÷��� ����ó�� �߰�(���� ������ �ȵǾ� �� �κп� ���� ������ �ȵ� �� �ֵ���)

	// 2010. 02. 11 by ckPark �ߵ��� ����������
	//stSellItem.pItemBase->SetEnchantParam(pSelectItem->GetEnchantParamFactor(),  pSelectItem->GetEnchantNumber());
	// �ߵ��� ��æƮ �� ��Ÿ�� �߰� ����
	stSellItem.pItemBase->CopyItemInfo( pSelectItem );
	// end 2010. 02. 11 by ckPark �ߵ��� ����������

	stSellItem.nItemCount = 1;	

	// 2007-11-14 by bhsohn ���� ������ ���⸦ �÷ȴ� ��ҽ�, ���� �Ѿ� ���� �߸������� ���� ����
	//stSellItem.pItemBase->CurrentCount = 1;
	// ������� �Ѿ˼��� �����Ѵ�.
	if(IS_WEAPON(stSellItem.pItemBase->Kind))
	{
		stSellItem.nBulletCount = stSellItem.pItemBase->CurrentCount;		
	}	
	stSellItem.pItemBase->CurrentCount = 1;	
	// end 2007-11-14 by bhsohn ���� ������ ���⸦ �÷ȴ� ��ҽ�, ���� �Ѿ� ���� �߸������� ���� ����	

	m_vecOpenBazaarItem.push_back(stSellItem);

	// ȭ�� ������ �Ѿ��
	if(m_vecOpenBazaarItem.size() > m_nScrollLine + SHOP_ITEM_SLOT_NUMBER)
	{
		m_nScrollLine++;
		if(m_nScrollLine > BAZAAR_SHOP_SCROLL_MAX_LINE)
		{
			SetScrollEndLine();
		}
		else
		{
			m_nScrollPosition = GetScrollLineInterval(m_nScrollLine);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::OnSellDelItem(UID64_t itemUID)
/// \brief		������ ��� �غ� ����
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::OnSellDelItem(UID64_t itemUID)
{
	vector<OPEN_BAZAAR_ITEM>::iterator it = FindItemItr(itemUID);
	OPEN_BAZAAR_ITEM * item = &*it;

	// ����
	if (item)
	{
		//m_vecOpenBazaarItem.erase(it);
		m_vecOpenBazaarItem.erase(it);

		// 2010. 02. 11 by ckPark �ߵ��� ����������
		SetItemInfo( NULL, 0, 0 );
		// end 2010. 02. 11 by ckPark �ߵ��� ����������
	}

	//������ �ٽ� ������ش�.
	CalTotalPrice();

}

///////////////////////////////////////////////////////////////////////////////
/// \class		PointInRect(POINT &pt,RenderRect &rt);
/// \brief		�����Ϳ� rt �� �Է��Ͽ� �����ִ��� �˾Ƴ��ش�.
///
/// \author		dgwoo
/// \version	
/// \date		2006-07-29 ~ 2006-07-29
/// \warning	
///////////////////////////////////////////////////////////////////////////////
bool CINFCityBazaarOpen::PointInRect(POINT &pt,RenderRect &rt)
{
	if(pt.x > rt.x &&
		pt.x < rt.x + rt.w &&
		pt.y > rt.y &&
		pt.y < rt.y + rt.h)
	{
		return TRUE;
	}
	return FALSE;

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Send_DelItem(int nSelectItem)
/// \brief		������ ���� ��û
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Send_DelItem(int nSelectItem)
{
	// ������ ��� ����
	if(m_nSelectIndex != -1)
	{
	if(m_byBazaarType == 1)
	{
		MSG_FC_BAZAAR_SELL_CANCEL_ITEM sMsg;
		sMsg.itemUID = m_vecOpenBazaarItem[m_nSelectIndex].pItemBase->UniqueNumber;
		g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_SELL_CANCEL_ITEM, (char*)&sMsg, sizeof(sMsg));
	}
	else if(m_byBazaarType == 2)
	{
		MSG_FC_BAZAAR_BUY_CANCEL_ITEM sMsg;
		sMsg.nBuyItemIndex0 = m_vecOpenBazaarItem[m_nSelectIndex].nItemIndex;
		g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_BUY_CANCEL_ITEM, (char*)&sMsg, sizeof(sMsg));
	}
		
	g_pD3dApp->m_bRequestEnable = FALSE;			// ���� �޼��� ��ٸ���
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Send_RegItem(int nSelectItem)
/// \brief		������ ��� ��û
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Send_RegItem(int nSelectItem)
{
	if(m_nSelectIndex != -1)
	{
		// �ʿ� ���� �Ǵ�
		if(m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice <= 0)
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060801_0103 , _MESSAGE);		// "������ �Է��� �ּ���.
			return;
		}
		if(m_vecOpenBazaarItem[m_nSelectIndex].nItemCount <= 0)
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060801_0104 , _MESSAGE);		// "������ �Է��ϼ���.
			return;
		}
	

		// ������ ���
		if(m_byBazaarType == 1)
		{
			// �������� �ʿ� ���� �Ǵ�
			// 2006-08-02 by dgwoo (���� ���� + ����ϴ� �������� �Ѿ�) = 20���� �Ѿ����� ���� ó���Ѵ�.
			int tempSpi = g_pGameMain->m_pInven->GetItemSpi();
			int total = tempSpi + m_nTotal;
			if(MAX_ITEM_COUNTS < total)
			{
				g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005 , _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
				return;
			}

			// �޼��� ����
			MSG_FC_BAZAAR_SELL_PUT_ITEM sMsg;
			sMsg.itemUID = m_vecOpenBazaarItem[m_nSelectIndex].pItemBase->UniqueNumber;
			sMsg.nAmount = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
			sMsg.nEachPrice = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
			g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_SELL_PUT_ITEM, (char*)&sMsg, sizeof(sMsg));
		}
		else if(m_byBazaarType == 2)
		{
			// �������� �ʿ� ���� �Ǵ�
			if(m_vecOpenBazaarItem[m_nSelectIndex].pItemBase == NULL)
			{
				g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060803_0000 , _MESSAGE);		// "�������� �����ϼ���"
				return;
			}
			INT64 tempTotal = m_nTotal + (m_vecOpenBazaarItem[m_nSelectIndex].nItemCount * m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice);
			if(tempTotal > g_pGameMain->m_pInven->GetItemSpi())
			{
				g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060801_0002 ,_MESSAGE);		//	"�������� ���ǰ� �����մϴ�.
				return;
			}

			// �޼��� ����
			MSG_FC_BAZAAR_BUY_PUT_ITEM sMsg;
			sMsg.itemNum0 = m_vecOpenBazaarItem[m_nSelectIndex].pItemBase->ItemNum;
			sMsg.nAmount = m_vecOpenBazaarItem[m_nSelectIndex].nItemCount;
			sMsg.nEachPrice = m_vecOpenBazaarItem[m_nSelectIndex].nItemPrice;
			g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_BUY_PUT_ITEM, (char*)&sMsg, sizeof(sMsg));
		}
	
		g_pD3dApp->m_bRequestEnable = FALSE;			// ���� �޼��� ��ٸ���
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::OnReadyBuyItem()
/// \brief		������ ��� �غ�
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::OnReadyBuyItem()
{
	// ������ ��� MAX�� üũ�Ѵ�.
	if(m_vecOpenBazaarItem.size() == BAZAARSHOP_ITEMCOUNT)
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060728_0000, _MESSAGE);	// "���̻� ����� �� �� �����ϴ�."
		return;
	}

	// ������ �Է�
	OPEN_BAZAAR_ITEM stBuyItem;
	m_vecOpenBazaarItem.push_back(stBuyItem);

	// ȭ�� ������ �Ѿ��
	if(m_vecOpenBazaarItem.size() > m_nScrollLine + SHOP_ITEM_SLOT_NUMBER)
	{
		m_nScrollLine++;
		if(m_nScrollLine > BAZAAR_SHOP_SCROLL_MAX_LINE)
		{
			SetScrollEndLine();
		}
		else
		{
			m_nScrollPosition = GetScrollLineInterval(m_nScrollLine);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::OnBuyItem(int ItemNum)
/// \brief		�޺����� ������ ������ ���
/// \author		ispark
/// \date		2006-07-31 ~ 2006-07-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::OnBuyItem(int ItemNum, int ItemKind)
{
	// 2006-08-04 by ispark, ���� ������ ��� �������� ����
	if(!CheckOnBuyItem(ItemNum, ItemKind))
	{
		return;
	}

	// ������ �Է�
	int nInputItemIndex = m_vecOpenBazaarItem.size() - 1;
	if(nInputItemIndex >= 0)
	{
		if(m_vecOpenBazaarItem[nInputItemIndex].pItemBase)
		{
			util::del(m_vecOpenBazaarItem[nInputItemIndex].pItemBase);
		}

		ITEM_GENERAL stItemBase;
		stItemBase.ItemNum				= ItemNum;
		stItemBase.UniqueNumber			= 0;
		stItemBase.Kind					= ItemKind;
		stItemBase.PrefixCodeNum		= 0;
		stItemBase.SuffixCodeNum		= 0;
		stItemBase.CurrentCount			= 0;

		CItemInfo * pItemInfo = new CItemInfo(&stItemBase);
		m_vecOpenBazaarItem[nInputItemIndex].pItemBase = pItemInfo;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Send_OpenShop()
/// \brief		���� ����
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Send_OpenShop()
{
	//���� ���� ������ �̸��� ���ų� ������ �޽����� �ٿ��.
	if( 2 > strlen(m_strInputMessage))
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060801_0102, _MESSAGE);		// "�����̸��� ���ų� ���ڼ��� 2�ڸ� �����Դϴ�.
		return;
	}
	// 2006-08-01 by dgwoo �⺻������ Sell:0  Buy:1�� ������ �ֱ� ������ �񱳸� �ٸ����Ѵ�.
	if(m_vecOpenBazaarItem.size() <= (m_byBazaarType-1))
	{
// 2011-12-23 by EP4 ���� ���� - [0004975]
		//g_pGameMain->m_pInfWindow->AddMsgBox(STRERR_ERROR_0025, _MESSAGE);			// "�ش� �������� �����ϴ�.
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_111223_0001, _MESSAGE);			// "������ ��� �Ǿ����� �ʽ��ϴ�."
// end 2011-12-23 by EP4 ���� ���� - [0004975]
		return;
	}

	// ���� �� �� �ִ��� üũ
	vector<OPEN_BAZAAR_ITEM>::iterator it = m_vecOpenBazaarItem.begin();
	while(it != m_vecOpenBazaarItem.end())
	{
		// ��� �ȵ� ���� �ִ°�
		if(!it->bRegister)
		{
			if(m_byBazaarType == 2)
			{
				if(!it->pItemBase)
				{
					m_vecOpenBazaarItem.erase(it);

					// 2010. 02. 11 by ckPark �ߵ��� ����������
					SetItemInfo( NULL, 0, 0 );
					// end 2010. 02. 11 by ckPark �ߵ��� ����������

					break;
				}
			}
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060728_0001, _MESSAGE);	// "������ ����� ���ľ� �մϴ�."
			return;
		}

		it++;
	}

	// ������ ���
	if(m_byBazaarType == 1)
	{
		MSG_FC_BAZAAR_SELL_START sMsg;
		strncpy(sMsg.szBazaarName, m_strInputMessage, SIZE_MAX_BAZAAR_NAME);
		g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_SELL_START, (char*)&sMsg, sizeof(sMsg));
	}
	else if(m_byBazaarType == 2)
	{
		MSG_FC_BAZAAR_BUY_START sMsg;
		strncpy(sMsg.szBazaarName, m_strInputMessage, SIZE_MAX_BAZAAR_NAME);
		g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_BUY_START, (char*)&sMsg, sizeof(sMsg));
	}
	
	g_pD3dApp->m_bRequestEnable = FALSE;			// ���� �޼��� ��ٸ���
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Send_CloseShop()
/// \brief		���� �ߴ�
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Send_CloseShop()
{
	m_bBazaarShopEnd = TRUE; // ������ ������ �޼��� �ڽ��� ��� �� ���� ��Ų��.	
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_OpenShopOK()
/// \brief		���� ����
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_OpenShopOK()
{
	m_bBazaarShopStart = TRUE;
	CheckBtnState();

	if(m_byBazaarType == 1)
	{
		if(g_pCharacterChild)
		{
			char szBazaarName [SIZE_MAX_BAZAAR_FULL_NAME];
			
			// 2007-07-09 by bhsohn China Working
			memset(szBazaarName , 0x00, SIZE_MAX_BAZAAR_FULL_NAME);

			wsprintf(szBazaarName, STRMSG_C_060811_0000, m_strInputMessage);
			g_pCharacterChild->m_pMoveChatShop = new CChatMoveData(nullptr, szBazaarName,COLOR_SKILL_USE,11,500,32,240,TRUE, 0x0001);
			g_pCharacterChild->m_pMoveChatShop->InitDeviceObjects();
			g_pCharacterChild->m_pMoveChatShop->RestoreDeviceObjects();
		}
	}
	else if(m_byBazaarType == 2)
	{
		if(g_pCharacterChild)
		{
			char szBazaarName [SIZE_MAX_BAZAAR_FULL_NAME];
			
			// 2007-07-09 by bhsohn China Working
			memset(szBazaarName , 0x00, SIZE_MAX_BAZAAR_FULL_NAME);

			wsprintf(szBazaarName, STRMSG_C_060811_0001, m_strInputMessage);
			g_pCharacterChild->m_pMoveChatShop = new CChatMoveData(nullptr, szBazaarName,GUI_FONT_COLOR_YM,11,500,32,240,TRUE, 0x0001);
			g_pCharacterChild->m_pMoveChatShop->InitDeviceObjects();
			g_pCharacterChild->m_pMoveChatShop->RestoreDeviceObjects();
		}
	}

	char strLogMsg[1024];

	// 2007-07-09 by bhsohn China Working
	memset(strLogMsg, 0x00, 1024);

	ATUM_DATE_TIME tmATime { true };
	string str;
	wsprintf(strLogMsg, STRMSG_C_060730_0004, g_pShuttleChild->m_myShuttleInfo.CharacterName, tmATime.GetLocalDateTimeString(str, TRUE));
	
	CheckLogMsg(strLogMsg, GUI_FONT_COLOR_W);
	g_pD3dApp->m_bRequestEnable = TRUE;			// ���� �޼��� �Ϸ�
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::CalTotalPrice()
/// \brief		�Ѿ� ���
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::CalTotalPrice()
{
	m_nTotal = 0;

	vector<OPEN_BAZAAR_ITEM>::iterator it = m_vecOpenBazaarItem.begin();
	while(it != m_vecOpenBazaarItem.end())
	{
		m_nTotal += it->nItemTotal;

		it++;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CINFCityBazaarOpen::GetItemIndexByPos(int nPosY)
/// \brief		��ġ������ ������ �ε��� ��������
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFCityBazaarOpen::GetItemIndexByPos(int nPosY)
{
	int nItemCount = m_vecOpenBazaarItem.size();
	if(nItemCount >= m_nScrollLine)
	{
		int nPtLine = (nPosY - BAZAAR_SHOP_ITEM_Y) / BAZAAR_SHOP_ITEM_H;

		if(nPtLine + m_nScrollLine < nItemCount)
		{
			return nPtLine + m_nScrollLine;
		}
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CINFCityBazaarOpen::GetShopItemCount(UID64_t itemUID)
/// \brief		
/// \author		ispark
/// \date		2006-08-10 ~ 2006-08-10
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFCityBazaarOpen::GetShopItemCount(UID64_t itemUID)
{
	OPEN_BAZAAR_ITEM* pOpenItem = FindItem(itemUID);

	int nItemCount = 0;

	if(pOpenItem)
	{
		nItemCount = pOpenItem->nItemCount;
	}
	return nItemCount;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(CItemInfo *pItemInfo)
/// \brief		���� ������ ���� ã��
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(CItemInfo *pItemInfo)
{
	vector<OPEN_BAZAAR_ITEM>::iterator it = m_vecOpenBazaarItem.begin();
	while(it != m_vecOpenBazaarItem.end())
	{
		if(it->pItemBase->UniqueNumber == pItemInfo->UniqueNumber)
		{
			return &*it;
		}

		it++;
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(UID64_t itemUID)
/// \brief		������ UID�� ������ ã��
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(UID64_t itemUID)
{
	return &*FindItemItr(itemUID);
}

vector<OPEN_BAZAAR_ITEM>::iterator CINFCityBazaarOpen::FindItemItr(UID64_t itemUID)
{
	vector<OPEN_BAZAAR_ITEM>::iterator it = m_vecOpenBazaarItem.begin();
	while (it != m_vecOpenBazaarItem.end())
	{
		if (it->pItemBase) // 2013-05-14 by ssjung ���Ż��� ���� �κ��� �ִ� ������ ���� �� ����� �ͼ��� ���� ���� 
		{
			if (it->pItemBase->UniqueNumber == itemUID)
			{
				return it;
			}
		}
		it++;
	}

	return m_vecOpenBazaarItem.end();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(int nItemNum, BYTE nItemType, BOOL bRegister)
/// \brief		������ ItemNum�� ������ �ε����� ������ ã��
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(int nItemNum, BYTE nItemType, BOOL bRegister)
{
	return &*FindItemItr(nItemNum, nItemType, bRegister);
}

vector<OPEN_BAZAAR_ITEM>::iterator CINFCityBazaarOpen::FindItemItr(int nItemNum, BYTE nItemType, BOOL bRegister)
{
	vector<OPEN_BAZAAR_ITEM>::iterator it = m_vecOpenBazaarItem.begin();
	while (it != m_vecOpenBazaarItem.end())
	{
		if (nItemType == 1)
		{
			if (it->pItemBase->ItemNum == nItemNum && bRegister == FALSE)
			{
				return it;
			}
			else if (bRegister == TRUE &&
				it->pItemBase->ItemNum == nItemNum &&
				it->bRegister == FALSE)
			{
				return it;
			}
		}
		else if (nItemType == 2)
		{
			if (it->nItemIndex == nItemNum)
			{
				return it;
			}
		}

		it++;
	}

	return m_vecOpenBazaarItem.end();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			CItemInfo *	CINFCityBazaarOpen::GetShopItemInfo(UID64_t itemUID)
/// \brief		������ ��� �� ������ ã��
/// \author		ispark
/// \date		2006-09-04 ~ 2006-09-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
CItemInfo *	CINFCityBazaarOpen::GetShopItemInfo(UID64_t itemUID)
{
	// 2008-12-08 by dgwoo �������� ������� ����.
	OPEN_BAZAAR_ITEM* pItem = FindItem(itemUID);
	if(pItem)
		return pItem->pItemBase;
	return NULL;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::CheckSellItemCount()
/// \brief		�� �κ��丮�� �ִ� ������ ������ ��
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::CheckSellItemCount()
{
	if(m_nSelectIndex != -1)
	{
		CItemInfo* pOnItemInfo = (CItemInfo *)m_vecOpenBazaarItem[m_nSelectIndex].pItemBase;
		CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber(pOnItemInfo->UniqueNumber);
		if(pItemInfo && pItemInfo->CurrentCount < m_vecOpenBazaarItem[m_nSelectIndex].nItemCount)
		{
			m_vecOpenBazaarItem[m_nSelectIndex].nItemCount = pItemInfo->CurrentCount;
		}
	}

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFCityBazaarOpen::CheckBuyCountItem(int nKind, int nItemNum)
/// \brief		
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFCityBazaarOpen::CheckBuyCountItem(int nKind, int nItemNum)
{
	if(IS_COUNTABLE_ITEM(nKind))
	{
		vector<OPEN_BAZAAR_ITEM>::iterator it = m_vecOpenBazaarItem.begin();
		while(it != m_vecOpenBazaarItem.end())
		{
			if(it->pItemBase && it->pItemBase->ItemNum == nItemNum)
			{
				return TRUE;
			}

			it++;
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_SellBuyItemOK(MSG_FC_BAZAAR_SELL_BUY_ITEM_OK* pMsg)
/// \brief		�Ǹ� �������� �ȷ����� 
/// \author		ispark
/// \date		2006-07-31 ~ 2006-07-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_SellBuyItemOK(MSG_FC_BAZAAR_SELL_BUY_ITEM_OK* pMsg)
{
	CEnemyData * pEnemy = NULL;
	CMapEnemyIterator itEnemy = g_pScene->m_mapEnemyList.find(pMsg->clientIndex0);
	if(itEnemy != g_pScene->m_mapEnemyList.end())
	{
		pEnemy = itEnemy->second;
	}

	if(pEnemy)
	{
		vector<OPEN_BAZAAR_ITEM>::iterator pBazaarItemItr = FindItemItr(pMsg->itemUID);
		OPEN_BAZAAR_ITEM* pBazaarItem = &*pBazaarItemItr;
		if(pBazaarItem)
		{
			char strLogMsg[1024];
			ATUM_DATE_TIME tmATime { true };
			string str;
			wsprintf(strLogMsg, STRMSG_C_060731_0000, 
					pEnemy->m_infoCharacter.CharacterInfo.CharacterName, 
					pBazaarItem->pItemBase->ItemInfo->ItemName, 
					pMsg->nAmount0, 
					pMsg->nAmount0 * pBazaarItem->nItemPrice,
					tmATime.GetLocalDateTimeString(str, TRUE));

			CheckLogMsg(strLogMsg, COLOR_SKILL_USE);
			//�Ǹŵ� �������� �׼��� �������ְ� �Ѿ׵� ���� �������ش�.
			pBazaarItem->nItemCount -= pMsg->nAmount0;
			pBazaarItem->pItemBase->CurrentCount = pBazaarItem->nItemCount;
			pBazaarItem->nItemTotal = pBazaarItem->nItemCount * pBazaarItem->nItemPrice;
			m_nTotal = m_nTotal - (pMsg->nAmount0 * pBazaarItem->nItemPrice);

			// 2010. 03. 15 by jskim ������ �������� �춧 �ڽ��� �ƾ��� ������ 2�� �����ϴ� ���� ����
			CItemInfo* pOrgItemInfo = g_pStoreData->FindItemInInventoryByUniqueNumber(pMsg->itemUID);
			if(pOrgItemInfo)
			{
				g_pStoreData->UpdateItemCount(pMsg->itemUID, pOrgItemInfo->CurrentCount - pBazaarItem->nItemCount);
			}
			//end 2010. 03. 15 by jskim ������ �������� �춧 �ڽ��� �ƾ��� ������ 2�� �����ϴ� ���� ����
			// ������ �� �� 0 ���ϸ� ����
			if(pBazaarItem->nItemCount <= 0)
			{
				util::del(pBazaarItem->pItemBase);
				//m_vecOpenBazaarItem.erase(pBazaarItem);
				m_vecOpenBazaarItem.erase(pBazaarItemItr);

				// 2010. 02. 11 by ckPark �ߵ��� ����������
				SetItemInfo( NULL, 0, 0 );
				// end 2010. 02. 11 by ckPark �ߵ��� ����������

				if(m_vecOpenBazaarItem.size() <= 0)
				{
					// ��� �ȸ��ų� ������ �κ�
				}
			}
		}
	}
	else
	{
		CMapEnemyIterator itEnemy = g_pScene->m_mapEnemyList.begin();
		while(itEnemy != g_pScene->m_mapEnemyList.end())
		{
			DbgOutA("����� �ѹ� ���� (%d)\n", itEnemy->second->m_infoCharacter.CharacterInfo.ClientIndex);
			itEnemy++;
		}

		DbgOutA("����� �ѹ� ���� (%d)\n", pMsg->clientIndex0);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_BuySellItemOK(MSG_FC_BAZAAR_BUY_SELL_ITEM_OK* pMsg)
/// \brief		���Ի������� �Ǹŵ�����.
/// \author		ispark
/// \date		2006-07-31 ~ 2006-07-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_BuySellItemOK(MSG_FC_BAZAAR_BUY_SELL_ITEM_OK* pMsg)
{
	CEnemyData * pEnemy = NULL;
	CMapEnemyIterator itEnemy = g_pScene->m_mapEnemyList.find(pMsg->clientIndex0);
	if(itEnemy != g_pScene->m_mapEnemyList.end())
	{
		pEnemy = itEnemy->second;
	}

	if(pEnemy)
	{
		vector<OPEN_BAZAAR_ITEM>::iterator pBazaarItemItr = FindItemItr(pMsg->nBuyItemIndex0, 2);
		OPEN_BAZAAR_ITEM* pBazaarItem = &*pBazaarItemItr;
		if(pBazaarItem)
		{
			char strLogMsg[1024];
			ATUM_DATE_TIME tmATime { true };
			string str;
			wsprintf(strLogMsg, STRMSG_C_060731_0002, 
					pEnemy->m_infoCharacter.CharacterInfo.CharacterName, 
					pBazaarItem->pItemBase->ItemInfo->ItemName, 
					pMsg->nAmount0, 
					pMsg->nAmount0 * pBazaarItem->nItemPrice,
					tmATime.GetLocalDateTimeString(str, TRUE));

			CheckLogMsg(strLogMsg, GUI_FONT_COLOR_YM);
			pBazaarItem->nItemCount -= pMsg->nAmount0;
			pBazaarItem->nItemTotal = pBazaarItem->nItemCount * pBazaarItem->nItemPrice;
			m_nTotal = m_nTotal - (pMsg->nAmount0 * pBazaarItem->nItemPrice);

			// ������ �� �� 0 ���ϸ� ����
			if(pBazaarItem->nItemCount <= 0)
			{
				//m_vecOpenBazaarItem.erase(pBazaarItem);
				m_vecOpenBazaarItem.erase(pBazaarItemItr);

				// 2010. 02. 11 by ckPark �ߵ��� ����������
				SetItemInfo( NULL, 0, 0 );
				// end 2010. 02. 11 by ckPark �ߵ��� ����������

				if(m_vecOpenBazaarItem.size() <= 0)
				{
					// ��� �ȸ��ų� ������ �κ�
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			�湮�� �α� �Է�
/// \brief		
/// \author		ispark
/// \date		2006-07-31 ~ 2006-07-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::Recv_CustomerInfoOK(MSG_FC_BAZAAR_CUSTOMER_INFO_OK* pMsg)
{
	CEnemyData * pEnemy = NULL;
	CMapEnemyIterator itEnemy = g_pScene->m_mapEnemyList.find(pMsg->clientIndex0);
	if(itEnemy != g_pScene->m_mapEnemyList.end())
	{
		pEnemy = itEnemy->second;
	}

	if(pEnemy)
	{
		char strLogMsg[1024];
		ATUM_DATE_TIME tmATime { true };
		string str;
		wsprintf(strLogMsg, STRMSG_C_060731_0001, pEnemy->m_infoCharacter.CharacterInfo.CharacterName, tmATime.GetLocalDateTimeString(str, TRUE));
		CheckLogMsg(strLogMsg, GUI_FONT_COLOR_W);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::CheckLogMsg(char * msgLog, DWORD dwColor)
/// \brief		�α� �޼��� üũ
/// \author		ispark
/// \date		2006-08-01 ~ 2006-08-01
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::CheckLogMsg(char * msgLog, DWORD dwColor)
{
	int nMsgCount = 1;
	vector<string> vecChatMessage;
	vecChatMessage.clear();
	STRING_CULL(msgLog, BAZAAR_SHOP_LOG_STRING_LENGTH, &vecChatMessage, m_pFontLogMsg);

	for(int i = 0; i < vecChatMessage.size(); i++)
	{
		m_LogChat.PushChatLine((char*)vecChatMessage[i].c_str(), dwColor);
	}

	if(m_byTabIndex == 1)
	{
		m_nScrollMaxCount = m_LogChat.m_nStoredLineCounts;
		SetScrollEndLine();
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFCityBazaarOpen::CheckOnSellItem(CItemInfo* pSelectItem)
/// \brief		��� ������ �Ǹ� ���������� ����
/// \author		ispark
/// \date		2006-08-04 ~ 2006-08-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFCityBazaarOpen::CheckOnSellItem(CItemInfo* pSelectItem)
{
	// �ߺ��� �ִ��� ã�´�.
	// ������ ��� MAX�� üũ�Ѵ�.
	// ������������ ���� ���ϰ� �Ѵ�.
	if(pSelectItem->Wear != WEAR_NOT_ATTACHED)
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_SHOP_0010, _MESSAGE);		// "������ �������� �� �� �����ϴ�."
		return FALSE;
	}
	else if(FindItem(pSelectItem))
	{
		// �ߺ�
		g_pGameMain->m_pInfWindow->AddMsgBox(STRERR_ERROR_0140, _MESSAGE);		// "��Ͽ� �̹� ��ϵǾ� �ֽ��ϴ�."
		return FALSE;
	}
	else if(m_vecOpenBazaarItem.size() == BAZAARSHOP_ITEMCOUNT)
	{
		// ��� MAX
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060728_0000, _MESSAGE);	// "���̻� ����� �� �� �����ϴ�."
		return FALSE;
	}
	else if(!COMPARE_BIT_FLAG(pSelectItem->ItemInfo->ItemAttribute, ITEM_ATTR_BAZAAR_ITEM))
	{
		// �ŷ� �� �� ���� ������
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060728_0003, _MESSAGE);	// "����� �� �� ���� ������ �Դϴ�."
		return FALSE;
	}

	// ������ ��� üũ
	int nItemListCount = m_vecOpenBazaarItem.size();
	if(nItemListCount > 0)
	{
		if(!m_vecOpenBazaarItem[nItemListCount - 1].bRegister)
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060728_0001, _MESSAGE);	// "������ ����� ���ľ� �մϴ�."
			return FALSE;
		}
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			BOOL CINFCityBazaarOpen::CheckOnBuyItem(int nItemNum, int nItemKind)
/// \brief		��� ������ ���� ���������� ����
/// \author		ispark
/// \date		2006-08-04 ~ 2006-08-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
BOOL CINFCityBazaarOpen::CheckOnBuyItem(int nItemNum, int nItemKind)
{
	if(CheckBuyCountItem(nItemKind, nItemNum))
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060803_0004, _MESSAGE);		// "���� �������� �ߺ� ����� �� �� �����ϴ�."
		m_pComboNameEx->m_nSelectDataIndex = -1;
		return FALSE;
	}

	return TRUE;
}
///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::OnButtonClicked(int nButton)
/// \brief		��ư ���� ó�� ���� �Լ�
/// \author		ispark
/// \date		2006-08-04 ~ 2006-08-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::OnButtonClicked(int nButton)
{
	if(nButton == OPEN_START)
	{
		// ���� ����
		Send_OpenShop();
	}
	else if(nButton == OPEN_END)
	{
		// ���� Ŭ����
		Send_CloseShop();
	}
	else if(nButton == OPEN_REGISTER)
	{
		// ������ ���
		Send_RegItem(m_nSelectIndex);
	}
	else if(nButton == OPEN_CANCEL)
	{
		// ������ ��� ���
		Send_DelItem(m_nSelectIndex);
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::InitOpenData()
/// \brief		���� ���� ����Ÿ �ʱ�ȭ, �Ǹ� ������ ���� �κ��丮�� �����
/// \author		ispark
/// \date		2006-08-04 ~ 2006-08-04
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::InitOpenData()
{
	vector<OPEN_BAZAAR_ITEM>::iterator it = m_vecOpenBazaarItem.begin();
	while(it != m_vecOpenBazaarItem.end())
	{
		// �Ǹ� ������ �κ��丮�� �����
		if(m_byBazaarType == 1 && it->bRegister)
		{
			if(IS_COUNTABLE_ITEM(it->pItemBase->Kind))
			{
				CItemInfo* pItemInfo = g_pStoreData->FindItemInInventoryByItemNum(it->pItemBase->ItemNum);
				if( pItemInfo )
				{
					pItemInfo->CurrentCount += it->nItemCount;
				}
				else
				{
					g_pStoreData->AddItemDataToUniqueNumberAndWindowPosition( it->pItemBase );
				}
			}
			else
			{
				g_pStoreData->AddItemDataToUniqueNumberAndWindowPosition( it->pItemBase );
			}
		}
		else
		{
			util::del(it->pItemBase);
		}
		it++;
	}

	if(m_vecOpenBazaarItem.size() > 0 && m_byBazaarType == 1)
	{
		g_pShuttleChild->ResortingItem();
		g_pShuttleChild->SetShuttleData(5);
		if(g_pGameMain && g_pGameMain->m_pInven)
		{
			g_pGameMain->m_pInven->SetAllIconInfo();
		}
	}
	
	m_vecOpenBazaarItem.clear();

	// 2010. 02. 11 by ckPark �ߵ��� ����������
	SetItemInfo( NULL, 0, 0 );
	// end 2010. 02. 11 by ckPark �ߵ��� ����������
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::SetSelectItem(CItemInfo* pSelectItem, POINT pt)
/// \brief		������ ����
/// \author		ispark
/// \date		2006-08-07 ~ 2006-08-07
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarOpen::SetSelectItem(CItemInfo* pSelectItem, POINT pt)
{
	if(pSelectItem != NULL)
	{
		// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

		//wsprintf(m_DisplayInfo.IconName, "%08d", pSelectItem->ItemInfo->SourceIndex);
		ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( pSelectItem->GetShapeItemNum() );

		int tempSourceIndex = NULL;
		if( pShapeItem )
		{
			tempSourceIndex = pShapeItem->SourceIndex;
		}
		else
		{
			tempSourceIndex = pSelectItem->ItemInfo->SourceIndex;
		}

		wsprintf( m_DisplayInfo.IconName, "%08d", tempSourceIndex );	
		// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

		wsprintf(m_DisplayInfo.Name, "%s", pSelectItem->ItemInfo->ItemName);
		m_DisplayInfo.pItem = pSelectItem;

		g_pGameMain->SetSelectItem(&m_DisplayInfo, pt, ITEM_BAZAAR_POS);
	}
	else
	{
		memset(m_DisplayInfo.IconName, 0x00, sizeof(m_DisplayInfo.IconName));
		memset(m_DisplayInfo.Name, 0x00, sizeof(m_DisplayInfo.Name));
		m_DisplayInfo.pItem = NULL;

		g_pGameMain->SetSelectItem(NULL, pt, ITEM_BAZAAR_POS);
	}
}










//////////////////////////////////////////////////////////////////////////
// ���� ���� �湮��
CINFCityBazaarVisit::CINFCityBazaarVisit(CAtumNode* pParent, CGameData* pGameData, int nBazaarType, ClientIndex_t clientIndex)
{
	m_pParent			= pParent;	// CGameMain*
	m_pGameData			= pGameData;

	m_nScrollLine		= 0;
	m_nSelectIndex		= -1;
	m_nSum				= 0;
	m_byFocusText		= TEXT_NON;
	m_nOutBtnState		= BTN_STATE_NORMAL;

	m_byBazaarType		= nBazaarType;
	m_ClientIndex		= clientIndex;
	m_nSum				= 0;

	// �ʱ�
	m_nScrollMaxCount = BAZAARSHOP_ITEMCOUNT;
	m_nScrollMaxLine  = SHOP_ITEM_SLOT_NUMBER;
	m_bBazaarMinAct	  = TRUE;

	m_byBazaarTypeState	= 2;
}

CINFCityBazaarVisit::~CINFCityBazaarVisit()
{

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::InitVisitData()
/// \brief		������ ����Ÿ �ʱ�ȭ
/// \author		ispark
/// \date		2006-08-02 ~ 2006-08-02
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::InitVisitData()
{
	vector<VISIT_BAZAAR_ITEM>::iterator it = m_vecVisitBazaarItem.begin();
	while(it != m_vecVisitBazaarItem.end())
	{
		util::del(it->pItemInfo);
		it++;
	}
	m_vecVisitBazaarItem.clear();

	// 2010. 02. 11 by ckPark �ߵ��� ����������
	SetItemInfo( NULL, 0, 0 );
	// end 2010. 02. 11 by ckPark �ߵ��� ����������

	if(g_pGameMain)
		g_pGameMain->SetItemInfo( 0, 0, 0, 0);

	m_nScrollLine		= 0;
	m_nSelectIndex		= -1;
	m_nSum				= 0;
	m_nScrollMaxCount = BAZAARSHOP_ITEMCOUNT;
	m_nScrollMaxLine  = SHOP_ITEM_SLOT_NUMBER;
}

HRESULT CINFCityBazaarVisit::InitDeviceObjects()
{
	int i;
	char buf[16] = {0,};
	DataHeader	* pDataHeader;
	
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	pDataHeader = g_pGameMain->m_GruopImagemanager->FindResource("Psh");
	m_pBackWindow = g_pGameMain->m_GruopImagemanager->GetGroupImage( pDataHeader );
	m_pBackWindow->InitDeviceObjects( g_pD3dApp->m_pImageList );

	m_pBackListBox = new CINFImageEx;
	wsprintf(buf, "BackList");
	pDataHeader = FindResource(buf);
	m_pBackListBox->InitDeviceObjects( pDataHeader );	
	
	for(i = 0; i < 4; i++)
	{
		//��� ��ư
		m_pDelItemBtn[i] = new CINFImageEx;
		wsprintf(buf, "cans0%d",i);
		pDataHeader = FindResource(buf);
		m_pDelItemBtn[i]->InitDeviceObjects(pDataHeader );
		
		//������ ��ư.
		m_pStopBtn[i] = new CINFImageEx;
		wsprintf(buf, "cans0%d",i);
		pDataHeader = FindResource(buf);
		m_pStopBtn[i]->InitDeviceObjects(pDataHeader );
	}
#else
	m_pBackWindow = new CINFImageEx;
	wsprintf(buf,"sellback");
	pDataHeader = FindResource(buf);
	m_pBackWindow->InitDeviceObjects(pDataHeader );
	
	for(i = 0; i < 4; i++)
	{
		//��� ��ư
		m_pDelItemBtn[i] = new CINFImageEx;
		wsprintf(buf, "canBtn_%d",i);
		pDataHeader = FindResource(buf);
		m_pDelItemBtn[i]->InitDeviceObjects(pDataHeader );

		//������ ��ư.
		m_pStopBtn[i] = new CINFImageEx;
		wsprintf(buf, "exitBtn_%d",i);
		pDataHeader = FindResource(buf);
		m_pStopBtn[i]->InitDeviceObjects(pDataHeader );
	}
#endif
	//����Ʈ ���.
	m_pBackList = new CINFImageEx;
	wsprintf(buf, "BackList");
	pDataHeader = FindResource(buf);
	m_pBackList->InitDeviceObjects(pDataHeader );

	//�հ� ���.
	m_pSum = new CINFImageEx;
	wsprintf(buf, "BackSum");
	pDataHeader = FindResource(buf);
	m_pSum->InitDeviceObjects(pDataHeader );

	// ��ũ�� ��ư
	m_pScrollButton = new CINFImageEx;
	pDataHeader = FindResource("c_scrlb");
	m_pScrollButton->InitDeviceObjects(pDataHeader ) ;	

	/*--------------------------------------------------------------------------*/
	// ���� ���� Ÿ�Կ� ���� �̹���
	//�� ���.
	m_pBackTab = new CINFImageEx;
	wsprintf(buf, "BackTabV_%d", m_byBazaarType - 1);
	pDataHeader = FindResource(buf);
	m_pBackTab->InitDeviceObjects(pDataHeader );

	//������ ���.
	m_pBackItem = new CINFImageEx;
	wsprintf(buf, "BackItemV_%d", m_byBazaarType - 1);
	pDataHeader = FindResource(buf);
	m_pBackItem->InitDeviceObjects(pDataHeader );

#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	// ���� ���
	m_pSelectBar = new CINFImageEx;
	pDataHeader = FindResource("Selitem");
	m_pSelectBar->InitDeviceObjects(pDataHeader );

	if(m_byBazaarType == 1)
	{
		for(i = 0; i < 4; i++)
		{
			//���� ��ư.
			m_pOKBtn[i] = new CINFImageEx;
			wsprintf(buf, "oks0%d",i);
			pDataHeader = FindResource(buf);
			m_pOKBtn[i]->InitDeviceObjects(pDataHeader );
		}

	}
	else if(m_byBazaarType == 2)
	{
		for(i = 0; i < 4; i++)
		{
			//�Ǹ� ��ư.
			m_pOKBtn[i] = new CINFImageEx;
			wsprintf(buf, "oks0%d",i);
			pDataHeader = FindResource(buf);
			m_pOKBtn[i]->InitDeviceObjects(pDataHeader );
		}
	}
#else
	m_pSelectBar = new CINFImageEx;
	wsprintf(buf, "SelItemV_%d", m_byBazaarType - 1);
	pDataHeader = FindResource(buf);
	m_pSelectBar->InitDeviceObjects(pDataHeader );

	if(m_byBazaarType == 1)
	{
		for(i = 0; i < 4; i++)
		{
			//���� ��ư.
			m_pOKBtn[i] = new CINFImageEx;
			wsprintf(buf, "buyBtn_%d",i);
			pDataHeader = FindResource(buf);
			m_pOKBtn[i]->InitDeviceObjects(pDataHeader );
		}

	}
	else if(m_byBazaarType == 2)
	{
		for(i = 0; i < 4; i++)
		{
			//�Ǹ� ��ư.
			m_pOKBtn[i] = new CINFImageEx;
			wsprintf(buf, "sellBtn_%d",i);
			pDataHeader = FindResource(buf);
			m_pOKBtn[i]->InitDeviceObjects(pDataHeader );
		}
	}
#endif
	/*--------------------------------------------------------------------------*/
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	// 2006-11-01 by dgwoo	
	//m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_VISIT_NAME_W,32);
	m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,256,32);
	m_pFontItemName->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_VISIT_SEL_PRICE_W,32);
	m_pFontItemPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemPrice->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_VISIT_SEL_COUNT_W,32);
	m_pFontItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,64,32);
	m_pFontItemCount->InitDeviceObjects(g_pD3dDev);
	//m_pFontBuySellItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,BAZAAR_VISIT_SEL_COUNT_W,32);
	m_pFontBuySellItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,64,32);
	m_pFontBuySellItemCount->InitDeviceObjects(g_pD3dDev);

	m_pFontSumPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontSumPrice->InitDeviceObjects(g_pD3dDev);
#else
	// 2006-11-01 by dgwoo	
	//m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_VISIT_NAME_W,32);
	m_pFontItemName = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,256,32);
	m_pFontItemName->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_VISIT_SEL_PRICE_W,32);
	m_pFontItemPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontItemPrice->InitDeviceObjects(g_pD3dDev);
	//m_pFontItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,BAZAAR_VISIT_SEL_COUNT_W,32);
	m_pFontItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,64,32);
	m_pFontItemCount->InitDeviceObjects(g_pD3dDev);
	//m_pFontBuySellItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,BAZAAR_VISIT_SEL_COUNT_W,32);
	m_pFontBuySellItemCount = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),8, D3DFONT_ZENABLE, TRUE,64,32);
	m_pFontBuySellItemCount->InitDeviceObjects(g_pD3dDev);

	m_pFontSumPrice = new CD3DHanFont(_T(g_pD3dApp->GetFontStyle()),9, D3DFONT_ZENABLE, TRUE,128,32);
	m_pFontSumPrice->InitDeviceObjects(g_pD3dDev);
#endif
	return S_OK;
}

HRESULT CINFCityBazaarVisit::RestoreDeviceObjects()
{
	int i;
	m_pBackWindow->RestoreDeviceObjects();
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	m_pBackListBox->RestoreDeviceObjects();	
#endif
	for(i = 0; i < 4; i++)
	{
		m_pDelItemBtn[i]->RestoreDeviceObjects();
		m_pOKBtn[i]->RestoreDeviceObjects();
		m_pStopBtn[i]->RestoreDeviceObjects();
	}

	m_pBackTab->RestoreDeviceObjects();
	m_pBackItem->RestoreDeviceObjects();
	m_pSum->RestoreDeviceObjects();
	m_pBackList->RestoreDeviceObjects();
	m_pScrollButton->RestoreDeviceObjects();
	m_pSelectBar->RestoreDeviceObjects();


	m_pFontItemName->RestoreDeviceObjects();
	m_pFontItemPrice->RestoreDeviceObjects();
	m_pFontItemCount->RestoreDeviceObjects();
	m_pFontBuySellItemCount->RestoreDeviceObjects();

	m_pFontSumPrice->RestoreDeviceObjects();

	return S_OK;
}

HRESULT CINFCityBazaarVisit::DeleteDeviceObjects()
{
	int i;
	m_pBackWindow->DeleteDeviceObjects();
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	m_pBackListBox->DeleteDeviceObjects();	
	util::del(m_pBackListBox);
#endif
	for(i = 0; i < 4; i++)
	{
		m_pDelItemBtn[i]->DeleteDeviceObjects();
		m_pOKBtn[i]->DeleteDeviceObjects();
		m_pStopBtn[i]->DeleteDeviceObjects();
		util::del(m_pDelItemBtn[i]);
		util::del(m_pOKBtn[i]);
		util::del(m_pStopBtn[i]);
	}

	m_pBackTab->DeleteDeviceObjects();
	m_pBackItem->DeleteDeviceObjects();
	m_pSum->DeleteDeviceObjects();
	m_pBackList->DeleteDeviceObjects();
	m_pScrollButton->DeleteDeviceObjects();
	m_pSelectBar->DeleteDeviceObjects();
	util::del(m_pBackTab);
	util::del(m_pBackItem);
	util::del(m_pSum);
	util::del(m_pBackList);
	util::del(m_pScrollButton);
	util::del(m_pSelectBar);


	m_pFontItemName->DeleteDeviceObjects();
	m_pFontItemPrice->DeleteDeviceObjects();
	m_pFontItemCount->DeleteDeviceObjects();
	m_pFontBuySellItemCount->DeleteDeviceObjects();
	util::del(m_pFontBuySellItemCount);
	util::del(m_pFontItemName);
	util::del(m_pFontItemPrice);
	util::del(m_pFontItemCount);

	m_pFontSumPrice->DeleteDeviceObjects();
	util::del(m_pFontSumPrice);

	InitVisitData();									// 2006-08-02 by ispark
	// 2009-04-13 by bhsohn ���� ���� �����ִ���, �Ʒ��� ���ӽ� ���� ����
// 	g_pGameMain->m_pInfWindow->DeleteMsgBox(_Q_BAZAAR_BUY_OK);
// 	g_pGameMain->m_pInfWindow->DeleteMsgBox(_Q_BAZAAR_SELL_OK);
	if(g_pGameMain && g_pGameMain->m_pInfWindow)
	{
		g_pGameMain->m_pInfWindow->DeleteMsgBox(_Q_BAZAAR_BUY_OK);
		g_pGameMain->m_pInfWindow->DeleteMsgBox(_Q_BAZAAR_SELL_OK);
	}
	// end 2009-04-13 by bhsohn ���� ���� �����ִ���, �Ʒ��� ���ӽ� ���� ����

	return S_OK;
}

HRESULT CINFCityBazaarVisit::InvalidateDeviceObjects()
{
	int i;
	m_pBackWindow->InvalidateDeviceObjects();
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	m_pBackListBox->InvalidateDeviceObjects();
#endif
	for(i = 0; i < 4; i++)
	{
		m_pDelItemBtn[i]->InvalidateDeviceObjects();
		m_pOKBtn[i]->InvalidateDeviceObjects();
		m_pStopBtn[i]->InvalidateDeviceObjects();
	}

	m_pBackTab->InvalidateDeviceObjects();
	m_pBackItem->InvalidateDeviceObjects();
	m_pSum->InvalidateDeviceObjects();
	m_pBackList->InvalidateDeviceObjects();
	m_pScrollButton->InvalidateDeviceObjects();
	m_pSelectBar->InvalidateDeviceObjects();

	m_pFontItemName->InvalidateDeviceObjects();
	m_pFontItemPrice->InvalidateDeviceObjects();
	m_pFontItemCount->InvalidateDeviceObjects();
	m_pFontBuySellItemCount->InvalidateDeviceObjects();

	m_pFontSumPrice->InvalidateDeviceObjects();

	return S_OK;
}

void CINFCityBazaarVisit::Render()
{

	if ( GetbBazaarShopEnd() )
		return;

	// ������ �κ��丮
	g_pGameMain->m_pInven->RenderOnCityBase();

	/*--------------------------------------------------------------------------*/
	// ���� �̹���
	Render_Common();

	/*--------------------------------------------------------------------------*/
	// Ÿ�Ժ� �̹���
	if(m_byBazaarType == 1)
	{
		Render_Sell();
	}
	else if(m_byBazaarType == 2)
	{
		Render_Buy();
	}
}

void CINFCityBazaarVisit::Render_Common()
{
	//���� ���� ���.
	m_pBackWindow->Move(BAZAAR_SHOP_WINDOW_X,BAZAAR_SHOP_WINDOW_Y);
	m_pBackWindow->Render();

	m_pBackTab->Move(BAZAAR_SHOP_TAB_START_X, BAZAAR_SHOP_TAB_START_Y);
	m_pBackTab->Render();

#ifndef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	m_pBackList->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y);
	m_pBackList->Render();
#endif
	//�հ�
	m_pSum->Move(BAZAAR_VISIT_TOTAL_PRICE_X, BAZAAR_VISIT_TOTAL_PRICE_Y);
	m_pSum->Render();

	char temp1[64];
	char temp2[64];
	wsprintf( temp1, "%d", m_nSum );
	MakeCurrencySeparator( temp2, temp1, 3, ',' );

	//������ ������ ����..
	SIZE texSize = m_pFontSumPrice->GetStringSize(temp2);
	m_pFontSumPrice->DrawText(BAZAAR_VISIT_TOTAL_PRICE_X+BAZAAR_VISIT_TOTAL_PRICE_W-texSize.cx,BAZAAR_VISIT_TOTAL_PRICE_Y, GUI_FONT_COLOR_W,temp2, 0L);

	// ������
	m_pStopBtn[m_nOutBtnState]->Move(BAZAAR_VISIT_OUT_X, BAZAAR_VISIT_OUT_Y);
	m_pStopBtn[m_nOutBtnState]->Render();

	// ��ũ��
	m_pScrollButton->Move(BAZAAR_SHOP_VISIT_SCROLL_X, BAZAAR_SHOP_SCROLL_Y + m_nScrollPosition);
	m_pScrollButton->Render();
}

void CINFCityBazaarVisit::Render_Sell()
{
	/*--------------------------------------------------------------------------*/
	//������ ��� �ִ� �� ����.	
	int i = 0;
	int nItemCount = m_vecVisitBazaarItem.size();
#ifndef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	if(nItemCount < m_nScrollLine)
		return;
#endif
	
	vector<VISIT_BAZAAR_ITEM>::iterator ite = m_vecVisitBazaarItem.begin();
	while(ite != m_vecVisitBazaarItem.end())
	{
		int nLineCount = i - m_nScrollLine;
		if(nLineCount >= 0)
		{
			if(nLineCount >= SHOP_ITEM_SLOT_NUMBER)
			{
				break;
			}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
			m_pBackListBox->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + ( nLineCount * BAZAAR_SHOP_ITEM_H ) );
			m_pBackListBox->Render();
			
			m_pBackItem->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
			m_pBackItem->Render();
			// ����
			if(m_nSelectIndex == i)
			{
				m_pSelectBar->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pSelectBar->Render();
			}
#else
			// ����
			if(m_nSelectIndex == i)
			{
				m_pSelectBar->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pSelectBar->Render();
			}
			else
			{
				m_pBackItem->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pBackItem->Render();
			}
#endif


			// ������
			SIZE size;
			char buf[64] = {0,};
			char buf1[64] = {0,};


			// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����
			//wsprintf(buf, "%08d", ite->pItemInfo->ItemInfo->SourceIndex);
			if( !ite->pItemInfo->ShapeItemNum )
				wsprintf(buf, "%08d", ite->pItemInfo->ItemInfo->SourceIndex);
			else
			{
				ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( ite->pItemInfo->ShapeItemNum );
				if( pShapeItem )
					wsprintf(buf, "%08d", pShapeItem->SourceIndex );
				else
					wsprintf(buf, "%08d", ite->pItemInfo->ItemInfo->SourceIndex );
					
			}
			// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����


			g_pGameMain->m_pIcon->SetIcon(buf, BAZAAR_SHOP_ICON_X, BAZAAR_SHOP_ICON_Y + (nLineCount * BAZAAR_SHOP_ITEM_H), 1.0f);
			g_pGameMain->m_pIcon->Render();

			// 2010. 02. 11 by ckPark �ߵ��� ����������
			if( (*ite).pItemInfo->ItemInfo->InvokingDestParamID
				|| (*ite).pItemInfo->ItemInfo->InvokingDestParamIDByUse )
			{
				char buf[128];

				if( GetString_CoolTime( (*ite).pItemInfo, buf ) )
				{
					int nFontPosX = BAZAAR_SHOP_ICON_X;
					int nFontPosY = BAZAAR_SHOP_ICON_Y + (nLineCount * BAZAAR_SHOP_ITEM_H) + 6;

					m_pFontItemName->DrawText( nFontPosX, nFontPosY, GUI_FONT_COLOR, buf, 0L );
				}
			}
			// end 2010. 02. 11 by ckPark �ߵ��� ����������

			// ������ �Ǹ� ����
			if(ite->nAmount0 > 1)
			{
				wsprintf( buf1, "%d", ite->nAmount0);
				size = m_pFontBuySellItemCount->GetStringSize(buf1);
				m_pFontBuySellItemCount->DrawText(BAZAAR_VISIT_SEL_ITEM_COUNT_X-size.cx,BAZAAR_VISIT_SEL_ITEM_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			}

			// ������ �̸�
			wsprintf(buf1,"%s", ite->cItemName);
			m_pFontItemName->DrawText(BAZAAR_VISIT_NAME_X,BAZAAR_VISIT_NAME_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);

			// ����
			wsprintf( buf1, "%d", ite->nEachPrice0);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontItemPrice->GetStringSize(buf);
		    m_pFontItemPrice->DrawText(BAZAAR_VISIT_SEL_PRICE_X+BAZAAR_VISIT_SEL_PRICE_W-size.cx,BAZAAR_VISIT_SEL_PRICE_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);

			// ���� ����
			wsprintf( buf1, "%d", ite->nCurrentCount);
			size = m_pFontItemCount->GetStringSize(buf1);
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
			if(m_byFocusText == TEXT_COUNT && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemCount,BAZAAR_VISIT_SEL_COUNT_X + BAZAAR_VISIT_SEL_COUNT_W - size.cx - 5,BAZAAR_VISIT_SEL_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			else
			    m_pFontItemCount->DrawText(BAZAAR_VISIT_SEL_COUNT_X+BAZAAR_VISIT_SEL_COUNT_W - size.cx,BAZAAR_VISIT_SEL_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
#else 
			if(m_byFocusText == TEXT_COUNT && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemCount,BAZAAR_VISIT_SEL_COUNT_X,BAZAAR_VISIT_SEL_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			else
			    m_pFontItemCount->DrawText(BAZAAR_VISIT_SEL_COUNT_X+(BAZAAR_VISIT_SEL_COUNT_W-size.cx)/2,BAZAAR_VISIT_SEL_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
#endif
			// �հ�
			wsprintf( buf1, "%d", m_nSum);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontSumPrice->GetStringSize(buf);
			m_pFontSumPrice->DrawText(BAZAAR_VISIT_TOTAL_PRICE_X+BAZAAR_VISIT_TOTAL_PRICE_W-size.cx,BAZAAR_VISIT_TOTAL_PRICE_Y,GUI_FONT_COLOR_W,buf,0L);

			//��ư �� �۾� ����.
			m_pOKBtn[m_nPutDelState[nLineCount]]->Move(BAZAAR_SHOP_RIGHT_BTN_X, BAZAAR_SHOP_RIGHT_BTN_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
			m_pOKBtn[m_nPutDelState[nLineCount]]->Render();
		}

		ite++;
		i++;
	}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	int j = i - m_nScrollLine;
	if(j < 0)
		j = 0;
	for(j; j < SHOP_ITEM_SLOT_NUMBER; j++)
	{
		m_pBackListBox->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y +  j * BAZAAR_SHOP_ITEM_H);
		m_pBackListBox->Render();
		m_pBackList->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y +  j * BAZAAR_SHOP_ITEM_H);
		m_pBackList->Render();
	}
#endif
}

void CINFCityBazaarVisit::Render_Buy()
{
	/*--------------------------------------------------------------------------*/
	//������ ��� �ִ� �� ����.	
	int i = 0;
	int nItemCount = m_vecVisitBazaarItem.size();
#ifndef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	if(nItemCount < m_nScrollLine)
		return;
#endif
	
	vector<VISIT_BAZAAR_ITEM>::iterator ite = m_vecVisitBazaarItem.begin();
	while(ite != m_vecVisitBazaarItem.end())
	{
		int nLineCount = i - m_nScrollLine;
		if(nLineCount >= 0)
		{
			if(nLineCount >= SHOP_ITEM_SLOT_NUMBER)
			{
				break;
			}
			// ����
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
			m_pBackListBox->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + ( nLineCount * BAZAAR_SHOP_ITEM_H ) );
			m_pBackListBox->Render();
			
			m_pBackItem->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
			m_pBackItem->Render();
			// ����
			if(m_nSelectIndex == i)
			{
				m_pSelectBar->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pSelectBar->Render();
			}
#else
			if(m_nSelectIndex == i)
			{
				m_pSelectBar->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pSelectBar->Render();
			}
			else
			{
				m_pBackItem->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
				m_pBackItem->Render();
			}
#endif

			// ������
			SIZE size;
			char buf[64] = {0,};
			char buf1[64] = {0,};


			// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

			//wsprintf(buf, "%08d", ite->pItemInfo->ItemInfo->SourceIndex);
			if( !ite->pItemInfo->ShapeItemNum )
				wsprintf(buf, "%08d", ite->pItemInfo->ItemInfo->SourceIndex);
			else
			{
				ITEM* pShapeItem = g_pDatabase->GetServerItemInfo( ite->pItemInfo->ShapeItemNum );
				if( pShapeItem )
					wsprintf(buf, "%08d", pShapeItem->SourceIndex);
				else
					wsprintf(buf, "%08d", ite->pItemInfo->ItemInfo->SourceIndex);
			}

			// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����


			g_pGameMain->m_pIcon->SetIcon(buf, BAZAAR_SHOP_ICON_X, BAZAAR_SHOP_ICON_Y + (nLineCount * BAZAAR_SHOP_ITEM_H), 1.0f);
			g_pGameMain->m_pIcon->Render();

			// ������ �Ǹ� ����
			if(ite->nAmount0 > 1)
			{
				wsprintf( buf1, "%d", ite->nAmount0);
				size = m_pFontBuySellItemCount->GetStringSize(buf1);
				m_pFontBuySellItemCount->DrawText(BAZAAR_VISIT_SEL_ITEM_COUNT_X-size.cx,BAZAAR_VISIT_SEL_ITEM_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			}

			// ������ �̸�
			wsprintf(buf1,"%s", ite->cItemName);
			m_pFontItemName->DrawText(BAZAAR_VISIT_NAME_X,BAZAAR_VISIT_NAME_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);

			// ����
			wsprintf( buf1, "%d", ite->nEachPrice0);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontItemPrice->GetStringSize(buf);  
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
		    m_pFontItemPrice->DrawText(BAZAAR_VISIT_BUY_PRICE_X + BAZAAR_OPEN_1_BUY_W - size.cx,BAZAAR_VISIT_SEL_PRICE_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);

			// ���� ����
			wsprintf( buf1, "%d", ite->nCurrentCount);
			size = m_pFontItemCount->GetStringSize(buf1);
			if(m_byFocusText == TEXT_COUNT && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemCount,BAZAAR_VISIT_BUY_COUNT_X+BAZAAR_VISIT_BUY_COUNT_W-size.cx - 5, BAZAAR_VISIT_BUY_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			else
			    m_pFontItemCount->DrawText(BAZAAR_VISIT_BUY_COUNT_X+BAZAAR_VISIT_BUY_COUNT_W-size.cx,BAZAAR_VISIT_BUY_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
#else			
			size = m_pFontItemPrice->GetStringSize(buf);
		    m_pFontItemPrice->DrawText(BAZAAR_VISIT_SEL_PRICE_X+BAZAAR_OPEN_1_BUY_W-size.cx,BAZAAR_VISIT_SEL_PRICE_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf,0L);

			// ���� ����
			wsprintf( buf1, "%d", ite->nCurrentCount);
			size = m_pFontItemCount->GetStringSize(buf1);
			if(m_byFocusText == TEXT_COUNT && m_nSelectIndex == i)
				UnderBarDrawText(m_pFontItemCount,BAZAAR_VISIT_BUY_COUNT_X,BAZAAR_VISIT_SEL_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
			else
			    m_pFontItemCount->DrawText(BAZAAR_VISIT_BUY_COUNT_X+(BAZAAR_VISIT_BUY_COUNT_W-size.cx)/2,BAZAAR_VISIT_SEL_COUNT_Y+(nLineCount * BAZAAR_SHOP_ITEM_H),GUI_FONT_COLOR_W,buf1,0L);
#endif

			// �հ�
			wsprintf( buf1, "%d", m_nSum);
			MakeCurrencySeparator(buf,buf1,3,',');
			size = m_pFontSumPrice->GetStringSize(buf);
			m_pFontSumPrice->DrawText(BAZAAR_VISIT_TOTAL_PRICE_X+BAZAAR_VISIT_TOTAL_PRICE_W-size.cx,BAZAAR_VISIT_TOTAL_PRICE_Y,GUI_FONT_COLOR_W,buf,0L);

			//��ư �� �۾� ����.
			if(ite->bExistence == FALSE)
			{
				m_nPutDelState[nLineCount] = BTN_STATE_DEACTIVE;
			}else
			{// 2008-06-10 by dgwoo ���λ������� �Ǹ� ��ư�� ��Ȱ��ȭ �Ǵ°��� ����.
				if(m_nPutDelState[nLineCount] == BTN_STATE_DEACTIVE)
					m_nPutDelState[nLineCount] = BTN_STATE_NORMAL;
			}
			
			m_pOKBtn[m_nPutDelState[nLineCount]]->Move(BAZAAR_SHOP_RIGHT_BTN_X, BAZAAR_SHOP_RIGHT_BTN_Y + (nLineCount * BAZAAR_SHOP_ITEM_H));
			m_pOKBtn[m_nPutDelState[nLineCount]]->Render();
		}

		ite++;
		i++;
	}
#ifdef C_EPSODE4_UI_CHANGE_JSKIM    // 2011. 10. 10 by jskim UI�ý��� ����
	int j = i - m_nScrollLine;
	if(j < 0)
		j = 0;
	for(j; j < SHOP_ITEM_SLOT_NUMBER; j++)
	{
		m_pBackListBox->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y +  j * BAZAAR_SHOP_ITEM_H);
		m_pBackListBox->Render();
		m_pBackList->Move(BAZAAR_SHOP_ITEM_X, BAZAAR_SHOP_ITEM_Y +  j * BAZAAR_SHOP_ITEM_H);
		m_pBackList->Render();
	}
#endif
}

void CINFCityBazaarVisit::Tick()
{

}


int CINFCityBazaarVisit::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nResultProc = INF_MSGPROC_NORMAL;

	
	/*--------------------------------------------------------------------------*/
	// ���� �޼���
	switch(uMsg)
	{
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			
			m_bScrollLock = FALSE;

			if(pt.x >= BAZAAR_VISIT_OUT_X &&
				pt.x <= BAZAAR_VISIT_OUT_X + BAZAAR_SHOP_BTN_OUT_W &&
				pt.y >= BAZAAR_VISIT_OUT_Y &&
				pt.y <= BAZAAR_VISIT_OUT_Y + BAZAAR_SHOP_BTN_H)
			{
				// ����
				CloseVisitShop();
				m_nOutBtnState = BTN_STATE_NORMAL;
			}
		}
		break;
	case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE)
			{
				// ����
				CloseVisitShop();
				m_nOutBtnState = BTN_STATE_NORMAL;
			}

		}
		break;
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
			//����̳� ��� ��ư ���� 
				//�������� ��ư�� ���¸� �������ش�.
			int i;
				for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
				{
					if(m_nPutDelState[i] != BTN_STATE_DEACTIVE)
					{
						if(GetPointInType(pt,BAZAAR_BTN,i))//BAZAAR_BTN
						{
							if(m_nPutDelState[i] != BTN_STATE_CLICK)
							{
								m_nPutDelState[i] = BTN_STATE_OVER;
							}
						}
						else
						{
							m_nPutDelState[i] = BTN_STATE_NORMAL;
						}
					}
				}

			if(GetPointInType(pt,BAZAAR_BTN_VISIT_OUT))
			{
				if(m_nOutBtnState != BTN_STATE_CLICK)
					m_nOutBtnState = BTN_STATE_OVER;
			}
			else
			{
				m_nOutBtnState = BTN_STATE_NORMAL;
			}
		
			// ��ũ��
			if(m_bScrollLock &&
				pt.x >= BAZAAR_SHOP_VISIT_SCROLL_X - 5 && 
				pt.x <= BAZAAR_SHOP_VISIT_SCROLL_X + BAZAAR_SHOP_SCROLL_W + 5)
			{
				int nScrollBtnY = pt.y - m_nScrollBtn;
				if(nScrollBtnY >= BAZAAR_SHOP_SCROLL_Y &&
					nScrollBtnY <= BAZAAR_SHOP_SCROLL_Y + BAZAAR_SHOP_SCROLL_LINE_LENGTH)
				{
					m_nScrollPosition = nScrollBtnY - BAZAAR_SHOP_SCROLL_Y;
					m_nScrollLine = GetScrollLineNumber(m_nScrollPosition);
				}
				else if(nScrollBtnY < BAZAAR_SHOP_SCROLL_Y)
				{
					InitScrollLine();
				}
				else if(nScrollBtnY > BAZAAR_SHOP_SCROLL_Y + BAZAAR_SHOP_SCROLL_LINE_LENGTH)
				{
					SetScrollEndLine();
				}
			}

			// ������ ����
			if(!g_pGameMain->m_stSelectItem.pSelectItem)
			{
				SetItemInfo(NULL, 0 ,0);
				
				if(GetPointInType(pt,BAZAAR_ICON))
				{
					int nItemIndex = GetItemIndexByPos(pt.y);
					if(nItemIndex != -1)
					{
						SetItemInfo((m_vecVisitBazaarItem[nItemIndex].pItemInfo), pt.x, pt.y);
					}
				}
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			int i = 0;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);			
			
			g_pD3dApp->m_bChatMode = FALSE;			


			if(GetPointInType(pt,BAZAAR_BTN_VISIT_OUT))
			{
				m_nOutBtnState = BTN_STATE_CLICK;
			}
		
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				//�������� ��ư�� ���¸� �������ش�.
				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
					GetPointInType(pt,BAZAAR_BTN,i))
				{
					m_nPutDelState[i] = BTN_STATE_CLICK;
				}

				// ����
				if(!g_pGameMain->m_stSelectItem.pSelectItem && 
					GetPointInType(pt,BAZAAR_SHOP_ITEM,i))
				{
					int nItemIndex = GetItemIndexByPos(pt.y);
					if(nItemIndex != -1)
					{
						m_nSelectIndex = nItemIndex;
						// 2006-08-02 by dgwoo �������� �������������� �հ� ���� ��ȭ �����ش�.
						m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
						break;
					}
					else
					{
						m_nSelectIndex = -1;
					}
				}
				else
				{
					m_nSelectIndex = -1;
				}
			}

			// ��ũ��
			if(GetPointInType(pt,BAZAAR_SHOP_SCROLL,m_nScrollPosition))
			{
				m_nScrollBtn = pt.y - (BAZAAR_SHOP_SCROLL_Y + m_nScrollPosition);
				m_bScrollLock = TRUE;
				return INF_MSGPROC_BREAK;
			}	
		}
		break;
	case WM_MOUSEWHEEL:
		{
			POINT pt;
			GetCursorPos(&pt);
			ScreenToClient(g_pD3dApp->GetHwnd(), &pt);
			CheckMouseReverse(&pt);

			if(GetPointInType(pt,BAZAAR_SHOP_ITEM_AREA))
			{
				if((int)wParam<0)
				{
					m_nScrollLine++;
					if(m_nScrollLine > BAZAAR_SHOP_SCROLL_MAX_LINE)
					{
						SetScrollEndLine();
					}
					else
					{
						m_nScrollPosition = GetScrollLineInterval(m_nScrollLine);
					}
				}
				else
				{
					m_nScrollLine--;
					if(m_nScrollLine < 0)
					{
						InitScrollLine();
					}
					else
					{
						m_nScrollPosition = GetScrollLineInterval(m_nScrollLine);
					}
				}

				return INF_MSGPROC_BREAK;
			}
			
		}
		break;
	}


	if(m_byBazaarType == 1)
	{
		nResultProc = WndProc_Sell(uMsg, wParam, lParam);
	}
	else if(m_byBazaarType == 2)
	{
		nResultProc = WndProc_Buy(uMsg, wParam, lParam);
	}
	
	return nResultProc;
}

int CINFCityBazaarVisit::WndProc_Sell(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int i;
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			m_bLButtonDown = FALSE;
			m_byFocusText = TEXT_NON;

			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				// ������ ��� Ȯ��
				if(m_nSelectIndex == m_nScrollLine + i)
				{
					//ī���ͺ� �������϶� ���� ��ȯ�Ѵ�.
					int kind = m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->ItemInfo->Kind;
					if(IS_COUNTABLE_ITEM(kind) &&
						GetPointInType(pt,BAZAAR_VISIT_SEL_COUNT,i))
					{
						m_byFocusText = TEXT_COUNT;
						g_pD3dApp->m_bChatMode = TRUE;
						break;
					}

					if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
						GetPointInType(pt,BAZAAR_BTN,i))
					{
						m_nPutDelState[i] = BTN_STATE_CLICK;
						break;
					}
				}
			}		
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			//�������� ��ư ó��
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
					GetPointInType(pt,BAZAAR_BTN,i))
				{
					m_nPutDelState[i] = BTN_STATE_NORMAL;
					int nCurrentItemIndex = GetItemIndexByPos(pt.y);
					// ������ �Ͱ� �ٸ��� ���
					if(nCurrentItemIndex == m_nSelectIndex)
					{
						// ������ ����
						Send_SellBuyItem();
						return INF_MSGPROC_BREAK;
					}
				}
			}		

		}
		break;
		// 2009-01-30 by bhsohn ���� ���� �Է� ��� ����
// 	case WM_CHAR:
// 		{
// 			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
// 			{
// 				char code = wParam;
// 				INT64 nCount;
// 				if(m_byFocusText == TEXT_COUNT)
// 				{
// 					if(code >= '0' && code <= '9' )
// 					{
// 						if(m_nSelectIndex != -1)
// 						{
// 							nCount = m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
// 							nCount *= 10;
// 							nCount += code - '0';
// 							if(nCount > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
// 								nCount = MAX_ITEM_COUNTS;							
// 							}
// 							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = nCount;
// 							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount, m_vecVisitBazaarItem[m_nSelectIndex].nAmount0);
// 							m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
// 						}
// 					}
// 					else if(code == VK_BACK)
// 					{
// 						m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount /= 10;
// 						m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
// 					}
// 				}
// 			}
// 		}
// 		break;
	case WM_KEYDOWN:
		{			
			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
			{
				DWORD dwCode = lParam;
				INT64 nCount;
				if(m_byFocusText == TEXT_COUNT)
				{
					int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
					if(nNumber != -1 )
					{
						if(m_nSelectIndex != -1)
						{
							nCount = m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
							nCount *= 10;
							nCount += nNumber;
							if(nCount > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
								nCount = MAX_ITEM_COUNTS;							
							}
							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = nCount;
							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount, m_vecVisitBazaarItem[m_nSelectIndex].nAmount0);
							m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
						}
					}
					else if(0x000e0001 == dwCode)
					{
						m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount /= 10;
						m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
					}
				}
			}
		}
		break;				
		// end 2009-01-30 by bhsohn ���� ���� ���� �Է� ��� ����
	}
	return INF_MSGPROC_NORMAL;
}


int CINFCityBazaarVisit::WndProc_Buy(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);
		}
		break;
	case WM_LBUTTONDOWN:
		{
			POINT pt;
			int i;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			m_bLButtonDown = FALSE;
			m_byFocusText = TEXT_NON;

			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				// ������ ��� Ȯ��
				if(m_nSelectIndex == m_nScrollLine + i)
				{
					if(GetPointInType(pt,BAZAAR_VISIT_BUY_COUNT,i))
					{
						m_byFocusText = TEXT_COUNT;
						g_pD3dApp->m_bChatMode = TRUE;
						break;
					}
				}

				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
					GetPointInType(pt,BAZAAR_BTN,i))
				{
					m_nPutDelState[i] = BTN_STATE_CLICK;
					break;
				}
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT pt;
			int i;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			CheckMouseReverse(&pt);

			//�������� ��ư ó��
			for(i = 0; i < SHOP_ITEM_SLOT_NUMBER; i++)
			{
				if(m_nPutDelState[i] != BTN_STATE_DEACTIVE &&
					GetPointInType(pt,BAZAAR_BTN,i))
				{
					m_nPutDelState[i] = BTN_STATE_NORMAL;
					int nCurrentItemIndex = GetItemIndexByPos(pt.y);
					// ������ �Ͱ� �ٸ��� ���
					if(nCurrentItemIndex == m_nSelectIndex)
					{
						// ������ ����
						Send_SellBuyItem();
						return INF_MSGPROC_BREAK;
					}
				}
			}		
		}
		break;
		// 2009-01-30 by bhsohn ���� ���� �Է� ��� ����
//	case WM_CHAR:
// 		{
// 			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
// 			{
// 				char code = wParam;
// 				INT64 nCount;
// 				if(m_byFocusText == TEXT_COUNT)
// 				{
// 					if(code >= '0' && code <= '9' )
// 					{
// 						if(m_nSelectIndex != -1)
// 						{
// 							nCount = m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
// 							nCount *= 10;
// 							nCount += code - '0';
// 							if(nCount > MAX_ITEM_COUNTS)
// 							{
// 								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
// 								nCount = MAX_ITEM_COUNTS;
// 							}
// 							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = nCount;
// 							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount, m_vecVisitBazaarItem[m_nSelectIndex].nAmount0);
// 							CItemInfo* pItemInfo = NULL;
// 							pItemInfo = g_pStoreData->FindItemInInventoryByItemNum(m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->ItemNum);
// 							// 2007-06-19 by bhsohn ���Ի������� ī���ͺ� �������� �ƴ� ��ǰ �Ȼ����� ���� ó��
// //							if(pItemInfo != NULL)
// //								m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount,pItemInfo->CurrentCount);
// 							int nMaxCount = 1;
// 							if(pItemInfo != NULL)
// 							{
// 								if( IS_COUNTABLE_ITEM(pItemInfo->Kind))
// 								{
// 									nMaxCount = pItemInfo->CurrentCount;
// 								}								
// 							}
// 							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount, nMaxCount);
// 							// end 2007-06-19 by bhsohn ���Ի������� ī���ͺ� �������� �ƴ� ��ǰ �Ȼ����� ���� ó��
// 							m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
// 						}
// 					}
// 					else if(code == VK_BACK)
// 					{
// 						m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount /= 10;
// 						m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
// 					}
// 				}
// 			}
// 		}
//		break;
case WM_KEYDOWN:
		{
			if(g_pInterface->m_pGameMain->m_pChat->m_bChatMode == FALSE)
			{
				DWORD dwCode = lParam;

				INT64 nCount;
				if(m_byFocusText == TEXT_COUNT)
				{
					int nNumber = g_pGameMain->GetKeyDownToNumber(dwCode);
					if(nNumber != -1 )					
					{
						if(m_nSelectIndex != -1)
						{
							nCount = m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
							nCount *= 10;
							nCount += nNumber;
							if(nCount > MAX_ITEM_COUNTS)
							{
								g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060802_0005, _MESSAGE);		// "������ �ִ���ȿ������ �ʰ��Ͽ����ϴ�.(�ִ���ȿ���� 20��)"
								nCount = MAX_ITEM_COUNTS;
							}
							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = nCount;
							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount, m_vecVisitBazaarItem[m_nSelectIndex].nAmount0);
							CItemInfo* pItemInfo = NULL;
							pItemInfo = g_pStoreData->FindItemInInventoryByItemNum(m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->ItemNum);
							// 2007-06-19 by bhsohn ���Ի������� ī���ͺ� �������� �ƴ� ��ǰ �Ȼ����� ���� ó��
//							if(pItemInfo != NULL)
//								m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount,pItemInfo->CurrentCount);
							int nMaxCount = 1;
							if(pItemInfo != NULL)
							{
								if( IS_COUNTABLE_ITEM(pItemInfo->Kind))
								{
									nMaxCount = pItemInfo->CurrentCount;
								}								
							}
							m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = min(m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount, nMaxCount);
							// end 2007-06-19 by bhsohn ���Ի������� ī���ͺ� �������� �ƴ� ��ǰ �Ȼ����� ���� ó��
							m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
						}
					}
					else if(0x000e0001 == dwCode)
					{
						m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount /= 10;
						m_nSum = m_vecVisitBazaarItem[m_nSelectIndex].nEachPrice0 * m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
					}
				}
			}
		}
		break;
		// end 2009-01-30 by bhsohn ���� ���� ���� �Է� ��� ����
	}

	return INF_MSGPROC_NORMAL;
}


///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::Recv_SetSellItem(SBAZAAR_SELL_ITEM *pSellItem)
/// \brief		�Ǹ� ������ ���
/// \author		ispark
/// \date		2006-07-29 ~ 2006-07-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::Recv_SetSellItem(SBAZAAR_SELL_ITEM *pSellItem)
{
	VISIT_BAZAAR_ITEM VisitItem;

	VisitItem.nAmount0			= pSellItem->nSellAmount0;
	VisitItem.nEachPrice0		= pSellItem->nSellEachPrice0;
	// �Ѱ��� ���� 1�� �ڵ� ����
	if(pSellItem->nSellAmount0 <= 1)
	{
		VisitItem.nCurrentCount = 1;
	}

	ITEM_GENERAL* pItemBase		= new ITEM_GENERAL;
	pItemBase->ItemNum			= pSellItem->nSellItemNum0;
	pItemBase->UniqueNumber		= pSellItem->itemUID;
	pItemBase->CurrentCount		= pSellItem->nSellAmount0;


	// 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

	//pItemBase->ColorCode		= pSellItem->ColorCode0;
	pItemBase->ShapeItemNum		= pSellItem->ShapeItemNum0;
	pItemBase->ColorCode		= pSellItem->EffectItemNum0;

	// end 2009. 08. 27 by ckPark �׷��� ���ҽ� ���� �ý��� ����

	
	// 2007-07-09 by bhsohn ��þ ���� ���� ����
	pItemBase->PrefixCodeNum	= pSellItem->PrefixCodeNum0;
	pItemBase->SuffixCodeNum	= pSellItem->SuffixCodeNum0;
	// end 2007-07-09 by bhsohn ��þ ���� ���� ����

	pItemBase->FixedTermShape = pSellItem->FixedTermShape; // 2012-10-13 by jhahn �Ⱓ�� ������ �߰�

	VisitItem.pItemInfo = new CItemInfo(pItemBase);
	VisitItem.pItemInfo->ChangeRareInfo(pSellItem->PrefixCodeNum0, pSellItem->SuffixCodeNum0);

	// 2010. 02. 11 by ckPark �ߵ��� ����������
	// ���λ��� ��ǰ�� ��Ÿ�� ���� �߰�
	VisitItem.pItemInfo->SetCoolElapsedTime( pSellItem->CoolingTime * 1000 );
	// end 2010. 02. 11 by ckPark �ߵ��� ����������

	SetItemFullName(&VisitItem);
	m_vecVisitBazaarItem.push_back(VisitItem);

}
///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::Recv_SetBuyItem(SBAZAAR_BUY_ITEM *pBuyItem)
/// \brief		�Ǹ� ������ ���
/// \author		ispark
/// \date		2006-07-29 ~ 2006-07-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::Recv_SetBuyItem(SBAZAAR_BUY_ITEM *pBuyItem)
{
	VISIT_BAZAAR_ITEM VisitItem;

	VisitItem.nAmount0			= pBuyItem->nBuyAmount0;
	VisitItem.nEachPrice0		= pBuyItem->nBuyEachPrice0;
	VisitItem.nItemIndex		= pBuyItem->nBuyItemIndex0;

	CItemInfo * pItemInfo = g_pStoreData->FindItemInInventoryByItemNum(pBuyItem->nBuyItemNum0);
	if(pItemInfo)
	{
		VisitItem.bExistence	= TRUE;
	}

	ITEM_GENERAL* pItemBase		= new ITEM_GENERAL;
	pItemBase->ItemNum			= pBuyItem->nBuyItemNum0;
	pItemBase->UniqueNumber		= 0;

	VisitItem.pItemInfo = new CItemInfo(pItemBase);

	SetItemFullName(&VisitItem);
	m_vecVisitBazaarItem.push_back(VisitItem);

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::Recv_SetSellEnchantItem(UID64_t itemUID, int EnchantItemNum)
/// \brief		�Ǹ� ������ ���
/// \author		ispark
/// \date		2006-07-29 ~ 2006-07-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::Recv_SetSellEnchantItem(UID64_t itemUID, int EnchantItemNum)
{
	VISIT_BAZAAR_ITEM VisitItem;

	vector<VISIT_BAZAAR_ITEM>::iterator it = m_vecVisitBazaarItem.begin();
	while(it != m_vecVisitBazaarItem.end())
	{
		if( it->pItemInfo->UniqueNumber == itemUID)
		{
			it->pItemInfo->AddEnchantItem( EnchantItemNum );
			SetItemFullName(&*it);
			break;
		}
		it++;
	}
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			int CINFCityBazaarVisit::GetItemIndexByPos(int nPosY)
/// \brief		��ġ������ ������ �ε��� ��������
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
int CINFCityBazaarVisit::GetItemIndexByPos(int nPosY)
{
	int nItemCount = m_vecVisitBazaarItem.size();
	if(nItemCount >= m_nScrollLine)
	{
		int nPtLine = (nPosY - BAZAAR_SHOP_ITEM_Y) / BAZAAR_SHOP_ITEM_H;

		if(nPtLine + m_nScrollLine < nItemCount)
		{
			return nPtLine + m_nScrollLine;
		}
	}

	return -1;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::CheckItemCount()
/// \brief		üũ ������ ī��Ʈ
/// \author		ispark
/// \date		2006-07-29 ~ 2006-07-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::CheckItemCount()
{
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::Send_SellBuyItem(BOOL bRequest)
/// \brief		������ ���� �� �Ǹ� ��û
/// \author		ispark
/// \date		2006-07-29 ~ 2006-07-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::Send_SellBuyItem(BOOL bRequest)
{
	const CItemInfo* a_pItemInfo = NULL;

	if( 0 >= m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount)
	{
		g_pGameMain->m_pInfWindow->AddMsgBox(STRMSG_C_060801_0104, _MESSAGE);		// "������ �Է����ּ���.
		return;
	}

	// 2006-08-03 by ispark, ���Ż��� �湮���̸� �κ��丮 Ȯ��
	if(m_byBazaarType == 2 && bRequest == FALSE)
	{
		//pItemInfo = g_pStoreData->FindItemInInventoryByItemNum(m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->ItemNum);
		a_pItemInfo = g_pStoreData->FindItemInInventoryByItemInfo ( m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo );
		if(a_pItemInfo == NULL)
		{
			g_pGameMain->m_pInfWindow->AddMsgBox(STRERR_ERROR_0025, _MESSAGE);		// "�ش� �������� �����ϴ�."
			return;
		}
	}

	if(m_nSelectIndex != -1 && bRequest == TRUE)
	{
		if(m_byBazaarType == 1)
		{
			// ������ ��û
			MSG_FC_BAZAAR_SELL_BUY_ITEM sMsg;
			sMsg.clientIndex0 = m_ClientIndex;
			sMsg.itemUID = m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->UniqueNumber;
			sMsg.nAmount0 = m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;

			g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_SELL_BUY_ITEM, (char*)&sMsg, sizeof(sMsg));
			g_pD3dApp->m_bRequestEnable = FALSE;			// ���� �޼��� ��ٸ���
		}
		else if(m_byBazaarType == 2)
		{
			// ������ ��û
			//pItemInfo = g_pStoreData->FindItemInInventoryByItemNum(m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->ItemNum);
			a_pItemInfo = g_pStoreData->FindItemInInventoryByItemInfo ( m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo );
			if(a_pItemInfo)
			{
				MSG_FC_BAZAAR_BUY_SELL_ITEM sMsg;
				sMsg.clientIndex0 = m_ClientIndex;
				sMsg.nBuyItemIndex0 = m_vecVisitBazaarItem[m_nSelectIndex].nItemIndex;
				sMsg.itemUID = a_pItemInfo->UniqueNumber;
				sMsg.nAmount0 = m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount;
				g_pFieldWinSocket->SendMsg(T_FC_BAZAAR_BUY_SELL_ITEM, (char*)&sMsg, sizeof(sMsg));
				g_pD3dApp->m_bRequestEnable = FALSE;			// ���� �޼��� ��ٸ���
			}
		}
	}
	else if(m_nSelectIndex != -1 && bRequest == FALSE)
	{
		char msgSellBuy[256];
		if(m_byBazaarType == 1)
		{
			wsprintf(msgSellBuy, STRMSG_C_SHOP_0006, m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->ItemInfo->ItemName);
			g_pGameMain->m_pInfWindow->AddMsgBox(msgSellBuy, _Q_BAZAAR_SELL_OK);	// "%s �������� ���� �Ͻðڽ��ϱ�?"
		}
		else if(m_byBazaarType == 2)
		{
			wsprintf(msgSellBuy, STRMSG_C_060802_0004, m_vecVisitBazaarItem[m_nSelectIndex].pItemInfo->ItemInfo->ItemName);
			g_pGameMain->m_pInfWindow->AddMsgBox(msgSellBuy, _Q_BAZAAR_BUY_OK);	// "%s �������� �Ǹ� �Ͻðڽ��ϱ�?"
		}
	}

}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::CloseVisitShop()
/// \brief		���� ����
/// \author		ispark
/// \date		2006-07-29 ~ 2006-07-29
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::CloseVisitShop()
{
	// 2009-04-15 by bhsohn ���ӻ��� �湮�� ���ߴ� ���� ó��
	if(g_pD3dApp && g_pD3dApp->m_bChatMode)
	{
		g_pD3dApp->EnableChatMode(FALSE, TRUE);
	}
	// end 2009-04-15 by bhsohn ���ӻ��� �湮�� ���ߴ� ���� ó��
	m_bBazaarShopEnd = TRUE;
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarVisit::SetItemFullName(VISIT_BAZAAR_ITEM* pVisitItem)
/// \brief		������ Ǯ���� ����
/// \author		ispark
/// \date		2006-07-30 ~ 2006-07-30
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::SetItemFullName(VISIT_BAZAAR_ITEM* pVisitItem)
{
	char strItemInfo[ITEMINFO_ITEM_FULL_NAME];
	memset( strItemInfo, 0x00, ITEMINFO_ITEM_FULL_NAME);

	RARE_ITEM_INFO* pRefPrefixRareInfo = pVisitItem->pItemInfo->GetPrefixRareInfo();
	RARE_ITEM_INFO* pRefSuffixRareInfo = pVisitItem->pItemInfo->GetSuffixRareInfo();

	if(pRefPrefixRareInfo)
	{
		wsprintf( strItemInfo, "\\g%s\\g", pRefPrefixRareInfo->Name );
	}

	if(pRefPrefixRareInfo || pRefSuffixRareInfo)
	{
		if(pVisitItem->pItemInfo->GetEnchantParamFactor())
		{
			wsprintf( strItemInfo,"%s \\e%s\\e", strItemInfo, pVisitItem->pItemInfo->ItemInfo->ItemName);
		}
		else
		{
			wsprintf( strItemInfo,"%s \\g%s\\g", strItemInfo, pVisitItem->pItemInfo->ItemInfo->ItemName);
		}
	}
	else
	{
		if(pVisitItem->pItemInfo->GetEnchantParamFactor())
		{
			wsprintf( strItemInfo,"%s \\e%s\\e", strItemInfo, pVisitItem->pItemInfo->ItemInfo->ItemName);				
		}
		else
		{
			wsprintf( strItemInfo,"%s %s", strItemInfo, pVisitItem->pItemInfo->ItemInfo->ItemName);				
		}
	}

	if(pRefSuffixRareInfo)
	{
		wsprintf( strItemInfo, "%s \\g%s\\g", strItemInfo, pRefSuffixRareInfo->Name );
	}

	memcpy(pVisitItem->cItemName, strItemInfo, ITEMINFO_ITEM_FULL_NAME);
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::SellBuyItemOK(MSG_FC_BAZAAR_SELL_BUY_ITEM_OK* pMsg)
/// \brief		��� �ȱ� ���� �Ϸ�
/// \author		ispark
/// \date		2006-07-31 ~ 2006-07-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::Recv_SellBuyItemOK(MSG_FC_BAZAAR_SELL_BUY_ITEM_OK* pMsg)
{
	// Ȯ�ο�

	vector<VISIT_BAZAAR_ITEM>::iterator it = FindItemItr(pMsg->itemUID);
	VISIT_BAZAAR_ITEM * pBazaarVisitItem = &*it;
	if(pBazaarVisitItem)
	{
		pBazaarVisitItem->nAmount0 -= pMsg->nAmount0;
		if(pBazaarVisitItem->nAmount0 <= 0)
		{
			util::del(pBazaarVisitItem->pItemInfo);
			//m_vecVisitBazaarItem.erase(pBazaarVisitItem);
			m_vecVisitBazaarItem.erase(it);

			// 2010. 02. 11 by ckPark �ߵ��� ����������
			SetItemInfo( NULL, 0, 0 );
			// end 2010. 02. 11 by ckPark �ߵ��� ����������

			if(m_vecVisitBazaarItem.size() <= 0)
			{
				// ����
				CMapEnemyIterator itEnemy = g_pScene->m_mapEnemyList.find(pMsg->clientIndex0);
				if(itEnemy != g_pScene->m_mapEnemyList.end())
				{
					itEnemy->second->DeleteChatMoveShop();
				}
				g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_060801_0000, COLOR_ERROR);
				CloseVisitShop();
			}
		}
		// 2006-08-02 by dgwoo �ȷ��� �÷� ���� �����ۺ��� ����� ������ ������ ������ �������ش�.
		if(pBazaarVisitItem->nAmount0 < m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount)
			m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = pBazaarVisitItem->nAmount0;
	}

	g_pD3dApp->m_bRequestEnable = TRUE;			// ���� �޼��� ��ٸ���
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			void CINFCityBazaarOpen::Recv_BuySellItemOK(MSG_FC_BAZAAR_BUY_SELL_ITEM_OK* pMsg)
/// \brief		��� �ȱ� ���� �Ϸ�
/// \author		ispark
/// \date		2006-07-31 ~ 2006-07-31
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
void CINFCityBazaarVisit::Recv_BuySellItemOK(MSG_FC_BAZAAR_BUY_SELL_ITEM_OK* pMsg)
{
	// Ȯ�ο�
	vector<VISIT_BAZAAR_ITEM>::iterator it = FindItemItr(pMsg->nBuyItemIndex0);
	VISIT_BAZAAR_ITEM * pBazaarVisitItem = &*it;
	if(pBazaarVisitItem)
	{
		pBazaarVisitItem->nAmount0 -= pMsg-> nAmount0;
		pBazaarVisitItem->pItemInfo->CurrentCount = pBazaarVisitItem->nAmount0;
		if(pBazaarVisitItem->nAmount0 <= 0)
		{
			util::del(pBazaarVisitItem->pItemInfo);
			//m_vecVisitBazaarItem.erase(pBazaarVisitItem);
			m_vecVisitBazaarItem.erase(it);

			// 2010. 02. 11 by ckPark �ߵ��� ����������
			SetItemInfo( NULL, 0, 0 );
			// end 2010. 02. 11 by ckPark �ߵ��� ����������

			if(m_vecVisitBazaarItem.size() <= 0)
			{
				// ����
				CMapEnemyIterator itEnemy = g_pScene->m_mapEnemyList.find(pMsg->clientIndex0);
				if(itEnemy != g_pScene->m_mapEnemyList.end())
				{
					itEnemy->second->DeleteChatMoveShop();
				}
				g_pD3dApp->m_pChat->CreateChatChild(STRMSG_C_060801_0000, COLOR_ERROR);
				CloseVisitShop();
			}
		}
		// 2006-08-02 by dgwoo
		m_vecVisitBazaarItem[m_nSelectIndex].nCurrentCount = 0;
	}

	g_pD3dApp->m_bRequestEnable = TRUE;			// ���� �޼��� ��ٸ���
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(UID64_t itemUID)
/// \brief		������ UID�� ������ ã��
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
VISIT_BAZAAR_ITEM * CINFCityBazaarVisit::FindItem(UID64_t itemUID)
{
	return &*FindItemItr(itemUID);
}

vector<VISIT_BAZAAR_ITEM>::iterator CINFCityBazaarVisit::FindItemItr(UID64_t itemUID)
{
	vector<VISIT_BAZAAR_ITEM>::iterator it = m_vecVisitBazaarItem.begin();
	while (it != m_vecVisitBazaarItem.end())
	{
		if (it->pItemInfo->UniqueNumber == itemUID)
		{
			return it;
		}

		it++;
	}

	return m_vecVisitBazaarItem.end();
}

///////////////////////////////////////////////////////////////////////////////
/// \fn			OPEN_BAZAAR_ITEM * CINFCityBazaarOpen::FindItem(int nItemIndex)
/// \brief		������ ������ �ε����� ������ ã��
/// \author		ispark
/// \date		2006-07-28 ~ 2006-07-28
/// \warning	
///
/// \param		
/// \return		
///////////////////////////////////////////////////////////////////////////////
VISIT_BAZAAR_ITEM * CINFCityBazaarVisit::FindItem(int nItemIndex)
{
	return &*FindItemItr(nItemIndex);
}

vector<VISIT_BAZAAR_ITEM>::iterator CINFCityBazaarVisit::FindItemItr(int nItemIndex)
{
	vector<VISIT_BAZAAR_ITEM>::iterator it = m_vecVisitBazaarItem.begin();
	while (it != m_vecVisitBazaarItem.end())
	{
		if (it->nItemIndex == nItemIndex)
		{
			return it;
		}

		it++;
	}

	return m_vecVisitBazaarItem.end();
}