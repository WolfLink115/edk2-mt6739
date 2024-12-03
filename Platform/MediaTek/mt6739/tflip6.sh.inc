function platform_build_bootimg(){
		gzip -f "${WORKSPACE}/uefi-${DEVICE}-kernel"
        python3 "${ROOTDIR}/tools/mkbootimg.py" \
                --tags_offset 0x04000000 \
                --second_offset 0xc0000000 \
                --ramdisk_offset 0x05000000 \
                --pagesize 2048 \
                --kernel_offset 0x00008000 \
                --header_version 2  \
                --dtb_offset 0x04808000 \
                --cmdline "bootopt=64S3,32S1,32S1" \
                --base 0x40000000 \
                --ramdisk "Platform/MediaTek/mt6739/dummyramdisk" \
                --dtb "Platform/MediaTek/mt6739/FdtBlob_compat/${DEVICE}.dtb" \
                --kernel "${WORKSPACE}/uefi-${DEVICE}-kernel.gz" \
                -o "${WORKSPACE}/boot.img" \
                ||return "$?"
}
