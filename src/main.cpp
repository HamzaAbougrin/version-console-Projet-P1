#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <iomanip>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
};

std::vector<Process> LoadProcessesFromFile(const std::string& filename) {
    std::vector<Process> processes;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file!" << std::endl;
        return processes;
    }

    int id, arrival, burst;
    while (file >> id >> arrival >> burst) {
        processes.push_back({id, arrival, burst});
    }

    file.close();
    return processes;
}

void PrintGanttChart(const std::vector<std::pair<int, int>>& ganttChart, int totalTime) {
    const std::string colors[] = {
        "\033[101m", // Bright red background
        "\033[102m", // Bright green background
        "\033[103m", // Bright yellow background
        "\033[104m", // Bright blue background
        "\033[105m", // Bright magenta background
        "\033[106m", // Bright cyan background
        "\033[107m"  // Bright white background
    };
    const std::string resetColor = "\033[0m";

    // Print each process on a separate line
    for (int p = 1; p <= 4; ++p) {
        std::cout << "P" << p << " |";
        int currentTime = 0;
        for (const auto& segment : ganttChart) {
            if (segment.first == p) {
                int processId = segment.first % 7;
                for (int i = 0; i < segment.second; ++i) {
                    std::cout << colors[processId] << "   " << resetColor; // Triple space for larger segments
                }
                currentTime += segment.second;
            } else {
                std::cout << std::string(segment.second * 3, ' '); // Triple space for larger segments
            }
        }
        std::cout << "\n";
    }
}

std::vector<std::pair<int, int>> FIFO(const std::vector<Process>& processes, int &totalTime) {
    std::vector<std::pair<int, int>> ganttChart;
    int currentTime = 0;

    for (const auto& process : processes) {
        if (currentTime < process.arrivalTime) {
            currentTime = process.arrivalTime;
        }
        ganttChart.push_back({process.id, process.burstTime});
        currentTime += process.burstTime;
    }

    totalTime = currentTime;
    return ganttChart;
}

std::vector<std::pair<int, int>> SJF(std::vector<Process> processes, int &totalTime) {
    std::vector<std::pair<int, int>> ganttChart;
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int currentTime = 0;
    while (!processes.empty()) {
        auto shortestJob = std::min_element(processes.begin(), processes.end(), [&](const Process& a, const Process& b) {
            return a.burstTime < b.burstTime && a.arrivalTime <= currentTime;
        });

        if (shortestJob == processes.end() || shortestJob->arrivalTime > currentTime) {
            currentTime++;
            continue;
        }

        ganttChart.push_back({shortestJob->id, shortestJob->burstTime});
        currentTime += shortestJob->burstTime;
        processes.erase(shortestJob);
    }

    totalTime = currentTime;
    return ganttChart;
}

std::vector<std::pair<int, int>> RoundRobin(std::vector<Process> processes, int quantum, int &totalTime) {
    std::vector<std::pair<int, int>> ganttChart;
    std::queue<Process> readyQueue;

    int currentTime = 0;
    size_t index = 0;
    while (index < processes.size() || !readyQueue.empty()) {
        while (index < processes.size() && processes[index].arrivalTime <= currentTime) {
            readyQueue.push(processes[index]);
            index++;
        }

        if (readyQueue.empty()) {
            currentTime++;
            continue;
        }

        Process currentProcess = readyQueue.front();
        readyQueue.pop();

        int executionTime = std::min(quantum, currentProcess.burstTime);
        ganttChart.push_back({currentProcess.id, executionTime});
        currentTime += executionTime;

        currentProcess.burstTime -= executionTime;
        if (currentProcess.burstTime > 0) {
            readyQueue.push(currentProcess);
        }
    }

    totalTime = currentTime;
    return ganttChart;
}

int main() {
    std::string filename;
    std::cout << "Insert the address of your file: ";
    std::cin >> filename;

    std::vector<Process> processes = LoadProcessesFromFile(filename);
    if (processes.empty()) {
        return 1;
    }

    int choice;
    std::cout << "==================== CPU Scheduling Algorithms ====================\n";
    std::cout << "1. First-Come, First-Served (FCFS)\n";
    std::cout << "2. Shortest Job First (SJF)\n";
    std::cout << "3. Round Robin (RR)\n";
    std::cout << "Enter your choice (1-3): ";
    std::cin >> choice;

    std::vector<std::pair<int, int>> ganttChart;
    int totalTime = 0;

    switch (choice) {
        case 1:
            ganttChart = FIFO(processes, totalTime);
            break;
        case 2:
            ganttChart = SJF(processes, totalTime);
            break;
        case 3:
            int quantum;
            std::cout << "Enter quantum time: ";
            std::cin >> quantum;
            ganttChart = RoundRobin(processes, quantum, totalTime);
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            return 1;
    }

    PrintGanttChart(ganttChart, totalTime);

    return 0;
}