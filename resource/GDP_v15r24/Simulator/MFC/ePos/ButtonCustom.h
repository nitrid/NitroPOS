#pragma once


// CButtonCustom

class CButtonCustom : public CButton
{
	DECLARE_DYNAMIC(CButtonCustom)

public:
	CButtonCustom();
	virtual ~CButtonCustom();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnPaint();
};


