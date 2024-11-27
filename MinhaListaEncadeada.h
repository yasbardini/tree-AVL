#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 *
 * @tparam T O tipo dos dados armazenados na lista.
 */
template <typename T>
class MinhaListaEncadeada : public ListaEncadeadaAbstrata<T>
{
    /**
     * @brief Destrutor. Destroi todos os elementos da lista
     */
    virtual ~MinhaListaEncadeada()
    {
        while (!vazia())
        {
            removerDoInicio();
        }
    }

    /**
     * @brief Obtém a quantidade de itens na lista.
     *
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const
    {
        // substitua a linha abaixo pelo algoritmo esperado
        return this->_tamanho;
    };

    /**
     * @brief Indica se há algum item na lista ou não.
     *
     * @return false se houver algum item na lista; true caso contrário.
     */
    virtual bool vazia() const
    {
        if (tamanho() == 0 && this->_primeiro == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    /**
     * @brief Obtém a posição de um item na lista. Lança
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     *
     * @param dado O item cuja posição deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posição da primeira ocorrência.
     */
    virtual std::size_t posicao(T dado) const
    {
        if (vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        else
        {
            Elemento<T> *proximo_ptr = this->_primeiro;

            for (size_t i = 0; i < tamanho(); i++)
            {
                if (proximo_ptr != nullptr)
                {
                    if (proximo_ptr->dado == dado)
                    {
                        return i;
                    }
                    proximo_ptr = proximo_ptr->proximo;
                }
            }
            throw ExcecaoDadoInexistente();
        }
    };

    /**
     * @brief Indica se um dado item está contido na lista ou não.
     *
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const
    {
        Elemento<T> *proximo_ptr = this->_primeiro;

        for (size_t i = 0; i < tamanho(); i++)
        {
            if (proximo_ptr != nullptr)
            {
                if (proximo_ptr->dado == dado)
                {
                    return true;
                }
                proximo_ptr = proximo_ptr->proximo;
            }
        }
        return false;
    };

    /**
     * @brief Insere um item no início da lista.
     *
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado)
    {
        if (vazia() == true)
        {
            this->_primeiro = new Elemento<T>{dado};
            this->_tamanho++;
        }
        else
        {
            Elemento<T> *novo_primeiro_ptr = new Elemento<T>{dado, this->_primeiro};
            this->_primeiro = novo_primeiro_ptr;
            this->_tamanho++;
        }
    };

    /**
     * @brief Insere um item em uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
     * [0, tamanho].
     *
     * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
     * uma posição já ocupada, a posição do item que já estava naquela posição
     * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
     * fim da lista.
     * @param dado O item sendo inserido.
     */
    virtual void inserir(std::size_t posicao, T dado)
    {
        if (posicao < 0 || posicao > tamanho())
        {
            throw ExcecaoPosicaoInvalida();
        }
        else if (posicao == 0)
        {
            inserirNoInicio(dado);
        }
        else
        {
            Elemento<T> *auxiliar_ptr = this->_primeiro;

            for (size_t i = 0; i < posicao - 1; i++)
            {
                auxiliar_ptr = auxiliar_ptr->proximo;
            }
            Elemento<T> *novo_ptr = new Elemento<T>{dado, auxiliar_ptr->proximo};

            auxiliar_ptr->proximo = novo_ptr;
            this->_tamanho++;
        }
    };

    /**
     * @brief Insere um item no fim da lista.
     *
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado)
    {
        if (vazia())
        {
            inserirNoInicio(dado);
        }
        else
        {
            inserir(tamanho(), dado);
        }
    };

    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     *
     * @return O item removido.
     */
    virtual T removerDoInicio()
    {
        if (vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        else
        {
            Elemento<T> *novo_ptr = this->_primeiro->proximo;

            T elemento = this->_primeiro->dado;

            delete this->_primeiro;

            this->_primeiro = novo_ptr;
            this->_tamanho--;

            return elemento;
        }
    };

    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     *
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao)
    {
        if (posicao < 0 || posicao >= tamanho())
        {
            throw ExcecaoPosicaoInvalida();
        }
        else if (posicao == 0)
        {
            return removerDoInicio();
        }
        else
        {
            Elemento<T> *auxiliar_ptr = this->_primeiro;
            for (size_t i = 0; i < posicao - 1; i++)
            {
                auxiliar_ptr = auxiliar_ptr->proximo;
            }

            T elemento = auxiliar_ptr->proximo->dado;

            Elemento<T> *auxiliar2_ptr = auxiliar_ptr->proximo;

            auxiliar_ptr->proximo = auxiliar_ptr->proximo->proximo;

            delete auxiliar2_ptr;

            this->_tamanho--;
            return elemento;
        }
    };

    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     *
     * @return O item removido.
     */
    virtual T removerDoFim()
    {
        if (vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        else
        {
            return removerDe(tamanho() - 1);
        }
    };

    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     *
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    virtual void remover(T dado)
    {
        if (vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        else if (!contem(dado))
        {
            throw ExcecaoDadoInexistente();
        }
        else
        {
            removerDe(posicao(dado));
        }
    };
};

#endif