
#ifndef MYTEST_HPP
#define MYTEST_HPP

#include "../container/container.hpp"

#include "../vector/vector.hpp"

#include "../list/list.hpp"

#include "../queue/queue.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../queue/vec/queuevec.hpp"

#include "../stack/stack.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../stack/vec/stackvec.hpp"

#include <iostream>

/* ************************************************************************** */


// Funzioni menu test

void menu();

template <typename Data>
void VectorTest(unsigned long, char);

template <typename Data>
void vecTestMenu(lasd::LinearContainer<Data>&);

template <typename Data>
void ListTest(unsigned long, char);

template <typename Data>
void listTestMenu(lasd::List<Data>&);

template <typename Data>
void QueueTest(unsigned long, char);

template <typename Data>
void QueueTestMenu(lasd::Queue<Data>&);

template <typename Data>
void StackTest(unsigned long, char);

template <typename Data>
void StackTestMenu(lasd::Stack<Data>&);


// Funzioni generiche

template <typename Data>
void elemTest(lasd::LinearContainer<Data>&);

template <typename Data>
void exitsTest(lasd::FoldableContainer<Data>&);

// Fold Test con funzioni accessorie 
void foldTest(lasd::FoldableContainer<int>&);

void foldTest(lasd::FoldableContainer<double>&);

void foldTest(lasd::FoldableContainer<std::string>&);

void foldSum(const int& dato, const void* parametro, void* accumulatore);

void foldProd(const double& dato, const void* parametro, void* accumulatore);

void foldConcat(const std::string& dato, const void* parametro, void* accumulatore);


// Map Test con funzioni accessorie
void specificTest(lasd::MappableContainer<int>& struttura);

void specificTest(lasd::MappableContainer<double>& struttura);

void specificTest(lasd::MappableContainer<std::string>& struttura);

template <typename Data>
void mapPrintDouble(Data&, void*);

void mapDouble(int& dato, void* parametro);

void mapPow(double& dato, void* parametro);

void mapUpperCase(std::string& dato, void* parametro);

template <typename Data>
void specificVecTest(lasd::Vector<Data>&);

template <typename Data>
void specificListTest(lasd::List<Data>&);


// Generatori Random
template <typename Data>
void intRandGenVec(lasd::LinearContainer<Data>&);

template <typename Data>
void doubleRandGenVec(lasd::LinearContainer<Data>&);

template <typename Data>
void stringRandGenVec(lasd::LinearContainer<Data>&);

template <typename Data>
void intRandGenList(lasd::List<Data>&, unsigned long);

template <typename Data>
void doubleRandGenList(lasd::List<Data>&, unsigned long);

template <typename Data>
void stringRandGenList(lasd::List<Data>&, unsigned long);

/* ************************************************************************** */

#endif
