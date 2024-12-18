/** @file
*  PCI Host Bridge Library instance for ARM Neoverse N1 platform
*
*  Copyright (c) 2019 - 2022, ARM Limited. All rights reserved.<BR>
*
*  SPDX-License-Identifier: BSD-2-Clause-Patent
*
**/

#include <PiDxe.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/PciHostBridgeLib.h>
#include <Protocol/PciHostBridgeResourceAllocation.h>
#include <Protocol/PciRootBridgeIo.h>

#define ROOT_COMPLEX_NUM 2

GLOBAL_REMOVE_IF_UNREFERENCED
STATIC CHAR16 CONST * CONST mPciHostBridgeLibAcpiAddressSpaceTypeStr[] = {
  L"Mem", L"I/O", L"Bus"
};

#pragma pack (1)
typedef struct {
  ACPI_HID_DEVICE_PATH     AcpiDevicePath;
  EFI_DEVICE_PATH_PROTOCOL EndDevicePath;
} EFI_PCI_ROOT_BRIDGE_DEVICE_PATH;
#pragma pack ()

STATIC EFI_PCI_ROOT_BRIDGE_DEVICE_PATH mEfiPciRootBridgeDevicePath[ROOT_COMPLEX_NUM] = {
  // PCIe
  {
    {
      {
        ACPI_DEVICE_PATH,
        ACPI_DP,
        {
          (UINT8)sizeof (ACPI_HID_DEVICE_PATH),
          (UINT8)(sizeof (ACPI_HID_DEVICE_PATH) >> 8)
        }
      },
      EISA_PNP_ID (0x0A08), // PCIe
      0
    },
    {
      END_DEVICE_PATH_TYPE,
      END_ENTIRE_DEVICE_PATH_SUBTYPE,
      {
        END_DEVICE_PATH_LENGTH,
        0
      }
    }
  },
  //CCIX
  {
    {
      {
        ACPI_DEVICE_PATH,
        ACPI_DP,
        {
          (UINT8)sizeof (ACPI_HID_DEVICE_PATH),
          (UINT8)(sizeof (ACPI_HID_DEVICE_PATH) >> 8)
        }
      },
      EISA_PNP_ID(0x0A08), // CCIX
      1
    },
    {
      END_DEVICE_PATH_TYPE,
      END_ENTIRE_DEVICE_PATH_SUBTYPE,
      {
        END_DEVICE_PATH_LENGTH,
        0
      }
    }
  },
};

STATIC PCI_ROOT_BRIDGE mPciRootBridge[ROOT_COMPLEX_NUM] = {
  {
    0,                                              // Segment
    0,                                              // Supports
    0,                                              // Attributes
    TRUE,                                           // DmaAbove4G
    FALSE,                                          // NoExtendedConfigSpace
    FALSE,                                          // ResourceAssigned
    EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM |          // AllocationAttributes
    EFI_PCI_HOST_BRIDGE_MEM64_DECODE,
    {
      // Bus
      FixedPcdGet32 (PcdPcieBusMin),
      FixedPcdGet32 (PcdPcieBusMax)
    }, {
      // Io
      FixedPcdGet64 (PcdPcieIoBase),
      FixedPcdGet64 (PcdPcieIoBase) + FixedPcdGet64 (PcdPcieIoSize) - 1
    }, {
      // Mem
      FixedPcdGet32 (PcdPcieMmio32Base),
      FixedPcdGet32 (PcdPcieMmio32Base) + FixedPcdGet32 (PcdPcieMmio32Size) - 1
    }, {
      // MemAbove4G
      FixedPcdGet64 (PcdPcieMmio64Base),
      FixedPcdGet64 (PcdPcieMmio64Base) + FixedPcdGet64 (PcdPcieMmio64Size) - 1
    }, {
      // PMem
      MAX_UINT64,
      0
    }, {
      // PMemAbove4G
      MAX_UINT64,
      0
    },
    (EFI_DEVICE_PATH_PROTOCOL *)&mEfiPciRootBridgeDevicePath[0]
  },
  {
    1,                                              // Segment
    0,                                              // Supports
    0,                                              // Attributes
    TRUE,                                           // DmaAbove4G
    FALSE,                                          // NoExtendedConfigSpace
    FALSE,                                          // ResourceAssigned
    EFI_PCI_HOST_BRIDGE_COMBINE_MEM_PMEM |          // AllocationAttributes
    EFI_PCI_HOST_BRIDGE_MEM64_DECODE,
    {
      // Bus
      FixedPcdGet32 (PcdCcixBusMin),
      FixedPcdGet32 (PcdCcixBusMax)
    }, {
      // Io
      FixedPcdGet64 (PcdCcixIoBase),
      FixedPcdGet64 (PcdCcixIoBase) + FixedPcdGet64 (PcdCcixIoSize) - 1
    }, {
      // Mem
      FixedPcdGet32 (PcdCcixMmio32Base),
      FixedPcdGet32 (PcdCcixMmio32Base) + FixedPcdGet32 (PcdCcixMmio32Size) - 1
    }, {
      // MemAbove4G
      FixedPcdGet64 (PcdCcixMmio64Base),
      FixedPcdGet64 (PcdCcixMmio64Base) + FixedPcdGet64 (PcdCcixMmio64Size) - 1
    }, {
      // PMem
      MAX_UINT64,
      0
    }, {
      // PMemAbove4G
      MAX_UINT64,
      0
    },
    (EFI_DEVICE_PATH_PROTOCOL *)&mEfiPciRootBridgeDevicePath[1]
  },
};

/**
  Return all the root bridge instances in an array.

  @param Count  Return the count of root bridge instances.

  @return All the root bridge instances in an array.
          The array should be passed into PciHostBridgeFreeRootBridges()
          when it's not used.
**/
PCI_ROOT_BRIDGE *
EFIAPI
PciHostBridgeGetRootBridges (
  UINTN                             *Count
  )
{
  *Count = ARRAY_SIZE (mPciRootBridge);
  return mPciRootBridge;
}

/**
  Free the root bridge instances array returned from PciHostBridgeGetRootBridges().

  @param Bridges The root bridge instances array.
  @param Count   The count of the array.
**/
VOID
EFIAPI
PciHostBridgeFreeRootBridges (
  PCI_ROOT_BRIDGE                   *Bridges,
  UINTN                             Count
  )
{
}

/**
  Inform the platform that the resource conflict happens.

  @param HostBridgeHandle Handle of the Host Bridge.
  @param Configuration    Pointer to PCI I/O and PCI memory resource
                          descriptors. The Configuration contains the resources
                          for all the root bridges. The resource for each root
                          bridge is terminated with END descriptor and an
                          additional END is appended indicating the end of the
                          entire resources. The resource descriptor field
                          values follow the description in
                          EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL.\
                          SubmitResources().
**/
VOID
EFIAPI
PciHostBridgeResourceConflict (
  EFI_HANDLE                        HostBridgeHandle,
  VOID                              *Configuration
  )
{
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *Descriptor;

  DEBUG ((DEBUG_ERROR, "PciHostBridge: Resource conflict happened!\n"));
  Descriptor = (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *) Configuration;

  while (Descriptor->Desc == ACPI_ADDRESS_SPACE_DESCRIPTOR) {
    for (; Descriptor->Desc == ACPI_ADDRESS_SPACE_DESCRIPTOR; Descriptor++) {
      ASSERT (Descriptor->ResType <
              (sizeof (mPciHostBridgeLibAcpiAddressSpaceTypeStr) /
               sizeof (mPciHostBridgeLibAcpiAddressSpaceTypeStr[0])
               )
              );
      DEBUG ((DEBUG_ERROR, " %s: Length/Alignment = 0x%lx / 0x%lx\n",
              mPciHostBridgeLibAcpiAddressSpaceTypeStr[Descriptor->ResType],
              Descriptor->AddrLen, Descriptor->AddrRangeMax
              ));
      if (Descriptor->ResType == ACPI_ADDRESS_SPACE_TYPE_MEM) {
        DEBUG ((DEBUG_ERROR, "     Granularity/SpecificFlag = %ld / %02x%s\n",
                Descriptor->AddrSpaceGranularity, Descriptor->SpecificFlag,
                ((Descriptor->SpecificFlag &
                  EFI_ACPI_MEMORY_RESOURCE_SPECIFIC_FLAG_CACHEABLE_PREFETCHABLE
                  ) != 0) ? L" (Prefetchable)" : L""
                ));
      }
    }
    //
    // Skip the END descriptor for root bridge
    //
    ASSERT (Descriptor->Desc == ACPI_END_TAG_DESCRIPTOR);
    Descriptor = (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *)(
                   (EFI_ACPI_END_TAG_DESCRIPTOR *)Descriptor + 1
                   );
  }
}
