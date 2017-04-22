//! Copyright [2017] <Geovani da Silva Junior>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! LISTA ENCADEADA
class LinkedList {
 public:
    //! Construtor da lista
    LinkedList(): head{nullptr}, size_{0} {}

    //! Destrutor
    ~LinkedList() {
        clear();
    }

    //! limpar lista
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

    //! inserir no fim
    void push_back(const T& data) {
        if (empty()) {
            push_front(data);
        } else {
            insert(data, size_);
        }
    }

    //! inserir no inicio
    void push_front(const T& data) {
        Node* novo = new Node(data, head);
        if (novo == nullptr) {
            throw std::out_of_range("ERROLISTACHEIA-pushfront");
        }
        head = novo;
        ++size_;
    }

    //! inserir na posição
    void insert(const T& data, std::size_t index) {
        Node *novo, *previous;
        if (index > size_) {
            throw std::out_of_range("ERROPOSICAO-insert");
        } else if (index == 0) {
            push_front(data);
        } else {
            novo = new Node(data);
            if (novo == nullptr) {
                throw std::out_of_range("ERROLISTACHEIA-insert");
            } else {
                previous = head;
                for (auto i = 1u; i < index; ++i) {
                    previous = previous->next();
                }
                novo->next(previous->next());
                previous->next(novo);
                ++size_;
            }
        }
    }

    //! inserir em ordem
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

    //! acessar um elemento na posiçao index
    T& at(std::size_t index) {
        auto it = head;
        for (auto i = 0u; i < index; ++i) {
            if (it->next() == nullptr) {
                throw std::out_of_range("ERROPOSIÇAO");
            }
            it = it->next();
        }
        return it->data();
    }

    //! retira da posição
    T pop(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("LISTAVAZIA");
        }
        Node *previous, *eliminate;
        T volta;
        if (index > size_ -1) {
            throw std::out_of_range("ERROPOSICAO-pop");
        } else if (index == 0) {
            return pop_front();
        } else {
            previous = head;
            for (auto i = 0u; i < index - 1; ++i) {
                previous = previous->next();
            }
            eliminate = previous->next();
            volta = eliminate->data();
            previous->next(eliminate->next());
            --size_;
            delete eliminate;
            return volta;
        }
    }
    //! retira do fim
    T pop_back() {
        return pop(size_ - 1);
    }

    //! retira do inicio
    T pop_front() {
        Node* left;
        T volta;
        if (empty()) {
            throw std::out_of_range("LISTAVAZIA-popfront");
        } else {
            left = head;
            volta = left->data();
            head = left->next();
            --size_;
            delete(left);
            return volta;
        }
    }

    //! remove dado
    void remove(const T& data) {
        pop(find(data));
    }

    //! lista vazia
    bool empty() const {
        return size_ == 0;
    }

    //! contem
    bool contains(const T& data) const {
        if (empty()) {
            throw std::out_of_range("LISTAVAZIA-contains");
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

    //! posição do dado
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

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  //! namespace structures

#endif


