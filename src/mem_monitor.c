#include "mem_monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double get_mem_usage(unsigned long *mem_total_kb, unsigned long *mem_used_kb) {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) { perror("open /proc/meminfo"); exit(EXIT_FAILURE); }

    char key[128];
    unsigned long value;
    char unit[32];
    unsigned long mem_total=0, mem_free=0, buffers=0, cached=0;

    while (fscanf(fp, "%s %lu %s", key, &value, unit) == 3) {
        if (strcmp(key, "MemTotal:") == 0) mem_total = value;
        else if (strcmp(key, "MemFree:") == 0) mem_free = value;
        else if (strcmp(key, "Buffers:") == 0) buffers = value;
        else if (strcmp(key, "Cached:") == 0) cached = value;
    }
    fclose(fp);

    unsigned long used = mem_total - (mem_free + buffers + cached);
    double usage_percent = ((double)used / mem_total) * 100.0;
    *mem_total_kb = mem_total;
    *mem_used_kb = used;
    return usage_percent;
}
