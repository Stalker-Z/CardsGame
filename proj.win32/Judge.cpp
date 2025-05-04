#include "Judge.h"

bool Judge::judgeNumber(int num, int stdnum)
{
    if (num - stdnum == 1 || stdnum - num == 1) return true;
    if (num == 0 && stdnum == 12) return true;
    if (num == 12 && stdnum == 0) return true;
    return false;
}
