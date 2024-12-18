/** @file

  @copyright
  Copyright 1999 - 2017 Intel Corporation. <BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

/* acpisrc:StructDefs -- for acpisrc conversion */

#ifndef __AMLRESRC_H
#define __AMLRESRC_H


/*
 * Resource descriptor tags, as defined in the ACPI specification.
 * Used to symbolically reference fields within a descriptor.
 */
#define ACPI_RESTAG_ADDRESS                     "_ADR"
#define ACPI_RESTAG_ALIGNMENT                   "_ALN"
#define ACPI_RESTAG_ADDRESSSPACE                "_ASI"
#define ACPI_RESTAG_ACCESSSIZE                  "_ASZ"
#define ACPI_RESTAG_TYPESPECIFICATTRIBUTES      "_ATT"
#define ACPI_RESTAG_BASEADDRESS                 "_BAS"
#define ACPI_RESTAG_BUSMASTER                   "_BM_"  /* Master(1), Slave(0) */
#define ACPI_RESTAG_DEBOUNCETIME                "_DBT"
#define ACPI_RESTAG_DECODE                      "_DEC"
#define ACPI_RESTAG_DEVICEPOLARITY              "_DPL"
#define ACPI_RESTAG_DMA                         "_DMA"
#define ACPI_RESTAG_DMATYPE                     "_TYP"  /* Compatible(0), A(1), B(2), F(3) */
#define ACPI_RESTAG_DRIVESTRENGTH               "_DRS"
#define ACPI_RESTAG_ENDIANNESS                  "_END"
#define ACPI_RESTAG_FLOWCONTROL                 "_FLC"
#define ACPI_RESTAG_GRANULARITY                 "_GRA"
#define ACPI_RESTAG_INTERRUPT                   "_INT"
#define ACPI_RESTAG_INTERRUPTLEVEL              "_LL_"  /* ActiveLo(1), ActiveHi(0) */
#define ACPI_RESTAG_INTERRUPTSHARE              "_SHR"  /* Shareable(1), NoShare(0) */
#define ACPI_RESTAG_INTERRUPTTYPE               "_HE_"  /* Edge(1), Level(0) */
#define ACPI_RESTAG_IORESTRICTION               "_IOR"
#define ACPI_RESTAG_LENGTH                      "_LEN"
#define ACPI_RESTAG_LINE                        "_LIN"
#define ACPI_RESTAG_MEMATTRIBUTES               "_MTP"  /* Memory(0), Reserved(1), ACPI(2), NVS(3) */
#define ACPI_RESTAG_MEMTYPE                     "_MEM"  /* NonCache(0), Cacheable(1) Cache+combine(2), Cache+prefetch(3) */
#define ACPI_RESTAG_MAXADDR                     "_MAX"
#define ACPI_RESTAG_MINADDR                     "_MIN"
#define ACPI_RESTAG_MAXTYPE                     "_MAF"
#define ACPI_RESTAG_MINTYPE                     "_MIF"
#define ACPI_RESTAG_MODE                        "_MOD"
#define ACPI_RESTAG_PARITY                      "_PAR"
#define ACPI_RESTAG_PHASE                       "_PHA"
#define ACPI_RESTAG_PIN                         "_PIN"
#define ACPI_RESTAG_PINCONFIG                   "_PPI"
#define ACPI_RESTAG_POLARITY                    "_POL"
#define ACPI_RESTAG_REGISTERBITOFFSET           "_RBO"
#define ACPI_RESTAG_REGISTERBITWIDTH            "_RBW"
#define ACPI_RESTAG_RANGETYPE                   "_RNG"
#define ACPI_RESTAG_READWRITETYPE               "_RW_"  /* ReadOnly(0), Writeable (1) */
#define ACPI_RESTAG_LENGTH_RX                   "_RXL"
#define ACPI_RESTAG_LENGTH_TX                   "_TXL"
#define ACPI_RESTAG_SLAVEMODE                   "_SLV"
#define ACPI_RESTAG_SPEED                       "_SPE"
#define ACPI_RESTAG_STOPBITS                    "_STB"
#define ACPI_RESTAG_TRANSLATION                 "_TRA"
#define ACPI_RESTAG_TRANSTYPE                   "_TRS"  /* Sparse(1), Dense(0) */
#define ACPI_RESTAG_TYPE                        "_TTP"  /* Translation(1), Static (0) */
#define ACPI_RESTAG_XFERTYPE                    "_SIZ"  /* 8(0), 8And16(1), 16(2) */
#define ACPI_RESTAG_VENDORDATA                  "_VEN"


/* Default sizes for "small" resource descriptors */

#define ASL_RDESC_IRQ_SIZE                      0x02
#define ASL_RDESC_DMA_SIZE                      0x02
#define ASL_RDESC_ST_DEPEND_SIZE                0x00
#define ASL_RDESC_END_DEPEND_SIZE               0x00
#define ASL_RDESC_IO_SIZE                       0x07
#define ASL_RDESC_FIXED_IO_SIZE                 0x03
#define ASL_RDESC_FIXED_DMA_SIZE                0x05
#define ASL_RDESC_END_TAG_SIZE                  0x01


typedef struct asl_resource_node
{
    UINT32                          BufferLength;
    VOID                            *Buffer;
    struct asl_resource_node        *Next;

} ASL_RESOURCE_NODE;


/* Macros used to generate AML resource length fields */

#define ACPI_AML_SIZE_LARGE(r)      (sizeof (r) - sizeof (AML_RESOURCE_LARGE_HEADER))
#define ACPI_AML_SIZE_SMALL(r)      (sizeof (r) - sizeof (AML_RESOURCE_SMALL_HEADER))

/*
 * Resource descriptors defined in the ACPI specification.
 *
 * Packing/alignment must be BYTE because these descriptors
 * are used to overlay the raw AML byte stream.
 */
#pragma pack(1)

/*
 * SMALL descriptors
 */
#define AML_RESOURCE_SMALL_HEADER_COMMON \
    UINT8                           DescriptorType;

typedef struct aml_resource_small_header
{
    AML_RESOURCE_SMALL_HEADER_COMMON

} AML_RESOURCE_SMALL_HEADER;


typedef struct aml_resource_irq
{
    AML_RESOURCE_SMALL_HEADER_COMMON
    UINT16                          IrqMask;
    UINT8                           Flags;

} AML_RESOURCE_IRQ;


typedef struct aml_resource_irq_noflags
{
    AML_RESOURCE_SMALL_HEADER_COMMON
    UINT16                          IrqMask;

} AML_RESOURCE_IRQ_NOFLAGS;


typedef struct aml_resource_dma
{
    AML_RESOURCE_SMALL_HEADER_COMMON
    UINT8                           DmaChannelMask;
    UINT8                           Flags;

} AML_RESOURCE_DMA;


typedef struct aml_resource_start_dependent
{
    AML_RESOURCE_SMALL_HEADER_COMMON
    UINT8                           Flags;

} AML_RESOURCE_START_DEPENDENT;


typedef struct aml_resource_start_dependent_noprio
{
    AML_RESOURCE_SMALL_HEADER_COMMON

} AML_RESOURCE_START_DEPENDENT_NOPRIO;


typedef struct aml_resource_end_dependent
{
    AML_RESOURCE_SMALL_HEADER_COMMON

} AML_RESOURCE_END_DEPENDENT;


typedef struct aml_resource_io
{
    AML_RESOURCE_SMALL_HEADER_COMMON
    UINT8                           Flags;
    UINT16                          Minimum;
    UINT16                          Maximum;
    UINT8                           Alignment;
    UINT8                           AddressLength;

} AML_RESOURCE_IO;


typedef struct aml_resource_fixed_io
{
    AML_RESOURCE_SMALL_HEADER_COMMON
    UINT16                          Address;
    UINT8                           AddressLength;

} AML_RESOURCE_FIXED_IO;


typedef struct aml_resource_vendor_small
{
    AML_RESOURCE_SMALL_HEADER_COMMON

} AML_RESOURCE_VENDOR_SMALL;


typedef struct aml_resource_end_tag
{
    AML_RESOURCE_SMALL_HEADER_COMMON
    UINT8                           Checksum;

} AML_RESOURCE_END_TAG;


typedef struct aml_resource_fixed_dma
{
    AML_RESOURCE_SMALL_HEADER_COMMON
    UINT16                          RequestLines;
    UINT16                          Channels;
    UINT8                           Width;

} AML_RESOURCE_FIXED_DMA;


/*
 * LARGE descriptors
 */
#define AML_RESOURCE_LARGE_HEADER_COMMON \
    UINT8                           DescriptorType;\
    UINT16                          ResourceLength;

typedef struct aml_resource_large_header
{
    AML_RESOURCE_LARGE_HEADER_COMMON

} AML_RESOURCE_LARGE_HEADER;


/* General Flags for address space resource descriptors */

#define ACPI_RESOURCE_FLAG_DEC      2
#define ACPI_RESOURCE_FLAG_MIF      4
#define ACPI_RESOURCE_FLAG_MAF      8

typedef struct aml_resource_memory24
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    UINT8                           Flags;
    UINT16                          Minimum;
    UINT16                          Maximum;
    UINT16                          Alignment;
    UINT16                          AddressLength;

} AML_RESOURCE_MEMORY24;


typedef struct aml_resource_vendor_large
{
    AML_RESOURCE_LARGE_HEADER_COMMON

} AML_RESOURCE_VENDOR_LARGE;


typedef struct aml_resource_memory32
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    UINT8                           Flags;
    UINT32                          Minimum;
    UINT32                          Maximum;
    UINT32                          Alignment;
    UINT32                          AddressLength;

} AML_RESOURCE_MEMORY32;


typedef struct aml_resource_fixed_memory32
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    UINT8                           Flags;
    UINT32                          Address;
    UINT32                          AddressLength;

} AML_RESOURCE_FIXED_MEMORY32;


#define AML_RESOURCE_ADDRESS_COMMON \
    UINT8                           ResourceType; \
    UINT8                           Flags; \
    UINT8                           SpecificFlags;


typedef struct aml_resource_address
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    AML_RESOURCE_ADDRESS_COMMON

} AML_RESOURCE_ADDRESS;


typedef struct aml_resource_extended_address64
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    AML_RESOURCE_ADDRESS_COMMON
    UINT8                           RevisionID;
    UINT8                           Reserved;
    UINT64                          Granularity;
    UINT64                          Minimum;
    UINT64                          Maximum;
    UINT64                          TranslationOffset;
    UINT64                          AddressLength;
    UINT64                          TypeSpecific;

} AML_RESOURCE_EXTENDED_ADDRESS64;

#define AML_RESOURCE_EXTENDED_ADDRESS_REVISION          1       /* ACPI 3.0 */


typedef struct aml_resource_address64
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    AML_RESOURCE_ADDRESS_COMMON
    UINT64                          Granularity;
    UINT64                          Minimum;
    UINT64                          Maximum;
    UINT64                          TranslationOffset;
    UINT64                          AddressLength;

} AML_RESOURCE_ADDRESS64;


typedef struct aml_resource_address32
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    AML_RESOURCE_ADDRESS_COMMON
    UINT32                          Granularity;
    UINT32                          Minimum;
    UINT32                          Maximum;
    UINT32                          TranslationOffset;
    UINT32                          AddressLength;

} AML_RESOURCE_ADDRESS32;


typedef struct aml_resource_address16
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    AML_RESOURCE_ADDRESS_COMMON
    UINT16                          Granularity;
    UINT16                          Minimum;
    UINT16                          Maximum;
    UINT16                          TranslationOffset;
    UINT16                          AddressLength;

} AML_RESOURCE_ADDRESS16;


typedef struct aml_resource_extended_irq
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    UINT8                           Flags;
    UINT8                           InterruptCount;
    UINT32                          Interrupts[1];
    /* ResSourceIndex, ResSource optional fields follow */

} AML_RESOURCE_EXTENDED_IRQ;


typedef struct aml_resource_generic_register
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    UINT8                           AddressSpaceId;
    UINT8                           BitWidth;
    UINT8                           BitOffset;
    UINT8                           AccessSize; /* ACPI 3.0, was previously Reserved */
    UINT64                          Address;

} AML_RESOURCE_GENERIC_REGISTER;


/* Common descriptor for GpioInt and GpioIo (ACPI 5.0) */

typedef struct aml_resource_gpio
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    UINT8                           RevisionId;
    UINT8                           ConnectionType;
    UINT16                          Flags;
    UINT16                          IntFlags;
    UINT8                           PinConfig;
    UINT16                          DriveStrength;
    UINT16                          DebounceTimeout;
    UINT16                          PinTableOffset;
    UINT8                           ResSourceIndex;
    UINT16                          ResSourceOffset;
    UINT16                          VendorOffset;
    UINT16                          VendorLength;
    /*
     * Optional fields follow immediately:
     * 1) PIN list (Words)
     * 2) Resource Source String
     * 3) Vendor Data bytes
     */

} AML_RESOURCE_GPIO;

#define AML_RESOURCE_GPIO_REVISION              1       /* ACPI 5.0 */

/* Values for ConnectionType above */

#define AML_RESOURCE_GPIO_TYPE_INT              0
#define AML_RESOURCE_GPIO_TYPE_IO               1
#define AML_RESOURCE_MAX_GPIOTYPE               1


/* Common preamble for all serial descriptors (ACPI 5.0) */

#define AML_RESOURCE_SERIAL_COMMON \
    UINT8                           RevisionId; \
    UINT8                           ResSourceIndex; \
    UINT8                           Type; \
    UINT8                           Flags; \
    UINT16                          TypeSpecificFlags; \
    UINT8                           TypeRevisionId; \
    UINT16                          TypeDataLength; \

/* Values for the type field above */

#define AML_RESOURCE_I2C_SERIALBUSTYPE          1
#define AML_RESOURCE_SPI_SERIALBUSTYPE          2
#define AML_RESOURCE_UART_SERIALBUSTYPE         3
#define AML_RESOURCE_MAX_SERIALBUSTYPE          3
#define AML_RESOURCE_VENDOR_SERIALBUSTYPE       192 /* Vendor defined is 0xC0-0xFF (NOT SUPPORTED) */

typedef struct aml_resource_common_serialbus
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    AML_RESOURCE_SERIAL_COMMON

} AML_RESOURCE_COMMON_SERIALBUS;

typedef struct aml_resource_i2c_serialbus
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    AML_RESOURCE_SERIAL_COMMON
    UINT32                          ConnectionSpeed;
    UINT16                          SlaveAddress;
    /*
     * Optional fields follow immediately:
     * 1) Vendor Data bytes
     * 2) Resource Source String
     */

} AML_RESOURCE_I2C_SERIALBUS;

#define AML_RESOURCE_I2C_REVISION               1       /* ACPI 5.0 */
#define AML_RESOURCE_I2C_TYPE_REVISION          1       /* ACPI 5.0 */
#define AML_RESOURCE_I2C_MIN_DATA_LEN           6

typedef struct aml_resource_spi_serialbus
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    AML_RESOURCE_SERIAL_COMMON
    UINT32                          ConnectionSpeed;
    UINT8                           DataBitLength;
    UINT8                           ClockPhase;
    UINT8                           ClockPolarity;
    UINT16                          DeviceSelection;
    /*
     * Optional fields follow immediately:
     * 1) Vendor Data bytes
     * 2) Resource Source String
     */

} AML_RESOURCE_SPI_SERIALBUS;

#define AML_RESOURCE_SPI_REVISION               1       /* ACPI 5.0 */
#define AML_RESOURCE_SPI_TYPE_REVISION          1       /* ACPI 5.0 */
#define AML_RESOURCE_SPI_MIN_DATA_LEN           9


typedef struct aml_resource_uart_serialbus
{
    AML_RESOURCE_LARGE_HEADER_COMMON
    AML_RESOURCE_SERIAL_COMMON
    UINT32                          DefaultBaudRate;
    UINT16                          RxFifoSize;
    UINT16                          TxFifoSize;
    UINT8                           Parity;
    UINT8                           LinesEnabled;
    /*
     * Optional fields follow immediately:
     * 1) Vendor Data bytes
     * 2) Resource Source String
     */

} AML_RESOURCE_UART_SERIALBUS;

#define AML_RESOURCE_UART_REVISION              1       /* ACPI 5.0 */
#define AML_RESOURCE_UART_TYPE_REVISION         1       /* ACPI 5.0 */
#define AML_RESOURCE_UART_MIN_DATA_LEN          10


/* restore default alignment */

#pragma pack()

/* Union of all resource descriptors, so we can allocate the worst case */

typedef union aml_resource
{
    /* Descriptor headers */

    UINT8                                   DescriptorType;
    AML_RESOURCE_SMALL_HEADER               SmallHeader;
    AML_RESOURCE_LARGE_HEADER               LargeHeader;

    /* Small resource descriptors */

    AML_RESOURCE_IRQ                        Irq;
    AML_RESOURCE_DMA                        Dma;
    AML_RESOURCE_START_DEPENDENT            StartDpf;
    AML_RESOURCE_END_DEPENDENT              EndDpf;
    AML_RESOURCE_IO                         Io;
    AML_RESOURCE_FIXED_IO                   FixedIo;
    AML_RESOURCE_FIXED_DMA                  FixedDma;
    AML_RESOURCE_VENDOR_SMALL               VendorSmall;
    AML_RESOURCE_END_TAG                    EndTag;

    /* Large resource descriptors */

    AML_RESOURCE_MEMORY24                   Memory24;
    AML_RESOURCE_GENERIC_REGISTER           GenericReg;
    AML_RESOURCE_VENDOR_LARGE               VendorLarge;
    AML_RESOURCE_MEMORY32                   Memory32;
    AML_RESOURCE_FIXED_MEMORY32             FixedMemory32;
    AML_RESOURCE_ADDRESS16                  Address16;
    AML_RESOURCE_ADDRESS32                  Address32;
    AML_RESOURCE_ADDRESS64                  Address64;
    AML_RESOURCE_EXTENDED_ADDRESS64         ExtAddress64;
    AML_RESOURCE_EXTENDED_IRQ               ExtendedIrq;
    AML_RESOURCE_GPIO                       Gpio;
    AML_RESOURCE_I2C_SERIALBUS              I2cSerialBus;
    AML_RESOURCE_SPI_SERIALBUS              SpiSerialBus;
    AML_RESOURCE_UART_SERIALBUS             UartSerialBus;
    AML_RESOURCE_COMMON_SERIALBUS           CommonSerialBus;

    /* Utility overlays */

    AML_RESOURCE_ADDRESS                    Address;
    UINT32                                  DwordItem;
    UINT16                                  WordItem;
    UINT8                                   ByteItem;

} AML_RESOURCE;

#endif
