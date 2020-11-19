/*
 * corePKCS11 V2.0.0
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/**
 * @file C_GenerateRandom_harness.c
 * @brief Implements the proof harness for C_GenerateRandom function.
 */

#include <stddef.h>
#include <stdlib.h>
#include "core_pkcs11.h"

void harness()
{
    CK_RV xResult;
    CK_FLAGS xFlags;
    CK_BYTE_PTR pucRandData;
    CK_ULONG ulRandLen;

    CK_SESSION_HANDLE xSession;

    xResult = C_Initialize( NULL );
    __CPROVER_assert( xResult == CKR_OK, "PKCS #11 module needs to be initialized"
                                         " to be uninitialized." );
    xResult = C_OpenSession( 0, xFlags, NULL, 0, &xSession );

    if( xResult == CKR_OK )
    {
        pucRandData = malloc( ( sizeof( CK_BYTE ) ) * ulRandLen );
        ( void ) C_GenerateRandom( xSession, pucRandData, ulRandLen );
        free( pucRandData );
    }
}