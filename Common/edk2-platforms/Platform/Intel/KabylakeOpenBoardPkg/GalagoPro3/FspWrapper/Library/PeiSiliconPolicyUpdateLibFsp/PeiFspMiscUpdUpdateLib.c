/** @file
  Implementation of Fsp Misc UPD Initialization.

Copyright (c) 2019 - 2021, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <PiPei.h>

#include <Library/DebugLib.h>
#include <Library/PeiLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiServicesLib.h>

#include <FspEas.h>
#include <FspmUpd.h>
#include <FspsUpd.h>

#include <Library/DebugLib.h>
#include <Library/DebugPrintErrorLevelLib.h>
#include <Library/PciLib.h>
#include <Guid/MemoryOverwriteControl.h>
#include <PchAccess.h>

/**
  Performs FSP Misc UPD initialization.

  @param[in][out]  FspmUpd             Pointer to FSPM_UPD Data.

  @retval          EFI_SUCCESS         FSP UPD Data is updated.
**/
EFI_STATUS
EFIAPI
PeiFspMiscUpdUpdatePreMem (
  IN OUT FSPM_UPD    *FspmUpd
  )
{
  EFI_STATUS                        Status;
  EFI_BOOT_MODE                     BootMode;
  UINTN                             VariableSize;
  VOID                              *FspNvsBufferPtr;
  UINT8                             MorControl;
  VOID                              *MorControlPtr;

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  //
  // Initialize S3 Data variable (S3DataPtr). It may be used for warm and fast boot paths.
  //
  FspNvsBufferPtr = NULL;
  VariableSize    = 0;

  Status = PeiGetLargeVariable (L"FspNvsBuffer", &gFspNvsBufferVariableGuid, &FspNvsBufferPtr, &VariableSize);
  if (Status == EFI_SUCCESS) {
    DEBUG ((DEBUG_INFO, "Get L\"FspNvsBuffer\" gFspNvsBufferVariableGuid - %r\n", Status));
    DEBUG ((DEBUG_INFO, "FspNvsBuffer Size - 0x%x\n", VariableSize));
    FspmUpd->FspmArchUpd.NvsBufferPtr = FspNvsBufferPtr;
  }

  if (FspmUpd->FspmArchUpd.NvsBufferPtr != NULL) {
    //
    // Set the DISB bit in PCH (DRAM Initialization Scratchpad Bit - GEN_PMCON_A[23]),
    // after memory Data is saved to NVRAM.
    //
    PciOr32 ((UINTN)PCI_LIB_ADDRESS (0, PCI_DEVICE_NUMBER_PCH_PMC, PCI_FUNCTION_NUMBER_PCH_PMC, R_PCH_PMC_GEN_PMCON_A), B_PCH_PMC_GEN_PMCON_A_DISB);
  }

  //
  // MOR
  //
  MorControl = 0;
  MorControlPtr = &MorControl;
  VariableSize = sizeof (MorControl);
  Status = PeiGetVariable (
             MEMORY_OVERWRITE_REQUEST_VARIABLE_NAME,
             &gEfiMemoryOverwriteControlDataGuid,
             &MorControlPtr,
             &VariableSize
             );
  DEBUG ((DEBUG_INFO, "MorControl - 0x%x (%r)\n", MorControl, Status));
  //
  // Do not set CleanMemory on S3 resume
  // TODO: Handle advanced features later - capsule update is in-memory list
  //
  if (MOR_CLEAR_MEMORY_VALUE (MorControl) && BootMode != BOOT_ON_S3_RESUME) {
    FspmUpd->FspmConfig.CleanMemory = (BOOLEAN)(MorControl & MOR_CLEAR_MEMORY_BIT_MASK);
  }

  return EFI_SUCCESS;
}

