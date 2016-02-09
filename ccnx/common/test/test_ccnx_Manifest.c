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
#include "../ccnx_Manifest.c"
#include <ccnx/common/ccnx_ManifestHashGroup.h>

#include <ccnx/common/ccnx_Link.h>

#include <inttypes.h>

#include <LongBow/unit-test.h>
#include <parc/algol/parc_SafeMemory.h>
#include <parc/algol/parc_ArrayList.h>

typedef struct test_data {
    PARCBuffer *signatureBits;
    PARCSignature *signature;

    CCNxName *name;
    CCNxName *acsName;

//    CCNxManifestSection *payloadSection;
    CCNxManifestHashGroup *hashGroup;

    CCNxManifest *object;
} ManifestTestData;

//static CCNxManifest *
//_createFullManifest(void)
//{
//    PARCBuffer *signatureBits = parcBuffer_WrapCString("signature");
//    PARCSignature *signature = parcSignature_Create(PARCSigningAlgorithm_RSA, PARC_HASH_SHA256, signatureBits);
//
//    CCNxName *name = ccnxName_CreateFromURI("lci:/foo/bar/manifest");
//    CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//    CCNxManifestSection *payloadSection = ccnxManifestSection_CreateWithACS(acsName);
//
//    CCNxManifest *object = ccnxManifest_Create(name);
//    ccnxManifest_SetSection(object, payloadSection);
//
//    parcBuffer_Release(&signatureBits);
//    parcSignature_Release(&signature);
//    ccnxName_Release(&name);
//    ccnxName_Release(&acsName);
//    ccnxManifestSection_Release(&payloadSection);
//
//    return object;
//}

static ManifestTestData *
_commonSetup(void)
{
    ManifestTestData *data = parcMemory_AllocateAndClear(sizeof(ManifestTestData));
//    assertNotNull(data, "parcMemory_AllocateAndClear(%zu) returned NULL", sizeof(ManifestTestData));
//
//    PARCBuffer *signatureBits = parcBuffer_WrapCString("signature");
//    PARCSignature *signature = parcSignature_Create(PARCSigningAlgorithm_RSA, PARC_HASH_SHA256, signatureBits);
//
//    CCNxName *name = ccnxName_CreateFromURI("lci:/foo/bar/manifest");
//    CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//    CCNxManifestSection *payloadSection = ccnxManifestSection_CreateWithACS(acsName);
//
//    CCNxManifest *object = ccnxManifest_Create(name);
//    ccnxManifest_SetSection(object, payloadSection);
//
//    data->signatureBits = signatureBits;
//    data->signature = signature;
//    data->name = name;
//    data->acsName = acsName;
//    data->payloadSection = payloadSection;
//    data->object = object;
    return data;
}

static void
_commonTeardown(ManifestTestData *data)
{
//    parcBuffer_Release(&data->signatureBits);
//    parcSignature_Release(&data->signature);
//    ccnxName_Release(&data->name);
//    ccnxName_Release(&data->acsName);
//    ccnxManifestSection_Release(&data->payloadSection);
//    ccnxManifest_Release(&data->object);

    parcMemory_Deallocate((void **) &data);
}

LONGBOW_TEST_RUNNER(ccnx_Manifest)
{
    LONGBOW_RUN_TEST_FIXTURE(Global);
}

// The Test Runner calls this function once before any Test Fixtures are run.
LONGBOW_TEST_RUNNER_SETUP(ccnx_Manifest)
{
    parcMemory_SetInterface(&PARCSafeMemoryAsPARCMemory);
    return LONGBOW_STATUS_SUCCEEDED;
}

// The Test Runner calls this function once after all the Test Fixtures are run.
LONGBOW_TEST_RUNNER_TEARDOWN(ccnx_Manifest)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE(Global)
{
//    LONGBOW_RUN_TEST_CASE(Global, ccnxManifest_Create_Full);
//    LONGBOW_RUN_TEST_CASE(Global, ccnxManifest_Create_OnlyPayload);
//
//    LONGBOW_RUN_TEST_CASE(Global, ccnxManifest_Acquire_and_Release);
//
//    LONGBOW_RUN_TEST_CASE(Global, ccnxManifest_GetName);
//    LONGBOW_RUN_TEST_CASE(Global, ccnxManifest_GetSection);
//
//    LONGBOW_RUN_TEST_CASE(Global, ccnxManifest_Create_ToString);
//
//    LONGBOW_RUN_TEST_CASE(Global, ccnxManifest_Equals);
}

LONGBOW_TEST_FIXTURE_SETUP(Global)
{
    longBowTestCase_SetClipBoardData(testCase, _commonSetup());

    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Global)
{
    _commonTeardown(longBowTestCase_GetClipBoardData(testCase));
    uint32_t outstandingAllocations = parcSafeMemory_ReportAllocation(STDERR_FILENO);
    if (outstandingAllocations != 0) {
        printf("%s leaks memory by %d allocations\n", longBowTestCase_GetName(testCase), outstandingAllocations);
        return LONGBOW_STATUS_MEMORYLEAK;
    }
    return LONGBOW_STATUS_SUCCEEDED;
}

//LONGBOW_TEST_CASE(Global, ccnxManifest_Create_Full)
//{
//    PARCBuffer *signatureBits = parcBuffer_WrapCString("signature");
//    PARCSignature *signature = parcSignature_Create(PARCSigningAlgorithm_RSA, PARC_HASH_SHA256, signatureBits);
//
//    CCNxName *name = ccnxName_CreateFromURI("lci:/foo/bar/manifest");
//    CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//    CCNxManifestSection *payloadSection = ccnxManifestSection_CreateWithACS(acsName);
//
//    CCNxManifest *object = ccnxManifest_Create(name);
//    ccnxManifest_SetSection(object, payloadSection);
//
//    assertNotNull(object, "Expected non-null return value.");
//
//    ccnxManifest_Release(&object);
//    parcBuffer_Release(&signatureBits);
//    parcSignature_Release(&signature);
//    ccnxName_Release(&name);
//    ccnxName_Release(&acsName);
//    ccnxManifestSection_Release(&payloadSection);
//}
//
//LONGBOW_TEST_CASE(Global, ccnxManifest_Create_OnlyPayload)
//{
//    PARCBuffer *signatureBits = parcBuffer_WrapCString("signature");
//    PARCSignature *signature = parcSignature_Create(PARCSigningAlgorithm_RSA, PARC_HASH_SHA256, signatureBits);
//
//    CCNxName *name = ccnxName_CreateFromURI("lci:/foo/bar/manifest");
//    CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
//
//    CCNxManifestSection *payloadSection = ccnxManifestSection_CreateWithACS(acsName);
//
//    CCNxManifest *object = ccnxManifest_Create(name);
//    ccnxManifest_SetSection(object, payloadSection);
//
//    assertNotNull(object, "Expected non-null return value.");
//
//    ccnxManifest_Release(&object);
//    parcBuffer_Release(&signatureBits);
//    parcSignature_Release(&signature);
//    ccnxName_Release(&name);
//    ccnxName_Release(&acsName);
//    ccnxManifestSection_Release(&payloadSection);
//}
//
//LONGBOW_TEST_CASE(Global, ccnxManifest_Acquire_and_Release)
//{
//    ManifestTestData *data = longBowTestCase_GetClipBoardData(testCase);
//    CCNxManifest *object = data->object;
//
//    assertNotNull(object, "Expected non-null return value.");
//
//    PARCReferenceCount oldReferenceCount = parcObject_GetReferenceCount(object);
//    CCNxManifest *handle = ccnxManifest_Acquire(object);
//
//    assertNotNull(object, "Expected non-null return value.");
//
//    PARCReferenceCount newReferenceCount = parcObject_GetReferenceCount(object);
//    assertTrue(oldReferenceCount + 1 == newReferenceCount,
//               "Error: expected reference count to be incremented by 1 from %" PRIu64 ", got %" PRIu64, oldReferenceCount, newReferenceCount);
//
//    ccnxManifest_Release(&handle);
//
//    PARCReferenceCount finalReferenceCount = parcObject_GetReferenceCount(object);
//    assertTrue(oldReferenceCount == finalReferenceCount,
//               "Error: expected reference count to be the same as the original (%" PRIu64 "), got %" PRIu64, oldReferenceCount, newReferenceCount);
//}
//
//LONGBOW_TEST_CASE(Global, ccnxManifest_GetName)
//{
//    ManifestTestData *data = longBowTestCase_GetClipBoardData(testCase);
//    CCNxManifest *object = data->object;
//
//    assertNotNull(object, "Expected non-null return value.");
//    CCNxName *name = ccnxManifest_GetName(object);
//    assertTrue(ccnxName_Equals(data->name, name), "Expected name links to be equal");
//}
//
//LONGBOW_TEST_CASE(Global, ccnxManifest_GetSection)
//{
//    ManifestTestData *data = longBowTestCase_GetClipBoardData(testCase);
//    CCNxManifest *object = data->object;
//
//    assertNotNull(object, "Expected non-null return value.");
//
//    CCNxManifestSection *realSection = ccnxManifest_GetSection(object);
//    assertTrue(ccnxManifestSection_Equals(data->payloadSection, realSection), "Expected payload sections to be equal");
//    ccnxManifestSection_Release(&realSection); // this basically constructs a new section from scratch
//}
//
//LONGBOW_TEST_CASE(Global, ccnxManifest_Equals)
//{
//    CCNxManifest *x = _createFullManifest();
//    CCNxManifest *y = _createFullManifest();
//    CCNxManifest *z = _createFullManifest();
//    CCNxManifest *u1 = _createFullManifest();
//
//    CCNxName *name = ccnxName_CreateFromURI("lci:/foo/bar/different-manifest");
//    ccnxName_Release(&name);
//
//    assertEqualsContract(ccnxManifest_Equals, x, y, z, u1, NULL);
//
//    ccnxManifest_Release(&x);
//    ccnxManifest_Release(&y);
//    ccnxManifest_Release(&z);
//    ccnxManifest_Release(&u1);
//}
//
//LONGBOW_TEST_CASE(Global, ccnxManifest_Create_ToString)
//{
//    ManifestTestData *data = longBowTestCase_GetClipBoardData(testCase);
//    CCNxManifest *object = data->object;
//
//    assertNotNull(object, "Expected non-null return value.");
//
//    char *string = ccnxManifest_ToString(object);
//    assertNotNull(string, "Expected non-null string.");
//    parcMemory_Deallocate((void **) &string);
//}

int
main(int argc, char *argv[])
{
    LongBowRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(ccnx_Manifest);
    int exitStatus = LONGBOW_TEST_MAIN(argc, argv, testRunner);
    longBowTestRunner_Destroy(&testRunner);
    exit(exitStatus);
}
