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

}  // namespace Components
