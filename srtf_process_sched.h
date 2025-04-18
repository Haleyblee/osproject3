//Brianna Lee
#ifndef SRTF_PROCESS_SCHED_H
#define SRTF_PROCESS_SCHED_H

typedef struct {
    char id;
    float arrival_time;
    float burst_time;
    float remaining_time;
    int start_time;
    int end_time;
    int completed;
    int first_start_time;
    int response_time;
    int has_started;
} Process;

void read_input_file(const char* filename, int* context_switch, Process** process_list, int* num_processes);
void simulate_srtf(Process* processes, int num_processes, int context_switch_time);
void calculate_and_display_metrics(Process* processes, int num_processes);
void free_memory(Process* processes);

#endif
