#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <vector>

using namespace std;

struct Job {
    string name;
    int request_time;
    int start_time;
    int duration;
    int remaining_time;
    int completion_time;
};

int main() {

  //LOAD EVERYTHING FROM THE JOB TEXT FILE INTO A MASTER LIST
    ifstream input_file("job.txt");
    string line;
    vector<Job> job_list;
    vector<Job> rr_list;
    vector<Job> finished_processes;

    while (getline(input_file, line)) {
        string field;
        stringstream ss(line);
        Job process;
        int field_counter = 0;
        while (getline(ss, field, ',')) {
            switch (field_counter) {
                case 0:
                    process.name = "Job " + field;
                    break;
                case 1:
                    process.request_time = stoi(field);
                    break;
                case 2:
                    process.duration = stoi(field);
                    break;
                default:
                    break;
            }
            field_counter++;
        }
        process.remaining_time = process.duration;
        process.completion_time = -1;

        job_list.push_back(process);
    }

    //THE FOLLOWING BLOCK OF CODE WAS USED TO CHECK IF ALL THE JOBS WERE CORRECTLY LOADED INTO THE FILE
  /*
    for (const auto& job : job_list) {
        cout << "Name: " << job.name << endl;
        cout << "Request Time: " << job.request_time << endl;
        cout << "Duration: " << job.duration << endl;
        cout << endl;
    }
    */

    int current_time = 0;
    int time_allocated = 0;

    while(1) {
        //PARSE THRU ALL JOBS AND ADD THEM TO THE ROUND ROBIN QUEUE IF THEIR SCHEDULING TIME IS THE SAME AS THE CURRENT TIME
        for (const auto& job : job_list) {
            if (job.request_time == current_time) {
                rr_list.push_back(job);
                cout << job.name << "," << "scheduled at time " << current_time << "ms for " << job.duration << "ms" << endl;
            }
        }
    
      //DECREMENT THE DURATION VALUE FOR WHATEVER PROCESS/JOB IS CURRENTLY AT THE FRONT OF THE QUEUE MAKE SURE THE SIZE OF THE QUEUE IS GREATER THAN ZERO IN ORDER FOR THIS TO HAPPEN. HOWEVER, SOME PROCESSES TAKE 0 ms TO FINISH, SO DON'T NEED TO ALLOCATE ANY RESOURCES TO THEM OR DECREMENT THE THEIR REMAINING TIME
        if (rr_list.size() > 0 && rr_list[0].duration > 0) {
            rr_list[0].remaining_time += -1;
            time_allocated++;
        }
    
      //IF THE PROCESS HAS FINISHED, THEN ANNOUNCE THAT IT IS FINISHED, ADD IT TO THE LIST OF STUFF THAT IS FINISHED, REMOVE THE PROCESS ENTIRELY FROM THE ROUND ROBIN QUEUE, AND RESET THE TIME ALLOCATED TO ZERO.
        if(rr_list[0].remaining_time == 0) {

            cout << rr_list[0].name << "," << "scheduled for " << rr_list[0].duration << "ms" << ", completed" << endl;

            Job placeholderJob = rr_list[0];
            finished_processes.push_back(placeholderJob);
            rr_list.erase(rr_list.begin());
            time_allocated = 0;
        
        }
    
      //IF THE TIME ALLOCATED HAS BEEN 10 SECONDS, TAKE THE THING IN FRONT OF THE RR LIST AND PUT IT TO THE BACK, AND RESET TIME ALLOCATED TO 0.
        if (time_allocated == 10) {
            Job myJob = rr_list[0];
            rr_list.push_back(myJob);
            rr_list.erase(rr_list.begin());
            time_allocated = 0;
        }
    
      //BREAK THE WHILE LOOP IF THE LIST SIZE OF THE COMPLETED TASKS IS EQUAL TO THE SIZE OF JOBS LIST (ALL JOBS FINISHED)
        if (finished_processes.size() == job_list.size()) {
            cout << "Schedule Simulation Complete.";
            break;
        }
  
      //INCREMENT THE CURRENT TIME
        current_time++;
    
    }

    return 0;
}