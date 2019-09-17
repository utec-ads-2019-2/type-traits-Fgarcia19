#ifndef SELF_LIST_H
#define SELF_LIST_H

#include "node.h"
using namespace std;

template <typename T>
class SelfList {
    public: 
        enum Method {
            Move, Count, Transpose
        };

    protected:
        Node<T>* head;
        Method method;
        int tamano;

    public:
        SelfList(Method method) : head(nullptr),tamano(0),method(method) {

        };

        bool insert(T data) {
            auto nuevo=new Node<T>(data);
            if(size()==0)
            {
                this->head=nuevo;
                nuevo->next= nullptr;
            }
            else{
                nuevo->next=this->head;
                this->head->prev=nuevo;
                this->head=nuevo;
            }
            tamano++;

        }
             
        bool remove(T data) {
            for(auto i=head;i!= nullptr;i=i->next)
            {
                if(i->data==data & i!=head & i->next!= nullptr) {
                    i->prev->next=i->next;
                    i->next->prev=i->prev;
                    delete i;
                    return true;
                }
                else if(i->data==data & i->next== nullptr){
                    i->prev->next= nullptr;
                    delete i;
                }
                else if(i->data==data & i==head){
                    head=head->next;
                    head->prev= nullptr;
                    delete i;
                }
                else
                    throw exception();
            }
            tamano--;
        }  

        bool find(T data) {
            bool encontrado=false;
            auto buscar=head;
            for(buscar;buscar!= nullptr;buscar=buscar->next){
                if(buscar->data==data) {
                    encontrado = true;
                    break;
                }
            }
            if(encontrado) {
                switch (method) {
                    case Move:
                        sort_move(buscar);
                        break;
                    case Count:
                        sort_count(buscar);
                        break;
                    case Transpose:
                        sort_transpose(buscar);
                        break;
                }
            }
            else throw exception();
        }

        T operator [] (int index) {
            auto aux=head;
            for(int i=0;i<index;i++){
                aux=aux->next;
            }
            return aux->data;
        }
             
        int size() {
            return tamano;
        }

        void print() {
            if(size()!=0) {
                for (auto i = head; i != nullptr; i=i->next)
                    cout << i->data << " ";
            }
            else throw exception();
        }

        ~SelfList() {
            head->killSelf();
        }

        void sort_move(Node<T>* i)
        {
            if(i!=head & i->next!= nullptr) {
                i->prev->next=i->next;
                i->next->prev=i->prev;
                i->next=head;
                i->prev= nullptr;
                head=i;
            }
            else if(i->next== nullptr){
                i->prev->next= nullptr;
                i->next=head;
                i->prev= nullptr;
                head=i;
            }
        }

        void sort_count(Node<T>* nodo)
        {
            nodo->count++;
            bool desordenado = true;
            while (desordenado) {
                desordenado=false;
                for (auto i=head; i->next!=nullptr;i=i->next) {
                    if (i->count < i->next->count)
                    {
                        int aux_data=i->data,aux_count=i->count;
                        i->count=i->next->count;
                        i->data=i->next->data;
                        i->next->data=aux_data;
                        i->next->count=aux_count;
                        desordenado=true;
                    }
                }
            }
        }

        void sort_transpose(Node<T>* nodo)
        {
            if(nodo!=head) {
                int aux = nodo->data;
                nodo->data = nodo->prev->data;
                nodo->prev->data = aux;
            }

        }

};

#endif