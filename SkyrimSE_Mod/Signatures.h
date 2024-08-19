#pragma once

namespace Signatures {
static const char *UpdateEntityPositionFunctionSignature =
    "\x40\x53\x48\x83\xEC?\x0F\x28\02";
static const int UpdateEntityPositionFunctionSignatureLength = 9;

static const char *UpdateCharacterPositionFunctionSignature =
    "\x48\x89\x5C\x24\x18\x57\x48\x83\xEC?\x8B";
static const int UpdateCharacterPositionFunctionSignatureLength = 11;
} // namespace Signatures