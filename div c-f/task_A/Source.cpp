
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <list>

typedef std::list<long> CoefList;
typedef CoefList RootList;

/* getRoots() ���������� ������ ������ ����������.
   � ������ inputStr �������� ������������ ���������� - ����� �����,
   ����������� ����������� ��������� */
RootList getRoots(const std::string& inputStr);
// � ���� ���������� ������ ������������� �� ������ �������� � ��������
RootList getRoots(const CoefList& coefList);
// ���������� ������� �� ������� ���������� � �������������� coefList �� (x - x0)
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

    // ����������� �� ���������� �����
    while (!coefList.empty() && coefList.front() == 0)
        coefList.pop_front();

    return getRoots(coefList);
}

RootList getRoots(const CoefList& coefList)
{
    RootList rootsList; // ������ ������
    long a0 = abs(coefList.back()); // ������ ���������� �����
    const long MAX_A0_DIVISOR = a0 / 2; // ������������ �������� ���������� �����

    if (coefList.empty())
        // ���� ������ ���������
        return RootList();

    for (long a0_divisor = 1; a0_divisor <= MAX_A0_DIVISOR; ++a0_divisor)
    {
        if (a0 % a0_divisor != 0)
            // ���� �� ������� ������, �� ��� �� ������
            continue;

        // �������� ������
        if (getRest(coefList, a0_divisor) == 0)
            rootsList.push_back(a0_divisor);

        if (getRest(coefList, -a0_divisor) == 0)
            rootsList.push_back(-a0_divisor);
    }

    // �������� �� ������ ������ ������������ ���������� �����

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