/** @file

  @copyright
  Copyright 2016 - 2021 Intel Corporation. <BR>
  Copyright (c) 2021 - 2022, American Megatrends International LLC. <BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#ifndef _IIOCFG_UPDATE_DXE_H_
#define _IIOCFG_UPDATE_DXE_H_

#include <Base.h>
#include <Uefi.h>
#include <Protocol/UbaCfgDb.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PciLib.h>
#include <Library/UbaIioConfigLib.h>
#include <IioPlatformData.h>

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
  Iio_Mcp0,
  Iio_Mcp1,
  Iio_IouMax
} IIO_IOUS;

typedef enum {
  VPP_PORT_0 = 0,
  VPP_PORT_1,
  VPP_PORT_2,
  VPP_PORT_3
} VPP_PORT;

#define ENABLE        1
#define DISABLE       0
#define NO_SLT_IMP    0xFF
#define SLT_IMP       1
#define HIDE          1
#define NOT_HIDE      0
#define VPP_PORT_0    0
#define VPP_PORT_1    1
#define VPP_PORT_MAX  0xFF
#define VPP_ADDR_MAX  0xFF
#define PWR_VAL_MAX   0xFF
#define PWR_SCL_MAX   0xFF

static IIO_BIFURCATION_DATA_ENTRY  IioBifurcationTable[] =
{
  { Iio_Socket0, Iio_Iou0, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket0, Iio_Iou1, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket0, Iio_Iou2, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket0, Iio_Mcp0, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket0, Iio_Mcp1, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket1, Iio_Iou0, IIO_BIFURCATE_xxx8xxx8 },
  { Iio_Socket1, Iio_Iou1, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket1, Iio_Iou2, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket1, Iio_Mcp0, IIO_BIFURCATE_xxxxxx16 },
  { Iio_Socket1, Iio_Mcp1, IIO_BIFURCATE_xxxxxx16 },
};

static IIO_SLOT_CONFIG_DATA_ENTRY   IioSlotTable[] = {
  // Port        |  Slot      | Inter      | Power Limit | Power Limit | Hot     | Vpp          | Vpp          | PcieSSD | PcieSSD     | PcieSSD       | Hidden
  // Index       |            | lock       | Scale       |  Value      | Plug    | Port         | Addr         | Cap     | VppPort     | VppAddr       |
  { PORT_1A_INDEX, 1          , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_0  , 0x4C           , NOT_HIDE},
  { PORT_2A_INDEX, 7          , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , DISABLE , VPP_PORT_MAX, VPP_ADDR_MAX  , NOT_HIDE},
  { PORT_3A_INDEX, 2          , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , ENABLE  , VPP_PORT_0   , 0x40         , ENABLE  , VPP_PORT_0  , 0x40         , NOT_HIDE},
  { SOCKET_1_INDEX +
    PORT_0_INDEX , NO_SLT_IMP , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , DISABLE , VPP_PORT_MAX, VPP_ADDR_MAX  , HIDE    },
  // Slot 4 supports HP: PCA9554 (CPU1) Address 0x40, SCH (Rev 0.604) P 121 (MRL in J287)
  { SOCKET_1_INDEX +
    PORT_1A_INDEX, 4          , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , ENABLE  , VPP_PORT_1   , 0x40         , ENABLE  , VPP_PORT_0  , 0x40         , NOT_HIDE},
  { SOCKET_1_INDEX +
    PORT_1C_INDEX, 3          , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , ENABLE  , VPP_PORT_0  , 0x42         , NOT_HIDE},
  { SOCKET_1_INDEX +
    PORT_2A_INDEX, 6          , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_1   , VPP_ADDR_MAX , ENABLE  , VPP_PORT_0  , 0x44         , NOT_HIDE},
  { SOCKET_1_INDEX +
    PORT_3A_INDEX, 5          , DISABLE    , PWR_SCL_MAX , PWR_VAL_MAX , DISABLE , VPP_PORT_MAX , VPP_ADDR_MAX , DISABLE , VPP_PORT_MAX, VPP_ADDR_MAX  , NOT_HIDE},
};

#endif //_IIOCFG_UPDATE_DXE_H_
