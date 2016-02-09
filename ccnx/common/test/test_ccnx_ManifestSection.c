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

// Include the file(s) containing the functions to be tested.
// This permits internal static functions to be visible to this Test Framework.
#include "../ccnx_ManifestHashGroup.c"

#include <inttypes.h>
#include <ccnx/common/ccnx_Manifest.h>

#include <ccnx/common/ccnx_Name.h>
#include <ccnx/common/codec/schema_v1/ccnxCodecSchemaV1_PacketEncoder.h>
#include <ccnx/common/codec/ccnxCodec_TlvPacket.h>
#include <ccnx/common/ccnx_WireFormatMessage.h>

#include <LongBow/unit-test.h>
#include <parc/algol/parc_SafeMemory.h>
#include <parc/algol/parc_Object.h>
#include <parc/algol/parc_ArrayList.h>

LONGBOW_TEST_RUNNER(ccnx_ManifestSection)
{
    LONGBOW_RUN_TEST_FIXTURE(Global);
}

// The Test Runner calls this function once before any Test Fixtures are run.
LONGBOW_TEST_RUNNER_SETUP(ccnx_ManifestSection)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

// The Test Runner calls this function once after all the Test Fixtures are run.
LONGBOW_TEST_RUNNER_TEARDOWN(ccnx_ManifestSection)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE(Global)
{
    // LONGBOW_RUN_TEST_CASE(Global, ccnxManifestHashGroup_Create);
    // LONGBOW_RUN_TEST_CASE(Global, ccnxManifestHashGroup_CreateWithACS_Empty);
    // LONGBOW_RUN_TEST_CASE(Global, ccnxManifestHashGroup_Acquire_Release);
    //
    // LONGBOW_RUN_TEST_CASE(Global, ccnxManifestHashGroup_AddNameEntry);
    // LONGBOW_RUN_TEST_CASE(Global, ccnxManifestHashGroup_AddContentObject);
    //
    // LONGBOW_RUN_TEST_CASE(Global, ccnxManifestHashGroup_GetNameCount);
    // LONGBOW_RUN_TEST_CASE(Global, ccnxManifestHashGroup_GetHashCount);
    // LONGBOW_RUN_TEST_CASE(Global, ccnxManifestHashGroup_GetNameFromHashIndex);
    // LONGBOW_RUN_TEST_CASE(Global, ccnxManifestHashGroup_GetNameChunkFromHashIndex);
    // LONGBOW_RUN_TEST_CASE(Global, ccnxManifestHashGroup_GetHash);
    //
    // LONGBOW_RUN_TEST_CASE(Global, ccnxManifestHashGroup_CreateWithACS_ToString);
    // LONGBOW_RUN_TEST_CASE(Global, ccnxManifestHashGroup_CreateWithACS_ToJson);
    //
    // LONGBOW_RUN_TEST_CASE(Global, ccnxManifestHashGroup_Equals);
}

LONGBOW_TEST_FIXTURE_SETUP(Global)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Global)
{
    uint32_t outstandingAllocations = parcSafeMemory_ReportAllocation(STDERR_FILENO);
    if (outstandingAllocations != 0) {
        printf("%s leaks memory by %d allocations\n", longBowTestCase_GetName(testCase), outstandingAllocations);
        return LONGBOW_STATUS_MEMORYLEAK;
    }
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_CASE(Global, ccnxManifestHashGroup_Create)
{
    CCNxManifestHashGroup *section = ccnxManifestHashGroup_Create();
    assertNotNull(section, "Expected non-null section");
    ccnxManifestHashGroup_Release(&section);
}

// LONGBOW_TEST_CASE(Global, ccnxManifestHashGroup_CreateWithACS_Empty)
// {
//     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//     CCNxManifestHashGroup *section = ccnxManifestHashGroup_CreateWithACS(acsName);
//
//     assertNotNull(section, "Expected non-null section");
//
//     ccnxManifestHashGroup_Release(&section);
//     ccnxName_Release(&acsName);
// }
//
// LONGBOW_TEST_CASE(Global, ccnxManifestHashGroup_AddNameEntry)
// {
//     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//     CCNxManifestHashGroup *section = ccnxManifestHashGroup_CreateWithACS(acsName);
//
//     assertNotNull(section, "Expected non-null section");
//
//     PARCBuffer *buffer = parcBuffer_WrapCString("test");
//     CCNxName *elementName = ccnxName_CreateFromURI("lci:/foo/bar/1");
//     bool result = ccnxManifestHashGroup_AddNameEntry(section, elementName, 0, buffer);
//     assertTrue(result, "Expected successful addition of new name entry");
//
//     size_t nameCount = ccnxManifestHashGroup_GetNameCount(section);
//     size_t hashCount = ccnxManifestHashGroup_GetHashCount(section);
//     assertTrue(nameCount == 1, "Expected 1 name, got %zu", nameCount);
//     assertTrue(hashCount == 1, "Expected 1 name, got %zu", hashCount);
//
//     ccnxManifestHashGroup_Release(&section);
//     ccnxName_Release(&acsName);
//     parcBuffer_Release(&buffer);
//     ccnxName_Release(&elementName);
// }
//
// LONGBOW_TEST_CASE(Global, ccnxManifestHashGroup_AddContentObject)
// {
//     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//     CCNxManifestHashGroup *section = ccnxManifestHashGroup_CreateWithACS(acsName);
//
//     assertNotNull(section, "Expected non-null section");
//
//     PARCBuffer *buffer = parcBuffer_WrapCString("test");
//     CCNxName *elementName = ccnxName_CreateFromURI("lci:/foo/bar/1");
//     CCNxContentObject *contentObject = ccnxContentObject_CreateWithDataPayload(elementName, buffer);
//
//     CCNxCodecNetworkBufferIoVec *iovec = ccnxCodecSchemaV1PacketEncoder_DictionaryEncode(contentObject, NULL);
//     CCNxWireFormatMessageInterface *wireFormatInterface = ccnxWireFormatMessageInterface_GetInterface(contentObject);
//     wireFormatInterface->putIoVec(contentObject, iovec);
//     ccnxCodecNetworkBufferIoVec_Release(&iovec);
//
//     bool result = ccnxManifestHashGroup_AddContentObject(section, contentObject);
//     assertTrue(result, "Expected successful addition of new name entry");
//
//     size_t nameCount = ccnxManifestHashGroup_GetNameCount(section);
//     size_t hashCount = ccnxManifestHashGroup_GetHashCount(section);
//     assertTrue(nameCount == 1, "Expected 1 name, got %zu", nameCount);
//     assertTrue(hashCount == 1, "Expected 1 name, got %zu", hashCount);
//
//     ccnxContentObject_Release(&contentObject);
//     ccnxManifestHashGroup_Release(&section);
//     ccnxName_Release(&acsName);
//     parcBuffer_Release(&buffer);
//     ccnxName_Release(&elementName);
// }
//
// LONGBOW_TEST_CASE(Global, ccnxManifestHashGroup_Acquire_Release)
// {
//     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//     CCNxManifestHashGroup *section = ccnxManifestHashGroup_CreateWithACS(acsName);
//
//     assertNotNull(section, "Expected non-null section");
//
//     PARCReferenceCount firstReferenceCount = parcObject_GetReferenceCount(section);
//
//     CCNxManifestHashGroup *handle = ccnxManifestHashGroup_Acquire(section);
//
//     PARCReferenceCount secondReferenceCount = parcObject_GetReferenceCount(section);
//
//     ccnxManifestHashGroup_Release(&handle);
//
//     PARCReferenceCount thirdReferenceCount = parcObject_GetReferenceCount(section);
//
//     assertTrue(firstReferenceCount == thirdReferenceCount, "Expected %" PRIu64 ", got %" PRIu64, firstReferenceCount, thirdReferenceCount);
//     assertTrue(firstReferenceCount + 1 == secondReferenceCount, "Expected %" PRIu64 ", got %" PRIu64, firstReferenceCount + 1, thirdReferenceCount);
//
//     ccnxManifestHashGroup_Release(&section);
//     ccnxName_Release(&acsName);
// }
//
// LONGBOW_TEST_CASE(Global, ccnxManifestHashGroup_GetACSName)
// {
//     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//     CCNxManifestHashGroup *section = ccnxManifestHashGroup_CreateWithACS(acsName);
//
//     assertNotNull(section, "Expected non-null section");
//
//     CCNxName *linkHandle = ccnxManifestHashGroup_GetACSName(section);
//     assertTrue(ccnxName_Equals(acsName, linkHandle), "Expected names to be equal");
//
//     ccnxManifestHashGroup_Release(&section);
//     ccnxName_Release(&acsName);
// }
//
// LONGBOW_TEST_CASE(Global, ccnxManifestHashGroup_GetNameCount)
// {
//     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//     CCNxManifestHashGroup *section = ccnxManifestHashGroup_CreateWithACS(acsName);
//
//     assertNotNull(section, "Expected non-null section");
//
//     PARCBuffer *buffer = parcBuffer_WrapCString("test");
//     CCNxName *elementName = ccnxName_CreateFromURI("lci:/foo/bar/1");
//     bool result = ccnxManifestHashGroup_AddNameEntry(section, elementName, 0, buffer);
//     assertTrue(result, "Expected successful addition of new name entry");
//
//     size_t nameCount = ccnxManifestHashGroup_GetNameCount(section);
//     assertTrue(nameCount == 1, "Expected 1 name, got %zu", nameCount);
//
//     ccnxManifestHashGroup_Release(&section);
//     ccnxName_Release(&acsName);
//     parcBuffer_Release(&buffer);
//     ccnxName_Release(&elementName);
// }
//
// LONGBOW_TEST_CASE(Global, ccnxManifestHashGroup_GetHashCount)
// {
//     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//     CCNxManifestHashGroup *section = ccnxManifestHashGroup_CreateWithACS(acsName);
//
//     assertNotNull(section, "Expected non-null section");
//
//     PARCBuffer *buffer = parcBuffer_WrapCString("test");
//     CCNxName *elementName = ccnxName_CreateFromURI("lci:/foo/bar/1");
//     bool result = ccnxManifestHashGroup_AddNameEntry(section, elementName, 0, buffer);
//     assertTrue(result, "Expected successful addition of new name entry");
//
//     size_t hashCount = ccnxManifestHashGroup_GetHashCount(section);
//     assertTrue(hashCount == 1, "Expected 1 hash entry, got %zu", hashCount);
//
//     ccnxManifestHashGroup_Release(&section);
//     ccnxName_Release(&acsName);
//     parcBuffer_Release(&buffer);
//     ccnxName_Release(&elementName);
// }
//
// LONGBOW_TEST_CASE(Global, ccnxManifestHashGroup_GetHash)
// {
//     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//     CCNxManifestHashGroup *section = ccnxManifestHashGroup_CreateWithACS(acsName);
//
//     assertNotNull(section, "Expected non-null section");
//
//     PARCBuffer *buffer = parcBuffer_WrapCString("test");
//     CCNxName *elementName = ccnxName_CreateFromURI("lci:/foo/bar/1");
//     bool result = ccnxManifestHashGroup_AddNameEntry(section, elementName, 0, buffer);
//     assertTrue(result, "Expected successful addition of new name entry");
//
//     PARCBuffer *handle = ccnxManifestHashGroup_GetHashAtIndex(section, 0);
//     assertTrue(parcBuffer_Equals(buffer, handle), "Expected PARCBuffer instances to be equal");
//
//     ccnxManifestHashGroup_Release(&section);
//     ccnxName_Release(&acsName);
//     parcBuffer_Release(&buffer);
//     ccnxName_Release(&elementName);
// }
//
// LONGBOW_TEST_CASE(Global, ccnxManifestHashGroup_GetNameFromHashIndex)
// {
//     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//     CCNxManifestHashGroup *section = ccnxManifestHashGroup_CreateWithACS(acsName);
//
//     assertNotNull(section, "Expected non-null section");
//
//     PARCBuffer *buffer = parcBuffer_WrapCString("test");
//     CCNxName *elementName = ccnxName_CreateFromURI("lci:/foo/bar/1");
//     bool result = ccnxManifestHashGroup_AddNameEntry(section, elementName, 0, buffer);
//     assertTrue(result, "Expected successful addition of new name entry");
//
//     CCNxName *mediaName = ccnxManifestHashGroup_GetNameFromHashIndex(section, 0);
//     assertTrue(ccnxName_Equals(elementName, mediaName), "Expected names to be equal");
//
//     ccnxManifestHashGroup_Release(&section);
//     ccnxName_Release(&acsName);
//     parcBuffer_Release(&buffer);
//     ccnxName_Release(&elementName);
// }
//
// LONGBOW_TEST_CASE(Global, ccnxManifestHashGroup_GetNameChunkFromHashIndex)
// {
//     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//     CCNxManifestHashGroup *section = ccnxManifestHashGroup_CreateWithACS(acsName);
//
//     assertNotNull(section, "Expected non-null section");
//
//     PARCBuffer *buffer = parcBuffer_WrapCString("test");
//     CCNxName *elementName = ccnxName_CreateFromURI("lci:/foo/bar/1");
//     bool result = ccnxManifestHashGroup_AddNameEntry(section, elementName, 10, buffer);
//     assertTrue(result, "Expected successful addition of new name entry");
//
//     size_t chunk = ccnxManifestHashGroup_GetNameChunkFromHashIndex(section, 0);
//     assertTrue(chunk == 10, "Expected chunk 10, got %zu", chunk);
//
//     ccnxManifestHashGroup_Release(&section);
//     ccnxName_Release(&acsName);
//     parcBuffer_Release(&buffer);
//     ccnxName_Release(&elementName);
// }
//
// LONGBOW_TEST_CASE(Global, ccnxManifestHashGroup_CreateWithACS_ToString)
// {
//     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//     CCNxManifestHashGroup *section = ccnxManifestHashGroup_CreateWithACS(acsName);
//
//     assertNotNull(section, "Expected non-null section");
//
//     PARCBuffer *buffer = parcBuffer_WrapCString("test");
//     CCNxName *elementName = ccnxName_CreateFromURI("lci:/foo/bar/1");
//     bool result = ccnxManifestHashGroup_AddNameEntry(section, elementName, 0, buffer);
//     assertTrue(result, "Expected successful addition of new name entry");
//
//     char *string = ccnxManifestHashGroup_ToString(section);
//     assertNotNull(string, "Expected non-null string.");
//     parcMemory_Deallocate((void **) &string);
//
//     ccnxManifestHashGroup_Release(&section);
//     ccnxName_Release(&acsName);
//     parcBuffer_Release(&buffer);
//     ccnxName_Release(&elementName);
// }
//
// LONGBOW_TEST_CASE(Global, ccnxManifestHashGroup_CreateWithACS_ToJson)
// {
//     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//     CCNxManifestHashGroup *section = ccnxManifestHashGroup_CreateWithACS(acsName);
//
//     assertNotNull(section, "Expected non-null section");
//
//     PARCBuffer *buffer = parcBuffer_WrapCString("test");
//     CCNxName *elementName = ccnxName_CreateFromURI("lci:/foo/bar/1");
//     bool result = ccnxManifestHashGroup_AddNameEntry(section, elementName, 0, buffer);
//     assertTrue(result, "Expected successful addition of new name entry");
//
//     CCNxJson *actual = ccnxManifestHashGroup_ToJson(section);
//
//     // Encode the expected result
//     char *expectedString = "{\n\
//     \"acs\":	\"lci:/foo/bar/manifest/acs\",\n\
//     \"ListOfNames\":	[{\n\
//                 \"chunk\":	0,\n\
//                 \"name\":	\"lci:/foo/bar/1\"\n\
//                 }],\n\
//     \"ListOfHashes\":	[{\n\
//                 \"index\":	0,\n\
//                 \"hash\":	\"test\"\n\
//                 }]\n\
// }";
//
//     CCNxJson *expected = ccnxJson_CreateFromText(expectedString);
//
//     assertTrue(ccnxJson_Equals(expected, actual), "Expected the correct CCNxJson string.");
//     ccnxJson_Destroy(&actual);
//     ccnxJson_Destroy(&expected);
//
//     ccnxManifestHashGroup_Release(&section);
//     ccnxName_Release(&acsName);
//     parcBuffer_Release(&buffer);
//     ccnxName_Release(&elementName);
// }
//
// static CCNxManifestHashGroup *
// _createFullManifestSection()
// {
//     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//     CCNxManifestHashGroup *section = ccnxManifestHashGroup_CreateWithACS(acsName);
//
//     assertNotNull(section, "Expected non-null section");
//
//     PARCBuffer *buffer = parcBuffer_WrapCString("test");
//     CCNxName *elementName = ccnxName_CreateFromURI("lci:/foo/bar/1");
//     ccnxManifestHashGroup_AddNameEntry(section, elementName, 0, buffer);
//
//     ccnxName_Release(&acsName);
//     parcBuffer_Release(&buffer);
//     ccnxName_Release(&elementName);
//
//     return section;
// }
//
// LONGBOW_TEST_CASE(Global, ccnxManifestHashGroup_Equals)
// {
//     CCNxManifestHashGroup *x = _createFullManifestSection();
//     CCNxManifestHashGroup *y = _createFullManifestSection();
//     CCNxManifestHashGroup *z = _createFullManifestSection();
//
//     CCNxManifestHashGroup *u1 = _createFullManifestSection();
//     ccnxName_Release(&u1->acsName);
//     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/different");
//     u1->acsName = acsName;
//
//     CCNxManifestHashGroup *u2 = _createFullManifestSection();
//     u2->numberOfHashes = 100;
//
//     CCNxManifestHashGroup *u3 = _createFullManifestSection();
//     u3->numberOfNames = 100;
//
//     // different hash entry
//     CCNxManifestHashGroup *u4 = _createFullManifestSection();
//     parcList_Release(&u4->listOfHashes);
//     parcList_Release(&u4->listOfNames);
//     PARCArrayList *hashList4 = parcArrayList_Create((void (*)(void **))parcObject_Release);
//     u4->listOfHashes = parcList(hashList4, PARCArrayListAsPARCList);
//     PARCArrayList *nameList4 = parcArrayList_Create((void (*)(void **))parcObject_Release);
//     u4->listOfNames = parcList(nameList4, PARCArrayListAsPARCList);
//     PARCBuffer *buffer4 = parcBuffer_WrapCString("THIS HASH IS DIFFERENT");
//     CCNxName *elementName4 = ccnxName_CreateFromURI("lci:/foo/bar/1");
//     ccnxManifestHashGroup_AddNameEntry(u4, elementName4, 0, buffer4);
//     parcBuffer_Release(&buffer4);
//     ccnxName_Release(&elementName4);
//
//     CCNxManifestHashGroup *u5 = _createFullManifestSection();
//     parcList_Release(&u5->listOfHashes);
//     parcList_Release(&u5->listOfNames);
//     PARCArrayList *hashList5 = parcArrayList_Create((void (*)(void **))parcObject_Release);
//     u5->listOfHashes = parcList(hashList5, PARCArrayListAsPARCList);
//     PARCArrayList *nameList5 = parcArrayList_Create((void (*)(void **))parcObject_Release);
//     u5->listOfNames = parcList(nameList5, PARCArrayListAsPARCList);
//     PARCBuffer *buffer5 = parcBuffer_WrapCString("test");
//     CCNxName *elementName5 = ccnxName_CreateFromURI("lci:/foo/bar/somethingdifferent");
//     ccnxManifestHashGroup_AddNameEntry(u5, elementName5, 0, buffer5);
//     parcBuffer_Release(&buffer5);
//     ccnxName_Release(&elementName5);
//
//     assertEqualsContract(ccnxManifestHashGroup_Equals, x, y, z, u1, u2, u3, u4, u5, NULL);
//
//     ccnxManifestHashGroup_Release(&x);
//     ccnxManifestHashGroup_Release(&y);
//     ccnxManifestHashGroup_Release(&z);
//     ccnxManifestHashGroup_Release(&u1);
//     ccnxManifestHashGroup_Release(&u2);
//     ccnxManifestHashGroup_Release(&u3);
//     ccnxManifestHashGroup_Release(&u4);
//     ccnxManifestHashGroup_Release(&u5);
// }

int
main(int argc, char *argv[])
{
    LongBowRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(ccnx_ManifestSection);
    int exitStatus = LONGBOW_TEST_MAIN(argc, argv, testRunner);
    longBowTestRunner_Destroy(&testRunner);
    exit(exitStatus);
}
