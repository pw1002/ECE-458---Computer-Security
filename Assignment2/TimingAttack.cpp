#include <iostream>
#include <inttypes.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <chrono>
using namespace std::chrono;

struct Interval {
    double start;
    double end;
};

bool compareInterval(Interval i1, Interval i2) {
    return (i1.start < i2.start) ? true : false;
}

//Returns a vector with intervals that do not overlap
std::vector<Interval> noOverlap(Interval arr[], int n) {
    std::vector<Interval> no_overlap;
    std::sort(arr, arr + n, compareInterval);
    
    for (int i = 1; i < n; i++) {
        //if there is no overlap
        if(!(arr[i-1].end > arr[i].start)) {
            no_overlap.push_back(arr[i]);
        }
    }

    return no_overlap;
}

Interval largestInterval (std::vector<Interval> v) {
    double largest_interval = 0;
    int index = 0;

    for (int i = 0; i < v.size(); i++) {
        /*
        if (v.at(i).start > largest_interval) {
            largest_interval = v.at(i).start;
            index = i;
        }
        */
        if (v.at(i).end > largest_interval) {
            largest_interval = v.at(i).end;
            index = i;
        }
    }

    return v.at(index);
}

int validate_password (const char * pwd){
    const char *c = "p";
    while (*pwd == *c && *pwd != '\0' && *c != '\0') {
        ++pwd;
        ++c;
    }
    return *pwd == *c && *pwd == '\0';
}

static __inline__ uint64_t rdtsc () {
    uint32_t hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)lo) | (((uint64_t)hi) << 32);
}

int main() {
    std::cout << "Hello World\n";
    char *pwd_guess;
    char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    double mean[26] = {0};
    double variance[26] = {0};
    Interval confidence_int[26] = {0};
    
    //Warming up
    for(int i = 0; i < 15002; i++) {
        int rand_int = i % 26;
        validate_password(&alphabet[rand_int]);
    }

    //First char of password
    for (int i = 0; i < sizeof(alphabet); i++) {
        std::random_shuffle (&alphabet[0], &alphabet[25]);
        pwd_guess = &alphabet[i];
        //run this measurement n times
        int n = 100;
        for (int j = 0; j < n; j++) {
            auto start = high_resolution_clock::now();
            validate_password(pwd_guess);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            //Add to mean & variance in array for corresponding index
            mean[i] = mean[i] + duration.count();
            variance[i] = variance[i] + pow((duration.count() - mean[i]), 2);
        }
        //Finish calculating variance
        for (int j = 0; j < sizeof(variance); j++) {
            variance[j] = variance[j] * (1/(n-1));
        }
        //Calculate confidence intervals
        confidence_int[i].start = mean[i] - (1.76 * (variance[i]/sqrt(n)));
        confidence_int[i].end = mean[i] + (1.76 * (variance[i]/sqrt(n)));\
    }
    int n1 = sizeof(confidence_int) / sizeof(confidence_int[0]);
    //Modify confidence_int to have no overlapping intervals
    std::vector<Interval> no_overlap = noOverlap(confidence_int, n1);
    Interval largest = largestInterval(no_overlap);
    //Find matching interval to find the correct character
    int largestIntervalIndex = 0;
    for (int i = 0; i < sizeof(confidence_int); i++) {
        if (confidence_int[i].start == largest.start && confidence_int[i].end == largest.end) {
            largestIntervalIndex = i;
            break;
        }
    }
    char correctChar = alphabet[largestIntervalIndex];
    std::cout << "The correct character is " << correctChar;
    
    return 0;
}