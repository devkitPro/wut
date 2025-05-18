#pragma once

#define FIONBIO   (0x8004667E)
#define FIONREAD  (0x4004667F)
#define FIONWRITE (0x40046677)

#ifdef __cplusplus
extern "C" {
#endif

int
ioctl(int fd,
      int request,
      ...);

#ifdef __cplusplus
}
#endif
