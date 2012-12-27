#pragma once


class CTemplateViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

// CTemplateView

class CTemplateView : public CDockablePane
{
	DECLARE_DYNAMIC(CTemplateView)

public:
	CTemplateView();
	virtual ~CTemplateView();

protected:
	DECLARE_MESSAGE_MAP()
};


