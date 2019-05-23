#include "stdafx.h"
#include "CLyricDraw.h"
#include "MusicPlayer2.h"


CLyricDraw::CLyricDraw(UIColors& colors)
    : m_colors(colors)
{
}


CLyricDraw::~CLyricDraw()
{
}

void CLyricDraw::DrawLryicCommon(CRect rect)
{
    SetDrawArea(rect);

    if (!IsDrawMultiLine(rect.Height()))
        DrawLyricTextSingleLine(rect);
    else
        DrawLyricTextMultiLine(rect);
}

int CLyricDraw::GetLyricTextHeight()
{
    return m_lyric_text_height;
}

void CLyricDraw::Create(CDC * pDC, CWnd * pMainWnd)
{
    CDrawCommon::Create(pDC, pMainWnd);

    //�����ı��߶�
    m_pDC->SelectObject(&theApp.m_font_set.lyric.GetFont(theApp.m_ui_data.full_screen));
    m_lyric_text_height = m_pDC->GetTextExtent(L"��").cy;	//���ݵ�ǰ���������ü����ı��ĸ߶�
}

bool CLyricDraw::IsDrawMultiLine(int height) const
{
    return height >= static_cast<int>(m_lyric_text_height * 3.5);
}

void CLyricDraw::DrawLyricTextMultiLine(CRect lyric_area)
{
    int line_space = theApp.m_app_setting_data.lyric_line_space;
    if (theApp.m_ui_data.full_screen)
        line_space = static_cast<int>(line_space * CONSTVAL::FULL_SCREEN_ZOOM_FACTOR);

    int lyric_height = m_lyric_text_height + line_space;			//�ı��߶ȼ����м��
    int lyric_height2 = lyric_height * 2 + line_space;		//��������ĸ�ʸ߶�

    SetFont(&theApp.m_font_set.lyric.GetFont(theApp.m_ui_data.full_screen));
    if (CPlayerUIHelper::IsMidiLyric())
    {
        wstring current_lyric{ CPlayer::GetInstance().GetMidiLyric() };
        DrawWindowText(lyric_area, current_lyric.c_str(), m_colors.color_text, Alignment::CENTER, false, true);
    }
    else if (CPlayer::GetInstance().m_Lyrics.IsEmpty())
    {
        DrawWindowText(lyric_area, CCommon::LoadText(IDS_NO_LYRIC_INFO), m_colors.color_text_2, Alignment::CENTER);
    }
    else
    {
        //CRect arect{ lyric_area };		//һ�и�ʵľ�������
        //arect.bottom = arect.top + lyric_height;
        //vector<CRect> rects(CPlayer::GetInstance().m_Lyrics.GetLyricCount() + 1, arect);
        //Ϊÿһ���ʴ���һ�����Σ�������������
        vector<CRect> rects;
        int lyric_count = CPlayer::GetInstance().m_Lyrics.GetLyricCount() + 1;		//��ȡ������������ڵ�һ�и����Ҫ��ʾ���⣬��������Ҫ+1��
        for (int i{}; i < lyric_count; i++)
        {
            CRect arect{ lyric_area };
            if (!CPlayer::GetInstance().m_Lyrics.GetLyric(i).translate.empty() && theApp.m_ui_data.show_translate)
                arect.bottom = arect.top + lyric_height2;
            else
                arect.bottom = arect.top + lyric_height;
            rects.push_back(arect);
        }
        int center_pos = (lyric_area.top + lyric_area.bottom) / 2;		//������������y����
        Time time{ CPlayer::GetInstance().GetCurrentPosition() };		//��ǰ����ʱ��
        int lyric_index = CPlayer::GetInstance().m_Lyrics.GetLyricIndex(time) + 1;		//��ǰ��ʵ���ţ���ʵĵ�һ��GetLyricIndex���ص���0��������ʾʱ��һ����Ҫ��ʾ���⣬��������Ҫ+1��
        int progress = CPlayer::GetInstance().m_Lyrics.GetLyricProgress(time);		//��ǰ��ʽ��ȣ���ΧΪ0~1000��
        int y_progress;			//��ǰ�����y���ϵĽ���
        if (!CPlayer::GetInstance().m_Lyrics.GetLyric(lyric_index).translate.empty() && theApp.m_ui_data.show_translate)
            y_progress = progress * lyric_height2 / 1000;
        else
            y_progress = progress * lyric_height / 1000;
        //int start_pos = center_pos - y_progress - (lyric_index + 1)*lyric_height;		//��1���ʵ���ʼy����
        //�����1���ʵ���ʼy����
        //���ڵ�ǰ�����Ҫ��ʾ�ڸ�����������λ�ã���˴�����λ�ÿ�ʼ����ȥ��ǰ�����Y���ϵĽ���
        //�����μ�ȥ֮ǰÿһ���ʵĸ߶ȣ����õ��˵�һ���ʵ���ʼλ��
        int start_pos;
        start_pos = center_pos - y_progress;
        for (int i{ lyric_index - 1 }; i >= 0; i--)
        {
            if (!CPlayer::GetInstance().m_Lyrics.GetLyric(i).translate.empty() && theApp.m_ui_data.show_translate)
                start_pos -= lyric_height2;
            else
                start_pos -= lyric_height;
        }

        //���λ���ÿһ����
        for (size_t i{}; i < rects.size(); i++)
        {
            //����ÿһ���ʵ�λ��
            if (i == 0)
                rects[i].MoveToY(start_pos);
            else
                rects[i].MoveToY(rects[i - 1].bottom);
            //���Ƹ���ı�
            if (!(rects[i] & lyric_area).IsRectEmpty())		//ֻ�е�һ���ʵľ�������͸������ľ����н���ʱ���Ż��Ƹ��
            {
                //���ø���ı��ͷ����ı��ľ�������
                CRect rect_text{ rects[i] };
                CRect rect_translate;
                if (!CPlayer::GetInstance().m_Lyrics.GetLyric(i).translate.empty() && theApp.m_ui_data.show_translate)
                {
                    rect_text.MoveToY(rect_text.top + line_space);
                    rect_text.bottom = rect_text.top + m_lyric_text_height;
                    rect_translate = rect_text;
                    rect_translate.MoveToY(rect_text.bottom + line_space);
                }

                if (i == lyric_index && progress < 1000)		//�������ڲ��ŵĸ��
                {
                    //���Ƹ���ı�
                    SetFont(&theApp.m_font_set.lyric.GetFont(theApp.m_ui_data.full_screen));
                    if (theApp.m_lyric_setting_data.lyric_karaoke_disp)
                        DrawWindowText(rect_text, CPlayer::GetInstance().m_Lyrics.GetLyric(i).text.c_str(), m_colors.color_text, m_colors.color_text_2, progress, true, true);
                    else
                        DrawWindowText(rect_text, CPlayer::GetInstance().m_Lyrics.GetLyric(i).text.c_str(), m_colors.color_text, m_colors.color_text, progress, true, true);
                    //���Ʒ����ı�
                    if (!CPlayer::GetInstance().m_Lyrics.GetLyric(i).translate.empty() && theApp.m_ui_data.show_translate)
                    {
                        SetFont(&theApp.m_font_set.lyric_translate.GetFont(theApp.m_ui_data.full_screen));
                        DrawWindowText(rect_translate, CPlayer::GetInstance().m_Lyrics.GetLyric(i).translate.c_str(), m_colors.color_text, m_colors.color_text, progress, true, true);
                    }
                }
                else		//���Ʒ����ڲ��ŵĸ��
                {
                    //���Ƹ���ı�
                    SetFont(&theApp.m_font_set.lyric.GetFont(theApp.m_ui_data.full_screen));
                    DrawWindowText(rect_text, CPlayer::GetInstance().m_Lyrics.GetLyric(i).text.c_str(), m_colors.color_text_2, Alignment::CENTER, true);
                    //���Ʒ����ı�
                    if (!CPlayer::GetInstance().m_Lyrics.GetLyric(i).translate.empty() && theApp.m_ui_data.show_translate)
                    {
                        SetFont(&theApp.m_font_set.lyric_translate.GetFont(theApp.m_ui_data.full_screen));
                        DrawWindowText(rect_translate, CPlayer::GetInstance().m_Lyrics.GetLyric(i).translate.c_str(), m_colors.color_text_2, Alignment::CENTER, true);
                    }
                }
            }
        }
    }
}

void CLyricDraw::DrawLyricTextSingleLine(CRect rect)
{
    SetFont(&theApp.m_font_set.lyric.GetFont(theApp.m_ui_data.full_screen));

    if (CPlayerUIHelper::IsMidiLyric())
    {
        wstring current_lyric{ CPlayer::GetInstance().GetMidiLyric() };
        DrawWindowText(rect, current_lyric.c_str(), m_colors.color_text, Alignment::CENTER, false, true);
    }
    else if (CPlayer::GetInstance().m_Lyrics.IsEmpty())
    {
        DrawWindowText(rect, CCommon::LoadText(IDS_NO_LYRIC_INFO), m_colors.color_text_2, Alignment::CENTER);
    }
    else
    {
        CRect lyric_rect = rect;
        CLyrics::Lyric current_lyric{ CPlayer::GetInstance().m_Lyrics.GetLyric(Time(CPlayer::GetInstance().GetCurrentPosition()), 0) };	//��ȡ�����
        if (current_lyric.text.empty())		//�����ǰ���Ϊ�հף�����ʾΪʡ�Ժ�
            current_lyric.text = CCommon::LoadText(IDS_DEFAULT_LYRIC_TEXT);
        int progress{ CPlayer::GetInstance().m_Lyrics.GetLyricProgress(Time(CPlayer::GetInstance().GetCurrentPosition())) };		//��ȡ��ǰ��ʽ��ȣ���ΧΪ0~1000��

        if ((!CPlayer::GetInstance().m_Lyrics.IsTranslated() || !theApp.m_ui_data.show_translate) && rect.Height() > static_cast<int>(m_lyric_text_height * 1.73))
        {
            wstring next_lyric_text = CPlayer::GetInstance().m_Lyrics.GetLyric(Time(CPlayer::GetInstance().GetCurrentPosition()), 1).text;
            if (next_lyric_text.empty())
                next_lyric_text = CCommon::LoadText(IDS_DEFAULT_LYRIC_TEXT);
            DrawLyricDoubleLine(lyric_rect, current_lyric.text.c_str(), next_lyric_text.c_str(), progress);
        }
        else
        {
            if (theApp.m_ui_data.show_translate && !current_lyric.translate.empty() && rect.Height() > static_cast<int>(m_lyric_text_height * 1.73))
            {
                lyric_rect.bottom = lyric_rect.top + rect.Height() / 2;
                CRect translate_rect = lyric_rect;
                translate_rect.MoveToY(lyric_rect.bottom);

                SetFont(&theApp.m_font_set.lyric_translate.GetFont(theApp.m_ui_data.full_screen));
                DrawWindowText(translate_rect, current_lyric.translate.c_str(), m_colors.color_text, m_colors.color_text, progress, true, true);
            }

            SetFont(&theApp.m_font_set.lyric.GetFont(theApp.m_ui_data.full_screen));
            if (theApp.m_lyric_setting_data.lyric_karaoke_disp)
                DrawWindowText(lyric_rect, current_lyric.text.c_str(), m_colors.color_text, m_colors.color_text_2, progress, true, true);
            else
                DrawWindowText(lyric_rect, current_lyric.text.c_str(), m_colors.color_text, m_colors.color_text, progress, true, true);
        }

        SetFont(m_pMainWnd->GetFont());
    }
}

void CLyricDraw::DrawLyricDoubleLine(CRect rect, LPCTSTR lyric, LPCTSTR next_lyric, int progress)
{
    SetFont(&theApp.m_font_set.lyric.GetFont(theApp.m_ui_data.full_screen));
    static bool swap;
    static int last_progress;
    if (last_progress > progress)		//�����ǰ�ĸ�ʽ��ȱ��ϴε�С��˵������л�������һ��
    {
        swap = !swap;
    }
    last_progress = progress;


    CRect up_rect{ rect }, down_rect{ rect };		//�ϰ벿�ֺ��°벿�ָ�ʵľ�������
    up_rect.bottom = up_rect.top + (up_rect.Height() / 2);
    down_rect.top = down_rect.bottom - (down_rect.Height() / 2);
    //������һ���ʵ��ı�������Ҫ�Ŀ��ȣ��Ӷ�ʵ����һ�и���Ҷ���
    //GetDC()->SelectObject(&theApp.m_font_set.lyric.GetFont(theApp.m_ui_data.full_screen));
    int width;
    if (!swap)
        width = GetTextExtent(next_lyric).cx;
    else
        width = GetTextExtent(lyric).cx;
    if (width < rect.Width())
        down_rect.left = down_rect.right - width;

    COLORREF color1, color2;
    if (theApp.m_lyric_setting_data.lyric_karaoke_disp)
    {
        color1 = m_colors.color_text;
        color2 = m_colors.color_text_2;
    }
    else
    {
        color1 = color2 = m_colors.color_text;
    }

    if (!swap)
    {
        DrawWindowText(up_rect, lyric, color1, color2, progress, false);
        DrawWindowText(down_rect, next_lyric, m_colors.color_text_2);
    }
    else
    {
        DrawWindowText(up_rect, next_lyric, m_colors.color_text_2);
        DrawWindowText(down_rect, lyric, color1, color2, progress, false);
    }
}