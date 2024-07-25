#include <iostream>
#include <array>
#include <memory>
#include <algorithm>
#include <map>
#include "functional"

struct S
{
    std::string s;

    S(){
        s = "BRUHHH\n";
    }
};

void glotaet(S& s){

}

int main(){

    // std::array<std::shared_ptr<S>, 3> arr;

    // std::for_each(arr.begin(), arr.end(), [](auto& elem){
    //     elem = std::shared_ptr<S>(new S());
    // });

    // std::for_each(arr.begin(), arr.end(), [](auto& elem){
    //     std::cout << (*elem).s << '\n';
    // });

    /////////////////

    // std::unique_ptr<S> ptr(new S());
    // std::unique_ptr<S> player = std::unique_ptr<S>(ptr.get());

    // glotaet(*ptr);

    // std::cout << player->s << '\n';

    /////////////////

    // printf("%d", (255 | 200 | 100));

    /////////////////

    // std::array<int, 5> arr{1,2,3,4,5};
    // std::for_each(arr.rbegin(), arr.rend(), [](auto num){
    //     printf("%d", num);
    // });

    /////////////////

    int x = -1;
    std::cout << (x-1) % 2 << '\n';

    return 0;
}