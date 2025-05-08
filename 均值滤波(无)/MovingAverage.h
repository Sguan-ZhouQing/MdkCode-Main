#ifndef __MOVINGAVERAGE_H
#define __MOVINGAVERAGE_H

#define WINDOW_SIZE 3  // 窗口大小（建议3~10，越大越平滑但延迟越高）
#define MAX_WINDOW_SIZE 7


typedef struct {
    float buffer[WINDOW_SIZE];
    uint8_t index;
    float sum;
} MovingAverageFilter;

void MovingAverage_Init(MovingAverageFilter* filter);
float MovingAverage_Update(MovingAverageFilter* filter, float new_value);


#endif // 均值滤波函数
