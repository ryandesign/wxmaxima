// -*- mode: c++; c-file-style: "linux"; c-basic-offset: 2; indent-tabs-mode: nil -*-
//
//  Copyright (C) 2004-2015 Andrej Vodopivec <andrej.vodopivec@gmail.com>
//            (C) 2014-2018 Gunter Königsmann <wxMaxima@physikbuch.de>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
//
//  SPDX-License-Identifier: GPL-2.0+

/*! \file
  This file defines the class FunCell

  FunCell is the Cell type that represents functions that don't require special handling.
 */

#include "FunCell.h"
#include "TextCell.h"
#include "VisiblyInvalidCell.h"

FunCell::FunCell(GroupCell *parent, Configuration **config) :
  Cell(parent, config),
  m_nameCell(std::make_unique<VisiblyInvalidCell>(parent,config)),
  m_argCell(std::make_unique<VisiblyInvalidCell>(parent,config))
{
  InitBitFields();
}

FunCell::FunCell(const FunCell &cell):
 FunCell(cell.m_group, cell.m_configuration)
{
  CopyCommonData(cell);
  m_altCopyText = cell.m_altCopyText;
  if(cell.m_nameCell)
    SetName(cell.m_nameCell->CopyList());
  if(cell.m_argCell)
    SetArg(cell.m_argCell->CopyList());
}

std::unique_ptr<Cell> FunCell::Copy() const
{
  return std::make_unique<FunCell>(*this);
}

void FunCell::SetName(std::unique_ptr<Cell> &&name)
{
  if (!name)
    return;
  m_nameCell = std::move(name);
  m_nameCell->SetStyle(TS_FUNCTION);
}

void FunCell::SetArg(std::unique_ptr<Cell> &&arg)
{  
  if (!arg)
    return;
  m_argCell = std::move(arg);
}

void FunCell::RecalculateWidths(AFontSize fontsize)
{
  if(!NeedsRecalculation(fontsize))
    return;

  m_argCell->RecalculateWidthsList(fontsize);
  m_nameCell->RecalculateWidthsList(fontsize);
  m_width = m_nameCell->GetFullWidth() + m_argCell->GetFullWidth() - Scale_Px(1);

  if(m_isBrokenIntoLines)
    m_width = 0;
  Cell::RecalculateWidths(fontsize);
}

void FunCell::RecalculateHeight(AFontSize fontsize)
{
  if(!NeedsRecalculation(fontsize))
    return;

  m_nameCell->RecalculateHeightList(fontsize);
  m_argCell->RecalculateHeightList(fontsize);
  if(!m_isBrokenIntoLines)
  {
    m_center = wxMax(m_nameCell->GetCenterList(), m_argCell->GetCenterList());
    m_height = m_center + wxMax(m_nameCell->GetMaxDrop(), m_argCell->GetMaxDrop());
  }
  else
    m_height = 0;
  Cell::RecalculateHeight(fontsize);
}

void FunCell::Draw(wxPoint point)
{
  Cell::Draw(point);
  if (DrawThisCell(point))
  {

    wxPoint name(point), arg(point);
    m_nameCell->DrawList(name);

    arg.x += m_nameCell->GetFullWidth();
    m_argCell->DrawList(arg);
  }
}

wxString FunCell::ToString() const
{
  if (m_isBrokenIntoLines)
    return wxEmptyString;
  if (m_altCopyText != wxEmptyString)
    return m_altCopyText;
  return m_nameCell->ListToString() + m_argCell->ListToString();
}

wxString FunCell::ToMatlab() const
{
  if (m_isBrokenIntoLines)
	return wxEmptyString;
  if (m_altCopyText != wxEmptyString)
	return m_altCopyText + Cell::ListToMatlab();
  wxString s = m_nameCell->ListToMatlab() + m_argCell->ListToMatlab();
  return s;
}

wxString FunCell::ToTeX() const
{
  if (m_isBrokenIntoLines)
    return wxEmptyString;

  wxString s;

  if (
    (m_nameCell->ToString() == wxT("sin")) ||
    (m_nameCell->ToString() == wxT("cos")) ||
    (m_nameCell->ToString() == wxT("cosh")) ||
    (m_nameCell->ToString() == wxT("sinh")) ||
    (m_nameCell->ToString() == wxT("log")) ||
    (m_nameCell->ToString() == wxT("cot")) ||
    (m_nameCell->ToString() == wxT("sec")) ||
    (m_nameCell->ToString() == wxT("csc")) ||
    (m_nameCell->ToString() == wxT("tan"))
    )
    s = wxT("\\") + m_nameCell->ToString() + wxT("{") + m_argCell->ListToTeX() + wxT("}");
  else
    s = m_nameCell->ListToTeX() + m_argCell->ListToTeX();
  
  return s;
}

wxString FunCell::ToXML() const
{
//  if (m_isBrokenIntoLines)
//    return wxEmptyString;
  wxString flags;
  if (m_forceBreakLine)
    flags += wxT(" breakline=\"true\"");
  return wxT("<fn") + flags + wxT("><r>") + m_nameCell->ListToXML() + wxT("</r>") +
         m_argCell->ListToXML() + wxT("</fn>");
}

wxString FunCell::ToMathML() const
{
//  if (m_isBrokenIntoLines)
//    return wxEmptyString;
  return wxT("<mrow>") + m_nameCell->ListToMathML() +
         wxT("<mo>&#x2061;</mo>") + m_argCell->ListToMathML() + wxT("</mrow>\n");
}

wxString FunCell::ToOMML() const
{
  return m_nameCell->ListToOMML() +
         m_argCell->ListToOMML();
}

bool FunCell::BreakUp()
{
  if (!m_isBrokenIntoLines)
  {
    Cell::BreakUp();
    m_isBrokenIntoLines = true;
    m_nameCell->last()->SetNextToDraw(m_argCell);
    m_argCell->last()->SetNextToDraw(m_nextToDraw);
    m_nextToDraw = m_nameCell;
    ResetCellListSizes();
    m_height = 0;
    m_center = 0;
    return true;
  }
  return false;
}

void FunCell::SetNextToDraw(Cell *next)
{
  if(m_isBrokenIntoLines)
    m_argCell->last()->SetNextToDraw(next);
  else
    m_nextToDraw = next;
}
