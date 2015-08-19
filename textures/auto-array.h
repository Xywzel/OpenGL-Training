/*
 * This is a helper class for array memory managment
 */
#pragma once
#include <assert.h>
#include <fstream>

using namespace std;

template<class T>
class AutoArray {
    private:
        T* array;
        mutable bool released;
    public:
        explicit AutoArray(T* array_ = NULL): array(array_), released(false){}

        AutoArray(const AutoArray<T> &aa) {
            array = aa.array;
            released = aa.released;
            aa.released = true;
        }

        ~AutoArray() {
            if (!released && array != NULL) {
                delete[] array;
            }
        }

        T* get() const {
            return array;
        }

        T &operator*() const {
            return array;
        }

        void operator=(const AutoArray<T> aa) {
            if(!released && array != NULL) {
                delete[] array;
            }
            array = aa.array;
            released = aa.released;
            aa.released = true;
        }

        T* operator->() const {
            return array;
        }

        T* release() {
            released = true;
            return array;
        }

        void reset(T* array_ = NULL) {
            if (!released && array != NULL) {
                delete[] array;
            }
            array = array_;
        }

        T* operator+(int i){
            return array + i;
        }

        T& operator[](int i){
            return array[i];
        }
};
