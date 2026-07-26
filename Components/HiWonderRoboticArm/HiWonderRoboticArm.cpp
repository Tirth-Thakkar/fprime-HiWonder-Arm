// ======================================================================
// \title  HiWonderRoboticArm.cpp
// \author thakkar
// \brief  cpp file for HiWonderRoboticArm component implementation class
// ======================================================================

#include "Components/HiWonderRoboticArm/HiWonderRoboticArm.hpp"

#include <cmath>

namespace Components {

namespace {    
    static constexpr F64 PI = 3.14159265358979323846;
    static constexpr F64 NOMINAL_PULSES_PER_RADIAN = 2000.0 / PI;
    static constexpr U16 MINIMUM_PULSE_US = 500;
    static constexpr U16 MAXIMUM_PULSE_US = 2500;
    static constexpr F64 ZERO_PULSE_US = 1500.0;

    static constexpr U8 CRC8_TABLE[256] = {
        0,   94,  188, 226, 97,  63,  221, 131, 194, 156, 126, 32,  163, 253, 31,  65,  157, 195, 33,  127, 252, 162,
        64,  30,  95,  1,   227, 189, 62,  96,  130, 220, 35,  125, 159, 193, 66,  28,  254, 160, 225, 191, 93,  3,
        128, 222, 60,  98,  190, 224, 2,   92,  223, 129, 99,  61,  124, 34,  192, 158, 29,  67,  161, 255, 70,  24,
        250, 164, 39,  121, 155, 197, 132, 218, 56,  102, 229, 187, 89,  7,   219, 133, 103, 57,  186, 228, 6,   88,
        25,  71,  165, 251, 120, 38,  196, 154, 101, 59,  217, 135, 4,   90,  184, 230, 167, 249, 27,  69,  198, 152,
        122, 36,  248, 166, 68,  26,  153, 199, 37,  123, 58,  100, 134, 216, 91,  5,   231, 185, 140, 210, 48,  110,
        237, 179, 81,  15,  78,  16,  242, 172, 47,  113, 147, 205, 17,  79,  173, 243, 112, 46,  204, 146, 211, 141,
        111, 49,  178, 236, 14,  80,  175, 241, 19,  77,  206, 144, 114, 44,  109, 51,  209, 143, 12,  82,  176, 238,
        50,  108, 142, 208, 83,  13,  239, 177, 240, 174, 76,  18,  145, 207, 45,  115, 202, 148, 118, 40,  171, 245,
        23,  73,  8,   86,  180, 234, 105, 55,  213, 139, 87,  9,   235, 181, 54,  104, 138, 212, 149, 203, 41,  119,
        244, 170, 72,  22,  233, 183, 85,  11,  136, 214, 52,  106, 43,  117, 151, 201, 74,  20,  246, 168, 116, 42,
        200, 150, 21,  75,  169, 247, 182, 232, 10,  84,  215, 137, 107, 53
    };
}  // namespace

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

HiWonderRoboticArm ::HiWonderRoboticArm(const char* const compName) : HiWonderRoboticArmComponentBase(compName) {}

HiWonderRoboticArm ::~HiWonderRoboticArm() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void HiWonderRoboticArm ::recv_handler(FwIndexType portNum, Fw::Buffer& buffer, const Drv::ByteStreamStatus& status) {
    // TODO
}

void HiWonderRoboticArm ::run_handler(FwIndexType portNum, U32 context) {
    // TODO
}

void HiWonderRoboticArm ::setClawState_handler(FwIndexType portNum, const Components::ClawStateCmd& value) {
    // TODO
}

void HiWonderRoboticArm ::setJointAngle_handler(FwIndexType portNum, const Components::JointAngleCmd& value) {
    JointPulses pulses{};
    if (!this->jointCommandToPulses(value, pulses)) {
        // TODO: Report invalid joint input through the driver response path.
        return;
    }

    // TODO: Pass `pulses` and value.get_durationMs() to the controller packet writer.
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void HiWonderRoboticArm ::setClaw_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, Components::ClawStateCmd value) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

void HiWonderRoboticArm ::setJointAngle_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, Components::JointAngleCmd value) {
    // TODO
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

bool HiWonderRoboticArm::jointAngleToPulse(const F64 jointAngleRad, U16& pulseUs) {
    if (!std::isfinite(jointAngleRad)) {
        return false;
    }

    const F64 pulse = ZERO_PULSE_US + jointAngleRad * NOMINAL_PULSES_PER_RADIAN;
    if (!std::isfinite(pulse) || pulse < MINIMUM_PULSE_US || pulse > MAXIMUM_PULSE_US) {
        return false;
    }

    pulseUs = static_cast<U16>(std::lround(pulse));
    return true;
}

bool HiWonderRoboticArm::jointCommandToPulses(const Components::JointAngleCmd& command, JointPulses& pulses) {
    const Components::JointAngle& angles = command.get_jointAngle();
    return jointAngleToPulse(angles.get_baseRad(), pulses.baseUs) &&
           jointAngleToPulse(angles.get_shoulderRad(), pulses.shoulderUs) &&
           jointAngleToPulse(angles.get_elbowRad(), pulses.elbowUs) &&
           jointAngleToPulse(angles.get_wristRad(), pulses.wristUs);
}

U8 HiWonderRoboticArm::checksumCrc8(const U8* const data, const U32 dataSize) {
    FW_ASSERT(data != nullptr);
    U8 crc = 0x0;
    for (U32 i = 0; i < dataSize; i++) {
        crc = CRC8_TABLE[crc ^ data[i]];
    }
    return crc;
}

}  // namespace Components
