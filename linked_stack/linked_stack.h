//! Copyright [2017] <Geovani da Silva Júnior>
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include "./linked_list.h"

namespace structures {

template<typename T>
//! Classe pilha encadeada
/*
Classe herda atributos da lista encadeada tendo em vista as similariadades da implementação
*/
class LinkedStack: public LinkedList<T> {
 public:
    //! Construtor padrão da pilha encadeada
    LinkedStack(): top_{nullptr}, size_{0} {}

    //! Destrutor da pilha encadeada
    ~LinkedStack() {
        clear();
    }

    //! Limpa pilha encadeada
    void clear() {
        LinkedList<T>::clear();
    }

    //! adiciona dado no topo na pilha
    void push(const T& data) {
        LinkedList<T>::push_front(data);
    }

    //! Retira dado do topo da pilha
    T pop() {
        return LinkedList<T>::pop_front();
    }

    //! Informa o dado do topo da pilha sem altera-lo ou remove-lo
    T& top() const {
        return LinkedList<T>::at(0);
    }

    //! Vazio
    /*
    retorna se pilha encadeada está vazia
    */
    bool empty() const {
        return LinkedList<T>::empty();
    }
    //! tamanho
    /*
    retorna o tamanho atual da pilha encadeada
    */
    std::size_t size() const {
        return LinkedList<T>::size();
    }

 private:
    class Node {
     public:
        explicit Node(const T& data);
        Node(const T& data, Node* next);

        T& data();  // getter: info
        const T& data() const;  // getter-constante: info

        Node* next();  // getter: próximo
        const Node* next() const;  // getter-constante: próximo

        void next(Node* next);  // setter: próximo
     private:
        T data_;
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  // namespace structures

#endif
