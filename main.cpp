#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

template<class Type>
class MyVector {
public:
    MyVector();
    MyVector(const MyVector&);
    MyVector(Type InputArray[], int inLength);
    ~MyVector();
    void PushBack(Type);
    const Type& operator[](int)const;
    MyVector& operator=(const MyVector&);
    bool IsEmpty()const;
    int Length()const;
    int Capacity()const;
    MyVector<Type>operator+(const MyVector&);

private:
    int length{};
    int capacity{};
    Type* dataPointer;
    void UpCapacity(int);

};
template <typename Type>
MyVector<Type>::MyVector() {
    this->length = 0;
    this->capacity = 1;
    this->dataPointer = new Type[1];
}
template<class Type>
MyVector<Type>::MyVector(const MyVector<Type>& other) {
    this->length = other.Length();
    this->capacity = other.Capacity();
    this->dataPointer = new Type[this->capacity];
    for (int i = 0; i < this->capacity; ++i) {
        this->dataPointer[i] = other[i];
    }
}
template <typename Type>
MyVector<Type>::MyVector(Type InputArray[], int inLength) {
    this->length = 0;
    this->capacity = 1;
    this->dataPointer = new Type[this->capacity];
    for (int i = 0; i < inLength; ++i) {
        this->PushBack(InputArray[i]);
    }
}

template<class Type>
MyVector<Type>::~MyVector() {
    delete[]this->dataPointer;
}

template<class Type>
void MyVector<Type>::PushBack(Type newElement) {
    this->length++;
    if (this->length > this->capacity)
        UpCapacity(2 * this->capacity);
    this->dataPointer[this->length - 1] = newElement;
}

template<class Type>
bool MyVector<Type>::IsEmpty() const {
    return not this->length;
}

template<class Type>
int MyVector<Type>::Length() const {
    return this->length;
}

template<class Type>
int MyVector<Type>::Capacity() const {
    return this->capacity;
}

template<class Type>
void MyVector<Type>::UpCapacity(int newCapacity) {

    Type* newDataPointer = new Type[newCapacity];
    for (int i = 0; i < this->length; i++)
        newDataPointer[i] = this->dataPointer[i];
    this->dataPointer = newDataPointer;
    this->capacity = newCapacity;
}


template<class Type>
const Type& MyVector<Type>::operator[](const int index) const {
    return *(this->dataPointer + index);
}

template<class Type>
MyVector<Type>& MyVector<Type>::operator=(const MyVector<Type>& other) {
    MyVector<Type> tmp(other);
    if (this->capacity != 0)
        delete[]this->dataPointer;
    this->length = tmp.Length();
    this->capacity = tmp.Length();
    this->dataPointer = new Type[this->capacity];
    for (int i = 0; i < this->capacity; ++i) {
        this->dataPointer[i] = tmp[i];
        return *this;
    }
}

template<class Type>
MyVector<Type> MyVector<Type>::operator+(const MyVector& other) {
    MyVector<Type> result = *this;
    for (int i = 0; i < other.Length(); ++i) {
        result.PushBack(other[i]);
    }
    return result;

}

template<class Type>
bool LessFunction(Type a, Type b) {
    return a->GetSpeed() <= b->GetSpeed();
}

template <class ArrayType, class LessFunctionType>
int FindMinimumIndex(ArrayType& data_array, int beginIndex, int endIndex, LessFunctionType LessFunction) {
    int minimumIndex = beginIndex;
    for (int element_number = beginIndex + 1; element_number <= endIndex; ++element_number) {
        if (LessFunction(data_array[element_number], data_array[minimumIndex])) {
            minimumIndex = element_number;
        }
    }
    return minimumIndex;
}


template <class ArrayType, class LessFunctionType>
void SelectionSort(ArrayType& data_array, int beginIndex, int endIndex, LessFunctionType LessFunction) {
    for (int element_number = beginIndex; element_number < endIndex; ++element_number) {
        int minimumIndex = FindMinimumIndex(data_array, element_number, endIndex, LessFunction);
        MySwap(data_array[minimumIndex], data_array[element_number]);
    }
}

template <class MyType>
void MySwap(MyType& v1, MyType& v2) {
    MyType v3 = v1;
    v1 = v2;
    v2 = v3;
}

class Vehicle {
public:
    Vehicle() : totalDistance(0), totalTime(0), baseSpeed(1.) {
        SetName(DefaultVehicleName);
    }
    Vehicle(const char inNameCString[], double inBaseSpeed, int inBasePrice ) : totalDistance(0),
        totalTime(0), baseSpeed(inBaseSpeed) {
        SetName(inNameCString);
    }
    virtual ~Vehicle() {
    }
    const char* GetName() const {
        return nameCString;
    }
    double GetBaseSpeed() const {
        return baseSpeed;
    }
    double GetTotalDistance() const {
        return totalDistance;
    }
    double GetTotalTime() const {
        return totalTime;
    }
    virtual bool MakeTrip(double distance) = 0;
    virtual double GetSpeed() const = 0;
    bool operator< (Vehicle& rhs) const {
        if (GetSpeed() < rhs.GetSpeed()) {
            return true;
        }
        return false;
    }

protected:
    double totalDistance;
    double totalTime;
private:
    static const int MAX_NAME_LENGTH = 50;
    void SetName(const char inNameCString[]) {
        int i;
        for (i = 0; (inNameCString[i] != 0) && (i < MAX_NAME_LENGTH); ++i) {
            nameCString[i] = inNameCString[i];
        }
        nameCString[i] = 0;
    }
    char DefaultVehicleName[16] = "Untyped Vehicle";
    char nameCString[MAX_NAME_LENGTH];
    double baseSpeed;
    constexpr static const double DefaultVehicleSpeed = -1.;
};

bool CompareDefault(Vehicle* lhs, Vehicle* rhs) {
    return *lhs < *rhs;
}

const double DefaultTimeToBoot = 0.01;
class Computer {
public:
    Computer() : baseTimeToBoot(DefaultTimeToBoot) {}
    virtual double GetTimeToBoot() {
        return baseTimeToBoot;
    }
protected:
    double baseTimeToBoot;
};

class Aeroplane : public Vehicle, private Computer {
public:
    Aeroplane(const char inNameCString[] = " ", double inBaseSpeed = 0., int inBasePrice = 0) : Vehicle(inNameCString, inBaseSpeed, inBasePrice) {

    }
    virtual double GetSpeed() const override {
        return GetBaseSpeed();
    }
    virtual double GetTimeToBoot() const {
        return DefaultTimeToBoot;
    }
    virtual bool MakeTrip(double distanceOfTrip) {
        double timeOfTrip = distanceOfTrip / GetSpeed() + GetTimeToBoot();
        if (timeSinceLastRepair + timeOfTrip > MAX_FLY_TIME) {
            return false;
        }
        timeSinceLastRepair += timeOfTrip;
        totalDistance += distanceOfTrip;
        totalTime += timeOfTrip;
        return true;
    }

    void Repair() {
        timeSinceLastRepair = 0;
    }
    double GetTimeSinceLastRepair() const {
        return timeSinceLastRepair;
    }

    void ComputerUpdate(double newTimeToBoot) {
        baseTimeToBoot = newTimeToBoot;
    }

private:
    double timeSinceLastRepair = 0;
    static const int MAX_FLY_TIME = 20000;

};
class Automobile : public Vehicle {
public:
    Automobile(const char inNameCString[] = " ", double inBaseSpeed = 0., int inBasePrice = 0) : Vehicle(inNameCString,
        inBaseSpeed,
        inBasePrice) {}

    virtual double GetSpeed() const {

        return GetBaseSpeed() * exp(-totalDistance / 500.);
    }

    virtual bool MakeTrip(double distanceOfTrip) {

        double timeOfTrip = distanceOfTrip / GetSpeed();

        totalDistance += distanceOfTrip;

        totalTime += timeOfTrip;

        return true;
    }
};
class Coach : public Vehicle {
private:
    static const int MAX_DISTANCE = 500;
public:
    Coach(const char inNameCString[] = " ", double inBaseSpeed = 0., int inBasePrice = 0) : Vehicle(inNameCString, inBaseSpeed, inBasePrice) {}
    virtual double GetSpeed() const {

        return GetBaseSpeed() * exp(-totalDistance / 500.);
    }
    virtual bool MakeTrip(double distanceOfTrip) {

        double timeOfTrip = distanceOfTrip / GetSpeed();

        if (distanceOfTrip > MAX_DISTANCE) {

            return false;

        }

        totalDistance += distanceOfTrip;

        totalTime += timeOfTrip;

        return true;

    }

};
MyVector<Coach> coaches;
MyVector<Automobile> automobiles;
MyVector<Aeroplane> aeroplanes;

void DisplayVehicles(const MyVector<Vehicle*>& vehicles) {
    cout << "\nName\t\t" << "Speed\t\t" << "Dist\t\t" << "Time\n";
    for (int i = 0; i < vehicles.Length(); ++i) {
        cout.width(10);
        cout << vehicles[i]->GetName() << "\t" << vehicles[i]->GetSpeed() << "\t\t" << vehicles[i]->GetTotalDistance() << "\t\t" << vehicles[i]->GetTotalTime() << endl;
    }
}

Aeroplane find_maxtime(const MyVector<Vehicle*> &Vec){
    cout<<"Repair aeroplane\n";
    int max = 0;
    for (int i = 0; i < Vec.Length(); ++i) {
        if(((Aeroplane*)Vec[i])->GetTimeSinceLastRepair()>((Aeroplane*)Vec[max])->GetTimeSinceLastRepair())
            max = i;
    }
    ((Aeroplane*)Vec[max])->Repair();
    return *(Aeroplane*)Vec[max];
}

void ShowAeroplanes (const MyVector<Vehicle*>& aeroplanePointers){
    cout << "\nStat aeroplanes\n";
    cout.width(10);
    cout << "Name \t\t TimesinceTO\n";
    for (int i = 0; i < aeroplanePointers.Length(); ++i) {
        printf("%s %17f\n", aeroplanePointers[i]->GetName(),
               dynamic_cast <Aeroplane *>(aeroplanePointers[i])->GetTimeSinceLastRepair());
    }
    cout << endl;
}

void CommitRandomTrips(MyVector<Vehicle*>& vehicles) {
    for (int i = 0; i < vehicles.Length(); ++i) {
        double randomDistance = double(rand() % 20001) / 10.;
        vehicles[i]->MakeTrip(randomDistance);
    }
}

int main() {
    srand(100);
    coaches.PushBack(Coach("Coach 1", 9.));
    coaches.PushBack(Coach("Coach 2", 11.));
    coaches.PushBack(Coach("Coach 3", 10.));
    coaches.PushBack(Coach("Coach 4", 9.5));
    coaches.PushBack(Coach("Coach 5"));
    automobiles.PushBack(Automobile("Automobile 1"));
    automobiles.PushBack(Automobile("Automobile 2", 90.));
    automobiles.PushBack(Automobile("Automobile 3", 120.));
    automobiles.PushBack(Automobile("Automobile 4", 150.));
    aeroplanes.PushBack(Aeroplane("Aeroplane 1", 1030.));
    aeroplanes.PushBack(Aeroplane("Aeroplane 2", 560.));
    aeroplanes.PushBack(Aeroplane("Aeroplane 3", 2200.));
    MyVector<Vehicle*> coachPointers;
    MyVector<Vehicle*> automobilePointers;
    MyVector<Vehicle*> aeroplanePointers;
    for (int i = 0; i < coaches.Length(); ++i) coachPointers.PushBack((Vehicle*)&coaches[i]);
    for (int i = 0; i < automobiles.Length(); ++i) automobilePointers.PushBack((Vehicle*)&automobiles[i]);
    for (int i = 0; i < aeroplanes.Length(); ++i) aeroplanePointers.PushBack((Vehicle*)&aeroplanes[i]);

    MyVector<Vehicle*> Veh = coachPointers + automobilePointers + aeroplanePointers;
    CommitRandomTrips(Veh);
    DisplayVehicles(Veh);
    ShowAeroplanes(aeroplanePointers);
    find_maxtime(aeroplanePointers);
    ShowAeroplanes(aeroplanePointers);
    return 0;
}
