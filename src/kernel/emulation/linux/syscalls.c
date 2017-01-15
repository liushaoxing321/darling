#include "syscalls.h"

#include "unistd/write.h"
#include "unistd/read.h"
#include "mman/mman.h"
#include "mman/madvise.h"
#include "unistd/sync.h"
#include "unistd/fsync.h"
#include "unistd/fdatasync.h"
#include "unistd/dup.h"
#include "unistd/dup2.h"
#include "unistd/exit.h"
#include "unistd/close.h"
#include "unistd/fchdir.h"
#include "unistd/fchown.h"
#include "unistd/fchmod.h"
#include "unistd/setgid.h"
#include "unistd/setegid.h"
#include "unistd/seteuid.h"
#include "unistd/setsid.h"
#include "unistd/setuid.h"
#include "unistd/getuid.h"
#include "unistd/geteuid.h"
#include "unistd/pread.h"
#include "unistd/pwrite.h"
#include "unistd/getpid.h"
#include "unistd/access.h"
#include "unistd/lseek.h"
#include "unistd/truncate.h"
#include "unistd/ftruncate.h"
#include "unistd/readlink.h"
#include "unistd/readv.h"
#include "unistd/writev.h"
#include "unistd/getegid.h"
#include "unistd/symlink.h"
#include "unistd/umask.h"
#include "unistd/chroot.h"
#include "unistd/link.h"
#include "unistd/unlink.h"
#include "unistd/chdir.h"
#include "unistd/mknod.h"
#include "unistd/chmod.h"
#include "unistd/getpgid.h"
#include "unistd/setpgid.h"
#include "unistd/chown.h"
#include "unistd/lchown.h"
#include "unistd/getgid.h"
#include "unistd/getppid.h"
#include "unistd/rename.h"
#include "unistd/getpgrp.h"
#include "unistd/getdtablesize.h"
#include "unistd/setpgid.h"
#include "unistd/getgroups.h"
#include "unistd/setgroups.h"
#include "unistd/pipe.h"
#include "unistd/chmod_extended.h"
#include "unistd/fchmod_extended.h"
#include "unistd/fchflags.h"
#include "unistd/chflags.h"
#include "unistd/issetugid.h"
#include "signal/kill.h"
#include "signal/sigaltstack.h"
#include "signal/sigaction.h"
#include "signal/sigreturn.h"
#include "signal/sigprocmask.h"
#include "signal/sigsuspend.h"
#include "process/vfork.h"
#include "process/wait4.h"
#include "process/waitid.h"
#include "process/execve.h"
#include "misc/getlogin.h"
#include "misc/shared_region_check_np.h"
#include "misc/ioctl.h"
#include "misc/getrlimit.h"
#include "misc/setrlimit.h"
#include "misc/thread_selfid.h"
#include "misc/sysctl.h"
#include "misc/proc_info.h"
#include "misc/gethostuuid.h"
#include "misc/getrusage.h"
#include "misc/syscall.h"
#include "synch/semwait_signal.h"
#include "fcntl/open.h"
#include "fcntl/fcntl.h"
#include "network/socket.h"
#include "network/connect.h"
#include "network/recvmsg.h"
#include "network/sendmsg.h"
#include "network/recvfrom.h"
#include "network/getpeername.h"
#include "network/getsockname.h"
#include "network/accept.h"
#include "network/shutdown.h"
#include "network/getsockopt.h"
#include "network/setsockopt.h"
#include "network/sendto.h"
#include "network/bind.h"
#include "network/listen.h"
#include "network/socketpair.h"
#include "dirent/getdirentries.h"
#include "stat/fstat.h"
#include "stat/stat.h"
#include "stat/lstat.h"
#include "stat/statfs.h"
#include "stat/mkdir.h"
#include "stat/mkfifo.h"
#include "stat/rmdir.h"
#include "stat/getfsstat.h"
#include "stat/fstatfs.h"
#include "stat/stat64_extended.h"
#include "stat/lstat64_extended.h"
#include "stat/fstat64_extended.h"
#include "time/gettimeofday.h"
#include "time/utimes.h"
#include "time/futimes.h"
#include "time/setitimer.h"
#include "time/getitimer.h"
#include "process/vfork.h"
#include "process/fork.h"
#include "process/posix_spawn.h"
#include "bsdthread/bsdthread_register.h"
#include "bsdthread/bsdthread_create.h"
#include "bsdthread/bsdthread_terminate.h"
#include "bsdthread/disable_threadsignal.h"
#include "hfs/stub.h"
#include "xattr/listxattr.h"
#include "xattr/flistxattr.h"
#include "xattr/removexattr.h"
#include "xattr/fremovexattr.h"
#include "xattr/getxattr.h"
#include "xattr/fgetxattr.h"
#include "xattr/setxattr.h"
#include "xattr/fsetxattr.h"
#include "select/select.h"
#include "select/poll.h"
#include "psynch/psynch_mutexwait.h"
#include "psynch/psynch_mutexdrop.h"
#include "psynch/psynch_cvwait.h"
#include "psynch/psynch_cvsignal.h"
#include "psynch/psynch_cvbroad.h"
#include "bsdthread/workq_kernreturn.h"
#include "bsdthread/workq_open.h"
#include "bsdthread/pthread_kill.h"
#include "conf/pathconf.h"
#include "conf/fpathconf.h"

void* __bsd_syscall_table[600] = {
	[0] = sys_syscall,
	[1] = sys_exit,
	[2] = sys_fork,
	[3] = sys_read,
	[4] = sys_write,
	[5] = sys_open,
	[6] = sys_close,
	[7] = sys_wait4,
	[9] = sys_link,
	[10] = sys_unlink,
	[12] = sys_chdir,
	[13] = sys_fchdir,
	[14] = sys_mknod,
	[15] = sys_chmod,
	[16] = sys_chown,
	[18] = sys_getfsstat,
	[20] = sys_getpid,
	[23] = sys_setuid,
	[24] = sys_getuid,
	[25] = sys_geteuid,
	[27] = sys_recvmsg,
	[28] = sys_sendmsg,
	[29] = sys_recvfrom,
	[30] = sys_accept,
	[31] = sys_getpeername,
	[32] = sys_getsockname,
	[33] = sys_access,
	[34] = sys_chflags,
	[35] = sys_fchflags,
	[36] = sys_sync,
	[37] = sys_kill,
	[39] = sys_getppid,
	[41] = sys_dup,
	[42] = sys_pipe,
	[43] = sys_getegid,
	[46] = sys_sigaction,
	[47] = sys_getgid,
	[48] = sys_sigprocmask,
	[49] = sys_getlogin,
	[53] = sys_sigaltstack,
	[54] = sys_ioctl,
	[57] = sys_symlink,
	[58] = sys_readlink,
	[59] = sys_execve,
	[60] = sys_umask,
	[61] = sys_chroot,
	[66] = sys_vfork,
	[73] = sys_munmap,
	[74] = sys_mprotect,
	[75] = sys_madvise,
	[78] = sys_mincore,
	[79] = sys_getgroups,
	[80] = sys_setgroups,
	[81] = sys_getpgrp,
	[82] = sys_setpgid,
	[83] = sys_setitimer,
	[86] = sys_getitimer,
	[89] = sys_getdtablesize,
	[90] = sys_dup2,
	[92] = sys_fcntl,
	[93] = sys_select,
	[95] = sys_fsync,
	[97] = sys_socket,
	[98] = sys_connect,
	[104] = sys_bind,
	[105] = sys_setsockopt,
	[106] = sys_listen,
	[111] = sys_sigsuspend,
	[116] = sys_gettimeofday,
	[117] = sys_getrusage,
	[118] = sys_getsockopt,
	[120] = sys_readv,
	[121] = sys_writev,
	[123] = sys_fchown,
	[124] = sys_fchmod,
	[128] = sys_rename,
	[132] = sys_mkfifo,
	[133] = sys_sendto,
	[134] = sys_shutdown,
	[135] = sys_socketpair,
	[136] = sys_mkdir,
	[137] = sys_rmdir,
	[138] = sys_utimes,
	[139] = sys_futimes,
	[142] = sys_gethostuuid,
	[147] = sys_setsid,
	[151] = sys_getpgid,
	[153] = sys_pread,
	[154] = sys_pwrite,
	[157] = sys_statfs,
	[158] = sys_fstatfs,
	[173] = sys_waitid,
	[181] = sys_setgid,
	[182] = sys_setegid,
	[183] = sys_seteuid,
	[184] = sys_sigreturn,
	[187] = sys_fdatasync,
	[188] = sys_stat,
	[189] = sys_fstat,
	[190] = sys_lstat,
	[191] = sys_pathconf,
	[192] = sys_fpathconf,
	[194] = sys_getrlimit,
	[195] = sys_setrlimit,
	[196] = sys_getdirentries,
	[197] = sys_mmap,
	[199] = sys_lseek,
	[200] = sys_truncate,
	[201] = sys_ftruncate,
	[202] = sys_sysctl,
	[216] = sys_mkcomplex,
	[217] = sys_statv,
	[218] = sys_lstatv,
	[219] = sys_fstatv,
	[220] = sys_getattrlist,
	[221] = sys_setattrlist,
	[222] = sys_getdirentriesattr,
	[223] = sys_exchangedata,
	[225] = sys_searchfs,
	[226] = sys_delete,
	[227] = sys_copyfile,
	[228] = sys_fgetattrlist,
	[229] = sys_fsetattrlist,
	[230] = sys_poll,
	[234] = sys_getxattr,
	[235] = sys_fgetxattr,
	[236] = sys_setxattr,
	[237] = sys_fsetxattr,
	[238] = sys_removexattr,
	[239] = sys_fremovexattr,
	[240] = sys_listxattr,
	[241] = sys_flistxattr,
	[244] = sys_posix_spawn,
	[282] = sys_chmod_extended,
	[283] = sys_fchmod_extended,
	[294] = sys_shared_region_check_np,
	[301] = sys_psynch_mutexwait,
	[302] = sys_psynch_mutexdrop,
	[303] = sys_psynch_cvbroad,
	[304] = sys_psynch_cvsignal,
	[305] = sys_psynch_cvwait,
	[327] = sys_issetugid,
	[328] = sys_pthread_kill,
	[329] = sys_sigprocmask, // __pthread_sigmask
	[331] = sys_disable_threadsignal,
	[334] = sys_semwait_signal,
	[336] = sys_proc_info,
	[338] = sys_stat64,
	[339] = sys_fstat64,
	[340] = sys_lstat64,
	[341] = sys_stat64_extended,
	[342] = sys_lstat64_extended,
	[343] = sys_fstat64_extended,
	[344] = sys_getdirentries64,
	[345] = sys_statfs64,
	[346] = sys_fstatfs64,
	[347] = sys_getfsstat64,
	[360] = sys_bsdthread_create,
	[361] = sys_bsdthread_terminate,
	[364] = sys_lchown,
	[366] = sys_bsdthread_register,
	[367] = sys_workq_open,
	[368] = sys_workq_kernreturn,
	[372] = sys_thread_selfid,
	[396] = sys_read_nocancel,
	[397] = sys_write_nocancel,
	[398] = sys_open_nocancel,
	[399] = sys_close_nocancel,
	[400] = sys_wait4,
	[401] = sys_recvmsg_nocancel,
	[402] = sys_sendmsg_nocancel,
	[403] = sys_recvfrom_nocancel,
	[404] = sys_accept_nocancel,
	[406] = sys_fcntl_nocancel,
	[407] = sys_select_nocancel,
	[408] = sys_fsync_nocancel,
	[409] = sys_connect_nocancel,
	[410] = sys_sigsuspend_nocancel,
	[411] = sys_readv_nocancel,
	[412] = sys_writev_nocancel,
	[413] = sys_sendto_nocancel,
	[414] = sys_pread_nocancel,
	[415] = sys_pwrite_nocancel,
	[417] = sys_poll_nocancel,
	[423] = sys_semwait_signal_nocancel,
};

