## @file
# This package provides PostCode Debug feature.
# This package should only depend on EDK II Core packages, IntelSiliconPkg, and MinPlatformPkg.
#
# The DEC files are used by the utilities that parse DSC and
# INF files to generate AutoGen.c and AutoGen.h files
# for the build infrastructure.
#
# Copyright (c) 2020, Intel Corporation. All rights reserved.<BR>
#
# SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

[Defines]
  PLATFORM_NAME                  = PostCodeFeaturePkg
  PLATFORM_GUID                  = 4ADE0B1A-7929-495D-A221-6576C7884CAC
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/$(PLATFORM_NAME)
  SUPPORTED_ARCHITECTURES        = IA32|X64
  BUILD_TARGETS                  = DEBUG|RELEASE|NOOPT
  SKUID_IDENTIFIER               = DEFAULT
  PEI_ARCH                       = IA32
  DXE_ARCH                       = X64

[Packages]
  MinPlatformPkg/MinPlatformPkg.dec

[PcdsDynamicExDefault]
  #
  # PCD needed for this feature to build
  #
  gPostCodeDebugFeaturePkgTokenSpaceGuid.PcdStatusCodeUsePostCode|TRUE

#
# MinPlatform common include for required feature PCD
# These PCD must be set before the core include files, CoreCommonLib,
# CorePeiLib, and CoreDxeLib.
#
!include MinPlatformPkg/Include/Dsc/MinPlatformFeaturesPcd.dsc.inc

#
# Include common libraries
#
!include MinPlatformPkg/Include/Dsc/CoreCommonLib.dsc
!include MinPlatformPkg/Include/Dsc/CorePeiLib.dsc
!include MinPlatformPkg/Include/Dsc/CoreDxeLib.dsc

[LibraryClasses.Common]
  #
  # Required by common status code handler infrastructure
  #
  PlatformHookLib|MdeModulePkg/Library/BasePlatformHookLibNull/BasePlatformHookLibNull.inf

#
# This package always builds the feature.
#
!include Include/PostCodeDebugFeature.dsc
