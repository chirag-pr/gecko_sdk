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
 *  This file implements the circular queue management and provides.
 *  These utility functions can be used to store and release the data
 *  in a circular queue.
 *
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "common/debug.hpp"
#include "utils/code_utils.h"

#include "circular_queue_manager.h"
#include "em_core.h"

#define CIRCULAR_QUEUE_SIZE_MIN 2

void efr32CircularQueueInit(efr32CircularQueue_t *aQueueHandle, const uint8_t aQueueSize)
{
    OT_ASSERT(aQueueHandle != NULL && aQueueSize >= CIRCULAR_QUEUE_SIZE_MIN);

    aQueueHandle->maxSize = aQueueSize;
    aQueueHandle->head    = 0;
    aQueueHandle->tail    = 0;
    aQueueHandle->isFull  = false;
}

bool efr32CircularQueueIsFull(efr32CircularQueue_t *aQueueHandle)
{
    OT_ASSERT(aQueueHandle != NULL);
    return (aQueueHandle->isFull);
}

bool efr32CircularQueueIsEmpty(efr32CircularQueue_t *aQueueHandle)
{
    OT_ASSERT(aQueueHandle != NULL);

    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();
    bool isEmpty = ((aQueueHandle->head == aQueueHandle->tail) && (!efr32CircularQueueIsFull(aQueueHandle)));
    CORE_EXIT_ATOMIC();

    return isEmpty;
}

efr32QueueIndex_t efr32CircularQueueGetFreeIndex(efr32CircularQueue_t *aQueueHandle)
{
    OT_ASSERT(aQueueHandle != NULL);

    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();
    efr32QueueIndex_t freeIndex =
        (efr32CircularQueueIsFull(aQueueHandle)) ? EFR32_INVALID_QUEUE_INDEX : aQueueHandle->head;
    otEXPECT(freeIndex < aQueueHandle->maxSize);
    // Increment the head.
    aQueueHandle->head   = ((aQueueHandle->head + 1) % aQueueHandle->maxSize);
    aQueueHandle->isFull = (aQueueHandle->head == aQueueHandle->tail);

exit:
    CORE_EXIT_ATOMIC();
    return freeIndex;
}

efr32QueueIndex_t efr32CircularQueueGetNextInuseIndex(efr32CircularQueue_t *aQueueHandle)
{
    OT_ASSERT(aQueueHandle != NULL);

    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();
    efr32QueueIndex_t inUseIndex =
        (efr32CircularQueueIsEmpty(aQueueHandle)) ? EFR32_INVALID_QUEUE_INDEX : aQueueHandle->tail;
    CORE_EXIT_ATOMIC();

    return inUseIndex;
}

void efr32CircularQueueFreeIndex(efr32CircularQueue_t *aQueueHandle)
{
    OT_ASSERT(aQueueHandle != NULL);

    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();
    aQueueHandle->tail   = ((aQueueHandle->tail + 1) % aQueueHandle->maxSize);
    aQueueHandle->isFull = false;
    CORE_EXIT_ATOMIC();
}
