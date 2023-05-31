#include <stdio.h>
#include <sys/time.h>

unsigned long long get_timestamp_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long long timestamp_ms = (unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000;
    return timestamp_ms;
}

int main() {
    unsigned long long timestamp_ms = get_timestamp_ms();
    printf("%llu\n", timestamp_ms);
    return 0;
}

