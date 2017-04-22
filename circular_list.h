//! Copyright [2017] <Geovani da Silva Júnior>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {
//! Classe lista circular
template<typename T>
class CircularList {
 public:
    //! Construtor
    CircularList() {
        size_ = 0;
        head = new Node((T)NULL, nullptr);
        head->next(head);
    }

    //! Destrutor
    ~CircularList() {
        clear();
        delete head;
    }

    //! Limpa lista
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    //! Insere no fim
    void push_back(const T& data) {
        if (empty()) {
            return push_front(data);
        } else {
            Node* novo = new Node(data, head);
            if (novo == nullptr) {
                throw std::out_of_range("Erro lista cheia!");
            }
            end()->next(novo);
            ++size_;
        }
    }

    //! Insere no inicio
    void push_front(const T& data) {
        head->next(new Node(data, head->next()));
        ++size_;
    }

    //! insere na posição
    void insert(const T& data, std::size_t index) {
        if (index > size_) {
            throw std::out_of_range("Erro posição!");
        } else if (index == size_) {
            return push_back(data);
        } else if (index == 0) {
            return push_front(data);
        } else {
            Node* novo = new Node(data);
            if (novo == nullptr) {
                throw std::out_of_range("Erro lista cheia!");
            }
            auto previous = head->next();
            for (auto i = 1u; i < index; ++i) {
                previous = previous->next();
            }
            novo->next(previous->next());
            previous->next(novo);
            ++size_;
        }
    }

    //! inserir em ordem
    void insert_sorted(const T& data) {
        if (empty()) {
            return push_front(data);
        }
        Node* actual = head->next();
        auto i = 0u;
        while (i < size_ && actual->data() < data) {
            actual = actual->next();
            ++i;
        }
        return insert(data, i);
    }

    //! acessar um indice (com checagem de limites)
    T& at(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista vazio!");
        } else if (index >= size_) {
            throw std::out_of_range("Erro posição!");
        } else {
            auto it = head->next();
            for (auto i = 0u; i < index; ++i) {
                it = it->next();
            }
            return it->data();
        }
    }

    //! versão const do acesso ao indice
    const T& at(std::size_t index) const {
        auto it = head->next();
        for (auto i = 0u; i < index; ++i) {
            it = it->next();
        }
        return it->data();
    }

    //! retirar da posição
    T pop(std::size_t index) {
        if (index >= size()) {
            throw std::out_of_range("Erro posição!");
        }
        if (index == 0) {
            return pop_front();
        }
        auto it = head->next();
        for (auto i = 1u; i < index; ++i) {
            it = it->next();
        }
        auto del = it->next();
        auto data = del->data();
        it->next(del->next());
        --size_;
        delete del;
        return data;
    }

    //! retirar do fim
    T pop_back() {
        if (size() == 1) {
            return pop_front();
        }
        return pop(size() - 1);
    }

    //! retirar do inicio
    T pop_front() {
        if (empty()) {
            throw std::out_of_range("Erro lista vazia!");
        }
        T data = head->next()->data();
        auto del = head->next();
        head->next(del->next());
        delete del;
        --size_;
        return data;
    }

    //! remover dado especifico
    void remove(const T& data) {
        pop(find(data));
    }

    //! lista vazia
    bool empty() const {
        return size_ == 0;
    }

    //! lista contém determinado dado?
    bool contains(const T& data) const {
        if (find(data) == size()) {
            return false;
        }
        return true;
    }

    //! retorna posição de um item da lista
    std::size_t find(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Erro lista vazia!");
        }
        auto it = head->next();
        for (auto i = 0u; i < size(); ++i) {
            if (it->data() == data) {
                return i;
            }
            it = it->next();
        }
        return size_;
    }

    //! tamanho da lista
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
        auto it = head->next();
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }
    Node* head;
    std::size_t size_;
};

}  // namespace structures

#endif
