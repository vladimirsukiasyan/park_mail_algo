#include <iostream>
#include <list>

int main() {
    int n,k;
    std::cin>>n>>k;

    int *rusRoulette=new int[n];
    for(int i=0;i<n;i++) rusRoulette[i]=i;

    int gunPoint=0, countOfAlive=n;
    while(true){
        if(countOfAlive==1){
            std::cout<<rusRoulette[0]+1;
            delete [] rusRoulette;
            return 0;
        }
        gunPoint=(gunPoint+k-1)%countOfAlive;
        for(int i=gunPoint;i<countOfAlive-1;i++){
            rusRoulette[i]=rusRoulette[i+1];
        }
        countOfAlive--;
    }
}