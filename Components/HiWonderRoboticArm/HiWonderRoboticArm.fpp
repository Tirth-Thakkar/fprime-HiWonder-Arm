module Components {
    @ HiWonder Robotic Arm Driver for tabletop robotic arm.

    # Driver Information
    enum Response {
        ACCEPTED
        INVALID_VALUE
        JOINT_LIMIT
        INVALID_DURATION
        UART_ERROR
    }

    struct DrvResponse {
        response: Response
        timeStamp: Fw.Time
    }

    # Joint Information
    enum Joint {
        CLAW = 1
        WRIST = 3
        ELBOW = 4
        SHOULDER = 5
        BASE = 6
    }

    enum JointStatus {
        IDLE
        MOVING
    }
    
    struct JointAngle {
        baseRad: F64,
        shoulderRad: F64,
        elbowRad: F64,
        wristRad: F64,
    }

    struct JointAngleCmd {
        jointAngle: JointAngle,
        durationMs: U32
    }

    struct JointAngleTlm {
        position: JointAngle
        status: JointStatus
    }
    
    # Claw Information  
    enum ClawPosition {
        OPEN = 0,
        CLOSE = 1
    }

    struct ClawStateCmd {
        position: ClawPosition,
        durationMs: U32
    }

    struct ClawStateTlm {
        position: ClawPosition
        status: JointStatus
    }
    
    # Port Types
    port JointAnglePort(value: JointAngleCmd)
    
    port ClawStatePort(value: ClawStateCmd)

    active component HiWonderRoboticArm {

        async command setClaw opcode 0

        async command setJointAngle opcode 1

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)

        # @ Example telemetry counter
        # telemetry ExampleCounter: U64

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"

        # @ Example port: receiving calls from the rate group
        sync input port run: Svc.Sched

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Enables command handling
        import Fw.Command

        @ Enables event handling
        import Fw.Event

        @ Enables telemetry channels handling
        import Fw.Channel

    }
}