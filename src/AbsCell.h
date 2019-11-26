﻿// -*- mode: c++; c-file-style: "linux"; c-basic-offset: 2; indent-tabs-mode: nil -*-
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
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//  SPDX-License-Identifier: GPL-2.0+

/*! \file
  This file declares the class AbsCell

  AbsCell is the Cell type that represents the field that represents the 
  <code>abs()</code> and <code>cabs()</code> commands.
 */

#ifndef ABSCELL_H
#define ABSCELL_H

#include "Cell.h"
#include "TextCell.h"

/*! \file
  
  This file defines the class for the cell type that represents an abs(x) block.
*/

/*! A cell that represents an abs(x) block
  
  In the case that this cell is broken into two lines in the order of
  m_nextToDraw this cell is represented by the following individual 
  cells:
  
   - The AbsCell itself
   - The opening "abs("
   - The contents
   - The closing ")".
   
  If it isn't broken into multiple cells m_nextToDraw points to the 
  cell that follows this AbsCell.  
 */
class AbsCell : public Cell
{
public:
  AbsCell(Cell *parent, Configuration **config, CellPointers *cellPointers);
  AbsCell(const AbsCell &cell);
  Cell *Copy() override {return new AbsCell(*this);}
  AbsCell& operator=(const AbsCell &other);
  ~AbsCell();
  
  std::list<Cell *> GetInnerCells() override;

  void SetInner(Cell *inner);

  bool BreakUp() override;

  void Unbreak() override;

  void RecalculateHeight(int fontsize) override;
  
  void RecalculateWidths(int fontsize) override;

  virtual void Draw(wxPoint point) override;

  wxString ToString() override;

  wxString ToMatlab() override;

  wxString ToTeX() override;

  wxString ToMathML() override;

  wxString ToXML() override;

  wxString ToOMML() override;

protected:
  //! The contents of the abs() comand
  Cell *m_innerCell;
  //! The cell containing the eventual "abs" and the opening parenthesis
  TextCell *m_open;
  //! The cell containing the closing parenthesis
  TextCell *m_close;
  //! The last element of m_innerCell
  Cell *m_last;
};

#endif // ABSCELL_H
