#include "cpu_monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void read_cpu_times(unsigned long long *total, unsigned long long *idle) {
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp) { perror("open /proc/stat"); exit(EXIT_FAILURE); }

    unsigned long long user, nice, system, idle_time, iowait, irq, softirq;
    fscanf(fp, "cpu  %llu %llu %llu %llu %llu %llu %llu",
           &user, &nice, &system, &idle_time, &iowait, &irq, &softirq);
    fclose(fp);

    *idle = idle_time + iowait;
    *total = user + nice + system + idle_time + iowait + irq + softirq;
}

double get_cpu_usage(int interval_ms) {
    unsigned long long total1, idle1, total2, idle2;
    read_cpu_times(&total1, &idle1);
    usleep(interval_ms * 1000);
    read_cpu_times(&total2, &idle2);

    unsigned long long total_diff = total2 - total1;
    unsigned long long idle_diff = idle2 - idle1;
    if (total_diff == 0) return 0.0;

    return (100.0 * (total_diff - idle_diff)) / total_diff;
}
