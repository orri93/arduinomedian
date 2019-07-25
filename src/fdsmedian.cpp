#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#endif

#include "fdsmedian.h"

namespace fds {
namespace statistics {
Median::Median() {
  reset();
}
void Median::reset() {
  count_ = 0;
  index_ = MEDIAN_COUNT;
  for (uint8_t i = 0; i < MEDIAN_COUNT; i++) {
    p_[i] = i;
  }
   issorted_= false;
}
void Median::clearallbutlast() {
  MEDIAN_TYPE last = values_[index_];
  reset();
  add(last);
}
bool Median::add(const MEDIAN_TYPE & value) {
  issorted_ = false;
  index_ = index_ < MEDIAN_COUNT - 1 ? index_ + 1 : 0;
  values_[index_] = value;
  if (count_ < MEDIAN_COUNT) {
    count_++;
    return false;
  } else {
    return true;
  }
}

MEDIAN_TYPE Median::median() {
  switch(count_) {
  case 0:
    return MEDIAN_UNDEFINED;
  case 1:
    return values_[0];
  case 2:
    return (values_[0] + values_[1]) / 2.0F;
  default:
    if (issorted_ == false) {
      MEDIAN_SORT();
    }
    if (count_ & 0x01)
      return values_[p_[count_/2]];
    else
      return (values_[p_[count_/2]] + values_[p_[count_/2 - 1]]) / 2.0F;
  }
}

#if MEDAIN_SORT == bubblesort
void Median::bubblesort()
{
  uint8_t i, j, t;
  // bubble sort with flag
  for (i = 0; i < count_ - 1; i++)
  {
    issorted_ = true;
    for (j = 1; j < count_- i; j++)
    {
      if (values_[p_[j-1]] > values_[p_[j]])
      {
        t = p_[j - 1];
        p_[j- 1] = p_[j];
        p_[j] = t;
        issorted_ = false;
      }
    }
    if (issorted_) break;
  }
  issorted_ = true;
}
#else
void Median::insertionsort() {
  for(i_ = 1; i_ < count_; i_++) {
    j_ = i_;
    for(j_ = i_; j_ > 0 && values_[p_[j_ - 1]] >  values_[p_[j_]]; j_--) {
      t_ = p_[j_ - 1];
      p_[j_ - 1] = p_[j_];
      p_[j_] = t_;
    }
  }
}
#endif

}
}
