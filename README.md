# MiniNVMe kernel module for Linux

## Description
The MiniNVMe kernel module is designed for data recovery from partially faulty NVMe devices. This module has minimal functionality and replaces the standard NVMe driver. This also means your system shall to boot from the non-NVMe storage (SATA, Live-USB, etc).

## Preparation
Before using this module you have to block the loading of the standard NVMe driver. Open `/etc/default/grub` in any plain text editor and append (or edit) the line below:
```
GRUB_CMDLINE_LINUX_DEFAULT="quiet splash modprobe.blacklist=nvme"
```
Finally type `sudo update-grub` and reboot your system.

## How to build
Make sure Linux kernel headers are installed:
```
sudo apt-get install linux-headers-$(uname -r)
```
If everything above is done type in terminal:
```
git clone https://github.com/aekhv/mininvme.git
cd mininvme
make
```
As result file `mininvme.ko` will be generated.

## How to run
Just type in terminal:
```
sudo insmod mininvme.ko
```
If any NVMe device is attached you will see in `dmesg | grep mininvme` output something like this:
```
[  707.339182] mininvme: Kernel object loaded
[  707.339222] mininvme: PCI device attached: vendor 0x1e95, device 0x9100, class 0x0108, revision 0x03
[  707.339929] mininvme: Character device created: /dev/mininvme4
```
>P.S. The number at the end of the device name means the PCIe bus number. For example, `/dev/mininvme4` means the device attached to the PCIe bus number 4.
