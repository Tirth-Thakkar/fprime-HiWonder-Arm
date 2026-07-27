// ======================================================================
// \title  HiWonderRoboticArm.hpp
// \author thakkar
// \brief  hpp file for HiWonderRoboticArm component implementation class
// ======================================================================

#ifndef Components_HiWonderRoboticArm_HPP
#define Components_HiWonderRoboticArm_HPP

#include "Components/HiWonderRoboticArm/HiWonderRoboticArmComponentAc.hpp"

namespace Components {

class HiWonderRoboticArm final : public HiWonderRoboticArmComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct HiWonderRoboticArm object
    HiWonderRoboticArm(const char* const compName  //!< The component name
    );

    //! Destroy HiWonderRoboticArm object
    ~HiWonderRoboticArm();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for recv
    //!
    //! Receive telemetry
    void recv_handler(FwIndexType portNum,  //!< The port number
                      Fw::Buffer& buffer,
                      const Drv::ByteStreamStatus& status) override;

    //! Handler implementation for run
    void run_handler(FwIndexType portNum,  //!< The port number
                     U32 context           //!< The call order
                     ) override;

    //! Handler implementation for setClawState
    void setClawState_handler(FwIndexType portNum,  //!< The port number
                              const Components::ClawStateCmd& value) override;

    //! Handler implementation for setJointAngle
    void setJointAngle_handler(FwIndexType portNum,  //!< The port number
                               const Components::JointAngleCmd& value) override;

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command setClaw
    void setClaw_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                            U32 cmdSeq,           //!< The command sequence number
                            Components::ClawStateCmd value) override;

    //! Handler implementation for command setJointAngle
    void setJointAngle_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                  U32 cmdSeq,           //!< The command sequence number
                                  Components::JointAngleCmd value) override;
    

    // ----------------------------------------------------------------------
    // Helper Methods for HiWonderRoboticArm Component
    // ----------------------------------------------------------------------
    
    struct JointPulses {
        U16 baseUs;
        U16 shoulderUs;
        U16 elbowUs;
        U16 wristUs;
        U16 clawUs;
    };

    //! Convert one KDL joint angle to the common ArmPi Mini PWM pulse range.
    static bool jointAngleToPulse(F64 jointAngleRad, U16& pulseUs);

    //! Convert the four fixed arm joints to controller pulse targets.
    static bool jointCommandToPulses(const Components::JointAngleCmd& command, JointPulses& pulses);

    static U8 checksumCrc8(const U8* const data, const U32 dataSize);

    //! Helper method to write all joint angles to the controller.
    Drv::ByteStreamStatus armSetPosition(const Components::JointAngleCmd& commands);

    //! Request the controller-reported positions for the four arm joints.
    Drv::ByteStreamStatus armReadPosition();

    //! Helper method to bundle shared logic for sending joint angle commands
    Drv::ByteStreamStatus setJointAngle(const Components::JointAngleCmd& value);

    //! Helper method to write only claw state instead of all joints.
    Drv::ByteStreamStatus setClawState(const Components::ClawStateCmd& value);

    //! Arm Joint State
    Components::JointAngle m_currentJointAngles;
};

}  // namespace Components

#endif
