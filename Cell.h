#pragma once

#include <utility>

using pos = std::pair<std::size_t, std::size_t>;

class Cell
{
public:
  enum class State {BLACK, WHITE, BLANK};
  Cell(State state) : mState(state) {}
  State GetState() const { return mState; }
  void SetState(State state) { mState = state; }
private:
  State mState;
};
