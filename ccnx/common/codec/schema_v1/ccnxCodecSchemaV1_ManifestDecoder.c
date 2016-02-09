/*
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * Copyright 2014-2015 Palo Alto Research Center (PARC), a Xerox company.  All Rights Reserved.
 * The content of this file, whole or in part, is subject to licensing terms.
 * If distributing this software, include this License Header Notice in each
 * file and provide the accompanying LICENSE file.
 */
/**
 * @author Marc Mosko, Computing Science Laboratory, PARC
 * @copyright 2014-2015 Palo Alto Research Center (PARC), A Xerox Company. All Rights Reserved.
 */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>

#include <LongBow/runtime.h>

#include <parc/algol/parc_Memory.h>
#include <parc/algol/parc_Object.h>
#include <parc/algol/parc_Buffer.h>

#include <ccnx/common/codec/schema_v1/ccnxCodecSchemaV1_Types.h>
#include <ccnx/common/codec/schema_v1/ccnxCodecSchemaV1_ManifestDecoder.h>

#include <ccnx/common/codec/ccnxCodec_TlvUtilities.h>
#include <ccnx/common/ccnx_PayloadType.h>
#include <ccnx/common/ccnx_InterestReturn.h>
#include <ccnx/common/ccnx_Manifest.h>
#include <ccnx/common/ccnx_ManifestHashGroup.h>

//            CCNxCodecSchemaV1Types_CCNxManifestHashGroup_Metadata = 0x0001,
//            CCNxCodecSchemaV1Types_CCNxManifestHashGroup_DataPointer = 0x0002,
//            CCNxCodecSchemaV1Types_CCNxManifestHashGroup_ManifestPointer = 0x0003,

static bool
_decodeHashGroup(CCNxCodecTlvDecoder *decoder, CCNxTlvDictionary *packetDictionary, CCNxManifestHashGroup *group, size_t length)
{
    bool success = true;
    size_t offset = 0;

    while (offset < length) { // add each pointer...
        uint16_t type = ccnxCodecTlvDecoder_GetType(decoder);
        uint16_t value_length = ccnxCodecTlvDecoder_GetLength(decoder);

        offset += (4 + value_length);

        switch (type) {
            case CCNxCodecSchemaV1Types_CCNxManifestHashGroup_DataPointer: {
                PARCBuffer *buffer = ccnxCodecTlvDecoder_GetValue(decoder, value_length);
                ccnxManifestHashGroup_AddPointer(group, CCNxManifestHashGroupPointerType_Data, buffer);
                break;
            }

            case CCNxCodecSchemaV1Types_CCNxManifestHashGroup_ManifestPointer: {
                PARCBuffer *buffer = ccnxCodecTlvDecoder_GetValue(decoder, value_length);
                ccnxManifestHashGroup_AddPointer(group, CCNxManifestHashGroupPointerType_Manifest, buffer);
                break;
            }

            case CCNxCodecSchemaV1Types_CCNxManifestHashGroup_Metadata: // fallthrough
            default:
                // if we do not know the TLV type, put it in this container's unknown list
                success = ccnxCodecTlvUtilities_PutAsListBuffer(decoder, packetDictionary, type, value_length, CCNxCodecSchemaV1TlvDictionary_Lists_MESSAGE_LIST);
                break;
        }

        if (!success) {
            CCNxCodecError *error = ccnxCodecError_Create(TLV_ERR_DECODE, __func__, __LINE__, ccnxCodecTlvDecoder_Position(decoder));
            ccnxCodecTlvDecoder_SetError(decoder, error);
            ccnxCodecError_Release(&error);
        }
    }

    printf("Successfully added the hash group? %d\n", success);

    CCNxManifestInterface *manifest = ccnxManifestInterface_GetInterface(packetDictionary);
    manifest->addHashGroup(packetDictionary, group);
//    _ccnxManifestFacadeV1_AddHashGroup(CCNxTlvDictionary *dict, const CCNxManifestHashGroup *group)

    return success;

}

static bool
_decodeType(CCNxCodecTlvDecoder *decoder, CCNxTlvDictionary *packetDictionary, uint16_t type, uint16_t length)
{
    bool success = false;
    switch (type) {
        case CCNxCodecSchemaV1Types_CCNxMessage_Name: {
            success = ccnxCodecTlvUtilities_PutAsName(decoder, packetDictionary, type, length, CCNxCodecSchemaV1TlvDictionary_MessageFastArray_NAME);
            break;
        }

        case CCNxCodecSchemaV1Types_CCNxMessage_HashGroup: {
            CCNxManifestHashGroup *group = ccnxManifestHashGroup_Create();
            success = _decodeHashGroup(decoder, packetDictionary, group, length);
            break;
        }

        default:
            // if we do not know the TLV type, put it in this container's unknown list
            success = ccnxCodecTlvUtilities_PutAsListBuffer(decoder, packetDictionary, type, length, CCNxCodecSchemaV1TlvDictionary_Lists_MESSAGE_LIST);
            break;
    }

    if (!success) {
        CCNxCodecError *error = ccnxCodecError_Create(TLV_ERR_DECODE, __func__, __LINE__, ccnxCodecTlvDecoder_Position(decoder));
        ccnxCodecTlvDecoder_SetError(decoder, error);
        ccnxCodecError_Release(&error);
    }
    return success;
}

/*
 * We are given a decoder that points to the first TLV of a list of TLVs.  We keep walking the
 * list until we come to the end of the decoder.
 */
bool
ccnxCodecSchemaV1ManifestDecoder_Decode(CCNxCodecTlvDecoder *decoder, CCNxTlvDictionary *manifestDictionary)
{
    return ccnxCodecTlvUtilities_DecodeContainer(decoder, manifestDictionary, _decodeType);
}
