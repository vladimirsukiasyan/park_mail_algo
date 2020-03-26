#include <iostream>
#include <list>

using namespace std;


int main() {
    int n,k;
    cin>>n>>k;
    list <int> rusRoulette;

    for(int i=0;i<n;i++) rusRoulette.push_back(i);
    int countOfDead=0;

    auto iter=rusRoulette.begin();
    while(true){
        if(countOfDead==n-1){
            cout<<*rusRoulette.begin()+1;
            return 0;
        }
        //Detect iterator's position;
        int iterPos=1;
        auto beg=rusRoulette.begin();
        while(*beg!=*iter) {
            iterPos++;
            beg++;
        }

        int countOfElemUntilEnd=(int)rusRoulette.size()-iterPos+1;
        if(countOfElemUntilEnd<k){
            iter=rusRoulette.begin();
            advance(iter,k-countOfElemUntilEnd-1);
        }
        else advance(iter,k-1);

        auto eraseIter=iter;
        iter++;
        rusRoulette.erase(eraseIter);
        countOfDead++;
    }
}