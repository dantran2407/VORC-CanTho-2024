#include <vector>
#include <DCMotor.h>

class DCMotorManagement
{
private:
    std::vector<DCMotor*> motors;
public:
    void addNewMotor(DCMotor &motor);
    std::vector<DCMotor*> getMotorList();
};

