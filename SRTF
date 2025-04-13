#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    char id;
    double arrival;
    double burst;
    double remaining;
    int start_time;
    int end_time;
    int response_time;
    int first_exec;
    int completed;
} Process;

int floor_time(double t) {
    return (int)t; // floor to nearest integer
}

int all_done(Process *plist, int n) {
    for (int i = 0; i < n; ++i)
        if (!plist[i].completed) return 0;
    return 1;
}

int get_next_process(Process *plist, int n, double current_time) {
    int idx = -1;
    for (int i = 0; i < n; ++i) {
        if (!plist[i].completed && plist[i].arrival <= current_time) {
            if (idx == -1 || plist[i].remaining < plist[idx].remaining)
                idx = i;
        }
    }
    return idx;
}

void run_srtf(Process *plist, int n, int context_time) {
    double current_time = 0;
    int last_pid = -1;

    printf("Gantt Chart:\n");

    while (!all_done(plist, n)) {
        int idx = get_next_process(plist, n, current_time);

        if (idx == -1) {
            current_time += 1;
            continue;
        }

        // Context switch (if needed)
        if (last_pid != -1 && last_pid != idx) {
            printf("%.0f x ", current_time);
            current_time += context_time;
        }

        if (plist[idx].remaining == plist[idx].burst) {
            plist[idx].response_time = floor_time(current_time) - floor_time(plist[idx].arrival);
            plist[idx].first_exec = floor_time(current_time);
        }

        printf("%.0f %c ", current_time, plist[idx].id);

        double exec_time = plist[idx].remaining;
        plist[idx].start_time = floor_time(current_time);
        plist[idx].end_time = floor_time(current_time + exec_time);
        current_time += exec_time;
        plist[idx].remaining = 0;
        plist[idx].completed = 1;

        last_pid = idx;
    }

    printf("%.0f\n", current_time);

    // Performance metrics
    printf("\nProcess\tTurnaround\tWaiting\t\tResponse\n");

    double total_turn = 0, total_wait = 0, total_resp = 0;
    for (int i = 0; i < n; ++i) {
        int turn = plist[i].end_time - floor_time(plist[i].arrival);
        int wait = turn - floor_time(plist[i].burst);
        int resp = plist[i].response_time;

        printf("%c\t%d\t\t%d\t\t%d\n", plist[i].id, turn, wait, resp);

        total_turn += turn;
        total_wait += wait;
        total_resp += resp;
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_turn / n);
    printf("Average Waiting Time: %.2f\n", total_wait / n);
    printf("Average Response Time: %.2f\n", total_resp / n);
}
