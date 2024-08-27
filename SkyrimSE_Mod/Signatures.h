#pragma once

namespace Signatures {
static const char *UpdateEntityPositionFunctionSignature =
    "\x40\x53\x48\x83\xEC?\x0F\x28\02";
static const int UpdateEntityPositionFunctionSignatureLength = 9;

static const char *UpdateCharacterPositionFunctionSignature =
    "\x48\x89\x5C\x24\x18\x57\x48\x83\xEC?\x8B";
static const int UpdateCharacterPositionFunctionSignatureLength = 11;

static const char *PrintToScreenFunctionSignature =
    "\x40\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x83\xEC?"
    "\x48\xC7\x44\x24\x28\xFE\xFF\xFF\xFF\x48\x89\x5C\x24\x60";
static const int PrintToScreenFunctionSignatureLength = 28;

static const char *UpdateLockpickHealthFunctionSignature =
    "\x48\x8B\xC4\x55\x56\x57\x41\x56\x41\x57\x48\x8D\x68\xA1\x48\x81\xEC????"
    "\x48\xC7\x45\xC7";
static const int UpdateLockpickHealthFunctionSignatureLength = 25;

static const char *CommunityShadersPresentFunctionSignature =
    "\x48\x89\x5C\x24\x08\x48\x89\x6C\x24\x10\x48\x89\x74\x24\x18\x57\x41\x56"
    "\x41\x57\x48\x83\xEC?\x41\x8B\xE8";
static const int CommunityShadersPresentFunctionSignatureLength = 27;

static const char *UpdateLockpickHealthInstructionSignature =
    "\xF3\x0F\x11\x0D????\xEB?\xF3\x0F\x10\x0D????\x0F";
static const int UpdateLockpickHealthInstructionSignatureLength = 19;

} // namespace Signatures