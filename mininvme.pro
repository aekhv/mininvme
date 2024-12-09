TEMPLATE = lib

CONFIG -= qt

DEFINES += \
    __KERNEL__ \
    KBUILD_MODNAME=\"\\\"\\\"\"

SOURCES += \
        ioctl.c \
        main.c \
        nvme.c

OTHER_FILES += \
    Makefile

KERNEL_RELEASE = $$system(uname -r)

INCLUDEPATH += \
    /usr/lib/modules/$${KERNEL_RELEASE}/build/include \
    /usr/lib/modules/$${KERNEL_RELEASE}/build/arch/x86/include

HEADERS += \
    driver.h \
    ioctl.h \
    nvme.h
