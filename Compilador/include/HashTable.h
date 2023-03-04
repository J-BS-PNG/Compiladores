#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Dictionary.h"
#include "KVPair.h"
#include "LinkedList.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;

template <typename K, typename V>
class HashTable : public Dictionary<K, V> {
private:
    LinkedList<KVPair<K, V> > *buckets;
    int nbuckets;

    int h(K key) {
        return compress(hashCodePolynomial(key));
    }
    // Genera un c�digo hash polinomial con constante de 33
    template <typename T>
    int hashCodePolynomial(T key) {
        int a = 33;
        int result = 0;
        char* bytes = reinterpret_cast<char*>(&key);
        for (unsigned int i = 0; i < sizeof(K); i++) {
            result += bytes[i] * pow(a, i);
        }
        return result;
    }
    int hashCodePolynomial(string key) {
        int a = 33;
        int result = 0;
        for (unsigned int i = 0; i < key.length(); i++) {
            result += key[i] * pow(a, i);
        }
        return result;
    }
    // Funci�n de compresi�n por multiplicaci�n, suma y divisi�n
    int compress(int hashCode) {
        int a = 1097;
        int b = 1279;
        return abs(a * hashCode + b) % nbuckets;
    }
    // M�todo auxiliar que verifica que una llave no exista.
    // Si se encuentra la llave, lanza exepci�n.
    // La posici�n actual de la lista queda se�alando al final
    // de la lista.
    void checkNotExisting(K key) throw (runtime_error) {
        if (buckets[h(key)].contains(key))
            throw runtime_error("Duplicated key.");
    }
    // M�todo auxiliar que verifica que una llave s� exista.
    // Si no se encuentra la llave, lanza excepci�n
    // La posici�n actual de la lista queda se�alando al
    // elemento buscado.
    void checkExisting(K key) throw (runtime_error) {
        if (!buckets[h(key)].contains(key)) {
            throw runtime_error("Key not found.");
        }
    }

public:
    HashTable(int nbuckets = 1021) {
        buckets = new LinkedList<KVPair<K, V> >[nbuckets];
        this->nbuckets = nbuckets;
    }
    ~HashTable() {
        delete [] buckets;
    }
    void insert(K key, V value) {
        checkNotExisting(key);
        KVPair<K, V> p(key, value);
        buckets[h(key)].append(p);
    }
    V remove(K key) {
        checkExisting(key);
        KVPair<K, V> p(key);
        p = buckets[h(key)].remove();
        return p.getValue();
    }
    V getValue(K key) {
        checkExisting(key);
        KVPair<K, V> p = buckets[h(key)].getElement();
        return p.getValue();
    }
    void setValue(K key, V value) {
        checkExisting(key);
        buckets[h(key)].remove();
        KVPair<K, V> p(key, value);
        buckets[h(key)].append(p);
    }
    void clear() {
        for (int i = 0; i < nbuckets; i++) {
            buckets[i].clear();
        }
    }
    bool contains(K key) {
        KVPair<K, V> p(key);
        return buckets[h(key)].contains(p);
    }
    List<K>* getKeys() {
        List<K> *keys = new LinkedList<K>();
        KVPair<K,V> p;
        for(int i = 0; i < nbuckets; i++){
            buckets[i].goToStart();
            while(!buckets[i].atEnd()){
                p = buckets[i].getElement();
                keys->append(p.getKey());
                buckets[i].next();
            }
            buckets[i].goToStart();
        }
        return keys;
    }
    List<V>* getValues() {
        List<V> *values = new LinkedList<V>();
        KVPair<K, V> p;
        for(int i = 0; i < nbuckets; i++){
            buckets[i].goToStart();
            while(!buckets[i].atEnd()){
                p = buckets[i].getElement();
                values->append(p.getValue());
                buckets[i].next();
            }
            buckets[i].goToStart();
        }
        return values;
    }
    int getSize() {
        int size = 0;
        for(int i = 0; i < nbuckets; i++){
            size += buckets[i].getSize();
        }
        return size;
    }
    void update(Dictionary<K, V> *D) {
        List<K> *keys = D->getKeys();
        K key;
        for(keys->goToStart(); !keys->atEnd(); keys->next()){
            key = keys->getElement();
            if(buckets[h(key)].contains(key))
                setValue(key, D->getValue(key));
            else
                insert(key, D->getValue(key));
        }
    }
    void zip(List<K> *keys, List<V> *values) {
        int sizeList = (keys->getSize() < values->getSize())? keys->getSize() : values->getSize();
        keys->goToStart();
        values->goToStart();
        for(int i = 0; i < sizeList; i++){
            insert(keys->getElement(), values->getElement());
            keys->next();
            values->next();
        }
    }
};

#endif // HASHTABLE_H
