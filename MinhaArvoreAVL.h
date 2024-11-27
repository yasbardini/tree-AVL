#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"

/**
 * @brief Representa uma árvore AVL.
 *
 * @tparam T O tipo de dado guardado na árvore.
 */

template <typename T>

class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
    virtual ~MinhaArvoreAVL()
    {
        destrutorR(this->raiz) ;

    };

    void destrutorR(Nodo<T> *raiz)
    {
        if(raiz != nullptr)
        {
            destrutorR(raiz->filhoDireita) ;
            destrutorR(raiz->filhoEsquerda) ;
            delete raiz ;
        }
    }

    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */

    virtual bool vazia() const
    {
        if (this->raiz == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */

    virtual int quantidade() const
    {
        if (this->raiz == nullptr)
        {
            return 0;
        }
        else
        {
            return 1 + quantidadeRecursiva(this->raiz->filhoDireita) + quantidadeRecursiva(this->raiz->filhoEsquerda);
        }
    };

    int quantidadeRecursiva(Nodo<T> *novaRaiz) const
    {
        if (novaRaiz == nullptr)
        {
            return 0;
        }
        else
        {
            return 1 + quantidadeRecursiva(novaRaiz->filhoDireita) + quantidadeRecursiva(novaRaiz->filhoEsquerda);
        }
    }

    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */

    virtual bool contem(T chave) const
    {
        Nodo<T> *novaRaiz = this->raiz;

        while (novaRaiz != nullptr)
        {
            if (novaRaiz->chave == chave)
            {
                return true;
            }
            if (chave < novaRaiz->chave)
            {
                novaRaiz = novaRaiz->filhoEsquerda;
            }
            else if (chave > novaRaiz->chave)
            {
                novaRaiz = novaRaiz->filhoDireita;
            }
        }

        return false;
    };

    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */

    virtual std::optional<int> altura(T chave) const
    {
        if (contem(!chave))
        {
            return std::nullopt;
        }
        else
        {
            Nodo<T> *novaRaiz = this->raiz;

            while (novaRaiz != nullptr)
            {
                if (novaRaiz->chave == chave)
                {
                    return novaRaiz->altura;
                }
                if (chave < novaRaiz->chave)
                {
                    novaRaiz = novaRaiz->filhoEsquerda;
                }
                else if (chave > novaRaiz->chave)
                {
                    novaRaiz = novaRaiz->filhoDireita;
                }
            }
            return std::nullopt;
        }
    };

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */

    virtual void inserir(T chave) override
    {
        int bPai = 0;
        int bFilho = 0;

        if (this->raiz == nullptr)
        {
            //new Nodo<T>{chave};
            //Nodo<T>* nodo = new Nodo<T>{chave}; 
            this->raiz = new Nodo<T>{chave};
            //this->raiz = nodo;
        }
        else
        {
            inserirRecursiva(chave, this->raiz, this->raiz);
        }

        bPai = getAltura(this->raiz->filhoEsquerda) - getAltura(this->raiz->filhoDireita);

        if (bPai == -2)
        {
            bFilho = getAltura(this->raiz->filhoDireita->filhoEsquerda) - getAltura(this->raiz->filhoDireita->filhoDireita);

            if (bFilho <= 0)
            {
                rotacaoSimplesEsquerda(this->raiz, this->raiz);
            }
            else if (bFilho > 0)
            {
                rotacaoDireitaEsquerda(this->raiz, this->raiz);
            }
        }
        else if (bPai == 2)
        {
            bFilho = getAltura(this->raiz->filhoEsquerda->filhoEsquerda) - getAltura(this->raiz->filhoEsquerda->filhoDireita);

            if (bFilho >= 0)
            {
                rotacaoSimplesDireita(this->raiz, this->raiz);
            }
            else if (bFilho < 0)
            {
                rotacaoEsquerdaDireita(this->raiz, this->raiz);
            }
        }
    };

    void inserirRecursiva(T chave, Nodo<T> *novaRaiz, Nodo<T> *paiRaiz)
    {
        int bPai = 0;
        int bFilho = 0;

        if (chave < novaRaiz->chave)
        {
            if (novaRaiz->filhoEsquerda == nullptr)
            {
                novaRaiz->filhoEsquerda = new Nodo<T>{chave};
            }
            else
            {
                inserirRecursiva(chave, novaRaiz->filhoEsquerda, novaRaiz);
            }

            bPai = getAltura(novaRaiz->filhoEsquerda->filhoEsquerda) - getAltura(novaRaiz->filhoEsquerda->filhoDireita);

            if (bPai == -2)
            {
                bFilho = getAltura(novaRaiz->filhoEsquerda->filhoDireita->filhoEsquerda) - getAltura(novaRaiz->filhoEsquerda->filhoDireita->filhoDireita);

                if (bFilho <= 0)
                {
                    rotacaoSimplesEsquerda(novaRaiz->filhoEsquerda, novaRaiz);
                }
                else if (bFilho > 0)
                {
                    rotacaoDireitaEsquerda(novaRaiz->filhoEsquerda, novaRaiz);
                }
            }
            else if (bPai == 2)
            {
                bFilho = getAltura(novaRaiz->filhoEsquerda->filhoEsquerda->filhoEsquerda) - getAltura(novaRaiz->filhoEsquerda->filhoEsquerda->filhoDireita);

                if (bFilho >= 0)
                {
                    rotacaoSimplesDireita(novaRaiz->filhoEsquerda, novaRaiz);
                }
                else if (bFilho < 0)
                {
                    rotacaoEsquerdaDireita(novaRaiz->filhoEsquerda, novaRaiz);
                }
            }
        }
        else
        {
            if (novaRaiz->filhoDireita == nullptr)
            {
                novaRaiz->filhoDireita = new Nodo<T>{chave};
            }
            else
            {
                inserirRecursiva(chave, novaRaiz->filhoDireita, novaRaiz);
            }

            bPai = getAltura(novaRaiz->filhoDireita->filhoEsquerda) - getAltura(novaRaiz->filhoDireita->filhoDireita);

            if (bPai == -2)
            {
                bFilho = getAltura(novaRaiz->filhoDireita->filhoDireita->filhoEsquerda) - getAltura(novaRaiz->filhoDireita->filhoDireita->filhoDireita);

                if (bFilho <= 0)
                {
                    rotacaoSimplesEsquerda(novaRaiz->filhoDireita, novaRaiz);
                }
                else if (bFilho > 0)
                {
                    rotacaoDireitaEsquerda(novaRaiz->filhoDireita, novaRaiz);
                }
            }
            else if (bPai == 2)
            {
                bFilho = getAltura(novaRaiz->filhoDireita->filhoEsquerda->filhoEsquerda) - getAltura(novaRaiz->filhoDireita->filhoEsquerda->filhoDireita);

                if (bFilho >= 0)
                {
                    rotacaoSimplesDireita(novaRaiz->filhoDireita, novaRaiz);
                }
                else if (bFilho < 0)
                {
                    rotacaoEsquerdaDireita(novaRaiz->filhoDireita, novaRaiz);
                }
            }
        }

        novaRaiz->altura = std::max(getAltura(novaRaiz->filhoDireita), getAltura(novaRaiz->filhoEsquerda)) + 1;
    }

    int getAltura(Nodo<T> *novaRaiz)
    {

        if (novaRaiz == nullptr)
        {
            return -1;
        }
        else
        {
            return novaRaiz->altura;
        }
    }

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     */

    virtual void remover(T chave)
    {
        int bPai = 0;
        int bFilho = 0;

        Nodo<T> *paiRaiz = this->raiz;
        Nodo<T> *novaRaiz = this->raiz;

        while (contem(chave))
        {
            if (novaRaiz->chave == chave)
            {
                removerRecursiva(chave, novaRaiz, paiRaiz);
                if (this->raiz != nullptr)
                {
                    this->raiz->altura = std::max(getAltura(this->raiz->filhoDireita), getAltura(this->raiz->filhoEsquerda)) + 1;

                    bPai = getAltura(this->raiz->filhoEsquerda) - getAltura(this->raiz->filhoDireita);

                    if (bPai == -2)
                    {
                        bFilho = getAltura(this->raiz->filhoDireita->filhoEsquerda) - getAltura(this->raiz->filhoDireita->filhoDireita);

                        if (bFilho <= 0)
                        {
                            rotacaoSimplesEsquerda(this->raiz, this->raiz);
                        }
                        else if (bFilho > 0)
                        {
                            rotacaoDireitaEsquerda(this->raiz, this->raiz);
                        }
                    }
                    else if (bPai == 2)
                    {
                        bFilho = getAltura(this->raiz->filhoEsquerda->filhoEsquerda) - getAltura(this->raiz->filhoEsquerda->filhoDireita);

                        if (bFilho >= 0)
                        {
                            rotacaoSimplesDireita(this->raiz, this->raiz);
                        }
                        else if (bFilho < 0)
                        {
                            rotacaoEsquerdaDireita(this->raiz, this->raiz);
                        }
                    }
                }
            }
            else if (chave < novaRaiz->chave)
            {
                paiRaiz = novaRaiz;
                novaRaiz = novaRaiz->filhoEsquerda;
            }
            else if (chave > novaRaiz->chave)
            {
                paiRaiz = novaRaiz;
                novaRaiz = novaRaiz->filhoDireita;
            }
        }
    };

    void removerRecursiva(T chave, Nodo<T> *novaRaiz, Nodo<T> *paiRaiz)
    {
        int bPai = 0;
        int bFilho = 0;

        if (novaRaiz->filhoDireita == nullptr && novaRaiz->filhoEsquerda == nullptr)
        {
            if (paiRaiz != novaRaiz)
            {
                if (paiRaiz->chave <= novaRaiz->chave)
                {
                    delete paiRaiz->filhoDireita;
                    paiRaiz->filhoDireita = nullptr;
                    paiRaiz->altura = std::max(getAltura(paiRaiz->filhoDireita), getAltura(paiRaiz->filhoEsquerda)) + 1;
                }
                else
                {
                    delete paiRaiz->filhoEsquerda;
                    paiRaiz->filhoEsquerda = nullptr;
                    paiRaiz->altura = std::max(getAltura(paiRaiz->filhoDireita), getAltura(paiRaiz->filhoEsquerda)) + 1;
                }
            }
            else
            {
                delete this->raiz;
                //this->raiz->altura = 0;
                this->raiz = nullptr;
            }
        }
        else if (novaRaiz->filhoDireita == nullptr && novaRaiz->filhoEsquerda != nullptr)
        {

            novaRaiz->chave = novaRaiz->filhoEsquerda->chave;
            removerRecursiva(novaRaiz->chave, novaRaiz->filhoEsquerda, novaRaiz);
            novaRaiz->altura = std::max(getAltura(novaRaiz->filhoEsquerda->filhoDireita), getAltura(novaRaiz->filhoEsquerda->filhoEsquerda)) + 1;

            bPai = getAltura(novaRaiz->filhoEsquerda) - getAltura(novaRaiz->filhoDireita);

            if (bPai == -2)
            {
                bFilho = getAltura(novaRaiz->filhoDireita->filhoEsquerda) - getAltura(novaRaiz->filhoDireita->filhoDireita);

                if (bFilho <= 0)
                {
                    rotacaoSimplesEsquerda(novaRaiz, paiRaiz);
                }
                else if (bFilho > 0)
                {
                    rotacaoDireitaEsquerda(novaRaiz, paiRaiz);
                }
            }
            else if (bPai == 2)
            {
                bFilho = getAltura(novaRaiz->filhoEsquerda->filhoEsquerda) - getAltura(novaRaiz->filhoEsquerda->filhoDireita);

                if (bFilho >= 0)
                {
                    rotacaoSimplesDireita(novaRaiz, paiRaiz);
                }
                else if (bFilho < 0)
                {
                    rotacaoEsquerdaDireita(novaRaiz, paiRaiz);
                }
            }
        }
        else if (novaRaiz->filhoDireita != nullptr)
        {
            if (novaRaiz->filhoDireita->filhoEsquerda != nullptr)
            {
                novaRaiz->chave = novaRaiz->filhoDireita->filhoEsquerda->chave;
                removerRecursiva(novaRaiz->chave, novaRaiz->filhoDireita->filhoEsquerda, novaRaiz->filhoDireita);
                novaRaiz->filhoDireita->altura = std::max(getAltura(novaRaiz->filhoDireita->filhoEsquerda), getAltura(novaRaiz->filhoDireita->filhoDireita)) + 1;
                novaRaiz->altura = std::max(getAltura(novaRaiz->filhoDireita), getAltura(novaRaiz->filhoEsquerda)) + 1;

                bPai = getAltura(novaRaiz->filhoDireita->filhoEsquerda) - getAltura(novaRaiz->filhoDireita->filhoDireita);

                if (bPai == -2)
                {
                    bFilho = getAltura(novaRaiz->filhoDireita->filhoDireita->filhoEsquerda) - getAltura(novaRaiz->filhoDireita->filhoDireita->filhoDireita);

                    if (bFilho <= 0)
                    {
                        rotacaoSimplesEsquerda(novaRaiz->filhoDireita, novaRaiz);
                    }
                    else if (bFilho > 0)
                    {
                        rotacaoDireitaEsquerda(novaRaiz->filhoDireita, novaRaiz);
                    }
                }
                else if (bPai == 2)
                {
                    bFilho = getAltura(novaRaiz->filhoDireita->filhoEsquerda->filhoEsquerda) - getAltura(novaRaiz->filhoDireita->filhoEsquerda->filhoDireita);

                    if (bFilho >= 0)
                    {
                        rotacaoSimplesDireita(novaRaiz->filhoDireita, novaRaiz);
                    }
                    else if (bFilho < 0)
                    {
                        rotacaoEsquerdaDireita(novaRaiz->filhoDireita, novaRaiz);
                    }
                }
            }
            else
            {
                novaRaiz->chave = novaRaiz->filhoDireita->chave;
                removerRecursiva(novaRaiz->chave, novaRaiz->filhoDireita, novaRaiz);
                novaRaiz->altura = std::max(getAltura(novaRaiz->filhoDireita), getAltura(novaRaiz->filhoEsquerda)) + 1;

                bPai = getAltura(novaRaiz->filhoEsquerda) - getAltura(novaRaiz->filhoDireita);

                if (bPai == -2)
                {
                    bFilho = getAltura(novaRaiz->filhoDireita->filhoEsquerda) - getAltura(novaRaiz->filhoDireita->filhoDireita);

                    if (bFilho <= 0)
                    {
                        rotacaoSimplesEsquerda(novaRaiz, paiRaiz);
                    }
                    else if (bFilho > 0)
                    {
                        rotacaoDireitaEsquerda(novaRaiz, paiRaiz);
                    }
                }
                else if (bPai == 2)
                {
                    bFilho = getAltura(novaRaiz->filhoEsquerda->filhoEsquerda) - getAltura(novaRaiz->filhoEsquerda->filhoDireita);

                    if (bFilho >= 0)
                    {
                        rotacaoSimplesDireita(novaRaiz, paiRaiz);
                    }
                    else if (bFilho < 0)
                    {
                        rotacaoEsquerdaDireita(novaRaiz, paiRaiz);
                    }
                }
            }
        }
    }

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoEsquerdaDe(T chave) const
    {
        if (contem(chave))
        {
            Nodo<T> *novaRaiz = this->raiz;

            while (novaRaiz != nullptr)
            {
                if (novaRaiz->chave == chave)
                {
                    if (novaRaiz->filhoEsquerda == nullptr)
                    {
                        return std::nullopt;
                    }
                    else
                    {
                        return novaRaiz->filhoEsquerda->chave;
                    }
                }
                if (chave < novaRaiz->chave)
                {
                    novaRaiz = novaRaiz->filhoEsquerda;
                }
                else if (chave > novaRaiz->chave)
                {
                    novaRaiz = novaRaiz->filhoDireita;
                }
            }
        }

        return std::nullopt;
    };

    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */
    virtual std::optional<T> filhoDireitaDe(T chave) const
    {
        if (contem(chave))
        {
            Nodo<T> *novaRaiz = this->raiz;

            while (novaRaiz != nullptr)
            {
                if (novaRaiz->chave == chave)
                {
                    if (novaRaiz->filhoDireita == nullptr)
                    {
                        return std::nullopt;
                    }
                    else
                    {
                        return novaRaiz->filhoDireita->chave;
                    }
                }
                if (chave < novaRaiz->chave)
                {
                    novaRaiz = novaRaiz->filhoEsquerda;
                }
                else if (chave > novaRaiz->chave)
                {
                    novaRaiz = novaRaiz->filhoDireita;
                }
            }
        }

        return std::nullopt;
    };

    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *emOrdem() const
    {
        MinhaListaEncadeada<T> *minhaLista = new MinhaListaEncadeada<T>{};

        if (this->raiz != nullptr)
        {
            emOrdemRecursiva(this->raiz, minhaLista);
        }
        return minhaLista;
    };

    void emOrdemRecursiva(Nodo<T> *novaRaiz, ListaEncadeadaAbstrata<T> *minhaLista) const
    {
        if (novaRaiz->filhoEsquerda != nullptr)
        {
            emOrdemRecursiva(novaRaiz->filhoEsquerda, minhaLista);
        }
        if (novaRaiz != nullptr)
        {
            minhaLista->inserirNoFim(novaRaiz->chave);
        }
        if (novaRaiz->filhoDireita != nullptr)
        {
            emOrdemRecursiva(novaRaiz->filhoDireita, minhaLista);
        }
    }

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem.
     */

    virtual ListaEncadeadaAbstrata<T> *preOrdem() const
    {
        MinhaListaEncadeada<T> *minhaLista = new MinhaListaEncadeada<T>{};

        if (this->raiz != nullptr)
        {
            preOrdemRecursiva(this->raiz, minhaLista);
        }
        return minhaLista;
    };

    void preOrdemRecursiva(Nodo<T> *novaRaiz, ListaEncadeadaAbstrata<T> *minhaLista) const
    {
        if (novaRaiz != nullptr)
        {
            minhaLista->inserirNoFim(novaRaiz->chave);

            if (novaRaiz->filhoEsquerda != nullptr)
            {
                preOrdemRecursiva(novaRaiz->filhoEsquerda, minhaLista);
            }
            if (novaRaiz->filhoDireita != nullptr)
            {
                preOrdemRecursiva(novaRaiz->filhoDireita, minhaLista);
            }
        }
    }

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem.
     */

    virtual ListaEncadeadaAbstrata<T> *posOrdem() const
    {
        MinhaListaEncadeada<T> *minhaLista = new MinhaListaEncadeada<T>{};

        if (this->raiz != nullptr)
        {
            posOrdemRecursiva(this->raiz, minhaLista);
        }
        return minhaLista;
    };

    void posOrdemRecursiva(Nodo<T> *novaRaiz, ListaEncadeadaAbstrata<T> *minhaLista) const
    {
        if (novaRaiz->filhoEsquerda != nullptr)
        {
            posOrdemRecursiva(novaRaiz->filhoEsquerda, minhaLista);
        }
        if (novaRaiz->filhoDireita != nullptr)
        {
            posOrdemRecursiva(novaRaiz->filhoDireita, minhaLista);
        }
        if (novaRaiz != nullptr)
        {
            minhaLista->inserirNoFim(novaRaiz->chave);
        }
    }

    void rotacaoSimplesDireita(Nodo<T> *novaRaiz, Nodo<T> *paiRaiz)
    {
        Nodo<T> *nodoA = novaRaiz;
        Nodo<T> *nodoB = novaRaiz->filhoEsquerda;

        nodoA->filhoEsquerda = nodoB->filhoDireita;
        nodoB->filhoDireita = nodoA;

        if (paiRaiz == novaRaiz)
        {
            this->raiz = nodoB;
        }
        else if (paiRaiz->chave > nodoB->chave)
        {
            paiRaiz->filhoEsquerda = nodoB;
        }
        else
        {
            paiRaiz->filhoDireita = nodoB;
        }

        nodoA->altura = std::max(getAltura(nodoA->filhoDireita), getAltura(nodoA->filhoEsquerda)) + 1;
        nodoB->altura = std::max(getAltura(nodoB->filhoDireita), getAltura(nodoB->filhoEsquerda)) + 1;
        paiRaiz->altura = std::max(getAltura(paiRaiz->filhoDireita), getAltura(paiRaiz->filhoEsquerda)) + 1;
    }

    void rotacaoSimplesEsquerda(Nodo<T> *novaRaiz, Nodo<T> *paiRaiz)
    {
        Nodo<T> *nodoA = novaRaiz;
        Nodo<T> *nodoC = novaRaiz->filhoDireita;

        nodoA->filhoDireita = nodoC->filhoEsquerda;
        nodoC->filhoEsquerda = nodoA;

        if (paiRaiz == novaRaiz)
        {
            this->raiz = nodoC;
        }
        else if (paiRaiz->chave < nodoC->chave)
        {
            paiRaiz->filhoDireita = nodoC;
        }
        else
        {
            paiRaiz->filhoEsquerda = nodoC;
        }

        nodoA->altura = std::max(getAltura(nodoA->filhoDireita), getAltura(nodoA->filhoEsquerda)) + 1;
        nodoC->altura = std::max(getAltura(nodoC->filhoDireita), getAltura(nodoC->filhoEsquerda)) + 1;
        paiRaiz->altura = std::max(getAltura(paiRaiz->filhoDireita), getAltura(paiRaiz->filhoEsquerda)) + 1;
    }

    void rotacaoEsquerdaDireita(Nodo<T> *novaRaiz, Nodo<T> *paiRaiz)
    {
        Nodo<T> *nodoA = novaRaiz;
        Nodo<T> *nodoB = novaRaiz->filhoEsquerda;
        Nodo<T> *nodoE = novaRaiz->filhoEsquerda->filhoDireita;

        nodoB->filhoDireita = nodoE->filhoEsquerda;
        nodoE->filhoEsquerda = nodoB;
        nodoA->filhoEsquerda = nodoE;
        nodoA->filhoEsquerda = nodoE->filhoDireita;
        nodoE->filhoDireita = nodoA;

        if (paiRaiz == novaRaiz)
        {
            this->raiz = nodoE;
        }
        else if (paiRaiz->chave > nodoE->chave)
        {
            paiRaiz->filhoEsquerda = nodoE;
        }
        else
        {
            paiRaiz->filhoDireita = nodoE;
        }

        nodoA->altura = std::max(getAltura(nodoA->filhoDireita), getAltura(nodoA->filhoEsquerda)) + 1;
        nodoB->altura = std::max(getAltura(nodoB->filhoDireita), getAltura(nodoB->filhoEsquerda)) + 1;
        nodoE->altura = std::max(getAltura(nodoE->filhoDireita), getAltura(nodoE->filhoEsquerda)) + 1;
        paiRaiz->altura = std::max(getAltura(paiRaiz->filhoDireita), getAltura(paiRaiz->filhoEsquerda)) + 1;
    }

    void rotacaoDireitaEsquerda(Nodo<T> *novaRaiz, Nodo<T> *paiRaiz)
    {
        Nodo<T> *nodoA = novaRaiz;
        Nodo<T> *nodoC = novaRaiz->filhoDireita;
        Nodo<T> *nodoD = novaRaiz->filhoDireita->filhoEsquerda;

        nodoC->filhoEsquerda = nodoD->filhoDireita;
        nodoD->filhoDireita = nodoC;
        nodoA->filhoDireita = nodoD;
        nodoA->filhoDireita = nodoD->filhoEsquerda;
        nodoD->filhoEsquerda = nodoA;

        if (paiRaiz == novaRaiz)
        {
            this->raiz = nodoD;
        }
        else if (paiRaiz->chave < nodoD->chave)
        {
            paiRaiz->filhoDireita = nodoD;
        }
        else
        {
            paiRaiz->filhoEsquerda = nodoD;
        }

        nodoA->altura = std::max(getAltura(nodoA->filhoDireita), getAltura(nodoA->filhoEsquerda)) + 1;
        nodoC->altura = std::max(getAltura(nodoC->filhoDireita), getAltura(nodoC->filhoEsquerda)) + 1;
        nodoD->altura = std::max(getAltura(nodoD->filhoDireita), getAltura(nodoD->filhoEsquerda)) + 1;
        paiRaiz->altura = std::max(getAltura(paiRaiz->filhoDireita), getAltura(paiRaiz->filhoEsquerda)) + 1;
    }
};

#endif