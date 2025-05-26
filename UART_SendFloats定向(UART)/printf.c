#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart2;  // 确保已在 main.c 定义 UART_HandleTypeDef huart2

/**
 * @brief 通过 UART2 发送多个 float 数据
 * @param data float 数组指针
 * @param count 数据个数
 * @param decimal_places 小数位数（如 2 表示保留 2 位小数）
 */
void UART_SendFloats(float *data, uint8_t count, uint8_t decimal_places) {
    char buffer[128];  // 缓冲区（根据数据量调整大小）
    char *ptr = buffer;  // 指针指向缓冲区起始位置

    // 遍历所有 float 数据
    for (uint8_t i = 0; i < count; i++) {
        // 格式化 float 到字符串（如 "1.23"）
        ptr += snprintf(ptr, sizeof(buffer) - (ptr - buffer), 
                      "%.*f", decimal_places, data[i]);

        // 添加逗号分隔（最后一个数据不加）
        if (i < count - 1) {
            ptr += snprintf(ptr, sizeof(buffer) - (ptr - buffer), ", ");
        }
    }

    // 添加换行符
    ptr += snprintf(ptr, sizeof(buffer) - (ptr - buffer), "\n");

    // 通过 HAL_UART_Transmit 发送
    HAL_UART_Transmit(&huart2, (uint8_t *)buffer, ptr - buffer, HAL_MAX_DELAY);
}
