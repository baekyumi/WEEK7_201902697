#include <iostream>
#include <stdexcept>

class Test {
public:
    Test(char id) : id_(id) {}
    ~Test() {
        std::cout << "Destructor execution: "
            << id_ << std::endl;
    }
private:
    char id_;
};

int funcB() {
    Test r('B');
    throw std::runtime_error("Exception from funcB!\n");
    std::cout << "Executed in B" << std::endl;
    return 0;
}

int funcA() {
    Test r('A');
    funcB();
    std::cout << "Executed in A" << std::endl;
    return 0;
}

int main() {
    try {
        funcA();
    }
    catch (std::exception& e) {
        std::cout << "Exception : " << e.what();
    }
}

/*
   main함수에서 funcA호출하여 id가 A인 Test 객체 생성.
   funcB호출하여 id가 B인 Test 객체 생성.
   Executed in B 메시지 출력 후 funcB return.
   파괴자 실행됨. Destructor execution B 메시지 출력. Test B가 사라짐.
   Executed in A 메시지 호출 후 funcA return.
   파괴자 실행됨. Destructor execution A 메시지 출력. Test A가 사라짐.
*/

/*
   main함수에서 funcA호출. Test A 객체 생성.
   funcB호출하여 Test B 객체 생성.
   Exception이 발생하면 funcB함수를 빠져나가게 되면서 파괴자가 실행되고 Test B 파괴.
   funcA도 그냥 종료가 됨. 파괴자 실행돼서 Test A 사라짐.
   main함수에서 Exception문구 출력.
*/