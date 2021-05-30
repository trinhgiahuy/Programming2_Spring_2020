#include "concur2020lib/concur2020.hh"
#include <iostream>
#include <mutex>
#include <thread>
const int SAMPLES = 1000;
std::mutex mu;
typedef uint64_t Counter;

struct {
    Counter alpha;
    Counter beta;
    Counter gamma;
} counters = { 0, 0, 0 };

void printCounters() {

    std::cout << "COUNTER:" << std::endl;
    std::cout << "alpha: " << counters.alpha << std::endl;
    std::cout << "beta : " << counters.beta << std::endl;
    std::cout << "gamma: " << counters.gamma << std::endl;

}

void countSample(concur2020::DetectorData_t sample) {

    auto name = concur2020::itemName(sample);
    if (name == "alpha") {
        counters.alpha++;
    }
    else if (name == "beta") {
        counters.beta++;
    }
    else if (name == "gamma") {
        counters.gamma++;
    }

}



void processSample(int& time_loop  ) {
    for(int i=0 ; i<time_loop;i++){

        std::lock_guard<std::mutex> guard(mu);

        auto sample = concur2020::detect();

        std::cout << "Read: " << concur2020::itemName(sample) << std::endl;

        countSample(sample);
    }
}



//void processSample()

int main() {

    const int num_thread = 5;
    int distance = SAMPLES / 5;
    std::thread thread_arr[5];

    for (auto i = 0; i < num_thread; i++) {
        thread_arr[i]=std::thread(processSample(distance));
    }
    printCounters();
    for(auto&t : thread_arr){
        t.join();
    }
    return EXIT_SUCCESS;

}
