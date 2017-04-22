//! Copyright [2017] <Geovani da Silva Junior>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
//! Classe que implementa Lista com vetores
class ArrayList {
 public:
    //! Construtor padrao
    ArrayList() {
        max_size_ = DEFAULT_MAX;
        contents = new T[max_size_];
        size_ = 0;
    }

    //! Construtor que define o tamanho da lista
    explicit ArrayList(std::size_t max_size) {
        max_size_ = max_size;
        contents = new T[max_size_];
        size_ = 0;
    }

    //! Destrutor
    ~ArrayList() {
        delete[] contents;
    }

    //! limpa Lista
    void clear() {
        size_ = 0;
    }

    //! adiciona no fim
    void push_back(const T& data) {
        insert(data, size_);
    }

    //! Adiciona no inicio
    void push_front(const T& data) {
        insert(data, 0);
    }

    //! Adiciona na posicao
    void insert(const T& data, std::size_t index) {
        std::size_t actual;
        if (full()) {
            throw std::out_of_range("LISTA CHEIA");
        }
        if (index > size_) {
            throw std::out_of_range("ERROPOSICAO");
        }
        actual = size_;
        while (actual > index) {
            contents[actual] = contents[actual -1];
            actual -= 1;
        }
        contents[index] = data;
        size_ += 1;
    }

    //! Adiciona em ordem
    void insert_sorted(const T& data) {
        std::size_t actual;
        if (full()) {
        throw std::out_of_range("LISTA CHEIA");
        }
        actual = 0;
        while ((actual < size_) && (data > contents[actual])) {
            actual += 1;
        }
        insert(data, actual);
    }

    //! Retira da posicao
    T pop(std::size_t index) {
        std::size_t actual;
        T value;
        if (index >= size_) {
            throw std::out_of_range("ERRO POSICAO");
        }
        value = contents[index];
        actual = index;
        while (actual < size_ -1) {
            contents[actual] = contents[actual + 1];
            actual += 1;
        }
        size_ -= 1;
        return value;
    }

    //! Retira do fim
    T pop_back() {
        return pop(size_ -1);
    }

    //! Retira do inicio
    T pop_front() {
        return pop(0);
    }

    //! retira Especifico;
    void remove(const T& data) {
        std::size_t index_;
        if (empty()) {
            throw std::out_of_range("ERRO LISTA VAZIA");
        }
        index_ = find(data);
        pop(index_);
    }

    //! Lista cheia
    bool full() const {
        return (size_ == max_size_);
    }

    //! Lista vazia
    bool empty() const {
        return (size_ == 0);
    }

    //! Contem
    bool contains(const T& data) const {
        if (empty()) {
            throw std::out_of_range("LISTA VAZIA");
        }
        bool have = false;
        for (int i = 0; i < size_; i++) {
            if (data == contents[i]) {
                have = true;
                break;
            }
        }
        return have;
    }

    //! posicao
    std::size_t find(const T& data) const {
        std::size_t actual;
        if (empty()) {
            throw std::out_of_range("LISTA VAZIA");
        }
        actual = 0;
        while ((actual < size_) && (data != contents[actual])) {
            actual++;
        }
        return actual;
    }

    //! Tamanho atual;
    std::size_t size() const {
        return size_;
    }

    //! Tamanho maximo
    std::size_t max_size() const {
        return max_size_;
    }

    //! at
    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("VALOR INVALIDO");
        }
        return contents[index];
    }

    //! operator[]
    T& operator[](std::size_t index) {
        return contents[index];
    }

    //! AT  const
    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("VALOR INVALIDO");
        }
        return contents[index];
    }

    //! operator[] const
    const T& operator[](std::size_t index) const {
        return contents[index];
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif
