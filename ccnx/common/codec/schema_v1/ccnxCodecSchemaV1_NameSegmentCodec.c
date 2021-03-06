/*
 * Copyright (c) 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Patent rights are not granted under this agreement. Patent rights are
 *       available under FRAND terms.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <LongBow/runtime.h>
#include <parc/algol/parc_Memory.h>
#include <parc/algol/parc_Buffer.h>

#include <ccnx/common/codec/schema_v1/ccnxCodecSchemaV1_NameSegmentCodec.h>

size_t
ccnxCodecSchemaV1NameSegmentCodec_Encode(CCNxCodecTlvEncoder *encoder, CCNxNameSegment *segment)
{
    assertTrue(ccnxNameSegment_Length(segment) <= UINT16_MAX,
               "Name segment too long!  length %zu maximum %u",
               ccnxNameSegment_Length(segment),
               UINT16_MAX);

    uint16_t segment_type = ccnxNameSegment_GetType(segment);
    PARCBuffer *value = ccnxNameSegment_GetValue(segment);

    return ccnxCodecTlvEncoder_AppendBuffer(encoder, segment_type, value);
}

CCNxNameSegment *
ccnxCodecSchemaV1NameSegmentCodec_Decode(CCNxCodecTlvDecoder *decoder)
{
    CCNxNameSegment *segment = NULL;

    if (ccnxCodecTlvDecoder_EnsureRemaining(decoder, 4)) {
        uint16_t type = ccnxCodecTlvDecoder_GetType(decoder);
        uint16_t length = ccnxCodecTlvDecoder_GetLength(decoder);

        if (ccnxCodecTlvDecoder_EnsureRemaining(decoder, length)) {
            PARCBuffer *value = ccnxCodecTlvDecoder_GetValue(decoder, length);
            segment = ccnxNameSegment_CreateTypeValue(type, value);
            parcBuffer_Release(&value);
        }
    }

    return segment;
}
