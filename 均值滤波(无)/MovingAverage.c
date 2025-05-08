#include "MovingAverage.h"


void MovingAverage_Init(MovingAverageFilter* filter) {
    memset(filter->buffer, 0, sizeof(filter->buffer));
    filter->index = 0;
    filter->sum = 0.0f;
}

float MovingAverage_Update(MovingAverageFilter* filter, float new_value) {
    // 减去最早的值，加上新值
    filter->sum -= filter->buffer[filter->index];
    filter->sum += new_value;
    
    // 更新缓冲区
    filter->buffer[filter->index] = new_value;
    filter->index = (filter->index + 1) % WINDOW_SIZE;
    
    return filter->sum / WINDOW_SIZE;
}

