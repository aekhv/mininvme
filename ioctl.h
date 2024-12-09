/****************************************************************************
**
** This file is part of the MiniNVMe project.
** Copyright (C) 2024 Alexander E. <aekhv@vk.com>
** License: GNU LGPL v2, see file LICENSE.
**
****************************************************************************/

#ifndef IOCTL_H
#define IOCTL_H

#include <linux/kernel.h>
#include <linux/ioctl.h>

typedef struct {
    uint32_t major;
    uint32_t minor;
    uint32_t patch;
} nvme_driver_version_t;

typedef struct {
    uint8_t domain;     // Domain
    uint8_t bus;        // Bus
    uint8_t slot;       // Slot
    uint8_t func;       // Function
} nvme_pci_device_location_t;

typedef struct {
    uint16_t vendorId;  // Vendor ID
    uint16_t deviceId;  // Device ID
    uint16_t classId;   // Class ID
    uint8_t revision;   // Revision
} nvme_pci_device_id_t;

typedef struct {
    uint8_t speed;      // Bus speed (Gen.1, Gen.2, etc.)
    uint8_t width;      // Bus width (1x, 2x, 4x, etc.)
} nvme_pci_device_link_t;

typedef struct {
    nvme_pci_device_location_t location;
    nvme_pci_device_id_t id;
    nvme_pci_device_link_t link;
} nvme_pci_device_info_t;

typedef struct {
    uint8_t major;
    uint8_t minor;
    uint8_t tertiary;
} nvme_controller_version_t;

typedef struct {
    bool enabled;
    bool ready;
    bool fatal;
} nvme_controller_state_t;

typedef struct {
    uint8_t opc;        // Opcode
    uint32_t nsid;      // Namespace Identifier
    uint32_t cdw10;     // Command dwords 10...15
    uint32_t cdw11;
    uint32_t cdw12;
    uint32_t cdw13;
    uint32_t cdw14;
    uint32_t cdw15;
} nvme_command_t;

typedef struct {
    uint8_t *pointer;   // Buffer pointer
    uint32_t length;    // Buffer length
} nvme_buffer_t;

typedef struct {
    uint8_t sct;        // Status code type
    uint8_t sc;         // Status code
    bool more;          // More bit
    bool dnr;           // Do not retry bit
    bool timeout;       // Timeout bit
} nvme_status_t;

typedef struct {
    nvme_command_t cmd;
    nvme_buffer_t buffer;
    nvme_status_t status;
} nvme_command_packet_t;

typedef struct {
    uint64_t offset;    // LBA offset
    uint32_t count;     // LBA count
} nvme_lba_t;

typedef struct {
    uint32_t nsid;      // Namespace Identifier
    nvme_lba_t lba;
    nvme_buffer_t buffer;
    nvme_status_t status;
} nvme_lba_packet_t;

enum _NVME_IOCTL {
    _NVME_IOCTL_GET_DRIVER_VERSION = 0x80,
    _NVME_IOCTL_GET_PCI_DEVICE_INFO,
    _NVME_IOCTL_GET_CONTROLLER_VERSION,
    _NVME_IOCTL_GET_CONTROLLER_STATE,
    _NVME_IOCTL_RUN_ADMIN_COMMAND,
    _NVME_IOCTL_RUN_IO_COMMAND,
    _NVME_IOCTL_READ_SECTORS,
    _NVME_IOCTL_WRITE_SECTORS,
    _NVME_IOCTL_CONTROLLER_RESET
};

#define NVME_IOCTL_BASE '#'

#define NVME_IOCTL_GET_DRIVER_VERSION       _IOR(NVME_IOCTL_BASE, _NVME_IOCTL_GET_DRIVER_VERSION, nvme_driver_version_t)
#define NVME_IOCTL_GET_PCI_DEVICE_INFO      _IOR(NVME_IOCTL_BASE, _NVME_IOCTL_GET_PCI_DEVICE_INFO, nvme_pci_device_info_t)
#define NVME_IOCTL_GET_CONTROLLER_VERSION   _IOR(NVME_IOCTL_BASE, _NVME_IOCTL_GET_CONTROLLER_VERSION, nvme_controller_version_t)
#define NVME_IOCTL_GET_CONTROLLER_STATE     _IOR(NVME_IOCTL_BASE, _NVME_IOCTL_GET_CONTROLLER_STATE, nvme_controller_state_t)
#define NVME_IOCTL_RUN_ADMIN_COMMAND        _IOWR(NVME_IOCTL_BASE, _NVME_IOCTL_RUN_ADMIN_COMMAND, nvme_command_packet_t)
#define NVME_IOCTL_RUN_IO_COMMAND           _IOWR(NVME_IOCTL_BASE, _NVME_IOCTL_RUN_IO_COMMAND, nvme_command_packet_t)
#define NVME_IOCTL_READ_SECTORS             _IOWR(NVME_IOCTL_BASE, _NVME_IOCTL_READ_SECTORS, nvme_lba_packet_t)
#define NVME_IOCTL_WRITE_SECTORS            _IOWR(NVME_IOCTL_BASE, _NVME_IOCTL_WRITE_SECTORS, nvme_lba_packet_t)
#define NVME_IOCTL_CONTROLLER_RESET         _IO(NVME_IOCTL_BASE, _NVME_IOCTL_CONTROLLER_RESET)

#endif // IOCTL_H
