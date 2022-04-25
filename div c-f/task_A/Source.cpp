
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <list>

typedef std::list<long> CoefList;
typedef CoefList RootList;

/* getRoots() возвращает список корней многочлена.
   В строке inputStr задаются коэффициенты многочлена - целые числа,
   разделенные пробельными символами */
RootList getRoots(const std::string& inputStr);
// а сюда передается список коэффициентов от самого страшего к младшему
RootList getRoots(const CoefList& coefList);
// возвращает остаток от деления многочлена с коэффициентами coefList на (x - x0)
long getRest(const CoefList& coefList, const long& x0);



int main()
{
    int N;
    RootList rootList;

    std::cin >> N;

    CoefList list;
    for (int i = 0; i < N; i++)
    {
        int tmp;
        std::cin >> tmp;
        list.push_back(tmp);
    }

    std::reverse(std::begin(list), std::end(list));


    rootList = getRoots(list);
    
    for (auto i : rootList)
    {
        if (i == 1)
        {
            std::cout << 1;
            return 0;
        }

        //else
        //{
        //    std::cout << 0;
        //    return 0;
        //}
    }

    std::cout << 0;

    return 0;
}

RootList getRoots(const std::string& inputStr)
{
    std::istringstream strStream(inputStr);
    CoefList coefList;
    long tmp;

    while (strStream >> tmp)
    {
        coefList.push_back(tmp);
    }

    // избавляемся от лидирующих нулей
    while (!coefList.empty() && coefList.front() == 0)
        coefList.pop_front();

    return getRoots(coefList);
}

RootList getRoots(const CoefList& coefList)
{
    RootList rootsList; // список корней
    long a0 = abs(coefList.back()); // модуль свободного члена
    const long MAX_A0_DIVISOR = a0 / 2; // максимальный делитель свободного члена

    if (coefList.empty())
        // если пустое уравнение
        return RootList();

    for (long a0_divisor = 1; a0_divisor <= MAX_A0_DIVISOR; ++a0_divisor)
    {
        if (a0 % a0_divisor != 0)
            // если не делится нацело, то это не корень
            continue;

        // проверка корней
        if (getRest(coefList, a0_divisor) == 0)
            rootsList.push_back(a0_divisor);

        if (getRest(coefList, -a0_divisor) == 0)
            rootsList.push_back(-a0_divisor);
    }

    // проверка на корень самого коэффициента свободного члена

    if (getRest(coefList, a0) == 0)
        rootsList.push_back(a0);

    if (getRest(coefList, -a0) == 0)
        rootsList.push_back(-a0);

    return rootsList;
}

long getRest(const CoefList& coefList, const long& x0)
{
    long rest = 0;

    for (CoefList::const_iterator i = coefList.begin(); i != coefList.end(); ++i)
    {
        rest = x0 * rest + (*i);
    }

    return rest;
}