#include <iostream>
#include <algorithm>
using namespace std;

class Student {
private:
    string name;
    int age;
    float avg_mark;
public:
    Student(string name_, int age_, float avg_mark_)
        : name(name_), age(age_), avg_mark(avg_mark_) {}
    string getName() const { return name; }
    int getAge() const { return age; }
    float getAvgMark() const { return avg_mark; }
};

 
bool cmp(const Student* s1, const Student* s2) {
    return s1->getAvgMark() > s2->getAvgMark();
}

int main() {
    const int N = 3;
    Student* arr[N];
    arr[0] = new Student("Иванов", 20, 4.5);
    arr[1] = new Student("Петров", 21, 3.8);
    arr[2] = new Student("Сидоров", 19, 4.2);

     
    sort(arr, arr + N, cmp);

  
    for (int i = 0; i < N; i++) {
        cout << arr[i]->getName() << " " << arr[i]->getAge() << " " << arr[i]->getAvgMark() << endl;
        delete arr[i];   
    }

    return 0;
}
