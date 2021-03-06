/*
 * whip6: Warsaw High-performance IPv6.
 *
 * Copyright (c) 2017 University of Warsaw
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE
 * files.
 */
#include <stdio.h>
#include "scif_uart_emulator.h"

#define LOST_BUFFER_SIZE 20

module HalUARTNonBlockingWritePrv {
    provides interface NonBlockingWrite<uint8_t>;
} implementation {
    const uint32_t SC_UART_FREE_THRESHOLD = 2 * SCIF_UART_TX_FIFO_MAX_COUNT / 4; // == 1/4

    uint32_t m_lost_bytes = 0;
    char m_last_char = 0;
    char m_buffer[LOST_BUFFER_SIZE]; // buffer to contain the message about lost bytes

    async command error_t NonBlockingWrite.write(uint8_t value) {
        // Each cell has space for two bytes
        uint32_t free = 2 * (SCIF_UART_TX_FIFO_MAX_COUNT - scifUartGetTxFifoCount());
        if (m_lost_bytes > 0) {
            uint32_t needed;
            snprintf(m_buffer, LOST_BUFFER_SIZE, "\nLOST:%d\n%c", m_lost_bytes, value);
            needed = strlen(m_buffer);
            if (free >= needed && free >= SC_UART_FREE_THRESHOLD) {
                scifUartTxPutChars(m_buffer, needed);
                m_lost_bytes = 0;
                return SUCCESS;
            } else {
                m_lost_bytes++;
                return FAIL;
            }
        } else {
            if (free > 0) {
                if (m_last_char != 0) {
                    scifUartTxPutTwoChars(m_last_char, value);
                    m_last_char = 0;
                } else if (value == '\n') { // flush after newline
                    scifUartTxPutChar(value);
                } else {
                    m_last_char = value;
                }
                return SUCCESS;
            } else {
                m_lost_bytes = 1;
                return FAIL;
            }
        }
    }
}
