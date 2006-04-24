///
///  Copyright (C) 2004-2006 Andrej Vodopivec <andrejv@users.sourceforge.net>
///
///  This program is free software; you can redistribute it and/or modify
///  it under the terms of the GNU General Public License as published by
///  the Free Software Foundation; either version 2 of the License, or
///  (at your option) any later version.
///
///  This program is distributed in the hope that it will be useful,
///  but WITHOUT ANY WARRANTY; without even the implied warranty of
///  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
///  GNU General Public License for more details.
///
///
///  You should have received a copy of the GNU General Public License
///  along with this program; if not, write to the Free Software
///  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
///

#ifndef _MATHCELL_H_
#define _MATHCELL_H_

#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)>(b) ? (b) : (a))
#define ABS(a) ((a)>=0 ? (a) : -(a))
#define SCALE_PX(px, scale) ((int)((double)((px)*(scale)) + 0.5))

#define MC_CELL_SKIP 2
#define MC_BASE_INDENT 5
#define MC_LINE_SKIP 5

#include <wx/wx.h>
#include "CellParser.h"
#include "TextStyle.h"

enum {
  MC_TYPE_TEXT,
  MC_TYPE_MAIN_PROMPT,
  MC_TYPE_PROMPT,
  MC_TYPE_LABEL,
  MC_TYPE_INPUT,
  MC_TYPE_ERROR,
  MC_TYPE_COMMENT
};

class MathCell
{
public:
  MathCell();
  virtual ~MathCell();
  virtual MathCell* Copy(bool all) = 0;
  virtual void Destroy() = 0;

  void AppendCell(MathCell *p_next);

  void BreakLine(bool breakLine)
  {
    m_breakLine = breakLine;
  }
  void BreakPage(bool breakPage)
  {
    m_breakPage = breakPage;
  }
  bool BreakLineHere();
  bool ForceBreakLineHere()
  {
    return m_forceBreakLine;
  }
  bool BreakPageHere()
  {
    return m_breakPage;
  }
  virtual bool BreakUp()
  {
    return false;
  }

  bool ContainsRect(wxRect& big, bool all = true);
  bool ContainsPoint(wxPoint& point)
  {
    return GetRect().Inside(point);
  }
  void CopyData(MathCell *s, MathCell *t);

  virtual void Draw(CellParser& parser, wxPoint point, int fontsize, bool all);
  void DrawBoundingBox(wxDC& dc, bool all = false);
  bool DrawThisCell(CellParser& parser, wxPoint point);

  void ForceBreakLine(bool force)
  {
    m_forceBreakLine = m_breakLine = force;
  }
  virtual void Fold(bool fold)
  { }

  int GetHeight()
  {
    return m_height;
  }
  int GetWidth()
  {
    return m_width;
  }
  int GetCenter()
  {
    return m_center;
  }
  int GetDrop()
  {
    return m_height - m_center;
  }
  int GetType()
  {
    return m_type;
  }
  int GetMaxDrop();
  int GetMaxCenter();
  int GetMaxHeight();
  int GetFullWidth(double scale);
  int GetLineWidth(double scale);
  int GetCurrentX()
  {
    return m_currentPoint.x;
  }
  int GetCurrentY()
  {
    return m_currentPoint.y;
  }
  virtual wxRect GetRect(bool all = false);
  virtual wxString GetDiffPart();

  virtual void RecalculateSize(CellParser& parser, int fontsize, bool all);
  virtual void RecalculateWidths(CellParser& parser, int fontsize, bool all);
  void ResetData();

  void SetSkip(bool skip)
  {
    m_bigSkip = skip;
  }
  void SetType(int type)
  {
    m_type = type;
  }
  void SetPen(CellParser& parser);
  void SetHighlight(bool highlight)
  {
    m_highlight = highlight;
  }
  virtual void SetExponentFlag()
  { }
  virtual void SetValue(wxString text)
  { }
  virtual wxString GetValue()
  { return wxEmptyString; }

  void SelectRect(wxRect& rect, MathCell** first, MathCell** last);
  void SelectFirst(wxRect& rect, MathCell** first);
  void SelectLast(wxRect& rect, MathCell** last);
  virtual void SelectInner(wxRect& rect, MathCell** first, MathCell** last);

  virtual bool IsOperator();
  bool IsCompound();
  virtual bool IsShortNum()
  {
    return false;
  }

  virtual wxString ToString(bool all);

  void UnsetPen(CellParser& parser);
  virtual void Unbreak(bool all);

  MathCell *m_next, *m_previous;
  MathCell *m_nextToDraw, *m_previousToDraw;
  wxPoint m_currentPoint;
  bool m_bigSkip;
  bool m_isFolded;
  bool m_isBroken;
  bool m_isHidden;
protected:
  int m_height;
  int m_width;
  int m_fullWidth;
  int m_lineWidth;
  int m_center;
  int m_maxCenter;
  int m_maxDrop;
  int m_type;
  bool m_breakPage;
  bool m_breakLine;
  bool m_forceBreakLine;
  bool m_highlight;
};

#endif //_MATHCELL_H_
