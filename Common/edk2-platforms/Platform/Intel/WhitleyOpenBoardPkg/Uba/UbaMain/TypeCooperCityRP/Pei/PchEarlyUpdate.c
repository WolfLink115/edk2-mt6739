/** @file
  Pch Early update.

  @copyright
  Copyright 2014 - 2021 Intel Corporation. <BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include "PeiBoardInit.h"

#include <Library/UbaPchEarlyUpdateLib.h>

#include <PchAccess.h>
#include <GpioPinsSklH.h>
#include <Library/GpioLib.h>
#include <Ppi/DynamicSiLibraryPpi.h>

EFI_STATUS
TypeCooperCityRPPchLanConfig (
  IN SYSTEM_CONFIGURATION         *SystemConfig
)
{
  DYNAMIC_SI_LIBARY_PPI  *DynamicSiLibraryPpi = NULL;
  EFI_STATUS              Status;

  Status = PeiServicesLocatePpi (&gDynamicSiLibraryPpiGuid, 0, NULL, (VOID **) &DynamicSiLibraryPpi);
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return Status;
  }

  DynamicSiLibraryPpi->PchDisableGbe ();

  return EFI_SUCCESS;
}

EFI_STATUS
TypeCooperCityRPOemInitLateHook (
  IN SYSTEM_CONFIGURATION         *SystemConfig
)
{
  return EFI_SUCCESS;
}


PLATFORM_PCH_EARLY_UPDATE_TABLE  TypeCooperCityRPPchEarlyUpdateTable =
{
  PLATFORM_PCH_EARLY_UPDATE_SIGNATURE,
  PLATFORM_PCH_EARLY_UPDATE_VERSION,
  TypeCooperCityRPPchLanConfig,
  TypeCooperCityRPOemInitLateHook
};


/**
  Entry point function for the PEIM

  @param FileHandle      Handle of the file being invoked.
  @param PeiServices     Describes the list of possible PEI Services.

  @return EFI_SUCCESS    If we installed our PPI

**/
EFI_STATUS
EFIAPI
TypeCooperCityRPPchEarlyUpdate(
  IN UBA_CONFIG_DATABASE_PPI    *UbaConfigPpi
  )
{
  EFI_STATUS                            Status;

  Status = UbaConfigPpi->AddData (
                               UbaConfigPpi,
                               &gPlatformPchEarlyConfigDataGuid,
                               &TypeCooperCityRPPchEarlyUpdateTable,
                               sizeof(TypeCooperCityRPPchEarlyUpdateTable)
                               );

  return Status;
}
