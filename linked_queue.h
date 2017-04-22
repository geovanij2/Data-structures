//! Copyright [2017] <Geovani da Silva Júnior>
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! Classe Fila encadeada
class LinkedQueue {
 public:
    //! Construtor padrão
    LinkedQueue(): head{nullptr}, tail{nullptr}, size_{0} {}

    //! Destrutor
    ~LinkedQueue() {
        clear();
    }

    //! limpa fila
    void clear() {
        Node *actual, *previous;
        actual = head;
        while (actual != nullptr) {
            previous = actual;
            actual = actual->next();
            delete previous;
        }
        size_ = 0u;
        head = nullptr;
        tail = nullptr;
    }

    //! enfilerar
    void enqueue(const T& data) {
        Node *novo = new Node(data, nullptr);
        if (empty()) {
            head = novo;
            tail = novo;
        } else {
            tail->next(novo);
        }
        tail = novo;
        ++size_;
    }

    //! desenfilerar
    T dequeue() {
        T volta;
        Node *left;
        if (empty()) {
            throw std::out_of_range("VAZIA");
        } else {
            left = head;
            volta = left->data();
            head = left->next();
            if (size_ == 1) {
                tail = nullptr;
            }
            --size_;
            delete left;
            return volta;
        }
    }

    //! primeiro dado
    T& front() const {
        if (empty()) {
            throw std::out_of_range("VAZIA");
        }
        return head->data();
    }

    //! ultimo dado
    T& back() const {
        if (empty()) {
            throw std::out_of_range("VAZIA");
        }
        return  tail->data();
    }

    //! fila vazia
    bool empty() const {
        return size_ == 0;
    }

    //! tamanho
    std::size_t size() const {
        return size_;
    }

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

 private:
    Node* head;  // nodo-cabeça
    Node* tail;  // nodo-fim
    std::size_t size_;  // tamanho
};

}  //! namespace structures

#endif
