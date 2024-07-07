#include <iostream>
#include <array>
#include <memory>
#include <algorithm>

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

    printf("%d", (255 | 200 | 100));

    return 0;
}