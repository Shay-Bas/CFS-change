#include <linux/kernel.h>
#include <sys/syscall.h>

long rtnice(int pid, long s_runtime){
	return syscall(323, pid, s_runtime);
}