#ifndef TRAITS_LIST_H
#define TRAITS_LIST_H

#include "node.h"

template <typename Tr>
class TraitsList {     
    public:
        typedef typename Tr::T T;
        typedef typename Tr::Operation Operation;
      
    private:
        Node<T>* head;
        Node<T>* tail;
        Operation cmp;
        int tamano;

        bool find(T data, Node<T> **&pointer) {
            for( pointer=&this->head;(*pointer)!= nullptr;pointer=&((*pointer)->next)){
                if((*pointer)->data==data){
                    return true;
                }
            }
            return false;
        }
              
    public:
        TraitsList() : tail(nullptr),head(nullptr),tamano(0){};
             
        bool insert(T data) {
            Node<T> **temp;
            if (size() != 0) {

                if (!this->find(data, temp)) {
                    tamano++;
                    auto nuevo = new Node<T>(data);
                    for (auto pointer = &this->head; (*pointer) != nullptr; pointer = &((*pointer)->next)) {
                        if(cmp(data,(*pointer)->data)){

                            if(pointer==&this->head){
                                this->head->prev=nuevo;
                                nuevo->next=this->head;
                                this->head=nuevo;

                                return  true;
                            }
                            else{
                                nuevo->prev=(*pointer)->prev;
                                nuevo->next=(*pointer);
                                (*pointer)->prev->next=nuevo;
                                (*pointer)->next->prev=nuevo;
                                return true;

                            }



                        }


                    }
                        this->tail->next=nuevo;
                        nuevo->prev=this->tail;
                        this->tail=nuevo;

                    return true;

                }
            }
            else {
                auto nuevo = new Node<T>(data);
                head = nuevo;
                head->next=tail;
                tail=nuevo;
                tamano++;
            }
        }
             
        bool remove(T data) {
            Node<T>** remover;
            if(find(data,remover)){
                if(remover==&this->head){
                    auto aux=this->head;
                    this->head=this->head->next;
                    this->head->prev= nullptr;
                    delete aux;
                }
                else if((*remover)->data==this->tail->data){
                    auto aux=this->tail;
                    this->tail=this->tail->prev;
                    this->tail->next= nullptr;
                    delete aux;
                }
                else {
                    auto aux = (*remover)->prev;
                    (*remover)->prev->next = (*remover)->next;
                    (*remover)->prev = aux;
                    delete remover;
                }
                tamano--;
            }

        }

        bool find(T data) {
            Node<T>** temp;
            this->find(data,temp);
        }

        T operator [] (int index) {
            // TODO
        }
             
        int size() {
            return tamano;
        }

        void print() {
            if(size()!=0) {
                for (auto i = head; i != nullptr; i=i->next)
                    cout << i->data << " ";
                cout<<endl;
                for (auto i = tail; i != nullptr; i=i->prev)
                    cout << i->data << " ";
                cout<<endl;
            }
            else throw exception();
        }

        ~TraitsList() {
            head->killSelf();
        }         
};

#endif