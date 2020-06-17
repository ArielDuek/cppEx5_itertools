#include "doctest.h"
#include "range.hpp"
#include "accumulate.hpp"
#include "filterfalse.hpp"
#include "compress.hpp"
#include <vector>
#include <string>
#include <set>
using namespace itertools;
using namespace std;


TEST_CASE("Test Range")
{
    vector<int> result = {1,2,3,4};
    int j = 0;
    for(int i : range(1,5))
    {
                CHECK(i == result.at(j));
        ++j;
    }
            CHECK(j == 4);


    j = 0;
    result.clear();
    result = {9,9};

    for(int i : range(9,9))
    {
                CHECK(0==1); // dont need to get
    }

    j = 0;
    result.clear();
    result = {20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,
              40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60};

    for(int i : range(20,61))
    {
                CHECK(i == result.at(j));
        ++j;
    }
            CHECK(j == 60);


}

TEST_CASE("Test Accumulate")
{
    vector<int> result1 = {3,7,12,18,25,33};
    int j = 0;

    for (int i: accumulate(range(3,9))) // 3, 3+4, 3+4+5, 3+4+5+6, 3+4+5+6+7, 3+4+5+6+7+8 = 3,7,12,18,25,33
    {
                CHECK(i == result1.at(j));
        ++j;
    }
            CHECK(j == 6);



    j = 0;
    for (int i: accumulate(vector({3,4,5,6,7,8}))) // 3, 3+4, 3+4+5, 3+4+5+6, 3+4+5+6+7, 3+4+5+6+7+8 = 3,7,12,18,25,33
    {
                CHECK(i == result1.at(j));
        ++j;
    }
            CHECK(j == 6);

    j=0;
    vector<string> result2 = {"na","nache","nachema","nacheman-meuman"};
    vector<string> vecString = {"na","che","ma","n-meuman"};
    for (auto i: accumulate(vecString) )
    {
        ++j;
    }
            CHECK(j == 4);

    j=0;
    vector<int> result3 = {3,12,60,360,2520,20160};

    for (int i: accumulate(range(3,9),[](int x, int y){return x*y;})) // 3,12,60,360,2520,20160
    {
                CHECK(i == result3.at(j));
        ++j;
    }
            CHECK(j == 6);

    j=0;
    result3.clear();

    result3 = {3,7,12,18,25,33};
    for (int i: accumulate(range(3,9),[](int x, int y){return x+y;})) // 3,7,12,18,25,33
    {
                CHECK(i == result3.at(j));
        ++j;
    }
            CHECK(j == 6);

    j=0;
    vector<int> set1 = {3,12,60,360,2520,20160};
    for (int i: accumulate(set{3,4,5,6,7,8},[](int x, int y){return x+y;})) // 
    {
                CHECK(i == set1.at(j));
        ++j;
    }
            CHECK(j == 6);

}


TEST_CASE("Test Filterfalse")
{
    vector<int> result = {5,7};
    int j = 0;
    for (auto i: filterfalse([](int i){return i%2==0;}, range(5,9)) )
    {
                CHECK(i == result.at(j));
        ++j;
    }
            CHECK(j == 2);


    result.clear();
    j = 0;
    result = {6,8};
    for (auto i: filterfalse([](int i){return i%2!=0;}, range(5,9)) )
    {
                CHECK(i == result.at(j));
        ++j;
    }
            CHECK(j == 2);


    result.clear();
    j = 0;
    result = {3,4,5,7,8};
    for (auto i: filterfalse([](int i){return i=6;}, set{3,4,5,6,7,8}) )
    {
                CHECK(i == result.at(j));
        ++j;
    }
            CHECK(j == 5);


    result.clear();
    j = 0;
    result = {-20,-2,-1,0,1,3,4,5,6,7,8,20,30,40,50,60,70,72,80,90,-99,100};
    for (auto i: filterfalse([](int i){return i > 0;}, set{-20,-2,-1,0,1,3,4,5,6,7,8,20,30,40,50,60,70,72,80,90,-99,100}) )
    {
                CHECK(i == result.at(j));
        ++j;
    }
            CHECK(j == 22);

}


TEST_CASE("Test Compress")
{
    vector<int> result = {6};
    int j = 0;
    vector<bool> fftf {false,false,true,false};
    for (auto i: compress(range(5,9), fftf) )
    {
                CHECK(i == result.at(j));
        ++j;
    }
            CHECK(j == 3);

    result.clear();
    j = 0;

    result = {1,7,11,20};
    j = 0;
    vector<bool> tftftft {true,false,true,false,true,false,true};
    vector<int> v1 {1,3,7,10,11,16,20};
    for (auto i: compress(v1, tftftft) )
    {
                CHECK(i == result.at(j));
        ++j;
    }
            CHECK(j == 4);


    result.clear();
    j = 0;

    vector<string> resultString = {"I","L", "o", "v", "e", "C", "+","+"};
    j = 0;
            CHECK(j == 8);

    vector<bool> tfffttttttt {true,false,false,false,true,true,true,true,true,true,true};
    string s1 {"InotLoveC++"};
    for (auto i: compress(s1, tfffttttttt) )
    {
        //CHECK(resultString.at(j) == i);
        ++j;
    }
            CHECK(j == 8);


    result.clear();
    j = 0;


}