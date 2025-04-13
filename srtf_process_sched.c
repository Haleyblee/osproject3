#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "srtf_process_sched.h"
#include <math.h>

void read_input_file(const char* filename, int* context_switch, Process** process_list, int* num_processes) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", context_switch);
    printf("Context Switch Time: %d\n\n", *context_switch);

    int capacity = 5;
    *process_list = malloc(capacity * sizeof(Process));
    float arrival, burst;
    char id = 'A';

    printf("Process List:\n");
    while (fscanf(file, "%f %f", &arrival, &burst) == 2) {
        if (*num_processes >= capacity) {
            capacity *= 2;
            *process_list = realloc(*process_list, capacity * sizeof(Process));
        }

        Process* p = &(*process_list)[*num_processes];
        p->id = id++;
        p->arrival_time = arrival;
        p->burst_time = burst;
        p->remaining_time = burst;
        p->start_time = -1;
        p->end_time = -1;
        p->completed = 0;
        p->response_time = -1;
        p->first_start_time = -1;
        p->has_started = 0;

        printf("%c | Arrival Time: %.3f | Burst Time: %.3f\n", p->id, arrival, burst);

        (*num_processes)++;
    }

    fclose(file);
}

int get_next_process(Process* processes, int n, int current_time) {
    int idx = -1;
    float min_remaining = INFINITY;

    for (int i = 0; i < n; i++) {
        if (!processes[i].completed && (int)floor(processes[i].arrival_time) <= current_time) {
            if (processes[i].remaining_time < min_remaining) {
                min_remaining = processes[i].remaining_time;
                idx = i;
            }
        }
    }

    return idx;
}

void simulate_srtf(Process* processes, int n, int context_switch_time) {
    int time = 0;
    int completed = 0;
    int prev = -1;

    printf("\nGantt Chart Timeline:\n");

    while (completed < n) {
        int idx = get_next_process(processes, n, time);

        if (idx == -1) {
            time++;
            continue;
        }

        if (prev != -1 && prev != idx) {
            printf(" x ");
            time += context_switch_time;
        }

        if (!processes[idx].has_started) {
            processes[idx].first_start_time = time;
            processes[idx].has_started = 1;
        }

        printf(" %d %c", time, processes[idx].id);
        time++;
        processes[idx].remaining_time -= 1;

        if (processes[idx].remaining_time <= 0) {
            processes[idx].completed = 1;
            processes[idx].end_time = time;
            completed++;
        }

        prev = idx;
    }

    printf(" %d\n", time);
}

void calculate_and_display_metrics(Process* processes, int n) {
    int total_tat = 0, total_wt = 0, total_rt = 0;

    printf("\nPerformance Report:\n");
    printf("Process | Turnaround | Waiting | Response\n");

    for (int i = 0; i < n; i++) {
        int arrival = (int)floor(processes[i].arrival_time);
        int burst = (int)floor(processes[i].burst_time);
        int end = processes[i].end_time;
        int start = processes[i].first_start_time;

        int turnaround = end - arrival;
        int wait = turnaround - burst;
        int response = start - arrival;

        total_tat += turnaround;
        total_wt += wait;
        total_rt += response;

        printf("  %c     |     %2d     |   %2d    |   %2d\n", processes[i].id, turnaround, wait, response);
    }

    printf("\nAverages:\n");
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Response Time: %.2f\n", (float)total_rt / n);
}

void free_memory(Process* processes) {
    free(processes);
}
