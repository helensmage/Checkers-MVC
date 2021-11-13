#include "Board.h"


Board::Board() : mBoardSize(8)
{
}


Board::~Board()
{
}

void Board::ResetMap()
{
  
  for (size_t i = 0; i < mBoardSize; i++)
  {
    for (size_t j = 0; j < mBoardSize; j++)
    {
      Cell::State state(Cell::State::BLANK);
      
      if (i == 0 && j % 2 != 0)
      {
        state = Cell::State::WHITE;
      }
      else if (i == 1 && j % 2 == 0)
      {
        state = Cell::State::WHITE;
      }
      else if (i == 2 && j % 2 != 0)
      {
        state = Cell::State::WHITE;
      } else if (i == 5 && j % 2 == 0)
      {
        state = Cell::State::BLACK;
      }
      else if (i == 6 && j % 2 != 0)
      {
        state = Cell::State::BLACK;
      }
      else if (i == 7 && j % 2 == 0)
      {
        state = Cell::State::BLACK;
      }

      const pos position = pos(i, j);
      Cell cell = Cell(state);
      mCells.insert({ std::move(position), std::move(cell) });
    }
  }
}


Board::MoveResult Board::CheckMove(const pos& startPos, const pos& endPos, bool direction)
{
  Board::MoveResult result = Board::MoveResult::PROHIBITED;
  const int dY = endPos.first - startPos.first;
  const int dX = endPos.second - startPos.second;
  bool isCombat = false;

  if (dX == 0 && dY == 0 && endPos.first == 0 && endPos.second == 0)
  {
    result = Board::MoveResult::FF;
  }
  else if (endPos.first >= 0 && endPos.first < mBoardSize && endPos.second >= 0 && endPos.second < mBoardSize)
  {
    auto targetCellState = mCells.at(endPos).GetState();

    if (targetCellState == Cell::State::BLANK)
    {
      if (abs(dX) == 2 && abs(dY) == 2)
      {
        pos victimPos((startPos.first + endPos.first) / 2, (startPos.second + endPos.second) / 2);
        auto victimCellState = mCells.at(victimPos).GetState();
        auto startCellState = mCells.at(startPos).GetState();

        result = 
          targetCellState != victimCellState && startCellState != victimCellState ? Board::MoveResult::SUCCESSFUL_COMBAT : result;
      }
      else if ((abs(dX) == 1 && dY == 1 && direction) || (abs(dX) == 1 && dY == -1 && !direction))
      {
        result = Board::MoveResult::SUCCESSFUL_MOVE;
      }
    }
  }

  return result;
}


Board::MoveResult Board::MakeMove(const pos& startPos, const pos& endPos, bool direction, bool forceCombat)
{
  auto moveResult = CheckMove(startPos, endPos, direction);

  switch(moveResult)
  {
  case Board::MoveResult::SUCCESSFUL_MOVE:
    mCells.at(endPos).SetState(mCells.at(startPos).GetState());
    mCells.at(startPos).SetState(Cell::State::BLANK);
    break;
  case Board::MoveResult::SUCCESSFUL_COMBAT:
    mCells.at(endPos).SetState(mCells.at(startPos).GetState());
    mCells.at(startPos).SetState(Cell::State::BLANK);
    mCells.at(pos((startPos.first + endPos.first) / 2, (startPos.second + endPos.second) / 2)).SetState(Cell::State::BLANK);
    break;
  }

  return moveResult;
}
