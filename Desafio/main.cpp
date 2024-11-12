#include "stdafx.h"
#include <chrono>
#include <stdio.h>
#include <thread>
#include <vector>

class Timer {
public:
    Timer() {
        start = clock.now();
    }

    // Retorna o tempo decorrido em segundos.
    double GetElapsed() {
        auto end = clock.now();
        auto duration = end - start;
        return std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count() * 1.e-9;
    }

private:
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock clock;

    Timer(const Timer&) = delete;
    Timer operator=(const Timer&) = delete;
};

// Função que cada thread executará para alocar e liberar memória
void AllocateMemory(int bufSize, int iterationCount) {
    Timer timer;
    for (int i = 0; i < iterationCount; ++i) {
        int* p = new int[bufSize / sizeof(int)];  // Aloca memória
        delete[] p;  // Libera a memória
    }
    printf("Thread %ld: %1.4f s to allocate %d MB %d times.\n",
        std::this_thread::get_id(),
        timer.GetElapsed(),
        bufSize / (1024 * 1024),
        iterationCount);
}

// Função para executar a alocação de memória com várias threads
void RunMultithreadedAllocation(int bufSize, int iterationCount, int numThreads) {
    std::vector<std::thread> threads;

    // Cria e inicia as threads
    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(AllocateMemory, bufSize, iterationCount));
    }

    // Aguarda que todas as threads terminem
    for (auto& th : threads) {
        th.join();
    }
}

int main() {
    const int iterationCount = 100;

    // Executa o teste com diferentes tamanhos de buffer e números de threads
    printf("Teste com 64 MB e 2 threads:\n");
    RunMultithreadedAllocation(64 * 1024 * 1024, iterationCount, 2);  // 64 MB, 2 threads

    printf("\nTeste com 64 MB e 4 threads:\n");
    RunMultithreadedAllocation(64 * 1024 * 1024, iterationCount, 4);  // 64 MB, 4 threads

    printf("\nTeste com 128 MB e 2 threads:\n");
    RunMultithreadedAllocation(128 * 1024 * 1024, iterationCount, 2);  // 128 MB, 2 threads

    printf("\nTeste com 128 MB e 4 threads:\n");
    RunMultithreadedAllocation(128 * 1024 * 1024, iterationCount, 4);  // 128 MB, 4 threads

    return 0;
}
