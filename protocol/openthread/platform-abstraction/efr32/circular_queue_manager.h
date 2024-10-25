/*
 *  Copyright (c) 2024, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *  This file defines the circular queue management API.
 *
 */

#ifndef CIRCULAR_QUEUE_MANAGER_H_
#define CIRCULAR_QUEUE_MANAGER_H_

typedef uint8_t efr32QueueIndex_t;

#define EFR32_INVALID_QUEUE_INDEX 0xFF

// Structure which holds the circular queue management metadata.
typedef struct
{
    // Max size of the queue.
    uint8_t maxSize;
    // Free index.
    volatile efr32QueueIndex_t head;
    // Next in use index.
    volatile efr32QueueIndex_t tail;
    // To check if Queue is full.
    bool isFull;
} efr32CircularQueue_t;

/**
 * Initialize the circular queue.
 *
 * @param[in]   aQueueHandle    A pointer to a circular queue.
 * @param[in]   aQueueSize      The size of a circular queue @p aQueueHandle.
 *
 */
void efr32CircularQueueInit(efr32CircularQueue_t *aQueueHandle, const uint8_t aQueueSize);

/**
 * Returns whether circular queue is full.
 *
 * @param[in]   aQueueHandle    A pointer to a circular queue.
 *
 * @retval  True    The circular queue is full.
 * @retval  False   The circular queue is not full.
 *
 */
bool efr32CircularQueueIsFull(efr32CircularQueue_t *aQueueHandle);

/**
 * Returns whether circular queue is empty.
 *
 * @param[in]   aQueueHandle    A pointer to a circular queue.
 *
 * @retval  True    The circular queue is empty.
 * @retval  False   The circular queue is not empty.
 *
 */
bool efr32CircularQueueIsEmpty(efr32CircularQueue_t *aQueueHandle);

/**
 * Returns the next available index or EFR32_INVALID_QUEUE_INDEX if queue
 * is full.
 *
 * @param[in]   aQueueHandle    A pointer to a circular queue.
 *
 * @retval  efr32QueueIndex_t   The next available index or EFR32_INVALID_QUEUE_INDEX
 *                              if queue is full.
 *
 */
efr32QueueIndex_t efr32CircularQueueGetFreeIndex(efr32CircularQueue_t *aQueueHandle);

/**
 * Returns the next in use index or EFR32_INVALID_QUEUE_INDEX if queue is empty.
 *
 * @param[in]   aQueueHandle    A pointer to a circular queue.
 *
 * @retval  efr32QueueIndex_t   The next in use index or EFR32_INVALID_QUEUE_INDEX
 *                              if queue is empty.
 *
 */
efr32QueueIndex_t efr32CircularQueueGetNextInuseIndex(efr32CircularQueue_t *aQueueHandle);

/**
 * Free the current in use index.
 *
 * @param[in]   aQueueHandle    A pointer to a circular queue.
 *
 */
void efr32CircularQueueFreeIndex(efr32CircularQueue_t *aQueueHandle);

#endif // CIRCULAR_QUEUE_MANAGER_H_
