#include "main.h"

unsigned long run_time_count = 0;

void StartRunTimeStat(void)
{
    LL_TIM_EnableIT_UPDATE(TIM6);
    LL_TIM_EnableCounter(TIM6);
}

unsigned long GetRuntimeCount(void)
{
    return run_time_count;
}

void Tim6Callback(void)
{
    run_time_count++;

    LL_TIM_ClearFlag_UPDATE(TIM6);
}
