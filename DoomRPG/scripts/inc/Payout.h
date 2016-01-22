#ifndef _PAYOUT_H_
#define _PAYOUT_H_

#include "Defs.h"

NamedScript Console void CalculatePayout();

NamedScriptSync void PayoutDrawData(PayoutData *, int);

void PayoutCalculateTotals();
void PayoutAddPP();
int PayoutCalculatePPTotal();

#endif
