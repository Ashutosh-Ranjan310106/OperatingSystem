execve("./a.out", ["./a.out", "1.c", "1.c.backupls"], 0xfffffe47fd90 /* 12 vars */) = 0
brk(NULL)                               = 0xaaaac93b5000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xffffb49a1000
faccessat(AT_FDCWD, "/etc/ld.so.preload", R_OK) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=15118, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 15118, PROT_READ, MAP_PRIVATE, 3, 0) = 0xffffb499d000
close(3)                                = 0
openat(AT_FDCWD, "/lib/aarch64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0\267\0\1\0\0\0000y\2\0\0\0\0\0"..., 832) = 832
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=1651408, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 1826912, PROT_NONE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xffffb47a9000
mmap(0xffffb47b0000, 1761376, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0) = 0xffffb47b0000
munmap(0xffffb47a9000, 28672)           = 0
munmap(0xffffb495f000, 32864)           = 0
mprotect(0xffffb4937000, 86016, PROT_NONE) = 0
mmap(0xffffb494c000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x18c000) = 0xffffb494c000
mmap(0xffffb4952000, 49248, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0xffffb4952000
close(3)                                = 0
set_tid_address(0xffffb49a2050)         = 1462
set_robust_list(0xffffb49a2060, 24)     = 0
rseq(0xffffb49a26a0, 0x20, 0, 0xd428bc00) = 0
mprotect(0xffffb494c000, 16384, PROT_READ) = 0
mprotect(0xaaaab9b0f000, 4096, PROT_READ) = 0
mprotect(0xffffb49a6000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0xffffb499d000, 15118)           = 0
openat(AT_FDCWD, "1.c", O_RDONLY)       = 3
openat(AT_FDCWD, "1.c.backupls", O_WRONLY|O_CREAT|O_TRUNC, 0644) = 4
read(3, "#include <fcntl.h>\n#include <uni"..., 4096) = 1159
write(4, "#include <fcntl.h>\n#include <uni"..., 1159) = 1159
read(3, "", 4096)                       = 0
close(3)                                = 0
close(4)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++