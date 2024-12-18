/** @file
  Slot Table Update.

  @copyright
  Copyright 2018 - 2021 Intel Corporation. <BR>
  Copyright (c) 2021 - 2022, American Megatrends International LLC. <BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include "PeiBoardInit.h"
#include <Library/UbaSlotUpdateLib.h>
#include <IioPlatformData.h>

#define PCI_DEVICE_ON_BOARD_TRUE   0
#define PCI_DEVICE_ON_BOARD_FALSE  1

typedef enum {
  Iio_Socket0 = 0,
  Iio_Socket1,
  Iio_Socket2,
  Iio_Socket3,
  Iio_Socket4,
  Iio_Socket5,
  Iio_Socket6,
  Iio_Socket7
} IIO_SOCKETS;

typedef enum {
  Iio_Iou0 = 0,
  Iio_Iou1,
  Iio_Iou2,
  Iio_Iou3,
  Iio_Iou4,
  Iio_IouMax
} IIO_IOUS;

typedef enum {
  Bw5_Addr_0 = 0,
  Bw5_Addr_1,
  Bw5_Addr_2,
  Bw5_Addr_3,
  Bw5_Addr_Max
} BW5_ADDRESS;

static UINT8  TypeAowandaPchPciSlotImpementedTableData[] = {
  PCI_DEVICE_ON_BOARD_TRUE,     // Root Port 0 I210
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 1
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 2
  PCI_DEVICE_ON_BOARD_TRUE,     // Root Port 3 BMC Video
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 4
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 5
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 6
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 7
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 8
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 9
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 10
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 11
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 12
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 13
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 14
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 15
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 16
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 17
  PCI_DEVICE_ON_BOARD_FALSE,    // Root Port 18
  PCI_DEVICE_ON_BOARD_FALSE     // Root Port 19
};

UINT8
GetTypeAowandaIOU0Setting (
  UINT8  IOU0Data
  )
{
  return IOU0Data;
}

UINT8
GetTypeAowandaIOU2Setting (
  UINT8  SkuPersonalityType,
  UINT8  IOU2Data
  )
{
  return IOU2Data;
}

static IIO_BROADWAY_ADDRESS_DATA_ENTRY  SlotTypeAowandaBroadwayTable[] = {
  { Iio_Socket0, Iio_Iou2, Bw5_Addr_0 },
  { Iio_Socket1, Iio_Iou1, Bw5_Addr_2 },
  { Iio_Socket1, Iio_Iou0, Bw5_Addr_1 },
};

PLATFORM_SLOT_UPDATE_TABLE  TypeAowandaSlotTable =
{
  PLATFORM_SLOT_UPDATE_SIGNATURE,
  PLATFORM_SLOT_UPDATE_VERSION,

  SlotTypeAowandaBroadwayTable,
  GetTypeAowandaIOU0Setting,
  0
};

PLATFORM_SLOT_UPDATE_TABLE2  TypeAowandaSlotTable2 =
{
  PLATFORM_SLOT_UPDATE_SIGNATURE,
  PLATFORM_SLOT_UPDATE_VERSION,

  SlotTypeAowandaBroadwayTable,
  GetTypeAowandaIOU0Setting,
  0,
  GetTypeAowandaIOU2Setting
};

PLATFORM_PCH_PCI_SLOT_IMPLEMENTED_UPDATE_TABLE  TypeAowandaPchPciSlotImplementedTable = {
  PLATFORM_SLOT_UPDATE_SIGNATURE,
  PLATFORM_SLOT_UPDATE_VERSION,

  TypeAowandaPchPciSlotImpementedTableData
};

/**
  Entry point function for the PEIM

  @param FileHandle      Handle of the file being invoked.
  @param PeiServices     Describes the list of possible PEI Services.

  @return EFI_SUCCESS    If we installed our PPI

**/
EFI_STATUS
TypeAowandaInstallSlotTableData (
  IN UBA_CONFIG_DATABASE_PPI  *UbaConfigPpi
  )
{
  EFI_STATUS  Status;

  Status = UbaConfigPpi->AddData (
                                  UbaConfigPpi,
                                  &gPlatformSlotDataGuid,
                                  &TypeAowandaSlotTable,
                                  sizeof (TypeAowandaSlotTable)
                                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = UbaConfigPpi->AddData (
                                  UbaConfigPpi,
                                  &gPlatformSlotDataGuid2,
                                  &TypeAowandaSlotTable2,
                                  sizeof (TypeAowandaSlotTable2)
                                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = UbaConfigPpi->AddData (
                                  UbaConfigPpi,
                                  &gPlatformPciSlotImplementedGuid,
                                  &TypeAowandaPchPciSlotImplementedTable,
                                  sizeof (TypeAowandaPchPciSlotImplementedTable)
                                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  return Status;
}
