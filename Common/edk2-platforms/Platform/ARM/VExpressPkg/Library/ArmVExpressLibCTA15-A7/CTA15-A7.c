/** @file
*
*  Copyright (c) 2012, ARM Limited. All rights reserved.
*
*  SPDX-License-Identifier: BSD-2-Clause-Patent
*
**/

#include <Library/IoLib.h>
#include <Library/ArmPlatformLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>

#include <Ppi/ArmMpCoreInfo.h>

#include <ArmPlatform.h>

ARM_CORE_INFO mVersatileExpressCTA15A7InfoTable[] = {
  {
    // Cluster 0, Core 0
    0x000,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A15_BX_ADDR0,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A15_BX_ADDR0,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A15_BX_ADDR0,
    (UINT64)0
  },
  {
    // Cluster 0, Core 1
    0x001,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A15_BX_ADDR1,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A15_BX_ADDR1,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A15_BX_ADDR1,
    (UINT64)0
  },
#ifndef ARM_BIGLITTLE_TC2
  {
    // Cluster 0, Core 2
    0x002,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A15_BX_ADDR2,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A15_BX_ADDR2,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A15_BX_ADDR2,
    (UINT64)0
  },
  {
    // Cluster 0, Core 3
    0x003,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A15_BX_ADDR3,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A15_BX_ADDR3,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A15_BX_ADDR3,
    (UINT64)0
  },
#endif
  {
    // Cluster 1, Core 0
    0x100,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A7_BX_ADDR0,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A7_BX_ADDR0,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A7_BX_ADDR0,
    (UINT64)0
  },
  {
    // Cluster 1, Core 1
    0x101,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A7_BX_ADDR1,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A7_BX_ADDR1,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A7_BX_ADDR1,
    (UINT64)0
  },
  {
    // Cluster 1, Core 2
    0x102,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A7_BX_ADDR2,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A7_BX_ADDR2,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A7_BX_ADDR2,
    (UINT64)0
  }
#ifndef ARM_BIGLITTLE_TC2
  ,{
    // Cluster 1, Core 3
    0x103,

    // MP Core MailBox Set/Get/Clear Addresses and Clear Value
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A7_BX_ADDR3,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A7_BX_ADDR3,
    (EFI_PHYSICAL_ADDRESS)ARM_CTA15A7_SPC_A7_BX_ADDR3,
    (UINT64)0
  }
#endif
};

/**
  Return the current Boot Mode

  This function returns the boot reason on the platform

  @return   Return the current Boot Mode of the platform

**/
EFI_BOOT_MODE
ArmPlatformGetBootMode (
  VOID
  )
{
  if (MmioRead32(ARM_CTA15A7_SCC_SYSINFO) & ARM_CTA15A7_SCC_SYSINFO_UEFI_RESTORE_DEFAULT_NORFLASH) {
    return BOOT_WITH_DEFAULT_SETTINGS;
  } else {
    return BOOT_WITH_FULL_CONFIGURATION;
  }
}

/**
  Initialize controllers that must setup in the normal world

  This function is called by the ArmPlatformPkg/Pei or ArmPlatformPkg/Pei/PlatformPeim
  in the PEI phase.

**/
RETURN_STATUS
ArmPlatformInitialize (
  IN  UINTN                     MpId
  )
{
  if (!ArmPlatformIsPrimaryCore (MpId)) {
    return RETURN_SUCCESS;
  }

  // Nothing to do here

  return RETURN_SUCCESS;
}

EFI_STATUS
PrePeiCoreGetMpCoreInfo (
  OUT UINTN                   *CoreCount,
  OUT ARM_CORE_INFO           **ArmCoreTable
  )
{
  // Only support one cluster
  *CoreCount    = sizeof(mVersatileExpressCTA15A7InfoTable) / sizeof(ARM_CORE_INFO);
  *ArmCoreTable = mVersatileExpressCTA15A7InfoTable;
  return EFI_SUCCESS;
}

ARM_MP_CORE_INFO_PPI mMpCoreInfoPpi = { PrePeiCoreGetMpCoreInfo };

EFI_PEI_PPI_DESCRIPTOR      gPlatformPpiTable[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_PPI,
    &gArmMpCoreInfoPpiGuid,
    &mMpCoreInfoPpi
  }
};

VOID
ArmPlatformGetPlatformPpiList (
  OUT UINTN                   *PpiListSize,
  OUT EFI_PEI_PPI_DESCRIPTOR  **PpiList
  )
{
  *PpiListSize = sizeof(gPlatformPpiTable);
  *PpiList = gPlatformPpiTable;
}
