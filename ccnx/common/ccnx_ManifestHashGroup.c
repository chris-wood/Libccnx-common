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
 * @author Christopher A. Wood, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#include <config.h>
#include <stdio.h>
#include <string.h>

#include <LongBow/runtime.h>

#include <parc/algol/parc_Object.h>
#include <parc/algol/parc_ArrayList.h>

#include <ccnx/common/ccnx_ManifesthashGroup.h>
#include <ccnx/common/internal/ccnx_WireFormatMessageInterface.h>

#define MAX_NUMBER_OF_POINTERS 100

struct ccnx_manifest_hash_group {
    PARCList *pointers;
    size_t numberOfPointers;

    // Metadata
    PARCBuffer *overallDataDigest;
    size_t totalSize;
    size_t childNodeBlockSize;
    CCNxName *locator;
};

struct ccnx_manifest_hash_group_pointer {
    CCNxManifestHashGroupPointerType pointerType;
    PARCBuffer *digest;
};

static void
CCNxManifestHashGroupPointer_FinalRelease(CCNxManifestHashGroupPointer **ptrP)
{
    if ((*ptrP)->digest != NULL) {
        parcBuffer_Release(&(*ptrP)->digest);
    }
}

static bool
CCNxManifestHashGroupPointer_Equals(const CCNxManifestHashGroupPointer *objectA, const CCNxManifestHashGroupPointer *objectB)
{
    if (objectA == objectB) {
        return true;
    }
    if (objectA == NULL || objectB == NULL) {
        return false;
    }
    if (objectA->pointerType == objectB->pointerType) {
        if (parcBuffer_Equals(objectA->digest, objectB->digest)) {
            return true;
        }
    }
    return false;
}

parcObject_ExtendPARCObject(CCNxManifestHashGroupPointer, CCNxManifestHashGroupPointer_FinalRelease,
                            NULL, NULL, CCNxManifestHashGroupPointer_Equals, NULL, NULL, NULL);

parcObject_ImplementAcquire(ccnxManifestHashGroupPointer, CCNxManifestHashGroupPointer);

parcObject_ImplementRelease(ccnxManifestHashGroupPointer, CCNxManifestHashGroupPointer);

CCNxManifestHashGroupPointer *
ccnxManifestHashGroupPointer_Create(CCNxManifestHashGroupPointerType type, const PARCBuffer *digest)
{
    CCNxManifestHashGroupPointer *ptr = parcObject_CreateAndClearInstance(CCNxManifestHashGroupPointer);
    if (ptr != NULL) {
        ptr->pointerType = type;
        ptr->digest = parcBuffer_Acquire(digest);
    }
    return ptr;
}

CCNxManifestHashGroupPointerType
ccnxManifestHashGroupPointer_GetType(const CCNxManifestHashGroupPointer *ptr)
{
    return ptr->pointerType;
}

PARCBuffer *
ccnxManifestHashGroupPointer_GetDigest(const CCNxManifestHashGroupPointer *ptr)
{
    return ptr->digest;
}

static void
_ccnxManifestHashGroup_FinalRelease(CCNxManifestHashGroup **groupP)
{
    if ((*groupP)->pointers != NULL) {
        parcList_Release(&(*groupP)->pointers);
    }
    if ((*groupP)->overallDataDigest != NULL) {
        parcBuffer_Release(&(*groupP)->overallDataDigest);
    }
    if ((*groupP)->locator != NULL) {
        ccnxName_Release(&(*groupP)->locator);
    }
}

parcObject_ExtendPARCObject(CCNxManifestHashGroup, _ccnxManifestHashGroup_FinalRelease, NULL,
                            ccnxManifestHashGroup_ToString, ccnxManifestHashGroup_Equals, NULL, NULL, NULL);

parcObject_ImplementAcquire(ccnxManifestHashGroup, CCNxManifestHashGroup);

parcObject_ImplementRelease(ccnxManifestHashGroup, CCNxManifestHashGroup);

CCNxManifestHashGroup *
ccnxManifestHashGroup_Create()
{
    CCNxManifestHashGroup *section = parcObject_CreateAndClearInstance(CCNxManifestHashGroup);

    if (section != NULL) {
        PARCArrayList *hashList = parcArrayList_Create((void (*)(void **))parcObject_Release);
        section->pointers = parcList(hashList, PARCArrayListAsPARCList);
        section->numberOfPointers = 0;

        section->overallDataDigest = NULL;
        section->totalSize = 0;
        section->childNodeBlockSize = 0;
        section->locator = NULL;
    }

    return section;
}

void
ccnxManifestHashGroup_AddPointer(CCNxManifestHashGroup *group, CCNxManifestHashGroupPointerType type, const PARCBuffer *buffer)
{
    CCNxManifestHashGroupPointer *ptr = ccnxManifestHashGroupPointer_Create(type, buffer);
    parcList_Add(group->pointers, ptr);
}

PARCBuffer *
ccnxManifestHashGroup_GetOverallDataDigest(const CCNxManifestHashGroup *group)
{
    return group->overallDataDigest;
}

size_t
ccnxManifestHashGroup_GetTotalSize(const CCNxManifestHashGroup *group)
{
    return group->totalSize;
}

size_t
ccnxManifestHashGroup_GetChildBlockSize(const CCNxManifestHashGroup *group)
{
    return group->childNodeBlockSize;
}

CCNxName *
ccnxManifestHashGroup_GetLocator(const CCNxManifestHashGroup *group)
{
    return group->locator;
}

size_t
ccnxManifestHashGroup_GetNumberOfPointers(const CCNxManifestHashGroup *group)
{
    return group->numberOfPointers;
}

CCNxManifestHashGroupPointer *
ccnxManifestHashGroup_GetPointerAtIndex(const CCNxManifestHashGroup *group, size_t index)
{
    CCNxManifestHashGroupPointer *entry = parcList_GetAtIndex(group->pointers, index);
    return entry;
}

CCNxManifestHashGroupPointerType
ccnxManifestHashGroup_GetPointerTypeAtIndex(const CCNxManifestHashGroup *group, size_t index)
{
    // TODO: assert in bounds?
    CCNxManifestHashGroupPointer *entry = parcList_GetAtIndex(group->pointers, index);
    return entry->pointerType;
}

PARCBuffer *
ccnxManifestHashGroup_GetPointerDigestAtIndex(const CCNxManifestHashGroup *group, size_t index)
{
    // TODO: assert in bounds?
    CCNxManifestHashGroupPointer *entry = parcList_GetAtIndex(group->pointers, index);
    return entry->digest;
}

bool
ccnxManifestHashGroup_IsFull(const CCNxManifestHashGroup *group)
{
    return group->numberOfPointers < MAX_NUMBER_OF_POINTERS;
}

bool
ccnxManifestHashGroup_Equals(const CCNxManifestHashGroup *objectA, const CCNxManifestHashGroup *objectB)
{
    if (objectA == objectB) {
        return true;
    }
    if (objectA == NULL || objectB == NULL) {
        return false;
    }
//    if (ccnxName_Equals(objectA->acsName, objectB->acsName)) {
//        if (objectA->numberOfHashes == objectB->numberOfHashes) {
//            if (objectA->numberOfNames == objectB->numberOfNames) {
//                for (size_t i = 0; i < parcList_Size(objectA->listOfHashes); i++) {
//                    _CCNxManifestHashGroupHashEntry *entryA = parcList_GetAtIndex(objectA->listOfHashes, i);
//                    _CCNxManifestHashGroupHashEntry *entryB = parcList_GetAtIndex(objectB->listOfHashes, i);
//                    if (!_CCNxManifestHashGroupHashEntry_Equals(entryA, entryB)) {
//                        return false;
//                    }
//                }
//                for (size_t i = 0; i < parcList_Size(objectA->listOfNames); i++) {
//                    _CCNxManifestHashGroupNameEntry *entryA = parcList_GetAtIndex(objectA->listOfNames, i);
//                    _CCNxManifestHashGroupNameEntry *entryB = parcList_GetAtIndex(objectB->listOfNames, i);
//                    if (!_CCNxManifestHashGroupNameEntry_Equals(entryA, entryB)) {
//                        return false;
//                    }
//                }
//                return true;
//            }
//        }
//    }
    return false;
}

char *
ccnxManifestHashGroup_ToString(const CCNxManifestHashGroup *section)
{
// <<<<<<< HEAD
//    char *acsString = ccnxName_ToString(section->acsName);
//
//    char *string;
//    int failure = asprintf(&string, "CCNxManifestHashGroup { .acsLink=\"%s\" }", acsString);
//    assertTrue(failure > -1, "Error asprintf");
//
//    parcMemory_Deallocate((void **) &acsString);
//
//    char *result = parcMemory_StringDuplicate(string, strlen(string));
//    free(string);
//
//    return result;

    return NULL;
}

PARCJSON *
ccnxManifestHashGroup_ToJson(const CCNxManifestHashGroup *group)
{
    PARCJSON *root = parcJSON_Create();

    if (group->overallDataDigest != NULL) {
        char *digestString = parcBuffer_ToString(group->overallDataDigest);
        parcJSON_AddString(root, "overallDataDigest", digestString);
        parcMemory_Deallocate((void **) &digestString);
    }

    if (group->locator != NULL) {
        char *locatorString = ccnxName_ToString(group->locator);
        parcJSON_AddString(root, "locator", locatorString);
        parcMemory_Deallocate((void **) &locatorString);
    }

    if (group->childNodeBlockSize > 0) {
        parcJSON_AddInteger(root, "childNodeBlockSize", group->childNodeBlockSize);
    }

    if (group->totalSize > 0) {
        parcJSON_AddInteger(root, "totalSize", group->totalSize);
    }

    PARCJSONArray *ptrList = parcJSONArray_Create();
    for (size_t i = 0; i < parcList_Size(group->pointers); i++) {
        CCNxManifestHashGroupPointer *ptr = (CCNxManifestHashGroupPointer *) parcList_GetAtIndex(group->pointers, i);
        PARCJSON *ptrJson = parcJSON_Create();

        if (ptr->pointerType == CCNxManifestHashGroupPointerType_Data) {
            parcJSON_AddInteger(ptrJson, "type", 0);
        } else {
            parcJSON_AddInteger(ptrJson, "type", 1);
        }

        char *digestString = parcBuffer_ToString(ptr->digest);
        parcJSON_AddString(ptrJson, "digest", digestString);
        parcMemory_Deallocate(&digestString);

        PARCJSONValue *val = parcJSONValue_CreateFromJSON(ptrJson);
        parcJSONArray_AddValue(ptrList, val);
        parcJSONValue_Release(&val);
    }
    parcJSON_AddArray(root, "HashGroup", ptrList);

    return root;
}

CCNxManifestHashGroup *
ccnxManifestHashGroup_CreateFromJson(const PARCJSON *json)
{
    CCNxManifestHashGroup *group = ccnxManifestHashGroup_Create();

    if (parcJSON_GetPairByName(json, "overallDataDigest") != NULL) {
        PARCJSONValue *overallDataDigestValue = parcJSON_GetValueByName(json, "overallDataDigest");
        group->overallDataDigest = parcJSONValue_GetString(overallDataDigestValue);
    }

    if (parcJSON_GetPairByName(json, "locator") != NULL) {
        PARCJSONValue *locatorValue = parcJSON_GetValueByName(json, "locator");
        PARCBuffer *buffer = parcJSONValue_GetString(locatorValue);
        group->locator = ccnxName_CreateFromURI(parcBuffer_ToString(buffer));
    }

    if (parcJSON_GetPairByName(json, "childNodeBlockSize") != NULL) {
        PARCJSONValue *childBlockNodeSizeValue = parcJSON_GetValueByName(json, "childNodeBlockSize");
        group->childNodeBlockSize = parcJSONValue_GetInteger(childBlockNodeSizeValue);
    }

    if (parcJSON_GetPairByName(json, "totalSize") != NULL) {
        PARCJSONValue *totalSizeValue = parcJSON_GetValueByName(json, "totalSize");
        group->totalSize = parcJSONValue_GetInteger(totalSizeValue);
    }

    PARCJSONValue *ptrListValue = parcJSON_GetValueByName(json, "HashGroup");
    PARCJSONArray *ptrList = parcJSONValue_GetArray(ptrListValue);
    group->numberOfPointers = parcJSONArray_GetLength(ptrList);
    for (size_t i = 0; i < group->numberOfPointers; i++) {
        PARCJSONValue *pointerValue = parcJSONArray_GetValue(ptrList, i); // {"type" : 0, "digest" : "0123102310230123"}

        PARCJSON *typeJson = parcJSONValue_GetJSON(pointerValue);
        PARCJSONValue *typeValue = parcJSON_GetValueByName(typeJson, "type");
        CCNxManifestHashGroupPointerType type;

        if (parcJSONValue_GetInteger(typeValue) == 0) {
            type = CCNxManifestHashGroupPointerType_Data;
        } else {
            type = CCNxManifestHashGroupPointerType_Manifest;
        }

        PARCJSON *digestJson = parcJSONValue_GetJSON(pointerValue);
        PARCJSONValue *digestValue = parcJSON_GetValueByName(digestJson, "digest");
        PARCBuffer *digest = parcJSONValue_GetString(digestValue);

        ccnxManifestHashGroup_AddPointer(group, type, digest);
    }

    return group;
}

struct _hashgroup_iterator_state {
    size_t pointerNumber;
    bool atEnd;
};
typedef struct _hashgroup_iterator_state _HashgroupIteratorState;

static void *
_iterator_Init(CCNxManifestHashGroup *group)
{
    _HashgroupIteratorState *state = parcMemory_Allocate(sizeof(_HashgroupIteratorState));
    state->pointerNumber = 0;
    state->atEnd = false;
    return state;
}

static bool
_iterator_HasNext(CCNxManifestHashGroup *group, void *voidstate)
{
    _HashgroupIteratorState *state = (_HashgroupIteratorState *) voidstate;
    return !state->atEnd;
}

static void *
_iterator_Next(CCNxManifestHashGroup *group, void *state)
{
    _HashgroupIteratorState *thestate = (_HashgroupIteratorState *) state;
    thestate->pointerNumber++;

    if (thestate->pointerNumber == group->numberOfPointers) {
        thestate->atEnd = true;
    }

    return thestate;
}

static void
_iterator_RemoveAt(CCNxManifestHashGroup *group, void **state)
{
    // pass
}

static void *
_iterator_GetElement(CCNxManifestHashGroup *group, void *state)
{
    _HashgroupIteratorState *thestate = (_HashgroupIteratorState *) state;
    CCNxManifestHashGroupPointer *ptr =
        (CCNxManifestHashGroupPointer *) parcList_GetAtIndex(group->pointers, thestate->pointerNumber - 1);
    return ptr;
}

static void
_iterator_Finish(CCNxManifestHashGroup *group, void *state)
{
    _HashgroupIteratorState *thestate = (_HashgroupIteratorState *) state;
    parcMemory_Deallocate(&thestate);
}

static void
_iterator_AssertValid(const void *state)
{
    // pass
}

PARCIterator *
ccnxManifestHashGroup_Iterator(const CCNxManifestHashGroup *group)
{
    PARCIterator *iterator = parcIterator_Create((void *) group,
                                                 (void *(*)(PARCObject *)) _iterator_Init,
                                                 (bool  (*)(PARCObject *, void *)) _iterator_HasNext,
                                                 (void *(*)(PARCObject *, void *)) _iterator_Next,
                                                 (void  (*)(PARCObject *, void **)) _iterator_RemoveAt,
                                                 (void *(*)(PARCObject *, void *)) _iterator_GetElement,
                                                 (void  (*)(PARCObject *, void *)) _iterator_Finish,
                                                 (void  (*)(const void *)) _iterator_AssertValid);

    return iterator;
}
