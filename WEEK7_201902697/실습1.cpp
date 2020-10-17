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
   main�Լ����� funcAȣ���Ͽ� id�� A�� Test ��ü ����.
   funcBȣ���Ͽ� id�� B�� Test ��ü ����.
   Executed in B �޽��� ��� �� funcB return.
   �ı��� �����. Destructor execution B �޽��� ���. Test B�� �����.
   Executed in A �޽��� ȣ�� �� funcA return.
   �ı��� �����. Destructor execution A �޽��� ���. Test A�� �����.
*/

/*
   main�Լ����� funcAȣ��. Test A ��ü ����.
   funcBȣ���Ͽ� Test B ��ü ����.
   Exception�� �߻��ϸ� funcB�Լ��� ���������� �Ǹ鼭 �ı��ڰ� ����ǰ� Test B �ı�.
   funcA�� �׳� ���ᰡ ��. �ı��� ����ż� Test A �����.
   main�Լ����� Exception���� ���.
*/