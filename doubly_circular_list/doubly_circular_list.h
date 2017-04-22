//! Copyright [2017] <Geovani da Silva Júnior>
#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {
//! Classe lista duplamente encadeada
template<typename T>
class DoublyCircularList {
 public:
    //! construtor
    DoublyCircularList() {
        size_ = 0u;
        head = nullptr;
    }

    //! destrutor
    ~DoublyCircularList() {
        clear();
    }

    //! limpa lista
    void clear() {
        Node *actual, *previous;
        actual = head;
        auto i = 0u;
        while (i < size_) {
            previous = actual;
            actual = actual->next();
            delete previous;
            ++i;
        }
        size_ = 0u;
        head = nullptr;
    }

    //! insere no fim
    void push_back(const T& data) {
        if (empty()) {
            return push_front(data);
        }
        auto novo = new Node(data, head);
        if (novo == nullptr) {
            throw std::out_of_range("Erro lista cheia!");
        }
        auto it = end();
        it->next(novo);
        novo->prev(it);
        head->prev(novo);
        ++size_;
    }

    //! insere no começo
    void push_front(const T& data) {
        auto novo = new Node(data);
        if (novo == nullptr) {
            throw std::out_of_range("Erro lista cheia!");
        }
        if (empty()) {
            head = novo;
            head->next(head);
            head->prev(head);
            ++size_;
        } else {
            novo->next(head);
            novo->prev(end());
            head = novo;
            end()->next(head);
            ++size_;
        }
    }

    //! insere na posição
    void insert(const T& data, std::size_t index) {
        if (index > size_) {
            throw std::out_of_range("Erro posição!");
        }
        if (index == 0) {
            return push_front(data);
        }
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        auto novo = new Node(data, it, it->next());
        if (novo == nullptr) {
            throw std::out_of_range("Erro lista cheia");
        }
        it->next()->prev(novo);
        it->next(novo);
        ++size_;
    }

    //! insere em ordem
    void insert_sorted(const T& data) {
        if (empty()) {
            return push_front(data);
        }
        auto it = head;
        auto index = 0u;
        while (index < size_ && data > it->data()) {
            it = it->next();
            ++index;
        }
        return insert(data, index);
    }

    //! retira da posição
    T pop(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Erro lista vazia");
        }
        if (index == 0) {
            return pop_front();
        }
        if (index == size_ - 1) {
            return pop_back();
        }
        auto it = head;
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        auto del = it->next();
        auto data = del->data();
        it->next(del->next());
        del->next()->prev(it);
        delete del;
        --size_;
        return data;
    }

    //! retira do final
    T pop_back() {
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        if (size_ == 1) {
            return pop_front();
        }
        auto data = end()->data();
        auto del = end();
        del->prev()->next(head);
        head->prev(del->prev());
        delete del;
        --size_;
        return data;
    }

    //! retira do começo
    T pop_front() {
        T data;
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        auto del = head;
        data = del->data();
        head = del->next();
        head->prev(end());
        end()->next(head);
        delete del;
        --size_;
        return data;
    }

    //! remove elemento
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
            throw std::out_of_range("Lista vazia!");
        }
        if (find(data) == size_) {
            return false;
        }
        return true;
    }

    //! acesso a um elemento(checando limites)
    T& at(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        if (index >= size_) {
            throw std::out_of_range("Erro index!");
        }
        auto it = head;
        for (auto i = 0u; i < index; ++i) {
            it = it->next();
        }
        return it->data();
    }

    //! acesso a um elemento(constante)
    const T& at(std::size_t index) const {
        auto it = head;
        for (auto i = 0u; i < index; ++i) {
            it = it->next();
        }
        return it->data();
    }

    //! encontra dado
    std::size_t find(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Lista vazia!");
        }
        auto it = head;
        for (auto i = 0u; i < size_; ++i) {
            if (it->data() == data) {
                return i;
            }
            it = it->next();
        }
        return size_;
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
            data_{data},
            next_{next}
        {}

        Node(const T& data, Node* prev, Node* next):
            data_{data},
            prev_{prev},
            next_{next}
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

    Node* end() {  // último nodo da lista
        return head->prev();
    }
    Node* head;
    std::size_t size_;
};

}  // namespace structures

#endif
