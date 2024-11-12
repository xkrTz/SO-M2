import threading
import time
import numpy as np  # Usado para alocar memória de forma mais controlada

class MemoryAllocator(threading.Thread):
    def __init__(self, buf_size, iteration_count):
        threading.Thread.__init__(self)
        self.buf_size = buf_size
        self.iteration_count = iteration_count

    def run(self):
        start_time = time.time()

        for _ in range(self.iteration_count):
            buffer = np.zeros(self.buf_size // 4, dtype=np.int32)  # Aloca um array de inteiros
            # Usa o buffer para simular algum processamento
            buffer[0] = 1  # Operação simples para evitar otimização

        elapsed_time = time.time() - start_time
        print(f"Thread {self.ident}: {elapsed_time:.4f} s to allocate {self.buf_size // (1024 * 1024)} MB {self.iteration_count} times.")

def run_test(buf_size, iteration_count, num_threads):
    threads = []

    # Cria e inicia threads
    for _ in range(num_threads):
        thread = MemoryAllocator(buf_size, iteration_count)
        threads.append(thread)
        thread.start()

    # Espera todas as threads terminarem
    for thread in threads:
        thread.join()

# Configuração do teste
if __name__ == "__main__":
    iteration_count = 100

    # Executa o teste com diferentes tamanhos de buffer e números de threads
    print("Teste com 64 MB e 2 threads:")
    run_test(64 * 1024 * 1024, iteration_count, 2)  # 64 MB, 2 threads
    
    print("\nTeste com 64 MB e 4 threads:")
    run_test(64 * 1024 * 1024, iteration_count, 4)  # 64 MB, 4 threads
    
    print("\nTeste com 128 MB e 2 threads:")
    run_test(128 * 1024 * 1024, iteration_count, 2)  # 128 MB, 2 threads
    
    print("\nTeste com 128 MB e 4 threads:")
    run_test(128 * 1024 * 1024, iteration_count, 4)  # 128 MB, 4 threads
