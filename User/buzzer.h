#ifndef __BUZZER_H
#define __BUZZER_H

#include "common.h"

void BUZZER_InitTIM2CH2();
void BUZZER_InitTIM3();
void BUZZER_Cmd(FunctionalState state);

#endif