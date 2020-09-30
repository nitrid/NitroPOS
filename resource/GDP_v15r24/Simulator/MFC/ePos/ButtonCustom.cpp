// ButtonCustom.cpp : implementation file
//

#include "stdafx.h"
#include "ePos.h"
#include "ButtonCustom.h"


// CButtonCustom

IMPLEMENT_DYNAMIC(CButtonCustom, CButton)

CButtonCustom::CButtonCustom()
{

}

CButtonCustom::~CButtonCustom()
{
}


BEGIN_MESSAGE_MAP(CButtonCustom, CButton)
	ON_WM_DRAWITEM()
	//	ON_WM_PAINT()
END_MESSAGE_MAP()



// CButtonCustom message handlers




void CButtonCustom::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{

}


void CButtonCustom::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CButtonCustom::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// Do not call CButton::OnPaint() for painting messages
}
