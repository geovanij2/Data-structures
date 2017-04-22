//! "Copyright [2017] <Geovani da Silva Junior>"
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
/*!
  classe que representa uma estrutura de dados estilo pilha
*/
class ArrayStack {
 public:
    //! Um construtor padrao
    /*!
      cria a pilha com tamanho padrao
    */
    ArrayStack() {
        max_size_ = DEFAULT_SIZE;
        contents = new T[max_size_];
        top_ = -1;
    }
    //! Um construtor
    /*!
      cria a pilha com tamanho escolhido    
    */
    explicit ArrayStack(std::size_t max) {
        max_size_ = max;
        contents = new T[max_size_];
        top_ = -1;
    }
    //! Destrutor
    ~ArrayStack() {
        delete[] contents;
    }
    //! empilha
    /*! recebe um dado do tipo T e o coloca no topo da pilha caso tenha espaço
    */
    void push(const T& data) {  // empilha
        if (full()) {
            throw std::out_of_range("stack full");
        }
        top_ += 1;
        contents[top_] = data;
    }
    //! desempilha
    /*!
     nenhum argumento e remove o dado do topo da pilha
     caso ela nao esteja vazia
    */
    T pop() {
		if(empty()) {
			throw std::out_of_range("stack empty");
		}
		top_ -= 1;
		return contents[top_ + 1];
	}
    //! topo
    /*!
      nenhum argumento e retorna o dado do tipo T do topo da pilha
    */
    T& top() {
        if (empty()) {
			throw std::out_of_range("stack empty");
		}
		return contents[top_];
    }
    //! limpa
    void clear() {
        top_ = -1;
    }
    //! retorna tamanho atual da pilha
    std::size_t size() {
        return top_ + 1;
    }
    //! retorna tamanho maximo da pilha
    std::size_t max_size() {
        return max_size_;
    }
    //! retorna um boolean verdadeiro se a pilha estver vazia
    bool empty() {
        return top_ == -1;
    }
    //! retorna um boolean verdadeiro se a pilha estiver cheia
    bool full() {  // cheia
        return (top_ == max_size() -1);
    }

 private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif
