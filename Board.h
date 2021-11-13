#pragma once

#include "Cell.h"
#include <map>

using map1 = std::map<pos, Cell>;

class Board
{
public:
  enum class MoveResult { SUCCESSFUL_MOVE, SUCCESSFUL_COMBAT, PROHIBITED, FF };
  Board();
  ~Board();
  void ResetMap();
  MoveResult MakeMove(const pos& startPos, const pos& endPos, bool direction, bool forceCombat = false);
  const map1& GetMap() const { return mCells; }
private:
  MoveResult CheckMove(const pos& startPos, const pos& endPos, bool direction);
  const size_t mBoardSize;
  map1 mCells;
};
