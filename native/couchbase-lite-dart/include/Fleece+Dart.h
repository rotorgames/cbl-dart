#pragma once

#include "CBLDart_Export.h"
#include "dart/dart_api_dl.h"
#ifdef CBL_FRAMEWORK_HEADERS
#include <CouchbaseLite/Fleece.h>
#else
#include "fleece/Fleece.h"
#endif

// === Slice ==================================================================

CBLDART_EXPORT
void CBLDart_FLSliceResult_BindToDartObject(Dart_Handle object,
                                            FLSliceResult slice, bool retain);

CBLDART_EXPORT
void CBLDart_FLSliceResult_Retain(FLSliceResult slice);

CBLDART_EXPORT
void CBLDart_FLSliceResult_Release(FLSliceResult slice);

// === SharedKeys =============================================================

CBLDART_EXPORT
void CBLDart_FLSharedKeys_BindToDartObject(Dart_Handle object,
                                           FLSharedKeys sharedKeys,
                                           bool retain);

// === Doc ====================================================================

CBLDART_EXPORT
void CBLDart_FLDoc_BindToDartObject(Dart_Handle object, FLDoc doc);

// === Value ==================================================================

CBLDART_EXPORT
void CBLDart_FLValue_BindToDartObject(Dart_Handle object, FLValue value,
                                      bool retain);

// === Decoder ================================================================

// An object which remembers which shared keys have been seen. This is used
// to avoid decoding the same shared key multiple times.
struct KnownSharedKeys;

CBLDART_EXPORT
KnownSharedKeys *CBLDart_KnownSharedKeys_New(Dart_Handle object);

struct CBLDart_LoadedDictKey {
  bool isKnownSharedKey;  // Whether the key has been seen before. For shared
                          // keys, stringBuf and stringSize are only set the
                          // first time the key is seen.
  int sharedKey;  // The id of the shared key or -1 if the key is not shared.
  const void *stringBuf;  // The pointer to the start of the key string.
  size_t stringSize;      // The length of the key string.
  FLValue value;          // The Fleece value of the key.
};

struct CBLDart_LoadedFLValue {
  bool exists;
  int8_t type;
  bool isInteger;
  uint32_t collectionSize;
  bool asBool;
  int64_t asInt;
  double asDouble;
  const void *stringBuf;
  size_t stringSize;
  FLSlice asData;
  FLValue value;
};

CBLDART_EXPORT
void CBLDart_FLValue_FromData(FLSlice data, uint8_t trust,
                              CBLDart_LoadedFLValue *out);

CBLDART_EXPORT
void CBLDart_GetLoadedFLValue(FLValue value, CBLDart_LoadedFLValue *out);

CBLDART_EXPORT
void CBLDart_FLArray_GetLoadedFLValue(FLArray array, uint32_t index,
                                      CBLDart_LoadedFLValue *out);

CBLDART_EXPORT
void CBLDart_FLDict_GetLoadedFLValue(FLDict dict, FLString key,
                                     CBLDart_LoadedFLValue *out);

struct CBLDart_FLDictIterator;

CBLDART_EXPORT
CBLDart_FLDictIterator *CBLDart_FLDictIterator_Begin(
    Dart_Handle object, FLDict dict, KnownSharedKeys *knownSharedKeys,
    CBLDart_LoadedDictKey *keyOut, CBLDart_LoadedFLValue *valueOut,
    bool finalize, bool preLoad);

CBLDART_EXPORT
bool CBLDart_FLDictIterator_Next(CBLDart_FLDictIterator *iterator);

struct CBLDart_FLArrayIterator;

CBLDART_EXPORT
CBLDart_FLArrayIterator *CBLDart_FLArrayIterator_Begin(
    Dart_Handle object, FLArray array, CBLDart_LoadedFLValue *valueOut,
    bool finalize);

CBLDART_EXPORT
bool CBLDart_FLArrayIterator_Next(CBLDart_FLArrayIterator *iterator);

// === Encoder ================================================================

CBLDART_EXPORT
void CBLDart_FLEncoder_BindToDartObject(Dart_Handle object, FLEncoder encoder);

CBLDART_EXPORT
bool CBLDart_FLEncoder_WriteArrayValue(FLEncoder encoder, FLArray array,
                                       uint32_t index);
