#include <vector>
#include <Motor/DCMotor.h>

class DCMotorManagement
{
private:
    std::vector<DCMotor*> motors;
public:
    void addNewMotor(DCMotor &motor){
        motors.push_back(&motor);
    };
    std::vector<DCMotor*> getMotorList() {
        return motors;
    };
};

