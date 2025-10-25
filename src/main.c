#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cpu_monitor.h"
#include "mem_monitor.h"
#include "sys_utils.h"

int main() {
    printf("Android Performance Profiler (C CLI)\n");
    printf("Press Ctrl+C to exit.\n\n");
    sleep(1);

    while (1) {
        double cpu_usage = get_cpu_usage(1000);
        unsigned long mem_total, mem_used;
        double mem_usage = get_mem_usage(&mem_total, &mem_used);

        clear_screen();
        printf("==========================================\n");
        printf("  ANDROID PERFORMANCE PROFILER (CLI)\n");
        printf("==========================================\n");
        printf("CPU Usage     : %.2f%%\n", cpu_usage);
        printf("Memory Usage  : %.2f%% (%lu MB / %lu MB)\n",
               mem_usage, mem_used / 1024, mem_total / 1024);
        printf("------------------------------------------\n");
        printf("Collecting data... (Ctrl+C to stop)\n");

        usleep(500 * 1000);
    }

    return 0;
}
