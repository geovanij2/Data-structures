// "Copyright 2017 Geovani da Silva Junior"
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
/*!
  classe que representa um estrutura de dados estilo fila
*/
class ArrayQueue {
 public:
    //! construtor padrao
    /*!
      cria fila com tamanho padrao
    */
    ArrayQueue() {
        contents = new T[DEFAULT_SIZE];
        size_ = -1;
    }
    //! Um construtor
    /*!
      cria fila com tamanho escolhido
    */
    explicit ArrayQueue(std::size_t max) {
        max_size_ = max;
        contents = new T[max];
        size_ = -1;
    }
    //! Um destrutor
    /*!
      Destroi a fila
    */
    ~ArrayQueue() {
        delete[] contents;
    }
    //! adiciona a fila
    /*!
      param 1 igual ao dado a ser enfileirado
      adiciona o dado ao fim da fila caso ela nao esteja cheia
    */
    void enqueue(const T& data) {
        if (full()) {
            throw std::out_of_range("queue full");
        }
        size_ += 1;
        contents[size_] = data;
    }
    //! retira da fila
    /*!
      remove o primeiro elemento da fila e reagrupa os que sobraram
    */
    T dequeue() {
        if (empty()) {
            throw std::out_of_range("queue empty");
        }
        T aux_ = contents[0];
        for (int i = 0; i < size_; i++) {
            contents[i] = contents[i+1];
        }
        size_ -=1;
        return aux_;
    }
    //! retorna o ultimo elemento da fila
    T& back() {
        if (empty()) {
            throw std::out_of_range("queue empty");
        }
        return contents[size_];
    }
    //! limpa fila
    void clear() {
        size_ = -1;
    }
    //! retorna tamanho atual
    std::size_t size() {
        return size_ +1;
    }
    //! retorna tamanho maximo
    std::size_t max_size() {
        return max_size_;
    }
    //! retorna true se a fila estiver vazia
    bool empty() {
        return size_ == -1;
    }
    //! retorna true se fila estiver cheia
    bool full() {
        return size_ == max_size_ - 1;
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif
