#include "srtf_process_sched.h"
#include <stdlib.h>

int main() {
    int context_switch_time;
    Process* processes = NULL;
    int num_processes = 0;

    read_input_file("input.txt", &context_switch_time, &processes, &num_processes);
    simulate_srtf(processes, num_processes, context_switch_time);
    calculate_and_display_metrics(processes, num_processes);
    free_memory(processes);

    return 0;
}
