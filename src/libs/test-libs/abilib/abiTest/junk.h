#pragma once
/*-------------------------------------------------------------------------------------------
 * qblocks - fast, easily-accessible, fully-decentralized data from blockchains
 * copyright (c) 2018 Great Hill Corporation (http://greathill.com)
 *
 * This program is free software: you may redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version. This program is
 * distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details. You should have received a copy of the GNU General
 * Public License along with this program. If not, see http://www.gnu.org/licenses/.
 *-------------------------------------------------------------------------------------------*/
#include <vector>
#include "etherlib.h"

//-----------------------------------------------------------------------------
class CJunk : public CBaseNode {
public:
    vector<CFunction> array1;
    DECLARE_NODE(CJunk);
    CJunk(void);
};
inline void CJunk::finishParse(void) {}
inline bool CJunk::Serialize(CArchive& archive) {return true;}
inline bool CJunk::SerializeC(CArchive& archive) const {return true;}
