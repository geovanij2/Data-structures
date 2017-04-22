//! Copyright [2017] <Geovani da Silva Júnior
#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! Classe Lista duplamente encadeada
class DoublyLinkedList {
 public:
    //! Construtor padrão
    DoublyLinkedList(): head{nullptr}, size_{0} {}

    //! Destrutor
    ~DoublyLinkedList() {
        clear();
    }

    //! limpa lista
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
    }

    //! insere no fim
    void push_back(const T& data) {
        insert(data, size_);
    }

    //! insere no inicio
    void push_front(const T& data) {
        Node *novo = new Node(data, nullptr, head);
        if (novo == nullptr) {
            throw std::out_of_range("CHEIA");
        }
        head = novo;
        if (novo->next() != nullptr) {
            novo->next()->prev(novo);
        }
        ++size_;
    }

    //! insere na posição
    void insert(const T& data, std::size_t index) {
        Node *previous, *novo;
        if (index > size_) {
            throw std::out_of_range("ARGUMENTO INVÁLIDO");
        } else if (index == 0) {
            return push_front(data);
        } else {
            novo = new Node(data);
            if (novo == nullptr) {
                throw std::out_of_range("CHEIA");
            } else {
                previous = head;
                for (auto i = 1u; i < index; ++i) {
                    previous = previous->next();
                }
                novo->next(previous->next());
                if (novo->next() != nullptr) {
                    novo->next()->prev(novo);
                }
                previous->next(novo);
                ++size_;
            }
        }
    }

    //! insere em ordem
    void insert_sorted(const T& data) {
        Node* actual;
        std::size_t index;
        if (empty()) {
            return push_front(data);
        } else {
            actual = head;
            index = 0;
            while (actual->next() != nullptr && data > actual->data()) {
                actual = actual->next();
                ++index;
            }
            if (data > actual->data()) {
                return insert(data, index +1);
            } else {
                return insert(data, index);
            }
        }
    }

    //! retira da posição
    T pop(std::size_t index) {
        Node *previous, *del;
        T data;
        if (index >= size_) {
            throw std::out_of_range("ARGUMENTO INVÁLIDO");
        } else if (empty()) {
            throw std::out_of_range("VAZIA");
        } else if (index == 0) {
            return pop_front();
        } else {
            previous = head;
            for (auto i = 1u; i < index; ++i) {
                previous = previous->next();
            }
            del = previous->next();
            data = del->data();
            previous->next(del->next());
            if (del->next() != nullptr) {
                del->next()->prev(previous);
            }
            --size_;
            delete del;
            return data;
        }
    }

    //! retira do fim
    T pop_back() {
        return pop(size() - 1);
    }

    //! retira do inicio
    T pop_front() {
        Node *left = head;
        T data;
        if (empty()) {
            throw std::out_of_range("VAZIA");
        }
        data = left->data();
        head = left->next();
        if (head != nullptr) {
            head->prev(nullptr);
        }
        --size_;
        delete left;
        return data;
    }

    //! retira especifico
    void remove(const T& data) {
        pop(find(data));
    }

    //! lista vazia
    bool empty() const {
        return size_ == 0;
    }

    //! contém
    bool contains(const T& data) const {
        if (empty()) {
            throw std::out_of_range("LISTAVAZIA");
        }
        auto it = head;
        while (it != nullptr) {
            if (it->data() == data) {
                return true;
            }
            it = it->next();
        }
        return false;
    }

    //! acesso a um elemento (checando limites)
    T& at(std::size_t index) {
        auto it = head;
        if (empty()) {
            throw std::out_of_range("VAZIO");
        } else if (index > size() - 1) {
            throw std::out_of_range("erro index");
        }
        for (auto i = 0u; i < index; ++i) {
            it = it->next();
        }
        return it->data();
    }

    //! getter constante a um elemento
    const T& at(std::size_t index) const {
        auto it = head;
        if (empty()) {
            throw std::out_of_range("VAZIO");
        } else if (index > size() - 1) {
            throw std::out_of_range("erro index");
        }
        for (auto i = 0u; i < index; ++i) {
            it = it->next();
        }
        return it->data();
    }

    //! posição de um dado
    std::size_t find(const T& data) const {
        if (empty()) {
            return -1;
        }
        auto it = head;
        auto index = 0u;
        while (it->data() != data) {
            it = it->next();
            ++index;
            if (it == nullptr) {
                break;
            }
        }
        return index;
    }

    //! tamanho
    std::size_t size() const {
        return size_;
    }

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data}, next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data}, prev_{prev}, next_{next}
        {}

        T& data() {
            return data_;
        }
        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    std::size_t size_;
};

}  //! namespace structures

#endif
