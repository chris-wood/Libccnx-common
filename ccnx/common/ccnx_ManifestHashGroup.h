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
 * @file ccnx_ManifestHashGroup.h
 * @ingroup ContentObject
 * @brief A SECTION in a generic manifest (metadata or payload).
 *
 * @author Christopher A. Wood, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef libccnx_ccnx_ManifestHashGroup_h
#define libccnx_ccnx_ManifestHashGroup_h

#include <ccnx/common/ccnx_Name.h>
#include <ccnx/common/ccnx_ContentObject.h>

#include <parc/algol/parc_Buffer.h>
#include <parc/algol/parc_List.h>
#include <parc/algol/parc_Memory.h>
#include <parc/algol/parc_JSON.h>
#include <parc/algol/parc_Iterator.h>

#include <parc/security/parc_Signature.h>

struct ccnx_manifest_hash_group;

typedef enum {
    CCNxManifestHashGroupPointerType_Data,
    CCNxManifestHashGroupPointerType_Manifest
} CCNxManifestHashGroupPointerType;

/**
 * @typedef CCNxManifestHashGroup
 * @brief A section in a generic Manifest (metadata or payload)
 */
typedef struct ccnx_manifest_hash_group CCNxManifestHashGroup;

struct ccnx_manifest_hash_group_pointer;
typedef struct ccnx_manifest_hash_group_pointer CCNxManifestHashGroupPointer;

CCNxManifestHashGroupPointerType ccnxManifestHashGroupPointer_GetType(const CCNxManifestHashGroupPointer *ptr);
PARCBuffer *ccnxManifestHashGroupPointer_GetDigest(const CCNxManifestHashGroupPointer *ptr);

/**
 * Create a new and empty {@link CCNxManifestHashGroup} instance.
 *
 * @return A pointer to a {@link CCNxManifestHashGroup} instance, or NULL if an error or out of memory.
 *
 * Example:
 * @code
 * {
 *     CCNxManifestHashGroup *section = CCNxManifestHashGroup_Create();
 *
 *     ...
 *
 *     CCNxManifestHashGroup_Release(&section);
 * }
 * @endcode
 */
CCNxManifestHashGroup *ccnxManifestHashGroup_Create();

/**
 * Create a new {@link CCNxManifestHashGroup} instance from a
 *
 * @param [in] jsonRepresentation - A pointer to a {@link PARCJSON} object representing the `CCNxManifestHashGroup`.
 *
 * @return A pointer to a {@link CCNxManifestHashGroup} instance, or NULL if an error or out of memory.
 *
 * Example:
 * @code
 * {
 *     PARCJSON *jsonRep = ccnxTlvDictionary_GetJson(dict, CCNxCodecSchemaV1TlvDictionary_MessageFastArray_ManifestHashGroup);
 *     CCNxManifestHashGroup *section = CCNxManifestHashGroup_CreateFromJson(jsonRep);
 *
 *     ...
 *
 *     ccnxJson_Destroy(&jsonRep);
 *     CCNxManifestHashGroup_Release(&section);
 * }
 * @endcode
 */
CCNxManifestHashGroup *ccnxManifestHashGroup_CreateFromJson(const PARCJSON *jsonRepresentation);

/**
 * Increase the number of references to an instance of this object.
 *
 * Note that new instance is not created,
 * only that the given instance's reference count is incremented.
 * Discard the reference by invoking {@link CCNxManifestHashGroup_Release()}.
 *
 * @param [in] section A pointer to the {@link CCNxManifestHashGroup} to acquire.
 * @return The value of the input parameter @p section.
 *
 * Example:
 * @code
 * {
 *     CCNxManifest *manifest = CCNxManifestHashGroup_Acquire(instance);
 *
 *     CCNxManifestHashGroup_Release(&manifest);
 * }
 * @endcode
 *
 * @see `CCNxManifestHashGroup_Release`
 */
CCNxManifestHashGroup *ccnxManifestHashGroup_Acquire(const CCNxManifestHashGroup *section);

/**
 * Release a previously acquired reference to the specified instance,
 * decrementing the reference count for the instance.
 *
 * The pointer to the instance is set to NULL as a side-effect of this function.
 *
 * If the invocation causes the last reference to the instance to be released,
 * the instance is deallocated and the instance's implementation will perform
 * additional cleanup and release other privately held references.
 *
 * @param [in,out] sectionP A pointer to a pointer to the instance to release.
 *
 *
 * Example:
 * @code
 * {
 *     CCNxManifestHashGroup *manifest = CCNxManifestHashGroup_Acquire(instance);
 *
 *     CCNxManifestHashGroup_Release(&manifest);
 * }
 * @endcode
 */
void ccnxManifestHashGroup_Release(CCNxManifestHashGroup **sectionP);

/**
 * Check that the pointer to the {@link CCNxManifestHashGroup} is valid. It should be non-null,
 * and any referenced data should also be valid.
 *
 * @param [in] manifest A pointer to the {@link CCNxManifestHashGroup} to check.
 *
 *
 * Example:
 * @code
 * {
 *     CCNxManifest *manifest = CCNxManifestHashGroup_Acquire(instance);
 *
 *     CCNxManifestHashGroup_AssertValid(manifest);
 * }
 * @endcode
 */
void ccnxManifestHashGroup_AssertValid(const CCNxManifestHashGroup *manifest);

////// TODO: REMOVE
/**
 * Add a new name entry to the {@link CCNxManifestHashGroup} with the specified name and hash digest.
 *
 * @param [in] section - A {@link CCNxManifestHashGroup} instance.
 * @param [in] name - The {@link CCNxName} instance to add.
 * @param [in] chunk - The chunk for the name entry.
 * @param [in] digest - The hash digest of the name entry.
 *
 * @return True if the name was added successful, False otherwise.
 *
 * Example:
 * @code
 * {
 *     CCNxName *acsName = ccnxName_CreateFromURI("lci:/foo/bar/manifest/acs");
 *     CCNxManifestHashGroup *section = CCNxManifestHashGroup_Create(acsLink);
 *
 *     CCNxName *nameEntry = ccnxName_CreateFromURI("lci:/some/content");
 *     PARCBuffer *hashDigest = ...;
 *
 *     CCNxManifestHashGroup_AddNameEntry(section, nameEntry, 0, hashDigest);
 *
 *     CCNxManifestHashGroup_Release(&section);
 * }
 * @endcode
 */
//bool ccnxManifestHashGroup_AddNameEntry(CCNxManifestHashGroup *section, const CCNxName *name, size_t chunk, const PARCBuffer *digest);

/**
 * Add a link to a `CCNxContentObject` to this `CCNxManifestHashGroup`.
 *
 * @param [in] section - A {@link CCNxManifestHashGroup} instance.
 * @param [in] name - The {@link CCNxContentObject} instance.
 *
 * @return True if the content object was added successful, False otherwise.
 *
 * Example:
 * @code
 * {
 *     CCNxContentObject *contentObject = ...;
 *
 *     CCNxManifestHashGroup_AddNameEntry(section, contentObject);
 *
 *     CCNxManifestHashGroup_Release(&section);
 * }
 * @endcode
 */
//bool ccnxManifestHashGroup_AddContentObject(CCNxManifestHashGroup *section, const CCNxContentObject *contentObject);

void ccnxManifestHashGroup_AddPointer(CCNxManifestHashGroup *group, CCNxManifestHashGroupPointerType type, const PARCBuffer *buffer);

/**
 * Determine if two {@link CCNxManifestHashGroup} instances are equal.
 *
 * The following equivalence relations on non-null {@link CCNxManifestHashGroup} instances are maintained:
 *   * It is reflexive: for any non-null reference value x, `CCNxManifestHashGroup_Equals(x, x)` must return true.
 *
 *   * It is symmetric: for any non-null reference values x and y, `CCNxManifestHashGroup_Equals(x, y)` must return true if and only if
 *        `CCNxManifestHashGroup_Equals(y x)` returns true.
 *
 *   * It is transitive: for any non-null reference values x, y, and z, if
 *        `CCNxManifestHashGroup_Equals(x, y)` returns true and
 *        `CCNxManifestHashGroup_Equals(y, z)` returns true,
 *        then  `CCNxManifestHashGroup_Equals(x, z)` must return true.
 *
 *   * It is consistent: for any non-null reference values x and y, multiple invocations of `CCNxManifestHashGroup_Equals(x, y)`
 *         consistently return true or consistently return false.
 *
 *   * For any non-null reference value x, `CCNxManifestHashGroup_Equals(x, NULL)` must return false.
 *
 *
 * @param [in] x A pointer to a {@link CCNxManifestHashGroup} instance.
 * @param [in] y A pointer to a {@link CCNxManifestHashGroup} instance.
 * @return `true` if the referenced {@link CCNxManifestHashGroup} instances are equal.
 *
 * Example:
 * @code
 * {
 *    CCNxManifestHashGroup *a = CCNxManifestHashGroup_Create(...);
 *    CCNxManifestHashGroup *b = CCNxManifestHashGroup_Create(...);
 *
 *    if (CCNxManifestHashGroup_Equals(a, b)) {
 *        // true
 *    } else {
 *        // false
 *    }
 * }
 * @endcode
 */
bool ccnxManifestHashGroup_Equals(const CCNxManifestHashGroup *x, const CCNxManifestHashGroup *y);

/**
 * Create a null-terminated string representation of the given {@link CCNxManifestHashGroup}.
 *
 * The returned value must be freed by the caller using {@link parcMemory_Deallocate()}.
 *
 * @param [in] section A pointer to a {@link CCNxManifestHashGroup} instance.
 *
 * @return A pointer to null-terminated string of characters repesenting the @p section that must be freed by the caller by `parcMemory_Deallocate()`.
 *
 * Example:
 * @code
 * {
 *     CCNxName *acsName = ...;
 *
 *     CCNxManifestHashGroup *section = CCNxManifestHashGroup_Create(acsName);
 *
 *     char *sectionDescription = CCNxManifestHashGroup_ToString(section);
 *     printf("Manifest: %s\n", sectionDescription);
 *
 *     CCNxManifestHashGroup_Release(&section);
 * }
 * @endcode
 */
char *ccnxManifestHashGroup_ToString(const CCNxManifestHashGroup *section);

/**
 * Create a `CCNxJson` representation of the given {@link CCNxManifestHashGroup}.
 *
 * The returned value must be freed by the caller using {@link ccnxJson_Destroy()}.
 *
 * @param [in] section A pointer to a {@link CCNxManifestHashGroup} instance.
 *
 * @return A pointer to the JSON representation of the @p section that must be freed by the caller by `ccnxJson_Destroy()`.
 *
 * Example:
 * @code
 * {
 *     CCNxName *acsName = ...;
 *
 *     CCNxManifestHashGroup *section = CCNxManifestHashGroup_Create(acsName);
 *
 *     CCNxJson *jsonForm = CCNxManifestHashGroup_ToJson(section);
 *     printf("Manifest: %s\n", ccnxJson_ToString(jsonForm));
 *
 *     ccnxJson_Destroy(&jsonForm);
 *     CCNxManifestHashGroup_Release(&section);
 * }
 * @endcode
 */
PARCJSON *ccnxManifestHashGroup_ToJson(const CCNxManifestHashGroup *section);

void ccnxManifestHashGroup_Release(CCNxManifestHashGroup **group);
CCNxManifestHashGroupPointer *ccnxManifestHashGroup_GetPointerAtIndex(const CCNxManifestHashGroup *group, size_t index);
PARCBuffer *ccnxManifestHashGroup_GetOverallDataDigest(const CCNxManifestHashGroup *group);
size_t ccnxManifestHashGroup_GetTotalSize(const CCNxManifestHashGroup *group);
size_t ccnxManifestHashGroup_GetChildBlockSize(const CCNxManifestHashGroup *group);
CCNxName *ccnxManifestHashGroup_GetLocator(const CCNxManifestHashGroup *group);
size_t ccnxManifestHashGroup_GetNumberOfPointers(const CCNxManifestHashGroup *group);
bool ccnxManifestHashGroup_IsFull(const CCNxManifestHashGroup *group);

PARCIterator *ccnxManifestHashGroup_Iterator(const CCNxManifestHashGroup *group);

#endif // libccnx_ccnx_ManifestHashGroup_h
