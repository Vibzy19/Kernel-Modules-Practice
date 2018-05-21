#ifdef CHARDEV_H

#define CHARDEV_H
#define DEVICE_NAME "educateddevice"

#define MAJOR_NUMBER 100

#define IOCTL_SET_MSG _IOR(MAJOR_NUMBER, 0, char *)
#define IOCTL_GET_MSG _IOR(MAJOR_NUMBER, 1, char *)
#define IOCTL_GET_NTH_BYTE _IOWR(MAJOR_NUMBER, 2, int)

#endif
